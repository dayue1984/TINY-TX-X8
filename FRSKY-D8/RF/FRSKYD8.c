/*******************************************************************************
--------------------------------------------------------------------------------
FRSKY-D8 注意的几点 :
(1) 遥控器按住对码键上电,进入对码状态(持续发送1000个数据包(18mS*1000 = 18S)，退出对码状态)。
(2) 根据遥控器 ID 号 ，生成一个跳频列表(共47个频段)。
(3) 对码时 地址固定为 0x03  , 对码完成后 地址设置为 遥控器ID号的后8位
(4) 相对FRSKY_D16 数据包内减少了CRC校验 ， 但启用了CC2500的硬件CRC校验
--------------------------------------------------------------------------------
FRSKYD8协议 :  整周期 36mS(共四段) 其中前三段为数据包发送 ， 最后一段为遥测接收
               对码 : 固定在 通道 0
           跳频 : 固定 47 通道 ， 通过遥控器生成的随机数来决定跳频步调。

对码数据包(30Byte) :  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
                      0x11 0x03 0x01 0xAA 0xBB 0xCC 0xDD 0xEE 0xFF 0xGG 0xHH 0x00 0xJJ 0X00 0x00 0x00 0x00 0x00
其中 :
[0] : 0x11
[1] : 0x03
[2] : 0x01
[3][4] : 遥控器ID号
[5]   [6][7][8][9][10]: [5] 为通当前道号  [6][7][8][9][10] 为 [5] 开始 后 5(包括[5]) 通道频点列表。
[11] -> [16] : 固定为 0x00
[17] : 0x01)


正常数据包(30Byte) :  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
                      0x11 0xAA 0xBB 0xCC 0xDD 0xEE 0xFF 0xGG 0x00 0xHH 0xII 0xJJ 0xKK 0xLL 0xMM 0xNN 0xOO 0xPP
其中 :
[0]    : 0x11
[1][2] : 遥控器 ID 号
[3]    : 遥测用户帧计数 (counter = (counter + 1) % 188)
[4]    : 0x00 (关闭遥测)
[5]    : 0x03
[6]  [7]  [8]  [9]  [10] [11] : 为前四通遥控数据
[12] [13] [14] [15] [16] [17] : 为后四通遥控数据

--------------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//某些接收机对时序要求特别严格 : 所以任何影响时序的部分修改特别小心。(精确到 uS)
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*******************************************************************************/
#include "include.h"

#define FRSKYD8_PACKET_LEN  18
#define FRSKYD8_BINDCHANNEL 47                          //跳频列表第47个频段固定为对码频段 0 

bool     Bind_flg = false ;
uint16_t FRSKYD8_BindCounts = 0 ;                       // 对码数据包发送个数

uint8_t  FRSKYD8_Counts = 0 ;                               // 发送数据包编号
uint8_t  FRSKYD8_HOPChannel[50] ;                       // 跳频列表(根据遥控器ID计算出47个跳频号(后三个频点无效))
uint8_t  FRSKYD8_calData[50];                           // 记录跳频通道频率值

bool CommunicationError_flg = false ;
bool HighThrottle_flg = true ;                          //高油门标志位
uint16_t TransmitterID ;                            //遥控器唯一ID
uint8_t  SendPacket[18] ;                           //发送数据包缓存

typedef enum
{
    FRSKYD8_BIND        = 0x00,
    FRSKYD8_BIND_PASSBACK   = 0x01,
    FRSKYD8_DATA        = 0x02,
    FRSKYD8_TUNE        = 0x03,
} FRSKYD8PhaseTypeDef ;
FRSKYD8PhaseTypeDef FRSKYD8Phase = FRSKYD8_DATA ;

//Channel values are 12-bit values between 988 and 2012, 1500 is the middle.
uint16_t FRSKYD8_SendDataBuff[8]  = { 1500, 1500, 988, 1500, 1500, 1500, 1500, 1500};

//FRSKYD8 通道发送顺序
const uint8_t  FRSKYD8_CH_Code[8] = {AILERON, ELEVATOR, THROTTLE, RUDDER, AUX1, AUX2, AUX3, AUX4};

//==============================================================================
//          FRSKYD8 初始化器件地址
//==============================================================================
static void FRSKYD8_InitDeviceAddr( bool IsBindFlg )
{
    CC2500_WriteReg( CC2500_18_MCSM0,    0x08 ) ;
    CC2500_WriteReg( CC2500_09_ADDR, IsBindFlg ? 0x03 : ( TransmitterID >> 8 ) & 0xFF );
    CC2500_WriteReg( CC2500_07_PKTCTRL1, 0x05 );
}

//==============================================================================
//          FRSKYD8 设置发送通道
//==============================================================================
static void FRSKYD8_TuneChannel( uint8_t Channel )
{
    CC2500_Strobe( CC2500_SIDLE );                      //进入闲置状态
    CC2500_WriteReg( CC2500_25_FSCAL1, FRSKYD8_calData[Channel] );      //设置发送通道
    CC2500_WriteReg( CC2500_0A_CHANNR, FRSKYD8_HOPChannel[Channel] );   //设置发送通道
    CC2500_Strobe( CC2500_SCAL );                   //校准频率合成器并关闭
}


//==============================================================================
//解释 : 因为上电时已经校准过频率，且回读了频率值，所以此处可以直接设置前面回读的
//频率值。避免了频率校准时间。
//==============================================================================
static void FRSKYD8_tune_chan_fast( void )
{
    CC2500_Strobe( CC2500_SIDLE );
    CC2500_WriteReg( CC2500_0D_FREQ2, Fre_Carrier_H );
    CC2500_WriteReg( CC2500_0E_FREQ1, Fre_Carrier_M );
    CC2500_WriteReg( CC2500_0F_FREQ0, Fre_Carrier_L );
    DelayUs( 2 );
    CC2500_Strobe( CC2500_SIDLE );
    CC2500_WriteReg( CC2500_0D_FREQ2, Fre_Carrier_H );
    CC2500_WriteReg( CC2500_0E_FREQ1, Fre_Carrier_M );
    CC2500_WriteReg( CC2500_0F_FREQ0, Fre_Carrier_L );
    CC2500_WriteReg( CC2500_25_FSCAL1, FRSKYD8_calData[FRSKYD8_Counts % 47] );
    CC2500_WriteReg( CC2500_0A_CHANNR, FRSKYD8_HOPChannel[FRSKYD8_Counts % 47] );
}

//==============================================================================
//对码包格式
//==============================================================================
static void  FRSKYD8_build_Bind_packet( void )
{
    //固定码
    SendPacket[0]   = 0x11;
    SendPacket[1]   = 0x03;
    SendPacket[2]   = 0x01;
    //遥控器 ID 号
    SendPacket[3]   = ( TransmitterID >> 8 ) & 0xFF  ;
    SendPacket[4]   = TransmitterID & 0xFF ;
    uint8_t  idx    = ( FRSKYD8_BindCounts % 10 ) * 5 ;
    SendPacket[5]   = idx;
    SendPacket[6]   = FRSKYD8_HOPChannel[idx++];
    SendPacket[7]   = FRSKYD8_HOPChannel[idx++];
    SendPacket[8]   = FRSKYD8_HOPChannel[idx++];
    SendPacket[9]   = FRSKYD8_HOPChannel[idx++];
    SendPacket[10]  = FRSKYD8_HOPChannel[idx++];
    //固定为0
    SendPacket[11]  = 0x00;
    SendPacket[12]  = 0x00;
    SendPacket[13]  = 0x00;
    SendPacket[14]  = 0x00;
    SendPacket[15]  = 0x00;
    SendPacket[16]  = 0x00;
    SendPacket[17]  = 0x01;
}

//==============================================================================
//数据包格式
//==============================================================================
static void  FRSKYD8_build_Data_packet( void )
{
    // 固定码 + 遥控器 ID
    SendPacket[0]   = 0x11;
    SendPacket[1]   = ( TransmitterID >> 8 ) & 0xFF  ;
    SendPacket[2]   = TransmitterID & 0xFF ;
    SendPacket[3]   = FRSKYD8_Counts;
    SendPacket[4]   = 0x00 ;
    SendPacket[5]   = 0x01 ;
    SendPacket[10] = 0;
    SendPacket[11] = 0;
    SendPacket[16] = 0;
    SendPacket[17] = 0;
    for( uint8_t i = 0; i < 8; i++ )
    {
        uint16_t value = FRSKYD8_SendDataBuff[i] + ( uint16_t )( ( float )FRSKYD8_SendDataBuff[i] / 2 + 0.5f ) ;
        if( i < 4 )
        {
            SendPacket[6 + i] = value & 0xff;
            SendPacket[10 + ( i >> 1 )] |= ( ( value >> 8 ) & 0x0f ) << ( 4 * ( i & 0x01 ) );
        }
        else
        {
            SendPacket[8 + i] = value & 0xff;
            SendPacket[16 + ( ( i - 4 ) >> 1 )] |= ( ( value >> 8 ) & 0x0f ) << ( 4 * ( ( i - 4 ) & 0x01 ) );
        }
    }
}

//==============================================================================
//FRSKYD8 : 计算 FRSKYD8 通道(通过计算得到 47 个通道 。轮询时，在这47个通道间跳频)
//相邻两频段间隔在 5 以上
// 1  - 26  : 取 16 个频点
// 27 - 52  : 取 15 个频点
// 53 - 76  : 取 16 个频点
//==============================================================================
void Calc_FRSKYD8_Channel()
{
    uint8_t  idx = 0;
    uint16_t id_tmp = ~ TransmitterID;                  //ID号 按位取反
    while( idx < 47 )
    {
        uint8_t i;
        uint8_t count_1_26 = 0, count_27_52 = 0, count_53_76 = 0;
        id_tmp = id_tmp * 0x0019660D + 0x3C6EF35F;          // Randomization
        uint8_t next_ch = ( ( id_tmp >> 8 ) % 0x4B ) + 1;       // Use least-significant byte and must be larger than 1
        for( i = 0; i < idx; i++ )
        {
            if( FRSKYD8_HOPChannel[i] == next_ch )
            {
                break;
            }
            if( FRSKYD8_HOPChannel[i] < 27 )
            {
                count_1_26++;
            }
            else if( FRSKYD8_HOPChannel[i] < 53 )
            {
                count_27_52++;
            }
            else
            {
                count_53_76++;
            }
        }
        if( i != idx )
        {
            continue;    //说明没有比对完(和其中一个频道重叠，放弃本频道，继续选择)
        }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 相邻两频道步调要大于 5 以上 (第一个频道不用判断)
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if( idx )
        {
            uint8_t Temp = 0 ;
            if( next_ch > FRSKYD8_HOPChannel[idx - 1] )
            {
                Temp = next_ch - FRSKYD8_HOPChannel[idx - 1] ;
            }
            else
            {
                Temp = FRSKYD8_HOPChannel[idx - 1] - next_ch ;
            }
            if( Temp < 5 )
            {
                continue ;
            }
        }
        if( next_ch == 0 )
        {
            break;
        }
        // 1  - 26  : 取 16 个频点
        // 27 - 52  : 取 15 个频点
        // 53 - 76  : 取 16 个频点
        if( ( ( next_ch < 27 ) && ( count_1_26 < 16 ) ) || ( ( next_ch >= 27 ) && ( next_ch < 53 ) && ( count_27_52 < 15 ) ) || ( ( next_ch >= 53 ) && ( count_53_76 < 16 ) ) )
        {
            FRSKYD8_HOPChannel[idx++] = next_ch;
        }
    }
    //对码频段固定为 0
    FRSKYD8_HOPChannel[FRSKYD8_BINDCHANNEL] = 0 ;
}

//==============================================================================
//无线发送跳转程序
//==============================================================================
uint16_t ReadFRSKYD8( void )
{
    static bool Test_flg = false ;
    static uint8_t Cnts = 0 ;
    switch( FRSKYD8Phase )
    {
        //发送对码数据包
        case FRSKYD8_BIND :
            if( FRSKYD8_BindCounts < 1200 )
            {
                FRSKYD8_TuneChannel( FRSKYD8_BINDCHANNEL ) ;
                CC2500_SetPower( CC2500_POWER_3 );      //对码时。发射功率降低
                CC2500_Strobe( CC2500_SFRX );
                FRSKYD8_build_Bind_packet() ;
                CC2500_Strobe( CC2500_SIDLE );
                CC2500_Strobe( CC2500_SFTX );
                CC2500_WriteData( SendPacket, FRSKYD8_PACKET_LEN );
                ++FRSKYD8_BindCounts ;
                Cnts = 0 ;
                FRSKYD8Phase = FRSKYD8_BIND_PASSBACK ;
            }
            else
            {
                Bind_flg = false ;
                FRSKYD8_BindCounts = 0 ;
                FRSKYD8_Counts = 0 ;
                CC2500_SetPower( CC2500_POWER_17 );
                FRSKYD8_InitDeviceAddr( Bind_flg ) ;
                //注意 : 只在正常情况下 ， 清零对码指示灯闪烁 ; 如果进入校准后 ， 会在另外一个地方清零
                if( MenuCtrl.RunStep == __stSarttUp )
                {
                    LED_State_Shake &= ~LED_BIND  ;
                    LED_State_ON    |= LED_BIND   ;
                    if( RunStatus == __stNormal )
                    {
                        beepCmd( BindFreCounts, __stStop );
                    }
                }
                FRSKYD8Phase = FRSKYD8_DATA ;
            }
            return 2443 ;
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 用于将对码包间的 9mS间隔拆成 4个 2mS(用于遥控器时基)
        // 实际协议中并不需要此步操作
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        case FRSKYD8_BIND_PASSBACK :
            if( Cnts < 3 )
            {
                ++Cnts ;
            }
            else
            {
                FRSKYD8Phase = FRSKYD8_BIND ;
            }
            return 2634 ;
        //发送数据包
        case FRSKYD8_DATA :
            if( Test_flg == false )
            {
                Test_flg = true ;
                GPIOF -> ODR |= ( 1 << 5 ) ;
            }
            else
            {
                Test_flg = false ;
                GPIOF -> ODR &= ~( 1 << 5 ) ;
            }
            FRSKYD8_Counts = ( FRSKYD8_Counts + 1 ) % 188 ;
            FRSKYD8_tune_chan_fast();
            FRSKYD8_build_Data_packet();
            CC2500_Strobe( CC2500_SIDLE );
            CC2500_WriteData( SendPacket, FRSKYD8_PACKET_LEN );
            FRSKYD8Phase = FRSKYD8_TUNE ;
            Cnts = 0 ;
            if( ( FRSKYD8_Counts % 4 ) == 2 )
            {
                return 680 ;
            }
            else if( ( FRSKYD8_Counts % 4 ) == 3 )
            {
                return 2340 ;
            }
            else
            {
                return 1520 ;
            }
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 用于将数据包间的 9mS间隔拆成 4个 2mS(用于遥控器时基)
        // 实际协议中并不需要此步操作
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        case FRSKYD8_TUNE :
            if( Cnts < 3 )
            {
                ++Cnts ;
            }
            else
            {
                FRSKYD8Phase = FRSKYD8_DATA ;
            }
            return 2550 ;
    }
    return 0 ;
}


void SetBind( void )
{
    FRSKYD8_BindCounts = 0 ;
    FRSKYD8Phase = FRSKYD8_BIND ;
    FRSKYD8_TuneChannel( FRSKYD8_HOPChannel[FRSKYD8_BINDCHANNEL] ) ;
}

//==============================================================================
//          FRSKYD16 初始化
//==============================================================================
void initFRSKYD8( void )
{
    //获取 遥控器 ID 号
    TransmitterID = GetUniqueID();
    //通过 遥控器 ID 号，计算出 47 个跳频号
    Calc_FRSKYD8_Channel();
    //初始化 CC2500 , 返回初始化是否成功标志位
    CommunicationError_flg = CC2500_Init() ;
    if( CommunicationError_flg == true )
    {
        //无线初始化失败，故障报警
        if( RunStatus < __stRF_err )            //状态更新前需要判断状态等级，是否更高(否则不更新,不提示)
        {
            beepCmd( NormalFreCounts, __stRFModelLostWarning );
            RunStatus = __stRF_err ;
            LED_State_ON = LED_NONE ;
            LED_State_Shake = LED_ALL ; //所有通道LED闪烁
        }
        //======================================================
        //跳转到故障报警状态
        //======================================================
        MenuCtrl.RunStep = __stError ;
        MenuCtrl.Sub_RunStep = 0 ;
    }
    else
    {
        // 校准 各通道频率值
        for( uint8_t i = 0 ; i < 48 ; i++ )
        {
            CC2500_Strobe( CC2500_SIDLE );
            CC2500_WriteReg( CC2500_0A_CHANNR, FRSKYD8_HOPChannel[i] );
            CC2500_Strobe( CC2500_SCAL );
            DelayUs( 1000 );
            FRSKYD8_calData[i]  =  CC2500_ReadReg( CC2500_25_FSCAL1 );
        }
        //按住对码按键上电 进入对码模式，否则
        if( !( GPIOE -> IDR & ( 1 << 7 ) ) )
        {
            Bind_flg = true ;
        }
        FRSKYD8_InitDeviceAddr( Bind_flg );
        FRSKYD8Phase = FRSKYD8_DATA ;
        FRSKYD8_TuneChannel( FRSKYD8_HOPChannel[0] ) ;
    }
}
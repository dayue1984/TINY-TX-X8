/*==============================================================================
�������� : 
(1) 4*2΢������(�ĸ�ҡ�˷ֱ�������΢������ : ��/��   ����״̬���� : �̰�������)
(2) CH5(��/��) CH6(��/��)
(3) BIND(����)   Auto(�� CH6Down ��� ��λУ׼)
(4) 8�����뿪��
==============================================================================*/
#include "include.h"

//20180801��ͨ���л����� : �̰� / ����������dip78״̬���ж��Ƿ񳤰���AUX12(CH56)��AUX34(CH78)��Ϊ����
volatile ChannelKeyTypeDef ChannelKeyValue 	= __stEmpty_Key; 

//΢������ : �̰� / ����
//�̰��ж� : down(20mS) -> up(20mS)
//�����ж� : down(1S)   -> down(50mS ����һ�ΰ���) -> up(20mS)
volatile OffSetKeyTypeDef  OffSetKeyValue  	 = __stOffset_EmptyKey ; 
// [x][0] : downcnt        [x][1] : upcnt
static uint8_t ChannelkeyTemp[5][3] = 
{
  	{ 0 , 0 } , //Ϊ���밴��˳�����
	
	//20180801��CH5-8
        // [x][0] : downcnt 
        // [x][1] : continumcnt
        // [x][2] : upcnt
	{ 0 , 0 } , 
	{ 0 , 0 } , 
	{ 0 , 0 } , 
	{ 0 , 0 } , 
};


static uint8_t OffSetKeyTemp[9][3] = 
{
  	{ 0 , 0 , 0} , //Ϊ���밴��˳�����
	
  	//R_Plus
  	{ 0 , 0 , 0} ,
  	//R_Sub
  	{ 0 , 0 , 0} ,
	
  	//T_Plus
  	{ 0 , 0 , 0} ,
  	//T_Sub
  	{ 0 , 0 , 0} ,
	
  	//A_Plus
  	{ 0 , 0 , 0} ,
  	//A_Sub
  	{ 0 , 0 , 0} ,
	
  	//E_Plus
  	{ 0 , 0 , 0} ,
  	//E_Sub
  	{ 0 , 0 , 0} ,
};


void key_int(void)
{
	//14������(8��΢������ + 4�� ͨ������ + Bind + Auto)
 	//CH5_UP + CH5_DOWN + TRIM_R_UP + TRIM_R_DOWN 
	GPIOC -> CR1 |=  (1<<7)|(1<<6)|(1<<5)|(1<<4)  ; 			
	GPIOC -> CR2 &= ~((1<<7)|(1<<6)|(1<<5)|(1<<4)) ; 
	GPIOC -> DDR &= ~((1<<7)|(1<<6)|(1<<5)|(1<<4)) ;
	
	//TRIM_T_UP + TRIM_T_DOWN
	GPIOD -> CR1 |=  (1<<1)|(1<<0) ; 
	GPIOD -> CR2 &= ~((1<<1)|(1<<0)) ; 
	GPIOD -> DDR &= ~((1<<1)|(1<<0)) ;
	
	//TRIM_A_UP + TRIM_A_DOWN + TRIM_E_UP + TRIM_E_DOWN + CH6_DOWN + CH6_UP + KEY_AUTO + KEY_BIND
	GPIOE -> CR1 |=  (1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0) ; 
	GPIOE -> CR2 &= ~((1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0)) ; 
	GPIOE -> DDR &= ~((1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0)) ;
	
	
	//8�� ���뿪��(��������) : ǰ6�����뿪�ض�Ӧǰ6ͨ�ķ��� �� ������Ϊ CH7 / CH8����ͨ��
	//INV_CH7 + INV_CH8 
  	GPIOG -> CR1 |=  (1<<3)|(1<<2)  ; 
	GPIOG -> CR2 &= ~((1<<3)|(1<<2)) ; 
	GPIOG -> DDR &= ~((1<<3)|(1<<2)) ; 
	
	//INV_CH5 + INV_CH6
  	GPIOF -> CR1 |=  (1<<1)|(1<<0)  ; 
	GPIOF -> CR2 &= ~((1<<1)|(1<<0)) ; 
	GPIOF -> DDR &= ~((1<<1)|(1<<0)) ; 
		
	//INV_A + INV_E + INV_T + INV_R
  	GPIOA -> CR1 |=  (1<<7)|(1<<6)|(1<<5)|(1<<4)   ; 
	GPIOA -> CR2 &= ~((1<<7)|(1<<6)|(1<<5)|(1<<4)) ; 
	GPIOA -> DDR &= ~((1<<7)|(1<<6)|(1<<5)|(1<<4)) ; 
	
	//1�� ������/�ձ��� ѡ�񺸵�   ����(PC0��©�����������������óɸ������룬ע��PCB��������������)
  	GPIOC -> CR1 &= ~(1<<0) ; 
	GPIOC -> CR2 &= ~(1<<0) ; 
	GPIOC -> DDR &= ~(1<<0) ;
}


static void ChannelKey_Scan(GPIO_TypeDef* GPIOx , uint8_t GPIO_Pin , ChannelKeyTypeDef KeyNum)
{            
        
        //��������
	if(!(GPIOx -> IDR & (uint8_t)GPIO_Pin))
	{
                bool LongClick_flg = (bool)(((KeyNum < __stKey_CH7) && (GPIOG -> IDR & (1<<2)==1))||((KeyNum > __stKey_CH6) && (GPIOG -> IDR & (1<<3)==1)));
         
	  	ChannelkeyTemp[KeyNum][2] = 0;
		if(ChannelkeyTemp[KeyNum][0] < 50) 
		{
			++ChannelkeyTemp[KeyNum][0];
			ChannelkeyTemp[KeyNum][1] = 0 ; 
			
			//�����̰�
                        if(ChannelkeyTemp[KeyNum][0] == 5 && !LongClick_flg) ChannelKeyValue = KeyNum ; 
		}
		else
                {
		  	//��������
		 	if(ChannelkeyTemp[KeyNum][1] = 15 && LongClick_flg) 
                        {
                          //ChannelkeyTemp[KeyNum][1] = 0 ;   
                          ChannelKeyValue = KeyNum ;
                          
                        }
			else
			{
                          ++ChannelkeyTemp[KeyNum][1];	
			} 
		}
		 
	}
	else
	{	//�����ɿ� 50mS
		if(ChannelkeyTemp[KeyNum][2] < 5) ++ChannelkeyTemp[KeyNum][2];
		else
		{
			ChannelkeyTemp[KeyNum][0] = 0 ;
		}
	}    
        
}

static void OffSetKey_Scan(GPIO_TypeDef* GPIOx , uint8_t GPIO_Pin , OffSetKeyTypeDef KeyNum)
{
  	//��������
	if(!(GPIOx -> IDR & (uint8_t)GPIO_Pin))
	{
	  	OffSetKeyTemp[KeyNum][2] = 0;
		if(OffSetKeyTemp[KeyNum][0] < 50) 
		{
			++OffSetKeyTemp[KeyNum][0];
			OffSetKeyTemp[KeyNum][1] = 0 ; 
			
			//�����̰�
			if(OffSetKeyTemp[KeyNum][0] == 5) 
			{
				OffSetKeyValue = KeyNum ; 
			}
		}
		else
		{
		  	//������������
		 	if(OffSetKeyTemp[KeyNum][1] < 15) ++OffSetKeyTemp[KeyNum][1];	
			else  
			{
			  	OffSetKeyTemp[KeyNum][1] = 0 ; 
				OffSetKeyValue = KeyNum ;
			} 
		}
		 
	}
	else
	{	//�����ɿ� 50mS
		if(OffSetKeyTemp[KeyNum][2] < 5) ++OffSetKeyTemp[KeyNum][2];
		else
		{
			OffSetKeyTemp[KeyNum][0] = 0 ;
		}
	}
}

void key_Scan(void)
{
	//CH5
	ChannelKey_Scan(GPIOC , GPIO_Pin_4 , __stKey_CH5) ;
        //CH6
	ChannelKey_Scan(GPIOC , GPIO_Pin_5 , __stKey_CH6) ;
	//CH7
	ChannelKey_Scan(GPIOE , GPIO_Pin_5 , __stKey_CH7) ;
        //CH8
	ChannelKey_Scan(GPIOE , GPIO_Pin_4 , __stKey_CH8) ;
	
	//8��΢������
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!! ע�� : ������ �� �ձ��� ΢�� �������� !!!!!!!!!!!!!!!!!!!!!!
	if(RFHabit == __AmericaPlayer)
	{
		OffSetKey_Scan(GPIOC , GPIO_Pin_7 , __stKey_T_Plus) ; 
		OffSetKey_Scan(GPIOC , GPIO_Pin_6 , __stKey_T_Sub) ; 
		
		OffSetKey_Scan(GPIOE , GPIO_Pin_0 , __stKey_E_Plus) ; 
		OffSetKey_Scan(GPIOE , GPIO_Pin_1 , __stKey_E_Sub) ; 
	}
	else
	{
		OffSetKey_Scan(GPIOE , GPIO_Pin_0 , __stKey_T_Plus) ; 
		OffSetKey_Scan(GPIOE , GPIO_Pin_1 , __stKey_T_Sub) ; 
		
		OffSetKey_Scan(GPIOC , GPIO_Pin_7 , __stKey_E_Plus) ; 
		OffSetKey_Scan(GPIOC , GPIO_Pin_6 , __stKey_E_Sub) ; 
	}

	OffSetKey_Scan(GPIOD , GPIO_Pin_1 , __stKey_R_Plus) ; 
	OffSetKey_Scan(GPIOD , GPIO_Pin_0 , __stKey_R_Sub) ; 

  
	OffSetKey_Scan(GPIOE , GPIO_Pin_3 , __stKey_A_Plus) ; 
	OffSetKey_Scan(GPIOE , GPIO_Pin_2 , __stKey_A_Sub) ; 
	

	
	//! ���΢������ͬһʱ��ֻ�ܴ���һ�Σ��ұ�΢������ͬһʱ��ֻ�ܴ���һ��
	//!!!!!!!!! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*uint8_t LefOffSetKey_Temp = 0xFF ;   uint8_t RightOffSetKey_Temp = 0xFF ; 
	static uint8_t LefOffSetKey_LastTemp   = 0xFF ; 
	static uint8_t RightOffSetKey_LastTemp = 0xFF ; 
	
	if(!(GPIOD -> IDR & (1<<1))) LefOffSetKey_Temp &= 0xFE ; 
	if(!(GPIOD -> IDR & (1<<0))) LefOffSetKey_Temp &= 0xFD ; 
	if(!(GPIOC -> IDR & (1<<7))) LefOffSetKey_Temp &= 0xFB ; 
	if(!(GPIOC -> IDR & (1<<6))) LefOffSetKey_Temp &= 0xF7 ; 
	if(!(GPIOE -> IDR & (1<<7))) LefOffSetKey_Temp &= 0xEF ; 
	
	if(!(GPIOE -> IDR & (1<<3))) RightOffSetKey_Temp &= 0xFE ; 
	if(!(GPIOE -> IDR & (1<<2))) RightOffSetKey_Temp &= 0xFD ; 
	if(!(GPIOE -> IDR & (1<<0))) RightOffSetKey_Temp &= 0xFB ; 
	if(!(GPIOE -> IDR & (1<<1))) RightOffSetKey_Temp &= 0xF7 ; 
	if(!(GPIOE -> IDR & (1<<6))) RightOffSetKey_Temp &= 0xEF ; 
	
        #warning  ȷ��΢�������Ƿ���ȷ
	if(LefOffSetKey_LastTemp == LefOffSetKey_Temp)
	{
	  	if(OffSetKeyTemp[0][0] < 50) 
		{
			++OffSetKeyTemp[0][0];
			OffSetKeyTemp[0][1] = 0 ; 
			if(OffSetKeyTemp[0][0] == 5) 
			{
			  	if(LefOffSetKey_Temp == 0xFE) 		OffSetKeyValue = __stKey_R_Plus ;//�����ά���� : ��
				else if(LefOffSetKey_Temp == 0xFD) 	OffSetKeyValue = __stKey_R_Sub ; //�����ά���� : ��
				else if(LefOffSetKey_Temp == 0xFB) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_T_Plus ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_E_Plus ;  //�����ά���� : ��
				}
				else if(LefOffSetKey_Temp == 0xF7) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_T_Sub ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_E_Sub ;  //�����ά���� : ��
				}
			}
		}
		else
		{
		  	//������������
		 	if(OffSetKeyTemp[0][1] < 15) ++OffSetKeyTemp[0][1];	
			else  
			{
			  	OffSetKeyTemp[0][1] = 0 ; 
			  	if(LefOffSetKey_Temp == 0xFE) 		OffSetKeyValue = __stKey_R_Plus ;//�����ά���� : ��
				else if(LefOffSetKey_Temp == 0xFD) 	OffSetKeyValue = __stKey_R_Sub ; //�����ά���� : ��
				else if(LefOffSetKey_Temp == 0xFB) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_T_Plus ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_E_Plus ;  //�����ά���� : ��
				}
				else if(LefOffSetKey_Temp == 0xF7) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_T_Sub ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_E_Sub ;  //�����ά���� : ��
				}
			} 
		}
	}
	else
	{
	  	LefOffSetKey_LastTemp = LefOffSetKey_Temp ; 
		OffSetKeyTemp[0][0] = 0 ; 
		OffSetKeyTemp[0][1] = 0 ;
	}
	
	
	if(RightOffSetKey_LastTemp == RightOffSetKey_Temp)
	{
	  	if(OffSetKeyTemp[1][0] < 50) 
		{
			++OffSetKeyTemp[1][0];
			OffSetKeyTemp[1][1] = 0 ; 
			if(OffSetKeyTemp[1][0] == 5) 
			{
			  	if(RightOffSetKey_Temp == 0xFE) 	OffSetKeyValue = __stKey_A_Plus ;//�����ά���� : ��
				else if(RightOffSetKey_Temp == 0xFD) 	OffSetKeyValue = __stKey_A_Sub ; //�����ά���� : ��
				else if(RightOffSetKey_Temp == 0xFB) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_E_Plus ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_T_Plus ;  //�����ά���� : ��
				}
				else if(RightOffSetKey_Temp == 0xF7) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_E_Sub ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_T_Sub ;  //�����ά���� : ��
				}
			}
		}
		else
		{
		  	//������������
		 	if(OffSetKeyTemp[1][1] < 15) ++OffSetKeyTemp[1][1];	
			else  
			{
			  	OffSetKeyTemp[1][1] = 0 ; 
			  	if(RightOffSetKey_Temp == 0xFE) 	OffSetKeyValue = __stKey_A_Plus ;//�����ά���� : ��
				else if(RightOffSetKey_Temp == 0xFD) 	OffSetKeyValue = __stKey_A_Sub ; //�����ά���� : ��
				else if(RightOffSetKey_Temp == 0xFB) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_E_Plus ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_T_Plus ;  //�����ά���� : ��
				}
				else if(RightOffSetKey_Temp == 0xF7) 	
				{
					if(RFHabit == __AmericaPlayer)	OffSetKeyValue = __stKey_E_Sub ; //�����ά���� : ��
					else				OffSetKeyValue = __stKey_T_Sub ;  //�����ά���� : ��
				}
			} 
		}
	}
	else
	{
	  	RightOffSetKey_LastTemp = RightOffSetKey_Temp ; 
		OffSetKeyTemp[1][0] = 0 ; 
		OffSetKeyTemp[1][1] = 0 ;
	}*/
}

void InversionKey_Scan(void)
{
  	uint8_t InversionKey_Temp = 0 ; 
	static uint8_t  InversionKey_LastTemp = 0 ; 
	static  uint8_t InversionKeySame_cnt  = 0 ; 
	
	//6�������뿪��
  	InversionKey_Temp  = (GPIOA -> IDR & 0xF0) ;
	InversionKey_Temp |= (GPIOG -> IDR & 0x0C) ;
	InversionKey_Temp |= (GPIOF -> IDR & 0x03) ;
	
	if(InversionKey_Temp == InversionKey_LastTemp)
	{
		if(InversionKeySame_cnt < 25) ++InversionKeySame_cnt ; 
		else 
		{
		  	//======================================================
		  	//��¼��ǰ ���򿪹ء� �����󣬸ı䷴�򿪹���Ч��ֱ���´��ϵ硣
		  	//======================================================
		  	ChannelInversion_flg = 0x3F ; 
		  	if(InversionKey_Temp & 0x80) ChannelInversion_flg &= 0xFE ;	//RUDDER
			if(InversionKey_Temp & 0x10) ChannelInversion_flg &= 0xFD ;	//THROTTLE
			if(InversionKey_Temp & 0x40) ChannelInversion_flg &= 0xFB ;	//ELEVATOR
			if(InversionKey_Temp & 0x20) ChannelInversion_flg &= 0xF7 ;	//AILERON
			
			if(InversionKey_Temp & 0x01) ChannelInversion_flg &= 0xAF ;	//AUX1��3
			if(InversionKey_Temp & 0x02) ChannelInversion_flg &= 0x5F ;	//AUX2��4
			
		}
	}
	else
	{
		InversionKeySame_cnt = 0 ; 
		InversionKey_LastTemp = InversionKey_Temp ; 
	}
	
	
	//!!!!!!!!!!!!!!!!!!!!! ע�� !!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!����ձ��ֺ���̽� , �����ձ��֡���֮��������!!!!!!!
	//!!������ �� �ձ��� ��λ���   ΢��������Ҫ����ӳ��!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	uint8_t RFHabit_flg = (GPIOC -> IDR & (1<<0)) ;
	static uint8_t RFHabit_Lastflg = 0 ; 
	static uint8_t HabitSameCnt = 0 ; 
	if(RFHabit_flg == RFHabit_Lastflg) 
	{
	  	if(HabitSameCnt < 25) ++HabitSameCnt ; 
		else 
		{
			if(RFHabit_Lastflg)
			{
				RFHabit = __AmericaPlayer ;
			}
			else
			{
				RFHabit = __JapanPlayer ;
			}
		}
	}
	else
	{
	  	RFHabit_Lastflg = RFHabit_flg ;
		HabitSameCnt = 0 ; 
	}
}
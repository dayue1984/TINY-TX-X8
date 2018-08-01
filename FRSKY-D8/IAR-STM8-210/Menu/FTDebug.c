/******************************************************************************
--------------------------------------------------------------------------------
���뼫ֵ�궨���� : ��ס CH6(��) + ����ά����(Enter) �ϵ磬���뼫ֵ�궨
--------------------------------------------------------------------------------
����У׼ : 
(1)�궨 Rud �� AIL �� ELE ҡ�˵���λֵ(ȡ10����Чֵ��ȥ�������Сֵ������ƽ��)
(2)�궨 Rud �� THR  ��AIL �� ELE ҡ�˵������Сֵ(ȡ10����Чֵ��ȥ�������Сֵ������ƽ��)
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
*******************************************************************************/
#include "include.h"

bool   FTDebug_err_flg = false ; 						//��λУ׼���ϱ�־λ(��λֵ������Ч)
static bool     MAXValueDebug_RightOrLeftflg = false ; 				//��ֵУ׼��ҡ�˻�����ҡ�˱�־λ
static uint8_t  SamplingCounts = 0 ; 						//��������
static uint8_t  OneSamplingDelayTime = 0 ; 					//ÿ�β�����ʱʱ��(���ǵ��������ݻ�����ÿ10mS����һ�Σ�������λ�궨�����ݻ���Ҳÿ10mS����һ��)
static uint16_t SamplingBuffer[4][10] ;  					//�������ݻ���
static uint16_t Sampling_OK_DelayCNT = 0 ; 					//���������ʱ��ת����
static uint16_t DisLEDCnts = 0 ; 
static uint16_t SamplingMaxMinValue_StabilizeCnts = 0 ; 			//������ֵ�ȶ�����

//==============================================================================
//��ȡ10������ҡ����λֵ(�ɿ�ҡ��ʱ������)
//ȥ��һ�����ֵ��һ����Сֵ������8����ƽ��
//==============================================================================
static void FT_GetHSKMidValue(void)
{
  	uint16_t MaxValue_Temp = 0 ; 						//������������ֵ
	uint16_t MinValue_Temp = 0 ; 						//�����������Сֵ
	uint32_t SumValue_Temp = 0 ; 						//�����ۼӺ�
	uint16_t Temp = 0 ; 
	uint8_t  i = 0 ; 

	if(SamplingCounts < 10) 
	{
	  	if(OneSamplingDelayTime < 5)
		{
			++OneSamplingDelayTime ; 
		}
		else
		{
			SamplingBuffer[RUDDER][SamplingCounts]   = Sampling_Data[RUDDER]; 
			SamplingBuffer[ELEVATOR][SamplingCounts] = Sampling_Data[ELEVATOR];
			SamplingBuffer[AILERON][SamplingCounts]  = Sampling_Data[AILERON];
			OneSamplingDelayTime = 0 ; 
			++SamplingCounts ; 	
		}
	}
	else
	{
	  	//==============================================================
	  	//��ʼ�� LED ״̬
	  	//==============================================================
		LED_State_Shake = LED_CH5 | LED_CH6_M | LED_CH6_H ;
		LED_State_ON = 0x00 ; 
	  
	  	//��ʼ��������λУ׼���ϱ�־λ
		FTDebug_err_flg = false ; 
		
		//==============================================================
	  	//ÿ��λȥ�������Сֵ����ƽ���õ���λֵ
	  	//==============================================================
	  	//��ʼ����ֵ
	  	MaxValue_Temp = Input_Min ; 
		MinValue_Temp = Input_Max ; 
		SumValue_Temp = 0 ; 
	  	for(i = 0; i < 10 ;i++)
		{
			if(MaxValue_Temp < SamplingBuffer[RUDDER][i]) MaxValue_Temp = SamplingBuffer[RUDDER][i] ; 
			if(MinValue_Temp > SamplingBuffer[RUDDER][i]) MinValue_Temp = SamplingBuffer[RUDDER][i] ; 
			SumValue_Temp += SamplingBuffer[RUDDER][i] ; 
		}
		Temp = (uint16_t)((SumValue_Temp - MaxValue_Temp - MinValue_Temp) / 8) ; 
		if((Temp < AD_MidValue_Min) || (Temp > AD_MidValue_Max)) 		 //��λֵУ׼��Ч���ж�
		{
			FTDebug_err_flg = true ; 
			LED_State_Shake |= LED_CH5 ; LED_State_ON &= ~LED_CH5 ;	 // RUDDER ��λֵ У׼������ʾ  CH5_L LED��˸
		}
		else
		{
		  	LED_State_ON |= LED_CH5 ; LED_State_Shake &= ~LED_CH5 ;	 // RUDDER ��λֵ У׼������ʾ
			Sampling_MaxMinData[RUDDER][MIDDAT] = Temp ;
		}
		
	  	//��ʼ����ֵ
	  	MaxValue_Temp = Input_Min ; 
		MinValue_Temp = Input_Max ; 
		SumValue_Temp = 0 ; 
	  	for(i = 0; i < 10 ;i++)
		{
			if(MaxValue_Temp < SamplingBuffer[ELEVATOR][i]) MaxValue_Temp = SamplingBuffer[ELEVATOR][i] ; 
			if(MinValue_Temp > SamplingBuffer[ELEVATOR][i]) MinValue_Temp = SamplingBuffer[ELEVATOR][i] ; 
			SumValue_Temp += SamplingBuffer[ELEVATOR][i] ; 
		}
		Temp = (uint16_t)((SumValue_Temp - MaxValue_Temp - MinValue_Temp) / 8) ;  
		//��λֵУ׼��Ч���ж�
		if((Temp < AD_MidValue_Min) || (Temp > AD_MidValue_Max)) 
		{
			FTDebug_err_flg = true ; 
			LED_State_Shake |= LED_CH6_H ; LED_State_ON &= ~LED_CH6_H ;	 // ELEVATOR ��λֵ У׼������ʾ
		}
		else
		{
		  	LED_State_ON |= LED_CH6_H ; LED_State_Shake &= ~LED_CH6_H ;	 // ELEVATOR ��λֵ У׼������ʾ
			Sampling_MaxMinData[ELEVATOR][MIDDAT] = Temp ; 
		}
		
	  	//��ʼ����ֵ
	  	MaxValue_Temp = Input_Min ; 
		MinValue_Temp = Input_Max ; 
		SumValue_Temp = 0 ; 
	  	for(i = 0; i < 10 ;i++)
		{
			if(MaxValue_Temp < SamplingBuffer[AILERON][i]) MaxValue_Temp = SamplingBuffer[AILERON][i] ; 
			if(MinValue_Temp > SamplingBuffer[AILERON][i]) MinValue_Temp = SamplingBuffer[AILERON][i] ; 
			SumValue_Temp += SamplingBuffer[AILERON][i] ; 
		}
		Temp = (uint16_t)((SumValue_Temp - MaxValue_Temp - MinValue_Temp) / 8) ; 
		//��λֵУ׼��Ч���ж�
		if((Temp < AD_MidValue_Min) || (Temp > AD_MidValue_Max)) 
		{
			FTDebug_err_flg = true ; 
			LED_State_Shake |= LED_CH7 ; LED_State_ON &= ~LED_CH7 ;	 // AILERON ��λֵ У׼������ʾ
		}
		else
		{
		  	LED_State_ON |= LED_CH7 ; LED_State_Shake &= ~LED_CH7 ;	 // AILERON ��λֵ У׼������ʾ
			Sampling_MaxMinData[AILERON][MIDDAT]  = Temp ; 
		}
		
		if(FTDebug_err_flg == false)
		{
		  	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//��λУ׼�ɹ��󣬴洢������λADֵ��
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			Write_EE_Byte((Sampling_MaxMinData[RUDDER][MIDDAT] >> 8)     , RUD_MIDVALUE_ADDR);
			Write_EE_Byte((Sampling_MaxMinData[RUDDER][MIDDAT] & 0xFF)   , RUD_MIDVALUE_ADDR + 1);
			Write_EE_Byte((Sampling_MaxMinData[ELEVATOR][MIDDAT] >> 8)   , ELE_MIDVALUE_ADDR);
			Write_EE_Byte((Sampling_MaxMinData[ELEVATOR][MIDDAT] & 0xFF) , ELE_MIDVALUE_ADDR + 1);
			Write_EE_Byte((Sampling_MaxMinData[AILERON][MIDDAT] >> 8)    , AIL_MIDVALUE_ADDR);
			Write_EE_Byte((Sampling_MaxMinData[AILERON][MIDDAT] & 0xFF)  , AIL_MIDVALUE_ADDR + 1);
			
			
			Sampling_OK_DelayCNT = 0 ; 
			MAXValueDebug_RightOrLeftflg = false ; 
			MenuCtrl.Sub_RunStep = 1 ; 
			
			//��������ʾͨ�����óɹ�(ֻ����������²���ʾ����ֹ��������������ʾ :����͵�ѹ����)
			if(RunStatus == __stNormal)   beepCmd(NormalFreCounts , __stMidADAdjustDown);
		}
		else    
		{
			if(RunStatus < __stNOAdjust)				//״̬����ǰ��Ҫ�ж�״̬�ȼ����Ƿ����(���򲻸���,����ʾ)
			{
			  	RunStatus = __stNOAdjust ;
				beepCmd(NormalFreCounts , __stFastContinumWarning);
			}
			
			//��ת�� ���ع���(��������)
			MenuCtrl.RunStep	= __stError ; 
			MenuCtrl.Sub_RunStep 	=  0 ; 
		}
	}
}

//==============================================================================
//��λУ׼��Ϻ�������ʱ(У׼״̬��ʾ)����ת����ֵУ׼
//==============================================================================
static void FT_SkipDelay(void)
{
	if(Sampling_OK_DelayCNT < 1000) ++Sampling_OK_DelayCNT;
	else
	{
		Sampling_OK_DelayCNT = 0 ; 
		Init_ChannelDis(false);
		MAXValueDebug_RightOrLeftflg = false ; 
		DisLEDCnts = 0 ;
	
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//��ʼ����ҡ�˵ļ�ֵ(��У��ǰ������ΪĬ��ֵ)
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for(uint8_t i = 0 ; i<4 ; i++)
		{
			Sampling_MaxMinData[i][MAXDAT] = Input_Min ; 
			Sampling_MaxMinData[i][MINDAT] = Input_Max ; 
		}
		
		//��У�����ҡ�� ��ֵ(��Դָʾ����˸ ��ʾ)
		LED_State_Shake = LED_VOLT ; 
		MenuCtrl.Sub_RunStep = 2 ; 
	}
}

//==============================================================================
//��ȡҡ�����ֵ����Сֵ����ʾ�û�ת��ҡ�ˡ�
//����ȡ����Ч�����Сֵʱ������ʱ5S������и��£������ȴ�5S�����û�У�У׼���
//==============================================================================
static void  FT_GetHSKMaxMinValue(void)
{
	//======================================================================
	//LED��ѭ����ת �� ��ʾ�û�ҡ��ҡ��
	//======================================================================
	if(DisLEDCnts < 600) ++DisLEDCnts ; 
	else                  DisLEDCnts = 0 ; 
	if(DisLEDCnts < 100)  		LED_State_ON = LED_CH6_H ; 
	else if(DisLEDCnts < 200)       LED_State_ON = LED_CH6_M ; 
	else if(DisLEDCnts < 300)       LED_State_ON = LED_CH5 ; 
	else if(DisLEDCnts < 400)       LED_State_ON = LED_CH7 ; 
	else if(DisLEDCnts < 500)       LED_State_ON = LED_CH8_M ; 
	else                            LED_State_ON = LED_CH8_H ;
	
	//У׼��ҡ�������Сֵ : ע������ ������/�ձ���
	if(MAXValueDebug_RightOrLeftflg == false)
	{
		//�ҳ���ҡ����ͨ���������Сֵ
		if(RFHabit == __AmericaPlayer)
		{
		  	if(Sampling_MaxMinData[RUDDER][MAXDAT] < Sampling_Data[RUDDER])   { Sampling_MaxMinData[RUDDER][MAXDAT] = Sampling_Data[RUDDER] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[RUDDER][MINDAT] > Sampling_Data[RUDDER])   { Sampling_MaxMinData[RUDDER][MINDAT] = Sampling_Data[RUDDER] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if(Sampling_MaxMinData[THROTTLE][MAXDAT] < Sampling_Data[THROTTLE]) { Sampling_MaxMinData[THROTTLE][MAXDAT] = Sampling_Data[THROTTLE] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[THROTTLE][MINDAT] > Sampling_Data[THROTTLE]) { Sampling_MaxMinData[THROTTLE][MINDAT] = Sampling_Data[THROTTLE] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if((Sampling_MaxMinData[RUDDER][MAXDAT]   > MAXValue_Min) && (Sampling_MaxMinData[RUDDER][MINDAT]   < MINValue_Max) 
			&& (Sampling_MaxMinData[THROTTLE][MAXDAT] > MAXValue_Min) && (Sampling_MaxMinData[THROTTLE][MINDAT] < MINValue_Max))
			{
				if(SamplingMaxMinValue_StabilizeCnts < 1000) ++SamplingMaxMinValue_StabilizeCnts ; 
				else
				{
				  	//��У���ұ�ҡ�� ��ֵ(��Դָʾ�Ƴ���   ����ָʾ����˸��ʾ)
				  	LED_State_Shake = LED_BIND ; 
					MAXValueDebug_RightOrLeftflg = true ; 
					SamplingMaxMinValue_StabilizeCnts = 0 ; 
					//��������ʾͨ�����óɹ�(ֻ����������²���ʾ����ֹ��������������ʾ :����͵�ѹ����)
					if(RunStatus == __stNormal)   beepCmd(NormalFreCounts , __stMidADAdjustDown);
				}
			}
			else
			{
				SamplingMaxMinValue_StabilizeCnts = 0 ; 
			}
		}
		else
		{
		  	if(Sampling_MaxMinData[RUDDER][MAXDAT] < Sampling_Data[RUDDER])   { Sampling_MaxMinData[RUDDER][MAXDAT] = Sampling_Data[RUDDER] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[RUDDER][MINDAT] > Sampling_Data[RUDDER])   { Sampling_MaxMinData[RUDDER][MINDAT] = Sampling_Data[RUDDER] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if(Sampling_MaxMinData[ELEVATOR][MAXDAT] < Sampling_Data[ELEVATOR]) { Sampling_MaxMinData[ELEVATOR][MAXDAT] = Sampling_Data[ELEVATOR] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[ELEVATOR][MINDAT] > Sampling_Data[ELEVATOR]) { Sampling_MaxMinData[ELEVATOR][MINDAT] = Sampling_Data[ELEVATOR] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if((Sampling_MaxMinData[RUDDER][MAXDAT]   > MAXValue_Min) && (Sampling_MaxMinData[RUDDER][MINDAT]   < MINValue_Max) 
			&& (Sampling_MaxMinData[ELEVATOR][MAXDAT] > MAXValue_Min) && (Sampling_MaxMinData[ELEVATOR][MINDAT] < MINValue_Max))
			{
				if(SamplingMaxMinValue_StabilizeCnts < 1000) ++SamplingMaxMinValue_StabilizeCnts ; 
				else
				{
				  	//��У���ұ�ҡ�� ��ֵ(��Դָʾ�Ƴ���   ����ָʾ����˸��ʾ)
				  	LED_State_Shake = LED_BIND ; 
					MAXValueDebug_RightOrLeftflg = true ; 
					SamplingMaxMinValue_StabilizeCnts = 0 ;
					//��������ʾͨ�����óɹ�(ֻ����������²���ʾ����ֹ��������������ʾ :����͵�ѹ����)
					if(RunStatus == __stNormal)   beepCmd(NormalFreCounts , __stMidADAdjustDown);
				}
			}
			else
			{
				SamplingMaxMinValue_StabilizeCnts = 0 ; 
			}
		}
	}
	else
	{
	  	LED_State_ON |= LED_VOLT ;
		//�ҳ���ҡ����ͨ���������Сֵ
		if(RFHabit == __AmericaPlayer)
		{
		  	if(Sampling_MaxMinData[AILERON][MAXDAT] < Sampling_Data[AILERON])   { Sampling_MaxMinData[AILERON][MAXDAT] = Sampling_Data[AILERON] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[AILERON][MINDAT] > Sampling_Data[AILERON])   { Sampling_MaxMinData[AILERON][MINDAT] = Sampling_Data[AILERON] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if(Sampling_MaxMinData[ELEVATOR][MAXDAT] < Sampling_Data[ELEVATOR]) { Sampling_MaxMinData[ELEVATOR][MAXDAT] = Sampling_Data[ELEVATOR] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[ELEVATOR][MINDAT] > Sampling_Data[ELEVATOR]) { Sampling_MaxMinData[ELEVATOR][MINDAT] = Sampling_Data[ELEVATOR] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if((Sampling_MaxMinData[AILERON][MAXDAT]  > MAXValue_Min) && (Sampling_MaxMinData[AILERON][MINDAT]  < MINValue_Max) 
			&& (Sampling_MaxMinData[ELEVATOR][MAXDAT] > MAXValue_Min) && (Sampling_MaxMinData[ELEVATOR][MINDAT] < MINValue_Max))
			{
				if(SamplingMaxMinValue_StabilizeCnts < 1000) ++SamplingMaxMinValue_StabilizeCnts ; 
				else
				{
					LED_State_ON = LED_BIND ;  
					MenuCtrl.Sub_RunStep = 3 ; 
					Sampling_OK_DelayCNT = 0 ; 
					//��������ʾͨ�����óɹ�(ֻ����������²���ʾ����ֹ��������������ʾ :����͵�ѹ����)
					if(RunStatus == __stNormal)   beepCmd(NormalFreCounts , __stMidADAdjustDown);
				}
			}
			else
			{
				SamplingMaxMinValue_StabilizeCnts = 0 ; 
			}
		}
		else
		{
		  	if(Sampling_MaxMinData[AILERON][MAXDAT] < Sampling_Data[AILERON])   { Sampling_MaxMinData[AILERON][MAXDAT] = Sampling_Data[AILERON] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[AILERON][MINDAT] > Sampling_Data[AILERON])   { Sampling_MaxMinData[AILERON][MINDAT] = Sampling_Data[AILERON] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if(Sampling_MaxMinData[THROTTLE][MAXDAT] < Sampling_Data[THROTTLE]) { Sampling_MaxMinData[THROTTLE][MAXDAT] = Sampling_Data[THROTTLE] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			if(Sampling_MaxMinData[THROTTLE][MINDAT] > Sampling_Data[THROTTLE]) { Sampling_MaxMinData[THROTTLE][MINDAT] = Sampling_Data[THROTTLE] ; SamplingMaxMinValue_StabilizeCnts = 0 ; }
			
			if((Sampling_MaxMinData[AILERON][MAXDAT]  > MAXValue_Min)  && (Sampling_MaxMinData[AILERON][MINDAT]  < MINValue_Max) 
			&& (Sampling_MaxMinData[THROTTLE][MAXDAT] > MAXValue_Min)  && (Sampling_MaxMinData[THROTTLE][MINDAT] < MINValue_Max))
			{
				if(SamplingMaxMinValue_StabilizeCnts < 1000) ++SamplingMaxMinValue_StabilizeCnts ; 
				else
				{
				  	LED_State_ON = LED_BIND ;  
					MenuCtrl.Sub_RunStep = 3 ; 
					Sampling_OK_DelayCNT = 0 ; 
					//��������ʾͨ�����óɹ�(ֻ����������²���ʾ����ֹ��������������ʾ :����͵�ѹ����)
					if(RunStatus == __stNormal)   beepCmd(NormalFreCounts , __stMidADAdjustDown);
				}
			}
			else
			{
				SamplingMaxMinValue_StabilizeCnts = 0 ; 
			}
		}
	}
}

//==============================================================================
//����У׼�ɹ�����ʾ�ɹ�(��ʾ2S������ת)
//��ת�������׶�
//==============================================================================
static void FT_OK(void)
{
	if(Sampling_OK_DelayCNT < 1000) ++Sampling_OK_DelayCNT;
	else
	{
		Sampling_OK_DelayCNT = 0 ; 
		//======================================
		//  �洢����У׼��ֵ����������ƫ��ֵ
		//======================================
		Write_EE_Byte(IS_EVER_MIDCALIBRATION_FLG , IS_EVER_MIDCALIBRATION_ADDR);
					
		Write_EE_Byte((Sampling_MaxMinData[RUDDER][MAXDAT] >> 8)     , RUD_MAXVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[RUDDER][MAXDAT] & 0xFF)   , RUD_MAXVALUE_ADDR + 1);
		Write_EE_Byte((Sampling_MaxMinData[RUDDER][MINDAT] >> 8)     , RUD_MINVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[RUDDER][MINDAT] & 0xFF)   , RUD_MINVALUE_ADDR + 1);
					
		Write_EE_Byte((Sampling_MaxMinData[THROTTLE][MAXDAT] >> 8)     , THR_MAXVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[THROTTLE][MAXDAT] & 0xFF)   , THR_MAXVALUE_ADDR + 1);
		Write_EE_Byte((Sampling_MaxMinData[THROTTLE][MINDAT] >> 8)     , THR_MINVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[THROTTLE][MINDAT] & 0xFF)   , THR_MINVALUE_ADDR + 1);				
		
		//��ֹ���� EEPROM �� ���Ź���ʱ��λ
		FeedTheDog();						//ι��
		
		Write_EE_Byte((Sampling_MaxMinData[ELEVATOR][MAXDAT] >> 8)     , ELE_MAXVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[ELEVATOR][MAXDAT] & 0xFF)   , ELE_MAXVALUE_ADDR + 1);
		Write_EE_Byte((Sampling_MaxMinData[ELEVATOR][MINDAT] >> 8)     , ELE_MINVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[ELEVATOR][MINDAT] & 0xFF)   , ELE_MINVALUE_ADDR + 1);
					
		Write_EE_Byte((Sampling_MaxMinData[AILERON][MAXDAT] >> 8)     , AIL_MAXVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[AILERON][MAXDAT] & 0xFF)   , AIL_MAXVALUE_ADDR + 1);
		Write_EE_Byte((Sampling_MaxMinData[AILERON][MINDAT] >> 8)     , AIL_MINVALUE_ADDR);
		Write_EE_Byte((Sampling_MaxMinData[AILERON][MINDAT] & 0xFF)   , AIL_MINVALUE_ADDR + 1);
		
		//��ֹ���� EEPROM �� ���Ź���ʱ��λ
		FeedTheDog();						//ι��
		
		Sampling_Offset[RUDDER]   = 50 ; 
		Write_EE_Byte(50   , RUD_OFFSET_ADDR);
		Sampling_Offset[THROTTLE] = 50 ; 
		Write_EE_Byte(50    , THR_OFFSET_ADDR);
		Sampling_Offset[ELEVATOR] = 50 ; 
		Write_EE_Byte(50   , ELE_OFFSET_ADDR);
		Sampling_Offset[AILERON]  = 50 ; 
		Write_EE_Byte(50   , AIL_OFFSET_ADDR);
                
                //��ֹ���� EEPROM �� ���Ź���ʱ��λ
		//FeedTheDog();						//ι��
		//AUX1-AUX4
                
		//��ͨ����ʾ(���� LED ��ʾ)
		Init_ChannelDis(true);
		LED_State_ON    |= LED_BIND   ; 
		MenuCtrl.RunStep = __stSarttUp ;
		MenuCtrl.Sub_RunStep = 0 ; 
	}
}

static void(*pFT[])(void) = 
{
	FT_GetHSKMidValue ,
	FT_SkipDelay , 
	FT_GetHSKMaxMinValue , 
	FT_OK , 
};

/*==============================================================================
(1)�ȱ궨��ҡ�˵���λֵ(�����������������ҡ��)
���� : ÿ��ҡ�˼�¼10��ֵ��ȥ����λ����λ������8��ȡƽ����
==============================================================================*/
void FTDebug(void)
{
	pFT[MenuCtrl.Sub_RunStep]();
}
/*******************************************************************************
--------------------------------------------------------------------------------
MCU : STM8LXXX
--------------------------------------------------------------------------------
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
�ر�ע�� : 
RWW : Read while write (ֻ��High-density ����) ������ע��ÿ��ֻ�ܲ���һ��Byte
����һ�ζ�д����1Byteʱ��Ҫ�ֶν��С�������ܵ��� MCU �����޷���Ӧ(�����ж�)��ֱ��EEPROM������ɡ�
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--------------------------------------------------------------------------------

*******************************************************************************/

#include "include.h"

////////////////////////////////////////////////////////////////////////////////
//                         �������ַ��д�뵥�ֽ�����                         //
//	             ��ַ: unsigned short  ���ݣ�unsigned char                //
////////////////////////////////////////////////////////////////////////////////
bool Write_EE_Byte(unsigned char WDat ,unsigned short WAddr)
{
  	//д����Կ:����EEд����
	FLASH -> DUKR = 0xAE ;
	FLASH -> DUKR = 0x56 ; 

	//��ֹд��ַԽλ
	if(WAddr > 0xFF) WAddr = 0xFF ; 
	
	//��Ҫд�������  �����Ӧ��ַ��
	*(unsigned char *)(WAddr + 0x1000) = WDat ; 
	
	//�ȴ� ��־λ��λ 
	unsigned char temp_flg = 0 ;
	unsigned int  Waite_Time = 0xFFFF ;
	while((temp_flg == 0) && (Waite_Time != 0))
	{
	  	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  	//�˴��ر�ע�� : ֻ�ܶ�һ��IAPSR�Ĵ�����������ܳ��ִ���
	  	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  	temp_flg = ((FLASH -> IAPSR) & ((1<<2)|(1<<0))) ;
        	--Waite_Time ; 
	}
	
	//EEPROMд����ʹ��
	FLASH -> IAPSR &= ~(1<<3);
	
	//�ض���̵�ַ���� : �����д������һ�£�˵��д�����ɹ�   �����һ�£�д����ʧ��
	unsigned char temp = *(unsigned char *)(WAddr + 0x1000) ; 
	
	if(temp == WDat)
	{
		return true ; 
	}
	else
	{
	 	return false ;
	}
}

////////////////////////////////////////////////////////////////////////////////
//                             ��ȡ�����ַ���ֽ�����                         //
////////////////////////////////////////////////////////////////////////////////
unsigned char Read_EE_Byte(unsigned short RAddr)
{
	if(RAddr > 0xFF) RAddr = 0xFF ;
	  
	unsigned char RDat = *(unsigned char *)(RAddr + 0x1000) ; 
	return RDat ; 
}

////////////////////////////////////////////////////////////////////////////////
//                             ��ȡ�����ַ˫�ֽ�����                         //
////////////////////////////////////////////////////////////////////////////////
uint16_t Read_EE_Word(unsigned short RAddr)
{
	if(RAddr > 0xFF) RAddr = 0xFF ;  
	  
	uint16_t RDat = *(uint16_t *)(RAddr + 0x1000) ; 
	return RDat ; 
}

////////////////////////////////////////////////////////////////////////////////
//                            ��ʼ����ȡEEPROM����                            //
////////////////////////////////////////////////////////////////////////////////
void Init_EEPROM_Dat(void)
{
  	uint16_t Temp = 0 ; 
	
	//======================================================================
	//�鿴�豸�Ƿ��һ���ϵ�(��ʼ������EEPROM���� ��ֱ�ӽ�����λУ׼)
	//======================================================================
	Temp = Read_EE_Word(IS_EVER_INITEEPROM_ADDR) ; 
	if(Temp != IS_EVER_INITEEPROM_FLG)
	{
		//==============================================================
	  	//���µ�һ�ϵ��־λ(0x1234)
		//==============================================================
		Write_EE_Byte(IS_EVER_INITEEPROM_FLG >> 8     , IS_EVER_INITEEPROM_ADDR);
		Write_EE_Byte(IS_EVER_INITEEPROM_FLG & 0xFF   , IS_EVER_INITEEPROM_ADDR + 1);
		
		//==============================================================
		//20180801��5-8ͨ����Ĭ�ϳ�ʼ��Ϊ��͵�λ
		//==============================================================
		Sampling_Data[AUX1] = ADC_AUX_LOW ;  
		Write_EE_Byte(Sampling_Data[AUX1] >> 8    , AUX1VALUE_ADDR);
		Write_EE_Byte(Sampling_Data[AUX1] & 0xFF  , AUX1VALUE_ADDR + 1);
		
		Sampling_Data[AUX2] = ADC_AUX_LOW ;  
		Write_EE_Byte(Sampling_Data[AUX2] >> 8    , AUX2VALUE_ADDR);
		Write_EE_Byte(Sampling_Data[AUX2] & 0xFF  , AUX2VALUE_ADDR + 1);
                
		Sampling_Data[AUX3] = ADC_AUX_LOW ;  
		Write_EE_Byte(Sampling_Data[AUX3] >> 8    , AUX3VALUE_ADDR);
		Write_EE_Byte(Sampling_Data[AUX3] & 0xFF  , AUX3VALUE_ADDR + 1);
                
		Sampling_Data[AUX4] = ADC_AUX_LOW ;  
		Write_EE_Byte(Sampling_Data[AUX4] >> 8    , AUX4VALUE_ADDR);
		Write_EE_Byte(Sampling_Data[AUX4] & 0xFF  , AUX4VALUE_ADDR + 1);
		
		//==============================================================
		// ��ʼ��ƫ��(Ĭ�ϳ�ʼ��Ϊ 50(��ƫ��  0/100 ��С ���ƫ��))
		//==============================================================
		Sampling_Offset[RUDDER]   = 50 ; 
		Write_EE_Byte(50   , RUD_OFFSET_ADDR);
		
		Sampling_Offset[THROTTLE] = 50 ; 
		Write_EE_Byte(50   , THR_OFFSET_ADDR);
		
		Sampling_Offset[ELEVATOR] = 50 ; 
		Write_EE_Byte(50   , ELE_OFFSET_ADDR);
		
		Sampling_Offset[AILERON]  = 50 ; 
		Write_EE_Byte(50   , AIL_OFFSET_ADDR);
		
		//==============================================================
		// ��ʼ��TIM2�������� : 0 ��
		//==============================================================
		TIM2_ErrorCnt = 0 ; 
		Write_EE_Byte(TIM2_ErrorCnt , TIM2ErrorCnt_ADDR);
		
		//==============================================================
		//��ǵ�ǰ��λУ׼��Ч , ��Ҫ���½�����λУ׼
		//==============================================================
		FTDebug_err_flg = true ; 
	}
	
	//======================================================================
	else
	{
  		//======================================================================
		//20180801����λ�洢 AUX1��3(1200 / 1800)   AUX2��4(1200 / 1500 / 1800)
  		//======================================================================
  		Temp = Read_EE_Word(AUX1VALUE_ADDR) ; 
		if(Temp > ADC_AUX_HIGH) Temp = ADC_AUX_HIGH ; 
		if(Temp >= ADC_AUX_HIGH)     			{Sampling_Data[AUX1] = ADC_AUX_HIGH ; }
		else 						{Sampling_Data[AUX1] = ADC_AUX_LOW  ; }

  		Temp = Read_EE_Word(AUX3VALUE_ADDR) ; 
		if(Temp > ADC_AUX_HIGH) Temp = ADC_AUX_HIGH ; 
		if(Temp >= ADC_AUX_HIGH)     			{Sampling_Data[AUX3] = ADC_AUX_HIGH ; }
		else 						{Sampling_Data[AUX3] = ADC_AUX_LOW  ; }               
                
		Temp = Read_EE_Word(AUX2VALUE_ADDR) ; 
		if(Temp > ADC_AUX_HIGH) Temp = ADC_AUX_HIGH ; 
		if(Temp >= ADC_AUX_HIGH)     			{Sampling_Data[AUX2] = ADC_AUX_HIGH ; }
		else if(Temp >= ADC_AUX_MID) 			{Sampling_Data[AUX2] = ADC_AUX_MID  ; }
		else 						{Sampling_Data[AUX2] = ADC_AUX_LOW  ; }

		Temp = Read_EE_Word(AUX4VALUE_ADDR) ; 
		if(Temp > ADC_AUX_HIGH) Temp = ADC_AUX_HIGH ; 
		if(Temp >= ADC_AUX_HIGH)     			{Sampling_Data[AUX4] = ADC_AUX_HIGH ; }
		else if(Temp >= ADC_AUX_MID) 			{Sampling_Data[AUX4] = ADC_AUX_MID  ; }
		else 						{Sampling_Data[AUX4] = ADC_AUX_LOW  ; }
		
		//==============================================================
		//			΢��ƫ��ֵ
		//==============================================================
		Temp = Read_EE_Byte(RUD_OFFSET_ADDR) ;
		if(Temp > 100) Temp = 50 ; 
		Sampling_Offset[RUDDER] = Temp ; 
		
		Temp = Read_EE_Byte(THR_OFFSET_ADDR) ;
		if(Temp > 100) Temp = 50 ; 
		Sampling_Offset[THROTTLE] = Temp ; 
		
		Temp = Read_EE_Byte(ELE_OFFSET_ADDR) ;
		if(Temp > 100) Temp = 50 ; 
		Sampling_Offset[ELEVATOR] = Temp ; 
		
		Temp = Read_EE_Byte(AIL_OFFSET_ADDR) ;
		if(Temp > 100) Temp = 50 ; 
		Sampling_Offset[AILERON] = Temp ; 
	  
		//==============================================================
		//		  TIM2 ��������
		//==============================================================
		TIM2_ErrorCnt = Read_EE_Byte(TIM2ErrorCnt_ADDR) ;

		//==============================================================
		//�Ƿ���й���У׼:
		//(1)�� : ��ȡ��ҡ�˵������С����ֵ��ƫ��
		//(2)�� : ǿ�ƽ�����λУ׼
		//==============================================================
		//����У׼��־λ
		Temp = Read_EE_Byte(IS_EVER_MIDCALIBRATION_ADDR) ; 
		if(Temp == IS_EVER_MIDCALIBRATION_FLG) 
		{
		  	//======================================================
		  	//     ���У׼����λֵ�����㡣�������ж���λֵ��Ч�ԡ�
		  	//======================================================
	  		FTDebug_err_flg = false ; 
		
			//======================================================
			//           �жϴ洢�ĸ���λУ׼�����Ƿ���Ч
			//======================================================
  			Temp = Read_EE_Word(RUD_MAXVALUE_ADDR) ; 		// RUD ���ֵ
			if(Temp < MAXValue_Min)					
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[RUDDER][MAXDAT] = Temp ;
			}
	
			
  			Temp = Read_EE_Word(RUD_MIDVALUE_ADDR) ; 
			if((Temp < AD_MidValue_Min) || (Temp > AD_MidValue_Max))//RUD ��ֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[RUDDER][MIDDAT] = Temp ;
			}
			
  			Temp = Read_EE_Word(RUD_MINVALUE_ADDR) ; 
			if(Temp > MINValue_Max)					//RUD��Сֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[RUDDER][MINDAT] = Temp ;
			}
			
			
	
  			Temp = Read_EE_Word(THR_MAXVALUE_ADDR) ; 
			if(Temp < MAXValue_Min)					//THR���ֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[THROTTLE][MAXDAT] = Temp ;
			}
	
			//THR û����λУ׼
			
  			Temp = Read_EE_Word(THR_MINVALUE_ADDR) ; 
			if(Temp > MINValue_Max)					//THR��Сֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[THROTTLE][MINDAT] = Temp ;
			}
	
			
			
  			Temp = Read_EE_Word(ELE_MAXVALUE_ADDR) ; 
			if(Temp < MAXValue_Min)					//ELE���ֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[ELEVATOR][MAXDAT] = Temp ;
			}
	
			
  			Temp = Read_EE_Word(ELE_MIDVALUE_ADDR) ; 
			if((Temp < AD_MidValue_Min) || (Temp > AD_MidValue_Max))//ELE��ֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[ELEVATOR][MIDDAT] = Temp ;
			}
			
  			Temp = Read_EE_Word(ELE_MINVALUE_ADDR) ; 
			if(Temp > MINValue_Max)					//ELE��Сֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[ELEVATOR][MINDAT] = Temp ;
			}
	
  			Temp = Read_EE_Word(AIL_MAXVALUE_ADDR) ; 
			if(Temp < MAXValue_Min)					//AIL���ֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[AILERON][MAXDAT] = Temp ;
			}
	
			
			
  			Temp = Read_EE_Word(AIL_MIDVALUE_ADDR) ; 
			if((Temp < AD_MidValue_Min) || (Temp > AD_MidValue_Max))//AIL��ֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[AILERON][MIDDAT] = Temp ;
			}
			
  			Temp = Read_EE_Word(AIL_MINVALUE_ADDR) ; 
			if(Temp > MINValue_Max)					//AIL��Сֵ
			{
		  		FTDebug_err_flg = true ;
			}
			else
			{
				Sampling_MaxMinData[AILERON][MINDAT] = Temp ;
			}
		}
		else 
		{
			FTDebug_err_flg = true ; 
		}
	}
}


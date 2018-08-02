#include "include.h"

#define OVERTIME_MAX 10 	//ң������ֹ���� 10Min ����

//ҡ��ӳ������
const uint16_t OutputCode[420] = 
{
/*   	0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 
	0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 
	0   , 0   , 0   , 0   , 0   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 1   , 
	1   , 1   , 1   , 1   , 1   , 2   , 2   , 2   , 2   , 2   , 2   , 2   , 2   , 2   , 2   , 2   , 3   , 3   , 3   , 3   , 
	3   , 3   , 3   , 3   , 3   , 3   , 4   , 4   , 4   , 4   , 4   , 4   , 4   , 5   , 5   , 5   , 5   , 5   , 5   , 6   , 
	6   , 6   , 6   , 6   , 6   , 7   , 7   , 7   , 7   , 7   , 8   , 8   , 8   , 8   , 8   , 9   , 9   , 9   , 9   , 10  , 
	10  , 10  , 10  , 11  , 11  , 11  , 11  , 12  , 12  , 12  , 13  , 13  , 13  , 13  , 14  , 14  , 14  , 15  , 15  , 15  , 
	16  , 16  , 16  , 17  , 17  , 17  , 18  , 18  , 18  , 19  , 19  , 20  , 20  , 20  , 21  , 21  , 22  , 22  , 22  , 23  , 
	23  , 24  , 24  , 25  , 25  , 26  , 26  , 27  , 27  , 27  , 28  , 28  , 29  , 29  , 30  , 31  , 31  , 32  , 32  , 33  , 
	33  , 34  , 34  , 35  , 35  , 36  , 37  , 37  , 38  , 38  , 39  , 40  , 40  , 41  , 42  , 42  , 43  , 44  , 44  , 45  , 
	46  , 46  , 47  , 48  , 48  , 49  , 50  , 51  , 51  , 52  , 53  , 54  , 54  , 55  , 56  , 57  , 57  , 58  , 59  , 60  , 
	61  , 61  , 62  , 63  , 64  , 65  , 66  , 67  , 68  , 68  , 69  , 70  , 71  , 72  , 73  , 74  , 75  , 76  , 77  , 78  , 
	79  , 80  , 81  , 82  , 83  , 84  , 85  , 86  , 87  , 88  , 89  , 90  , 91  , 92  , 93  , 94  , 96  , 97  , 98  , 99  , 
	100 , 101 , 102 , 104 , 105 , 106 , 107 , 108 , 110 , 111 , 112 , 113 , 115 , 116 , 117 , 118 , 120 , 121 , 122 , 124 , 
	125 , 126 , 128 , 129 , 130 , 132 , 133 , 135 , 136 , 137 , 139 , 140 , 142 , 143 , 145 , 146 , 148 , 149 , 151 , 152 , 
	154 , 155 , 157 , 158 , 160 , 162 , 163 , 165 , 166 , 168 , 170 , 171 , 173 , 175 , 176 , 178 , 180 , 181 , 183 , 185 , 
	187 , 188 , 190 , 192 , 194 , 196 , 197 , 199 , 201 , 203 , 205 , 207 , 208 , 210 , 212 , 214 , 216 , 218 , 220 , 222 , 
	224 , 226 , 228 , 230 , 232 , 234 , 236 , 238 , 240 , 242 , 244 , 246 , 248 , 251 , 253 , 255 , 257 , 259 , 261 , 264 , 
	266 , 268 , 270 , 272 , 275 , 277 , 279 , 282 , 284 , 286 , 289 , 291 , 293 , 296 , 298 , 300 , 303 , 305 , 308 , 310 , 
	313 , 315 , 318 , 320 , 323 , 325 , 328 , 330 , 333 , 335 , 338 , 340 , 343 , 346 , 348 , 351 , 354 , 356 , 359 , 362 , 
	365 , 367 , 370 , 373 , 376 , 378 , 381 , 384 , 387 , 390 , 393 , 395 , 400 , 401 , 404 , 407 , 410 , 413 , 416 , 419 , */
  
  
  
          //////////////////////////////////////////////////////////////////////////////////////////
          ///////// ������11��18�����Ż������ߣ���С������
          //////////////////////////////////////////////////////////////////////////////////////////
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   3,   3,
	  3,   3,   4,   4,   4,   4,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,   9,
	  9,  10,  10,  10,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,  16,  16,  17,  17,  18,  18,
	 19,  19,  20,  20,  21,  21,  22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  27,  27,  28,  28,
	 29,  29,  30,  30,  31,  31,  32,  32,  33,  33,  34,  34,  35,  35,  36,  36,  37,  37,  38,  39,
	 39,  40,  41,  41,  42,  43,  43,  44,  45,  45,  46,  47,  47,  48,  49,  49,  50,  51,  52,  53,
	 54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,
	 74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,
	 94,  96,  97,  99, 100, 102, 103, 105, 106, 108, 109, 111, 112, 114, 115, 117, 118, 120, 121, 123,
	124, 126, 127, 128, 130, 131, 133, 134, 135, 137, 138, 140, 141, 143, 144, 146, 147, 149, 150, 152,
	153, 155, 156, 158, 159, 161, 162, 164, 165, 165, 167, 168, 170, 171, 173, 174, 176, 177, 179, 180,
	182, 183, 185, 186, 188, 189, 191, 192, 194, 195, 197, 198, 200, 201, 203, 204, 206, 207, 209, 210,
	212, 213, 215, 216, 218, 219, 221, 222, 224, 225, 227, 228, 230, 231, 233, 234, 236, 237, 239, 241,
	242, 244, 245, 247, 248, 250, 251, 253, 254, 256, 257, 259, 260, 262, 263, 265, 266, 268, 269, 271,
	272, 274, 275, 277, 278, 280, 281, 283, 284, 286, 287, 289, 290, 292, 293, 295, 296, 298, 299, 301,
	302, 304, 305, 307, 308, 310, 311, 313, 314, 316, 318, 319, 321, 322, 324, 325, 327, 328, 330, 331,
	333, 334, 336, 337, 339, 340, 342, 343, 345, 346, 348, 349, 351, 352, 354, 355, 357, 358, 360, 361, 
	363, 364, 366, 367, 369, 370, 372, 373, 375, 376, 378, 379, 381, 382, 384, 385, 387, 388, 390, 392, 
	393, 395, 396, 398, 399, 401, 402, 404, 405, 407, 408, 410, 411, 413, 414, 416, 417, 419, 420, 420, 

};

uint8_t  ChannelInversion_flg = 0x00 ; 	//ͨ�������־λ(��������������㣬����ʱ����)
//ҡ����ر���
//��� 12 - CH                    RUD        /  THR   / ELE       /     ALL    /   Gear    /   Aux1    /   Aux2    /   Aux3    /   Aux4    /   Aux5    /   Aux6    /   Aux7  
uint16_t Sampling_Data[12]  = {  Input_Mid  ,   0 ,  Input_Mid   , Input_Mid  , Input_Mid , Input_Mid , Input_Mid , Input_Mid , Input_Mid , Input_Mid , Input_Mid , Input_Mid};	
//��ҡ����ر���(�����С����λֵ)
uint16_t Sampling_MaxMinData[4][3] = 
{
	{Input_Max , Input_Mid , Input_Min},
	{Input_Max , Input_Mid , Input_Min},
	{Input_Max , Input_Mid , Input_Min},
	{Input_Max , Input_Mid , Input_Min},
};
uint8_t  Sampling_Offset[4] = {50   , 50   , 50   , 50};			//��ҡ��ƫ��ֵ(0-100)
 
//==============================================================================
//ͨ������ֵ�����㷢��ֵ
//==============================================================================
uint16_t Get_SendValue(ChannelTypeDef Channel)
{
  	uint16_t ADTemp = 0 ; 
	uint16_t OutputTemp = 0 ; 
	
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!ֻ������ҡ��������Ҫ����λֵ����(������������)!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!ǧ��ע�⣬��λ�����Խ��!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if((Channel == RUDDER) || (Channel == ELEVATOR) || (Channel == AILERON))
	{	
	  	//�жϱ궨��ֵֵ��Χ����ֹ��������������
	  	if(Sampling_MaxMinData[Channel][MAXDAT] < MAXValue_Min)         Sampling_MaxMinData[Channel][MAXDAT] = MAXValue_Min ; 
		if(Sampling_MaxMinData[Channel][MINDAT] > MINValue_Max)         Sampling_MaxMinData[Channel][MINDAT] = MINValue_Max ; 
	  	if(Sampling_MaxMinData[Channel][MIDDAT] > AD_MidValue_Max)      Sampling_MaxMinData[Channel][MIDDAT] = AD_MidValue_Max ; 
		else if(Sampling_MaxMinData[Channel][MIDDAT] < AD_MidValue_Min) Sampling_MaxMinData[Channel][MIDDAT] = AD_MidValue_Min ; 
		
		//�޶�����AD��Ч��Χ(�궨��Сֵ - �궨���ֵ)
		if(Sampling_Data[Channel] > Sampling_MaxMinData[Channel][MAXDAT])     ADTemp = Sampling_MaxMinData[Channel][MAXDAT] ; 
		else if(Sampling_Data[Channel] < Sampling_MaxMinData[Channel][MINDAT])ADTemp = Sampling_MaxMinData[Channel][MINDAT] ; 
		else								      ADTemp = Sampling_Data[Channel] ; 
		
		//������ҡ������������޷�����(���·�ֵ���� 100)
	  	if(ADTemp >= Sampling_MaxMinData[Channel][MIDDAT]) { OutputTemp = Output_Mid + (uint16_t)((ADTemp - Sampling_MaxMinData[Channel][MIDDAT]) * (((float)(Output_Max - Output_Mid - 100))/(Sampling_MaxMinData[Channel][MAXDAT] - Sampling_MaxMinData[Channel][MIDDAT])) + 0.5f) ; }
		else { OutputTemp = Output_Mid - (uint16_t)((Sampling_MaxMinData[Channel][MIDDAT] - ADTemp) * (((float)(Output_Mid - Output_Min - 100))/(Sampling_MaxMinData[Channel][MIDDAT] - Sampling_MaxMinData[Channel][MINDAT])) + 0.5f)  ; }
		
		//�����ǰ��������ݷ�Χ��ֹԽ��(���Χ���ܳ���412)
		if(OutputTemp > (Output_Max - 100)) OutputTemp = (Output_Max - 100) ; 
		if(OutputTemp < (Output_Min + 100)) OutputTemp = (Output_Min + 100) ;
		if(OutputTemp > Output_Mid) OutputTemp = OutputCode[OutputTemp - Output_Mid] + Output_Mid;
		else		            OutputTemp = Output_Mid - OutputCode[Output_Mid - OutputTemp];
		
		//����ƫ�����
		if(Sampling_Offset[Channel] > 100)   Sampling_Offset[Channel] = 100 ;
		OutputTemp += Sampling_Offset[Channel] * 2 ; 
		//��ֹ���ݼ���С�� 100 
		if(OutputTemp > 200) OutputTemp -= 100 ;
		else OutputTemp = 100 ; 
		
		//�ٴμ�鷢�����ݷ�Χ
		if(OutputTemp > (Output_Max - 100)) OutputTemp = (Output_Max - 100); 
		if(OutputTemp < (Output_Min + 100)) OutputTemp = (Output_Min + 100) ;
		
	}
	
	//����û����λֵ��ͨ������������ 
	else
	{
		
		if(Channel == THROTTLE)
		{
		  	//�жϱ궨��ֵֵ��Χ����ֹ��������������
	  		if(Sampling_MaxMinData[Channel][MAXDAT] < MAXValue_Min)         Sampling_MaxMinData[Channel][MAXDAT] = MAXValue_Min ; 
			if(Sampling_MaxMinData[Channel][MINDAT] > MINValue_Max)         Sampling_MaxMinData[Channel][MINDAT] = MINValue_Max ;
			//�޶�����AD��Ч��Χ(�궨��Сֵ - �궨���ֵ)
			if(Sampling_Data[Channel] > Sampling_MaxMinData[Channel][MAXDAT])       ADTemp = Sampling_MaxMinData[Channel][MAXDAT] ; 
			else if(Sampling_Data[Channel] < Sampling_MaxMinData[Channel][MINDAT])  ADTemp = Sampling_MaxMinData[Channel][MINDAT] ;
			else								        ADTemp = Sampling_Data[Channel] ; 
		  	OutputTemp = (uint16_t)((ADTemp- Sampling_MaxMinData[Channel][MINDAT]) * ((float)(THR_Output_Max - THR_Output_Min)/(Sampling_MaxMinData[Channel][MAXDAT] - Sampling_MaxMinData[Channel][MINDAT]))+ 0.5f) + THR_Output_Min ;
			//����ƫ��ֵ
			if(Sampling_Offset[Channel] > 100)   Sampling_Offset[Channel] = 100 ;
			OutputTemp += Sampling_Offset[Channel] * 2 ; 
			if(OutputTemp > 100) OutputTemp -= 100 ;
			else OutputTemp = 0 ; 
			
			//�����޷�
			if(OutputTemp > THR_Output_Max) OutputTemp = THR_Output_Max ; 
			if(OutputTemp < THR_Output_Min) OutputTemp = THR_Output_Min ;
		}
		else
		{
			OutputTemp = (uint16_t)(Sampling_Data[Channel] * ((float)(Output_Max - Output_Min)/(Input_Max - Input_Min))+ 0.5f) + Output_Min ;
		}
	}
	
	//�Ƿ���Ҫ����
        //20180801������AUX3��4
	if((Channel < 8) && (ChannelInversion_flg & (1<<Channel)))
	{
		 OutputTemp = 2*Output_Mid - OutputTemp;
	}
	//======================================================================
	//	         ��ֹ���ݳ������ֵ
	//======================================================================
	if(OutputTemp > Output_Max) OutputTemp = Output_Max ; 
	if(OutputTemp < Output_Min) OutputTemp = Output_Min ; 
	
	return OutputTemp ; 
}


//ONOFF_flg : �򿪹ر�ͨ����ʾ
//true : ��ǰ��ʾң����ͨ��     false : ����LED��ʾ���������ڱ�����ʾ
void Init_ChannelDis(bool ONOFF_flg)
{
        LED_State_ON &= LED_NONE ; 
        LED_State_Shake &= LED_NONE ;
  	//��ʾ��ǰͨ����λ
	if(ONOFF_flg == true)
	{
		//6��
                if(Sampling_Data[AUX2] >= ADC_AUX_HIGH)
                  {
                    //56ȫ��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON |= LED_CH5|LED_CH6_M|LED_CH6_H ;}
                    //5��6ȫ��
                    else {LED_State_ON &= ~(LED_CH5) ; LED_State_ON |= LED_CH6_M|LED_CH6_H ;}
                  }
                //6��
		else if(Sampling_Data[AUX2] >= ADC_AUX_MID)
                  {
                    //5����6��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH6_H) ; LED_State_ON |= LED_CH5|LED_CH6_M ;}
                    //5��6��
                    else {LED_State_ON &= ~(LED_CH5|LED_CH6_H) ; LED_State_ON |= LED_CH6_M ;}
                  }
                //6��
                else
                  {
                    //5����6��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH6_H|LED_CH6_M) ; LED_State_ON |= LED_CH5 ;}
                    //5��6��
                    else {LED_State_ON &= ~(LED_CH5|LED_CH6_H|LED_CH6_M) ;}
                  }
                
                
		//8�ߣ�AUX3��4
                if(Sampling_Data[AUX4] >= ADC_AUX_HIGH)
                  {
                    //78ȫ��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON |= LED_CH7|LED_CH8_M|LED_CH8_H ;}
                    //7��8ȫ��
                    else {LED_State_ON &= ~(LED_CH7) ; LED_State_ON |= LED_CH8_M|LED_CH8_H ;}
                  }
                //8��
		else if(Sampling_Data[AUX4] >= ADC_AUX_MID)
                  {
                    //7����8��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH8_H) ; LED_State_ON |= LED_CH7|LED_CH8_M ;}
                    //7��8��
                    else {LED_State_ON &= ~(LED_CH7|LED_CH8_H) ; LED_State_ON |= LED_CH8_M ;}
                  }
                //8��
                else
                  {
                    //7����8��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH8_H|LED_CH8_M) ; LED_State_ON |= LED_CH7 ;}
                    //7��8��
                    else {LED_State_ON &= ~(LED_CH7|LED_CH8_H|LED_CH8_M) ;}
                  }
	}
}

//==============================================================================
//����΢������
//==============================================================================
void SetOffSet(void)
{
	////////////////////////////////////////////////////////////////////////
	////////			ƫ��΢��			////////
	////////////////////////////////////////////////////////////////////////
  	if(OffSetKeyValue == __stKey_R_Plus)					//RUDDER ƫ�� ��
	{
		if(Sampling_Offset[RUDDER] < 100) ++Sampling_Offset[RUDDER] ; 
		else Sampling_Offset[RUDDER] = 100 ; 
		
		if(Sampling_Offset[RUDDER] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[RUDDER] == 0)||(Sampling_Offset[RUDDER] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[RUDDER] > 50) beepCmd(1500 - ((Sampling_Offset[RUDDER] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[RUDDER])*10), __stKeyClick);  
			}
		} 
		Write_EE_Byte(Sampling_Offset[RUDDER]   , RUD_OFFSET_ADDR);
	}
	else if(OffSetKeyValue == __stKey_R_Sub)				//RUDDER ƫ�� ��
	{
		if(Sampling_Offset[RUDDER]) --Sampling_Offset[RUDDER] ; 
		
		if(Sampling_Offset[RUDDER] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[RUDDER] == 0)||(Sampling_Offset[RUDDER] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[RUDDER] > 50) beepCmd(1500 - ((Sampling_Offset[RUDDER] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[RUDDER])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[RUDDER]   , RUD_OFFSET_ADDR);
	}
  
  	else if(OffSetKeyValue == __stKey_T_Plus)				//THROTTLE ƫ�� ��
	{
		if(Sampling_Offset[THROTTLE] < 100) ++Sampling_Offset[THROTTLE] ; 
		else Sampling_Offset[THROTTLE] = 100 ; 
		
		if(Sampling_Offset[THROTTLE] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[THROTTLE] == 0)||(Sampling_Offset[THROTTLE] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[THROTTLE] > 50) beepCmd(1500 - ((Sampling_Offset[THROTTLE] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[THROTTLE])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[THROTTLE]   , THR_OFFSET_ADDR);
	}
	else if(OffSetKeyValue == __stKey_T_Sub)				//THROTTLE ƫ�� ��
	{
		if(Sampling_Offset[THROTTLE]) --Sampling_Offset[THROTTLE] ; 
		
		if(Sampling_Offset[THROTTLE] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[THROTTLE] == 0)||(Sampling_Offset[THROTTLE] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[THROTTLE] > 50) beepCmd(1500 - ((Sampling_Offset[THROTTLE] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[THROTTLE])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[THROTTLE]   , THR_OFFSET_ADDR);
	}
	
  	else if(OffSetKeyValue == __stKey_E_Plus)				//ELEVATOR ƫ�� ��
	{
		if(Sampling_Offset[ELEVATOR] < 100) ++Sampling_Offset[ELEVATOR] ; 
		else Sampling_Offset[ELEVATOR] = 100 ; 
		
		if(Sampling_Offset[ELEVATOR] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[ELEVATOR] == 0)||(Sampling_Offset[ELEVATOR] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[ELEVATOR] > 50) beepCmd(1500 - ((Sampling_Offset[ELEVATOR] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[ELEVATOR])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[ELEVATOR]   , ELE_OFFSET_ADDR);
	}
	else if(OffSetKeyValue == __stKey_E_Sub)				//ELEVATOR ƫ�� ��
	{
		if(Sampling_Offset[ELEVATOR]) --Sampling_Offset[ELEVATOR] ; 
		
		if(Sampling_Offset[ELEVATOR] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[ELEVATOR] == 0)||(Sampling_Offset[ELEVATOR] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[ELEVATOR] > 50) beepCmd(1500 - ((Sampling_Offset[ELEVATOR] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[ELEVATOR])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[ELEVATOR]   , ELE_OFFSET_ADDR);
	}
	
  	else if(OffSetKeyValue == __stKey_A_Plus)				//AILERON ƫ�� ��
	{
		if(Sampling_Offset[AILERON] < 100) ++Sampling_Offset[AILERON] ; 
		else Sampling_Offset[AILERON] = 100 ; 
		
		if(Sampling_Offset[AILERON] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[AILERON] == 0)||(Sampling_Offset[AILERON] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[AILERON] > 50) beepCmd(1500 - ((Sampling_Offset[AILERON] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[AILERON])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[AILERON]   , AIL_OFFSET_ADDR);
	}
	else if(OffSetKeyValue == __stKey_A_Sub)				//AILERON ƫ�� ��
	{
		if(Sampling_Offset[AILERON]) --Sampling_Offset[AILERON] ; 
		
		if(Sampling_Offset[AILERON] == 50) 						{ if(RunStatus == __stNormal) beepCmd(1600 , __stMidOffSet);  }
		else if((Sampling_Offset[AILERON] == 0)||(Sampling_Offset[AILERON] == 100))	{ if(RunStatus == __stNormal) beepCmd(1000 , __stMidADAdjustDown); }
		else 				  						
		{ 
		  	if(RunStatus == __stNormal) 
			{
				if(Sampling_Offset[AILERON] > 50) beepCmd(1500 - ((Sampling_Offset[AILERON] - 50)*10), __stKeyClick);  
				else beepCmd(1500 - ((50 - Sampling_Offset[AILERON])*10), __stKeyClick);  
			}
		}
		Write_EE_Byte(Sampling_Offset[AILERON]   , AIL_OFFSET_ADDR);
	}
}

//��ֹ��ʱ�ж�
void StaticOverTime(void)
{
	//�����ϴ�ҡ��AD����ֵ���͵�ǰAD�ȶԣ�����仯����40/60������(���㾲ֹ��ʱ)�����򲻱�
  	static uint16_t Sampling_HSK_AD_LastValue[5] ; 
	//20180801��AUX3��4 ״̬ͨ��EE�洢
        static uint8_t  DIP78_LastState = 0 ; 
	//��ֹ��ʱ����
	static uint16_t StaticOverTime_Secondcnt = 0 ; 
	static uint8_t  StaticOverTime_Mincnt	 = 0 ;
	
	uint16_t Temp = 0 ; 
	//�Ƚ�ҡ��5��ADֵ
	for(uint8_t i = 0 ; i<5 ; i++)
	{	
	  	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  	//!!!!!!!!!!!!! ֻ��Ƚ��ĸ�ҡ�˺�һ����λ��ADֵ!!!!!!!!!!!!!!!!
	  	//!!!!!!!!!!!!!!!!!!!!!!!ע������Խ��!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //20180801������AUX3��4��ADֵ����
	  	if(i < 4)
		{
			if(Sampling_HSK_AD_LastValue[i] > Sampling_Data[i]) Temp = Sampling_HSK_AD_LastValue[i] - Sampling_Data[i] ; 
			else Temp = Sampling_Data[i] - Sampling_HSK_AD_LastValue[i] ; 
		}
		//else
		//{
			//if(Sampling_HSK_AD_LastValue[4] > Sampling_Data[AUX3]) Temp = Sampling_HSK_AD_LastValue[4] - Sampling_Data[AUX3] ; 
			//else Temp = Sampling_Data[AUX3] - Sampling_HSK_AD_LastValue[4] ; 	
		//}
		
		//==============================================================
		//(1)��û�б���ǰ��AD�仯С��40 ��Ϊ�Ǿ�ֹ��
		//(2)��ֹ��ʱ������AD�仯С�� 60 ����Ϊ�Ǿ�ֹ(���ǵ�����������ʱ���𶯣�����AD�仯�Ӵ�)
		//==============================================================
		if(((RunStatus != __stStaTimeOver) && (Temp > 40))||((RunStatus == __stStaTimeOver)&&(Temp > 60)))
		{
			StaticOverTime_Secondcnt = 0 ; StaticOverTime_Mincnt = 0 ;
			if(i < 4) Sampling_HSK_AD_LastValue[i] = Sampling_Data[i] ; 	 //����ADֵ
			//else 	  Sampling_HSK_AD_LastValue[4] = Sampling_Data[AUX3] ;   //����ADֵ
		}
	}
	
	//�ж��Ƿ��а��� ����
	if((ChannelKeyValue != __stEmpty_Key) || (OffSetKeyValue != __stOffset_EmptyKey))
	{
		StaticOverTime_Secondcnt = 0 ; StaticOverTime_Mincnt = 0 ;
	}
	
	//�ж��Ƿ�ı��˲���78λ��
	if(DIP78_LastState != (GPIOG -> IDR & ((1<<2)|(1<<3))))
	{
	  	StaticOverTime_Secondcnt = 0 ; StaticOverTime_Mincnt = 0 ;
		DIP78_LastState = (GPIOG -> IDR & ((1<<2)|(1<<3))) ; 
	}
	
	//ң������ֹ���� OVERTIME_MAX ң��������
	if(StaticOverTime_Mincnt >= OVERTIME_MAX)
	{
	  	//��λǰ��Ҫ�ж� ��ǰ����״̬���ȼ� �Ƿ���� ��ֹ��ʱ����
		if(RunStatus < __stStaTimeOver) 
		{
			RunStatus = __stStaTimeOver ;
			beepCmd(NormalFreCounts, __stStaticOverTimeWarning);
		} 
	}
	else
	{
	 	if(StaticOverTime_Secondcnt > 30000) {++StaticOverTime_Mincnt ; StaticOverTime_Secondcnt = 0 ;}
		else ++StaticOverTime_Secondcnt ; 
		
		if(RunStatus == __stStaTimeOver) 
		{
		  	RunStatus = __stNormal ; 
			beepCmd(NormalFreCounts, __stExitStaticOverTime);
		}
	}
	
}

//��ʼ���������ʱ������λ��(���ŷ���ֵ���� �����ת�㣬�����ͣ�������)
static void ST_Init(void)
{
	//����ʱ ���ŷ������� ����С�� �����ת��(��Ҫע��������/�ձ���  ����/���� ������) 
  	uint16_t THR_Temp = Get_SendValue(THROTTLE) ; 
	if((!(ChannelInversion_flg & (1<<THROTTLE))&&(Get_SendValue(THROTTLE) < (Output_Min + ESC_StartUp_Value))) 
	 ||((ChannelInversion_flg & (1<<THROTTLE))&&(Get_SendValue(THROTTLE)  > (Output_Max - ESC_StartUp_Value))))
	{
	  	HighThrottle_flg = false ; 					//����������ϵ��־λ(�������ϵ��־λ�� 1 ʱ�����߷��ͳ�ʼ����)
		MenuCtrl.Sub_RunStep = 1 ; 

		//ֻ������״̬���з�������ʾ(��ֹ������������״̬)
		if((RunStatus == __stNormal) || (RunStatus == __stTHR_err))  
		{
			if(Bind_flg == false) beepCmd(PowerOnFreCounts , __stExitStaticOverTime) ;
			else
			{
				SetBind();
				LED_State_Shake |=  LED_BIND ;
				LED_State_ON    &= ~LED_BIND ; 
				beepCmd(BindFreCounts , __stBindWarning) ;
			}
			RunStatus = __stNormal ; 
		}
		
		
	}
	else
	{
		//����ҡ�˸� ����
	  	HighThrottle_flg = true ; 
	  	if(RunStatus < __stTHR_err) //����״̬ǰ����Ҫ�ж�״̬�ȼ�����״̬�ȼ����ܸ��Ǹ�״̬�ȼ�
		{
		  	beepCmd(NormalFreCounts , __stThrottleHighWarning) ;
			RunStatus = __stTHR_err ; 
		}
	}
}

/*******************************************************************************
��ʼ����ɣ���ʼ��������
(1) ͨ������ : �����ķ�ͨ������ͨ����������
*******************************************************************************/
static void ST_StartWork(void)
{
	////////////////////////////////////////////////////////////////////////
	////////			ͨ������			////////
  	//ע�� : AUX1(1200/1800 -> ADֵ850/3253)   AUX2(1200 / 1500 / 1800 -> ADֵ 850 / 2052 / 3253)
	////////////////////////////////////////////////////////////////////////
        //20180801��AUX1��3Ϊ���ο��أ�1200 / 1800����AUX2��4Ϊ���ο��أ�1200/ 1500 / 1800��
	if(ChannelKeyValue == __stKey_CH5)	//CH5
	{
	 	if(RunStatus == __stNormal) beepCmd(NormalFreCounts , __stKeyClick);
                //AUX1��ת��
		if(Sampling_Data[AUX1] == ADC_AUX_HIGH ) {Sampling_Data[AUX1] = ADC_AUX_LOW; }
                //AUX1��ת��
                else {Sampling_Data[AUX1] = ADC_AUX_HIGH; }
                //ˢ��led��ʾ
		//6�ߣ�AUX1��2
                if(Sampling_Data[AUX2] >= ADC_AUX_HIGH )
                  {
                    //56ȫ��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON |= LED_CH5|LED_CH6_M|LED_CH6_H ;}
                    //5��6ȫ��
                    else {LED_State_ON &= ~(LED_CH5) ; LED_State_ON |= LED_CH6_M|LED_CH6_H ;}
                  }
                //6��
		else if(Sampling_Data[AUX2] >= ADC_AUX_MID )
                  {
                    //5����6��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH6_H) ; LED_State_ON |= LED_CH5|LED_CH6_M ;}
                    //5��6��
                    else {LED_State_ON &= ~(LED_CH5|LED_CH6_H) ; LED_State_ON |= LED_CH6_M ;}
                  }
                //6��
                else
                  {
                    //5����6��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH6_H|LED_CH6_M) ; LED_State_ON |= LED_CH5 ;}
                    //5��6��
                    else {LED_State_ON &= ~(LED_CH5|LED_CH6_H|LED_CH6_M) ;}
                  }
		//Sampling_Data[AUX1] = ADC_AUX_HIGH ;  LED_State_ON &= ~(LED_CH5_M|LED_CH5_L) ; LED_State_ON |= LED_CH5_H ; 
		//F**K , ��Ϊ RWW ֻ֧�ֵ��ֽڲ���(���ֽڶ�д����Ӱ�쵥Ƭ���������������԰����ݲ�ֳ��������ֽ�����������)
		Write_EE_Byte((Sampling_Data[AUX1] >> 8)   , AUX1VALUE_ADDR);
		Write_EE_Byte((Sampling_Data[AUX1] & 0xFF) , AUX1VALUE_ADDR + 1);
	}
	else if(ChannelKeyValue == __stKey_CH6) 	//CH6
	{
		if(RunStatus == __stNormal) beepCmd(NormalFreCounts , __stKeyClick);
                //AUX2��ת��
		if(Sampling_Data[AUX2] >= ADC_AUX_HIGH ) { Sampling_Data[AUX2] = ADC_AUX_LOW; }
                //AUX2��ת��
                else if (Sampling_Data[AUX2] >= ADC_AUX_MID ) { Sampling_Data[AUX2] = ADC_AUX_HIGH; }
                //AUX2��ת��
                else { Sampling_Data[AUX2] = ADC_AUX_MID; }
                //ˢ��led��ʾ
		//6�ߣ�AUX1��2
                if(Sampling_Data[AUX2] >= ADC_AUX_HIGH )
                  {
                    //56ȫ��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH ) { LED_State_ON |= LED_CH5|LED_CH6_M|LED_CH6_H ;}
                    //5��6ȫ��
                    else {LED_State_ON &= ~(LED_CH5) ; LED_State_ON |= LED_CH6_M|LED_CH6_H ;}
                  }
                //6��
		else if(Sampling_Data[AUX2] >= ADC_AUX_MID)
                  {
                    //5����6��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH6_H) ; LED_State_ON |= LED_CH5|LED_CH6_M ;}
                    //5��6��
                    else {LED_State_ON &= ~(LED_CH5|LED_CH6_H) ; LED_State_ON |= LED_CH6_M ;}
                  }
                //6��
                else
                  {
                    //5����6��
                    if(Sampling_Data[AUX1] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH6_H|LED_CH6_M) ; LED_State_ON |= LED_CH5 ;}
                    //5��6��
                    else {LED_State_ON &= ~(LED_CH5|LED_CH6_H|LED_CH6_M) ;}
                  }
		//Sampling_Data[AUX1] = ADC_AUX_LOW ; LED_State_ON &= ~(LED_CH5_H|LED_CH5_M) ; LED_State_ON |= LED_CH5_L ; 
                //F**K , ��Ϊ RWW ֻ֧�ֵ��ֽڲ���(���ֽڶ�д����Ӱ�쵥Ƭ���������������԰����ݲ�ֳ��������ֽ�����������)
		Write_EE_Byte((Sampling_Data[AUX2] >> 8)   , AUX2VALUE_ADDR);
		Write_EE_Byte((Sampling_Data[AUX2] & 0xFF) , AUX2VALUE_ADDR + 1);
	}
	
	else if(ChannelKeyValue == __stKey_CH7)	//CH7
	{
		if(RunStatus == __stNormal) beepCmd(NormalFreCounts , __stKeyClick);
                //AUX3��ת��
		if(Sampling_Data[AUX3] == ADC_AUX_HIGH ) {Sampling_Data[AUX3] = ADC_AUX_LOW; }
                //AUX3��ת��
                else {Sampling_Data[AUX3] = ADC_AUX_HIGH; }
                //ˢ��led��ʾ
		//8�ߣ�AUX3��4
                if(Sampling_Data[AUX4] >= ADC_AUX_HIGH)
                  {
                    //78ȫ��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON |= LED_CH7|LED_CH8_M|LED_CH8_H ;}
                    //7��8ȫ��
                    else {LED_State_ON &= ~(LED_CH7) ; LED_State_ON |= LED_CH8_M|LED_CH8_H ;}
                  }
                //8��
		else if(Sampling_Data[AUX4] >= ADC_AUX_MID)
                  {
                    //7����8��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH8_H) ; LED_State_ON |= LED_CH7|LED_CH8_M ;}
                    //7��8��
                    else {LED_State_ON &= ~(LED_CH7|LED_CH8_H) ; LED_State_ON |= LED_CH8_M ;}
                  }
                //8��
                else
                  {
                    //7����8��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH8_H|LED_CH8_M) ; LED_State_ON |= LED_CH7 ;}
                    //7��8��
                    else {LED_State_ON &= ~(LED_CH7|LED_CH8_H|LED_CH8_M) ;}
                  }
		//if(Sampling_Data[AUX2] < ADC_AUX_MID)      		{ Sampling_Data[AUX2] = ADC_AUX_MID  ; LED_State_ON &= ~(LED_CH6_H|LED_CH6_L) ; LED_State_ON |= LED_CH6_M ; }
		//else 				    			{ Sampling_Data[AUX2] = ADC_AUX_HIGH ; LED_State_ON &= ~(LED_CH6_M|LED_CH6_L) ; LED_State_ON |= LED_CH6_H ; }
		//F**K , ��Ϊ RWW ֻ֧�ֵ��ֽڲ���(���ֽڶ�д����Ӱ�쵥Ƭ���������������԰����ݲ�ֳ��������ֽ�����������)
		Write_EE_Byte((Sampling_Data[AUX3] >> 8)   , AUX3VALUE_ADDR);
		Write_EE_Byte((Sampling_Data[AUX3] & 0xFF) , AUX3VALUE_ADDR + 1);
	}
	else if(ChannelKeyValue == __stKey_CH8) 	//CH8
	{
		if(RunStatus == __stNormal) beepCmd(NormalFreCounts , __stKeyClick);
                //AUX4��ת��
		if(Sampling_Data[AUX4] >= ADC_AUX_HIGH ) { Sampling_Data[AUX4] = ADC_AUX_LOW; }
                //AUX4��ת��
                else if (Sampling_Data[AUX4] >= ADC_AUX_MID ) { Sampling_Data[AUX4] = ADC_AUX_HIGH; }
                //AUX4��ת��
                else { Sampling_Data[AUX4] = ADC_AUX_MID; }
                //ˢ��led��ʾ
		//8�ߣ�AUX3��4
                if(Sampling_Data[AUX4] >= ADC_AUX_HIGH)
                  {
                    //78ȫ��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON |= LED_CH7|LED_CH8_M|LED_CH8_H ;}
                    //7��8ȫ��
                    else {LED_State_ON &= ~(LED_CH7) ; LED_State_ON |= LED_CH8_M|LED_CH8_H ;}
                  }
                //8��
		else if(Sampling_Data[AUX4] >= ADC_AUX_MID)
                  {
                    //7����8��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH8_H) ; LED_State_ON |= LED_CH7|LED_CH8_M ;}
                    //7��8��
                    else {LED_State_ON &= ~(LED_CH7|LED_CH8_H) ; LED_State_ON |= LED_CH8_M ;}
                  }
                //8��
                else
                  {
                    //7����8��
                    if(Sampling_Data[AUX3] >= ADC_AUX_HIGH) { LED_State_ON &= ~(LED_CH8_H|LED_CH8_M) ; LED_State_ON |= LED_CH7 ;}
                    //7��8��
                    else {LED_State_ON &= ~(LED_CH7|LED_CH8_H|LED_CH8_M) ;}
                  }
                //if(Sampling_Data[AUX2] > ADC_AUX_MID)      		{ Sampling_Data[AUX2] = ADC_AUX_MID ; LED_State_ON &= ~(LED_CH6_H|LED_CH6_L) ; LED_State_ON |= LED_CH6_M ; }
		//else				   	 		{ Sampling_Data[AUX2] = ADC_AUX_LOW ; LED_State_ON &= ~(LED_CH6_H|LED_CH6_M) ; LED_State_ON |= LED_CH6_L ; }
		//F**K , ��Ϊ RWW ֻ֧�ֵ��ֽڲ���(���ֽڶ�д����Ӱ�쵥Ƭ���������������԰����ݲ�ֳ��������ֽ�����������)
		Write_EE_Byte((Sampling_Data[AUX4] >> 8)   , AUX4VALUE_ADDR);
		Write_EE_Byte((Sampling_Data[AUX4] & 0xFF) , AUX4VALUE_ADDR + 1);
	}	
	
	//======================================================================
	// ���� AUX3 / AUX4  ��Ӧ���뿪�� �� 7 / 8 
        // 20180801��DIP78 ����Ϊ AUX12��34 �̰�������
	//======================================================================
	/*if((GPIOG -> IDR & (1<<2)) == 0)
	{
		Sampling_Data[AUX3] = ADC_AUX_HIGH ; 
	}
	else
	{
		Sampling_Data[AUX3] = ADC_AUX_LOW ; 
	}
	
	if((GPIOG -> IDR & (1<<3)) == 0)
	{
		Sampling_Data[AUX4] = ADC_AUX_HIGH ; 
	}
	else
	{
		Sampling_Data[AUX4] = ADC_AUX_LOW ; 
	}*/
	
	//======================================================================
	//ң������ֹ��ʱ�ж�:ҡ�˾�ֹ���� 15Min 
	//(1)ҡ��ADֵ�仯С�� 20  (2)�����κΰ������� ��Ϊң������ֹ
	//======================================================================
        StaticOverTime();
}

void (*pST[])(void) = 
{
	ST_Init , 
	ST_StartWork , 
};

void StartUp(void)
{
	pST[MenuCtrl.Sub_RunStep]();
	
	//======================================================================
	//�������������κ�ʱ�����΢������ : ��ֹĳЩʱ�������������λʱ�� ����ֵ��Ȼ
	//������ת����ֵ�� ������������
	//======================================================================
	SetOffSet();
}
/*******************************************************************************
�ϵ��� : 
(1)��ⷴ���뿪��λ�á�
(2)�Ƿ���Ҫ���빤��У׼ģʽ��
*******************************************************************************/
#include "include.h"

//�ϵ���ʱ 1000 mS �ȴ� ��ص��� ������ҡ��λ�� �� ����������
static uint16_t PowerOn_Counts = 0 ; 

void PowerOn(void)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//ÿ���ϵ�ʱ���һ�Σ��м��������������Ҫ�ȴ���һ���ϵ���Ч��
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	InversionKey_Scan() ;  
	
	//�ϵ���ʱ����
	if(PowerOn_Counts < 500) ++PowerOn_Counts ; 
	else
	{
	  	uint8_t KeyTemp = 0 ; 
		
		//AUTO �� CH6_DOWN ͬʱ���£�������λУ׼����
		KeyTemp  = (GPIOE -> IDR & ((1<<4) | (1<<6))) ; 
		//���빤��У׼
		if(((KeyTemp == 0x00)) || (FTDebug_err_flg == true))		//�ұ���ά Enter ���� �� + CH6_Downͬʱ���� ���� �ϵ�ʱ��λУ׼������Ч��������λУ׼״̬
		{
			//���빤��У׼ǰ���ر�����LED��ʾ 
			Init_ChannelDis(false);
			
			MenuCtrl.RunStep =  __stFTDebug;
			MenuCtrl.Sub_RunStep = 0 ; 
		}
		
		//�ް��� / ��Ч���� ����λֵУ׼���������� 
		else
		{
		  	//��ʾ��ǰͨ���������(AUX1 - AUX4)
		  	Init_ChannelDis(true);
			LED_State_Shake &= ~LED_BIND ;
			LED_State_ON    |=  LED_BIND ; 
			
			MenuCtrl.RunStep =  __stSarttUp;
			MenuCtrl.Sub_RunStep = 0 ; 
		}
	}
}
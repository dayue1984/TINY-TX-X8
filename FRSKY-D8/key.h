#ifndef _KEY_H_
#define _KEY_H_

typedef enum
{
 	__stEmpty_Key		= 0 ,  	
	__stKey_CH5    		= 1 , 
	__stKey_CH6     	= 2 , 	
	__stKey_CH7		= 3 ,
	__stKey_CH8     	= 4 ,
}ChannelKeyTypeDef ; 


typedef enum
{
  	__stOffset_EmptyKey	= 0  , 
	
	__stKey_R_Plus 		= 1 , 
	__stKey_R_Sub		= 2 ,

	__stKey_T_Plus		= 3 , 
	__stKey_T_Sub	 	= 4 , 

	__stKey_A_Plus	 	= 5 , 
	__stKey_A_Sub	 	= 6 , 

  	__stKey_E_Plus	 	= 7 , 
	__stKey_E_Sub	 	= 8 , 
	
}OffSetKeyTypeDef ; 

void key_int(void);
void key_Scan(void);
void InversionKey_Scan(void);

extern volatile ChannelKeyTypeDef ChannelKeyValue ; 

extern volatile OffSetKeyTypeDef  OffSetKeyValue     ; 
extern volatile bool OffSetKey_Repeatflg ; 
#endif

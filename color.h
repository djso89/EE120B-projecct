#ifndef __COLOR_H_
#define __COLOR_H_


#define colr_DS 0 //serial data pin connected to PA 0
#define colr_STCP 1 //load clk pin connected to PA1
#define colr_SHCP 2 //shift clk pin connected to PA2
#define col_DS 3
#define col_STCP 4
#define col_SHCP 5
#define SH_Prt PORTA

#include <bit.h>

uchar canvas[3][8];

uchar rg_pos[3][8];//current position of red ghost: this is manipulated by another syncSM
uchar bldorge_pos[3][8];//current position of bald ogre: this is manipulated by another syncSM
uchar gun_pos[3][8];
uchar Knf_pos[3][8];

uchar atk1pos[3][8];
uchar atk2pos[3][8];
//anode column transmit
inline void anodeCol_transmit(uchar col_data)
{
	
	for (uchar i = 0; i<8; i++)
	{
	//clear
		SH_Prt = SetBit(SH_Prt,col_STCP,0);
		SH_Prt = SetBit(SH_Prt,col_SHCP,0);
		SH_Prt = SetBit(SH_Prt,col_DS,0);
		
		SH_Prt = SetBit(SH_Prt,col_DS,GetBit(col_data,i));
		SH_Prt = SetBit(SH_Prt,col_SHCP,1);		
	}
	SH_Prt = SetBit(SH_Prt,col_STCP,1);
	
	//clear
		SH_Prt = SetBit(SH_Prt,col_STCP,0);
		SH_Prt = SetBit(SH_Prt,col_SHCP,0);
		SH_Prt = SetBit(SH_Prt,col_DS,0);
}	

inline void anodeCol_clear()
{

	for (uchar i = 0; i<8; i++)
	{
		SH_Prt = SetBit(SH_Prt,col_STCP,0);
		SH_Prt = SetBit(SH_Prt,col_SHCP,0);
		SH_Prt = SetBit(SH_Prt,col_DS,0);
		SH_Prt = SetBit(SH_Prt,col_SHCP,1);
	}
	SH_Prt = SetBit(SH_Prt,col_STCP,1);
	//clear
		SH_Prt = SetBit(SH_Prt,col_STCP,0);
		SH_Prt = SetBit(SH_Prt,col_SHCP,0);
		SH_Prt = SetBit(SH_Prt,col_DS,0);	
}

inline void color_transmit(uchar r_data,uchar gr_data,uchar bl_data)
{
	
	for(uchar i = 0; i<8;i++)
	{
		//clear
		SH_Prt = SetBit(SH_Prt,colr_STCP,0); 
		SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
		SH_Prt = SetBit(SH_Prt,colr_DS,0);
		
		SH_Prt = SetBit(SH_Prt,colr_DS,GetBit(bl_data,i));
		SH_Prt = SetBit(SH_Prt,colr_SHCP,1);
	}
	for(uchar i = 0; i<8; i++)
	{
		//clear
		SH_Prt = SetBit(SH_Prt,colr_STCP,0);
		SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
		SH_Prt = SetBit(SH_Prt,colr_DS,0);
		
		
		SH_Prt = SetBit(SH_Prt,colr_DS,GetBit(gr_data,i));
		SH_Prt = SetBit(SH_Prt,colr_SHCP,1);
	}

	for(uchar i = 0; i<8;i++)
	{
		//clear
		SH_Prt = SetBit(SH_Prt,colr_STCP,0);
		SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
		SH_Prt = SetBit(SH_Prt,colr_DS,0);
				
		SH_Prt = SetBit(SH_Prt,colr_DS,GetBit(r_data,i));
		SH_Prt = SetBit(SH_Prt,colr_SHCP,1);
	}
	SH_Prt = SetBit(SH_Prt,colr_STCP,1);
	
			//clear
	SH_Prt = SetBit(SH_Prt,colr_STCP,0);
	SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
	SH_Prt = SetBit(SH_Prt,colr_DS,0);
}

inline void color_clear()
{
	//SH_Prt = SetBit(SH_Prt,colr_STCP,0);
	for(uchar i = 0; i<8;i++)
	{
		SH_Prt = SetBit(SH_Prt,colr_STCP,0);
		SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
		SH_Prt = SetBit(SH_Prt,colr_DS,0);		
		SH_Prt = SetBit(SH_Prt,colr_SHCP,1);
	}
	for(uchar i = 0; i<8; i++)
	{
		SH_Prt = SetBit(SH_Prt,colr_STCP,0);		
		SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
		SH_Prt = SetBit(SH_Prt,colr_DS,0);
		SH_Prt = SetBit(SH_Prt,colr_SHCP,1);
	}

	for(uchar i = 0; i<8;i++)
	{
		SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
		SH_Prt = SetBit(SH_Prt,colr_DS,0);
		SH_Prt = SetBit(SH_Prt,colr_SHCP,1);
	}
	
	SH_Prt = SetBit(SH_Prt,colr_STCP,1);
	
	SH_Prt = SetBit(SH_Prt,colr_SHCP,0);
	SH_Prt = SetBit(SH_Prt,colr_STCP,0);
	SH_Prt = SetBit(SH_Prt,colr_DS,0);
}

enum LMtrx_States{LMtrx_initial,LMtrx_Rfr}LMtrx_State;

void LMTrx_display()
{
	static uchar i=0;
	switch(LMtrx_State)
	{
		case -1:
		LMtrx_State = LMtrx_initial;
		break;
		case LMtrx_initial:
		if (i<10)
		{
			LMtrx_State = LMtrx_initial;
		}
		else if (!(i<10))
		{
			LMtrx_State = LMtrx_Rfr;
			i=0;
		}
		break;
		case LMtrx_Rfr:
		LMtrx_State = LMtrx_Rfr;
		anodeCol_clear();
		color_clear();
		if(i<8)
		{
			i++;
		}
		else if(!(i<8))
		{
			i = 0;
		}
		break;
		default:
		LMtrx_State = LMtrx_initial;
	}
	switch(LMtrx_State)
	{
		case LMtrx_initial:
		anodeCol_clear();
		color_clear();
		i++;
		break;
		case LMtrx_Rfr:
		anodeCol_transmit(0x01<<i);
		canvas[0][i] = rg_pos[0][i]|bldorge_pos[0][i]|gun_pos[0][i]|Knf_pos[0][i]|atk1pos[0][i]|atk2pos[0][i];//red
		canvas[1][i] = rg_pos[1][i]|bldorge_pos[1][i]|gun_pos[1][i]|Knf_pos[1][i]|atk1pos[1][i]|atk2pos[1][i];//green
		canvas[2][i] = rg_pos[2][i]|bldorge_pos[2][i]|gun_pos[2][i]|Knf_pos[2][i]|atk1pos[2][i]|atk2pos[2][i];//blue
		color_transmit(canvas[0][i],canvas[1][i],canvas[2][i]);
		break;
		default:
		break;
	}
	
}


#endif
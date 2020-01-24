//living moving monster
#ifndef _MONSTER_H_
#define _MONSTER_H_
/**/
#include <color.h>

uchar display_rg;
uchar display_og;

//red_ghost picture
const uchar red_ghost[3][8]=
{
	{0x7C,0x1E,0x7F,0x1F,0x7F,0x1E,0x7C,0x00},//red rows
	{0x00,0x00,0x0C,0x00,0x00,0x0C,0x00,0x00},//green rows
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} //blue rows
};
//bald ogre picture
const uchar bald_ogre[3][8]=
{
	{0x00,0x24,0x10,0x20,0x14,0x00,0x00,0x00}, //red rows
	{0x7E,0x7B,0x5F,0x6F,0x5B,0x7E,0x00,0x00}, //green rows
	{0x00,0x20,0x10,0x20,0x10,0x00,0x00,0x00} //blue rows
};


/*displaying moving red ghost*/
enum RGLM_States{RGLM_Initial,RGLM_Set,RGLM_MoveR,RGLM_MoveDwn,RGLM_MoveL}RGLM_State;//red ghost living monster
void RG_LMTick()//redghost living monster
{
	static uchar tmpR;
	static uchar tmpGR;
	static uchar tmpBL;
	switch(RGLM_State)
	{
		case -1:
		RGLM_State = RGLM_Initial;
		break;
		case RGLM_Initial:
		if(!display_rg)
		{
			RGLM_State = RGLM_Initial;
		}
		else if(display_rg)
		{
			RGLM_State = RGLM_Set;
		}
		break;
		case RGLM_Set:
		if(display_rg)
		{
			RGLM_State = RGLM_MoveR;
		}
		else if(!display_rg)
		{
			RGLM_State = RGLM_Initial;
		}
		break;
		case RGLM_MoveR:
		if(display_rg)
		{
			RGLM_State = RGLM_MoveDwn;
		}
		else if(!display_rg)
		{
			RGLM_State = RGLM_Initial;
		}
		break;
		case RGLM_MoveDwn:
		if(display_rg)
		{
			RGLM_State = RGLM_MoveL;
		}
		else if(!display_rg)
		{
			RGLM_State = RGLM_Initial;
		}
		break;
		case RGLM_MoveL:
		if(display_rg)
		{
			RGLM_State = RGLM_Set;
		}
		else if(!display_rg)
		{
			RGLM_State = RGLM_Initial;
		}
		break;
		default:
		RGLM_State = RGLM_Initial;
	}
	switch(RGLM_State)
	{
		case RGLM_Initial:
		for (uchar i = 0; i<3;i++)
		{
			for (uchar j = 0;j<8;j++)
			{
				rg_pos[i][j]=0x00;
			}
		}
		break;
		case RGLM_Set:
		for(uchar i = 0; i<8; i++)
		{
			rg_pos[0][i]=red_ghost[0][i];
			rg_pos[1][i]=red_ghost[1][i];
			rg_pos[2][i]=red_ghost[2][i];
		}
		break;
		case RGLM_MoveR:
		tmpR = rg_pos[0][7];
		tmpGR = rg_pos[1][7];
		tmpBL = rg_pos[2][7];
		for(uchar i = 7; i>0 ; i--)
		{
			rg_pos[0][i]= rg_pos[0][i-1];
			rg_pos[1][i]= rg_pos[1][i-1];
			rg_pos[2][i]= rg_pos[2][i-1];
		}
		rg_pos[0][0]=tmpR;
		rg_pos[1][0] = tmpGR;
		rg_pos[2][0] = tmpBL;
		break;
		case RGLM_MoveDwn:
		for (uchar i = 0; i<3;i++)
		{
			for (uchar j = 0; j<8; j++)
			{
				rg_pos[i][j] = (rg_pos[i][j])<<2;
			}
		}
		break;
		case RGLM_MoveL:
		tmpR=	rg_pos[0][0];
		tmpGR = rg_pos[1][0];
		tmpBL = rg_pos[2][0];
		for(uchar i = 0; (i+1)<8;i++)
		{
			rg_pos[0][i]=rg_pos[0][i+1];
			rg_pos[1][i]=rg_pos[1][i+1];
			rg_pos[2][i]=rg_pos[2][i+1];
		}
		rg_pos[0][7]=tmpR;
		rg_pos[1][7]=tmpGR;
		rg_pos[2][7]=tmpBL;
		break;
		default:
		break;
	}
}
enum BOG_States{BOG_Initial,BOG_Set,BOG_MoveR,BOG_MoveDwn,BOG_MoveL}BOG_State;
void BldOG_LMTick()//redghost living monster
{
	static uchar tmpR;
	static uchar tmpGR;
	static uchar tmpBL;
	switch(BOG_State)
	{
		case -1:
		BOG_State = BOG_Initial;
		break;
		case BOG_Initial:
		if(!display_og)
		{
			BOG_State = BOG_Initial;
		}
		else if(display_og)
		{
			BOG_State = BOG_Set;
		}
		break;
		case BOG_Set:
		if(display_og)
		{
			BOG_State = BOG_MoveR;
		}
		else if(!display_og)
		{
			BOG_State = BOG_Initial;
		}
		break;
		case BOG_MoveR:
		if(display_og)
		{
			BOG_State = BOG_MoveDwn;
		}
		else if(!display_og)
		{
			BOG_State = BOG_Initial;
		}
		break;
		case BOG_MoveDwn:
		if(display_og)
		{
			BOG_State = BOG_MoveL;
		}
		else if(!display_og)
		{
			BOG_State = BOG_Initial;
		}
		break;
		case BOG_MoveL:
		if(display_og)
		{
			BOG_State = BOG_Set;
		}
		else if(!display_og)
		{
			BOG_State = BOG_Initial;
		}
		break;
		default:
		BOG_State = BOG_Initial;
	}
	switch(BOG_State)
	{
		case BOG_Initial:
		for (uchar i = 0; i<3;i++)
		{
			for (uchar j = 0;j<8;j++)
			{
				bldorge_pos[i][j]=0x00;
			}
		}
		break;
		case BOG_Set:
		for(uchar i = 0; i<8; i++)
		{
			bldorge_pos[0][i]=bald_ogre[0][i];
			bldorge_pos[1][i]=bald_ogre[1][i];
			bldorge_pos[2][i]=bald_ogre[2][i];
		}
		break;
		case BOG_MoveR:
		tmpR = bldorge_pos[0][7];
		tmpGR = bldorge_pos[1][7];
		tmpBL = bldorge_pos[2][7];
		for(uchar i = 7; i>0 ; i--)
		{
			bldorge_pos[0][i]= bldorge_pos[0][i-1];
			bldorge_pos[1][i]= bldorge_pos[1][i-1];
			bldorge_pos[2][i]= bldorge_pos[2][i-1];
		}
		bldorge_pos[0][0]=tmpR;
		bldorge_pos[1][0] = tmpGR;
		bldorge_pos[2][0] = tmpBL;
		break;
		case BOG_MoveDwn:
		for (uchar i = 0; i<3;i++)
		{
			for (uchar j = 0; j<8; j++)
			{
				bldorge_pos[i][j] = (bldorge_pos[i][j])<<2;
			}
		}
		break;
		case BOG_MoveL:
		tmpR=	bldorge_pos[0][0];
		tmpGR = bldorge_pos[1][0];
		tmpBL = bldorge_pos[2][0];
		for(uchar i = 0; (i+1)<8;i++)
		{
			bldorge_pos[0][i]=bldorge_pos[0][i+1];
			bldorge_pos[1][i]=bldorge_pos[1][i+1];
			bldorge_pos[2][i]=bldorge_pos[2][i+1];
		}
		bldorge_pos[0][7]=tmpR;
		bldorge_pos[1][7]=tmpGR;
		bldorge_pos[2][7]=tmpBL;
		break;
		default:
		break;
	}
}


#endif
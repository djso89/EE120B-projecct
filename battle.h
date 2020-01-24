#ifndef __BATTLE_H__
#define __BATTLE_H__
#include <keypad.h>
#include <color.h>
#include <mndata.h>

uchar GameOn;

unsigned char btnCntGun=0;
unsigned char btnCntKnife=0;
uchar pl2_go=0;//player two flag
uchar sw_knife;//player 2: switch to knife
uchar sw_gun; //player 2: switch to gun

uchar pl1_go=0;//player one flag
uchar atk1_go=0;//monster move1 go flag
uchar atk2_go=0;//monster move2 go flag

uchar keyread;
uchar update_scoreGun;
uchar update_scoreKnife;

uchar busymv1;
uchar busymv2;


signed short humanHp;
signed char monHp;
signed char monMp;
uchar stren;
uchar Defen;
uchar mon_num;
uchar spd_factor;//=5;
uchar ammo;
const uchar gun[3][8] =
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//red
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//green
	{0x00,0x08,0x08,0x0C,0x0C,0x1C,0x3C,0x68}//blue
};
const uchar knife[3][8]=
{
	{0x00,0x08,0x08,0x08,0x08,0x3E,0x08,0x08},//red
	{0x00,0x08,0x08,0x08,0x08,0x3E,0x08,0x08},//green
	{0x00,0x08,0x08,0x08,0x08,0x00,0x00,0x00}//blue
};

/*Monster attacks*/
/*Red Ghost Moves*/
const uchar Possess[3][3][8] =
{
	{	
		{0x7C,0x1E,0x7F,0x1F,0x7F,0x1E,0x7C,0x00},//red rows
		{0x00,0x00,0x0C,0x00,0x00,0x0C,0x00,0x00},//green rows
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} //blue rows
	},
	{	
		{0x7C,0x1E,0x7F,0x1F,0x7F,0x1E,0x7C,0x00},//red rows
		{0x7C,0x1E,0x7F,0x1F,0x7F,0x1E,0x7C,0x00},//green rows
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} //blue rows
	},
	{	
		{0x7C,0x1E,0x7F,0x1F,0x7F,0x1E,0x7C,0x00},//red rows
		{0x7C,0x1E,0x7F,0x1F,0x7F,0x1E,0x7C,0x00},//green rows
		{0x7C,0x1E,0x73,0x1F,0x7F,0x12,0x7C,0x00} //blue rows		
	}	
};

const uchar BrnAgnMv[3][3][8]=
{
	{	{0x38,0x70,0xFC,0xFE,0xFF,0xFC,0x70,0x38},//red
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//green
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}//blue
},
{	{0x38,0x70,0xFC,0xFE,0xFF,0xFC,0x70,0x38},//red
{0x00,0x20,0x70,0xFC,0xFC,0x70,0x20,0x00},//green
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}//blue
},
{
	{0x38,0x70,0xFC,0xFE,0xFF,0xFC,0x70,0x38},//red
	{0x00,0x20,0x50,0x0C,0x04,0x50,0x20,0x00},//green
	{0x00,0x00,0x20,0xF0,0xF8,0x20,0x00,0x00}//blue
}
};

/*Bald Ogre's Moves*/
const uchar bash[3][3][8]=
{
	{	
		{0x00,0x24,0x10,0x20,0x14,0x00,0x00,0x00}, //red rows
		{0x7E,0x7B,0x5F,0x6F,0x5B,0x7E,0x00,0x00}, //green rows
		{0x00,0x20,0x10,0x20,0x10,0x00,0x00,0x00} //blue rows
	},
	{
		{0x00,0x0A,0x14,0x00,0x12,0x00,0x00,0x00},//red row
		{0x3F,0x2B,0x37,0x3F,0x2D,0x3F,0x1E,0x00},//green row
		{0x00,0x0A,0x14,0x00,0x00,0x00,0x00,0x00}//blue
	},
	{
		{0x00,0x00,0x00,0x00,0x00,0x0A,0x14,0x00},
		{0x00,0x00,0x00,0x00,0x3F,0x2B,0x37,0x3F},
		{0x00,0x00,0x00,0x00,0x00,0x0A,0x14,0x3F}		
	}
	
};

const uchar GndStomp[3][3][8]=
{
	{
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //red rows
		{0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00}, //green rows
		{0xF0,0xB0,0xD0,0x00,0x00,0x00,0x00,0x00} //blue rows
	},
	{
		{0x00,0x7D,0x7F,0x5F,0x6F,0x5F,0x7D,0x00},//red row
		{0x00,0x00,0x20,0x10,0x20,0x10,0x00,0x00},//green row
		{0x00,0x7D,0x7B,0x5F,0x6F,0x5B,0x7D,0x00}//blue
	},
	{
		{0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00},
		{0x00,0x00,0x00,0x00,0x00,0xE0,0xB0,0xF0},
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
	}				
};


enum PLT_States {PLT_initial,PLT_pl1go,PLT_pl2go}PLT_State;//player timer

void PlayerTimerTck()
{
	static uchar spd_cnt;
	switch (PLT_State)
	{
		case -1:
			PLT_State = PLT_initial;
			break;
		case PLT_initial:
			if(GameOn)
			{
				PLT_State= PLT_pl1go;
			}
			else if(!GameOn)
			{
				PLT_State= PLT_initial;
			}
			break;
		case PLT_pl1go:
			if(GameOn&&(spd_cnt<spd_factor))
			{
				PLT_State= PLT_pl1go;
			}
			else if(GameOn && !(spd_cnt<spd_factor))
			{
				PLT_State= PLT_pl2go;
				spd_cnt= 0;
			}
			else if (!GameOn)
			{
				PLT_State = PLT_initial;
				spd_cnt = 0;
			}
			break;
		case PLT_pl2go:
			if(GameOn&&(spd_cnt<spd_factor))
			{
				PLT_State= PLT_pl2go;
			}
			else if(GameOn&& !(spd_cnt<spd_factor))
			{
				PLT_State= PLT_pl1go;
				spd_cnt= 0;
			}
			else if (!GameOn)
			{
				PLT_State = PLT_initial;
				spd_cnt = 0;
			}
			break;
		default:
			PLT_State=PLT_initial;
	}
	switch (PLT_State)
	{
		case PLT_initial:
			PORTB = SetBit(PORTB,7,0);
			PORTB = SetBit(PORTB,6,0);
			pl1_go = 0;
			pl2_go = 0;
			break;
		case PLT_pl1go:
			PORTB = SetBit(PORTB,7,0);
			PORTB = SetBit(PORTB,6,1);
			pl1_go = 1;
			pl2_go = 0;
			spd_cnt++;
			break;
		case PLT_pl2go:
			PORTB = SetBit(PORTB,7,1);
			PORTB = SetBit(PORTB,6,0);
			pl1_go = 0;
			pl2_go = 1;
			spd_cnt++;
			break;
		default:
			break;
	}
}

enum MMV_States {MMV_initial,MMV_Stdby,MMV_ATK1Go,MMV_ATK2Go}MMV_State;//monster move SM: this will turn on by PLT(player timer) sm
void MonAtkTck()
{
	uchar kp; kp = GetKeypadKey();
	static uchar holdcnt;
	switch (MMV_State)
	{
		case -1:
			MMV_State = MMV_initial;
			break;
		case MMV_initial:
			if(pl1_go)
			{
				MMV_State = MMV_Stdby;
			}
			else if (!pl1_go)
			{
				MMV_State = MMV_initial;
			}
			break;
		case MMV_Stdby:
			if(pl1_go && !kp)
			{
				MMV_State = MMV_Stdby;
			}
			else if (pl1_go && (kp=='A'))
			{
				MMV_State = MMV_ATK1Go;				
			}
			else if (pl1_go && (kp== 'B'))
			{
				MMV_State = MMV_ATK2Go;
			}				
			else if (!pl1_go)
			{
				MMV_State = MMV_initial;
			}
			break;
		case MMV_ATK1Go:
			if(pl1_go&&(holdcnt<8))
			{
				MMV_State = MMV_ATK1Go;
			}
			else if (pl1_go&&!(holdcnt<8))
			{
				MMV_State = MMV_Stdby;
				holdcnt =0;
			}
			else if (!pl1_go)
			{
				MMV_State = MMV_initial;						
				holdcnt = 0;
			}
			break;
		case MMV_ATK2Go:
			if(pl1_go &&(holdcnt <8))
			{
				MMV_State = MMV_ATK2Go;
			}
			else if(pl1_go &&!(holdcnt <8))
			{
				MMV_State = MMV_Stdby;
				holdcnt = 0;
			}			
			else if (!pl1_go)
			{
				MMV_State = MMV_initial;
				holdcnt = 0;								
			}
			break;
		default:
			MMV_State = MMV_initial;
	}
	switch (MMV_State)
	{
		case MMV_initial:
			atk1_go= 0;
			atk2_go= 0;
			keyread = 0;			
			break;
		case MMV_Stdby:
			keyread = 0;
			break;
		case MMV_ATK1Go:
			keyread = 'A';
			atk1_go= 1;
			atk2_go= 0;
			holdcnt++;
			break;
		case MMV_ATK2Go:
			keyread = 'B';
			atk1_go= 0;
			atk2_go= 1;
			holdcnt++;			
			break;			
		default:
			break;
	}
}


enum ATK1_States{ATK1_initial,ATK1_exe} ATK1_State;
void ATK1Tck()
{
	static uchar cnt;
	switch(ATK1_State)
	{
		case -1:
		ATK1_State = ATK1_initial;
		break;
		case ATK1_initial:
		if(atk1_go&&!busymv1)
		{
			ATK1_State = ATK1_exe;
		}
		else if(!atk1_go||busymv1)
		{
			ATK1_State = ATK1_initial;
		}
		break;
		case ATK1_exe:
			if(atk1_go&&!busymv1)
			{
				ATK1_State = ATK1_exe;
				if(cnt ==3)
				{
					for (uchar i = 0; i <3 ; i++)
					{
						for(uchar j = 0; j<8;j++)
						{														
							atk1pos[i][j]=0x00;												
						}
					}
					cnt=0;
				}				
			}
			else if(!atk1_go||busymv1)
			{
				ATK1_State = ATK1_initial;
				cnt = 0;
			}
			break;
		default:
			ATK1_State = ATK1_initial;
	}
	switch(ATK1_State)
	{
		case ATK1_initial:
			for (uchar i = 0; i <3 ; i++)
			{
				for(uchar j = 0; j<8;j++)
				{
					atk1pos[i][j]=0x00;
				}
			}
			cnt = 0;
			break;
		case ATK1_exe:
			for (uchar i = 0; i<3;i++)
			{
				for (uchar j = 0; j <8;j++)
				{
					if(mon_num == 1)
					{
						atk1pos[i][j]=Possess[cnt][i][j];
					}
					else if(mon_num == 2)
					{
						atk1pos[i][j]=bash[cnt][i][j];
					}
				}
			}
			cnt++;
			break;
		default:
			break;
	}
}


enum ATK2_States{ATK2_initial,ATK2_exe} ATK2_State;
void ATK2Tck()
{
	static uchar cnt;
	switch(ATK2_State)
	{
		case -1:
			ATK2_State = ATK2_initial;
			break;
		case ATK2_initial:
			if(atk2_go&&!busymv2)
			{
				ATK2_State = ATK2_exe;
			}
			else if(!atk2_go||busymv2)
			{
				ATK2_State = ATK2_initial;
			}
			break;
		case ATK2_exe:
			if(atk2_go&&!busymv2)
			{
				ATK2_State = ATK2_exe;
				if(cnt ==3)
				{
					for (uchar i = 0; i <3 ; i++)
					{
						for(uchar j = 0; j<8;j++)
						{
							atk2pos[i][j]=0x00;
						}
					}
					cnt=0;
				}
			}
			else if(!atk2_go||busymv2)
			{
				ATK2_State = ATK2_initial;
				cnt = 0;
			}
			break;
		default:
			ATK2_State = ATK2_initial;
	}
	switch(ATK2_State)
	{
		case ATK2_initial:
			for (uchar i = 0; i <3 ; i++)
			{
				for(uchar j = 0; j<8;j++)
				{
					atk2pos[i][j]=0x00;
				}
			}
			cnt = 0;
			break;
		case ATK2_exe:
			for (uchar i = 0; i<3;i++)
			{
				for (uchar j = 0; j <8;j++)
				{
					if(mon_num == 1)
					{
						atk2pos[i][j]=BrnAgnMv[cnt][i][j];
					}
					else if (mon_num == 2)
					{
						atk2pos[i][j]=GndStomp[cnt][i][j];
					}
				}
			}
			cnt++;
			break;
		default:
			break;
	}
}

/*switching weapon SM for player two. SWTck switches weapon from knife to gun*/


enum SW_States{SW_initial,SW_Stdby,SW_waitbtn,SW_switch,SW_switchBack}SW_State;
void SWTck()
{
	static uchar B2;   B2 = !GetBit(PINB,2);
	switch(SW_State)
	{
		case -1:
			SW_State = SW_initial;
			break;
		case SW_initial:
			if(pl2_go)
			{
				SW_State = SW_Stdby;
			}
			else if (!pl2_go)
			{
				SW_State = SW_initial;
			}
			break;
		case SW_Stdby:
			if(!B2&&pl2_go)
			{
				SW_State = SW_Stdby;
			}
			else if(B2&&pl2_go)
			{
				SW_State = SW_waitbtn;
			}
			else if(!pl2_go)
			{
				SW_State = SW_initial;
			}
			break;
		case SW_waitbtn:
			if(B2&&pl2_go)
			{
				SW_State = SW_waitbtn;
			}
			else if(!B2&&pl2_go)
			{
				SW_State = SW_switch;
			}
			else if(!pl2_go)
			{
				SW_State = SW_initial;
			}
			break;
		case SW_switch:
			if(B2&&pl2_go)
			{
				SW_State = SW_switchBack;
			}
			else if(!B2&&pl2_go)
			{
				SW_State = SW_switch;
			}
			else if(!pl2_go)
			{
				SW_State = SW_initial;
			}
			break;
		case SW_switchBack:
			if(B2&&pl2_go)
			{
				SW_State = SW_switchBack;
			}
			else if(!B2&&pl2_go)
			{
				SW_State = SW_Stdby;
			}
			else if(!pl2_go)
			{
				SW_State = SW_initial;
			}
			break;
		default:
			SW_State = SW_Stdby;
	}
	switch(SW_State)
	{
		case SW_initial:
			sw_knife = 0;
			sw_gun = 0;
			break;
		case SW_Stdby:
			sw_knife = 1;
			sw_gun = 0;
			break;
		case SW_waitbtn:
			break;
		case SW_switch:
			sw_knife = 0;
			sw_gun = 1;
			break;
		case SW_switchBack:
			break;
		default:
			break;
	}
}

/*animating knife stab mmovement SM. when sw_knife is on which is triggered by SWTck function,
knife is available to use to stab monster, and count the number of button presses.
*/
enum Knf_States{Knf_initial,Knf_set,Knf_stab,Knf_Wstab}Knf_State;
void KnfStabTck()
{
	static uchar B1;
	static uchar stb_cnt;

	
	B1 = !GetBit(PINB,1);
	switch(Knf_State)
	{
		case -1:
			Knf_State = Knf_initial;
			break;
		case Knf_initial:
			if(!sw_knife)
			{
				Knf_State = Knf_initial;
			}
			else if (sw_knife)
			{
				Knf_State = Knf_set;
			}
			break;
		case Knf_set:
			if(!B1&&sw_knife)
			{
				Knf_State = Knf_set;
			}
			else if(B1&&sw_knife)
			{
				Knf_State = Knf_stab;
			}
			else if (!sw_knife)
			{
				Knf_State = Knf_initial;
			}
			break;
		case Knf_stab:
			if(B1 &&sw_knife&&(stb_cnt<5))
			{	
				Knf_State = Knf_stab;
			}
			else if(B1&&sw_knife&&!(stb_cnt<5))
			{
				Knf_State = Knf_Wstab;
				stb_cnt = 0;
				btnCntKnife++;				
			}
			else if(!B1&&sw_knife)
			{
				Knf_State = Knf_set;
				stb_cnt = 0;
			}
			else if(!sw_knife)
			{
				Knf_State = Knf_initial;
				stb_cnt = 0;
			}
			break;
		case Knf_Wstab:
			if (B1&&sw_knife)
			{
				Knf_State = Knf_Wstab;
			}
			else if (!B1&&sw_knife)
			{
				Knf_State = Knf_set;
				update_scoreKnife=1;
			}
			else if (!sw_knife)
			{
				Knf_State = Knf_initial;
			}
			break;
		default:
			Knf_State = Knf_initial;
	}
	switch(Knf_State)
	{
		case Knf_initial:
			if (!pl2_go)
			{
				btnCntKnife = 0;
			}
			for(uchar i = 0; i<8 ; i++)
			{
				Knf_pos[0][i]=0x00;
				Knf_pos[1][i]=0x00;
				Knf_pos[2][i]=0x00;
			}
			stb_cnt = 0;
			update_scoreKnife = 0;		
			break;
		case Knf_set:
			for(uchar i = 0; i<8 ; i++)
			{
				Knf_pos[0][i]=knife[0][i];
				Knf_pos[1][i]=knife[1][i];
				Knf_pos[2][i]=knife[2][i];
			}
			update_scoreKnife = 0;
			break;
		case Knf_stab:
			for(int j = 0; j<8 ; j++)
			{
				Knf_pos[0][j]=Knf_pos[0][j+1];
				Knf_pos[1][j]=Knf_pos[1][j+1];
				Knf_pos[2][j]=Knf_pos[2][j+1];				
			}
			for(int k = (7-stb_cnt);k<=7;k++)
			{
				Knf_pos[0][k]=0;
				Knf_pos[1][k]=0;
				Knf_pos[2][k]=0;
			}
			stb_cnt++;
			break;
		case Knf_Wstab:
			break;
		default:
			break;
	}
}

/*animating gun shooting SM. when sw_gun is on which is triggered by SWTck function,
knife is available to use to stab monster, and count the number of button B0 presses.
*/
enum GM_States{GM_initial,GM_Set,GM_mvBack,GM_mvBackWait,GM_LdBullet,GM_hit,GM_shoot}GM_State;

void GMShoot()
{
	static uchar tmp1;
	static uchar tmp2;
	static uchar shoot_cnt;//shoot counter
	static uchar B0;	B0 = !GetBit(PINB,0);
	switch(GM_State)//transitions
	{
		case -1:
			GM_State = GM_initial;
			break;
		case GM_initial:
			if(sw_gun)
			{
				GM_State = GM_Set;
			}
			else if(!sw_gun)	
			{
				GM_State = GM_initial;
			}
			break;
		case GM_Set:
			if(!B0&&sw_gun)
			{
				GM_State = GM_Set;
			}
			else if(B0&&sw_gun)
			{
				GM_State = GM_mvBack;
			}
			else if(!sw_gun)
			{
				GM_State = GM_initial;
			}
			break;
		case GM_mvBack:
			if(!B0&&sw_gun)
			{
				GM_State = GM_Set;
			}
			else if(B0&&sw_gun)
			{
				GM_State = GM_mvBackWait;
			}
			else if (!sw_gun)
			{
				GM_State = GM_initial;
			}
			break;
		case GM_mvBackWait:
			if(B0&&sw_gun)
			{
				GM_State = GM_mvBackWait;
			}
			else if(!B0&&sw_gun)
			{
				GM_State = GM_LdBullet;
				btnCntGun++;
			}
			else if(!sw_gun)
			{
				GM_State = GM_initial;
			}
			break;
		case GM_LdBullet:
			GM_State = GM_shoot;
			shoot_cnt = 4;
			break;
		case GM_shoot:
			if(shoot_cnt > 0)
			{
				GM_State = GM_shoot;
			}
			else
			{
				GM_State = GM_hit;			
			}
			break;
		case GM_hit:
			GM_State = GM_Set;
			shoot_cnt = 4;
			break;
		default:
			GM_State = GM_initial;
	}
	switch(GM_State)//actions
	{
		case GM_initial:
			if(!pl2_go)
			{
				btnCntGun = 0;
			}
			for (uchar i = 0; i<3;i++)
			{
				for (uchar j = 0;j<8;j++)
				{
					gun_pos[i][j]=0x00;
				}
			}
			break;
		case GM_Set:
			update_scoreGun = 0;
			for(uchar i = 0; i<8; i++)
			{
				gun_pos[0][i]=gun[0][i];
				gun_pos[1][i]=gun[1][i];
				gun_pos[2][i]=gun[2][i];
			}
			break;
		case GM_mvBack:
			for(uchar i= 0; i<4; i++)
			{
				gun_pos[0][i+4]= gun_pos[0][i];
				gun_pos[1][i+4]= gun_pos[1][i];
				gun_pos[2][i+4]= gun_pos[2][i];
			}
			for(uchar i = 0; i<4; i++)
			{
				gun_pos[0][i]= 0x00;
				gun_pos[1][i]= 0x00;
				gun_pos[2][i]= 0x00;
			}
			break;
		case GM_mvBackWait:
			break;
		case GM_LdBullet:
			//cyan bullet appears
			gun_pos[1][4]=0x08;//bullet appears
			gun_pos[2][4]=0x08;//bullet appears		
			update_scoreGun = 1;
			break;
		case GM_shoot:
			tmp1 = gun_pos[1][shoot_cnt];
			tmp2 = gun_pos[2][shoot_cnt];
			gun_pos[1][shoot_cnt]= 0;
			gun_pos[2][shoot_cnt]= 0;		
			gun_pos[1][shoot_cnt-1]=tmp1;
			gun_pos[2][shoot_cnt-1]=tmp2;
			shoot_cnt--;
			break;
		case GM_hit:
			gun_pos[1][shoot_cnt]= 0;
			gun_pos[2][shoot_cnt]= 0;
			break;
		default:
			break;
	}
}




#endif
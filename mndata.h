#ifndef __MNDATA_H__
#define __MNDATA_H__

#include <avr/eeprom.h>

#define uchar unsigned char


//eeprom write protocol
uchar go_write;
uchar write_busy;
uchar slot_pick;

typedef struct _MnStats{
	uchar MnNum;
	uchar Lvl;
	uchar Str;
	uchar Def;
	signed char Hp;
	signed char Mp;
	uchar Spd;	
}MnStats;

MnStats EEMEM SlotA_mem;
MnStats EEMEM SlotB_mem;
MnStats EEMEM SlotC_mem;

MnStats data;

MnStats SetStats(uchar m_num,uchar l,uchar str,uchar def,signed char hp,signed char mp,uchar spd)
{
	static MnStats tmp; 
	tmp.MnNum = m_num;
	tmp.Lvl = l;
	tmp.Str = str;
	tmp.Def = def;
	tmp.Hp = hp;
	tmp.Mp = mp;
	tmp.Spd = spd;
	
	return tmp;
}

signed char GetHp(MnStats mon)
{
	return mon.Hp;
}


char mvList[2][2][20] = {{{"Possess"},{"Burning Agony"}},//Red Ghost's moves
							{{"Bash"},{"Stomp"}}//bald ogre's moves		
						};

char * concatStat(MnStats data)
{
	static char str_buf[50];
	sprintf(str_buf,"#:%d,L:%d,S:%d,H:%d,M:%d,D:%d,Sp:%d",data.MnNum,
	data.Lvl,data.Str,data.Hp,data.Mp,data.Def,data.Spd);
	
	return str_buf;
}

inline uchar H_GetMLdmg(uchar NmashKnf,uchar Def)//get melee damage
{
	static uchar mashKnife;
	//static char knifeDmg;	
	if(NmashKnf>Def)
	{
		mashKnife = NmashKnf-Def;
		if(mashKnife >= 5)
		{
			return 1;
		}
		else if(mashKnife >= 10)
		{
			return 2;
		}
		else
		{
			return 0;
		}	
	}
	else 
	{
		return ('\0');
	}				
}



inline uchar H_GetLRdmg(uchar NmashGun,uchar Def)
{
	static uchar mashGun;
	
	if(NmashGun>(Def-10))
	{
		mashGun = NmashGun-(Def-10);		
		if(mashGun >= 15)
		{
			return 4;
		}
		else if(mashGun >= 20)
		{
			return 5;
		}
		else
		{
			return 0;
		}
	}		
	else
	{
		return ('\0');
	}
	
}


inline uchar GetSpdFactor(uchar speed)
{
	if(speed <= 5&&(speed >0))
	{
		return 10;//10 second
	}
	else if((speed >5)&& (speed<=10))
	{
		return 8;
	}
	else if((speed>10))
	{
		return 5;
	}
}

enum dw_States {dw_initial, dw_wrtEEPROM, dw_done}dw_State;
void DataWrtTck()
{
	switch(dw_State)
	{
		case -1:
			dw_State = dw_initial;
			break;
		case dw_initial:
			if(!go_write)
			{
				dw_State = dw_initial;
			}
			else if(go_write)
			{
				dw_State = dw_wrtEEPROM;
				write_busy = 1;
			}
			break;
		case dw_wrtEEPROM:
			dw_State = dw_done;
			break;
		case dw_done:
			dw_State = dw_initial;
			break;
		default:
			dw_State = dw_initial;
	}
	switch(dw_State)
	{
		case dw_initial:
			write_busy = 0;
			break;
		case dw_wrtEEPROM:
			write_busy = 1;
			if(slot_pick == 'A')
			{
				eeprom_write_block(&data,&SlotA_mem,sizeof(MnStats));
			}
			else if(slot_pick == 'B')
			{
				eeprom_write_block(&data,&SlotB_mem,sizeof(MnStats));
			}
			else if(slot_pick =='C')
			{
				eeprom_write_block(&data,&SlotC_mem,sizeof(MnStats));
			}
			break;
		case dw_done:
			write_busy = 0;
			break;
		default:
			break;
	}
}



#endif
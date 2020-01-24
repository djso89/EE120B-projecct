/*
 * LED_matrix_test.c
 *
 * Created: 8/19/2014 1:05:32 PM
 *  Author: dan
 */ 


#include <avr/io.h>
#include <mndata.h>
#include <bit.h>
#include <timer.h>
#include <battle.h>
#include <monster.h>
#include <keypad.h>
#include <io.c>





const MnStats RG_default = {1,1,12,15,15,10,15};
const MnStats OG_default = {2,1,25,20,20,5,5};
		




	
enum UI_States{UI_initial,
				UI_intr,
				UI_Menu,
				UI_MtrMenu,//monster menu
				UI_MtrStrge,UI_readSlot,UI_dispMnStrge,//monster storage menus
				UI_NewMon,UI_nmSlot,UI_nmDispStat,UI_nmSetData,UI_nmWrite,UI_nmSaved,//make new monster menu
				UI_BttlMenu,UI_BtlmChseMn,UI_btlreadSlot,UI_btlChkEmpty,UI_BtlDispMon,UI_BtlSetStats, //battle menu
				//battle interfacing states
				UI_GameOn,UI_BtlStdby,UI_MnAtksMenu,UI_DisplayAtk1,
				UI_DisplayAtk2,UI_ChkHumanHP,UI_PL1Won,UI_WaitScr,UI_DispScrKnf,UI_DispScrGun,UI_DmgPL1,UI_PL2Won,	
				UI_Feed} UI_State;//user interface/command prompt
void UsrInterface()
{
	uchar key;
	key = GetKeypadKey();
	static uchar mon_pick;
	static uchar k;//string index
	static uchar cnt;//time counter
	static char str[100];
	static char * str_tmp;
	static MnStats slotReadRam;
	
	static unsigned char mashGun;
	static unsigned char mashKnife;
	static unsigned char tmpGun = 0;
	static unsigned char tmpKnife=0;
	
	switch(UI_State)
	{
		case -1:
			UI_State = UI_initial;
			break;
		case UI_initial:
			UI_State = UI_intr;
			LCD_DisplayString(1,"Battle Mnstr:   press any");
			break;
		case UI_intr:
			if(!key)
			{
				UI_State = UI_intr;
			}
			else 
			{
				UI_State = UI_Menu;
				LCD_DisplayString(1,"Main A:Mstrs    B:Bttle  C:Feed");//menu								
			}
			break;
//main menu			
		case UI_Menu:
			if (!key)
			{
				//currently displaying "Main A:Mstrs    B:Bttle  C:Feed"
				UI_State = UI_Menu;	
			}
			else if(key=='A')
			{
				UI_State = UI_MtrMenu;
				LCD_DisplayString(1,"1:New Mnstr 2:Mnstr Strge 3:back");//monster menu
			}
			else if(key == 'B')
			{
				UI_State = UI_BttlMenu;
				LCD_DisplayString(1,"Battle: 1:choose Mnstr 2:back");//battle menu	
			}
			else if(key == 'C')
			{
				UI_State = UI_Feed;
				LCD_DisplayString(1,"Feed: 1:Meat    2:water 3:back");
			}
			break;
//monster menu			
		case UI_MtrMenu:
			if(!key)
			{
				//currently displaying "1:New Mnstr 2:Mnstr Strge 3:back"
				UI_State = UI_MtrMenu;	
			}
			else if(key == '1')
			{
				UI_State = UI_NewMon;
				LCD_DisplayString(1,"Pick: slotA,slotB,slotC,4:back");
			}
			else if(key == '2')
			{
				UI_State = UI_MtrStrge;
				LCD_DisplayString(1,"MnStrge:SLOTA,SLOTB,SLOTC,4:bk");
			}
			else if(key =='3')
			{
				UI_State = UI_Menu;
				LCD_DisplayString(1,"Main A:Mstrs    B:Bttle  C:Feed");
			}
			break;
	//subMonster menu: new monster
		case UI_NewMon:
			if(!key)
			{
				//currently displaying Pick: slotA,slotB,slotC,4:back
				UI_State = UI_NewMon;
			}
			else if((key == 'A' )||(key == 'B')||(key =='C'))//or 'b' or 'c'
			{
				slot_pick = key;				
				UI_State =	UI_nmSlot;				
				strcpy(str,"Pick Mnstr: 1:RedGhst,2:BldOgre,3:back");
				LCD_DisplayString(1,str);
				
			}
			else if(key == '4')
			{
				UI_State = UI_MtrMenu;
				LCD_DisplayString(1,"1:New Mnstr 2:Mnstr Strge 3:back");//monster menu								
			}
			break;
//sub menu of new monster: new monster on slot 
		case UI_nmSlot:		
			if (!key)
			{
				//currently displaying Pick Mnstr: 1:RedGhst,2:BldOgre,3:back
				 if (cnt>=10)
				 {
					 if(k < strlen(str))
					 {
						 LCD_DisplayString(1,str+k);
					 }
					 else
					 {
						 LCD_DisplayString(1,str);
						 k = 0;
					 }
					 k++;
					 cnt=0;
				 }
				UI_State = UI_nmSlot;
				
			}
			else if (key == '3')
			{
				UI_State = UI_NewMon;
				LCD_DisplayString(1,"Pick: slotA,slotB,slotC,4:back");
				k =0;
				cnt = 0;			
			}
			else if( (key == '1')||(key == '2')) 
			{
				mon_pick = key;
				UI_State = UI_nmDispStat;
				k=0;
				cnt =0;
				if(mon_pick == '1')
				{				
					str_tmp = concatStat(RG_default);
					strcpy(str,"Red Ghost");
					strcat(str,str_tmp);
					strcat(str," *:confirm, #:back");						
					LCD_DisplayString(1,str);
				}
				if(mon_pick == '2')
				{
					strcpy(str,"Bald Orge");
					str_tmp = concatStat(OG_default);					
					strcat(str,str_tmp);
					strcat(str," *:confirm, #:back");						
					LCD_DisplayString(1, str);
				}
			}						
			break;
//display stat menu		
		case UI_nmDispStat:
			 if(!key)
			 {
				 UI_State = UI_nmDispStat;
				 if (cnt>=10)
				 {
					 if(k < strlen(str))
					 {
						 LCD_DisplayString(1,str+k);
					 }
					 else
					 {
						 LCD_DisplayString(1,str);
						 k = 0;
					 }
					 k++;
					 cnt=0;					 
				 }

			 }			 			 
			 else if(key=='#')//back 
			 {
				 UI_State = UI_nmSlot;
				 cnt=0;
				 k=0;
				 strcpy(str,"Pick Mnstr:1:RedGhst,2:BldOgre,3:back");
				 LCD_DisplayString(1,str);
			 }
			 else if(key == '*')
			 {
				 UI_State = UI_nmSetData;
				 cnt  = 0;
				 k = 0;
				 display_rg = 0;
				 display_og = 0;
				 strcpy(str,"saving");
				 LCD_DisplayString(1,str);
			 }
			 break;	
		case UI_nmSetData:
			UI_State = UI_nmWrite;
			go_write = 1;
			break;
		case UI_nmWrite:
			if(write_busy)
			{
				UI_State =	UI_nmWrite;
			}
			else if(!write_busy)
			{
				UI_State = UI_nmSaved;
				go_write = 0;
				LCD_DisplayString(1,"Saved!!");
			}			
			break;
		case UI_nmSaved:
			if (cnt <10)			
			{
				UI_State = UI_nmSaved;
			}
			else if(!(cnt <10))
			{
				UI_State = UI_MtrMenu;
				LCD_DisplayString(1,"1:New Mnstr 2:Mnstr Strge 3:back");				
				cnt = 0;
			}
			break;
//monster storage menu
		case UI_MtrStrge:
			if(!key)
			{
				//currently displaying "MnStrge:SLOTA,SLOTB,SLOTC,4:bk"
				UI_State = UI_MtrStrge;
			}
			else if ((key == 'A')||(key == 'B')||(key == 'C'))
			{
				UI_State = UI_readSlot;
				slot_pick = key;
				
			}
			else if (key == '4')
			{
				UI_State = UI_MtrMenu;
				LCD_DisplayString(1,"1:New Mnstr 2:Mnstr Strge 3:back");
			}
			break;
		case UI_readSlot:
			UI_State = UI_dispMnStrge;
			break;
		case UI_dispMnStrge:
			if(!key)
			{	if(cnt>=10)
				{
					if(k <strlen(str))
					{
						LCD_DisplayString(1,str+k);
					}
					else
					{
						LCD_DisplayString(1,str);
						k=0;
					}
					k++;
					cnt = 0;
				}
				UI_State = UI_dispMnStrge;
			}
			else if(key == '#')
			{
				UI_State = UI_MtrStrge;
				LCD_DisplayString(1,"MnStrge:SLOTA,SLOTB,SLOTC,4:bk");
				cnt = 0;
				k = 0;
			}
			break;		
//Battle menu
		case UI_BttlMenu:
			if(!key)
			{
				//currently displaying "Battle: 1:choose Mnstr 2:back"
				UI_State = UI_BttlMenu;
			}
			else if (key == '1')
			{
				UI_State = UI_BtlmChseMn;
				LCD_DisplayString(1,"A:SLOTA B:SLOTB C:SLOTC 4:back");
			}
			else if (key == '2')
			{
				UI_State = UI_Menu;
				LCD_DisplayString(1,"Main A:Mstrs    B:Bttle  C:Feed");
			}			
			break;
//sub menu of battle:Choose Monster from slot A to C
		case UI_BtlmChseMn:
			if(!key)
			{
				//currently displaying A:SLOTA B:SLOTB C:SLOTC 4:back
				UI_State = UI_BtlmChseMn;
			}
			else if ((key == 'A')||(key == 'B')||(key == 'C'))
			{
				UI_State = UI_btlreadSlot;
				slot_pick = key;
			}
			else if(key == '4')						
			{
				UI_State = UI_BttlMenu;
				LCD_DisplayString(1,"Battle: 1:choose Mnstr 2:back");
			}
			break;
		case UI_btlreadSlot:
			UI_State = UI_btlChkEmpty;
			break;
		case UI_btlChkEmpty:
			if(slotReadRam.MnNum == 0)
			{
				UI_State = UI_BtlmChseMn;
				LCD_DisplayString(1,"A:SLOTA B:SLOTB C:SLOTC 4:back");
			}
			else if (!(slotReadRam.MnNum == 0))
			{
				UI_State = UI_BtlDispMon;
				str_tmp = concatStat(slotReadRam);
				strcpy(str,str_tmp);
				strcat(str," *:ok #:bk");
				LCD_DisplayString(1,str);	
			}
			break;
		case UI_BtlDispMon:
			if(!key)
			{	
				UI_State = UI_BtlDispMon;
				if(cnt>=10)
				{
					if(k<strlen(str))
					{
						LCD_DisplayString(1,str+k);
					}
					else
					{
						LCD_DisplayString(1,str);
						k=0;
					}
					k++;
					cnt = 0;
				}				
			}
			else if (key == '*')
			{
				UI_State = UI_BtlSetStats;
				display_og = 0;
				display_rg =0;
				LCD_DisplayString(1,"Loading....");
			}
			else if (key == '#')
			{
				UI_State = UI_BtlmChseMn;
				LCD_DisplayString(1,"A:SLOTA B:SLOTB C:SLOTC 4:back");
				cnt = 0;
				k =0;
			}
			break;
		case UI_BtlSetStats:
			UI_State = UI_GameOn;
			break;
//battle interfacing			
		case UI_GameOn:
			UI_State = UI_BtlStdby;
			GameOn = 1;
			break;
		case UI_BtlStdby:
			if(!pl1_go && pl2_go)
			{
				UI_State = UI_WaitScr;	
				mashGun = 0;
				mashKnife = 0;
				sprintf(str,"HP:%d Shoots:%d Stabs:%d",humanHp,mashGun,mashKnife);
				LCD_DisplayString(1,str);
			}
			else if(pl1_go && !pl2_go)
			{
				UI_State = UI_MnAtksMenu;
				sprintf(str,"HP:%d MP:%d ",monHp,monMp);
				strcat(str,"A:mv1 B:mv2");
				LCD_DisplayString(1,str);
			}
			else
			{
				UI_State = UI_BtlStdby;
			}
			break;
		case UI_MnAtksMenu:
			if(pl1_go&&((keyread !='A')&&(keyread !='B')))
			{
				UI_State =UI_MnAtksMenu;
			}
			else if (pl1_go&&(keyread=='A'))
			{
				UI_State = UI_DisplayAtk1;
				busymv2 = 1;
				if(humanHp > 0)
				{
					humanHp = humanHp - stren;
				}
				strcpy(str,mvList[mon_num-1][0]);
				LCD_DisplayString(1,str);
			}
			else if (pl1_go&&(keyread =='B'))
			{
				UI_State = UI_DisplayAtk2;
				busymv1 = 1;
				if(humanHp > 0)
				{
					humanHp = humanHp - stren;
				}
				strcpy(str,mvList[mon_num-1][1]);
				LCD_DisplayString(1,str);
			}
			else if (!pl1_go)
			{
				UI_State = UI_BtlStdby;
			}
			break;
		case UI_DisplayAtk1:
			if(pl1_go)
			{
				UI_State = UI_DisplayAtk1;
			}
			else if(!pl1_go)
			{
				UI_State = UI_ChkHumanHP;
				busymv2 = 0;
			}
			break;
		case UI_DisplayAtk2:
			if(pl1_go)
			{
				UI_State = UI_DisplayAtk2;
			}	
			else if(!pl1_go)
			{
				UI_State = UI_ChkHumanHP;
				busymv1 = 0;
			}
			break;
		case UI_ChkHumanHP:
			if (humanHp >0)
			{
				UI_State = UI_BtlStdby;
			}
			else if (!(humanHp >0))
			{
				UI_State = UI_PL1Won;
				GameOn = 0;
				LCD_DisplayString(1,"Player1: Monster Wins");
			}
			break;
		case UI_PL1Won:
			if(cnt<50)
			{
				UI_State = UI_PL1Won;
			}
			else if (!(cnt<50))
			{
				UI_State = UI_Menu;
				cnt = 0;
				LCD_DisplayString(1,"Main A:Mstrs    B:Bttle  C:Feed");
			}
			break;
		case UI_WaitScr:
			if(pl2_go&&!update_scoreGun&&!update_scoreKnife)
			{
				UI_State = UI_WaitScr;
			}
			else if(pl2_go&&!update_scoreGun&&update_scoreKnife)//update knife stab
			{
				UI_State = UI_DispScrKnf;
				mashGun = btnCntGun;
				mashKnife = btnCntKnife;
				sprintf(str,"HP:%d Shoots:%d Stabs:%d",humanHp,mashGun,mashKnife);
				LCD_DisplayString(1,str);			
			}
			else if(pl2_go&&update_scoreGun&&!update_scoreKnife)//update gunshoot
			{
				UI_State = UI_DispScrGun;
				mashGun = btnCntGun;
				mashKnife = btnCntKnife;
				sprintf(str,"HP:%d Shoots:%d Stabs:%d",humanHp,mashGun,mashKnife);
				LCD_DisplayString(1,str);
			}
			else if(!pl2_go)
			{
				UI_State = UI_DmgPL1;
				if(monHp >0)
				{
					monHp = monHp - H_GetMLdmg(mashKnife,Defen)-H_GetLRdmg(mashGun,Defen);
				}
			}
			break;
		case UI_DispScrKnf:
			if(pl2_go)
			{
				UI_State = UI_WaitScr;	
			}
			else if(!pl2_go)
			{
				UI_State = UI_DmgPL1;
				if(monHp >0)
				{
					monHp = monHp - H_GetMLdmg(mashKnife,Defen)-H_GetLRdmg(mashGun,Defen);
				}
			}
			break;
		case UI_DispScrGun:
			if(pl2_go)
			{
				UI_State = UI_WaitScr;
			}
			else if (!pl2_go)
			{
				UI_State = UI_DmgPL1;
				if(monHp >0)
				{
					monHp = monHp - H_GetMLdmg(mashKnife,Defen)-H_GetLRdmg(mashGun,Defen);
				}	
			}
			break;
		case UI_DmgPL1:
			if(monHp  > 0)
			{
				UI_State = UI_BtlStdby;
			}	
			else if (!(monHp >0))
			{
				UI_State = UI_PL2Won;
				GameOn = 0;
				LCD_DisplayString(1,"Player2: Human Won");
			}
			break;
		case UI_PL2Won:
			if(cnt < 50)
			{
				UI_State = UI_PL2Won;	
			}
			else if(!(cnt<50))
			{
				UI_State = UI_Menu;
				LCD_DisplayString(1,"Main A:Mstrs    B:Bttle  C:Feed");	
				cnt = 0;
			}			
			break;		
//feed menu
		case UI_Feed:
			if(!key)
			{
				UI_State = UI_Feed;
			}
			else if(key == '3')
			{
				UI_State = UI_Menu;
				LCD_DisplayString(1,"Main A:Mstrs    B:Bttle  C:Feed");				
			}
			break;
		default:
			UI_State = UI_initial;
	}
	switch(UI_State)
	{
		case UI_initial:
			LCD_ClearScreen();
			go_write = 0;			
			display_rg  = 0;
			display_og = 0;
			cnt=0;
			k=0;
			break;
		case UI_intr:		
			break;
		case UI_Menu:					
			break;
		case UI_MtrMenu:
			slot_pick = 0;
			break;
		case UI_NewMon:
			slot_pick = 0;
			break;
		case UI_nmSlot:
			display_rg = 0;
			display_og = 0;
			cnt++;			
			break;
		case UI_nmDispStat:
			if(mon_pick == '1')
			{
				display_rg = 1;
				display_og = 0;
			}
			else if(mon_pick == '2')
			{
				display_rg = 0;
				display_og = 1;
			}			
			cnt++;
			break;
		case UI_nmSetData:
			if(mon_pick == '1')
			{
				data = RG_default;
			}
			else if (mon_pick == '2')
			{
				data = OG_default;
			}
			break;
		case UI_nmWrite:
			break;
		case UI_nmSaved:
			cnt++;
			break;
		case UI_MtrStrge:
			display_og = 0;
			display_rg = 0;
			break;
		case UI_readSlot:
			if(slot_pick == 'A')
			{
				eeprom_read_block(&slotReadRam,&SlotA_mem,sizeof(MnStats));
				if(slotReadRam.MnNum == 0)
				{
					strcpy(str,"empty...#:back");
					LCD_DisplayString(1,str);
				}
				else
				{
					str_tmp = concatStat(slotReadRam);
					strcpy(str,str_tmp);
					strcat(str," press '#' to go back");
					LCD_DisplayString(1,str);
				}
			}
			else if(slot_pick == 'B')
			{
				eeprom_read_block(&slotReadRam,&SlotB_mem,sizeof(MnStats));
				if(slotReadRam.MnNum == 0)
				{
					strcpy(str,"empty...#:back");					
					LCD_DisplayString(1,str);
				}
				else
				{
					str_tmp = concatStat(slotReadRam);
					strcpy(str,str_tmp);
					strcat(str," press '#' to go back");
					LCD_DisplayString(1,str);
				}
			}
			else if (slot_pick == 'C')
			{
				eeprom_read_block(&slotReadRam,&SlotC_mem,sizeof(MnStats));
				if(slotReadRam.MnNum == 0)
				{
					strcpy(str,"empty...#:back");
					LCD_DisplayString(1,str);
				}
				else
				{
					str_tmp = concatStat(slotReadRam);
					strcpy(str,str_tmp);
					strcat(str," press '#' to go back");
					LCD_DisplayString(1,str);
				}
			}		
			break;
		case UI_dispMnStrge:
			if(slotReadRam.MnNum == 1)
			{
				display_rg = 1;
				display_og = 0;
			}
			if(slotReadRam.MnNum == 2)
			{
				display_rg = 0;
				display_og = 1;				
			}
			cnt++;
			break;
//battle menu			
		case UI_BttlMenu:
			break;
		case UI_BtlmChseMn:
			slot_pick = 0;
			display_og = 0;
			display_rg = 0;
			break;
		case UI_btlreadSlot:
			if (slot_pick == 'A')
			{
				eeprom_read_block(&slotReadRam,&SlotA_mem,sizeof(MnStats));
			}
			else if (slot_pick == 'B')
			{
				eeprom_read_block(&slotReadRam,&SlotB_mem,sizeof(MnStats));				
			}
			else if (slot_pick == 'C')
			{
				eeprom_read_block(&slotReadRam,&SlotC_mem,sizeof(MnStats));
			}
			break;
		case UI_btlChkEmpty:
			break;
		case UI_BtlDispMon:
			if(slotReadRam.MnNum == 1)
			{
				display_rg = 1;
				display_og = 0;
			}
			else if (slotReadRam.MnNum == 2)
			{
				display_rg = 0;
				display_og = 1;				
			}
			cnt++;
			break;
		case UI_BtlSetStats:
			monHp = slotReadRam.Hp;
			monMp = slotReadRam.Mp;
			mon_num = slotReadRam.MnNum;
			stren = slotReadRam.Str;
			Defen = slotReadRam.Def;
			humanHp = 200;
			spd_factor = GetSpdFactor(slotReadRam.Spd); 
			break;
//battle interfacing			
		case UI_GameOn:
			break;
		case UI_BtlStdby:
			LCD_ClearScreen();
			break;
		case UI_MnAtksMenu:
			break;
		case UI_DisplayAtk1:
			break;
		case UI_DisplayAtk2:
			break;
		case UI_ChkHumanHP:
			break;
		case UI_PL1Won:
			cnt++;
			break;
		case UI_WaitScr:
			break;
		case UI_DispScrKnf:
			break;
		case UI_DispScrGun:
			break;
		case UI_DmgPL1:
			if (ammo >0)
			{
				//decrement ammo
			}
			break;
		case UI_PL2Won:
			cnt++;
			break;			
//feed menu			
		case UI_Feed:
			break;			
		default:
			break;		
	}
}




int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xF0; PORTB = 0x0F;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	LCD_init();
	
	LMtrx_State = -1;
	RGLM_State = -1;
	BOG_State= -1;
	UI_State = -1;
	dw_State = -1;
	
	PLT_State = -1;
	GM_State = -1;
	Knf_State =-1;

	SW_State = -1;
	ATK1_State = -1;
	ATK2_State = -1;
	MMV_State =-1;
	
	TimerSet(1);//1ms
	TimerOn();
	unsigned short cnt = 0;
	unsigned short cnt2 = 0;
	unsigned short cnt3 = 0;
	unsigned short cnt4 = 0;
	unsigned short cnt5 = 0;
	unsigned short cnt6 = 0;
	unsigned short cnt8 = 0;
	unsigned short cnt9 = 0;
	unsigned short cnt10 = 0;
	unsigned short cnt11 = 0;
	
    while(1)
    {					
		LMTrx_display();
		if(cnt>= 300)
		{
			RG_LMTick();
			BldOG_LMTick();
			cnt = 0;
		}
		if(cnt2>= 100)
		{
			UsrInterface();
			cnt2 = 0;
		}
		if(cnt3 >= 10)
		{
			DataWrtTck();
			cnt3=0;
		}
		if(cnt4>= 5)
		{
			KnfStabTck();
			cnt4 = 0;
		}
		if(cnt5>= 20)
		{
			GMShoot();
			cnt5 = 0;
		}
		if(cnt6>=10)
		{
			SWTck();
			cnt6 = 0;
		}
		if(cnt8>= 100)
		{
			ATK1Tck();
			cnt8 = 0;
		}
		if(cnt9>= 100)
		{
			ATK2Tck();
			cnt9 = 0;
		}
		if(cnt10>= 1000)
		{
			PlayerTimerTck();
			cnt10 = 0;
		}
		if(cnt11 >= 10)
		{
			MonAtkTck();
			cnt11=0;
		}		
		while(!TimerFlag){}
		TimerFlag = 0;
		cnt++;
		cnt2++;
		cnt3++;
		cnt4++;
		cnt5++;
		cnt6++;		
		cnt8++;
		cnt9++;
		cnt10++;
		cnt11++;		
    }
}
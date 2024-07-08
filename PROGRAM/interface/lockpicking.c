int checkingstagenum = 10;
int pickposition = 90;
int openingcount = 0;
int iBrokePick = 35;
int iBrokePickReducer = 1;

int correctposition;

string wrenchtex, picktex;
string chestID;

bool openingstarted = false;
bool cylinderstarted = false;
bool lockclick = false;
bool g_bToolTipStarted = false;

bool firsttime;
bool opened = false;

bool mousechangepos = true;
string mpos;
string ompos;

void InitInterface_gm(string iniName)
{
	LAi_SetActorTypeNoGroup(pchar);
	locCameraSleep(true);
	SetTimeScale(0.0);

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("eSlideChange","procSlideChange",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	
	if (CheckAttribute(pchar, "questTemp.lockpicking.firsttime"))
	{
		if(makeint(pchar.questTemp.lockpicking.firsttime) == 1) firsttime = true;
		else firsttime = false;
	}
	else
	{
		firsttime = true;
	}
	
	PlaySound("interface\lockpicking\ui_lockpicking_enter_01.wav"); // Звук начала процедуры
	
	if(CheckAttribute(pchar, "questTemp.Lockpicking.ID"))
	{
	    chestID = pchar.questTemp.Lockpicking.ID;
	}
	
	if(CheckCharacterPerk(pchar, "SkilledThief")) iBrokePickReducer = 0.7;
	if(CheckCharacterPerk(pchar, "BreakAndSilence")) iBrokePickReducer = 0.5;
	if(CheckCharacterPerk(pchar, "Lockpicking")) iBrokePickReducer = 0;
	
	iBrokePick = iBrokePick * iBrokePickReducer;
	
	correctposition = 1+rand(179);
	
	if(correctposition < 15) correctposition = 15;
	if(correctposition > 165) correctposition = 165;
	
	if(firsttime == true) CreateTooltip("#" + XI_ConvertString("LockPicking"), XI_ConvertString("lockpicking_descr1"), argb(255,255,255,255), XI_ConvertString("lockpicking_descr2"), argb(255,255,192,192), XI_ConvertString("lockpicking_descr3"), argb(255,255,255,255), "", argb(255,255,255,255), "none", "none", "none", 64, 64);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
    switch(nodName)
	{
		
	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();
}

void IProcessFrame()
{
	int randsound;
	int squeaksound;
	int randclicksound;
	
	int difference;
	float dmultiplier;
	
	float mouseposition;
	int movsound;
	
	if (CheckAttribute(GameInterface,"mousepos")) mouseposition = 600.0 - (stf(GameInterface.mousepos.y));
	
	if(mouseposition > 600) mouseposition = 600;
	if(mouseposition < 9) mouseposition = 9;
	
	pickposition = mouseposition*0.3;
	picktex = "interfaces\LockPicking\pick\" + makeint(pickposition/2) + ".tga";
	SetNewPicture("PICK_PIC",picktex);
	
	if(lockclick == false)
	{
		SetRealMouseSensitivity();
	}
	else
	{
		XI_SetMouseSensitivity(0.0, 0.0);
	}
	
	if(checkingstagenum < 460)
	{
		if(mousechangepos == false)
		{
			mpos = GameInterface.mousepos.y;
			
			if(mpos != ompos)
			{
				if(rand(20) == 0)
				{
					movsound = rand(11)+1;
					
					if(movsound < 10) PlaySound("interface\lockpicking\mov\ui_lockpicking_pickmovement_0"+ movsound +".wav");
					else PlaySound("interface\lockpicking\mov\ui_lockpicking_pickmovement_"+ movsound +".wav");
				}
			}
			
			mousechangepos = true;
		}
		
		if(mousechangepos == true)
		{
			if (CheckAttribute(GameInterface,"mousepos")) ompos = GameInterface.mousepos.y;
			mousechangepos = false;
		}
	}
	
	if(checkingstagenum < 460)
	{
		if((pickposition - correctposition) <= 0) difference = correctposition - pickposition;
		else difference = pickposition - correctposition;
		
		dmultiplier = makefloat(difference)/180.0;
		
		if(XI_IsKeyPressed("control")) // Двигаем цилиндр, если нажата кнопка Ctrl
		{
			checkingstagenum = checkingstagenum + 8;
			
			if(cylinderstarted == false) // Звук начала поворота цилиндра
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = true;
			}
		}
		else // Если кнопка не нажата, то возвращаем в исходное положение
		{
			checkingstagenum = checkingstagenum - 8;
			
			if(cylinderstarted == true) // Звук начала поворота цилиндра
			{
				randsound = rand(7)+1;
				PlaySound("interface\lockpicking\cylturn\ui_lockpicking_cylinderturn_0"+ randsound +".wav");
				cylinderstarted = false;
			}
		}
		
		if(makeint(dmultiplier*100.0) > 2)
		{
			if(checkingstagenum > makeint((1.0 - dmultiplier)*460.0))
			{
				checkingstagenum = makeint((1.0 - dmultiplier)*460.0);
				
				if(lockclick == false)
				{
					lockclick = true;
					
					randclicksound = rand(2)+1;
					PlaySound("interface\lockpicking\cylstop\ui_lockpicking_cylinderstop_0"+ randclicksound +".wav");
					
					if (pickposition > 0)
					{
						if((rand(99) + 1) <= iBrokePick)
						{
							pchar.brokenlockpick = true;
						    ProcessCancelExit();
						}
					}
				}
			}
		}
		
		if(checkingstagenum > 460) checkingstagenum = 460;
		
		if(checkingstagenum < 10)
		{
			checkingstagenum = 10;
			lockclick = false;
		}
		
		if(checkingstagenum == 460) OpenProcedure(); // Если цилиндр повернут на 90 градусов, то запускаем процесс открытия
		
		if(checkingstagenum != 10 && checkingstagenum != 460 && checkingstagenum != makeint((1.0 - dmultiplier)*460.0)) // Поскрипывания цилиндра при его движении
		{
			if(rand(160) == 0)
			{
				squeaksound = rand(11)+1;
				
				if(squeaksound < 10) PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_0"+ squeaksound +".wav");
				else PlaySound("interface\lockpicking\cylsqueak\ui_lockpicking_cylindersqueak_"+ squeaksound +".wav");
			}
		}
		
		// Меняем визуальное положение цилиндра
		wrenchtex = "interfaces\LockPicking\wrench\" + makeint(checkingstagenum/10) + ".tga";
		SetNewPicture("WRENCH_PIC",wrenchtex);
	}
	
	if(openingstarted == true)
	{
		openingcount = openingcount + 1;
		
		if(openingcount > 200)
		{
			openingstarted = false;
			opened = true;
			
			SetNodeUsing("BACK_PIC",false);
			SetNodeUsing("LOCK_PIC",false);
			SetNodeUsing("WRENCH_PIC",false);
			SetNodeUsing("PICK_PIC",false);
			SetNodeUsing("PICKSLIDE",false);
			
			if(CheckAttribute(pchar, "Boxname")) OpenLocationChest();
			else OpenChest();
		}
	}
}

void OpenProcedure() // Процесс открытия
{
	int randsound = rand(2)+1;
	
	openingstarted = true;
	PlaySound("interface\lockpicking\ui_lockpicking_unlock_0"+ randsound +".wav"); // Звук щелчка замка
}

void OpenLocationChest()
{
	DeleteAttribute(pchar, "lockpicking");
	IDoExit(RC_INTERFACE_LOCKPICKED_LOCATION, true);
}

void OpenChest()
{
	string nameitm[10];
	int itmq[10];
	
	for (i = 0; i < 10; i++)
	{
		nameitm[i] = "";
	}
	
	if(chestID == "Chest_Closed")
	{
		TakeItemFromCharacter(pchar, chestID);
		
		if(drand(1) == 0) // чтобы не сливали
		{
			nameitm[0] = "gold";
			itmq[0] = 8000 + drand(5)*1000;
		}
		else
		{
			nameitm[0] = "gold";
			itmq[0] = 3000 + drand(4)*1000;
			
			if(rand(2) == 0)
			{
				nameitm[1] = "jewelry2";
				itmq[1] = 1 + rand(9);
			}
			
			if(rand(2) == 0)
			{
				nameitm[2] = "jewelry3";
				itmq[2] = 1 + rand(2);
			}
			
			if(rand(2) == 0)
			{
				if(rand(1) == 0)
				{
					nameitm[3] = "jewelry5";
					itmq[3] = 1 + rand(7);
				}
				else
				{
					nameitm[3] = "jewelry6";
					itmq[3] = 1 + rand(5);
				}
			}
			
			if(rand(2) == 0)
			{
				if(rand(1) == 0)
				{
					if(rand(1) == 0)
					{
						nameitm[4] = "jewelry4";
						itmq[4] = 1 + rand(4);
					}
					else
					{
						nameitm[4] = "jewelry5";
						itmq[4] = 1 + rand(6);
					}
				}
				else
				{
					nameitm[4] = "jewelry6";
					itmq[4] = 1 + rand(40);
				}
			}
		}
	}
	
	DeleteAttribute(pchar, "lockpicking");
	pchar.lockpicking.money = 0;
	pchar.lockpicking.items = "";
	for (i = 0; i < 10; i++)
	{
		string name = nameitm[i];
		int qty = itmq[i];
		if (name == "") {
			continue;
		}
		if (name == "gold")
		{
			pchar.lockpicking.money = qty;
		}
		else
		{
			pchar.lockpicking.items.(name) = qty;
		}
	}
	
	pchar.InLockpickedChest = true;
	
	IDoExit(RC_INTERFACE_LOCKPICKED, true);
}

void ShowInfo()
{
	if(firsttime == false && opened == false)
	{
		g_bToolTipStarted = true;
		string sHeader = "TEST";
		string sNode = GetCurrentNode();

		string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
		sPicture = "none";
		sGroup = "none";
		sGroupPicture = "none";

		switch (sNode)
		{
			case "BACK_PIC":
				sHeader = XI_ConvertString("LockPicking");
				sText1 = XI_ConvertString("lockpicking_descr1");
				sText2 = XI_ConvertString("lockpicking_descr2");
				sText3 = XI_ConvertString("lockpicking_descr3");
			break;
		}

		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfo()
{
	if(firsttime == false && opened == false)
	{
		if( g_bToolTipStarted ) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("PICKSLIDE");
		}
	}
}

void ProcessCancelExit()
{
	if(openingstarted == false)
	{
		if(firsttime == false || opened == true)
		{
			CloseTooltip();
			IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
		}
		else
		{
			firsttime = false;
			pchar.questTemp.lockpicking.firsttime = false;
			CloseTooltip();
			SetCurrentNode("PICKSLIDE");
		}
	}	
}

void IDoExit(int exitCode, bool bClear)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("eSlideChange","procSlideChange");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");

	LAi_SetPlayerType(pchar);
	SetRealMouseSensitivity();

	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);

	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DeleteAttribute(pchar, "pause");
	DelPerkFromActiveList("TimeSpeed");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME )
	{
		DeleteEntitiesByType("scrshoter");
	}
	
	if(CheckAttribute(pchar, "brokenlockpick"))
	{
		DeleteAttribute(pchar, "brokenlockpick");
		TakeItemFromCharacter(pchar, "Lockpick");
	}
	
	EndCancelInterface(bClear);
}
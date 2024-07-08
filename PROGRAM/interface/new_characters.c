string sCurChangeOfficer = "";	// название должности, назначение на которую сейчас открыто (абордажники сразу с индексом)
int iCurChangeOfficer = -1;		// индекс персонажа, назначенного на должность, которая сейчас открыта
int iCurPassenger = -1;			// индекс пассажира, окно которого сейчас открыто
ref rCurPassenger;				// пассажир, окно которого сейчас открыто
bool isActiveChangeOfficers = false;	// открыто ли окно назначения офицера
bool isActiveClassPanel = false;		// открыта ли панель класса ГГ
bool canMove = true;					// можно ли двигать ноды (нельзя, пока происходит движение)
int nCurScrollOfficerNum;		// номер выбранного персонажа в скролле назначения на должность
bool isOffPanelEmpty = false;	// пуст ли скролл назначения на должность
string sCurAppointMode = "";	// текущий режим для кнопки "назначить"/"сместить"
int iCurItem = -1;	// индекс предмета, который выделен в окне пассажира
string curSort = "all";
string curWindow = "main";	// активное окно
int iCurTextFrameIndex = -1;
bool bUpdateTextFrame = true;
int idLngFile;
float fOffsetX, fOffsetY;



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ИНИЦИАЛИЗАЦИЯ
////////////////////////////////////////////////////////////////////////////

void InitInterface(string iniName)	// основной инит
{
	InterfaceStack.SelectMenu_node = "LaunchMainCharacter";
	GameInterface.title = "titleCharacter";
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	XI_RegistryExitKey("IExit_F2");
	XI_RegistryExitKey("IExit_Escape");
	
	GetXYWindowOffset(&fOffsetX, &fOffsetY);
	
	StartSetEventHandlers();
	StartSetTitles();
	StartSetMoveList();
	StartSetPositions();
	StartHideNodes();
	StartFillNodes();
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
}

void StartSetEventHandlers()	// выставление эвентов
{
	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
//	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
//	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("ShowChangeOfficers","ShowChangeOfficers",0);
//	SetEventHandler("ExitChangeOfficers","ExitChangeOfficers",0);
	SetEventHandler("ShowClassPanel","ShowClassPanel",0);
	SetEventHandler("HideClassPanel","HideClassPanel",0);
	SetEventHandler("MoveFinished","MoveFinished",0);
	SetEventHandler("ExitPassWindow","ExitPassWindow",0);
	SetEventHandler("HideOffPanel","HideOffPanel",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("UpdateTextFrame", "UpdateTextFrame", 0);
	SetEventHandler("SetBlinking", "SetBlinking", 0);
//	SetEventHandler("eTabControlPress","procTabChange",0);
}

void StartFillNodes()	// стартовое заполнение листов и баров
{
	FillCharacterBars(pchar);
	FillOfficersList();
	FillPassengersList();
}

void StartSetMoveList()	// заполнение мувлиста
{
	// характеристики ГГ - индекс 1
	AddNodeToMoveList(1,"ADDPANEL_LEFT_CHAIN",-78,-515,-56,-409);
	AddNodeToMoveList(1,"ADDPANEL_RIGHT_CHAIN",112,-517,134,-411);
	AddNodeToMoveList(1,"ADDPANEL_BACK",-85,-416,140,-40);
	AddNodeToMoveList(1,"ADDPANEL_FRAME",-92,-423,146,-29);
	AddNodeToMoveList(1,"ADDPANEL_EXIT",105,-415,137,-383);
	AddNodeToMoveList(1,"HERO_CLASS_HEADER",4,-396,57,-371);
	AddNodeToMoveList(1,"HERO_CLASS_ICON",-61,-373,33,-279);
	AddNodeToMoveList(1,"HERO_CLASS_NAME",37,-338,116,-313);
	AddNodeToMoveList(1,"HERO_TABLE_PIRATES",-63,-268,119,-208);
	AddNodeToMoveList(1,"HERO_TALENTS_HEADER",-8,-186,60,-161);
	AddNodeToMoveList(1,"HERO_TALENT1",-57,-155,23,-75);
	AddNodeToMoveList(1,"HERO_TALENT2",30,-155,110,-75);
	
	// назначение офицера - индекс 2
	AddNodeToMoveList(2,"OFFPANEL_LEFT_CHAIN",224,-515,246,-409);
	AddNodeToMoveList(2,"OFFPANEL_RIGHT_CHAIN",778,-517,800,-411);
	AddNodeToMoveList(2,"OFFPANEL_BACK",202,-416,826,-40);
	AddNodeToMoveList(2,"OFFPANEL_FRAME",193,-423,835,-29);
	AddNodeToMoveList(2,"OFFPANEL_EXIT",739,-400,779,-360);
	AddNodeToMoveList(2,"OFFPANEL_SCROLL",253,-343,773,-243);
	AddNodeToMoveList(2,"OFFPANEL_LEFTBUTTON",217,-312,249,-280);
	AddNodeToMoveList(2,"OFFPANEL_RIGHTBUTTON",779,-312,811,-280);
	AddNodeToMoveList(2,"OFFPANEL_BIGFRAME",456,-351,570,-222);
	AddNodeToMoveList(2,"OFFPANEL_MORE",257,-392,357,-360);
	AddNodeToMoveList(2,"OFFPANEL_TITLE",340,-391,690,-358);
	AddNodeToMoveList(2,"OFFPANEL_LEFTSTICK",209,-229,409,-199);
	AddNodeToMoveList(2,"OFFPANEL_RIGHTSTICK",819,-229,619,-199);
	AddNodeToMoveList(2,"OFFPANEL_RANK",501,-247,528,-227);
	AddNodeToMoveList(2,"OFFPANEL_NAME",407,-221,624,-201);	
	AddNodeToMoveList(2,"OFFPANEL_TABLE_LAND",224,-193,416,-73); 
	AddNodeToMoveList(2,"OFFPANEL_HP_BACK",442,-191,582,-163);
	AddNodeToMoveList(2,"OFFPANEL_HP",450,-191,574,-163);
	AddNodeToMoveList(2,"OFFPANEL_HP_TEXT",459,-184,568,-164);
	AddNodeToMoveList(2,"OFFPANEL_ENERGY_BACK",442,-151,582,-123);
	AddNodeToMoveList(2,"OFFPANEL_ENERGY",450,-151,574,-123);
	AddNodeToMoveList(2,"OFFPANEL_ENERGY_TEXT",459,-144,568,-124);
	AddNodeToMoveList(2,"OFFPANEL_APPOINT",460,-107,560,-75);
	AddNodeToMoveList(2,"OFFPANEL_PERKS_FENCING_BACK",618,-200,698,-120);
	AddNodeToMoveList(2,"OFFPANEL_PERKS_PISTOL_BACK",665,-138,745,-58);
	AddNodeToMoveList(2,"OFFPANEL_PERKS_ATHLETICS_BACK",713,-200,793,-120);
	AddNodeToMoveList(2,"OFFPANEL_PERKS_FENCING",637,-182,679,-140);
	AddNodeToMoveList(2,"OFFPANEL_PERKS_PISTOL",683,-118,725,-76);
	AddNodeToMoveList(2,"OFFPANEL_PERKS_ATHLETICS",728,-183,776,-135);
}

void StartSetPositions()
{
	SetNodePos("PASS_BLADE", 548,87,610,149);
	SetNodePos("PASS_PISTOL", 612,87,674,149);
	SetNodePos("PASS_CUIRASS", 676,87,738,149);
	SetNodePos("PASS_TALISMAN", 740,87,802,149);
}

void StartSetTitles()	// заполнение заголовков
{
	SetFormatedText("TITLE_HERONAME", GetFullName(pchar));
	SetFormatedText("TITLE_MAINSKILLS", "Умения");
	SetFormatedText("TITLE_PASSENGERS", "Пассажиры");
	SetFormatedText("TITLE_OFFICERS", "Офицеры");
	
	SetFormatedText("TITLE_HERONAME_FALSE", GetFullName(pchar));
	SetFormatedText("TITLE_MAINSKILLS_FALSE", "Умения");
	SetFormatedText("TITLE_PASSENGERS_FALSE", "Пассажиры");
	SetFormatedText("TITLE_OFFICERS_FALSE", "Офицеры");
	
	SetFormatedText("PASS_TITLE_SELFSKILL", "Личные умения");
	SetFormatedText("PASS_TITLE_SHIPSKILL", "Корабельные умения");
	SetFormatedText("PASS_TITLE_EQUIP", "Экипировка");
	SetFormatedText("PASS_TITLE_INVENTORY", "Инвентарь");
	SetFormatedText("HERO_CLASS_HEADER", "Класс");
	SetFormatedText("HERO_TALENTS_HEADER", "Таланты");
	SetFormatedText("HERO_CLASS_NAME", "");
	
	SetFormatedText("TEXT_NOPASSENGERS", "Список"+newStr()+"пассажиров"+newStr()+"пуст");
}

void StartHideNodes()	// стартовое выключение лишнего
{
	SetNodeUsing("BLIND_CHANGEOFFICERS", false);
	SetNodeUsing("TABLE_OFFICERS", false);
	SetNodeUsing("SCROLL_OFFICERS", false);
	SetNodeUsing("CHANGEOFFICERS_EXIT", false);
	SetNodeUsing("TITLE_HERONAME_FALSE", false);
	SetNodeUsing("OFFPANEL_TABLE_SHIP", false);
	SetNodeUsing("TEXT_NOPASSENGERS", false);
	
	HideTextFrame();
}

void ProcessExitCancel()	// основной выход
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)	// выход
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
//    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
//	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("ShowClassPanel","ShowClassPanel");
	DelEventHandler("HideClassPanel","HideClassPanel");
	DelEventHandler("ShowChangeOfficers","ShowChangeOfficers");
//	DelEventHandler("ExitChangeOfficers","ExitChangeOfficers");
	DelEventHandler("MoveFinished","MoveFinished");
	ClearMoveList(1);
	ClearMoveList(2);

	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
//	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ExitPassWindow","ExitPassWindow");
	DelEventHandler("HideOffPanel","HideOffPanel");
	
	DelEventHandler("UpdateTextFrame", "UpdateTextFrame");
	DelEventHandler("SetBlinking", "SetBlinking");
	
	LanguageCloseFile(idLngFile);
	
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ОСНОВНАЯ ОБРАБОТКА
////////////////////////////////////////////////////////////////////////////

void ProcessCommandExecute()	// считывание команд
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "OFFPANEL_APPOINT":
			if(comName=="click")
			{
				switch(sCurAppointMode)
				{
					case "add":		AppointOfficer();	break;
					case "remove":	RemoveOfficer();	break;
				}
				return;
			}
		break;
		case "OFFPANEL_MORE":
			if(comName=="click")
			{
				if(iCurPassenger != -1)
					ShowPassengerWindow();
				return;
			}
		break;
		case "PASS_BUTTON_EQUIP":
			if(comName == "click")
			{
				PressEquipItem();
				return;
			}
		break;
		case "PASS_BUTTON_REMOVE":
			if(comName == "click")
			{
				PressRemoveItem();
				return;
			}
		break;
		case "PASS_BUTTON_USE":
			if(comName == "click")
			{
				PressUseItem();
				return;
			}
		break;
		case "PASS_SORT_1":
			if(comName=="click")
			{
				FilterPassItems("All");
				return;
			}
		break;
		case "PASS_SORT_2":
			if(comName=="click")
			{
				FilterPassItems("Gear");
				return;
			}
		break;
		case "PASS_SORT_3":
			if(comName=="click")
			{
				FilterPassItems("Potion");
				return;
			}
		break;
		case "PASS_SORT_4":
			if(comName=="click")
			{
				FilterPassItems("Ingredients");
				return;
			}
		break;
		case "PASS_SORT_5":
			if(comName=="click")
			{
				FilterPassItems("Other");
				return;
			}
		break;
        case "TITLE_INVENTORY":
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", "I_ITEMS", 2);
				return;
			}
		break;
		case "TITLE_SHIPS":
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", "I_SHIP", 2);
				return;
			}
		break;
		case "TITLE_JOURNAL":
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", "I_QUESTBOOK", 2);
				return;
			}
		break;
		case "TABLE_PASSENGERS":
			if(comName=="click" && !isActiveChangeOfficers)
				ShowPassengerWindow();
		break;	
	}
}

void ProcessFrame()	// ежефреймовая обработка
{
	CheckMousePosition();
	if(CheckAttribute(&GameInterface, "OFFPANEL_SCROLL") && sti(GameInterface.OFFPANEL_SCROLL.current) != nCurScrollOfficerNum && GetCurrentNode() == "OFFPANEL_SCROLL")
	{
		nCurScrollOfficerNum = sti(GameInterface.OFFPANEL_SCROLL.current);
		SetChangeOfficerInfo();
		return;
	}
}

void CS_TableSelectChange()	// обработка выбора ячейки в таблице
{
	string sControl = GetEventData();
	int rSelected = GetEventData();
	int cSelected = GetEventData();
    string CurTable = sControl;
    string CurRow = "tr" + (rSelected);
	string CurCol = "td" + (cSelected);
	switch(CurTable)
	{
		case "TABLE_PASSENGERS":
			if(CheckAttribute(&GameInterface,"TABLE_PASSENGERS."+CurRow+".UserData.index"))
			{
				iCurPassenger = sti(GameInterface.TABLE_PASSENGERS.(CurRow).UserData.index);
			}
		break;
		
		case "PASS_TABLE_ITEMS":
			if(CheckAttribute(&GameInterface,"PASS_TABLE_ITEMS."+CurRow+"."+CurCol+".index"))
			{
				iCurItem = sti(GameInterface.PASS_TABLE_ITEMS.(CurRow).(CurCol).index);
				CheckPassButtons();
			}
			else
			{
				SetNodeUsing("PASS_BUTTON_EQUIP", false);
				SetNodeUsing("PASS_BUTTON_REMOVE", false);			
				SetNodeUsing("PASS_BUTTON_USE", false);
				iCurItem = -1;
			}
		break;
	}
}

void MoveFinished()	// обработка конца движения группы нод
{
	int mIdx = GetEventData();
	string tag = GetEventData();
	switch(mIdx)
	{
		case 1:
			if(tag == "close")
			{
				isActiveClassPanel = false;
				SetNodeUsing("TITLE_HERONAME", true);
				SetNodeUsing("TITLE_HERONAME_FALSE", false);
			}
			if(tag == "open")
			{
				isActiveClassPanel = true;
			}
		break;
		
		case 2:	// назначение офицеров новое
			if(tag == "close")
			{
				isActiveChangeOfficers = false;
				iCurChangeOfficer = -1;
				sCurChangeOfficer = "";
				SetNodeUsing("TITLE_MAINSKILLS", true);
				SetNodeUsing("TITLE_MAINSKILLS_FALSE", false);
				SetNodeUsing("TITLE_PASSENGERS", true);
				SetNodeUsing("TITLE_PASSENGERS_FALSE", false);
				SetNodeUsing("TITLE_OFFICERS", true);
				SetNodeUsing("TITLE_OFFICERS_FALSE", false);
			}
			if(tag == "open")
			{
				isActiveChangeOfficers = true;
				if(!isOffPanelEmpty)
				{
					SetNodeUsing("OFFPANEL_APPOINT", true);
					SetNodeUsing("OFFPANEL_MORE", true);
				}
			}
		break;
	}
	canMove = true;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ОСНОВНОЙ ЭКРАН
////////////////////////////////////////////////////////////////////////////

void FillCharacterTables(ref chr)	// таблица навыков ГГ
{
	string sChar, sSkill, sRow, sNode;
	int i, n, iCur, iMax;
	if(IsMainCharacter(chr))
	{
		n = 6;
		sChar = "HERO";
	}
	else
	{
		n = 3;
		sChar = "PASS";
	}
	for(i=1; i<=n; i++)
	{
		switch(i)
		{
			case 1:		sSkill = "fencing";			break;
			case 2:		sSkill = "athletics";		break;
			case 3:		sSkill = "pistol";			break;
			case 4:		sSkill = "sneak";			break;
			case 5:		sSkill = "speechcraft";		break;
			case 6:		sSkill = "alchemy";			break;
		}
		sNode = sChar + "_TABLE_SELFSKILL";
		sRow = "tr"+i;

		GameInterface.(sNode).(sRow).td1.icon.group = "CHARACTER_SKILLS";
		GameInterface.(sNode).(sRow).td1.icon.image = sSkill;
		GameInterface.(sNode).(sRow).td1.icon.width = 42;
		GameInterface.(sNode).(sRow).td1.icon.height = 42;
		GameInterface.(sNode).(sRow).td1.icon.offset = "0, 0";
			
		GameInterface.(sNode).(sRow).td2.align = "center";
		GameInterface.(sNode).(sRow).td2.valign = "center";
		GameInterface.(sNode).(sRow).td2.scale = 1.0;
		GameInterface.(sNode).(sRow).td2.textoffset = "0,0";
		GameInterface.(sNode).(sRow).td2.str = XI_ConvertString("skill "+sSkill);
		
		GameInterface.(sNode).(sRow).td3.align = "center";
		GameInterface.(sNode).(sRow).td3.valign = "center";
		GameInterface.(sNode).(sRow).td3.scale = 1.5;
		GameInterface.(sNode).(sRow).td3.textoffset = "0,0";
		GameInterface.(sNode).(sRow).td3.str = rand(99)+1;
	}
	for(i=1; i<=5; i++)
	{
		switch(i)
		{
			case 1:		sSkill = "navigation";			break;
			case 2:		sSkill = "grappling";			break;
			case 3:		sSkill = "cannons";				break;
			case 4:		sSkill = "defence";				break;
			case 5:		sSkill = "repair";				break;
		}
		sNode = sChar + "_TABLE_SHIPSKILL";
		sRow = "tr"+i;
	
		GameInterface.(sNode).(sRow).td1.icon.group = "CHARACTER_SKILLS";
		GameInterface.(sNode).(sRow).td1.icon.image = sSkill;
		GameInterface.(sNode).(sRow).td1.icon.width = 42;
		GameInterface.(sNode).(sRow).td1.icon.height = 42;
		GameInterface.(sNode).(sRow).td1.icon.offset = "0, 0";
		
		GameInterface.(sNode).(sRow).td2.align = "center";
		GameInterface.(sNode).(sRow).td2.valign = "center";
		GameInterface.(sNode).(sRow).td2.scale = 1.0;
		GameInterface.(sNode).(sRow).td2.textoffset = "0,0";
		GameInterface.(sNode).(sRow).td2.str = XI_ConvertString("skill "+sSkill);
	
		GameInterface.(sNode).(sRow).td3.align = "center";
		GameInterface.(sNode).(sRow).td3.valign = "center";
		GameInterface.(sNode).(sRow).td3.scale = 1.5;
		GameInterface.(sNode).(sRow).td3.textoffset = "0,0";
		GameInterface.(sNode).(sRow).td3.str = rand(99)+1;
	}
	Table_UpdateWindow(sChar+"_TABLE_SELFSKILL");
	Table_UpdateWindow(sChar+"_TABLE_SHIPSKILL");
	
	if(!CheckAttribute(chr, "sea_spec"))
		chr.sea_spec = LinkRandPhrase("navigator", "boatswain", LinkRandPhrase("cannoner", "doctor", "carpenter"));
	sNode = sChar+"_TABLE_SPECIAL";
	GameInterface.(sNode).tr1.td1.str = "Специализация";
	GameInterface.(sNode).tr1.td1.scale = 1.0;
	GameInterface.(sNode).tr2.td1.str = XI_ConvertString(chr.sea_spec);
	GameInterface.(sNode).tr2.td1.color = argb(255,225,165,0);
	Table_UpdateWindow(sNode);
}

void FillCharacterBars(ref chr)	// бары персонажа (ГГ или пассажир в окне)
{
	chr.Health.HP = rand(60);
	chr.reputation = rand(89)+1;
	string _type = "PASS_";
	string sNode;
	if(IsMainCharacter(chr))
	{
		_type = "HERO_";
		SetFormatedText("GOLD_BAR_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
		SetFormatedText("WEIGHT_BAR_TEXT", FloatToString(GetItemsWeight(pchar), 1) + " / "+sti(GetMaxItemsWeight(pchar)));
		GameInterface.StatusLine.LEVEL_BAR.Max = GetCharacterRankRate(pchar);
		GameInterface.StatusLine.LEVEL_BAR.Min = 0;
		GameInterface.StatusLine.LEVEL_BAR.Value = GetCharacterRankRateCur(pchar);
		SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "LEVEL_BAR", 0);
		SetFormatedText("LEVEL_TEXT", pchar.rank);
	}
	else
	{
		chr.loyality = rand(35);
		GameInterface.StatusLine.PASS_LOYALITY.Max   = MAX_LOYALITY;
		GameInterface.StatusLine.PASS_LOYALITY.Min   = 0;
		GameInterface.StatusLine.PASS_LOYALITY.Value = GetCharacterLoyality(chr);
		SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "PASS_LOYALITY", 0);
		GameInterface.StatusLine.PASS_EXP.Max = GetCharacterRankRate(chr);
		GameInterface.StatusLine.PASS_EXP.Min = 0;
		GameInterface.StatusLine.PASS_EXP.Value = rand(GetCharacterRankRate(chr));//GetCharacterRankRateCur(chr);
		SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "PASS_EXP", 0);
		SetFormatedText("PASS_RANK", chr.rank);
		SetFormatedText("PASS_WEIGHT_TEXT", FloatToString(GetItemsWeight(chr), 1) + "/"+sti(GetMaxItemsWeight(chr)));
	}
	
	sNode = _type + "HEALTH";
	GameInterface.StatusLine.(sNode).Max   = 60;
	GameInterface.StatusLine.(sNode).Min   = 0;
	GameInterface.StatusLine.(sNode).Value = makeint(chr.Health.HP);
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, sNode, 0);
	sNode = _type + "HEALTH_TEXT";
	SetFormatedText(sNode, UpperFirst(GetStrSmallRegister(GetHealthName(chr))));
//	float offsetX, offsetY;
//	GetXYWindowOffset(&offsetX, &offsetY);
//	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"TEST", -1, 4, makeint(-59+offsetX),442,-59 + makeint(172*makeint(chr.Health.HP)/60 + offsetX),470);
	
	sNode = _type + "HP";
	GameInterface.StatusLine.(sNode).Max   = MakeInt(LAi_GetCharacterMaxHP(chr));
	GameInterface.StatusLine.(sNode).Min   = 0;
	GameInterface.StatusLine.(sNode).Value = MakeInt(LAi_GetCharacterHP(chr))
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, sNode, 0);
	sNode = _type + "HP_TEXT";
	SetFormatedText(sNode, MakeInt(LAi_GetCharacterHP(chr)) + "/" + MakeInt(LAi_GetCharacterMaxHP(chr)));
	
	sNode = _type + "ENERGY";
	GameInterface.StatusLine.(sNode).Max   = LAi_GetCharacterMaxEnergy(chr);
	GameInterface.StatusLine.(sNode).Min   = 0;
	GameInterface.StatusLine.(sNode).Value = makeint(Lai_CharacterGetEnergy(chr)));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, sNode, 0);
	sNode = _type + "ENERGY_TEXT";
	SetFormatedText(sNode, sti(Lai_CharacterGetEnergy(chr)) + "/" + sti(LAi_GetCharacterMaxEnergy(chr)));
	
	if(sti(chr.reputation) >= 41 && sti(chr.reputation) < 51)
	{
		SetNodeUsing(_type + "REPUTATION_GOOD_LEFT", false);
		SetNodeUsing(_type + "REPUTATION_GOOD_RIGHT", false);
		SetNodeUsing(_type + "REPUTATION_BAD_LEFT", false);
		SetNodeUsing(_type + "REPUTATION_BAD_RIGHT", false);
		SetNodeUsing(_type + "REPUTATION_NEUTRAL", true);
	}
	else
	{
		SetNodeUsing(_type + "REPUTATION_NEUTRAL", false);
		if(sti(chr.reputation) > REPUTATION_NEUTRAL)
		{
			sNode = _type + "REPUTATION_GOOD_LEFT";
			GameInterface.StatusLine.(sNode).Max   = REPUTATION_MAX;
			GameInterface.StatusLine.(sNode).Min   = 50;
			GameInterface.StatusLine.(sNode).Value = sti(chr.reputation);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNode,0);
			SetNodeUsing(sNode, true);
			sNode = _type + "REPUTATION_GOOD_RIGHT";
			GameInterface.StatusLine.(sNode).Max   = REPUTATION_MAX;
			GameInterface.StatusLine.(sNode).Min   = 50;
			GameInterface.StatusLine.(sNode).Value = sti(chr.reputation);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNode,0);
			SetNodeUsing(sNode, true);
			SetNodeUsing(_type + "REPUTATION_BAD_LEFT", false);
			SetNodeUsing(_type + "REPUTATION_BAD_RIGHT", false);
		}
		else
		{
			sNode = _type + "REPUTATION_BAD_LEFT";
			GameInterface.StatusLine.(sNode).Max   = REPUTATION_MAX - REPUTATION_MIN;
			GameInterface.StatusLine.(sNode).Min   = 41;
			GameInterface.StatusLine.(sNode).Value = REPUTATION_MAX - sti(chr.reputation);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNode,0);
			SetNodeUsing(sNode, true);
			sNode = _type + "REPUTATION_BAD_RIGHT";
			GameInterface.StatusLine.(sNode).Max   = REPUTATION_MAX - REPUTATION_MIN;
			GameInterface.StatusLine.(sNode).Min   = 41;
			GameInterface.StatusLine.(sNode).Value = REPUTATION_MAX - sti(chr.reputation);
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,sNode,0);
			SetNodeUsing(sNode, true);
			SetNodeUsing(_type + "REPUTATION_GOOD_LEFT", false);
			SetNodeUsing(_type + "REPUTATION_GOOD_RIGHT", false);
		}
	}
	SetFormatedText(_type + "REPUTATION_TEXT", XI_ConvertString(GetReputationName(sti(chr.reputation))));
	if(!CheckAttribute(chr, "perks.FreePoints_self"))
		chr.perks.FreePoints_self = 0;
	if(!CheckAttribute(chr, "perks.FreePoints_ship"))
		chr.perks.FreePoints_ship = 0;
	SetFormatedText(_type + "PERKS_SELF_TEXT", chr.perks.FreePoints_self);
	SetFormatedText(_type + "PERKS_SHIP_TEXT", chr.perks.FreePoints_ship);
	
	FillCharacterTables(pchar);
}

void FillOfficersList()	// лист должностей
{
	aref arPass;
	ref rOff;
	int iOff;
	string sImg, sOff, sPic, sFrame;
	makearef(arPass, pchar.Fellows.Passengers);
	for(int i=1; i<=8; i++)
	{
		if(i<=3)
		{
			sOff = "fighter"+i;
			iOff = GetOfficersIndex(pchar, i);
			sPic = "fighter";
		}
		else
		{
			switch(i)
			{
				case 4:		sOff = "navigator";		break;
				case 5:		sOff = "boatswain";		break;
				case 6:		sOff = "cannoner";		break;
				case 7:		sOff = "doctor";		break;
				case 8:		sOff = "carpenter";		break;
			//	case 9:		sOff = "carpenter";		break;
			}
			sPic = sOff;
			iOff = sti(arPass.(sOff));
		//	sPath = "interfaces\portraits\128\"+sOff+".tga";
		}
		sImg = "IMG_"+ToUpper(sOff);
		sFrame = "FRAME_"+ToUpper(sOff);
		if(iOff == -1)
		{
			SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, sImg, 6, "OFFICER_PORTRAITS", sPic);
			SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, sFrame, 6, "OFFICER_PORTRAITS", "frame_empty");
		//	SetNewPicture(sImg, sPath);
		}
		else
		{
			rOff = &Characters[iOff];
			SetNewPicture(sImg, "interfaces\portraits\128\face_" + rOff.FaceId + ".tga");
			SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, sFrame, 6, "OFFICER_PORTRAITS", "frame_full");
		}
	}
}

void FillPassengersList()	// таблица пассажиров
{
	int k=1;
	int i, iPsg;
	ref rPsg;
	string row, sPath;
	Table_Clear("TABLE_PASSENGERS", false, true, false);
	int n=GetPassengersQuantity(pchar);
	if(n>4) n=4;
	if(n == 0)
	{
		SetNodeUsing("TABLE_PASSENGERS", false);
		SetNodeUsing("SCROLL_PASSENGERS", false);
		SetNodeUsing("TEXT_NOPASSENGERS", true);
		return;
	}
	else
	{
		GameInterface.TABLE_PASSENGERS.top = 0;
		GameInterface.TABLE_PASSENGERS.select = 1;
		SetNodeUsing("TABLE_PASSENGERS", true);
		SetNodeUsing("SCROLL_PASSENGERS", true);
		SetNodeUsing("TEXT_NOPASSENGERS", false);
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"TABLE_PASSENGERS", -1, 4, makeint(700+fOffsetX), 108, makeint(883+fOffsetX), 108+n*63);
	}
	
	for(i=0; i<GetPassengersQuantity(pchar); i++)	// перебор компаньонов
	{
		iPsg = GetPassenger(pchar, i);
		rPsg = &Characters[iPsg];
		if(!IsCompanion(rPsg))
			continue;
		row = "tr"+k;
		sPath = "interfaces\portraits\128\face_"+rPsg.FaceId+".tga";
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.texture = sPath;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.width = 59;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.height = 59;
		GameInterface.TABLE_PASSENGERS.(row).td2.str = GetFullName(rPsg) + " \n " + ColorText(XI_ConvertString("companion"), "yellow");
		GameInterface.TABLE_PASSENGERS.(row).td2.color = argb(255,255,255,255);
		GameInterface.TABLE_PASSENGERS.(row).UserData.index = iPsg;
		k++;
	}
	
	for(i=0; i<GetPassengersQuantity(pchar); i++)	// перебор офицеров
	{
		iPsg = GetPassenger(pchar, i);
		rPsg = &Characters[iPsg];
		if(IsCompanion(rPsg) || !GetRemovable(rPsg) || CheckAttribute(rPsg, "prisoned"))
			continue;
		row = "tr"+k;
		sPath = "interfaces\portraits\128\face_"+rPsg.FaceId+".tga";
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.texture = sPath;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.width = 59;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.height = 59;
		if(GetOfficerRole(rPsg) == "")
			GameInterface.TABLE_PASSENGERS.(row).td2.str = GetFullName(rPsg) + " \n " + ColorText(XI_ConvertString("officer"), "orange");
		else
			GameInterface.TABLE_PASSENGERS.(row).td2.str = GetFullName(rPsg) + " \n " + ColorText(XI_ConvertString(GetOfficerRole(rPsg)), "orange");
		GameInterface.TABLE_PASSENGERS.(row).td2.color = argb(255,255,255,255);
		GameInterface.TABLE_PASSENGERS.(row).UserData.index = iPsg;
		k++;
	}
	for(i=0; i<GetPassengersQuantity(pchar); i++)	// перебор пассажиров
	{
		iPsg = GetPassenger(pchar, i);
		rPsg = &Characters[iPsg];
		if(GetRemovable(rPsg) || CheckAttribute(rPsg, "prisoned"))
			continue;
		row = "tr"+k;
		sPath = "interfaces\portraits\128\face_"+rPsg.FaceId+".tga";
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.texture = sPath;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.width = 59;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.height = 59;
		GameInterface.TABLE_PASSENGERS.(row).td2.str = GetFullName(rPsg) + " \n " + ColorText(XI_ConvertString("passengership"), "green");
		GameInterface.TABLE_PASSENGERS.(row).td2.color = argb(255,255,255,255);
		GameInterface.TABLE_PASSENGERS.(row).UserData.index = iPsg;
		k++;
	}
	
	for(i=0; i<GetPassengersQuantity(pchar); i++)	// перебор пленников
	{
		iPsg = GetPassenger(pchar, i);
		rPsg = &Characters[iPsg];
		if(!CheckAttribute(rPsg, "prisoned"))
			continue;
		row = "tr"+k;
		sPath = "interfaces\portraits\128\face_"+rPsg.FaceId+".tga";
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.texture = sPath;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.width = 59;
		GameInterface.TABLE_PASSENGERS.(row).td1.icon.height = 59;
		GameInterface.TABLE_PASSENGERS.(row).td2.str = GetFullName(rPsg) + " \n " + ColorText(XI_ConvertString("prisonership"), "red");
		GameInterface.TABLE_PASSENGERS.(row).td2.color = argb(255,255,255,255);
		GameInterface.TABLE_PASSENGERS.(row).UserData.index = iPsg;
		k++;
	}
	Table_UpdateWindow("TABLE_PASSENGERS");
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ПАНЕЛЬ ХАРАКТЕРИСТИК ГГ
////////////////////////////////////////////////////////////////////////////

void ShowClassPanel()	// открыть панель
{
	if(!isActiveClassPanel && canMove)
	{
		FillHeroInfo();
		SetNodeUsing("TITLE_HERONAME_FALSE", true);
		SetNodeUsing("TITLE_HERONAME", false);
		MoveAllNodesToDirSoftly(1, "down", 15, 500, "open");
		PlaySound("interface\Chains_fast.wav");
		canMove = false;
	}
}

void HideClassPanel()	// закрыть панель
{
	if(isActiveClassPanel && canMove)
	{
		MoveAllNodesToDirSoftly(1, "up", 15, 500, "close");
		PlaySound("interface\Chains_fast.wav");
		canMove = false;
	}
}

void FillHeroInfo()	// заполнить панель
{
	string sClass = "spy";
	SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "HERO_CLASS_ICON", 6, "CHARACTER_TALENTS", sClass+"_"+pchar.sex);
	SetFormatedText("HERO_CLASS_NAME", XI_ConvertString("class "+sClass));
	SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "HERO_TALENT1", 6, "CHARACTER_TALENTS", "talent1");
	SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, "HERO_TALENT2", 6, "CHARACTER_TALENTS", "talent2");
	
	
	GameInterface.HERO_TABLE_PIRATES.tr1.td1.str = "P";
	GameInterface.HERO_TABLE_PIRATES.tr1.td1.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td1.str = GetCharacterSPECIAL(pchar, SPECIAL_S);
	GameInterface.HERO_TABLE_PIRATES.tr2.td1.scale = 1.4;
	GameInterface.HERO_TABLE_PIRATES.tr1.td2.str = "I";
	GameInterface.HERO_TABLE_PIRATES.tr1.td2.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td2.str = GetCharacterSPECIAL(pchar, SPECIAL_P);
	GameInterface.HERO_TABLE_PIRATES.tr2.td2.scale = 1.4;
	GameInterface.HERO_TABLE_PIRATES.tr1.td3.str = "R";
	GameInterface.HERO_TABLE_PIRATES.tr1.td3.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td3.str = GetCharacterSPECIAL(pchar, SPECIAL_A);
	GameInterface.HERO_TABLE_PIRATES.tr2.td3.scale = 1.4;
	GameInterface.HERO_TABLE_PIRATES.tr1.td4.str = "A";
	GameInterface.HERO_TABLE_PIRATES.tr1.td4.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td4.str = GetCharacterSPECIAL(pchar, SPECIAL_C);
	GameInterface.HERO_TABLE_PIRATES.tr2.td4.scale = 1.4;
	GameInterface.HERO_TABLE_PIRATES.tr1.td5.str = "T";
	GameInterface.HERO_TABLE_PIRATES.tr1.td5.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td5.str = GetCharacterSPECIAL(pchar, SPECIAL_I);
	GameInterface.HERO_TABLE_PIRATES.tr2.td5.scale = 1.4;
	GameInterface.HERO_TABLE_PIRATES.tr1.td6.str = "E";
	GameInterface.HERO_TABLE_PIRATES.tr1.td6.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td6.str = GetCharacterSPECIAL(pchar, SPECIAL_E);
	GameInterface.HERO_TABLE_PIRATES.tr2.td6.scale = 1.4;
	GameInterface.HERO_TABLE_PIRATES.tr1.td7.str = "S";
	GameInterface.HERO_TABLE_PIRATES.tr1.td7.color = argb(255,225,135,0);
	GameInterface.HERO_TABLE_PIRATES.tr2.td7.str = GetCharacterSPECIAL(pchar, SPECIAL_L);
	GameInterface.HERO_TABLE_PIRATES.tr2.td7.scale = 1.4;
	Table_UpdateWindow("HERO_TABLE_PIRATES");
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ПАНЕЛЬ НАЗНАЧЕНИЯ ОФИЦЕРОВ
////////////////////////////////////////////////////////////////////////////

void ShowChangeOfficers()	// открыть панель
{
	string sCurrentNode = GetCurrentNode();
	sCurChangeOfficer = GetStrSmallRegister(strcut(sCurrentNode, 4, strlen(sCurrentNode)-1));
	string sOff, sRole;
	iCurChangeOfficer = -1;
	if(findsubstr(sCurChangeOfficer, "fighter" , 0) != -1)
	{
		sOff = "id"+strright(sCurChangeOfficer, 1);
		sRole = "fighter";
		if(CheckAttribute(pchar, "Fellows.Passengers.Officers."+sOff))
		{
			iCurChangeOfficer = sti(pchar.Fellows.Passengers.Officers.(sOff));
		}
	}
	else
	{
		sRole = sCurChangeOfficer;
		if(CheckAttribute(pchar, "Fellows.Passengers."+sCurChangeOfficer))
			iCurChangeOfficer = sti(pchar.Fellows.Passengers.(sCurChangeOfficer));
	}
	
	FillOfficersScroll(sRole);
	SetChangeOfficerTitle(sRole);
	
	if(!isActiveChangeOfficers && canMove && !isOffPanelEmpty)
	{
		SetNodeUsing("OFFPANEL_APPOINT", false);
		SetNodeUsing("OFFPANEL_MORE", false);
		SetNodeUsing("TITLE_PASSENGERS", false);
		SetNodeUsing("TITLE_PASSENGERS_FALSE", true);
		SetNodeUsing("TITLE_OFFICERS", false);
		SetNodeUsing("TITLE_OFFICERS_FALSE", true);
		SetNodeUsing("TITLE_MAINSKILLS", false);
		SetNodeUsing("TITLE_MAINSKILLS_FALSE", true);
		MoveAllNodesToDirSoftly(2, "down", 15, 500, "open");
		PlaySound("interface\Chains_fast.wav");
		canMove = false;
		SetSelectable("TABLE_PASSENGERS", false);
		SetSelectable("SCROLL_PASSENGERS", false);
	}
}

void HideOffPanel()	// закрыть панель
{
	if(isActiveChangeOfficers && canMove)
	{
		SetNodeUsing("OFFPANEL_APPOINT", false);
		SetNodeUsing("OFFPANEL_MORE", false);
		FillPassengersList();
		MoveAllNodesToDirSoftly(2, "up", 15, 500, "close");
		PlaySound("interface\Chains_fast.wav");
		canMove = false;
		SetSelectable("TABLE_PASSENGERS", true);
		SetSelectable("SCROLL_PASSENGERS", true);
	}
}

void SetChangeOfficerTitle(string sRole)	// выставить заголовок панели назначения
{
	SetFormatedText("OFFPANEL_TITLE", "Назначение "+GetStrSmallRegister(XI_ConvertString(sRole))+"а");

	SetChangeOfficerInfo();
}

void AppointOfficer()	// назначить офицера
{
	ref rPsg;
	string sCharacter = "pic"+(sti(GameInterface.OFFPANEL_SCROLL.current)+1);
	int iPsg;
	
	if (!CheckAttribute(GameInterface, "OFFPANEL_SCROLL."+sCharacter))
		return;

	if (!CheckAttribute(GameInterface, "OFFPANEL_SCROLL."+sCharacter + ".character"))
		return;

	iPsg = sti(GameInterface.OFFPANEL_SCROLL.(sCharacter).character);
	rPsg = &characters[iPsg];

	string sRole = GetOfficerRole(rPsg);
	int iOff;
	if(sRole != "")
	{
		if(sRole == "fighter")
		{
			RemoveOfficersIndex(pchar, iPsg);
		}
		else
		{
			pchar.Fellows.Passengers.(sRole) = -1;
		}
	}
	if(findsubstr(sCurChangeOfficer, "fighter" , 0) != -1)
	{
		iOff = sti(strright(sCurChangeOfficer, 1));
		SetOfficersIndex(pchar, iOff, iPsg);
	}
	else
	{
		pchar.Fellows.Passengers.(sCurChangeOfficer) = iPsg;
	}
	iCurChangeOfficer = iPsg;
	FillOfficersList();
	SetChangeOfficerInfo();
}

void RemoveOfficer()	// сместить офицера
{
	if(findsubstr(sCurChangeOfficer, "fighter" , 0) != -1)
	{
		RemoveOfficersIndex(pchar, iCurChangeOfficer);
	}
	else
	{
		pchar.Fellows.Passengers.(sCurChangeOfficer) = -1;
	}
	iCurChangeOfficer = -1;
	FillOfficersList();
	SetChangeOfficerInfo();
}

void FillOfficersScroll(string sRole)	// заполнить скролл офицеров
{
	DeleteAttribute(&GameInterface, "OFFPANEL_SCROLL");
	ref rPsg;
	int iPsg;
	string sTemp;
	GameInterface.OFFPANEL_SCROLL.current = 0;	// какой портрет будет по центру в начале
	
	nCurScrollOfficerNum = -1;
	
	GameInterface.OFFPANEL_SCROLL.NotUsed = 0;	// пока непонятно
	GameInterface.OFFPANEL_SCROLL.ListSize = GetFreePassengersQuantity(pchar) + 2;	// пока непонятно
	GameInterface.OFFPANEL_SCROLL.ImagesGroup.t0 = "OFFICER_ICONS";	// назначение группы, из которой будем брать картинки по индексу 0
	GameInterface.OFFPANEL_SCROLL.ImagesGroup.t1 = "OFFICER_FRAME";	// назначение группы, из которой будем брать картинки по индексу 1
	
	FillFaceList("OFFPANEL_SCROLL.ImagesGroup", pchar, 0);	// заполнение фейслиста офицерами (индекс 2)
	FillFaceList("OFFPANEL_SCROLL.ImagesGroup", pchar, 2);	// заполнение фейслиста пассажирами (индекс 2)
	
	GameInterface.OFFPANEL_SCROLL.BadTex1 = 0;
	GameInterface.OFFPANEL_SCROLL.BadPic1 = "empty_portrait";	// ставим первым слоем портрет
	GameInterface.OFFPANEL_SCROLL.BadTex2 = 1;
	GameInterface.OFFPANEL_SCROLL.BadPic2 = "frame";			// ставим вторым слоем рамку
		
	int m=0;
	for(i=0; i<GetPassengersQuantity(pchar); i++)	// перебор пассажиров
	{
		iPsg = GetPassenger(pchar, i);
		sTemp = "pic"+(m+1);
		rPsg = &Characters[iPsg];
		
		if(IsCompanion(rPsg) || !GetRemovable(rPsg) || CheckAttribute(rPsg, "prisoned"))
			continue;
		
		if(sRole != "fighter" && sRole != rPsg.sea_spec)
			continue;
		
		if(sRole == "fighter")
		{
			
		}
		else
		{
			
		}
		if(iCurChangeOfficer != -1 && iPsg == iCurChangeOfficer)
			GameInterface.OFFPANEL_SCROLL.current = m;

		GameInterface.OFFPANEL_SCROLL.(sTemp).character = iPsg;
		GameInterface.OFFPANEL_SCROLL.(sTemp).img1 = GetFacePicName(rPsg);
		GameInterface.OFFPANEL_SCROLL.(sTemp).tex1 = FindFaceGroupNum("OFFPANEL_SCROLL.ImagesGroup","FACE128_"+rPsg.FaceID);
		m++;
	}	
	if(m>=5)
	{
		GameInterface.OFFPANEL_SCROLL.ListSize = m;
		GameInterface.OFFPANEL_SCROLL.NotUsed = 0;
	}
	else
	{
		GameInterface.OFFPANEL_SCROLL.ListSize = 5;
		GameInterface.OFFPANEL_SCROLL.NotUsed = 5-m;
	}
	
	isOffPanelEmpty = (m == 0);
	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"OFFPANEL_SCROLL",-1);
	
}	

void SetChangeOfficerInfo()	// заполнить панель назначения офицера
{
	ref rPsg;
	int iPsg;
	string sCharacter = "pic"+(sti(GameInterface.OFFPANEL_SCROLL.current)+1);
	if (checkAttribute(GameInterface, "OFFPANEL_SCROLL."+sCharacter))
	{
		if (checkAttribute(GameInterface, "OFFPANEL_SCROLL."+sCharacter + ".character"))
		{
			iPsg = sti(GameInterface.OFFPANEL_SCROLL.(sCharacter).character);
			rPsg = &characters[iPsg];
			SetFormatedText("OFFPANEL_NAME", GetFullName(rPsg));
			SetFormatedText("OFFPANEL_RANK", rPsg.rank);
			iCurPassenger = iPsg;
        }
        else
        {
			SetFormatedText("OFFPANEL_NAME", "");
			SetFormatedText("OFFPANEL_RANK", "");
			SetFormatedText("OFFPANEL_HP_TEXT", "");
			SetFormatedText("OFFPANEL_ENERGY_TEXT", "");
			SetNodeUsing("OFFPANEL_APPOINT", false);
			SetNodeUsing("OFFPANEL_MORE", false);
			Table_Clear("OFFPANEL_TABLE_LAND", false, true, false);
			Table_Clear("OFFPANEL_TABLE_SHIP", false, true, false);
			return;
        }
	}
	else
    {
        SetFormatedText("OFFPANEL_NAME", "");
		SetFormatedText("OFFPANEL_RANK", "");
		SetFormatedText("OFFPANEL_HP_TEXT", "");
		SetFormatedText("OFFPANEL_ENERGY_TEXT", "");
		SetNodeUsing("OFFPANEL_APPOINT", false);
		SetNodeUsing("OFFPANEL_MORE", false);
		Table_Clear("OFFPANEL_TABLE_LAND", false, true, false);
		Table_Clear("OFFPANEL_TABLE_SHIP", false, true, false);
		return;
    }
	
	if(iPsg == iCurChangeOfficer)
	{
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"OFFPANEL_APPOINT", 0, "Remove Officer" );
		sCurAppointMode = "remove";
	}
	else
	{
		SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"OFFPANEL_APPOINT", 0, "Add Officer" );
		sCurAppointMode = "add";
	}
	
	GameInterface.StatusLine.OFFPANEL_HP.Max   = MakeInt(LAi_GetCharacterMaxHP(rPsg));
	GameInterface.StatusLine.OFFPANEL_HP.Min   = 0;
	GameInterface.StatusLine.OFFPANEL_HP.Value = MakeInt(LAi_GetCharacterHP(rPsg))
	SendMessage(&GameInterface,"lsl", MSG_INTERFACE_MSG_TO_NODE, "OFFPANEL_HP", 0);
	SetFormatedText("OFFPANEL_HP_TEXT", MakeInt(LAi_GetCharacterHP(rPsg)) + "/" + MakeInt(LAi_GetCharacterMaxHP(rPsg)));
	
	GameInterface.StatusLine.OFFPANEL_ENERGY.Max   = LAi_GetCharacterMaxEnergy(rPsg);
	GameInterface.StatusLine.OFFPANEL_ENERGY.Min   = 0;
	GameInterface.StatusLine.OFFPANEL_ENERGY.Value = makeint(Lai_CharacterGetEnergy(rPsg)));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "OFFPANEL_ENERGY", 0);
	SetFormatedText("OFFPANEL_ENERGY_TEXT", sti(Lai_CharacterGetEnergy(rPsg)) + "/" + sti(LAi_GetCharacterMaxEnergy(rPsg)));
	
	string sRow, sSkill;
	for(int i=1; i<=3; i++)
	{
		sRow = "tr"+i;
		switch(i)
		{
			case 1:		sSkill = "fencing";		break;
			case 2:		sSkill = "athletics";	break;
			case 3:		sSkill = "pistol";		break;
		}
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td1.icon.group = "CHARACTER_SKILLS";
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td1.icon.image = sSkill;
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td1.icon.width = 40;
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td1.icon.height = 40;
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td1.icon.offset = "0, 0";
			
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td2.align = "center";
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td2.valign = "center";
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td2.scale = 1.2;
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td2.textoffset = "0,0";
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td2.str = XI_ConvertString("skill "+sSkill);
		
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td3.align = "center";
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td3.valign = "center";
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td3.scale = 1.2;
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td3.textoffset = "0,0";
		if(!CheckAttribute(rPsg, "skill."+sSkill))
			rPsg.skill.(sSkill) = rand(99)+1;
		GameInterface.OFFPANEL_TABLE_LAND.(sRow).td3.str = rPsg.skill.(sSkill);
	}
	Table_UpdateWindow("OFFPANEL_TABLE_LAND");
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ОКНО ПАССАЖИРА
////////////////////////////////////////////////////////////////////////////

void ShowPassengerWindow()	// открыть окно
{
	XI_WindowShow("PASSENGER_WINDOW", true);
	XI_WindowDisable("PASSENGER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	curWindow = "pass";
	rCurPassenger = &Characters[iCurPassenger];
	SetNewPicture("PASS_PICTURE", "interfaces\portraits\128\face_" + rCurPassenger.FaceId + ".tga");
	SetFormatedText("PASS_TITLE_HERONAME", GetFullName(rCurPassenger));
	SetNodeUsing("PASS_BUTTON_EQUIP", false);
	SetNodeUsing("PASS_BUTTON_REMOVE", false);
	SetNodeUsing("PASS_BUTTON_USE", false);
	SetNewGroupPicture("PASS_SORT_1", "TABS_NEW", "All_on");
	SetFormatedText("PASS_SORT_TEXT", "Всё");
	FillCharacterTables(rCurPassenger);
	FillPassTables();
	FillCharacterBars(rCurPassenger);
	FillPassEquip();
	FilterPassItems("All");
}

void ExitPassWindow()	// закрыть окно
{
	XI_WindowShow("PASSENGER_WINDOW", false);
	XI_WindowDisable("PASSENGER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	curWindow = "main";
//	iCurPassenger = -1;
}

void FillPassTables()	// заполнить таблицы пассажира (PIRATES и специализация)
{
	GameInterface.PASS_TABLE_PIRATES.tr1.td1.str = "P";
	GameInterface.PASS_TABLE_PIRATES.tr1.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr1.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_S);
	GameInterface.PASS_TABLE_PIRATES.tr2.td1.str = "I";
	GameInterface.PASS_TABLE_PIRATES.tr2.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr2.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_P);
	GameInterface.PASS_TABLE_PIRATES.tr3.td1.str = "R";
	GameInterface.PASS_TABLE_PIRATES.tr3.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr3.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_A);
	GameInterface.PASS_TABLE_PIRATES.tr4.td1.str = "A";
	GameInterface.PASS_TABLE_PIRATES.tr4.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr4.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_C);
	GameInterface.PASS_TABLE_PIRATES.tr5.td1.str = "T";
	GameInterface.PASS_TABLE_PIRATES.tr5.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr5.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_I);
	GameInterface.PASS_TABLE_PIRATES.tr6.td1.str = "E";
	GameInterface.PASS_TABLE_PIRATES.tr6.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr6.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_E);
	GameInterface.PASS_TABLE_PIRATES.tr7.td1.str = "S";
	GameInterface.PASS_TABLE_PIRATES.tr7.td1.color = argb(255,225,165,0);
	GameInterface.PASS_TABLE_PIRATES.tr7.td2.str = GetCharacterSPECIAL(rCurPassenger, SPECIAL_L);
	Table_UpdateWindow("PASS_TABLE_PIRATES");
}

void FillPassEquip()	// заполнить экипировку пассажира
{
	string sNode, sType, sItem, sGroup, sPic;
	ref rItem;
	for(int i=1; i<=4; i++)
	{
		sGroup = "EQUIPMENT";
		switch(i)
		{
			case 1:	sNode = "PASS_BLADE";		sType = BLADE_ITEM_TYPE;	sPic = "blade";		break;
			case 2:	sNode = "PASS_PISTOL";		sType = GUN_ITEM_TYPE;		sPic = "pistol";	break;
			case 3:	sNode = "PASS_CUIRASS";		sType = CIRASS_ITEM_TYPE;	sPic = "cuirass";	break;
			case 4:	sNode = "PASS_TALISMAN";	sType = TALISMAN_ITEM_TYPE;	sPic = "talisman";	break;
		}
		sItem = GetCharacterEquipByGroup(rCurPassenger, sType);
		if(sItem != "")	
		{
			rItem = ItemsFromID(sItem);
			sGroup = rItem.picTexture;
			sPic = "itm" + rItem.picIndex;
		}
		SetNewGroupPicture(sNode, sGroup, sPic);
	}
}

void FillPassItems()	// заполнить таблицу предметов пассажира
{
	aref rootItems, curItem, arItem;
	int i, m, n;
	string row, col, sItem, groupID;
	bool ok = true;
	Table_Clear("PASS_TABLE_ITEMS", false, true, false);
	makearef(rootItems, rCurPassenger.items);
	m = 1;
	n = 1;
    for (i = 0; i < GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{
			if(CheckAttribute(arItem, "groupID")) groupID = arItem.groupID;
			switch(curSort)
			{
				case "Gear":
					ok = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
					(groupID == GUN_ITEM_TYPE)	||		// огнестрельное оружие
					(groupID == SPYGLASS_ITEM_TYPE) || // подзорные трубы
					(groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
					(groupID == AMMO_ITEM_TYPE) ||        // боеприпасы
					(groupID == TALISMAN_ITEM_TYPE);        // талисманы
				break;
				case "Potion":
					ok = (CheckAttribute(arItem, "potion")) || (CheckAttribute(arItem, "poison"));
				break;
				case "Ingredients":
					ok = (HasSubStr(arItem.id, "ingredient")) && (!CheckAttribute(arItem, "special_item"));
				break;
				case "Other":
					ok = (HasSubStr(arItem.id, "mineral")) || (HasSubStr(arItem.id, "jewelry"));
				break;
			}
			if(!ok)
				continue;
			row = "tr" + m;
			col = "td" + n;
			sItem = arItem.id;
			if (GetCharacterItem(rCurPassenger, sItem) > 0)
			{
				GameInterface.PASS_TABLE_ITEMS.(row).(col).index = GetItemIndex(arItem.id);
				GameInterface.PASS_TABLE_ITEMS.(row).(col).icon.group = arItem.picTexture;
				GameInterface.PASS_TABLE_ITEMS.(row).(col).icon.image = "itm" + arItem.picIndex;
				if(n==1)
					GameInterface.PASS_TABLE_ITEMS.(row).(col).icon.offset = "0,0";
				else
					GameInterface.PASS_TABLE_ITEMS.(row).(col).icon.offset = "-2,0";
				GameInterface.PASS_TABLE_ITEMS.(row).(col).icon.width = 57;
				GameInterface.PASS_TABLE_ITEMS.(row).(col).icon.height = 57;
				GameInterface.PASS_TABLE_ITEMS.(row).(col).str = GetCharacterItem(rCurPassenger, sItem);
				GameInterface.PASS_TABLE_ITEMS.(row).(col).scale = 0.9;
				GameInterface.PASS_TABLE_ITEMS.(row).(col).textoffset = "40,20";
				n++;
				if(n > 4)
				{
					m++;
					n = 1;
				}
			}
		}
    }
	GameInterface.PASS_TABLE_ITEMS.select = 0;
	GameInterface.PASS_TABLE_ITEMS.selectcol = 0;
	GameInterface.PASS_TABLE_ITEMS.top = 0;
	Table_UpdateWindow("PASS_TABLE_ITEMS");
	
	CheckPassButtons();
}

void FilterPassItems(string filter)	// отфильтровать предметы пассажира
{
	string prevSort = curSort;
	curSort = filter;	//"All";
	string sText, sSort;
	int iSort;
	switch(curSort)
	{
		case "All":				sText = "Всё";			iSort = 1;	break;
		case "Gear":			sText = "Снаряжение";	iSort = 2;	break;
		case "Potion":			sText = "Зелья";		iSort = 3;	break;
		case "Ingredients":		sText = "Ингредиенты";	iSort = 4;	break;
		case "Other":			sText = "Разное";		iSort = 5;	break;
	}
	SetFormatedText("PASS_SORT_TEXT", sText);
	for(int i=1; i<=5; i++)
	{
		switch(i)
		{
			case 1:		sSort = "All";			break;
			case 2:		sSort = "Gear";			break;
			case 3:		sSort = "Potion";		break;
			case 4:		sSort = "Ingredients";	break;
			case 5:		sSort = "Other";		break;
		}
		if(i == iSort)
		{
			SetNewGroupPicture("PASS_SORT_"+i, "TABS_NEW", sSort+"_on");
		}
		else
		{
			SetNewGroupPicture("PASS_SORT_"+i, "TABS_NEW", sSort+"_off");
		}
	}
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"PASS_TABLE_ITEMS", 3);
	if(prevSort != curSort)
	{
		iCurItem = -1;
	}
	FillPassItems();
}

void PressEquipItem()
{
	if(iCurItem == -1)
		return;
	
	string sItem = Items[iCurItem].id;	
	EquipCharacterByItem(rCurPassenger, sItem);
	FillPassEquip();
	FillPassItems();
}

void PressRemoveItem()
{
	if(iCurItem == -1)
		return;
	
	string sGroup = Items[iCurItem].groupID;	
	RemoveCharacterEquip(rCurPassenger, sGroup);
	FillPassEquip();
	FillPassItems();
}

void PressUseItem()
{
	if(iCurItem == -1)
		return;
	
	string sItem = Items[iCurItem].id;	
	DoCharacterUsedItem(rCurPassenger, sItem);
	FillPassEquip();
	FillPassItems();
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
////////////////////////////////////////////////////////////////////////////

string GetOfficerRole(ref chr)	// получить должность персонажа
{
	int i, iOff;
	string sOff;
	string res = "";
	sOff = "";
	iOff = sti(chr.index);
	if(IsOfficer(chr))
	{
		res = "fighter";
	}
	else
	{
		for(i=1; i<=5; i++)
		{
			switch(i)
			{
				case 1:		sOff = "navigator";		break;
				case 2:		sOff = "boatswain";		break;
				case 3:		sOff = "cannoner";		break;
				case 4:		sOff = "doctor";		break;
				case 5:		sOff = "carpenter";		break;
			//	case 6:		sOff = "carpenter";		break;
			}
			if(CheckAttribute(pchar, "Fellows.Passengers."+sOff) && sti(pchar.Fellows.Passengers.(sOff)) == iOff)
			{
				res = sOff;
				break;
			}
		}
	}
	return res;
}

bool IsItemEquipable(ref chr, aref arItem)
{
	if(!CheckAttribute(arItem,"groupID"))
		return false;
	
	if(!IsCanEquiping(chr, arItem.groupID))
		return false;
	
	if (arItem.groupID == AMMO_ITEM_TYPE) 
		return false;
	
	if (arItem.groupID == GUN_ITEM_TYPE) 
	{
		if (!CheckAttribute(arItem,"chargeQ"))
			return false;

		int chrgQ = sti(arItem.chargeQ);,
		if (chrgQ >= 2 && !IsCharacterPerkOn(chr,"Musketeer"))
			return false;
	}
    
	if (arItem.groupID == CIRASS_ITEM_TYPE && arItem.Clothes == false)
    {
		if(arItem.id == "cirass4" || arItem.id == "cirass5")
		{
			if(!IsCharacterPerkOn(chr, "Knight")) 
				return false;
		}
			
		if(arItem.id == "cirass2" || arItem.id == "cirass3")
		{
			if(!IsCharacterPerkOn(chr, "BasicDefense")) 
				return false;
		}
    }
	
	if(CheckAttribute(arItem, "poison"))
		return false;

	return true;
}

void CheckPassButtons()
{
	if(iCurItem == -1)
	{
		SetNodeUsing("PASS_BUTTON_EQUIP", false);
		SetNodeUsing("PASS_BUTTON_REMOVE", false);
		SetNodeUsing("PASS_BUTTON_USE", false);
		return;
	}
	aref arItem;
	makearef(arItem, Items[iCurItem]);
	if(IsEquipCharacterByItem(rCurPassenger, arItem.id))
	{
		SetNodeUsing("PASS_BUTTON_EQUIP", false);
		SetNodeUsing("PASS_BUTTON_REMOVE", true);
		SetNodeUsing("PASS_BUTTON_USE", false);
	}
	else
	{
		if(CheckAttribute(arItem, "potion"))
		{
			SetNodeUsing("PASS_BUTTON_EQUIP", false);
			SetNodeUsing("PASS_BUTTON_REMOVE", false);			
			SetNodeUsing("PASS_BUTTON_USE", true);
		}
		else
		{
			SetNodeUsing("PASS_BUTTON_EQUIP", IsItemEquipable(rCurPassenger, arItem));
			SetNodeUsing("PASS_BUTTON_REMOVE", false);			
			SetNodeUsing("PASS_BUTTON_USE", false);
		}
	}	
}

void CheckMousePosition()
{
	if(curWindow == "main")
		return;
	
	string sItem = "";
	if(CheckMouseNodePos("PASS_BLADE"))
	{
		sItem = GetCharacterEquipByGroup(rCurPassenger, BLADE_ITEM_TYPE);
		if(sItem != "")	
		{
			iCurTextFrameIndex = GetItemIndex(sItem);
			PostEvent("UpdateTextFrame", 800);
		}
		return;
	}
	if(CheckMouseNodePos("PASS_PISTOL"))
	{
		sItem = GetCharacterEquipByGroup(rCurPassenger, GUN_ITEM_TYPE);
		if(sItem != "")	
		{
			iCurTextFrameIndex = GetItemIndex(sItem);
			PostEvent("UpdateTextFrame", 800);
		}
		return;
	}
	if(CheckMouseNodePos("PASS_CUIRASS"))
	{
		sItem = GetCharacterEquipByGroup(rCurPassenger, CIRASS_ITEM_TYPE);
		if(sItem != "")	
		{
			iCurTextFrameIndex = GetItemIndex(sItem);
			PostEvent("UpdateTextFrame", 800);
		}
		return;
	}
	if(CheckMouseNodePos("PASS_TALISMAN"))
	{
		sItem = GetCharacterEquipByGroup(rCurPassenger, TALISMAN_ITEM_TYPE);
		if(sItem != "")	
		{
			iCurTextFrameIndex = GetItemIndex(sItem);
			PostEvent("UpdateTextFrame", 800);
		}
		return;
	}
	
	int iCurRow = -1;
	int iCurCol = -1;
	iCurRow = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "PASS_TABLE_ITEMS", 1);
	iCurRow += sti(GameInterface.PASS_TABLE_ITEMS.top);
	iCurCol = SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "PASS_TABLE_ITEMS", 2);
	
	if(iCurRow == -1 || iCurCol == -1)
	{
		iCurTextFrameIndex = -1;
		HideTextFrame();
		return;
	}
	
	string sCurRow = "tr"+(iCurRow+1);
	string sCurCol = "td"+(iCurCol+1);
	if(!CheckAttribute(&GameInterface,"PASS_TABLE_ITEMS."+sCurRow+"."+sCurCol+".index"))
	{
		iCurTextFrameIndex = -1;
		HideTextFrame();
		return;
	}
	
	if(iCurTextFrameIndex != sti(GameInterface.PASS_TABLE_ITEMS.(sCurRow).(sCurCol).index))
	{
		iCurTextFrameIndex = sti(GameInterface.PASS_TABLE_ITEMS.(sCurRow).(sCurCol).index);
		bUpdateTextFrame = false;
		HideTextFrame();
		PostEvent("UpdateTextFrame", 800);
	}
	else
	{
		if(bUpdateTextFrame)
			Event("UpdateTextFrame");
	}
}

void UpdateTextFrame()
{
	if(iCurTextFrameIndex == -1)
		return;
	bUpdateTextFrame = true;
	float mouseX, mouseY;
	if (CheckAttribute(&GameInterface,"mousepos"))
	{
		mouseX = stf(GameInterface.mousepos.x);
		mouseY = stf(GameInterface.mousepos.y);
		string sTitle, sText;
		sTitle = ColorTextLine(GetAssembledString(LanguageConvertString(idLngFile, Items[iCurTextFrameIndex].name), Items[iCurTextFrameIndex]), "red");
		sText = GetAssembledString(LanguageConvertString(idLngFile, Items[iCurTextFrameIndex].describe), Items[iCurTextFrameIndex]);
		ShowTextFrame(mouseX, mouseY, sTitle, sText);
	}
}	

// задаёт мерцание выделенного портрета офицера
void SetBlinking()
{
	string sNode = GetCurrentNode();
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_NAVIGATOR", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_DOCTOR", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_CARPENTER", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_CANNONER", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_BOATSWAIN", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_FIGHTER1", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_FIGHTER2", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"IMG_FIGHTER3", 5, false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 5, true);
}

void SetNodePos(string sNode, int x1, int y1, int x2, int y2)
{
	GameInterface.(sNode).pos.x1 = x1;
	GameInterface.(sNode).pos.y1 = y1;
	GameInterface.(sNode).pos.x2 = x2;
	GameInterface.(sNode).pos.y2 = y2;
}

bool CheckMouseNodePos(string sNode)
{
	if(!CheckAttribute(&GameInterface, sNode+".pos"))
		return false;
	
	if(!CheckAttribute(&GameInterface,"mousepos"))
		return false;
	
	float mouseX = stf(GameInterface.mousepos.x);
	float mouseY = stf(GameInterface.mousepos.y);
	float x1 = sti(GameInterface.(sNode).pos.x1) + fOffsetX;
	float y1 = sti(GameInterface.(sNode).pos.y1) + fOffsetY;
	float x2 = sti(GameInterface.(sNode).pos.x2) + fOffsetX;
	float y2 = sti(GameInterface.(sNode).pos.y2) + fOffsetY;
	if(mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2)
		return true;
	
	return false;
}
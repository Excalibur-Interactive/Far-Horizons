// boal 14.02.06 меню дебугера
// Hokkins: Обновленная верстка (25.07.2022)
string totalInfo;
int idLngFile = -1;
int remInt = 0;
string textLine = "***********************************"

void InitInterface(string iniName)
{
 	StartAboveForm(true);
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	CalculateInfoData();

	SetFormatedText("DEBUGER_INFO",totalInfo);//"Информация отладчика");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"DEBUGER_INFO",5);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0); 
	SetEventHandler("exitCancel","ProcessCancelExit",0); 
	SetEventHandler("evntDoPostExit","DoPostExit",0); 
	SetEventHandler("ievnt_command","ProcCommand",0);

    GameInterface.teleport_edit.str = "Pirates_Shipyard, reload, reload1";
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_QUICK_SAVE );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
	
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ievnt_command","ProcCommand");

	if(bSeaActive)
    {
        RefreshBattleInterface();
    }
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}


void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	totalInfo = "Старый-добрый отладчик"+ NewStr() + textLine + textLine + textLine + NewStr();
	totalInfo = totalInfo + "1 - " + descS1 + NewStr() +
	            "2 - " + descS2 + NewStr() +
				"3 - " + descS3 + NewStr() +
				"4 - " + descS4 + NewStr() +
				"5 - " + descS5 + NewStr() +
				"6 - " + descS6 + NewStr() +
				"7 - " + descS7 + NewStr() +
				"8 - " + descS8 + NewStr() +
				"9 - " + descS9 + NewStr() +
				"10 - " + descF1 + NewStr() +
	            "11 - " + descF2 + NewStr() +
	            "12 - " + descF3 + NewStr() +
	            "13 - " + descF4 + NewStr() +
	            "14 - " + descF5 + NewStr() +
	            "15 - " + descF6 + NewStr() +
	            "16 - " + descF7 + NewStr() +
	            "17 - " + descF8 + NewStr() +
	            "18 - " + descF9 + NewStr() +
	            "19 - " + descF10 + NewStr() +
	            "20 - " + descF11 + NewStr() +
	            "21 - " + descF12 + NewStr() +
	            "22 - " + descF13 + NewStr() +
	            "23 - " + descF14 + NewStr() +
	            "24 - " + descF15 + NewStr() +
	            "25 - " + descF16 + NewStr() +
	            "26 - " + descF17 + NewStr() +
	            "27 - " + descF18 + NewStr() +
                "28 - " + descF19 + NewStr() +
                "29 - " + descF20 + NewStr() +
				"30 - " + descF21 + NewStr() +
				"31 - " + descF22 + NewStr() +
				"32 - " + descF23 + NewStr() +
				"33 - " + descF24 + NewStr() +
				"34 - " + descF25 + NewStr() +
				"35 - " + descF26 + NewStr() +
				"36 - " + descF27 + NewStr() +
				"37 - " + descF28 + NewStr() +
				"38 - " + descF29 + NewStr() +
				"39 - " + descF30 + NewStr() +
				"40 - " + descF31 + NewStr() +
				"41 - " + descF32 + NewStr();
	
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL1", 0, "#1" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL2", 0, "#2" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL3", 0, "#3" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL4", 0, "#4" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL5", 0, "#5" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL6", 0, "#6" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL7", 0, "#7" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL8", 0, "#8" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BTN_SPECIAL9", 0, "#9" );
	
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F1", 0, "#10" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F2", 0, "#11" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F3", 0, "#12" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F4", 0, "#13" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F5", 0, "#14" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F6", 0, "#15" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F7", 0, "#16" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F8", 0, "#17" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F9", 0, "#18" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F10", 0, "#19" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F11", 0, "#20" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F12", 0, "#21" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F13", 0, "#22" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F14", 0, "#23" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F15", 0, "#24" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F16", 0, "#25" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F17", 0, "#26" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F18", 0, "#27" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F19", 0, "#28" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F20", 0, "#29" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F21", 0, "#30" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F22", 0, "#31" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F23", 0, "#32" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F24", 0, "#33" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F25", 0, "#34" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F26", 0, "#35" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F27", 0, "#36" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F28", 0, "#37" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F29", 0, "#38" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F30", 0, "#39" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F31", 0, "#40" );
	SendMessage( &GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"B_F32", 0, "#41" );
}
void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{	
		case "TELEPORT_BTN":
		  if(comName=="activate" || comName=="click")
		  {
              ReloadByStr();
		  }
	    break;
		case "B_BETA":
		  if(comName=="activate" || comName=="click")
		  {
              IDoExit(RC_INTERFACE_DO_BOAL_BETA);
		  }
	    break;
		case "BTN_SPECIAL1":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataS1();
		  }
	    break;
		
		case "BTN_SPECIAL2":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataS2();
		  }
	    break;
		
		case "BTN_SPECIAL3":
		  if(comName=="activate" || comName=="click")
		  {
		     CalculateInfoDataS3();
		  }
	    break;
		
		case "BTN_SPECIAL4":
		  if(comName=="activate" || comName=="click")
		  {
		     CalculateInfoDataS4();
		  }
	    break;
		
		case "BTN_SPECIAL5":
		  if(comName=="activate" || comName=="click")
		  {
		    CalculateInfoDataS5();
		  }
	    break;
		
		case "BTN_SPECIAL6":
		  if(comName=="activate" || comName=="click")
		  {
		     CalculateInfoDataS6();
		  }
	    break;
		
		case "BTN_SPECIAL7":
		  if(comName=="activate" || comName=="click")
		  {
		     CalculateInfoDataS7();
		  }
	    break;
		
		case "BTN_SPECIAL8":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataS8();
		  }
	    break;
		
		case "BTN_SPECIAL9":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataS9();
		  }
	    break;
		
	    case "B_F1":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF1();
		  }
	    break;
		
	    case "B_F2":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF2();
		  }
	    break;
		
	    case "B_F3":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF3();
		  }
	    break;
		
	    case "B_F4":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF4();
		  }
	    break;
		
	    case "B_F5":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF5();
		  }
	    break;

	    case "B_F6":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF6();
		  }
	    break;

	    case "B_F7":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF7();
		  }
	    break;

	    case "B_F8":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF8();
		  }
	    break;

	    case "B_F9":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF9();
		  }
	    break;

	    case "B_F10":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF10();
		  }
	    break;

	    case "B_F11":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF11();
		  }
	    break;

	    case "B_F12":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF12();
		  }
	    break;

	    case "B_F13":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF13();
		  }
	    break;

	    case "B_F14":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF14();
		  }
	    break;

	    case "B_F15":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF15();
		  }
	    break;

	    case "B_F16":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF16();
		  }
	    break;

	    case "B_F17":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF17();
		  }
	    break;

	    case "B_F18":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF18();
		  }
	    break;
	    
	    case "B_F19":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF19();
		  }
	    break;

        case "B_F20":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF20();
		  }
	    break;
	    
	    case "B_F21":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF21();
		  }
	    break;
		
	    case "B_F22":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF22();
		  }
	    break;
		
	    case "B_F23":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF23();
		  }
	    break;
		
	    case "B_F24":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF24();
		  }
	    break;
		
	    case "B_F25":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF25();
		  }
	    break;
		
	    case "B_F26":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF26();
		  }
	    break;
		
	    case "B_F27":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF27();
		  }
	    break;
		
	    case "B_F28":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF28();
		  }
	    break;
		
	    case "B_F29":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF29();
		  }
	    break;
		
	    case "B_F30":
		  if(comName=="activate" || comName=="click")
		  {
		      CalculateInfoDataF30();
		  }
	    break;
		
	    case "B_F31":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF31();
		}
	    break;
		
	    case "B_F32":
		if(comName=="activate" || comName=="click")
		{
			CalculateInfoDataF32();
		}
	    break;
	}
}

string descS1 = "Неуязвимость Вкл/Выкл";
void CalculateInfoDataS1()
{
	totalInfo = descS1;
	ref mc;
	string Immortality;
	mc = GetMainCharacter();
	if(LAi_IsImmortal(mc))
	{
		LAi_SetImmortal(mc, false);
		Log_SetStringToLog("Неуязвимость ВЫКЛ");
        Immortality = "Выключена";				
	}
	else
	{
		LAi_SetImmortal(mc, true);
		Log_SetStringToLog("Неуязвимость ВКЛ");
        Immortality = "Включена";				
	}

    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно! Неуязвимость " +Immortality+ "!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS2 = "+ 50 000 монет";
void CalculateInfoDataS2()
{
	totalInfo = descS2;
	Pchar.money = sti(Pchar.money) + 50000;
	totalInfo = totalInfo + NewStr() + GetAssembledString("Нужно больше золота? Текущее количество монет теперь равно #dmoney#.",	Pchar);
	
	totalInfo = totalInfo + NewStr();
	totalInfo = totalInfo + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS3 = "ID локации + координаты";
void CalculateInfoDataS3()
{
	totalInfo = descS3 +"\n";
	
	ref mc;
	mc = GetMainCharacter();

	float locx, locy, locz;
	if (bSeaActive && !bAbordageStarted)
	{
	    if (CheckAttribute(mc, "Ship.pos.x"))
		{
		    totalInfo = totalInfo + NewStr() + mc.location + "     ship(x,z)= "+mc.Ship.pos.x +", "+mc.Ship.pos.z;
			totalInfo = totalInfo + NewStr() + " Sea_Coord.X " + Sea_GetRealCoordX(makefloat(mc.Ship.pos.x)) + " Sea_Coord.Z " + Sea_GetRealCoordZ(makefloat(mc.Ship.pos.z));
			
		    if (false)
	        {
	            string sTemp = mc.curIslandId;
	            float r1 = stf(worldMap.islands.(sTemp).GoMapRadius);

				r1 *= WDM_MAP_TO_SEA_SCALE;
	            float d2 = GetDistance2D(stf(mc.Ship.Pos.x),
	                              stf(mc.Ship.Pos.z),
	                              stf(worldMap.islands.(sTemp).position.rx),
	                              stf(worldMap.islands.(sTemp).position.rz));

	            totalInfo = totalInfo + "         Координаты для карты radius= " + r1 + "   GetDistance2D= " + d2 + "      ";
	        }
		}
	}
	else
	{
  		if (IsEntity(loadedLocation))
  		{
			GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
			totalInfo = totalInfo + "id = " + mc.location + " (x,y,z)= "+locx + ", " +locy + ", "+locz;
			totalInfo = totalInfo + NewStr() + "filespath.models = " + loadedLocation.filespath.models;
			totalInfo = totalInfo + NewStr() + "image = " + loadedLocation.image;
			totalInfo = totalInfo + NewStr() + "models.locators = " + loadedLocation.models.always.locators;
			
			if(CheckAttribute(LoadedLocation, "islandId"))
			{
				totalInfo = totalInfo + NewStr() + "islandId = " + LoadedLocation.islandId;
			}
			
			if(CheckAttribute(LoadedLocation, "townsack"))
			{
				totalInfo = totalInfo + NewStr() + "townsack = " + LoadedLocation.townsack;
			}
		}
	}
	totalInfo = totalInfo + NewStr() + " MapShipX " +	worldMap.playerShipX + " MapShipZ " + worldMap.playerShipZ + " X " + worldMap.island.x + " Z " + worldMap.island.z;
	
	totalInfo = totalInfo + NewStr() + " Map_Coord.X " + Map_GetRealCoordX(makefloat(worldMap.playerShipX)) + " Map_Coord.Z " + Map_GetRealCoordZ(makefloat(worldMap.playerShipZ));
	
	totalInfo = totalInfo + NewStr() + " Zero_Point_X " + makefloat(worldMap.zeroX) + " Zero_Point_Z " + makefloat(worldMap.zeroZ);
    // <
	
	totalInfo = totalInfo + NewStr();
	totalInfo = totalInfo + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS4 = "Перегруз локации - для КОЛОВ (Освещения)";
void CalculateInfoDataS4()
{
	totalInfo = descS4;
	
	totalInfo = totalInfo + NewStr();
	totalInfo = totalInfo + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
	
    ProcessCancelExit();
    if(bSeaActive && !bAbordageStarted)
    {
    	Sea_ReloadStart();
	}
	else
	{
	    DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
	}
}

string descS5 = "Скрыть/Показать интерфейс";
void CalculateInfoDataS5()
{
	totalInfo = descS5;
	ChangeShowIntarface();
	
	totalInfo = totalInfo + NewStr();
	totalInfo = totalInfo + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS6 = "Все личные умения по 100 / по 10";
void CalculateInfoDataS6()
{
	totalInfo = descS6;
	int iSkill;
	ref mc = GetMainCharacter();
	
	if(CheckAttribute(pchar, "RemovedSelfPerks"))
	{
		DeleteAttribute(pchar, "RemovedSelfPerks");
	    iSkill = 10;
		Log_info("Все личные умения по 10.");
		totalInfo += "Все личные умения по 10." + NewStr();
	}
	else
	{
    	mc.RemovedSelfPerks = true;
	    iSkill = 100;
		Log_info("Все личные умения по 100.");
		totalInfo += "Все личные умения по 100." + NewStr();
	}
	
    mc.skill.Fencing = iSkill;
    mc.skill.Pistol = iSkill;
	mc.skill.Sneak = iSkill;
	mc.skill.Leadership = iSkill;
	
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS7 = "Все корабельные умения по 100 / по 10";
void CalculateInfoDataS7()
{
	totalInfo = descS7;
	int iSkill;
	ref mc = GetMainCharacter();
	
	if(CheckAttribute(pchar, "RemovedShipPerks"))
	{
		DeleteAttribute(pchar, "RemovedShipPerks");
	    iSkill = 10;
		Log_info("Все корабельные умения по 10.");
		totalInfo += "Все корабельные умения по 10." + NewStr();
	}
	else
	{
    	mc.RemovedShipPerks = true;
	    iSkill = 100;
		Log_info("Все корабельные умения по 100.");
		totalInfo += "Все корабельные умения по 100." + NewStr();
	}
	
    mc.skill.Sailing = iSkill;
    mc.skill.Cannons = iSkill;
    mc.skill.Accuracy = iSkill;
    mc.skill.Commerce = iSkill;
    mc.skill.Defence = iSkill;
    mc.skill.Repair = iSkill;
    mc.skill.Grappling = iSkill;
	
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS8 = "Получить по 1 свободному перку в личные и корабельные способности";
void CalculateInfoDataS8()
{
	totalInfo = descS8;
	
	PChar.Perks.FreePoints_Self = sti(PChar.Perks.FreePoints_Self) + 1;
	Log_info("Получен 1 свободный личный перк!");
	totalInfo += "Получен 1 свободный личный перк!" + NewStr() + "Личных перков: " + sti(PChar.Perks.FreePoints_Self);
	
	totalInfo += "\n\n";
	
	PChar.Perks.FreePoints_Ship = sti(PChar.Perks.FreePoints_Ship) + 1;
	Log_info("Получен 1 свободный корабельный перк!");
	totalInfo += "Получен 1 свободный корабельный перк!" + NewStr() + "Корабельных перков: " + sti(PChar.Perks.FreePoints_Ship);
	
	totalInfo = totalInfo + NewStr();
	totalInfo = totalInfo + "Команда отработала успешно!";
	
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descS9 = "Починить корабль Главного Героя";
void CalculateInfoDataS9()
{
	totalInfo = descS9;
	Pchar.ship.hp = RealShips[sti(pchar.Ship.Type)].hp;
    DeleteAttribute(Pchar,"ship.sails");
    DeleteAttribute(Pchar,"ship.masts");
    DeleteAttribute(Pchar,"ship.blots");
		
	totalInfo = totalInfo + NewStr();
	totalInfo = totalInfo + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
	
}

string descF1 = "Телепорт по Тавернам";
void CalculateInfoDataF1()
{
	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	totalInfo = descF1;
	// -->
	ref mc, ch;
	int n, idx;
	mc = GetMainCharacter();
    idx = GetCharIDXByParam("TavernMan", "location", mc.location);
    bool ok = true;
    while (ok)
    {
        for(n=0; n<MAX_CHARACTERS; n++)
    	{
    		makeref(ch,Characters[n]);
    		if (CheckAttribute(ch, "TavernMan"))
    		{
                if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
                if (n > idx)
                {
                    ok = false;
                    if (GetCityFrom_Sea(ch.City) != "")
                    {
                        setCharacterShipLocation(mc, GetCityFrom_Sea(ch.City));
                        setWDMPointXZ(GetCityFrom_Sea(ch.City));
                    }
                    DoQuestReloadToLocation(ch.location,"reload","reload1", "");
                    Log_Info(ch.location);
                    break;
                }
    		}
        }
        idx = -1;
    }
	// <
    totalInfo = totalInfo + LanguageConvertString(idLngFile,"new_string") + LanguageConvertString(idLngFile,"new_string") +
                "Команда отработала успешно!";
    LanguageCloseFile(idLngFile);
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF2 = "Кастомная кнопка";
void CalculateInfoDataF2()
{
	totalInfo = descF2;
	
	
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);

	ProcessCancelExit();
}
////////////////////////////////////////////////////////////////////////
string descF3 = "+10 ед. опыта команде корабля";

void CalculateInfoDataF3()
{
	// -->
	totalInfo = descF3;
	
	ChangeCrewExp(pchar, "Sailors", 10);
	ChangeCrewExp(pchar, "Cannoners", 10);
	ChangeCrewExp(pchar, "Soldiers", 10);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF4 = "+35 свободных очков умений (1 ранг)";

void CalculateInfoDataF4()
{
	// -->
	totalInfo = descF4;
	
	pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 35;
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
  
}
////////////////////////////////////////////////////////////////////////
string descF5 = "Миллион, Фрегат с 32-ым калибром, 20-ый ранг";
void CalculateInfoDataF5()
{
	totalInfo = descF5;
	
    ref mc;
	string sEquipItem;
	mc = GetMainCharacter();
	SetRandSelfSkill(mc, 80, 100);
	SetRandShipSkill(mc, 80, 100);
	
	mc.rank = 20;
	LAi_SetHP(mc, 250.0, 250.0);
	mc.Ship.Type = GenerateShipExt(SHIP_FRIGATE, true, mc);
	SetBaseShipData(mc);
	mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	SetCrewQuantityFull(mc);
	AddCrewMorale(mc, 80);
	ChangeCrewExp(mc, "Sailors", 50);
	ChangeCrewExp(mc, "Cannoners", 50);
	ChangeCrewExp(mc, "Soldiers", 50);

	SetCharacterGoods(mc, GOOD_BALLS, 700);
	SetCharacterGoods(mc, GOOD_GRAPES, 700);
	SetCharacterGoods(mc, GOOD_KNIPPELS, 700);
	SetCharacterGoods(mc, GOOD_FOOD, 500);
	SetCharacterGoods(mc, GOOD_POWDER, 2000);
	SetCharacterGoods(mc, GOOD_WEAPON, 500);

	sEquipItem = GetCharacterEquipByGroup(mc, BLADE_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, GUN_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);
	sEquipItem = GetCharacterEquipByGroup(mc, SPYGLASS_ITEM_TYPE);
	RemoveItems(mc, sEquipItem, 1);

	AddMoneyToCharacter(mc, 1000000);
	AddItems(mc, "spyglass4", 1);
	AddItems(mc, "pistol5", 1);
	
	sEquipItem = SelectGeneratedItem("", "excellent", "", "");;
	AddItems(mc, sEquipItem, 1);
	
	AddItems(mc, "bullet", 50);
	AddItems(mc, "GunPowder", 50);

	EquipCharacterbyItem(mc, "spyglass3");
	EquipCharacterbyItem(mc, "pistol5");
 	EquipCharacterbyItem(mc, sEquipItem);
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF6 = "Ветер 14.5";

void CalculateInfoDataF6()
{
	totalInfo = descF6;
 	
	Weather.Wind.Speed = 14.5;
	pchar.wind.speed = Weather.Wind.Speed;
	fWeatherSpeed = stf(Weather.Wind.Speed);
	
	totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
	SetFormatedText("DEBUGER_INFO", totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF7 = "Репутация + 10";

void CalculateInfoDataF7()
{
	totalInfo = descF7;
    int i, cn;
    ref mc;
	mc = GetMainCharacter();

    if ( sti(mc.reputation) < REPUTATION_MAX)
	{
	   mc.reputation = sti(mc.reputation) + 10;
	   if (sti(mc.reputation) > REPUTATION_MAX)
	   {
	       mc.reputation = REPUTATION_MAX;
	   }
	}
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF8 = "Репутация -10";

void CalculateInfoDataF8()
{
	totalInfo = descF8;
	if ( sti(pchar.reputation) > 1)
	{
	   pchar.reputation = sti(pchar.reputation) - 10;
	   if (sti(pchar.reputation) < 1)
	   {
	       pchar.reputation = 1;
	   }
	}
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF9 = "Энкаунтеры на картах Вкл/Выкл";

void CalculateInfoDataF9()
{
	// -->
	totalInfo = descF9;
    ref mc;
	mc = GetMainCharacter();
    if(CheckAttribute(mc,"worldmapencountersoff") == 0)
	{
		mc.worldmapencountersoff = "1";
		Log_SetStringToLog("Worldmap encounters OFF");
	}
	else
	{
		if(mc.worldmapencountersoff == "1")
		{
			mc.worldmapencountersoff = "0";
			Log_SetStringToLog("Worldmap encounters ON");
		}
		else
		{
			mc.worldmapencountersoff = "1";
			Log_SetStringToLog("Worldmap encounters OFF");
		}
	}
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF10 = "Вызвать смену отношения наций";

void CalculateInfoDataF10()
{
	totalInfo = descF10;
	DoQuestCheckDelay("Nation_Legend_Map", 2.0);
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
    ProcessCancelExit();
}
////////////////////////////////////////////////////////////////////////
string descF11 = "Режим Дробовика Вкл/Выкл";

void CalculateInfoDataF11()
{
	totalInfo = descF11;
     if(globalSGMode != false)
	{
		globalSGMode = false;
		Log_SetStringToLog("Shotgun mode OFF");
	}
	else
	{
		globalSGMode = true;
		Log_SetStringToLog("Shotgun mode ON");
	}
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}
////////////////////////////////////////////////////////////////////////
string descF12 = "Промотать 5 дней";

void CalculateInfoDataF12()
{
	totalInfo = descF12;
	LAi_Fade("", "");
    for (int i = 1; i<=5; i++)
    {
		AddDataToCurrent(0, 0, 1);
	}
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF13 = "Обновление света на маяках";
void CalculateInfoDataF13()
{
	totalInfo = descF13;
    // -->
	Sea_CreateLighthouse("Jamaica");
	Sea_CreateLighthouse("Cuba1");
	Sea_CreateLighthouse("Cuba2");
	SendMessage(&lighthouseLightModel, "lffffffffffff", MSG_MODEL_SET_POSITION,-116.0, 55.0, -1568.5, 1, 0, 0, 0, 1, 0, 0, 0, 1);
    // <--
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF14 = "Реинит локаций";

void CalculateInfoDataF14()
{
	totalInfo = descF14;
	ProcessCancelExit();
    LocationInit();
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF15 = "Вкл/Выкл проверку патрулем в городах";

void CalculateInfoDataF15()
{
	totalInfo = descF15;
	string sPatrol = "";
    if(!CheckAttribute(pchar, "NoPatrolTest"))
	{
	    pchar.NoPatrolTest = true;
		sPatrol = "выключена."
    }
	else
	{
		DeleteAttribute(pchar, "NoPatrolTest");
		sPatrol = "включена."
	}
    totalInfo = totalInfo + NewStr() + NewStr() + " Проверка патрулем " + sPatrol;
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF16 = "НЗГ у всех наций +50 000";

void CalculateInfoDataF16()
{
	totalInfo = descF16;
    for (int j=0; j< MAX_NATIONS; j++)
	{
        ChangeCharacterNationReputation(pchar, j, -50);
    }
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF17 = "НЗГ у всех наций - 50 000";

void CalculateInfoDataF17()
{
	totalInfo = descF17;
	for (int j=0; j< MAX_NATIONS; j++)
	{
        ChangeCharacterNationReputation(pchar, j, 50);
    }
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF18 = "Добавить офицера в пассажиры";
void CalculateInfoDataF18()
{
	totalInfo = descF18;
	for (int i = 1; i <= 16; i++)
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("Debug_Off" + i, "sailor_" + (rand(15) + 1), "man", "man", sti(pchar.rank), PIRATE, -1, true, F_OFFICER));
	    sld.Dialog.Filename = "Enc_Officer_dialog.c";
	    sld.dialog.currentnode = "hired";
	    LAi_SetOfficerType(sld);
	    SetOfficerParam(sld, rand(4));
	    pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
	    LandEnc_OfficerHired();
	}
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF19 = "Вызвать шторм в текущей сухопутной локации (для создания освещения и тестов)";
void CalculateInfoDataF19()
{
    totalInfo = descF19;

	if(!bSeaActive && !IsEntity(&WorldMap))
	{
		ref location = &Locations[FindLocation(pchar.location)];
		if (CheckAttribute(location, "alwaysStorm"))
		{
			DeleteAttribute(location, "alwaysStorm");
			DeleteAttribute(location, "storm");
			DeleteAttribute(location, "tornado");
			DeleteAttribute(location, "QuestlockWeather");
		}
		else
		{
		location.alwaysStorm = true; 
		location.storm = true;
		location.tornado = true;
	    }
	}
	
	DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF20 = "Сменить материал парусов";
void CalculateInfoDataF20()
{
	aref sails;
	makearef(sails, RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
	RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = ((sti(sails) + 1) % 3) + 1;
	totalInfo = "Текущий материал: " + GetSailsType(sti(sails));
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF21 = "Пусто";
void CalculateInfoDataF21()
{
    totalInfo = descF21;
	
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF22 = "Пусто";
void CalculateInfoDataF22()
{
	totalInfo = descF22;
	
   totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF23 = "Пусто";
void CalculateInfoDataF23()
{
    totalInfo = descF23;

    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF24 = "Пусто";
void CalculateInfoDataF24()
{
    totalInfo = descF24;
    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF25 = "Пусто";
void CalculateInfoDataF25()
{
    totalInfo = descF25;

    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF26 = "Пусто";
void CalculateInfoDataF26()
{
	totalInfo = descF26;
	
	totalInfo = totalInfo + NewStr() + NewStr() +
		"Команда отработала успешно!";
	SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF27 = "Пусто";
void CalculateInfoDataF27()
{
    totalInfo = descF27;

    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF28 = "Пусто";
void CalculateInfoDataF28()
{
    totalInfo = descF28;
	
    totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
    SetFormatedText("INFO_TEXT",totalInfo);
}

string descF29 = "Пусто";
void CalculateInfoDataF29()
{
    totalInfo = descF29;

    totalInfo = totalInfo + NewStr() + NewStr() +"Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF30 = "Пусто";
void CalculateInfoDataF30()
{
    totalInfo = descF30;

    totalInfo = totalInfo + NewStr() + NewStr() +
                "Команда отработала успешно!";
    SetFormatedText("DEBUGER_INFO",totalInfo);
}

string descF31 = "Пусто";
void CalculateInfoDataF31()
{
	totalInfo = descF31;
	 	
	totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
	SetFormatedText("DEBUGER_INFO", totalInfo);
}

string descF32 = "Пусто";
void CalculateInfoDataF32()
{
	totalInfo = descF32;
 	pchar.chr_ai.hp = 300;
 	pchar.chr_ai.hp_max = 3000;
	totalInfo = totalInfo + NewStr() + NewStr() + "Команда отработала успешно!";
	
	SetFormatedText("DEBUGER_INFO", totalInfo);
}


void ReloadByStr()
{
	// разбор строки
	string  loc = stripblank(GetSubStringByNum(GameInterface.teleport_edit.str, 0));
	string  grp = stripblank(GetSubStringByNum(GameInterface.teleport_edit.str, 1));
	string  ltr = stripblank(GetSubStringByNum(GameInterface.teleport_edit.str, 2));

    int i = FindLocation(loc);
    if (i != -1)
    {
        if(CheckAttribute(&locations[i],"fastreload"))
        {
			if (GetCityFrom_Sea(locations[i].fastreload) != "")
		    {
		        setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		        setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
		    }
	    }
	    else
	    {
	        if (locations[i].type == "seashore" || locations[i].type == "mayak")
	        {
	            setCharacterShipLocation(pchar, loc));
		        setWDMPointXZ(loc);
	        }
	    }
	    DoQuestReloadToLocation(loc, grp, ltr, "");
	    Log_Info(loc);
	    
		// Статистика по читам
		Statistic_AddValue(PChar, "Cheats.ReloadByStr", 1);
    }
    else
    {
        Log_Info("Нет локации");
    }
}

void GetRealCoordsObjects()
{
	trace("---------");
	trace("Barbados (island)					: " + Map_GetRealCoordX(946.0062) + " " + Map_GetRealCoordZ(-486.9014));
	trace("Бриджтаун 							: " + Map_GetRealCoordX(903.6217) + " " + Map_GetRealCoordZ(-522.2799));
	trace("Mayak2 (маяк Барбадоса)				: " + Map_GetRealCoordX(918.619) + " " + Map_GetRealCoordZ(-506.827));
	trace("Shore4 (мыс Гаррисон)				: " + Map_GetRealCoordX(919.808) + " " + Map_GetRealCoordZ(-448.061));
	trace("Shore5 (мыс Раггед Пойнт)			: " + Map_GetRealCoordX(983.787) + " " + Map_GetRealCoordZ(-518.14));	
	trace("---------");
	trace("Antigua (island)						: " + Map_GetRealCoordX(903.9222) + " " + Map_GetRealCoordZ(109.0605));
	trace("Сент-Джонс 							: " + Map_GetRealCoordX(852.4083) + " " + Map_GetRealCoordZ(128.9092));
	trace("Shore1 (мыс Бун)						: " + Map_GetRealCoordX(880.892) + " " + Map_GetRealCoordZ(148.897));
	trace("Shore2 (залив Уиллогби)				: " + Map_GetRealCoordX(931.028) + " " + Map_GetRealCoordZ(74.5353));
	trace("---------");
	trace("Curacao (island) 					: " + Map_GetRealCoordX(383.4142) + " " + Map_GetRealCoordZ(-691.11));
	trace("Виллемштадт 							: " + Map_GetRealCoordX(396.1) + " " + Map_GetRealCoordZ(-722.8));	
	trace("Shore22 (Пальмовый берег)			: " + Map_GetRealCoordX(354.604) + " " + Map_GetRealCoordZ(-678.54));
	trace("Shore23 (Мыс Кальвинистов)			: " + Map_GetRealCoordX(347.313) + " " + Map_GetRealCoordZ(-705.112));
	trace("Shore24 (берег Приют Контрабандиста)	: " + Map_GetRealCoordX(455.427) + " " + Map_GetRealCoordZ(-740.655));
	trace("---------");
	trace("SentMartin (island)					: " + Map_GetRealCoordX(921.559) + " " + Map_GetRealCoordZ(523.596));
	trace("Мариго 								: " + Map_GetRealCoordX(900.0994) + " " + Map_GetRealCoordZ(501.6531));	
	trace("Shore40 (берег Спасения)				: " + Map_GetRealCoordX(924.442) + " " + Map_GetRealCoordZ(554.385));	
	trace("Shore41 (бухта Неистового ветра)		: " + Map_GetRealCoordX(898.877) + " " + Map_GetRealCoordZ(522.703));	
	trace("---------");
	trace("Guadeloupe (island)					: " + Map_GetRealCoordX(537.114) + " " + Map_GetRealCoordZ(-25.3853));	
	trace("Бас-Тер 								: " + Map_GetRealCoordX(462.2107) + " " + Map_GetRealCoordZ(-73.0837));		
	trace("Mayak4 (маяк Гваделупы)				: " + Map_GetRealCoordX(465.076) + " " + Map_GetRealCoordZ(-38.9423));		
	trace("Shore28 (бухта Морн л'О)				: " + Map_GetRealCoordX(536.636) + " " + Map_GetRealCoordZ(26.1279));		
	trace("Shore29 (пляж Капстер)				: " + Map_GetRealCoordX(507.669) + " " + Map_GetRealCoordZ(-75.4176));		
	trace("Shore30 (бухта Гран Бур)				: " + Map_GetRealCoordX(549.807) + " " + Map_GetRealCoordZ(-69.7107));		
	trace("Shore31 (мыс Недоступный)			: " + Map_GetRealCoordX(589.889) + " " + Map_GetRealCoordZ(-65.0601));		
	trace("---------");
	trace("Martinique (island) 					: " + Map_GetRealCoordX(538.524) + " " + Map_GetRealCoordZ(-385.567));		
	trace("Форт-де-Франс 						: " + Map_GetRealCoordX(513.51) + " " + Map_GetRealCoordZ(-397.645));		
	trace("Ле-Франсуа 							: " + Map_GetRealCoordX(559.008) + " " + Map_GetRealCoordZ(-368.16));		
	trace("Shore38 (пляж Ламантен)				: " + Map_GetRealCoordX(481.181) + " " + Map_GetRealCoordZ(-340.832));		
	trace("Shore39 (бухта Ле Марен)				: " + Map_GetRealCoordX(557.181) + " " + Map_GetRealCoordZ(-422.987));		
	trace("---------");
	trace("Bermudes (island)					: " + Map_GetRealCoordX(920.738) + " " + Map_GetRealCoordZ(920.767));		
	trace("Пиратское поселение 					: " + Map_GetRealCoordX(931.059) + " " + Map_GetRealCoordZ(928.281));		
	trace("Shore3 (залив Руны)					: " + Map_GetRealCoordX(915.745) + " " + Map_GetRealCoordZ(966.469));		
	trace("Shore_ship1 (бухта Разбитого Корыта) : " + Map_GetRealCoordX(968.947) + " " + Map_GetRealCoordZ(923.636));		
	trace("---------");
	trace("Maracaibo (areal) 					: " + Map_GetRealCoordX(178.51) + " " + Map_GetRealCoordZ(-870.37));		
	trace("Маракайбо 							: " + Map_GetRealCoordX(134.82) + " " + Map_GetRealCoordZ(-939.65));		
	trace("Shore37 (бухта Гуахира)				: " + Map_GetRealCoordX(140.753) + " " + Map_GetRealCoordZ(-828.99));		
	trace("Shore_ship3 (мыс Несбывшихся Надежд)	: " + Map_GetRealCoordX(198.162) + " " + Map_GetRealCoordZ(-994.035));		
	trace("---------");
	trace("Beliz (areal) 						: " + Map_GetRealCoordX(-896.084) + " " + Map_GetRealCoordZ(230.227));		
	trace("Shore_ship2 (залив Гибели)			: " + Map_GetRealCoordX(-1022.94) + " " + Map_GetRealCoordZ(629.355));		
	trace("Shore6 (мыс Каточе)					: " + Map_GetRealCoordX(-909.655) + " " + Map_GetRealCoordZ(629.079));		
	trace("Shore7 (залив Косумель)				: " + Map_GetRealCoordX(-915.581) + " " + Map_GetRealCoordZ(409.002));		
	trace("Shore8 (бухта Четумаль)				: " + Map_GetRealCoordX(-963.489) + " " + Map_GetRealCoordZ(281.628));		
	trace("Белиз 								: " + Map_GetRealCoordX(-978.396) + " " + Map_GetRealCoordZ(158.751));		
	trace("Shore9 (бухта Аматике)				: " + Map_GetRealCoordX(-1017.2) + " " + Map_GetRealCoordZ(-33.7293));		
	trace("Shore10 (лагуна Каратаска)			: " + Map_GetRealCoordX(-818.198) + " " + Map_GetRealCoordZ(-177.208));		
	trace("---------");
	trace("Jamaica (island)						: " + Map_GetRealCoordX(-298.0) + " " + Map_GetRealCoordZ(-128.0));		
	trace("Порт-Ройал 							: " + Map_GetRealCoordX(-250.157) + " " + Map_GetRealCoordZ(-150.839));		
	trace("Shore35 (мыс Негрил)					: " + Map_GetRealCoordX(-446.951) + " " + Map_GetRealCoordZ(-107.118));			
	trace("Shore36 (бухта Портленд)				: " + Map_GetRealCoordX(-281.543) + " " + Map_GetRealCoordZ(-164.245));			
	trace("Mayak3 (маяк Порт Рояля)				: " + Map_GetRealCoordX(-224.127) + " " + Map_GetRealCoordZ(-163.435));			
	trace("---------");
	trace("PuertoRico (island) 					: " + Map_GetRealCoordX(506.489) + " " + Map_GetRealCoordZ(460.815));			
	trace("Сан-Хуан 							: " + Map_GetRealCoordX(528.645) + " " + Map_GetRealCoordZ(484.18));				
	trace("Shore44 (бухта Агуадилья)			: " + Map_GetRealCoordX(392.82) + " " + Map_GetRealCoordZ(501.808));				
	trace("Shore45 (пляж Фахардо)				: " + Map_GetRealCoordX(602.049) + " " + Map_GetRealCoordZ(458.322));				
	trace("---------");
	trace("Cuba1 (areal) 						: " + Map_GetRealCoordX(-358.027) + " " + Map_GetRealCoordZ(819.223));				
	trace("Сантьяго 							: " + Map_GetRealCoordX(-339.796) + " " + Map_GetRealCoordZ(771.839));					
	trace("Пуэрто-Принсипе 						: " + Map_GetRealCoordX(-282.032) + " " + Map_GetRealCoordZ(839.056));					
	trace("Shore11 (мыс Камагуэй)				: " + Map_GetRealCoordX(-386.907) + " " + Map_GetRealCoordZ(883.044));				
	trace("Shore12 (залив Анна Мария)			: " + Map_GetRealCoordX(-468.486) + " " + Map_GetRealCoordZ(838.497));				
	trace("Mayak9 (маяк Сантьяго)				: " + Map_GetRealCoordX(-333.295) + " " + Map_GetRealCoordZ(723.486));				
	trace("---------");
	trace("Cuba2 (areal) 						: " + Map_GetRealCoordX(-640.61) + " " + Map_GetRealCoordZ(870.058));					
	trace("Гавана 								: " + Map_GetRealCoordX(-663.685) + " " + Map_GetRealCoordZ(913.862));					
	trace("Shore13 (залив Батабано)				: " + Map_GetRealCoordX(-613.56) + " " + Map_GetRealCoordZ(886.009));				
	trace("Shore14 (бухта Хувентуд)				: " + Map_GetRealCoordX(-653.269) + " " + Map_GetRealCoordZ(871.013));				
	trace("Shore15 (мыс Сан Антонио)			: " + Map_GetRealCoordX(-715.129) + " " + Map_GetRealCoordZ(797.212));				
	trace("Mayak10 (маяк Гаваны)				: " + Map_GetRealCoordX(-647.18) + " " + Map_GetRealCoordZ(925.046));				
	trace("---------");
	trace("Tortuga (island) 					: " + Map_GetRealCoordX(102.328) + " " + Map_GetRealCoordZ(852.912));				
	trace("Тортуга 								: " + Map_GetRealCoordX(116.875) + " " + Map_GetRealCoordZ(817.942));				
	trace("Shore58 (пляж Глаз Рыбы)				: " + Map_GetRealCoordX(131.064) + " " + Map_GetRealCoordZ(849.44));				
	trace("Mayak6 (маяк Тортуги)				: " + Map_GetRealCoordX(103.23) + " " + Map_GetRealCoordZ(812.356));				
	trace("---------");
	trace("Trinidad (island)					: " + Map_GetRealCoordX(889.76) + " " + Map_GetRealCoordZ(-774.746));				
	trace("Порт-оф-Спейн 						: " + Map_GetRealCoordX(848.282) + " " + Map_GetRealCoordZ(-822.588));				
	trace("Shore59 (бухта Скарборо)				: " + Map_GetRealCoordX(937.322) + " " + Map_GetRealCoordZ(-737.478));				
	trace("Shore60 (мыс Галера)					: " + Map_GetRealCoordX(906.25) + " " + Map_GetRealCoordZ(-757.928));				
	trace("Mayak1 (маяк Тринидада и Тобаго)		: " + Map_GetRealCoordX(821.24) + " " + Map_GetRealCoordZ(-847.69));				
	trace("---------");
	trace("Nevis (island)						: " + Map_GetRealCoordX(681.595) + " " + Map_GetRealCoordZ(256.013));				
	trace("Чарльзтаун 							: " + Map_GetRealCoordX(658.918) + " " + Map_GetRealCoordZ(241.972));				
	trace("Shore42 (бухта Ньюкасл)				: " + Map_GetRealCoordX(690.047) + " " + Map_GetRealCoordZ(291.621));					
	trace("Shore43 (пляж Бат)					: " + Map_GetRealCoordX(684.026) + " " + Map_GetRealCoordZ(212.793));					
	trace("Mayak5 (маяк Невиса)					: " + Map_GetRealCoordX(663.418) + " " + Map_GetRealCoordZ(228.281));					
	trace("---------");
	trace("Hispaniola1 (areal) 					: " + Map_GetRealCoordX(198.977) + " " + Map_GetRealCoordZ(588.696));					
	trace("Санто-Доминго 						: " + Map_GetRealCoordX(198.683) + " " + Map_GetRealCoordZ(547.97));					
	trace("Ла-Вега 								: " + Map_GetRealCoordX(166.708) + " " + Map_GetRealCoordZ(662.952));					
	trace("Shore32 (мыс Исабела)				: " + Map_GetRealCoordX(130.591) + " " + Map_GetRealCoordZ(682.362));						
	trace("Shore33 (бухта Самана)				: " + Map_GetRealCoordX(229.081) + " " + Map_GetRealCoordZ(593.727));						
	trace("Mayak8 (маяк Санто-Доминго)			: " + Map_GetRealCoordX(168.314) + " " + Map_GetRealCoordZ(520.218));						
	trace("---------");
	trace("Hispaniola2 (areal) 					: " + Map_GetRealCoordX(-47.1762) + " " + Map_GetRealCoordZ(625.596));					
	trace("Порт-о-Пренс 						: " + Map_GetRealCoordX(22.521) + " " + Map_GetRealCoordZ(592.233));					
	trace("Shore34 (бухта Гонаив)				: " + Map_GetRealCoordX(0.999614) + " " + Map_GetRealCoordZ(643.122));							
	trace("Mayak7 (маяк Порт-о-Пренса)			: " + Map_GetRealCoordX(-14.9756) + " " + Map_GetRealCoordZ(606.258));						
	trace("---------");
	trace("Dominica 							: " + Map_GetRealCoordX(783.057) + " " + Map_GetRealCoordZ(-256.833));					
	trace("Shore27 (мыс Скотс Хед)				: " + Map_GetRealCoordX(779.89) + " " + Map_GetRealCoordZ(-295.002));								
	trace("Shore26 (пляж Касл Брус)				: " + Map_GetRealCoordX(803.577) + " " + Map_GetRealCoordZ(-252.617));								
	trace("---------");
	trace("Теркс 								: " + Map_GetRealCoordX(443.257) + " " + Map_GetRealCoordZ(939.102));						
	trace("Shore57 (залив Южный)				: " + Map_GetRealCoordX(434.944) + " " + Map_GetRealCoordZ(923.524));								
	trace("Shore56 (залив Северный)				: " + Map_GetRealCoordX(444.298) + " " + Map_GetRealCoordZ(954.975));								
	trace("---------");
	trace("Кайман 								: " + Map_GetRealCoordX(-489.6) + " " + Map_GetRealCoordZ(362.455));						
	trace("Shore17 (залив Эсмеральды)			: " + Map_GetRealCoordX(-505.038) + " " + Map_GetRealCoordZ(348.115));									
	trace("Shore16 (Пустынный пляж)				: " + Map_GetRealCoordX(-449.837) + " " + Map_GetRealCoordZ(366.308));
	trace("---------");
	trace("Panama (areal) 						: " + Map_GetRealCoordX(-395.198) + " " + Map_GetRealCoordZ(-972.801));							
	trace("Панама 								: " + Map_GetRealCoordX(-389.965) + " " + Map_GetRealCoordZ(-949.118));							
	trace("Shore63 (залив Сан Мигель) 			: " + Map_GetRealCoordX(-328.166) + " " + Map_GetRealCoordZ(-1023.72));
	trace("---------");
	trace("PortoBello (areal) 					: " + Map_GetRealCoordX(-435.73) + " " + Map_GetRealCoordZ(-895.763));							
	trace("Порто-Белло 							: " + Map_GetRealCoordX(-427.183) + " " + Map_GetRealCoordZ(-907.277));
	trace("Shore46 (лагуна Чирики)				: " + Map_GetRealCoordX(-627.474) + " " + Map_GetRealCoordZ(-940.853));
	trace("Shore47 (залив Москитос)				: " + Map_GetRealCoordX(-486.49) + " " + Map_GetRealCoordZ(-976.966));
	trace("Shore48 (Дарьенский залив)			: " + Map_GetRealCoordX(-279.316) + " " + Map_GetRealCoordZ(-1005.49));
	trace("---------");
	trace("Cartahena (areal) 					: " + Map_GetRealCoordX(-51.2104) + " " + Map_GetRealCoordZ(-851.77));								
	trace("Картахена 							: " + Map_GetRealCoordX(-26.7669) + " " + Map_GetRealCoordZ(-872.535));								
	trace("Shore25 (бухта Ковеньяс)				: " + Map_GetRealCoordX(-115.589) + " " + Map_GetRealCoordZ(-937.387));
	trace("Mayak11 (маяк Картахены)				: " + Map_GetRealCoordX(-65.6347) + " " + Map_GetRealCoordZ(-842.072));
	trace("---------");
	trace("Caracas (areal) 						: " + Map_GetRealCoordX(435.126) + " " + Map_GetRealCoordZ(-936.197));								
	trace("Каракас 								: " + Map_GetRealCoordX(440.684) + " " + Map_GetRealCoordZ(-960.339));
	trace("Shore21 (мыс Аруба)					: " + Map_GetRealCoordX(410.688) + " " + Map_GetRealCoordZ(-913.531));
	trace("---------");
	trace("Cumana (areal) 						: " + Map_GetRealCoordX(767.999) + " " + Map_GetRealCoordZ(-936.266));								
	trace("Кумана 								: " + Map_GetRealCoordX(691.343) + " " + Map_GetRealCoordZ(-896.619));								
	trace("Shore20 (пляж Лос Текес)				: " + Map_GetRealCoordX(574.327) + " " + Map_GetRealCoordZ(-929.042));
	trace("Shore19 (бухта Карупано)				: " + Map_GetRealCoordX(768.622) + " " + Map_GetRealCoordZ(-914.469));
	trace("Shore18 (берег Бока де ла Сьерпе)	: " + Map_GetRealCoordX(924.423) + " " + Map_GetRealCoordZ(-969.921));
	trace("---------");
	trace("SantaCatalina (areal) 				: " + Map_GetRealCoordX(-742.269) + " " + Map_GetRealCoordZ(-563.205));									
	trace("Санта-Каталина 						: " + Map_GetRealCoordX(-769.375) + " " + Map_GetRealCoordZ(-537.051));
	trace("Shore53 (Берег Москитов)				: " + Map_GetRealCoordX(-792.718) + " " + Map_GetRealCoordZ(-331.728));
	trace("Shore54 (мыс Перлас)					: " + Map_GetRealCoordX(-760.343) + " " + Map_GetRealCoordZ(-484.106));
	trace("Shore55 (залив Сан Хуан дель Норте)	: " + Map_GetRealCoordX(-736.763) + " " + Map_GetRealCoordZ(-756.295));
	trace("---------");
	trace("ГПК									: " + Map_GetRealCoordX(-938.667) + " " + Map_GetRealCoordZ(938.654));										
	trace("---------");
	trace("Teno (areal)							: " + Map_GetRealCoordX(-966.062) + " " + Map_GetRealCoordZ(-294.232));										
	trace("Теночтитлан 							: " + Map_GetRealCoordX(-969.194) + " " + Map_GetRealCoordZ(-305.237));										
	trace("Shore61 (Тепейакак) 					: " + Map_GetRealCoordX(-955.553) + " " + Map_GetRealCoordZ(-281.197));
	trace("Shore62 (Истапалапу)					: " + Map_GetRealCoordX(-935.811) + " " + Map_GetRealCoordZ(-316.162));
	trace("---------");	
}
string arrayNPCModel[128];
int    arrayNPCModelHow; // для рандомизации моделей в одной локации

// создаем горожан в локацию + солдаты, фантомы-многодневки (живут 48ч) переработка boal 13.05.06
void CreateCitizens(aref loc)
{
	if(loc.type != "town" && loc.type != "church" && loc.type != "residence") return; //городской генератор не должен отрабатывать везде
	
	if(LAi_IsCapturedLocation) // fix нефиг грузить, когда город трупов или боевка
	{
		return;
	}
	int iColony = -1;
	int iNation = -1;

	if(isLocationHasCitizens(loc.id)) return; // boal  если есть еще с того раза, но не нужно
	
	if(CheckAttribute(loc, "fastreload"))
	{
		iColony = FindColony(loc.fastreload);
	}
	if(iColony == -1)
	{
		return;
	}
	
	iNation = GetCityNation(loc.fastreload);
	
	if(iNation == -1)
	{
		return;
	}

	int iCitizensQuantity, iModel;
	ref chr, sld;
	int iChar, i, iSex;
	int iSailorQty, iNobleQty, iOldWomanQty;
	bool bOk;
	string slai_group, locatorName, sType, sFraction;
    slai_group = GetNationNameByType(iNation)  + "_citizens";
	arrayNPCModelHow = 0;
	
	// "Моряки желают развлечений" (Event) -->
	bOk = !CheckAttribute(pchar, "Event.SailorBrothel") || GetQuestPastMonthParam("Event.SailorBrothel") > 1; // не чаще раза в пару месяцев
	if(loc.type == "town" && pchar.location.from_sea == Colonies[iColony].from_sea && sti(pchar.ship.crew.quantity) > 6 && FindLocation(Colonies[iColony].id + "_brothel") != -1 
	&& GetRelation2BaseNation(iNation) != RELATION_ENEMY && ChangeCharacterNationReputation(pchar, iNation, 0) > -15 && GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY
	&& !chrDisableReloadToLocation && !LAi_grp_alarmactive && bOk && !CheckAttribute(CharacterFromID(Colonies[iColony].id + "_Hostess"), "SailorEvent_Block")
	&& pchar.location.locator == "reload1") //&& dRandEx(10, false) == 1
	{
		if(!CheckAttribute(&TEV, "SB_Counter")) TEV.SB_Counter = 1; //для диалогов
		else TEV.SB_Counter = 2;
		
		PChar.Event.SailorEvent.City = Colonies[iColony].id;
		PChar.Event.SailorEvent.MassagePrice = 5000 + dRandEx(5, false)*1000;
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(loc, true);
		SaveCurrentQuestDateParam("Event.SailorBrothel"); //для даты именно SailorBrothel, а не SailorEvent, который потом затирается
		
		for (i = 1; i < 4; i++)
		{
			chr = GetCharacter(NPC_GenerateCharacter("Sailor_" + i, "sailor_" + (rand(15) + 1), "man", "man", sti(pchar.rank), sti(pchar.nation), -1, true, F_SAILOR));
			SetNPCModelUniq(chr, "sailor", MAN);
			ChangeCharacterAddressGroup(chr, loc.id, "quest", "quest1");
			chr.dialog.filename    = "Events/SailorEvent.c";
			chr.dialog.currentnode = "sailor_pier1";
			chr.greeting = ""; //to_do
			LAi_SetActorType(chr);
			if(i != 3) LAi_ActorFollow(chr, pchar, "", -1);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		}
		LAi_ActorDialog(chr, pchar, "SailorEvent_TurnToKatya", -1, 0);
	}
	// <-- "Моряки желают развлечений" (Event)
	
	// нищие -->
	if (loc.type == "town")
	{
		int iPoorIdx = GetCharacterIndex(colonies[iColony].id + "_Poorman");
		if (iPoorIdx != -1)
		{
			if (rand(1)) 
			{
				characters[iPoorIdx].PoorSit = true;
				sType = "locator" + rand(2);
				locatorName = characters[iPoorIdx].forSit.(sType);
			}
			else 
			{ 
				DeleteAttribute(&characters[iPoorIdx], "PoorSit");
				locatorName = characters[iPoorIdx].forStay.locator;
			}
			LAi_SetPoorTypeNoGroup(&characters[iPoorIdx]);
			if (LAi_CheckLocatorFree("goto", locatorName))
				ChangeCharacterAddressGroup(&characters[iPoorIdx], loc.id, "goto", locatorName);
			else
				PlaceCharacter(&characters[iPoorIdx], "patrol", "random_free");

		}
	}
	// нищие <--

    // горожане -->	
	
	// Rebbebion, разделение по фракциям (взял из ККС)
	iSailorQty = rand(2) + 2;
	iNobleQty = rand(2) + 1;
	iOldWomanQty = rand(1) + 1;
	if (loc.type == "church")
	{
		iSailorQty = 0;
		iNobleQty = 0;
		iOldWomanQty = 0;
	}
    
	if (checkAttribute(loc, "citizens") || loc.type == "church")
	{
		// гуляющие матросы
		if (iNation != PIRATE || sti(Colonies[iColony].HeroOwn) == true) // в пиратских поселениях и собственных колониях уникальных статиков не будет
		{
			for (i = 1; i < iSailorQty; i++)
			{
				iSex = MAN;
				sType = "sailor";
				iChar = NPC_GeneratePhantomCharacter("sailor", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename    = "Fractions\Sailor.c";
				chr.dialog.currentnode = "First time";
				// рандомно заговорит и предложит наняться в команду
				if (rand(5) == 1 && sti(pchar.ship.type) != SHIP_NOTUSED)
				{
					chr.quest.crew = "true";
					chr.quest.crew.qty = 5 + rand(15);
					chr.quest.crew.type = rand(2);
					chr.quest.crew.money = (1 + rand(1)) * 100 + rand(50);
					chr.talker = rand(9);
				}
			}
			
			for (i = 1; i < iNobleQty; i++) // дворяне
			{
				iSex = rand(WOMAN);
				sType = "noble";
				iChar = NPC_GeneratePhantomCharacter("noble", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename = "Fractions\Noble.c";
				chr.dialog.currentnode = "First time";
			}
			
			for (i = 1; i < iOldWomanQty; i++) // старухи
			{
				iSex = WOMAN;
				sType = "oldwoman";
				iChar = NPC_GeneratePhantomCharacter("oldwoman", iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				PlaceCharacter(chr, "goto", "random_free");
				chr.dialog.filename = "Common_citizen.c";
				chr.dialog.currentnode = "First time";
			}
		}
		iCitizensQuantity = rand(8) + 6;
		if (loc.type == "church")  iCitizensQuantity = rand(6) + 2;
		
		if(CheckAttribute(loc, "MaxCitizensQuantity")) 
	    {
			if(iCitizensQuantity > sti(loc.MaxCitizensQuantity)) iCitizensQuantity = sti(loc.MaxCitizensQuantity);
        }

		for(i=0; i<iCitizensQuantity; i++)
		{
			if(iNation != PIRATE || sti(Colonies[iColony].HeroOwn) == true)
			{
			    // пусть нормальные горожане будут тоже, куда без жителей? солдаты == пираты - это да
                if (loc.type == "church") iSex = MAN;
				else iSex = rand(WOMAN);
                sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);
			}
			else
			{
                iSex = MAN;
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, iSex, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, iSex);
			
			chr.City = Colonies[iColony].id;
			chr.CityType = "citizen";
			LAi_SetLoginTime(chr, 6.0, 21.99);
			
			if (sti(chr.nation) == PIRATE && sti(Colonies[iColony].HeroOwn) != true)
			{
				LAi_SetWarriorType(chr);
				LAi_warrior_DialogEnable(chr, true);
				chr.watchBoxes = true;
			}
			else
			{
				if (loc.type == "church" && chr.sex == "man")
				{
				    LAi_SetSitType(chr);
				}
				else
				{
					LAi_SetCitizenType(chr);
				}
			}

			if (LAi_IsCapturedLocation)  // to_do трупы на земле, пока не работет, тк суда не доходит
			{
				chr.location.loadcapture = 1;
				LAi_SetActorType(chr);
				LAi_ActorSetLayMode(chr);
				LAi_SetImmortal(chr, 1);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			}
			else
			{
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
            if (loc.type == "church" && chr.sex == "man")
            {
                PlaceCharacter(chr, "sit", "random_free");
            }
            else
			{
				PlaceCharacter(chr, "goto", "random_free");
			}
			if (loc.type == "church")
			{
				chr.dialog.filename    = "Enc_Walker.c";
				chr.nonTable = true;
			}
			else
			{
				chr.dialog.filename    = "Common_citizen.c";
			}
			chr.dialog.currentnode = "first time";

			if(sti(chr.nation) == PIRATE && sti(Colonies[iColony].HeroOwn) != true)
			{
				chr.greeting = "pirat_common";
			}
			else
			{
				if(chr.sex == "man")
				{
					chr.greeting = "cit_common";
				}
				else
				{
					chr.greeting = "Gr_Woman_Citizen";
				}
			}
		}
	}
	// горожане <--
	
    // торговцы -->
	aref st;
	if (checkAttribute(loc, "locators.merchant"))
	{
		makearef(st, loc.locators.merchant);
		iCitizensQuantity = GetAttributesNum(st) / 2;
		for (i=0; i<iCitizensQuantity; i++)
		{
			//eddy. пусть не только мужики торгуют
			iSex = rand(1);
			iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 2);

			chr = &characters[iChar];
			SetNPCModelUniq(chr, "citizen", iSex);
			
			chr.City = Colonies[iColony].id;
			chr.CityType = "citizen";
			chr.Merchant = true; // Флаг "торговец"
			LAi_SetLoginTime(chr, 7.0, 20.0);

			//PlaceCharacter(chr, "merchant", "random");
			ChangeCharacterAddressGroup(chr, loc.id, "merchant", "merchant"+(i+1));
			LAi_SetMerchantType(chr);
			chr.dialog.filename = "Common_ItemTrader.c";
			chr.dialog.currentnode = "first time";
			if (chr.sex == "man") chr.greeting = "tra_common";
			else chr.greeting = "tra_woman_common";			
   			if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	} 
	// торговцы <--	
	
	// солдаты -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		aref soldierLoc;
		makearef(st, loc.locators.soldiers);
		iCitizensQuantity = GetAttributesNum(st);		
		for (i=0; i<iCitizensQuantity; i++)
		{
			if(iNation != PIRATE)
			{
				if (loc.type == "residence") sType = "veteran"; // Rebbebion, ветераны в резиденциях
				else sType = "soldier";
			}
			else sType = "pirate";
			
			iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля :)

			soldierLoc = GetAttributeN(st, i);
			locatorName = GetAttributeName(soldierLoc);
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
			// eddy. проверяем, должен ли солдат быть протектором -->
			if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
			{
				chr.protector = true;
				chr.greeting = "soldier_arest";
			}
			else chr.greeting = "soldier_common";
			// <-- eddy. проверяем, должен ли солдат быть протектором
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			
			LAi_SetGuardianType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	// солдаты <--
	// патруль -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		iCitizensQuantity = GetAttributesNum(st);
		if(iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
			if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";

			LAi_SetPatrolType(chr);
			
            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				chr.greeting = "soldier_common";
			}
			PlaceCharacter(chr, "patrol", "random_free");
		}
		//мушкетеры
		for (i=1; i<=3; i++)
		{
			if(iNation == PIRATE)
			{
                sType = "mush_pir_" + (rand(5) + 1);
			}
			else
			{
                sType = "mush_" + NationShortName(iNation) + "_" + (rand(4) + 1);
			}
			
			if(iNation == PIRATE)
			{
                sFraction = F_PIRATE;
			}
			else
			{
                sFraction = F_MILITARY;
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false, sFraction));
			chr.id = "GenChar_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.greeting = "soldier_common";
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			LAi_SetLoginTime(chr, 0.0, 24.0); //а ночью будет беготня от патруля :)

			PlaceCharacter(chr, "patrol", "random_free");

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";				

			LAi_SetPatrolType(chr);
			
            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	// патруль <--
	
	//Экку Korsar - Статичные мушкетеры-стражи в новых локаторах
    if(CheckAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.mushketer"))
	{
		makearef(st, loc.locators.mushketer);
	    iCitizensQuantity = GetAttributesNum(st);
        for (i=1; i <= iCitizensQuantity; i++)
	    {
			if(iNation == PIRATE)
			{
                sType = "mush_pir_" + (rand(5) + 1);
			}
			else
			{
                sType = "mush_" + NationShortName(iNation) + "_" + (rand(4) + 1);
			}
				
			chr = GetCharacter(NPC_GenerateCharacter(loc.id + "_mush_"+i, sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false, F_MILITARY));
			//chr.id = "GenChar_" + chr.index; // Одноглазый - Айди для мушкетеров уникальные (Нужно для фичи ниже)
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
				
			if(chr.nation == PIRATE)
			{
			    chr.greeting = "town_pirate";
			}
			else
			{
				chr.greeting = "soldier";
			}
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
   	        SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			LAi_SetLoginTime(chr, 0.0, 24.0); //а ночью будет беготня от патруля :)
			
			chr.MusketerDistance = 0; // Что-бы стояли на месте статично
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";				
			LAi_SetGuardianType(chr);
			
			
			//Одноглазый - Костыльное копирование внешности мушкетеру Ла Веги (Чтобы был типо один человек ина входе в город, и в самом городе) -->
			if(loc.id == "LaVega_ExitTown" && i == 3)
			{
				if(GetCharacterIndex("LaVega_Town_mush_1") != -1)
				{
					sld = characterFromID("LaVega_Town_mush_1");
					if(CheckAttribute(sld, "CopyFrom") && !CheckAttribute(chr, "CopyFrom"))
					{
						chr.model = sld.model;
						chr.name = sld.name;
						chr.lastname = sld.lastname;
						chr.faceid = sld.faceid;
						chr.reputation = sti(sld.reputation);
					}
				}
				else
				{
					chr.CopyFrom = true;
				}
			}
			
			if(loc.id == "LaVega_Town" && i == 1)
			{
				if(GetCharacterIndex("LaVega_ExitTown_mush_3") != -1)
				{
					sld = characterFromID("LaVega_ExitTown_mush_3");
					if(CheckAttribute(sld, "CopyFrom") && !CheckAttribute(chr, "CopyFrom"))
					{
						chr.model = sld.model;
						chr.name = sld.name;
						chr.lastname = sld.lastname;
						chr.faceid = sld.faceid;
						chr.reputation = sti(sld.reputation);
					}
				}
				else
				{
					chr.CopyFrom = true;
				}
			}
			//<--
			
			ChangeCharacterAddressGroup(chr, pchar.location, "mushketer", "mushketer"+i);
		
       	    if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	
	// Rebbebion, тяжёлая пехота (протекторы)
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.EliteProtector"))
	{
		makearef(st, loc.locators.EliteProtector);
		iCitizensQuantity = GetAttributesNum(st);
		
		if (iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		
		for (i = 0; i < iCitizensQuantity; i++)
		{
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "sold_" + NationShortName(iNation) + "_" + (rand(7) + 9), "man", "man", sti(pchar.rank), iNation, 2, false, F_MILITARY));
			chr.id = "GenChar_" + chr.index;
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			chr.greeting = "soldier_common";
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE * 2, true); // бравые орлы
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE + 4); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "EliteProtector", "random_free");

			LAi_SetGuardianType(chr);
			
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	
	// Rebbebion, тяжёлая пехота
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.PatrolElite"))
	{
		makearef(st, loc.locators.PatrolElite);
		iCitizensQuantity = GetAttributesNum(st);
		
		if (iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		
		// пешие солдаты
		for (i = 0; i < iCitizensQuantity - 3; i++)
		{
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "sold_" + NationShortName(iNation) + "_" + (rand(7) + 9), "man", "man", sti(pchar.rank), iNation, 2, false, F_MILITARY));
			chr.id = "GenChar_" + chr.index;
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			chr.greeting = "soldier_common";
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE * 2, true); // бравые орлы
			chr.RebirthPhantom = true; 
			chr.PatrolElite = true; // для хождения только по заданным локаторам
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE + 4); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "PatrolElite", "random_free");

			LAi_SetPatrolType(chr);
			
			LAi_group_MoveCharacter(chr, slai_group);
		}
		
		// мушкетёры
		for (i = 1; i <= 2; i++)
		{
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "mush_" + NationShortName(iNation) + "_" + (rand(4) + 6), "man", "mushketer", sti(pchar.rank), iNation, 2, false, F_MILITARY));
			chr.id = "GenChar_" + chr.index;
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			chr.greeting = "soldier_common";
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
			chr.RebirthPhantom = true;
			chr.PatrolElite = true; // для хождения только по заданным локаторам
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE + 4); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "PatrolElite", "random_free");

			LAi_SetPatrolType(chr);
			
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	
	// Rebbebion, стража генерал-губернатора Гаваны
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.HGuardProtector"))
	{
		makearef(st, loc.locators.HGuardProtector);
		iCitizensQuantity = GetAttributesNum(st);
		
		if (iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		
		for (i = 0; i < iCitizensQuantity; i++)
		{
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "sold_havana_" + (rand(5) + 1), "man", "man", sti(pchar.rank), iNation, 2, false, F_MILITARY));
			chr.id = "GenChar_" + chr.index;
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			chr.greeting = "soldier_common";
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE * 2, true); // бравые орлы
			chr.RebirthPhantom = true; 
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE + 4); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "HGuardProtector", "random_free");

			LAi_SetGuardianType(chr);
			
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	
	// Rebbebion, патруль генерал-губернатора Гаваны
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.HGuardPatrol"))
	{
		makearef(st, loc.locators.HGuardPatrol);
		iCitizensQuantity = GetAttributesNum(st);
		
		if (iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		
		for (i = 0; i < iCitizensQuantity - 1; i++)
		{
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "sold_havana_" + (rand(5) + 1), "man", "man", sti(pchar.rank), iNation, 2, false, F_MILITARY));
			chr.id = "GenChar_" + chr.index;
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			chr.greeting = "soldier_common";
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE * 2, true); // бравые орлы
			chr.RebirthPhantom = true; 
			chr.HGuardPatrol = true; // для хождения только по заданным локаторам
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE + 4); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "HGuardPatrol", "random_free");

			LAi_SetPatrolType(chr);
			
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	
	//Посидельцы в порту Ла-Веги
	string sHabType;
	if(loc.id == "Lavega_Port" && CheckAttribute(loc, "locators.sit"))
	{
		makearef(st, loc.locators.sit);
	    iCitizensQuantity = GetAttributesNum(st);
		for (i=1; i <= rand(iCitizensQuantity); i++)
		{
			if (CheckFreeLocator(loc.id, "Fire" + i, -1))
			{
               	if(iNation == PIRATE)
				{
					sHabType = "pirate";
				}
               	else
				{
					sHabType = RandPhraseSimple("soldier","sailor");
				}
				iChar = NPC_GeneratePhantomCharacter(sHabType, iNation, MAN, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sHabType, MAN);
				
				FaceMaker(chr);
				
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.standUp = true; //Встать и напасть в случае алярма.
				ChangeCharacterAddressGroup(chr, loc.id, "sit", "fire" + i);
				if(rand(1))
				{
					LAi_SetLoginTime(chr, 18.0+rand(5), 0.0);
			    }
				else
				{
					if(rand(1)) LAi_SetLoginTime(chr, 0.0, 1.0+(rand(5)));
					else LAi_SetLoginTime(chr, 0.0 + rand(6), 12.0 + rand(12));
				}
				LAi_SetGroundSitType(chr);
				LAi_CharacterDisableDialog(chr);
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
		}
	}
	
	// посидельцы в Ла-Веге
	if(loc.id == "LaVega_town" && CheckAttribute(loc, "locators.sit"))
	{
		makearef(st, loc.locators.sit);
		for (i=1; i <= rand(5); i++)
		{
			if (CheckFreeLocator(loc.id, "sit" + i, -1))
			{
               	if(iNation == PIRATE)
				{
					sHabType = RandPhraseSimple("pirate","sailor");
					iChar = NPC_GeneratePhantomCharacter(sHabType, iNation, MAN, 2);
				}
               	else
				{
					sHabType = RandPhraseSimple("soldier","sailor");
					iChar = NPC_GeneratePhantomCharacter(sHabType, iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sHabType, MAN);
				
				FaceMaker(chr);
				
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.standUp = true; //Встать и напасть в случае алярма.
				ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit" + i);
				LAi_SetLoginTime(chr, 0.0 + rand(6), 12.0 + rand(12));
				LAi_SetSitType(chr);
				chr.dialog.filename = "Habitue_dialog.c";
				chr.dialog.currentnode = "First time";
                chr.greeting = "habitue";
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
		}
	}
	
	// грузчики -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[7];
		locReload[0] = "reload4_back";
		locReload[1] = "reload5_back";
		locReload[2] = "reload6_back";
		locReload[3] = "reload7_back";
		locReload[4] = "reload8_back";
		locReload[5] = "reload10_back";
		locReload[6] = "reload9_back";
		string CarrierName[10];
		CarrierName[0] = "GenresBag1";
		CarrierName[1] = "GenresBag2";
		CarrierName[2] = "GenresBarrel1";
		CarrierName[3] = "GenresBarrel2";
		CarrierName[4] = "GenresBarrelTop1";
		CarrierName[5] = "GenresBarrelTop2";
		CarrierName[6] = "GenresBottle1";
		CarrierName[7] = "GenresBottle2";
		CarrierName[8] = "GenresChest1";
		CarrierName[9] = "GenresChest2";
		for (i=iQtyCarrier; i>0; i--)
		{
			//выберем уникальную для этой локации модельку
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(9);
				if (CarrierName[iTemp] != "") iSex = 0;
			}
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, iNation, 2, false, F_TRADER));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			CarrierName[iTemp] = ""; //имя модельки уберем из списка
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 7.0, 20.0);
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(6);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = frand(7) + 4.0;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// грузчики <--
}

// плодим завсегдатеев в таверну, тоже фантомы-многоджневки (24ч) переработка boal 13.05.06
void CreateHabitues(aref loc)
{
	int iColony = -1;
	int iNation = -1;
	
	if (!checkAttribute(loc, "habitues")) return;
	if(LAi_IsCapturedLocation) return;
	
	OfficersReactionResult(); // уход офов в местах, где есть пьянь и др офы - пока это таверна

	if (!isLocationHasCitizens(loc.id))  // boal  если есть еще с того раза, но не нужно
	{
		if (CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);

			if(iColony == -1)
			{
				return;
			}

			iNation = GetCityNation(loc.fastreload);

			if (iNation == -1)
			{
				return;
			}

			string sColony = loc.fastreload;
			int iCitizensQuantity, iModel;
			ref chr;
		    string slai_group;
			int iChar;
			int i, n, k;
			string sTemp;

			slai_group = GetNationNameByType(iNation)  + "_citizens";

            arrayNPCModelHow = 0;
			// сажаем пьянь, на козырные места под ГГ
			for (i = 1; i <=4; i++)
			{
                if (CheckFreeLocator(loc.id, "sit_base" + i, -1))
				{
					// Rebbebion, в тавернах колоний сидят матросы с пьяницами, у пиратов же - только пираты (obviously, lol :D)
					string sType = RandPhraseSimple("drunkard", "sailor");
					if (Colonies[iColony].nation == PIRATE) sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);

					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, MAN);
					
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn) == true)
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Tavern_Mate";
				}
			}
			iChar = GetCharacterIndex(Colonies[iColony].id + "_Smuggler");
			if (iChar != -1) // у пиратов нет вообще - это статики
			{
		        chr = &characters[iChar];
				if (sti(Colonies[iColony].HeroOwn) != true)
				{ // грузим контрикова агента, он статик, но локацию и локатор ставим тут
		            chr.City = Colonies[iColony].id;  // это можно прописать в статике, но мне лениво по 20 городам лазить.
		            chr.nation = iNation; // нация его нужна, тк она будет нацией патруля на берегу, он не пират
					CreateModel(iChar, "smuggler", MAN);
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);
					LAi_group_MoveCharacter(chr, slai_group);
				}
				else
				{
				    ChangeCharacterAddressGroup(chr, "none", "none", "none");
				}
				// вне группы
			}
			// аганты наций и контриков, только в пиратских тавернах -->
			if (iNation == PIRATE && sti(Colonies[iColony].HeroOwn) != true)
			{
				iChar = NPC_GeneratePhantomCharacter("citizen", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "citizen", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
				ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetSitType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				chr.Name = "Дипломат";
				chr.LastName = "";
				chr.dialog.filename = "RelationAgent_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_RelationAgent";
				LAi_group_MoveCharacter(chr, slai_group);
			}
			// аганты наций и контриков, только в пиатских тавернах <--
			// офицеры -->
			iCitizensQuantity = rand(6) - 3;
			for (i = 0; i <iCitizensQuantity; i++)
			{
			    iChar = NPC_GeneratePhantomCharacter("pofficer", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "pofficer", MAN);
				SetOfficerParam(chr, rand(4));
				sTemp = PlaceCharacter(chr, "sit", "random_free");
				ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetSitType(chr);
				// без группы
				chr.dialog.filename = "Enc_Officer_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_Officer";
    			if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// офицеры <--
			
			iCitizensQuantity = rand(3) - 1 ; // простая пьянь для антуражу
			for (i = 0; i <iCitizensQuantity; i++)
			{
			    iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
                ReSitCharacterOnFree(chr, loc.id, sTemp);

				LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
				LAi_SetSitType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				chr.dialog.filename = "Habitue_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_Tavern_Mate";
			}
		}
	}
	//navy -- ПГГ в таверне.
	//Это метод вызывается при каждом заходе в таверну...
	//PGG_TavernCheckIsPGGHere();
}

// заполнение инквизиции. eddy
void CreateIncquisitio(aref loc)
{	
	if (GetCityNation("Santiago") != SPAIN) return; 
	
	if (CheckAttribute(loc, "Incquisitio"))
	{
		ref sld;
		string LocatorGroup, LocatorName;
		int i, nSit;
		//====> накидаем священников
		if (CheckNPCQuestDate(loc, "Incquisitor_date"))
		{
			SetNPCQuestDate(loc, "Incquisitor_date");
			LocatorGroup = "goto";
			nSit = rand(2)+1;
			for (i=1; i<=3; i++)
			{
				LocatorGroup = "goto";
				LocatorName = LAi_FindRandomLocator("goto");				 
				if (i==nSit) 
				{
					LocatorGroup = "sit";
					LocatorName = "sit"+(rand(3)+1);			
				}
				sld = GetCharacter(NPC_GenerateCharacter("Incquisitor_"+i, "jesuit_1", "man", "man", 20, SPAIN, 1, false, F_CATHOLICS));
				sld.Dialog.Filename = "Incquistors.c";									
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (i==nSit) LAi_SetSitType(sld);
				else LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", LocatorGroup, LocatorName);
			}
		}
		//====> накидаем солдат.
		if (CheckNPCQuestDate(loc, "Guard_date"))
		{
			SetNPCQuestDate(loc, "Guard_date");
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("IncqGuard_"+i, "sold_spa_1", "man", "man", 35, SPAIN, 1, true, F_MILITARY));
				sld.City = "Santiago";
				sld.CityType = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15, 100, 90, BLADE_LONG, "pistol3", "bullet", 100);//спецназ
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
				locatorName = PlaceCharacter(sld, "soldiers", "random");
				// eddy. проверяем, должен ли солдат быть протектором -->				
				if (locatorName == "soldier1" || locatorName == "soldier2")
				{
					sld.protector.CheckAlways = true; //проверять всегда
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "soldier_arest";
				}
				else
				{
					if (findsubstr(locatorName, "protector" , 0) != -1) sld.protector = true;
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.greeting = "soldier_common";
				}
				// <-- eddy. проверяем, должен ли солдат быть протектором
			}
		}
		//====> накидаем заключенных, раз в месяц.
		if (!CheckAttribute(loc, "Prison_date") || GetNpcQuestPastDayParam(loc, "Prison_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "Prison_date");
			for (i=1; i<=8; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Prisoner_"+i, "pirate_" + (rand(15) + 1), "man", "man", 10, SPAIN, 30, false, F_SLAVE));							
					sld.Dialog.Filename = "Incquistors.c";
					sld.greeting = "Gr_prison";
					LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					if (rand(10)>5) LAi_ActorSetLayMode(sld);
					else 
					{
						LAi_SetGroundSitType(sld);
					}				
					//ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison"+i);
					PlaceCharacter(sld, "prison", "random_free");
				}
			}
		}
	}
}
//eddy. наполнение маяка
void CreateMayak(aref loc)
{
	if (loc.type == "mayak")
	{		
		if (!CheckAttribute(loc, "Mayak_date") || GetNpcQuestPastDayParam(loc, "Mayak_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Mayak_date");

			if(CheckAttribute(loc, "from_colony")) 
			{
				int iColony = FindColony(loc.from_colony);
			}
			else 
			{
				iColony = FindColony(GetCityNameByIsland(GiveArealByLocation(loc)));
			}
			if(iColony == -1) return;

			int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loc)));
			if(iNation == -1) return;

			int iCitizensQuantity, iModel;
			ref chr;
			aref st, soldierLoc;
			int iChar, i;
			string slai_group, locatorName;
			slai_group = GetNationNameByType(iNation)  + "_mayak"; 
			// солдаты -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
			{
				makearef(st, loc.locators.soldiers);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					soldierLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(soldierLoc);					
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{		
						iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
						chr = &characters[iChar];
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("GenChar_", "mush_eng_1", "man", "mushketer", sti(pchar.rank), iNation, 2, false, F_MILITARY));
						chr.id = "GenChar_" + chr.index;
						chr.MusketerDistance = 0;
					}					
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					chr.greeting = "soldier_common";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+6, true); // бравые орлы
					LAi_SetLoginTime(chr, 0.0, 24.0);
					soldierLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(soldierLoc);
					ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
					// eddy. проверяем, должен ли солдат быть протектором -->
					if (findsubstr(locatorName, "protector" , 0) != -1) 
					{
						chr.protector = true;
						chr.greeting = "soldier_arest";
						if (locatorName != "protector1" && locatorName != "protector2") 
						{
							chr.protector.CheckAlways = 1; //проверять всегда
							if (locatorName == "protector11") chr.dialog.currentnode = "PortRoyal_Mayak";
							else chr.dialog.currentnode = "PortRoyal_Gans";
						}
					}
					else chr.greeting = "soldier_common";
					// <-- eddy. проверяем, должен ли солдат быть протектором
					chr.dialog.filename = "Common_Soldier.c";
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// солдаты <--
			// патруль -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
			{
				makearef(st, loc.locators.patrol);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
					chr = &characters[iChar];
					chr.City = Colonies[iColony].id;
					chr.CityType = "soldier";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetPatrolType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier_common";
					PlaceCharacter(chr, "patrol", "random_free");
					chr.dialog.filename = "Common_Soldier.c";
					chr.dialog.currentnode = "first time";
				}
			}
			// патруль <--
			LAi_group_SetLookRadius(slai_group, 80);
			LAi_group_SetHearRadius(slai_group, 80);
		}
	}
}

void CreateBrothels(aref loc)
{
	if (CheckAttribute(loc, "brothel"))
	{
		ref location;
		if (findsubstr(loc.id, "SecBrRoom", 0) != -1)
		{
			location = &locations[FindLocation(loc.fastreload + "_Brothel")];
		}
		else
		{
			makeref(location, loc);
		}
		if (!CheckAttribute(location, "Brothel_date") || GetNpcQuestPastDayParam(location, "Brothel_date") > 100)
		{
			ref sld;
			int iColony, iNation, qty, num, qtyAll;
			// ==>  массив моделек шлюх, чтоб не двоились в локациях
			string horse[8];
			horse[0] = "whore_1";
			horse[1] = "whore_2";
			horse[2] = "whore_3";
			horse[3] = "whore_4";
			horse[4] = "whore_5";
			horse[5] = "whore_6";
			horse[6] = "whore_7";
			horse[7] = "whore_8";
			SaveCurrentNpcQuestDateParam(location, "Brothel_date");
			if(CheckAttribute(location, "fastreload"))
			{
				iColony = FindColony(location.fastreload);
			}
			else return;
			iNation = GetCityNation(location.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			qty = 1;
			qtyAll = rand(2) + 4;
			while (qty < qtyAll)
			{
				num = rand(7);
				if (horse[num] != "")
				{
					sld = GetCharacter(NPC_GenerateCharacter("HorseGen_"+location.index +"_"+ qty, horse[num], "woman", "towngirl", 3, iNation, 100, false, F_CITY));
					sld.City = location.fastreload;
					sld.CityType = "horse";
					sld.dialog.filename = "Common_Brothel.c";
					sld.dialog.currentnode = "Horse_talk";
					sld.greeting = "whore";
					switch (location.fastreload)
					{
						case "Tortuga":		 sld.quest.price = 1000*(rand(4)+5); break;
						case "PortRoyal":	 sld.quest.price = 1100*(rand(4)+5); break;
						case "Panama":		 sld.quest.price = 900*(rand(4)+5); break;
						case "Marigo":	     sld.quest.price = 700*(rand(4)+5); break;
						case "Bridgetown":	 sld.quest.price = 400*(rand(4)+5); break;
						case "FortFrance":	 sld.quest.price = 500*(rand(4)+5); break;
						case "Charles":		 sld.quest.price = 300*(rand(4)+5); break;
						case "SantoDomingo": sld.quest.price = 200*(rand(4)+5); break;
					}
					LAi_SetCitizenType(sld);
					LAi_group_MoveCharacter(sld, slai_group);
					ChangeCharacterAddressGroup(sld, location.id, "goto", "goto"+qty);
					horse[num] = "";
					qty++;
				}
			}
		}
	}
}

//eddy. наполнение жемчужных поселений
void CreatePearlVillage(aref loc)
{
	if (CheckAttribute(loc, "pearlVillage") && sti(loc.pearlVillage) == true)
	{	
		string iPrefix, sTemp;
		sTemp = loc.id;
		iPrefix = GetSymbol(sTemp, strlen(sTemp)-1); //получаем префикс куда грузить нпс
		int iPearNation = sti(colonies[FindColony("SantaCatalina")].nation);
		int iTemp = GetCharacterIndex("PearlGuardMan_"+iPrefix);
		if (iTemp != -1 && !CheckAttribute(&characters[iTemp], "quest.TalkOk")) 
		{//если не завалил часового
			if (characters[iTemp].location == "none")
			{
				loc.pearlVillage = false;
				DeleteAttribute(&locations[FindLocation("PearlTown"+iPrefix+"_Townhall")], "box1");
				DeleteAttribute(&locations[FindLocation("PearlTown"+iPrefix+"_Townhall")], "box2");
				Log_SetStringToLog("Часовой на подходе к поселению успел поднять тревогу, и весь жемчужный промысел скрылся в джунглях.");
				return; 
			}
			else
			{//если успел вперед часового
				DoQuestCheckDelay("Pearl_GuardManIsLife", 3.5);
				pchar.quest.Pearl_GuardManIsLife.idx = iTemp;//индекс часового передаем
				chrDisableReloadToLocation = true;			
			}
		}
		else 
		{//часовой убит
			//LAi_group_SetRelation("PearlGroup_"+iPrefix, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		}
		ref chr;
		int num, i, iMassive, iRank;
		string sAnime;
		string model[10];
		loc.pearlVillage = false; //флаг не генерить пиплов
		// ==> глава администрации
		iRank = 20+rand(15);
		chr = GetCharacter(NPC_GenerateCharacter("HeadMan_"+iPrefix, "off_"+ NationShortName(iPearNation) +"_1", "man", "man", iRank, iPearNation, 30, true, F_MILITARY));
		SetCharacterPerk(chr, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней  
		chr.dialog.Filename = "Pearl_dialog.c";
	    chr.dialog.currentnode = "HeadMan";		
		chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
		SetFantomParamFromRank(chr, iRank, true);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
        sTemp = "PearlTown"+iPrefix+"_Townhall"; //ID резиденции
		ChangeCharacterAddressGroup(chr, sTemp, "goto", "goto5");
		// ==> защитники, повоевать таки придется
		model[0] = "pirate_1";
		model[1] = "pirate_2";
		model[2] = "pirate_3";
		model[3] = "pirate_4";
		model[4] = "pirate_5";
		model[5] = "pirate_6";
		model[6] = "pirate_7";
		model[7] = "pirate_8";
		model[8] = "pirate_9";
		model[9] = "pirate_10";
		model[10] = "pirate_11";
		model[11] = "pirate_12";
		model[12] = "pirate_13";
		model[13] = "pirate_14";
		model[14] = "pirate_15";
		model[15] = "pirate_16";
		i = 0;
		num = rand(3) + 2; //кол-во защитников
		while(i < num)
		{
			iMassive = rand(9);
			if (model[iMassive] != "")
			{
				chr = GetCharacter(NPC_GenerateCharacter("FightMan"+iPrefix+"_"+i, "pirate_" + (rand(15) + 1), "man", "man", 15, iPearNation, 30, true, F_CITY));
				SetFantomParamFromRank(chr, 15, true);
				chr.dialog.Filename = "Pearl_dialog.c";
				chr.dialog.currentnode = "PearlMan";
				chr.greeting = "cit_common";
				chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
				PlaceCharacter(chr, "goto", "random");
				LAi_SetWarriorType(chr);
				LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
				i++;
				model[iMassive] = "";
			}
		}
		// ==> просто работники
		model[0] = "barman_1";
		model[1] = "shipbuilder_1";
		model[2] = "barman_1";
		model[3] = "barman_1";
		model[4] = "barman_1";
		model[5] = "officer_1";
		model[6] = "shipbuilder_1";
		model[7] = "trader_1";
		model[8] = "trader_1";
		model[9] = "barman_1";
		i = 0;
		num = rand(3) + 2; //кол-во 
		while(i < num)
		{
			iMassive = rand(9);
			if (model[iMassive] != "")
			{
				sAnime = "man"
				if (model[iMassive] == "indsair2" || model[iMassive] == "indsar1") sAnime = "man";
				chr = GetCharacter(NPC_GenerateCharacter("WorkMan"+iPrefix+"_"+i, model[iMassive], "man", sAnime, 7, iPearNation, 30, false, F_SLAVE));
				chr.dialog.Filename = "Pearl_dialog.c";
				chr.dialog.currentnode = "PearlMan";
				if (model[iMassive] == "indsair2" || model[iMassive] == "indsar1") 
				{
					chr.name = LinkRandPhrase("Венету", "Соколиный глаз", "Гойко Митич");
					chr.lastname = "";
					chr.dialog.currentnode = "IndPearlMan";
					chr.greeting = "Gr_PearlIndian";
				}
				else
				{
				    chr.greeting = "cit_common";
				}
				chr.CityType = "citizen";
				chr.city = "SantaCatalina"; //НЗГ Санта-Каталины

				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
				i++;
				model[iMassive] = "";
			}
		}
		LAi_group_SetLookRadius("PearlGroup_"+iPrefix, 16);
		LAi_group_SetHearRadius("PearlGroup_"+iPrefix, 10);
	}
}

void CreateInsideHouseEncounters(aref loc)
{	
	if (CheckAttribute(loc, "MustSetReloadBack") && loc.id.label == "house" && !IsLocationCaptured(loc.fastreload+"_town"))
	{
		// проверяем разрешение города на формирование энкаунтеров
		int iBaseCity = FindLocation(loc.fastreload+"_town");
		if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
		//--> ночью не забалуешь
		bool bDN = IsDay();
    	aref arRld, arDis;
		makearef(arRld, loc.reload);
		int i;
    	int	Qty = GetAttributesNum(arRld);
		for (i=0; i<Qty; i++)
    	{
    		arDis = GetAttributeN(arRld, i);
    		if (arDis.name != "reload1")
    		{
				if (bDN && !isBadReputation(pchar, 40)) DeleteAttribute(arDis, "disable");
				else arDis.disable = true; //закрываем вход в коммоны 2 уровня
    		}
    	}
		//<-- ночью не забалуешь
		//==> блокируем локации второго уровня		
		if (locations[reload_cur_location_index].type == "town")
		{
			ref chr, npchar;
			aref rCity;
			makearef(rCity, locations[iBaseCity].houseEnc);		
			bool bMW = rand(1);
			int iNation = GetCityNation(loc.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			string Model, Name, LastName, sName;
			string sTemp = reload_locator_ref.name + loc.index;
			int iManIdx = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+loc.index);
			int iWomanIdx = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+loc.index);
			if (iWomanIdx != -1 || iManIdx != -1) 
			{				
				if (!CheckAttribute(rCity, sTemp)) //уже есть хозяин, но дом не тот же, новый!!! сделаем из старого хозяина нового
				{
					if (iWomanIdx != -1) 
					{
						npchar = &characters[iWomanIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "philistine_" + (rand(7) + 1);
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						rCity.(sTemp) = "woman"; //последний сгенеренный
						rCity.(sTemp).woman.model = npchar.model;
						rCity.(sTemp).woman.name = npchar.name;
						rCity.(sTemp).woman.lastname = npchar.lastname;
						//<-- запомним параметры нпс в структуре колонии
					}
					else 
					{
						npchar = &characters[iManIdx];
						SetRandomNameToCharacter(npchar);
						npchar.model = "burgher_" + (rand(7) + 1);
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0); 
						LAi_group_MoveCharacter(npchar, slai_group);
						//--> запомним параметры нпс в структуре колонии
						rCity.(sTemp) = "man"; //последний сгенеренный
						rCity.(sTemp).man.model = npchar.model;
						rCity.(sTemp).man.name = npchar.name;
						rCity.(sTemp).man.lastname = npchar.lastname;
						//<-- запомним параметры нпс в структуре колонии
					}
				}
				else //уже есть структура на дом с данными хозяина
				{
					if (iWomanIdx != -1) npchar = &characters[iWomanIdx];
					else npchar =  &characters[iManIdx];
					string sSex = sTemp + "." + rCity.(sTemp);
					if (rCity.(sSex).model != npchar.model) 
					{	//данные на хозяина другие, преобразим текущего	
						npchar.model = rCity.(sSex).model;
						if (rCity.(sTemp) == "man") 
						{
							npchar.sex = "man";
							npchar.model.animation = "man";
							npchar.dialog.currentnode = "HouseMan";
							npchar.greeting = "cit_common";
							LAi_NPC_Equip(npchar, sti(npchar.rank), true, true);
						}
						else 
						{
							npchar.sex = "woman";
							npchar.model.animation = "towngirl";
							npchar.dialog.currentnode = "HouseWoman";
							npchar.greeting = "Gr_Woman_Citizen";
							DeleteAttribute(npchar, "equip");
						}
						npchar.name = rCity.(sSex).name;
						npchar.lastname = rCity.(sSex).lastname;
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету					
					}
				}
				return;
			}
			Model = "";
			Name = "";
			LastName = "";
			//-->> генерился ли такой раньше		
			if (CheckAttribute(rCity, sTemp))
			{
				if (GetNpcQuestPastDayParam(rCity, sTemp) < 30)
				{
					if (rCity.(sTemp) == "man") 
					{//если был мужик, то след. - баба
						bMW = true;
						if (CheckAttribute(rCity, sTemp + ".woman.model"))
						{
							Model = rCity.(sTemp).woman.model;
							Name = rCity.(sTemp).woman.name;
							LastName = rCity.(sTemp).woman.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".man.lastname"))
							{
								LastName = rCity.(sTemp).man.lastname;
							}
						}
					}
					else 
					{//если была баба, то след. - мужик
						bMW = false;
						if (CheckAttribute(rCity, sTemp + ".man.model"))
						{
							Model = rCity.(sTemp).man.model;
							Name = rCity.(sTemp).man.name;
							LastName = rCity.(sTemp).man.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".woman.lastname"))
							{
								LastName = rCity.(sTemp).woman.lastname;
							}
						}
					}
				}
				else //смена хозяев в доме
				{
					if (rand(10) > 8) //шанс на пустой дом.
					{
						for (i=0; i<Qty; i++) 
    					{//снимаем возможный блок коммонов второго уровня (если репа у ГГ хреновая) 
    						arDis = GetAttributeN(arRld, i);
    						if (arDis.name != "reload1")
    						{
								DeleteAttribute(arDis, "disable");
    						}
    					}
						return; 
					}
					SaveCurrentNpcQuestDateParam(rCity, sTemp); //пишем дату генерации первого нпс в этой локации
				}
			}
			else 
			{
				if (rand(10) > 8) //шанс на пустой дом.
				{
					for (i=0; i<Qty; i++) 
    				{//снимаем возможный блок коммонов второго уровня (если репа у ГГ хреновая) 
    					arDis = GetAttributeN(arRld, i);
    					if (arDis.name != "reload1")
    					{
							DeleteAttribute(arDis, "disable");
    					}
    				}
					return; 
				}
				SaveCurrentNpcQuestDateParam(rCity, sTemp); //пишем дату генерации первого нпс в этой локации
			}
			//<<-- генерился ли такой раньше
			if (bMW)
			{//============= генерим бабу ====================
				if (Model == "") Model = "philistine_" + (rand(7) + 1);
				sName = "HouseWoman_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "woman", "towngirl", rand(2)+4, iNation, 3, false, F_CITY));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c"; 
				chr.dialog.currentnode = "HouseWoman";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //НЗГ
				chr.greeting = "Gr_Woman_Citizen";			
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> запомним параметры нпс в структуре колонии
				rCity.(sTemp) = "woman"; //последний сгенеренный
				rCity.(sTemp).woman.model = chr.model;
				rCity.(sTemp).woman.name = chr.name;
				rCity.(sTemp).woman.lastname = chr.lastname;
				//<-- запомним параметры нпс в структуре колонии
			}
			else
			{//============ генерим мужика ==================
				if (Model == "") Model = "burgher_" + (rand(7) + 1);
				sName = "HouseMan_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "man", "man", rand(10)+4, iNation, 3, true, F_CITY));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "HouseEnc_dialog.c"; 
				chr.dialog.currentnode = "HouseMan";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //НЗГ
				chr.greeting = "cit_common";
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0); 
				LAi_group_MoveCharacter(chr, slai_group);
				//--> запомним параметры нпс в структуре колонии
				rCity.(sTemp) = "man"; //последний сгенеренный
				rCity.(sTemp).man.model = chr.model;
				rCity.(sTemp).man.name = chr.name;
				rCity.(sTemp).man.lastname = chr.lastname;
				//<-- запомним параметры нпс в структуре колонии
			}
		}
		//==> следование хозяина за ГГ в другие комнаты дома
		else
		{
			//если в комнате уже есть кто-то, то не следуем за ГГ на второй этаж
			for(int n=0; n<MAX_CHARACTERS; n++)
			{
				if (characters[n].location == pchar.location && characters[n].id != "MainHero")
				{
					return;
				}
			}
			//переносим хозяина на второй этаж				
			int iLocIndexEnc;
			if (pchar.location.locator == "reload1") iLocIndexEnc = reload_cur_location_index;
			else iLocIndexEnc = reload_location_index;
			int iEnc = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+iLocIndexEnc);
			if (iEnc != -1)
			{
				ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
			}
			else
			{
				iEnc = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+iLocIndexEnc);
				if (iEnc != -1)
				{
					ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
				}
			}
			
		}
	}
}

//энкаунтеры в резиденциях
void CreateInsideResidenceEncounters(aref loc)
{	
	bool bOk;
	if (CheckAttribute(loc, "MustSetReloadBack"))
	{ //если заглушка
		if (loc.id.label == "TownhallRoom" || loc.id.label == "Townhall")
		{
			CreateResidenceNpc(loc);	
		}	
	}
	else
	{ //если статичная локация
		if (loc.id.label == "TownhallRoom")
		{
			CreateResidenceNpc(loc);	
		}	
	}
}
//относится к методу выше
void CreateResidenceNpc(aref loc)
{
	ref chr;
	int Rank;
	string sModel, sSex, sAni, sNode, sGreeting;
	bool bWeapon;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
	if (rand(10) > 8) return; //шанс на пустую комнату
	//==> выбираем тип
	int iEncType = rand(2); //0 - служанка, 1 - прислуга, 2 - солдат.
	if (loc.id.label  == "TownhallRoom") iEncType = 2;
	if (CheckAttribute(loc, "Bedroom"))  iEncType = 0;	
	if (CheckAttribute(loc, "PlayHall")) iEncType = 1;	
	int iNation = GetCityNation(loc.fastreload);
	if (iNation == PIRATE) return; //пиратские резиденции нам не нужны
	switch (iEncType)
	{
	case 0:
		Rank = 3;
		sModel = "philistine_" + (rand(7) + 1);
		sSex = "woman";
		sAni = "towngirl"
		bWeapon = false;
		sNode = "ResWoman";
		sGreeting = "Gr_Woman_Citizen";
		break;
	case 1:
		Rank = 5;
		sModel = "barman_1";
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResMan";
		sGreeting = "worker";
		break;
	case 2:
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
		sModel = "sold_" + NationShortName(iNation) + "_" + (rand(7) + 9);
		sSex = "man";
		sAni = "man"
		bWeapon = true;
		sNode = "ResGuard";
		sGreeting = "guardHouse";
		break;
	}
	//==> генерим непися
	string slai_group = GetNationNameByType(iNation) + "_citizens";		
	string sName = "EncResidence_" + iBaseCity + "_" + loc.index;
	if (GetCharacterIndex(sName) > 0) return; //если есть
	chr = GetCharacter(NPC_GenerateCharacter(sName, sModel, sSex, sAni, Rank, iNation, 1, bWeapon, F_CITY));
	chr.dialog.Filename = "ResidenceEnc_dialog.c"; 
	chr.dialog.currentnode = sNode;
	chr.CityType = "citizen";
	chr.city = loc.fastreload; //НЗГ
	chr.greeting = sGreeting;
	ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
	LAi_SetOwnerType(chr);
	LAi_group_MoveCharacter(chr, slai_group);
}

//энкаунтеры на склад верфи и магазине
void CreateSkladInsideEncounters(aref loc)
{
	if (CheckAttribute(loc, "packhouse") && !IsLocationCaptured(loc.id))
	{
		ref chr;
		int iNation = GetCityNation(loc.fastreload);
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
		string sName = "SkladMan_"+reload_cur_location_index;
		if (GetCharacterIndex(sName) > 0) return; //если есть
		int Rank = sti(pchar.rank) + rand(6);
		if (Rank < 10) Rank += 10;
		if (Rank > 30) Rank -= 10;
		chr = GetCharacter(NPC_GenerateCharacter(sName, "burgher_" + (rand(7) + 1), "man", "man", Rank, iNation, 2, true, F_CITY));
		chr.dialog.Filename = "HouseEnc_dialog.c"; 
		chr.dialog.currentnode = "SkladMan";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; //НЗГ
		chr.greeting = "cit_common";
		LAi_LoginInCaptureTown(chr, false);
		ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
		LAi_SetOwnerType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
	}
}

//тюрьма
void CreateJail(aref loc)
{
	if (loc.type == "jail")
	{
		ref sld;
		string LocatorGroup, LocatorName, slai_group, nShortName;
		int i, nSit, iNation, iRank;			
		if(!CheckAttribute(pchar, "isload") && reload_location_index != reload_cur_location_index)
		{
			pchar.questTemp.jailCanMove = false;
		}
		if (CheckNPCQuestDate(loc, "Jail_date"))
		{
			SetNPCQuestDate(loc, "Jail_date");
			LAi_group_Delete("Prisoner_Group"); 
			iNation = GetCityNation(loc.parent_colony);
			slai_group = GetNationNameByType(iNation)  + "_citizens";
			nShortName = NationShortName(iNation);
			iRank = sti(pchar.rank) + rand(4);
			if (iRank < 10) iRank = 10;
			if (iRank > 20) iRank = 20;
			//====> начальник тюрьмы
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailOff", "off_" + nShortName+"_" + (rand(5) + 4), "man", "man", iRank+5, iNation, 2, true, F_MILITARY));
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //вставать и нападать на врага
 			sld.Dialog.Filename = "Common_prison.c";
			sld.dialog.currentnode = "First_officer";
			sld.greeting = "soldier_common";
			FantomMakeCoolFighter(sld, iRank+5, 70, 50, BLADE_LONG, "pistol3", "bullet", 30);//спецназ
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			//====> солдаты
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailSold_"+i, "sold_" + nShortName + "_" + (rand(7) + 1), "man", "man", iRank, iNation, 2, true, F_MILITARY));
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_prison.c";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				locatorName = PlaceCharacter(sld, "soldiers", "random_free");
				// eddy. проверяем, должен ли солдат быть протектором -->				
				if (locatorName == "protector1")
				{
					sld.protector = true;
					sld.protector.CheckAlways = 1; //проверять всегда
					sld.dialog.currentnode = "First_protector";
					sld.greeting = "soldier_arest";
				}
				else
				{
					sld.dialog.currentnode = "First_soldier";
					sld.greeting = "soldier_common";
				}
				// <-- eddy. проверяем, должен ли солдат быть протектором
			}
			//====> накидаем заключенных
			for (i=1; i<=10; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"Prisoner_"+i, "pirate_" + (rand(15) + 1), "man", "man", 10, iNation, 2, false, F_SLAVE));							
					sld.Dialog.Filename = "Common_prison.c";
					sld.dialog.currentnode = "First_prisoner";
					sld.City = loc.parent_colony;
					sld.greeting = "Gr_prison";
					//LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					locatorName = "prison"+i;
					if (rand(10)>5) 
					{
						LAi_ActorSetLayMode(sld);
						locatorName += "lay";
					}
					else LAi_SetGroundSitType(sld);
					LAi_group_MoveCharacter(sld, "Prisoner_Group");
					ChangeCharacterAddressGroup(sld, loc.id, "prison", locatorName);
				}
			}
		}
	}
}

//форты
void CreateFortsNPC(aref loc)
{	
	if (loc.type == "fort")
	{
		int iNation = GetCityNation(loc.parent_colony);	
		if(iNation == -1) return;
		string slai_group = GetNationNameByType(iNation)  + "_citizens";
		if (locations[reload_cur_location_index].type == "jail" && GetNationRelation2MainCharacter(iNation) == RELATION_ENEMY && !CheckAttribute(loc, "loginNpc"))
		{
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			return;
		}
		DeleteAttribute(loc, "loginNpc"); //снимаем возможный флаг на генерацию нпс при выходе из тюрьмы
		if (GetNpcQuestPastDayWOInit(loc, "Fort_date") < 2) return;
		ref chr;
		int iCitizensQuantity, iChar, i;
		string locatorName, sType;
		int iColony = -1;
		SaveCurrentNpcQuestDateParam(loc, "Fort_date");
		if(CheckAttribute(loc, "parent_colony")) iColony = FindColony(loc.parent_colony);
		if(iColony == -1) return;		
		arrayNPCModelHow = 0;
		// солдаты -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
		{
			aref soldierLoc, st;
			makearef(st, loc.locators.soldiers);
			iCitizensQuantity = GetAttributesNum(st);		
			for (i=0; i<iCitizensQuantity; i++)
			{	
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				soldierLoc = GetAttributeN(st, i);
				locatorName = GetAttributeName(soldierLoc);
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
				// eddy. проверяем, должен ли солдат быть протектором -->
				if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE) 
				{
					chr.protector = true;
					chr.greeting = "soldier_arest";
				}
				else chr.greeting = "soldier_common";
				// <-- eddy. проверяем, должен ли солдат быть протектором
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetGuardianType(chr);
				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// солдаты <--
		// патруль -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
		{			
			makearef(st, loc.locators.patrol);
			iCitizensQuantity = GetAttributesNum(st);
			for (i=0; i<iCitizensQuantity; i++)
			{
				if(iNation != PIRATE)
				{
					sType = "soldier";
					iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "fortPatrol";
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				chr.RebirthPhantom = true; 
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetPatrolType(chr);

				if (sti(Colonies[iColony].HeroOwn) == true)
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					chr.greeting = "pirat_guard";
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier_common";
				}
				PlaceCharacter(chr, "patrol", "random_free");
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// патруль <--
	}
}

void CreateAmmo(aref loc) // Jason, оружейная
{
	if (loc.type == "ammo")
	{
		ref sld;
		int i, iNation, iRank;			
		if (!CheckAttribute(loc, "Ammo_date") || GetNpcQuestPastDayParam(loc, "Ammo_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Ammo_date");
			iNation = GetCityNation(loc.parent_colony);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			iRank = sti(pchar.rank)+5+MOD_SKILL_ENEMY_RATE*2;
			// комендант
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoOff", "off_" + NationShortName(iNation) + "_" + (rand(5) + 4), "man", "man", iRank, iNation, 2, true, F_MILITARY));
			FantomMakeCoolFighter(sld, iRank+5, 70, 70, BLADE_LONG, GUN_COMMON, "bullet", 100); //to_do: настроить
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //вставать и нападать на врага
			sld.Dialog.Filename = "Common_Ammo.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "soldier_common";
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			// солдаты
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoSold_"+i, "sold_" + NationShortName(iNation) + "_" + (rand(7) + 9), "man", "man", iRank, iNation, 2, true, F_MILITARY));
				FantomMakeCoolFighter(sld, iRank, 60, 60, BLADE_LONG, GUN_COMMON, "bullet", 50); //to_do: настроить
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_Fort.c";
				sld.greeting = "soldier_common";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				ChangeCharacterAddressGroup(sld, loc.id, "soldiers", "soldier" + i);
			}
		}
	}
}

int GetCityNation(string _sColony) // boal метод вернет нацию по ид города
{
    int iColony = FindColony(_sColony)
	if (colonies[iColony].nation == "none")
	{
		return PIRATE;
	}
	return sti(Colonies[iColony].nation);
}

/// boal
// проерка локации на сгенеренного в ней фантома многожневку, если есть, то новый не плодим
bool isLocationHasCitizens(string _locId)
{
    ref rCharacter; //ищем
	int n, Qty;
	bool bOk = false;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "CityType")) // признак фантома-многодневки
		{
            if (rCharacter.location == _locId)
			{
				bOk = true;
				if (rCharacter.chr_ai.type == "patrol")
					PlaceCharacter(rCharacter, "patrol", "random_free"); //патруль генерится в разных локаторах
			}
		}
    }
	return bOk;
}

void ReSitCharacterOnFree(ref chr, string _locId, string sTemp)
{
	int n, k;
	
	n = 0;
	while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && n < 10)
	{
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    n++;
	}
	
	n = 0;
	while (findsubstr(sTemp, "sit_front" , 0) != -1 && n < 20)
	{    // чтоб не занимали место напротив
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    k = 0;
	    while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && k < 10)
		{
		    sTemp = PlaceCharacter(chr, "sit", "random_free");
		    k++;
		}
	    n++;
	}
}

bool CheckNPCModelUniq(ref chr)
{
	int   i, n;
	bool  bOk;
	string sModel = chr.model;
	
    bOk = true;
	for (i=0; i<arrayNPCModelHow; i++)
	{
	    if (arrayNPCModel[i] == sModel)
	    {
	        bOk = false;
	        break;
	    }
	}
	return bOk;
}

void SetNPCModelUniq(ref chr, string sType, int iSex)
{
	int i;
	
	i = 0;
	while (!CheckNPCModelUniq(chr) && i < 10)
	{
	    i++;
	    CreateModel(sti(chr.index), sType, iSex);
	}
	arrayNPCModel[arrayNPCModelHow] = chr.model;
	arrayNPCModelHow++;
}


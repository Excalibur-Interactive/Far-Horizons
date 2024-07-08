//новый файл, для усиления защиты

void CreatPlantation(aref loc)
{
    if (loc.id != "Bridgetown_Plantation") return;
    if(LAi_IsCapturedLocation) // fix нефиг грузить, когда город трупов или боевка
	{
		return;
	}
	if (GetNpcQuestPastDayWOInit(loc, "Plantation_date") < 2) return;

	int iColony = -1;
	int iNation = -1;

    iColony = FindColony("Bridgetown");

	if(iColony == -1)
	{
		return;
	}

	iNation = GetCityNation("Bridgetown");

	if(iNation == -1)
	{
		return;
	}
	SaveCurrentNpcQuestDateParam(loc, "Plantation_date");
	int iCitizensQuantity, iModel;
	ref chr;
	aref st;
	int iChar, i, iSex;
	string slai_group, locatorName, sType, sFraction;
    slai_group = GetNationNameByType(iNation)  + "_citizens";
	int num, iMassive, iRank;
	string model[10];
    
    	// ==> просто работники
		model[0] = "barman_1";
		model[1] = "barman_1";
		model[2] = "barman_1";
		model[3] = "barman_1";
		model[4] = "barman_1";
		model[5] = "officer_1";
		model[6] = "shipbuilder_1";
		model[7] = "trader_1";
		model[8] = "pirate_1";
		model[9] = "pirate_2";
		i = 0;
		num = rand(3) + 7; //кол-во
		while(i < num)
		{
			iMassive = rand(9);
			if (model[iMassive] != "")
			{
				chr = GetCharacter(NPC_GenerateCharacter("Slave_"+i, model[iMassive], "man", "man", 7, ENGLAND, 2, false, F_SLAVE));
				// Rebbebion, ПЕРЕНАЗНАЧИТЬ!!!!!!
				//chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                chr.greeting = "Gr_slave";
                chr.CityType = "citizen";
				chr.city = Colonies[iColony].id;
				LAi_SetLoginTime(chr, 6.0, 22.99);

				PlaceCharacter(chr, "goto", "random_free");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				i++;
				model[iMassive] = "";
			}
		}

	// солдаты -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
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
		chr.MusketerDistance = 0;
		LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля :)

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
		chr.dialog.filename = "Common_Soldier.c";
		chr.dialog.currentnode = "first time";   
		ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", "soldier1");
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
			LAi_SetPatrolType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "town_pirate";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				chr.greeting = "soldier";
			}
			PlaceCharacter(chr, "patrol", "random_free");			
	        chr.dialog.filename = "Common_Soldier.c";            
			chr.dialog.currentnode = "first time";
		}
	}
	// патруль <--
	// грузчики -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[5];
		locReload[0] = "houseSp1";
		locReload[1] = "houseS1";
		locReload[2] = "houseF1";
		locReload[3] = "houseF2";
		locReload[4] = "houseS2";
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
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(4);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = rand(7) + 3;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_SetLoginTime(chr, 6.0, 23.0);//homo ночью пусть спят
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// грузчики <--
}

void CreatUnderwater(aref loc)
{
	if (loc.type == "underwater")
	{
		if (CheckAttribute(loc, "type.LSC"))
		{
			LocatorReloadEnterDisable("LostShipsCity_town", "reload73", true);
			pchar.questTemp.LSC.immersions.pay = false; //оплаченное погружение использовано
			pchar.questTemp.LSC.immersions = sti(pchar.questTemp.LSC.immersions);
			SetShowTimer(400.0); //таймер
			for (int i=1; i<=22; i++)
			{
				if (GetCharacterIndex("Crab_"+i) == -1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Crab_"+i, "crabBig", "crab", "crabBig", 40+(MOD_SKILL_ENEMY_RATE), PIRATE, -1, false, F_OTHER));
					GiveItem2Character(sld, "unarmed");
					EquipCharacterbyItem(sld, "unarmed");
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_warrior_DialogEnable(sld, false);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				}
				PlaceCharacter(sld, "goto", "random_free");
			}
		}
		else
		{
			SetShowTimer(80.0); //таймер
		}
	}
}





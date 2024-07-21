
void QuestComplete(string sQuestName, string qname)
{
	// boal -->
	ref sld, npchar;
	aref arOldMapPos, arAll, arPass;
	int iTemp, i, ShipType, Rank, CrewQty; // нужно для вычислений любых целых (нации)
    float locx, locy, locz, fTemp;
	string  attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool   bOk;
	int iChurchGenBanditsCount;
	if (bQuestLogShow)
    {
	    Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--
	if (CheckAttribute(pchar, "quest." + qname + ".function"))
	{
		string sFunction = pchar.quest.(qname).function;
		call sFunction(qname);
		return;
	}
	
	// mitrokosta замена квестов на функции
	if (findsubstr(sQuestName, "Call_", 0) == 0)
	{
		sFunction = strcut(sQuestName, 5, strlen(sQuestName) - 1);
		call sFunction(qname);
		return;
	}

	switch(sQuestName)
	{	
		// boal -->
		// смена отношений от времени
        // boal все теперь проверяется 15-25 день при расчете состояния мира = изменение в 5% - ранд(100) > 95
        case "Nation_Legend":
            SetTimerCondition("Nation_Legend", 0, 0, 15+rand(10), true);
			// тут чиним стророжевики -->
			if (!bSeaActive && !bAbordageStarted)
            {
              //  RepairAllDefenderFortShips();
            }
            // тут чиним стророжевики <--
            if (rand(100) > 93 && !bWorldAlivePause)
            {
                if(IsEntity(worldMap))
                {
                    LaunchNationLegend();
                }else{
                    if (!bQuestCheckProcessFreeze) // можно показать
					{
					    DoQuestCheckDelay("Nation_Legend_Map", 1.5);
					}
					else
					{
	      				Pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
	                    Pchar.quest.Nation_Legend_Map.win_condition = "Nation_Legend_Map";
			        }
                }
        	}
        break;

        case "Nation_Legend_Map":
            if (!bQuestCheckProcessFreeze) // можно показать
			{
                LaunchNationLegend();
            }else{
                Pchar.quest.Nation_Legend_Map_TEST.win_condition.l1 = "MapEnter";
                Pchar.quest.Nation_Legend_Map_TEST.win_condition = "Nation_Legend_Map";
            }
        break;
		
		case "LocTeleport":
			TeleportCharacterToPos(pchar, stf(pchar.locx), stf(pchar.locy), stf(pchar.locz)); 
		break;
		
        // ОЗГи
        case "Battle_Hunters_Land":
            Lai_SetPlayerType(pchar);
            LAi_SetFightMode(Pchar, true);
			for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_RemoveCheckMinHP(sld);
	            LAi_SetWarriorType(sld);
	            LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
            LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
        break;
        
        case "GoAway_Hunters_Land":
            DoQuestCheckDelay("OpenTheDoors", 4.0);
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
            for (i=1; i<= sti(PChar.HunterCost.Qty); i++)
			{
	            sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
        break;
        
		// офицеры выживают!
        case "Survive_In_SeaOfficer":
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaOfficerIdx));
            iTemp = NPC_GeneratePhantomCharacter("citizen", sti(sld.Nation), MAN, -1);  // создать клон
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                if (CheckAttribute(sld, "PGGAi"))
	            {
	            	sTemp = npchar.id; // новый рандомный ИД
					DeleteAttribute(npchar, "");// все трем, а там и перки!
					CopyAttributes(npchar, sld);
	
					npchar.index = iTemp;
					// меняемся ИД, старый новому, новый трупу
					sld.id = sTemp; //navy (ПГГ fix) 26.12.06
					// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
					DeleteAttribute(npchar, "Ship");
					npchar.ship.type = SHIP_NOTUSED;
                    npchar.location = "none";
                    npchar.location.from_sea = "";
					
					DeleteAttribute(npchar, "Fellows"); // его офицеры
					// пгг в рядового НПС
					sld.LifeDay = 0;
                    DeleteAttribute(sld, "PGGAi");
	            }
	            else
	            {
	                ChangeAttributesFromCharacter(npchar, sld, true);
	                
	    			sld.location = "none";
	    			sld.location.from_sea = "";
    			}
    			PlaySound("Encounter_Map_1");
    			LAi_SetCurHPMax(npchar);
    			AddPassenger(Pchar, npchar, false);
    			Log_Info("Офицер " + GetFullName(npchar) + " поднялся на борт.");
            }
        break;
		
        // враги спасшиеся на шлюпках homo
        case "Survive_In_SeaPrisoner":  //homo 22/06/07
            sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaPrisonerIdx));
            iTemp = SetCharToPrisoner(sld);
			if (iTemp != -1)
			{
                npchar = &Characters[iTemp];
                PlaySound("Encounter_Map_1");
                // лишнее, помер ПГГ и все тут if (findsubstr(sld.id, "PsHero_" , 0) != -1) npchar = sld.id; //homo for navy (ПГГ fix)
                LAi_SetCurHPMax(npchar);
    			sld.location = "none";
    			sld.location.from_sea = "";
                Log_Info(GetFullName(npchar) + " сдался в плен.");
            }
        break;
		
		case "Survive_In_Sea":
            DeleteSeaEnvironment();
            Survive_In_Sea_Go2Land();
        break;
        
		////////////////////////////////////Квест награда за голову///////////////////////////////////////////////////////
        case "SeaHunterCheck":
            SeaHunterCheck();
        break;

		case "CheckMaxHealthQuest":
            SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
            SetNewDayHealthMax();
        break;
        
		case "My_Deck_Battle_End":  // запрет битв в трюме -после казни пленных
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], true);
            LAi_SetFightMode(Pchar, false);
        break;
		//  boal 290804 наказание битьем морды -->
        case "PunishmentAction":
            LAi_SetActorTypeNoGroup(PChar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
			LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToCharacter(pchar, sld);
            LAi_ActorAnimation(pchar, "attack_force_3", "", 0.9);
            DoQuestCheckDelay("PunishmentAction_1", 0.5);
         break;

         case "PunishmentAction_1":
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            LAi_ActorAnimation(sld, "hit_attack_2", "PunishmentAction_2", 0.6);
         break;

         case "PunishmentAction_2":
            Lai_SetPlayerType(pchar);
            sld = &Characters[makeint(Pchar.GenQuest.FreeRandomOfficerIdx)];
            switch (pchar.GenQuest.PunishmentActionManType)
            {
                case "LAi_SetHuberStayType":
                    LAi_SetHuberStayTypeNoGroup(sld);
                    break;

                case "LAi_SetStayType":
                    LAi_SetCitizenTypeNoGroup(sld);
                    break;
            }
		break;
		//  boal 290804 наказание битьем морды <--
		// индульгенция -->
		case "donation":
			int iDonation = makeint(pchar.questTemp.donate);
			int iRep      = makeint(pchar.reputation);
			int iRepIncr;
			if (iRep <10)
			{
				if (iDonation >= 1000)
				{
					iRepIncr = iDonation / 1000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep < 20 && iRep >= 10)
			{
				if (iDonation >= 2000)
				{
					iRepIncr = iDonation/2000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <30 && iRep >=20)
			{
				if (iDonation >= 3000)
				{
					iRepIncr = iDonation/3000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <40 && iRep >=30)
			{
				if (iDonation >= 4000)
				{
					iRepIncr = iDonation/4000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <50 && iRep >=40)
			{
				if (iDonation >= 5000)
				{
					iRepIncr = iDonation/5000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <60 && iRep >=50)
			{
				if (iDonation >= 6000)
				{
					iRepIncr = iDonation/6000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <70 && iRep >=60)
			{
				if (iDonation >= 7000)
				{
					iRepIncr = iDonation/7000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep <80 && iRep >=70)
			{
				if (iDonation >= 8000)
				{
					iRepIncr = iDonation/8000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			if (iRep < REPUTATION_MAX && iRep >=80)
			{
				if (iDonation >= 10000)
				{
					iRepIncr = iDonation/10000;
					ChangeCharacterReputation(pchar, iRepIncr);
					pchar.questTemp.donate = 0;
				}
			}
			pchar.questTemp.donate = 0; // mitrokosta фикс накопления пожертвований
		break;
	    // индульгенция <--
		case "SetNPCInShipDeck":  // народ внутри нашего корабля
            if (Pchar.location == Get_My_Cabin())
	        {
                SetOfficersInCabin();
            }
            else
            {
                if (Pchar.location == "My_Deck")// трюм
                {
                    SetPrisonerInHold();
                }
                else
                {
	                if (Pchar.location == "My_Campus")// кают-компания
	                {
	                    SetOfficersInCampus();
	                }
                }
            }
        break;
        
		case "SetQuestHoldBox":
			if (Pchar.location == "My_Deck")// трюм
            {
                FillQuestHoldBox(&Locations[FindLocation(Pchar.location)]);
            }
		break;
		
        case "Munity_on_Ship_Map":
            if (IsEntity(worldMap) && GetCrewQuantity(pchar) > 0)
        	{
                MunityOnShip("ShipMunity");
            }
        break;

        case "Munity_on_Ship":
            pchar.quest.Munity = "";
            pchar.GenQuest.MunityStart = true;
            PlaySound("Boarding_1");
            InterfaceStates.Buttons.Save.enable = 0;
            LAi_SetFightMode(Pchar, true);

            if (!CheckAttribute(pchar, "GenQuest.SlavesMunity"))
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomDefenceForts("goto", "", PIRATE, LAI_GROUP_TmpEnemy);
                    if (i >= (sti(PChar.Ship.Crew.Quantity)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterCrew(PChar, (8-GetCharacterShipClass(PChar))*8);
                }
                PChar.Ship.Crew.Morale = 25;
                ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
            }
            else
            {
                for (i=1; i<=9; i++)
                {
                    sld = SetFantomSlaves("goto", "", LAI_GROUP_TmpEnemy);
                    if (i >= (GetCargoGoods(PChar, GOOD_SLAVES)/((8-GetCharacterShipClass(PChar))*8))) break;
                    RemoveCharacterGoodsSelf(PChar, GOOD_SLAVES, (8-GetCharacterShipClass(PChar))*8);
                }
                DeleteAttribute(pchar, "GenQuest.SlavesMunity");
                ChangeCrewExp(PChar, "Soldiers", 3); // бонус на подавление
            }
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Dead_Munity");
        break;

        case "Dead_Munity":
		if (Pchar.questTemp.MunityOfficerIDX.begin == "1")
		{
			Log_Info("Бренные тела бунтовщиков отправлены в последнее морское путешествие");
			Pchar.questTemp.MunityOfficerIDX.begin = "0";
		}
		else Log_Info("Восстание было подавлено");

            InterfaceStates.Buttons.Save.enable = 1;
            pchar.quest.Munity = "Deads";
            LAi_SetFightMode(Pchar, false);
            DeleteAttribute(pchar, "GenQuest.MunityStart");
        break;
        
		///  захват форта - город
        case "FreeCaptureForts": // уберем солдат, откроем входы (на всяк случай) при выходе на карту
            TWN_FreeCaptureForts();
        break;
        // захват с суши по диалогу мэра (телепорт)
        case "Town_Capture_Land":
            sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            DeleteQuestAttribute("Union_with_Escadra");

            SetLocationCapturedState(sld.Default, true);

            DoQuestReloadToLocation(sld.Default.BoardLocation, sld.Default.BoardGroup, sld.Default.BoardLocator, "Capture_Forts");
        break;
        
        case "Capture_Town_Siege":
            PrepareTownBattle(); // тут только джунгли для этого случая

			if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))
			{
            	PlaySound("Landing_0");
            	AddCharacterExpToSkill(Pchar, "Leadership", 100);
			    AddCharacterExpToSkill(Pchar, "Sneak", 100);
            }
            else
            {
                DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
            }
        break;
        // Возвращение губернаторам родные диалоги // boal переделал 251204
        case "Return_Gover_Dialog":
            Characters[sti(PChar.GenQuest.GoverIdx)].dialog.CurrentNode = "First time";
        break;

        case "Return_Gover_Dialog_Exit":
            DoQuestCheckDelay("Return_Gover_Dialog", 0.5);
        break;
        // после битвы в форте сюда
        case "Capture_Forts":
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (sld.city == "Havana") HavanaResGatesUnlock();
            TWN_Capture_Forts();
        break;

        case "FightInTown":
            TWN_FightInTown();
        break;

        case "FightInTown_OpenNext":
            TWN_FightInTown_OpenNext();
        break;

        case "FightInTown_Finish":
            LAi_grp_alarmactive = false; // конец тревоги

			LAi_LockFightMode(pchar, false);
            LAi_SetFightMode(Pchar, false);
        break;

        //Два пути захвата форта
        // 1 уходим с добычей - в диалоге мэра

        // 2 Если оставляем форт себе
        case "Residence_Captured_Any":
            TWN_Residence_Captured_Any();
        break;

        case "Residence_Captured_Any_02":
   			TWN_Residence_Captured_Any_02();
        break;

        case "Back_Mayor_Type":
            TWN_Back_Mayor_Type();
        break;

        case "CapturedToOurCity":
			PlayStereoOGG("music_ship_victory");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
            //DeleteQuestHeader("tales_" + sld.City);  // to_do
            //AddQuestRecord("tales_" + sld.City, "1");

            Log_Info("Город " + GetCityName(sld.City) + " теперь наш!");

			// убрать контрабандиста
			sTemp = sld.City + "_Smuggler";
			if (GetCharacterIndex(sTemp) >= 0) // не везде есть
			{
				ChangeCharacterAddress(characterFromID(sTemp), "None", ""); // вся логика теперь в рассидки таверны
			}
            SetCaptureTownByHero(sld.City);
            LaunchColonyInfoScreen(); // табличка   to_do дает вылет :(
			// отсчет для отбития
			//if (!isCityHasFort(sld.City)) // сухопутный город
			sTemp = "Attack_Fort_" + sld.City;
            SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
            PChar.Quest.(sTemp).CityId   = sld.City;
			PChar.Quest.(sTemp).function = "TWN_Siege_Any";
        break;
		///////////////////////////////// захват города <--
		//  системные фичи
		case "PostVideo_Start":
            bMainMenuLaunchAfterVideo = true;
			PostVideoAndQuest(PChar.GenQuest.VideoAVI, 100, "PostVideo_After");
        break;

        case "PostVideo_After":
            PostEvent("DoInfoShower",100,"s","");
			DoQuestCheckDelay(PChar.GenQuest.VideoAfterQuest, 0.1);
        break;
        
        case "SetTimerEvent":
        	attrName = PChar.Quest.(qname).Event;
        	sTemp = PChar.Quest.(qname).Event.Type;
        	Model = PChar.Quest.(qname).Event.Param;
        	SetEventHandler(attrName, attrName, 0);
        	Event(attrName, sTemp, Model);
        	break;

        case "CallFunctionParam":
            attrName = PChar.GenQuest.CallFunctionParam;
            call attrName();
        break;
        
	    // Warship. CallFunctionParam не хочет работать с диалогами, поэтому испльзовать можно эту...
	    case "NextFunction":
		    DoQuestFunctionDelay(PChar.QuestTemp.NextFunction, 0.1);
		break;
        
        // вызов табличкм А в это время..
        case "LaunchFrameForm":
            PChar.GenQuest.CallFunctionParam = "LaunchFrameForm";
			DoQuestCheckDelay("CallFunctionParam", stf(pchar.AutoQuest.FrameDelay));
        break;
        
        case "Move_Govenour":  // переместим губернатора в другой город
            SetTimerCondition("Move_Govenour", 0, 0, 25+rand(10), true);
            Move_Govenour();
        break;
        
		case "pchar_back_to_player":
			Lai_SetPlayerType(pchar);
		break;

        case "God_hit_us": // это такой прикол - задействовать в ловушки для сундуков(boal)
			iTemp = 10+rand(15);
			if ((MakeInt(pchar.chr_ai.hp) - iTemp) > 0)
            {
    			LAi_SetActorType(PChar);
                LAi_ActorAnimation(PChar, "hit_attack_2", "pchar_back_to_player", 1.0);
            }
			if (!LAi_IsImmortal(pchar))
			{
				LAi_ApplyCharacterDamage(pchar, iTemp);
				SendMessage(pchar, "lfff", MSG_CHARACTER_VIEWDAMAGE, iTemp, MakeFloat(MakeInt(pchar.chr_ai.hp)), MakeFloat(MakeInt(pchar.chr_ai.hp_max)));
				LAi_CheckKillCharacter(pchar);
				SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
			}
		break;
		// диалог с ГГ генератор
        case "TalkSelf_Start":
            StartActorSelfDialog("TalkSelf_Main");
        break;
        // диалог с ГГ квестовые реплики
        case "TalkSelf_Quest":
            StartActorSelfDialog("First time");
        break;
        /////  сидим за столом в таверне ->
        case "alc":
			LAi_Fade("alc_2_prepare", "alc2");
		break;

		case "alc_2_prepare":
			LAi_SetSitType(pchar);
			LAi_SetActorType(characterFromID(pchar.questTemp.friend_in_tavern));
			LAi_ActorSetSitMode(characterFromID(pchar.questTemp.friend_in_tavern));

            sld = characterFromID(pchar.questTemp.friend_in_tavern);
            FreeSitLocator(sld.Default, sld.Default.ToLocator);  // очистим стул
			ChangeCharacterAddressGroup(pchar, sld.Default, sld.Default.group, sld.Default.ToLocator);
		break;

		case "alc2":
			LAi_ActorDialogNow(characterFromID(pchar.questTemp.friend_in_tavern), pchar, "", -1);
		break;

		case "exit_sit":
			if (CheckQuestAttribute("fight_in_tavern", "fight"))
			{
				pchar.quest.fight_in_tavern = "0";
				LAi_SetSitType(characterFromID(pchar.questTemp.friend_in_tavern));
			}
			else
			{
				if (pchar.location.group == "sit")
				{
					LAi_Fade("exit_sit_2", "");
				}
			}
		break;

		case "exit_sit_2":
   			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			//ChangeCharacterAddress(pchar, sld.Default, sld.Default.ToGo);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
		break;
		// реплика таверншика о запрете драк -->
		case "tavern_keeper":
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "tavern_keeper";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "tavern_keeper_2", -1);
		break;

		case "tavern_keeper_2":
            attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
            sld = characterFromID(attrName);
			sld.dialog.currentnode = "First time";
			LAi_SetBarmanType(sld);
		break;
		// реплика таверншика о запрете драк <--
 		case "without_memory":
			LAi_Fade("exit_sit_2", "saved_by_off");
			bQuestCheckProcessFreeze = true;
			WaitDate("",0,0,0, 5, 30);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
		break;

		case "saved_by_off":
			LAi_SetStayType(pchar);
			Log_Info("Кто-то порылся в карманах.");

			int oSum = 500 + rand(4500);
			if (makeint(Pchar.money) < oSum) oSum = makeint(Pchar.money);
			AddMoneyToCharacter(pchar, -oSum);
			if (sti(pchar.questTemp.stels.tavern) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, makeint(50+oSum/100));
				pchar.questTemp.stels.tavern = GetDataDay();
			}

   			sld = characterFromID(loadedLocation.fastreload + "_waitress");
   			pchar.questTemp.officiantLocator = sld.location.locator;
   			pchar.questTemp.officiantGroup   = sld.location.group;   // запомнить, где была
			pchar.questTemp.officiantNode = sld.dialog.currentnode; // mitrokosta - фикс диалогов официантки
			PlaceCharacter(sld, "goto", pchar.location);
			sld.dialog.currentnode = "without_money";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "officiant_back_to_citizen", 5.0, 1.0);
			DoQuestCheckDelay("pchar_back_to_player", 6.0);
		break;

		case "officiant_back_to_citizen":
			LAi_SetPlayerType(pchar);
            sld = characterFromID(loadedLocation.fastreload + "_waitress");
			LAi_SetWaitressType(sld);
			sld.location.locator = pchar.questTemp.officiantLocator;
			sld.location.group   = pchar.questTemp.officiantGroup;
			sld.dialog.currentnode = pchar.questTemp.officiantNode; // mitrokosta - фикс диалогов официантки
		break;
		//  агенты стран в таверне -->
        case "NationUpdate":
            UpdateRelations();
            if(bSeaActive)
            {
                RefreshBattleInterface();
            }
		break;

        case "pir_flag_rise":
			Flag_PIRATE();
		break;
		// агенты в тавернах -->
        case "any_patent_take":
            AddMoneyToCharacter(pchar, -sti(pchar.PatentPrice));

            RemovePatent();

			GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
            EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);

            Items[sti(pchar.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
		break;

        case "fra_flag_rise":
            Flag_FRANCE();
        break;

        case "eng_flag_rise":
            Flag_ENGLAND();
        break;

        case "spa_flag_rise":
            Flag_SPAIN();
        break;

        case "hol_flag_rise": 
            Flag_HOLLAND();
        break;

        case "QuestAboardCabinDialog":  // диалог в абордаже, в каюте при достижении минНР
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]; // фантом, тень отца капитана
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;
		
		case "LAi_ReloadBoarding": // задержка нужна
			LAi_EnableReload();
		    DelEventHandler("Control Activation", "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			LAi_ReloadBoarding();
		break;
		// boal <---
		
        ////////////////////////////////////////////////////////////////////////
		//  Служебный квест контрабандистов - ограничение по времени
		////////////////////////////////////////////////////////////////////////
		case "Rand_Smuggling":
			//слишком падает ChangeContrabandRelation(pchar, -10); // boal
			pchar.quest.KillSmugglers_after.over = "yes";  
			RemoveSmugglersFromShore();
		break;

		//Постановка стражников в локацию передачи контрабандистов
		case "Rand_ContrabandInterruption":
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			// солдаты в начале
			iTemp = GetCityNation(GetCityNameByIsland(GiveArealByLocation(loadedLocation)));
			if(iTemp == -1) 
			{
				iTemp = sti(pchar.GenQuest.Contraband.GuardNation);// Нация патруля
			}	
			Pchar.quest.contraband.SoldierQty = makeint(2*GetOfficersQuantity(Pchar) + 3);
			for (i = 2; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			sld = SetFantomDefenceForts("", "", iTemp, "CoastalGuards");
    			attrName = "SoldierIDX"+i;
    			Pchar.quest.contraband.(attrName) = sld.index;
    			LAi_SetActorType(sld);
    			LAi_ActorFollow(sld, Pchar, "", 38);
    			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
				sld.Dialog.CurrentNode = "First time";
				sld.greeting = "Gr_Costal_Guards";
            }
			// вызовем независимо!!!! не тут :) SetCoastalGuardPursuit();

			// офицер в конце
            sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
			Pchar.quest.contraband.SoldierIDX1 = sld.index;
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
			sld.Dialog.CurrentNode = "First time";
			sld.greeting = "Gr_Costal_Guards";

			LAi_ActorDialog(&Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], Pchar, "", 35, 1); // boal 120c - озвереть ждать!!!
			LAi_group_SetCheck("CoastalGuards", "CoastalGuardsAllDead");
		break;

		case "Rand_ContrabandInterruptionAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity("А вот давеча баталия у маяка была. Какой-то капитан пытался продать крупную партию контрабанды, так его патрульная эскадра за энтим делом накрыла. С поличным, значит. "+ 
				"Грохоту было - весь город переполошился, а в местной лавке крышу ядром проломило! Да только без толку всё. Местные-то - скупщики значит, в джунглях спрятались, а капитан морем ушёл. Как есть, с носом нашу эскадру оставил! Так из бухты вырулил - любой лоцман позавидует!", Pchar.quest.contraband.City, 3, 5, "");	
		break;

		case "Rand_ContrabandAtSeaEnded":
			StopCoastalGuardPursuit();
			
			AddSimpleRumourCity("А вот давеча баталия у маяка была. Какой-то капитан пытался продать крупную партию контрабанды, так его патрульная эскадра за энтим делом накрыла. С поличным, значит. "+ 
				"Грохоту было - весь город переполошился, а в местной лавке крышу ядром проломило! Да только без толку всё. Местные-то - скупщики значит, в джунглях спрятались, а капитан морем ушёл. Как есть, с носом нашу эскадру оставил! Так из бухты вырулил - любой лоцман позавидует!", Pchar.quest.contraband.City, 3, 5, "");				
		break;

		case "CoastalGuardsAllDead":
			for (i=1; i<4; i++)
			{
				sTemp = "Rand_Smug0" + i;
				LAi_SetGuardianTypeNoGroup(CharacterFromID(sTemp));
			}
			LAi_grp_alarmactive = false; // конец тревоги
		break;
		//  контрабанды <--
		
		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////
		case "EraseWind":
			DeleteAttribute(pchar, "wind");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////		
		case "HabitueSpeakDisable_End":
			DeleteAttribute(pchar,"questTemp.HabitueSpeakDisable");
			DeleteAttribute(pchar,"questTemp.duelQty");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////				
		
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////
		case "hide_weapon":
			LAi_SetFightMode(pchar, false);
			break;

		case "AnyReloadToLocation":
			int iMonth, iDay, iHour, iMin;

			iMonth	= sti(PChar.AutoQuest.delayMonth);
			iDay	= sti(PChar.AutoQuest.delayDay);
			iHour	= sti(PChar.AutoQuest.delayHour);
			iMin	= sti(PChar.AutoQuest.delayMin);

			if(iMonth > 0 || iDay > 0 || iHour > 0 || iMin > 0)
			{
                bQuestCheckProcessFreeze = true;
				WaitDate("", 0, iMonth, iDay, iHour, iMin);
				bQuestCheckProcessFreeze = false;
			}
			DoQuestReloadToLocation(PChar.AutoQuest.idLocation, PChar.AutoQuest.idGroup, PChar.AutoQuest.idLocator, PChar.AutoQuest.questName);
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	START OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////
		case "PGG_Companion_Leave":
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
			PlaceCharacter(sld, "goto", "random_must_be_near");

			sld.Dialog.CurrentNode = "companion_leave";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;

		case "RemoveCharacterFromLocation":
			sld = CharacterFromID(PChar.questTemp.Chr2Remove);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			LAi_SetImmortal(sld, false);
			break;

		case "PGG_Q1AfterShoreFight":
			PGG_Q1AfterShoreFight();
			break;

		case "PGG_Q1AfterDeckFight":
			PGG_Q1AfterDeckFight();
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////
		case "RemoveTravelSmugglers":
			if (!CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight")) ChangeContrabandRelation(PChar, -10);
			RemoveSmugglersFromShore();

			if (!CheckAttribute(PChar, "GenQuest.contraTravel.ship")) 
			{
				AddQuestRecord("Gen_ContrabandTravel", "3");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
			}

			sld = CharacterFromID("Abracham_Gray");
			sld.location.from_sea = "";
			break;

		case "Travel_talkOnDeck":
			//убираем контрабандистов
			RemoveSmugglersFromShore();
			//кинозвезда Абрахам Грей :)
			sld = CharacterFromID("Abracham_Gray");
			//параметры..
			sld.nation = PIRATE;
			Ship_FlagRefresh(PChar); //флаг на лету
			sld.location.from_sea = "";

			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);

			SetActorDialogAny2Pchar("Abracham_Gray", "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "", 1.0);
			//компания....
			iTemp = 3 + rand(3);
			for(i = 0; i < iTemp; i++)
			{
				sTemp = "pirat" + (2 + rand(5));
				attrName = "goto" + (3 + i);
				sld = SetFantomDefenceForts("goto", attrName, PIRATE, "TmpEnemy");
			}
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_ClearAllTargets();
			LAi_SetFightModeForOfficers(false);
			break;

		case "Travel_AfterDeckFight":
			AddQuestRecord("Gen_ContrabandTravel", "5");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
			StartActorSelfDialog("GenTravel_Main");
			break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		case "trade_quest_open":
			int iTradeGoods    = sti(pchar.CargoQuest.iTradeGoods);
			int iQuantityGoods = sti(pchar.CargoQuest.iQuantityGoods);
			int iTradeNation   = sti(pchar.CargoQuest.iTradeNation);
			int iMoney         = sti(pchar.CargoQuest.iMoney);
            AddCharacterGoods(pchar, iTradeGoods, iQuantityGoods);
			//задаем квест
			SetTimerCondition("generate_trade_quest", 0, 0, sti(pchar.CargoQuest.iDaysExpired), false);

			pchar.quest.generate_trade_quest_progress = "begin";
			ReOpenQuestHeader("DELIVERY_TRADE_QUEST");
			AddQuestRecord("DELIVERY_TRADE_QUEST", "1");

			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));

			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sBaseColony", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city+"Gen"));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            attrName = "";
            if (pchar.CargoQuest.iTradeIsland != pchar.CargoQuest.iTradeColony)
            {
                attrName = ", что находится на " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
            }
            AddQuestUserData("DELIVERY_TRADE_QUEST", "island", attrName);
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sTermsDelivery", FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)));
    		AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            // немного веселой жизни
            TraderHunterOnMap();
		break;
		
		case "generate_trade_quest":
			if (pchar.quest.generate_trade_quest_progress == "begin")
			{
				pchar.quest.generate_trade_quest_progress = "failed";
				Log_SetStringToLog("Время для поставки груза истекло.");
				ChangeCharacterReputation(pchar, -10);
				OfficersReaction("bad");
				ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) + "hunter", 15);
                AddQuestRecord("DELIVERY_TRADE_QUEST", "3");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(sti(pchar.CargoQuest.iTradeGoods)));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "sleep_in_tavern":
			DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
		break;
		
		case "restore_hp":
			int iOfficer;
			LAi_SetCurHPMax(pchar);
			for (i=1; i<4; i++)
			{
				if (GetOfficersIndex(Pchar, i) != -1)
				{
					iOfficer = GetOfficersIndex(Pchar, i);
					LAi_SetCurHPMax(&characters[iOfficer]);
				}
			}			
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////					
		
 		////////////////////////////////////////////////////////////////////////
		//  Начало    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_convoy_quest":
			iTemp = sti(colonies[FindColony(pchar.quest.destination)].nation);
            sld = GetCharacter(NPC_GenerateCharacter("QuestTrader", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true, F_TRADER));
			SetCaptanModelByEncType(sld, "trade");
			sld.reputation = (1 + rand(44) + rand(44));
			sld.Dialog.Filename = "convoy_traider.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			sld.greeting = "Gr_ConvoyTrader";
			sld.BakNation = sld.nation;		
		    sld.Abordage.Enable = true;
			sld.CompanionEnemyEnable = true;
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
			pchar.quest.generate_convoy_quest_progress = "begin";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "convoy_refused":
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over = "yes";
			if (checkquestattribute("generate_convoy_quest_progress", "completed"))
			{
				OfficersReaction("good");
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
				AddQuestRecord("convoy_quest", "4");
				CloseQuestHeader("convoy_quest");
				AddMoneyToCharacter(pchar, sti(pchar.ConvoyQuest.convoymoney));
				ChangeCharacterReputation(pchar, 1);
				RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
				CloseQuestHeader("convoy_quest");
			}
			pchar.quest.generate_convoy_quest_progress = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(characterFromID("QuestTrader"));
			LAi_ActorGoToLocation(characterFromID("QuestTrader"), "reload", LAi_FindFarLocator("reload", locx, locy, locz), "none", "", "", "", 20.0);
		break;
		
		case "generate_convoy_quest_timer":
            AddQuestRecord("convoy_quest", "2");
			CloseQuestHeader("convoy_quest");            
            sld = characterFromID("QuestTrader");
            ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 5+rand(10));// награда
			RemoveCharacterCompanion(Pchar, sld);
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -10);
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
		break;
		
		case "generate_convoy_quest_failed": // торговец умер
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
            RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
            pchar.quest.generate_convoy_quest_timer.over  = "yes";            
            AddQuestRecord("convoy_quest", "3");
			CloseQuestHeader("convoy_quest");
		break;
		
		case "generate_convoy_quest_completed":
			sld = characterFromID("QuestTrader");
			if (IsCompanion(sld))
			{
				sld.dialog.currentnode = "complete_convoy_quest";
				PlaceCharacter(sld, "goto", pchar.location);			
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.			
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 10+rand(10));// награда
				OfficersReaction("bad");
				pchar.quest.generate_convoy_quest_progress = "";				
				pchar.quest.generate_convoy_quest_failed.over = "yes";
				pchar.quest.generate_convoy_quest_completed.over = "yes";
				pchar.quest.generate_convoy_quest_timer.over  = "yes";  
				AddQuestRecord("convoy_quest", "5");
				CloseQuestHeader("convoy_quest");
			}
		break;		

		case "convoy_agreeded":
			sld = characterFromID("QuestTrader");
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", "reload1_back", 3.0, false);
            ReOpenQuestHeader("convoy_quest");
			AddQuestRecord("convoy_quest", "1");
			AddQuestUserData("convoy_quest", "sSex", GetSexPhrase("ся","ась"));
			sTemp = XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ", что на " + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Dat") + ",";
			AddQuestUserData("convoy_quest", "sCity", sTemp);
			AddQuestUserData("convoy_quest", "sDay", FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)));
            AddQuestUserData("convoy_quest", "sMoney", FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
			// по городу вернем его порт
            attrName = GetPortByCityName(pchar.quest.destination);            
			pchar.quest.generate_convoy_quest_completed.win_condition.l1 = "Location";
			pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = attrName;
			pchar.quest.generate_convoy_quest_completed.win_condition = "generate_convoy_quest_completed";			
			if (rand(2) == 1) TraderHunterOnMap();
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////

 		////////////////////////////////////////////////////////////////////////
		//  Начало    Доставка пассажира
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_passenger_quest":
			iTemp = sti(colonies[FindColony(sGlobalTemp)].nation);
            Rank = NPC_GenerateCharacter("QuestPassanger", "", "man", "man", makeint((sti(pchar.rank)+60)/4), iTemp, -1, true, F_CITY);
			sld = &characters[Rank];
			sld.id = sld.id + "_" + sld.index; //меняем ID на оригинальный
			sld.reputation = (1 + rand(44) + rand(44));
			SetCaptanModelByEncType(sld, "trade");
			SetRandomNameToCharacter(sld);
			sld.Dialog.Filename = "convoy_passenger.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");			
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);            
		break;

		case "AllPassangersDead": // торговец умер
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			ChangeCharacterReputation(pchar, -5);
            RemovePassenger(PChar, sld);
			sTemp = sld.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + sld.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			attrName = sld.index + "convoy_passenger";
			AddQuestRecordEx(attrName, "Gen_convoy_passenger", "3");
            CloseQuestHeader(attrName);
		break;
		
		case "AllPassangersTimeOver":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id;
			Pchar.GenQuest.ConvoyPassenger.(sTemp) = sld.index; //в структуру недовольных
			if (!CheckAttribute(Pchar, "quest.ConvoyMapPassenger"))
			{
				Pchar.quest.ConvoyMapPassenger.win_condition.l1 = "MapEnter";
        		Pchar.quest.ConvoyMapPassenger.win_condition = "AllPassengerDeck";
			}
		break;
		
		case "AllPassengerDeck": // разговор на палубе			
            MakeCloneShipDeck(pchar, true); // подмена палубы
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
    		iTemp = GetAttributesNum(arAll);
    		for (i=0; i<iTemp; i++)
    		{
    			arPass = GetAttributeN(arAll, i);
				sld = &characters[sti(arPass)];				
				ChangeCharacterAddress(sld, "Ship_deck", "goto4");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0); 
    		}
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
			ReloadFromWMtoL_complete();
            pchar.quest.Munity = "";  // признак выхода с палубы
            LAi_LockFightMode(Pchar, true);
        break;
        
		case "AllPassangersComplited":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id + "_TimeOver";
            pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			chrDisableReloadToLocation = true;
			sld.dialog.currentnode = "complete_convoy_quest";
			PlaceCharacter(sld, "goto", "random_must_be");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);     
		break;
 		////////////////////////////////////////////////////////////////////////
		//  Конец    Доставка пассажира
		////////////////////////////////////////////////////////////////////////

   		////////////////////////////////////////////////////////////////////////
		//  Начало   Бордель
		//////////////////////////////////////////////////////////////////////// 
        case "Brothel_checkVisitTime":
			LocatorReloadEnterDisable(qname + "_Brothel", "reload2_back", true); //закрываем комнату
			sld = characterFromId(pchar.quest.(qname).HorseId);
			sld.location = qname+"_Brothel";
			sld.location.group = "goto";
			sld.location.locator = pchar.quest.(qname).locator;
			//ChangeCharacterAddressGroup(sld, qname+"_Brothel", "goto", pchar.quest.(qname).locator);
			DeleteAttribute(&characters[GetCharacterIndex(qname + "_Hostess")], "quest.selected"); //снимаем флаг у хозяйки
			//==> ноду девкам
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, Characters[i]);
				if (sld.location == qname+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_talk";
				}
			}
        break;	
		////////////////////////////////////////////////////////////////////////
		//  Конец    Бордель
		////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////
		//  Начало   Моряки желают развлечений
		//////////////////////////////////////////////////////////////////////// 
		case "SailorEvent_EraseSailors":
			for (i = 1; i < 4; i++)
			{
				sld = characterFromID("Sailor_" + i);
				ChangeCharacterAddressGroup(sld, "none", "none", "none");
			}
		break;
		
		case "SailorEvent_MamanTalk_1":
			iTemp = FindColony(loadedLocation.fastreload);
			DoQuestReloadToLocation(Colonies[iTemp].id + "_SecBrRoom", "goto", "goto8", "SailorEvent_MamanTalk_2");
		break;
		
		case "SailorEvent_MamanTalk_2":
			AddMoneyToCharacter(Pchar, -makeint(GetPartyCrewQuantity(pchar, true)*30));
			sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
			sld.dialog.currentnode = "SailorEvent_Wholesale_1";
			DeleteAttribute(pchar, "Event.SailorEvent");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "SailorEvent_ToBrothel":
			PChar.Event.SailorEvent = "InBrothel";
			for (i = 1; i < 4; i++)
			{
				sld = characterFromID("Sailor_" + i);
				sld.dialog.currentnode = "sailor_in_brothel";
				LAi_SetCitizenTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, PChar.Event.SailorEvent.City + "_brothel", "goto", "goto"+i);
			}
			DoQuestReloadToLocation(PChar.Event.SailorEvent.City + "_brothel", "reload", "reload1", "SailorEvent_ToBrothel_QR");
		break;
		
		case "SailorEvent_ToBrothel_QR": //чтобы звук не прерывался
			AddPartyCrewMorale(pchar, 2);
			
			CrewQty = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(GetMainCharacter(),i);
				if(iTemp >= 0)
				{
					sld = &Characters[iTemp];
					if(GetRemovable(sld))
					{
						sTemp = sld.Ship.Type; //привязка по кораблю, а не компаньону
						TEV.TeamReserve.(sTemp) = GetCrewQuantity(sld)/2;
						RemoveCharacterCrew(sld, sti(TEV.TeamReserve.(sTemp))); //округления нечётных учтены
						CrewQty += sti(TEV.TeamReserve.(sTemp));
					}
				}
			}
			if(GetCompanionQuantity(pchar) > 1) sTemp = "свои корабли";
			else sTemp = "корабль";
			Log_Info("Команда отдыхает в городе");
			Log_SetStringToLog("Через два дня " + FindRussianSailorString(CrewQty, "Acc") + " вернутся на " + sTemp);
			
			ReOpenQuestHeader("SailorEvent");
			if(sti(TEV.SB_Counter) == 1) sTemp = "Start_Agree_1";
			else sTemp = "Start_Agree_2";
			AddQuestRecord("SailorEvent", sTemp);
			
			SetTimerFunction("SailorEvent_Finish", 0, 0, 2);
			pchar.quest.SailorEvent_LeftTeam.win_condition.l1 = "MapEnter";
			pchar.quest.SailorEvent_LeftTeam.function = "SailorEvent_LeftTeam";
			
			//слухи на время ивента -->		
			for(i = 0; i < 3; i++)
			{
				switch(i)
				{
					case 0:
						sTemp = "Вы уже знаете, что наш бордель заняли какие-то моряки? Пьют там, грешат с девушками... (шёпотом) Вот ведь счастливчики.";
						attrName = "Да, я того же мнения.";
					break;
					
					case 1:
						sTemp = "В нашем борделе творится форменное безобразие. Простым горожанам нет покоя. Да падёт кара Божья на это заведение!";
						attrName = "Кажется, подобные места были придуманы именно для этого, верно?";
					break;
					
					case 2:
						sTemp = "Какие новости? Да такие, что честным людям нельзя сходить отдохнуть с девушками, потому что бордель захватили моряки.";
						attrName = "Честные люди сидят дома с жёнами, а не шляются по борделям.";
					break;
				}
				iTemp = FindRumour(AddSimpleRumourCityTip(sTemp, PChar.Event.SailorEvent.City, 2, 1, "citizen", ""));
				Rumour[iTemp].link.l1 = attrName;
				Rumour[iTemp].link.l1.go = "new question";
				Rumour[iTemp].link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.", "Всего хорошего.");
				Rumour[iTemp].link.l2.go = "exit";
				Rumour[iTemp].sex = "man";
				Rumour[iTemp].group = "SailorEvent";
			}
			//<-- слухи на время ивента
		break;
		
		case "SailorEvent_NakedSailor":
			PlaySound("interface\SailorEvent_Door.wav");
			sld = GetCharacter(NPC_GenerateCharacter("SailorEvent_NakedSailor", "pirate_12", "man", "man", sti(pchar.rank), sti(pchar.nation), -1, false, F_SAILOR));
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload2_back");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "SailorEvent_OpenBrothelDoors", -1);
		break;
		
		case "SailorEvent_OpenBrothelDoors":
			AddPartyCrewMorale(pchar, -4); //-2 относительно прибавки
			SailorEvent_DeleteRumours();
			SailorEvent_CrewToShip();
			CrewQty = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(GetMainCharacter(),i);
				if(iTemp >= 0)
				{
					sld = &Characters[iTemp];
					if(GetRemovable(sld))
					{
						CrewQty += GetCrewQuantity(sld)/10;
						AddCharacterCrew(sld, -GetCrewQuantity(sld)/10);
					}
				}
			}
			if(GetCompanionQuantity(pchar) > 1) attrName = "эскадру";
			else attrName = "корабль";
			Log_Info("Мораль команды упала! " + FindRussianSailorString(CrewQty, "Acc") + " покинули " + attrName + "!");
			chrDisableReloadToLocation = false;
			AddQuestRecord("SailorEvent", "Please_Stop");
			CloseQuestHeader("SailorEvent");
		break;
		
		case "SailorEvent_Massage_Frame":
			SetLaunchFrameFormParam("Спустя один час...", "SailorEvent_Massage_Start", 0, 1);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			RefreshLandTime();
			RecalculateJumpTable();
		break;
		
		case "SailorEvent_Massage_Start":
			sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
			ChangeCharacterAddressGroup(sld, sld.City + "_Brothel_room", "goto", "goto3")
			DoQuestReloadToLocation(sld.city + "_Brothel_room", "reload", "reload1", "SailorEvent_Massage_Dialog");
		break;
		
		case "SailorEvent_Massage_Dialog":
			sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
			sld.dialog.currentnode = "Hostess_Massage_5";
			LAi_SetActorTypeNoGroup(pchar);
			LAi_SetActorTypeNoGroup(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", -1);
		break;
		
		case "SailorEvent_Massage_Over":
			chrDisableReloadToLocation = true;
			sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", sld.City + "_SecBrRoom", "goto", "goto8", "SailorEvent_HostessToNormal", -1);
			SetTimerFunction("SailorEvent_MassageEffectOver", 0, 0, 10); // эффект от массажа, будет длиться десять дней
		break;
		
		case "SailorEvent_HostessToNormal":
			chrDisableReloadToLocation = false;
			sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
			LAi_SetOwnerTypeNoGroup(sld);
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Моряки желают развлечений
		//////////////////////////////////////////////////////////////////////// 

		////////////////////////////////////////////////////////////////////////
		//  Начало Тюремные квесты
		//////////////////////////////////////////////////////////////////////// 
        case "GivePrisonFree":
			chrDisableReloadToLocation = true;
			LAi_LocationDisableMonstersGen(pchar.location, true);
			pchar.quest.GivePrisonFree_Death.over = "yes";
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			sld.dialog.currentnode = "PrisonerInPlace";
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;

        case "GivePrisonFree_Death":
			AddQuestRecord("GivePrisonFree", "2");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.GivePrisonFree.over = "yes";
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "GivePrisonFree_Over":
			AddQuestRecord("GivePrisonFree", "6");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.prisonerId);
			if (iTemp > 0) 
			{
				characters[iTemp].lifeDay = 0;
				ChangeCharacterAddress(&characters[iTemp], "none", "");	
			}
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup"
		break;

        case "DeliverToBander":
			if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.City") && pchar.questTemp.jailCanMove.Deliver.City == locations[reload_location_index].fastreload)
			{
				LAi_group_Delete("EnemyFight");
				chrDisableReloadToLocation = true;
				pchar.quest.DeliverToBander.over = "yes";
				pchar.quest.DeliverToBander_over.over = "yes";
				//--> генерим ранг 
				if (sti(pchar.rank) > 6) 
				{
					Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
				}
				else  
				{	//казуалам зеленый свет на начало игры
					if (sti(pchar.rank) > 3) Rank = sti(pchar.rank);
					else 
					{
						Rank = 1;
					}
				}	
				//<-- генерим ранг
				GetCharacterPos(pchar, &locx, &locy, &locz);
				for (i=1; i<=2; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Bander_"+i, "pirate_" + (rand(15) + 1), "man", "man", Rank, PIRATE, 0, true, F_PIRATE));
					sld.dialog.filename = "quest\Banders_dialog.c";
					sld.dialog.currentnode = "First time";
					sld.greeting = "cit_common"; 
					SetFantomParamFromRank(sld, Rank, true);
					if (i == 1)
					{
						LAi_SetOwnerType(sld);
						sld.dialog.currentnode = "Second time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
					}
					else
					{
						LAi_SetActorType(sld);
						sld.dialog.currentnode = "First time";
         				ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
					}
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_ActorDialog(sld, pchar, "", 1.0, 0); 
			}
		break;

        case "DeliverToBander_over":
			AddQuestRecord("GivePrisonFree", "9");
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.DeliverToBander.over = "yes";
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeliverToBander_Dead":
			AddQuestRecord("GivePrisonFree", "10");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			CloseQuestHeader("GivePrisonFree");
            chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

        case "DeletePrisonGroup":
			LAi_group_Delete("DeliveQuest_Prison");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец  Тюремные квесты
		//////////////////////////////////////////////////////////////////////// 

		// универсальный диалогостартер (см метод  SetActorDialogAny2Pchar)
        case "ActorDialog_Any2Pchar":
            LAi_SetActorType(PChar);
            LAi_ActorWaitDialog(Pchar, characterFromID(Pchar.AutoQuest.NPCharId));
            LAi_ActorDialog(characterFromID(Pchar.AutoQuest.NPCharId), Pchar, Pchar.AutoQuest.Quest, stf(Pchar.AutoQuest.Time1), stf(Pchar.AutoQuest.Time2));
        break;

        case "OpenTheDoors":
            chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
        break;

        case "CanEnterToMap":
            bQuestDisableMapEnter = false;
        break;

        case "CloseBermudesDungeonDoor":
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			sld = characterFromId("Pirates_shipyarder");
			DeleteAttribute(sld, "Step_Door");
        break;

        case "CanFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
        break;

        case "CannotFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
        break;

        case "MainHeroFightModeOn":
			LAi_SetFightMode(pchar, true);
        break;

        case "MainHeroFightModeOff":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
        break;

		case "ChurchNightGuard_timerInChurch_2":
			TavernWaitDate("wait_day");
		break;
		
		case "MayorSitBack": //посадить мэра обратно
			iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
			if (iTemp > 0)
			{
				sld = &characters[iTemp];
				sld.location = Pchar.quest.MayorSitBack.locationName;
				sld.location.group = "sit";
				sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
				LAi_SetHuberTypeNoGroup(sld);
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
				RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			}
        break;

		case "PlaySex_1":
			ResetSound();
			iTemp = rand(13)+1;
			switch (iTemp)
			{
				case 1: fTemp = 18.2; break;
				case 2: fTemp = 5.1;  break;
				case 3: fTemp = 19.3; break;
				case 4: fTemp = 8.2;  break;
				case 5: fTemp = 11.3; break;
				case 6: fTemp = 18.2; break;
				case 7: fTemp = 18.2; break;
				case 8: fTemp = 9.3;  break;
				case 9: fTemp = 19.4; break;
				case 10:fTemp = 12.2; break;
				case 11:fTemp = 19.4; break;
				case 12:fTemp = 12.3; break;
				case 13:fTemp = 10.2; break;
				case 14:fTemp = 11.2; break;
			}
			sGlobalTemp = iTemp;
			SetLaunchFrameFormParam("", "", 0, fTemp);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
            LaunchFrameForm();
			DoQuestCheckDelay("PlaySex_2", 1.0);			
		break;

		case "PlaySex_2":
			PlayStereoSound("sex\sex" + sGlobalTemp + ".wav");
            AddTimeToCurrent(2, rand(30));
			//массаж хозяйки борделя
			if(CheckAttribute(&TEV, "SensualMassage.Bonus"))
			{
				DeleteAttribute(&TEV, "SensualMassage.Bonus");
				AddCharacterHealth(pchar, 10);
				//to_do: временный бонус, например, +10% к шкале здоровья и энергии на 10 дней
				sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
				sld.greeting = ""; //to_do: можно в PlaySound что-нибудь вставить
				sld.dialog.currentnode = "Hostess_Massage_7";
				ChangeCharacterAddressGroup(pchar, sld.City + "_Brothel_room", "goto", "goto1");
				ChangeCharacterAddressGroup(sld, sld.City + "_Brothel_room", "goto", "goto2");
				LAi_SetPlayerType(pchar);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		// mitrokosta заметил что это требуется в нескольких местах
		case "EnemyFight":
			chrDisableReloadToLocation = true;
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		break;

		case "ChangeShowInterface":
			ChangeShowIntarface();
		break;
		
		case "DegreaseCityDialogsByOne":
			pchar.QuestTemp.CityDialogs = sti(pchar.QuestTemp.CityDialogs) - 1;
		break;
		
		case "DegreaseCityDialogsToZero":
			pchar.QuestTemp.CityDialogs = 0;
		break;
		
		case "Officer_BerserkerLock":
			sld = CharacterFromID(sTotalTemp);
			
			if(CheckAttribute(sld, "MultiFighter"))
		    {
		    	sld.MultiFighter = sld.oldMultiFighter;
		    }
		    else DeleteAttribute(sld, "MultiFighter");
			DoQuestCheckDelay("Officer_BerserkerUnLock", 60.0);
		break;
		
		case "Officer_BerserkerUnLock":
			sld = CharacterFromID(sTotalTemp);
			sld.BerserkerCan = true;
		break;
	}	
}

// boal -->
////////////////////////   общие методы //////////////////////////
void SetActorDialogAny2Pchar(string _charId, string _doQuest, float time1, float time2)
{
    Pchar.AutoQuest.NPCharId = _charId;
    Pchar.AutoQuest.Quest    = _doQuest;
    Pchar.AutoQuest.Time1    = time1;
    Pchar.AutoQuest.Time2    = time2;
}

//для универсализации (navy 17.10.05)
//уcтановки для телепорта ГГ в любую локацию с задержкой или без. 
//Для отложенного вызова напр. AddDialogExitQuest()
void SetAnyReloadToLocation(string idLocation, string idGroup, string idLocator, string questName, int delayMonth, int delayDay, int delayHour, int delayMin)
{
    ref PChar = GetMainCharacter();

	PChar.AutoQuest.delayMonth	= delayMonth;
	PChar.AutoQuest.delayDay	= delayDay;
	PChar.AutoQuest.delayHour	= delayHour;
	PChar.AutoQuest.delayMin	= delayMin;

	PChar.AutoQuest.idLocation	= idLocation;
	PChar.AutoQuest.idGroup		= idGroup;
	PChar.AutoQuest.idLocator	= idLocator;
	PChar.AutoQuest.questName	= questName;
}

// Инициация таблички В это время на Беде  -->
// _FrameText - текст  Перенос строки делать "текст"+ NewStr() +"текст"
// _FrameQuest - квест после завершения таблички, если == "Reload_To_Location" см. SetLaunchFrameReloadLocationParam
// если же будет == "Run_Function" см. SetLaunchFrameRunFunctionParam
// _delay - время в с. отложения вызова таблички (нужно для неконфликта с заставкой загрузки локаций, где-то 0.1-1.5с)
// _autoEnd - время в с. автозавершения показа таблички, 4-6с на фразу
void SetLaunchFrameFormParam(string _FrameText, string _FrameQuest, float _delay, float _autoEnd)
{
    pchar.AutoQuest.FrameText    = _FrameText;
    pchar.AutoQuest.FrameQuest   = _FrameQuest;
    pchar.AutoQuest.FrameDelay   = _delay;
    pchar.AutoQuest.FrameAutoEnd = _autoEnd;
}

void SetLaunchFrameFormPic(string _FramePic)
{
    pchar.AutoQuest.FramePic    = _FramePic;
}
// метод для инициации перехода после таблички
void SetLaunchFrameReloadLocationParam(string idLocation, string idGroup, string idLocator, string questName)
{
    pchar.AutoQuest.FrameLocation      = idLocation;
    pchar.AutoQuest.FrameGroup         = idGroup;
    pchar.AutoQuest.FrameLocator       = idLocator;
    pchar.AutoQuest.FrameLocationQuest = questName;
}
// метод для вызова метода из кода после таблички _func - метод, _delay - задержка вызова метода после таблички в с.
void SetLaunchFrameRunFunctionParam(string _func, float _delay)
{
    pchar.AutoQuest.FrameFunction      = _func;
    pchar.AutoQuest.FrameFunctionDelay = _delay;
}
// Инициация таблички В это время на Беде  <--

void WaitNextHours(string qName)
{
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour = "Прошло несколько часов...";
	switch(sti(pchar.quest.waithours))
	{
    	case 1:		sHour = "Прошёл один час..."; break;
    	case 2:		sHour = "Прошло два часа..."; break;
		case 3:		sHour = "Прошло три часа..."; break;
		case 4:		sHour = "Прошло четыре часа..."; break;
		case 5:		sHour = "Прошло пять часов..."; break;
		case 6:		sHour = "Прошло шесть часов..."; break;
		case 7:		sHour = "Прошло семь часов..."; break;
		case 8:		sHour = "Прошло восемь часов..."; break;
		case 9:		sHour = "Прошло девять часов..."; break;
		case 10:	sHour = "Прошло десять часов..."; break;
		case 11:	sHour = "Прошло одиннадцать часов..."; break;
		case 12:	sHour = "Прошло двенадцать часов..."; break;
		case 13:	sHour = "Прошло тринадцать часов..."; break;
		case 14:	sHour = "Прошло четырнадцать часов..."; break;
		case 15:	sHour = "Прошло пятнадцать часов..."; break;
		case 16:	sHour = "Прошло шестнадцать часов..."; break;
		case 17:	sHour = "Прошло семнадцать часов..."; break;
		case 18:	sHour = "Прошло восемнадцать часов..."; break;
		case 19:	sHour = "Прошло девятнадцать часов..."; break;
		case 20:	sHour = "Прошло двадцать часов..."; break;
		case 21:	sHour = "Прошёл двадцать один час..."; break;
		case 22:	sHour = "Прошло двадцать два часа..."; break;
		case 23:	sHour = "Прошло двадцать три часа..."; break;
		case 24:	sHour = "Прошли одни сутки..."; break;
	}
	if(isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}
	
	WaitDate("", 0, 0, 0, sti(pchar.quest.waithours), 0);
	LaunchFrameForm();
	DeleteAttribute(pchar,"quest.waithours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void RemovePatent()
{
	RemoveCharacterEquip(pchar, "patent");
    if (CheckCharacterItem(Pchar, "patent_eng"))
    {
        TakeItemFromCharacter(pchar, "patent_eng");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_fra"))
    {
        TakeItemFromCharacter(pchar, "patent_fra");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_spa"))
    {
        TakeItemFromCharacter(pchar, "patent_spa");
        ChangeCharacterReputation(pchar, -10);
    }
    if (CheckCharacterItem(Pchar, "patent_hol"))
    {
        TakeItemFromCharacter(pchar, "patent_hol");
        ChangeCharacterReputation(pchar, -10);
    }
}

void StartActorSelfDialog(string _CurrentNode)
{
    LAi_SetActorType(pchar);
    LAi_CharacterSaveAy(pchar);
    locCameraSleep(true);
    if (stf(pchar.chr_ai.type.ay) > 0)
    {
    	CharacterTurnAy(pchar,  -PI + abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    else
    {
    	CharacterTurnAy(pchar,  PI - abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
    }
    pchar.Dialog.CurrentNode = _CurrentNode;
    LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

// подъем флагов
void Flag_PIRATE()
{
	PChar.nation	= PIRATE;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(PIRATE);
	
	SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
	
	SetNationRelation2MainCharacter(PIRATE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
	
	LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_PIRATE_SOLDIERS();
	
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}            

void Flag_FRANCE()
{
	PChar.nation	= FRANCE;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(FRANCE);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, FRANCE));
    SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(FRANCE, SPAIN));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);

    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(FRANCE, HOLLAND));

    LAi_group_SetRelation("FRANCE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); //LAI_GROUP_FRIEND);
    //Relation_FRANCE_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_ENGLAND()
{
	PChar.nation	= ENGLAND;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(ENGLAND);

	SetNationRelation2MainCharacter(ENGLAND, RELATION_FRIEND);
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(ENGLAND, FRANCE));
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(ENGLAND, HOLLAND));

    LAi_group_SetRelation("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_ENGLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_SPAIN()
{
	PChar.nation = SPAIN;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(SPAIN);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, SPAIN));
	SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(SPAIN, HOLLAND));

    LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_SPAIN_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_HOLLAND()
{
	PChar.nation	= HOLLAND;
    Ship_FlagRefresh(PChar); //флаг на лету
    SetNationToOfficers(HOLLAND);

    SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, HOLLAND));
    SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, HOLLAND));
    SetNationRelation2MainCharacter(SPAIN, GetNationRelation(SPAIN, HOLLAND));
    SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
    SetNationRelation2MainCharacter(HOLLAND, RELATION_FRIEND);

    LAi_group_SetRelation("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    //Relation_HOLLAND_SOLDIERS();
    LAi_group_ClearAllTargets();
    DoQuestCheckDelay("NationUpdate", 3.0);
    UpdateRelations();
	RefreshBattleInterface();
	wdmSetNationFlag(sti(pchar.nation));
	SetSchemeAfterFlagRise();
}

void Flag_Rerise()
{
	switch (sti(PChar.nation))
	{
    	case ENGLAND:	Flag_ENGLAND();	break;
    	case FRANCE:	Flag_FRANCE();	break;
    	case SPAIN:		Flag_SPAIN();	break;
    	case PIRATE:	Flag_PIRATE();	break;
    	case HOLLAND:	Flag_HOLLAND();	break;
	}
}

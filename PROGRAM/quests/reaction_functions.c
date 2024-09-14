ref		sld, rCharacter;
int     iTemp, i; // нужно для вычислений любых целых (нации)
float   locx, locy, locz;
string  sTemp; // любые строки для вычислений
bool    bOk;

#include "quests\Start quests\Catherine.c"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  разное с оптимизации   начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==> грабители
void Birglars_fight(string qName)
{
	if (GetCharacterIndex("Berglar" + pchar.quest.(qName).city) != -1)
	{
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);		
		sTemp = "berglar" + pchar.quest.(qName).city;
		pchar.questTemp.tugs.(sTemp) = "over";
		sld = characterFromId("Berglar" + pchar.quest.(qName).city);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	}
}
//освободить флаг на дачу миниквестов
void SmallQuests_free(string qName)
{
	pchar.questTemp.different = "free";
}
//вернуть тип губернаторов обратно в sit после боевки
void MayorSitBack(string qName) 
{
	iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
	if (iTemp > 0)
	{
		sld = &characters[iTemp];
		sld.location = Pchar.quest.MayorSitBack.locationName;
		sld.location.group = "sit";
		sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
		LAi_SetHuberTypeNoGroup(sld);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		RemoveCharacterEquip(sld, MUSKET_ITEM_TYPE);
	}
}

void SeekShip_Stay(string qName)
{
	sld = &characters[sti(pchar.quest.(qName).Idx)];
	LAi_SetStayType(sld);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  разное с оптимизации   конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//zagolski - побег офицера
void mOfficer_fc(string qName)
{
	if (IsEntity(worldMap))
    	{
		ref sld = &Characters[sti(Pchar.questTemp.MunityOfficerIDX)];
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog("Офицер " + GetFullName(sld) + " сбежал с кораблем " + sld.ship.name + "");
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else
			{
				Log_SetStringToLog("Офицер " + GetFullName(sld) + " сбежал с корабля " + pchar.ship.name + "");
				if (GetCrewQuantity(pchar) > 0)
				{
					MunityOnShip("ShipMunity");
				}
				else Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else Pchar.questTemp.MunityOfficerIDX.begin = "0";
		
        }
	else
        {
            	pchar.quest.mOfficer_fc2.win_condition.l1 = "MapEnter";
		pchar.quest.mOfficer_fc2.function    = "mOfficer_fc2";
        }
}

void mOfficer_fc2(string qName)
{
	ref sld = &Characters[sti(Pchar.questTemp.MunityOfficerIDX)];
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog("Офицер " + GetFullName(sld) + " сбежал с кораблем " + sld.ship.name + "");
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else
			{
	Log_SetStringToLog("Офицер " + GetFullName(sld) + " сбежал с корабля " + pchar.ship.name + "");

        if (GetCrewQuantity(pchar) > 0)
	{
		MunityOnShip("ShipMunity");
				}
				else Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else Pchar.questTemp.MunityOfficerIDX.begin = "0";
}

void Survive_In_Sea_Go2Land()
{
    string  sTemp;
    int     iDay;
    ref 	ch;
	int 	n, i, idx;
    int 	storeArray[30];
    int 	howStore = 0;
    
	PChar.nation = GetBaseHeroNation();
    // трем всех офов и компаньонов, не квестовых
    iDay = GetPassengersQuantity(pchar);
    i = 0;
    n = 0;
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx==-1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // квестовых не трогаем
		{
		    ch.LifeDay = 1; // чтоб не сразу потерся
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}

	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // не трогаем квестовых и ПГГ
			{
			    ch.LifeDay = 1; // чтоб не сразу потерся
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
	
	DeleteAttribute(pchar, "ship");
	pchar.ship.name = "";
	pchar.ship.type = SHIP_NOTUSED;
	pchar.money = 0;

	SetCharacterShipLocation(pchar, "");

	// выбор города близ бухты
    for (n = 0; n < MAX_COLONIES; n++)
	{
  		if (colonies[n].nation == "none") continue; // необитайки
  		if (sti(colonies[n].nation) == PIRATE) continue;
  		if (colonies[n].from_sea == "") continue; // необитайки
  		if (!CheckAttribute(&Colonies[n], "islandLable") || Colonies[n].islandLable == "Mein") continue; // только острова
  		
        storeArray[howStore] = n;
   		howStore++;
    }

    makeref(ch,colonies[storeArray[rand(howStore-1)]]);
    setWDMPointXZ(ch.from_sea);
    pchar.location = ch.from_sea; // это порт, ниже ищем бухту

    // нулим предметы в каюте
    ref loc;
    if (Pchar.SystemInfo.CabinType != "")
    {
	    loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

	    for (n = 1; n <= 4; n++)
	    {
	        sTemp = "box" + n;
			DeleteAttribute(loc, sTemp + ".items");
		    loc.(sTemp).items = "";
		    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
		    loc.(sTemp).money = 0;
	    }
    }
    loc = &locations[FindLocation("My_Deck")];
    for (n = 1; n <= 4; n++)
    {
        sTemp = "box" + n;
		DeleteAttribute(loc, sTemp + ".items");
	    loc.(sTemp).items = "";
	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
	    loc.(sTemp).money = 0;
    }
	Pchar.GenQuest.Hunter2Pause = true;
    iDay = 5+rand(17);
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,iDay, rand(10), 1); // прошло время
    bQuestCheckProcessFreeze = false;
    
	// бухта контры
    pchar.location = SelectSmugglingLocation();
    
    pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*40;
	Log_Info("О чудо! Я жив"+ GetSexPhrase("","а") +"!");
	
	SetLaunchFrameFormParam("Прошло " + iDay + " дней." + NewStr() + "Остров " + GetConvertStr(ch.islandLable, "LocLables.txt")+","+ NewStr() + "" + GetConvertStr(pchar.location, "LocLables.txt") + ".", "Reload_To_Location", 0.1, 7.0);
    SetLaunchFrameReloadLocationParam(pchar.location, "Smugglers", "Smuggler01", "");
	LaunchFrameForm();
}

void Hero_ExitTown_SoldierChasePrepare(string qName)
{
	for (i=1; i<=5; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter(PChar.Hero_ExitTown_SoldierChase.city+"_ChaseSold_"+i, "sold_" + NationShortName(sti(PChar.Hero_ExitTown_SoldierChase.nation)) + "_" + (rand(7) + 1), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8, sti(PChar.Hero_ExitTown_SoldierChase.nation), 1, true, F_MILITARY));
		EquipCharacterByPhantomType(sld, "soldier", true, true);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, GetNationNameByType(sti(PChar.Hero_ExitTown_SoldierChase.nation))+"_CITIZENS_Chase");         
        LAi_group_SetRelation(GetNationNameByType(sti(PChar.Hero_ExitTown_SoldierChase.nation))+"_CITIZENS_Chase", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups(GetNationNameByType(sti(PChar.Hero_ExitTown_SoldierChase.nation))+"_CITIZENS_Chase", LAI_GROUP_PLAYER, false);		
    }
	DoQuestFunctionDelay("Hero_ExitTown_SoldierChase", 3);
}

void Hero_ExitTown_SoldierChase(string qName)
{
    for (i=1; i<=5; i++)
    {
		sld = CharacterFromID(PChar.Hero_ExitTown_SoldierChase.city+"_ChaseSold_"+i);
        ChangeCharacterAddressGroup(sld, PChar.Hero_ExitTown_SoldierChase.city  + "_ExitTown", "reload", "reload3");
    }
	DeleteAttribute(pchar, "Hero_ExitTown_SoldierChase");
}

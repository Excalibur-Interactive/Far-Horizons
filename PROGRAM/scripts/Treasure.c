// клады из ВМЛ

//  Карты сокровищ  ГЕНЕРАТОР -->
string GetIslandForTreasure()
{
	int iNum, m;
	ref Itm;
	aref arDest, arImt;
	string sAttr;
	
	m = 0;
	string sCurIsland = GetCharacterCurrentIslandId(pchar);
	makearef(arDest, NullCharacter.TravelMap.Islands);
	iNum = GetAttributesNum(arDest);
	
	string sArray[50]; // динамические массивы в Шторме не организуешь :(
	for (int i = 0; i<iNum; i++)
	{
		arImt = GetAttributeN(arDest, i);
		sAttr = GetAttributeName(arImt);
		if(CheckAttribute(&NullCharacter,"TravelMap.Islands." + sAttr + ".Treasure"))
		{
			if(sCurIsland == sAttr || CheckTreasureMaps(sAttr)) continue;
			else
			{
				sArray[m] = sAttr;
				m++;		
			}	
		}
	}
	m = rand(m-1);
	return sArray[m];
}

bool CheckTreasureMaps(string sIsland)
{
	ref Itm;
	
	if(GetCharacterItem(pchar,"mapQuest") > 0)
	{
		itm = ItemsFromID("mapQuest");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}		
	if(GetCharacterItem(pchar,"map_full") > 0)
	{
		itm = ItemsFromID("map_full");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}	
	return false;
}

string GetLocationForTreasure(string island)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure);
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeName(arImt);
}

string GetBoxForTreasure(string island, string location)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure.(location));
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);
    
    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeValue(arImt);  // тут не атрибут, а значеие
}
// не при деле....
string GetFileMapForTreasure(string island)
{
    int n;

    for (n = 0; n < ITEMS_QUANTITY; n++)
	{
		if (CheckAttribute(&Items[n], "MapIsland") )
		{
            if (Items[n].MapIsland == island)
            {
                return Items[n].imageTga;
            }
		}
    }
    return "";
}

void GenerateMapsTreasure(ref item, int iProbability1, int iProbability2)
{		
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) item.BoxTreasure.map_jam = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) item.BoxTreasure.map_cayman = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) item.BoxTreasure.map_barbados = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) item.BoxTreasure.map_trinidad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) item.BoxTreasure.map_Curacao = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) item.BoxTreasure.map_martiniqua = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) item.BoxTreasure.map_dominica = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) item.BoxTreasure.map_puerto = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) item.BoxTreasure.map_cuba = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) item.BoxTreasure.map_hisp = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) item.BoxTreasure.map_nevis = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) item.BoxTreasure.map_guad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) item.BoxTreasure.map_antigua = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) item.BoxTreasure.map_TORTUGA = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) item.BoxTreasure.map_terks = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) item.BoxTreasure.map_sm = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) item.BoxTreasure.map_bermudas = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) item.BoxTreasure.map_Pearl = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) item.BoxTreasure.map_beliz = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) item.BoxTreasure.map_santa = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) item.BoxTreasure.map_maine_1 = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) item.BoxTreasure.map_maine_2 = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) item.BoxTreasure.map_panama = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) item.BoxTreasure.map_maracaibo = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) item.BoxTreasure.map_cumana = 1;
}


void FillMapForTreasure(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
    item.MapTypeIdx = rand(2);

    // генерим клад
    DeleteAttribute(item, "BoxTreasure");
    FillBoxForTreasure(item, rand(3));
    FillBoxForTreasureAddition(item);

    if (!CheckAttribute(Pchar, "GenQuest.TreasureBuild"))
    {
        if (rand(15) == 1) item.MapTypeIdx = -1;
    }
    else
    {
       FillBoxForTreasureSuper(item);
    }
    DeleteAttribute(Pchar, "GenQuest.TreasureBuild"); //сборный

    if (sti(item.MapTypeIdx) != -1)
    {
        Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
        Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
        Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
    }
}
void FillBoxForTreasure(ref item, int i)
{
	// определяем тип
	switch (i)
	{
		// good
		case 0:
		    if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry2 = 2 + rand(30);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry3 = 10 + rand(3);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry3 = 1 + rand(30);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry5 = 5 + rand(60);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry7 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry10 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry14 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry17 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry18 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral2 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral5 = 5 + rand(100);
	        }
	        if (rand(4) == 1)
	        {
            	item.BoxTreasure.suit_2 = 1;
	        }
			GenerateMapsTreasure(item, 35, 70);
	    break;
	    // best
	    case 1:
            if (rand(2) == 1)
	        {
            	item.BoxTreasure.chest = 1 + rand(14);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry12 = 10 + rand(3);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.icollection = 1 + rand(4);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry1 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry12 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry11 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry6 = 5 + rand(100);
	        }
	        if (rand(4) == 1)
	        {
            	item.BoxTreasure.suit_3 = 1;
	        }
			GenerateMapsTreasure(item, 25, 50);
	    break;
	    // bad
	    case 2:
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.rabble = 5 + rand(100);
	        }
	        else
	        {
                item.BoxTreasure.blade1 = 5 + rand(100);//fix
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade1 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade5 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry16 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral4 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral6 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral7 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral10 = 25 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian4 = 15 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian8 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian16 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade5 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.suit_1 = 1;
	        }
	    break;

	    case 3:
	        FillBoxForTreasure(item, 0);
	    break;
	}
}

void FillBoxForTreasureAddition(ref item)
{
    float   nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);

    if (5*nLuck > rand(55))
    {
	    if (GetCharacterItem(Pchar, "map_part1") == 0)
	    {
	        item.BoxTreasure.map_part1 = 1;
	    }
	    else
	    {
	        if (GetCharacterItem(Pchar, "map_part2") == 0)
		    {
		        item.BoxTreasure.map_part2 = 1;
		    }
	    }
	}
	// +1 вещи
	switch (rand(40))
	{
		case 1:
		    item.BoxTreasure.STATUE1 = 1;
		break;
		case 2:
		    item.BoxTreasure.jewelry9 = 1;
		break;
		case 3:
		    item.BoxTreasure.jewelry15 = 1;
		break;
		case 4:
		    item.BoxTreasure.jewelry8 = 1;
		break;
		case 5:
		    item.BoxTreasure.indian7 = 1;
		break;
		case 6:
		    item.BoxTreasure.indian2 = 1;
		break;
		case 7:
		    item.BoxTreasure.jewelry4 = 1;
		break;
		case 8:
		    item.BoxTreasure.indian3 = 1;
		break;
		case 9:
		    item.BoxTreasure.indian1 = 1;
		break;
		case 10:
		    item.BoxTreasure.indian5 = 1;
		break;
		case 11:
		    item.BoxTreasure.indian6 = 1;
		break;
		case 12:
		    item.BoxTreasure.indian10 = 1;
		break;
		case 13:
		    item.BoxTreasure.indian12 = 1;
		break;
		case 14:
		    item.BoxTreasure.indian14 = 1;
		break;
		case 15:
		    item.BoxTreasure.indian15 = 1;
		break;
		case 16:
		    item.BoxTreasure.indian17 = 1;
		break;
		case 17:
		    item.BoxTreasure.indian18 = 1;
		break;
		case 18:
		    item.BoxTreasure.indian19 = 1;
		break;
		case 19:
		    item.BoxTreasure.indian20 = 1;
		break;
		case 20:
		    item.BoxTreasure.indian21 = 1;
		break;
		case 21:
		    item.BoxTreasure.indian22 = 1;
		break;
		case 22:
		    item.BoxTreasure.Mineral3 = 1;
		break;
		case 23:
		    item.BoxTreasure.Mineral8 = 1;
		break;
		case 24:
		    item.BoxTreasure.Coins = 1;
		break;
		case 25:
		    item.BoxTreasure.sculMa1 = 1;
		break;
		case 26:
		    item.BoxTreasure.sculMa2 = 1;
		break;
		case 27:
		    item.BoxTreasure.sculMa3 = 1;
		break;
	}
	GenerateMapsTreasure(item, 10, 20);
}

void FillBoxForTreasureSuper(ref item)
{
    float     nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
	int     i;
	string  itmName;

    if (3*nLuck > rand(21))// еще поди найди 2 куска
    {
		i = 0;
		itmName = "";
		while (itmName == "" && i < 15)
		{
            switch (rand(16))
			{
                case 0:
                	itmName = GetGeneratedItem("blade13");
				break;
				case 1:
        			itmName = GetGeneratedItem("blade20");
				break;
				case 2:
        			itmName = GetGeneratedItem("blade23");
				break;
				case 3:
        			itmName = GetGeneratedItem("blade24");
				break;
				case 4:
        			itmName = "pistol4";
				break;
				case 5:
        			itmName = "indian11";//"idol";
				break;
				case 6:
                    itmName = GetGeneratedItem("topor2"); // to_do
					//itmName = "map_good";
				break;
				case 7:
        			itmName = "spyglass4";
				break;
				case 8:
        			//itmName = "cirass5";
        			itmName = "cirass4";
				break;
				case 9:
        			itmName = "indian11";
				break;
				case 10:
        			itmName = "cirass3";
				break;

				case 11:
        			itmName = "spyglass5";
				break;
				case 12:
        			itmName = GetGeneratedItem("blade25");
				break;
				case 13:
        			itmName = GetGeneratedItem("blade26");
				break;
				case 14:
        			itmName = GetGeneratedItem("blade30");
				break;
				case 15:
        			itmName = GetGeneratedItem("blade33");
				break;				
				case 16:
        			itmName = "mushket";
				break;					
			}
			if (GetCharacterItem(Pchar, itmName) > 0)
		    {
          		itmName = "";
		    }
		    i++;
	    }
	    if (itmName != "")
	    {
	        item.BoxTreasure.(itmName) = 1;
	    }
	}
}

void SetTreasureBoxFromMap()
{
    aref   item;
    ref    loc;
    string box;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(Pchar, "map_full")>0 )
    {
        Log_Info("Сокровища где-то рядом!");
        PlaySound("Notebook");
		Statistic_AddValue(Pchar, "Treasure", 1);
        // немного веселой жизни
        TraderHunterOnMap();
        if( CheckAttribute(Pchar,"location.from_sea") )
        {
            if (rand(2) == 1) //33%
            {
                Pchar.quest.SetTreasureHunter.win_condition.l1          = "location";
                Pchar.quest.SetTreasureHunter.win_condition.l1.location = Pchar.location.from_sea;
                Pchar.quest.SetTreasureHunter.win_condition             = "";
                Pchar.quest.SetTreasureHunter.function    = "SetTreasureHunter";
            }
        }

        Items_FindItem("map_full", &item);

        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure =  true; // признак сокровища в сундуке

        DeleteAttribute(item, "MapIslId");
        TakeNItems(Pchar, "map_full", -1);
    }
}
//  Карты сокровищ  ГЕНЕРАТОР <--

// погодня за ГГ на карте
void  TraderHunterOnMap()
{
    // немного веселой жизни
    ref  sld;
    int  i;

    string sCapId = "Follower0";
    string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    for (i = 1; i <= GetCompanionQuantity(pchar); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 15, true), F_PIRATE);
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = "Джентльмены удачи";
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateWarrior("", sCapId + "1", 8);
}

void SetTreasureHunter(string temp)
{
    int    j, i, k;
	string sTemp, sCapId;
	ref    sld;
	bool   ok;

	if (chrDisableReloadToLocation) return; // идет некий другой квест с запретом выхода
	
    Pchar.GenQuest.Hunter2Pause            = true;
    
    j = GetOfficersQuantity(Pchar) + 2;
    
	sCapId = "LandHunter0";
    sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
    for (i = 1; i <= j; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 0, true, F_MERCENARY));
        SetFantomParamHunter(sld); //крутые парни
        sld.Dialog.CurrentNode = "TreasureHunter";
        sld.dialog.filename = "Hunter_dialog.c";
        sld.greeting = "Gr_HUNTER";
        sld.location = "none"; // вот где порылась собака!!!!!!!!!!!

        SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;
		
        LAi_SetActorTypeNoGroup(sld);
        LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
        if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
        {
            ok = false;
            break;
        }
        LAi_ActorFollow(sld, pchar, "", 8.0);
        //LAi_Actor2WaitDialog(sld, pchar); // ждать диалог, но бежать
        LAi_group_MoveCharacter(sld, sTemp);
    }

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //сразу генерим
        PChar.HunterCost.Qty = i;
        PChar.HunterCost.TempHunterType = "";
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("OpenTheDoors", 5.0);
    }
}
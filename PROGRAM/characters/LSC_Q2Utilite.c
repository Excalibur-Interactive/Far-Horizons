// Warship -->
// Выставлялка рандомных скиллов
void SetRandSelfSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Leadership = _min + rand(iDelta);
	_ch.skill.Fencing = _min + rand(iDelta);
	_ch.skill.Pistol = _min + rand(iDelta);
	_ch.skill.Fortune = _min + rand(iDelta);
	_ch.skill.Sneak = _min + rand(iDelta);
}

void SetRandShipSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Sailing = _min + rand(iDelta);
	_ch.skill.Commerce = _min + rand(iDelta);
	_ch.skill.Accuracy = _min + rand(iDelta);
	_ch.skill.Cannons = _min + rand(iDelta);
	_ch.skill.Repair = _min + rand(iDelta);
	_ch.skill.Grappling = _min + rand(iDelta);
	_ch.skill.Defence = _min + rand(iDelta);
}

// Установить персу все перки
void SelAllPerksToChar(ref _ch, bool _isOfficer)
{
    
}

// Установить персу половину перков
void SetHalfPerksToChar(ref _ch, bool _isOfficer)
{
	
}

// Отобрать все предметы (кроме квестовых) у выбранного персонажа
void RemoveAllCharacterItems(ref _ch, bool _removemoney)
{
	RemoveCharacterEquip(_ch, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(_ch, GUN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, CIRASS_ITEM_TYPE);
	
	//сносим все предметы, кроме квестовых -->
	aref arItems;
	string sName;
	ref rLoc;
	makearef(arItems, _ch.items);
	int	Qty = GetAttributesNum(arItems);
	for (int a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			_ch.questTemp.items.(sName) = _ch.items.(sName);
		}
	}			
	DeleteAttribute(_ch, "items");
	_ch.items = "";
	makearef(arItems, _ch.questTemp.items);
	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{		
		sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(_ch, sName, sti(arItems.(sName)));
	}		
	DeleteAttribute(_ch, "questTemp.items");
	
	if(_removemoney)
	{
		_ch.money = 0;
	}
}

// снести всех пассажиров и компаньонов ГГ
void RemoveAllPassengersAndCompanions()
{
    int iDay = GetPassengersQuantity(pchar);
    int i = 0;
    int n = 0;
	int idx;
	ref ch;
	
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx == -1) break;
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
}

void CleanAllCabinBoxes()
{
	ref loc;
	int n;
	string sTemp;
	
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
}

// Метод вернет случайный тип корабля, который зависит от класса шипа персонажа
int RandShipFromShipClass(ref _ch)
{
	int iShipClass = sti(RealShips[sti(_ch.Ship.Type)].Class);
	int iShipType;
	switch(iShipClass)
	{
		case 1:
			iShipType = SHIP_WARSHIP + rand(2);
			break;
			
		case 2:
			iShipType = SHIP_FRIGATE + rand(1);
			break;
		
		case 3:
			iShipType = SHIP_CORVETTE + rand(2);
			break;
			
		case 4:
			iShipType = SHIP_FLEUT + rand(2);
			break;
			
		case 5:
			iShipType = SHIP_BARQUE + rand(1);
			break;
			
		case 6:
			iShipType = SHIP_SLOOP + rand(1);
			break;
			
		case 7:
			iShipType = SHIP_WAR_TARTANE + rand(1);
			break;
	}
	return iShipType;
}

// Проверка, есть ли у ГГ казначей
bool IsPCharHaveTreasurer()
{
	ref rOfficer;

	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		rOfficer = &characters[i];
		if(CheckAttribute(rOfficer, "treasurer") && sti(rOfficer.Treasurer) == 1)
		{
			return true; // Казначей есть
		}
		
	}
	
	return false;
}

// Метод вернет ссылку на казначея
ref GetPCharTreasurerRef()
{
	if(!IsPCharHaveTreasurer()) return &NullCharacter;
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if(CheckAttribute(&characters[i], "treasurer") && sti(characters[i].Treasurer) == 1)
		{
			return &characters[i];
		}
	}
	
	return &NullCharacter;
}

// Метод вернет значение атрибута
string GetAttrValue(ref _rChar, string _sAttr)
{
	string sTemp;
	if(!CheckAttribute(_rChar, _sAttr)) _rChar.(_sAttr) = "";
	
	sTemp = _rChar.(_sAttr);
	return sTemp;
}

// Получить рандомную локацию с указанным типом на заданном острове
string IslandGetLocationFromType(string _island, string _type)
{
	ref rLoc;
	int i, iMaxLoc[MAX_LOCATIONS];
	int iRandLoc = 0;
	for(i=1; i<MAX_LOCATIONS; i++)
	{
		makeref(rLoc, locations[i]);
		if(findsubstr(rLoc.id, _type, 0) != -1 && rLoc.islandId == _island)
		{
			iMaxLoc[iRandLoc] = i;
			iRandLoc++;
		}
	}
	
	if(iRandLoc == 0)
		return "none";
	
	i = iMaxLoc[rand(iRandLoc-1)];
	return locations[i].id;
}

// Просто сокращение -->
void DisableAllExits(bool _truefalse)
{
	chrDisableReloadToLocation = _truefalse;
	bDisableFastReload         = _truefalse;
}
// Просто сокращение <--

// Warship <--

void LockQuestLine(ref refChar) // Лочим квестовую линейку
{
	refChar.notQuestLine = true;
}

string QuestGetGangLocation(string _areal)	// Получить локацию для генерации банд и т.д.
{
	int n;
	string island = GetArealByCityName(_areal);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if(GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if(CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if(findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[rand(howStore-1)];
	return locations[n].id;
}

string QuestGetColony(string _city) // Получить рандомную колонию по аттрибуту NPChar.city, не равную _city
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != _city)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

string GetColonyExpect2Colonies(string _city1, string _city2) // Исключая две колонии
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;
	ref rColony;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		if(!CheckAttribute(rColony, "HasNoFort") && rColony.nation != "none" && sti(rColony.nation) != PIRATE && GetRelation2BaseNation(sti(rColony.nation)) != RELATION_ENEMY && rColony.id != "Panama" && rColony.id != _city1 && rColony.id != _city2)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

// инициализация мультиобъектов - по дефолту рецепты ГГ не доступны
void InitAlchemy()
{
	ref item;		
	for(int n = 0; n < ITEMS_QUANTITY; n++)
	{
		item = &Items[n];
		if(CheckAttribute(item,"multiobject"))
		{
			string sGood = item.id;
			pchar.alchemy.(sGood).isKnown = false;
		}
	}
}

// проверка - знает ли ГГ рецепт мультиобъекта
bool isMultiObjectKnown(string itemId)
{
	ref item;		
	for(int n = 0; n < ITEMS_QUANTITY; n++)
	{
		item = &Items[n];
		if( CheckAttribute(item,"multiobject") )
		{
			string sGood = item.id;
			if(sGood == itemId && pchar.alchemy.(sGood).isKnown == true) return true;
		}
	}
	return false;
}

void SetAlchemyRecipeKnown(string Recipe)
{
	pchar.alchemy.(Recipe).isKnown = true;
}

void initStartState2Character(ref ch)
{// метод вызывается в момент новой игры, заполняет главного героя атрибутами, чтоб убрать лишние проверки в if
    NullCharacter.Siege = "";
    
	ch.SystemInfo.SaveCount = 0;
    ch.SystemInfo.LoadCount = 0;
    ch.SystemInfo.DeadCount = 0;

    ch.SystemInfo.CabinType          = ""; // boal 28.03.05 каюты нет  My_Cabin_Small
    
    ch.questTemp.Contraband.relation = 60;
    DeleteAttribute(ch, "quest.meeting");
    ch.ShipInStock = 0; // кораблей в порту
	ch.questTemp.abordage = 0;   // двойной абордаж
	ch.questTemp.donate   = 0; // пожертвование церкви

	ch.questTemp.friend_in_tavern = ""; // оптимизация boal
	ch.questTemp.RelationAgentMet = "0"; // оптимизация boal

	ch.questTemp.NationQuest = ""; // взятая линейка квестов

	ch.I_MAP_SHOW = false;  // boal карты смотрим из предметов
	ch.CameraHoldPos = false;
	ch.CameraShipNPC = 0;// номер компаньона для камеры 0 - ГГ
	ch.GenQuestFort.FarLocator = true; // для методов пихания фантомов в город

	// ==> состояние квеста текущей линейки
	ch.questTemp.State = "";
	// ==> кол-во дней ожидания выдачи следующего квеста губером, стандарт - два дня
	ch.questTemp.Waiting_time = "2";
	// ==> номер текущего квеста, присваиваем сразу второй, т.к. первый берется на момент первого обращения к губеру.
	ch.questTemp.CurQuestNumber = "2";
	//параметры островов и бухт для корсарского метро, ПГГ, и много еще чего :)
	InitTravelMap();
	// ==> Количество карт в навигационном атласе
	ch.MapsAtlasCount = 0;
	// ==> Номер пиратского флага (берется из текстуры персональных флагов ГГ)
	ch.Flags.Pirate = 5;
	// ==>  флаги и иниты бергларов 
	// ==>  нищие
	PoormansInit();
	// ==>  кол-во лута, отданного шлюхами
	pchar.questTemp.HorseLoot = 0;
	// ==>  кол-во перетраха со шлюхами
	pchar.questTemp.HorseQty = 0;
	// ==> тюремный флаг на проход внутрь
	ch.questTemp.jailCanMove = false;
	// ==> набор мелких квестов, дается по одному до закрытия
	ch.questTemp.different = "free";
	ch.questTemp.CapBUnarmed = false; //ГГ сабля не положена - false
	// ==> установка алхимии (знакомы рецепты или нет - по умолчанию на начало новой игры все рецепты не знакомы)
	InitAlchemy();
    //Избранные зелья
	ch.GenQuest.Potion_choice.v1 = "";
	ch.GenQuest.Potion_choice.v2 = "";
	ch.GenQuest.Poison_choise = "";
    ch.GenQuest.Potion_choice.variant = "";
}

//==> eddy. квестовая обработка 'ноль часов'.
void QuestActions()
{
	ref sld;
	int i;
	CompanionTravel_ProcessAllTravellers(); // Warship. Процессирование компаньонов-путешественников
	// забираем просроченные лицензии
	for (i=0; i<4; i++)
	{
		if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence") && GetDaysContinueNationLicence(i) == -1)
		{
			TakeNationLicence(i);
		}		
	}
	
	// ************** поверка нпс-кэпов 5 и 20 числа каждого месяца *******************
	if (GetDataDay() == 5 || GetDataDay() == 20)
	{
		if (CheckAttribute(NullCharacter, "capitainBase"))
		{
			string sName;
			int capIndex, a;
			aref arCapBase, arBase;
    		makearef(arBase, NullCharacter.capitainBase);
    		int	Qty = GetAttributesNum(arBase);
    		for (a=0; a<Qty; a++)
    		{
    			arCapBase = GetAttributeN(arBase, a);
				sName = GetAttributeName(arCapBase); //Id кэпа
				capIndex = GetCharacterIndex(sName);
    			//---------- мертв ------------
				if (capIndex == -1)
    			{
					DeleteAttribute(arBase, sName);
					Qty --; //для корректной работы цикла при удалении записи в базе
					a--;
				}
				//---------- жив ------------
				else
				{
					if (GetNpcQuestPastDayParam(arCapBase, "checkTime") >= sti(arCapBase.checkTime))
					{
						Cap_SetMapAgain(&characters[capIndex], arCapBase);
					}
				}		
    		}
		}
	}
}

//снятие квеста, если энкаунтер кэпа исчез на карте
void CitizCapIsDead_CloseQuest(aref arCapBase, string capId)
{
	ref sld;
	string sTemp;
	//снимаем установленный таймер
	sTemp = "SecondTimer_" + capId;
	if (capId == "MushketCap") sTemp = "MushketTimer";
	if (capId == "Danielle")   sTemp = "DanielleTimer";
	pchar.quest.(sTemp).over = "yes";
	//---------- нпс-квестодатель -------------
	int iTemp = GetCharacterIndex(arCapBase.questGiver);
	if (iTemp != -1)
	{
		//снимаем прерывание на смерть квестодателя
		ref npchar = &characters[iTemp];
		if (CheckAttribute(npchar, "quest.PortmansSeekShip") || CheckAttribute(npchar, "quest.PortmansJornal"))
		{
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			DeleteAttribute(npchar, "quest.PortmansJornal");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		}
		else
		{
			sTemp = "SCQ_" + iTemp;
			pchar.quest.(sTemp).over = "yes"; 
			characters[iTemp].lifeDay = 0;
		}
	}
	string sTitle1 = arCapBase.Tilte1;
	string sTitle2 = arCapBase.Tilte2;
}

//переустанавливаем на карте живого, но потерянного кэпа
void Cap_SetMapAgain(ref sld, aref arCapBase) 
{
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	switch (arCapBase.quest)
	{
	case "mushket": 
		if (sld.cityShore == sld.quest.targetShore)
		{
			sld.quest.targetShore = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "citizen": 
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "robber": 
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "jornal": 
		if (sld.quest.baseShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.quest.baseShore);
		}
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "Danielle": 
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	}
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

// -- нищие --
void PoormansInit()
{
	ref sld;
	//нищий в Сент-Джонсе
	sld = GetCharacter(NPC_GenerateCharacter("SentJons_Poorman", "panhandler_1", "man", "man", 5, ENGLAND, -1, false, F_CITY));
	sld.city = "SentJons";	
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Бриджтауне
	sld = GetCharacter(NPC_GenerateCharacter("Bridgetown_Poorman", "panhandler_1", "man", "man", 5, ENGLAND, -1, false, F_CITY)));
	sld.city = "Bridgetown";
	sld.location	= "Bridgetown_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Белизе
	sld = GetCharacter(NPC_GenerateCharacter("Beliz_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "Beliz";
	sld.location	= "Beliz_town";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.forStay.locator = "goto9"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto7";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Каракасе
	sld = GetCharacter(NPC_GenerateCharacter("Caracas_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "Caracas";
	sld.location	= "Caracas_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.forStay.locator = "goto20"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto21"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Картахене
	sld = GetCharacter(NPC_GenerateCharacter("Cartahena_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto18";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto6";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("Cumana_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto13";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Бас-Тере, Гваделупа
	sld = GetCharacter(NPC_GenerateCharacter("BasTer_Poorman", "panhandler_1", "man", "man", 5, FRANCE, -1, false, F_CITY)));
	sld.city = "BasTer";
	sld.location	= "BasTer_town";
	sld.location.group = "goto";
	sld.location.locator = "goto18";
	sld.forStay.locator = "goto18"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto24";
	sld.forSit.locator1 = "goto16"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto17";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Гаване
	sld = GetCharacter(NPC_GenerateCharacter("Havana_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "Havana";
	sld.location	= "Havana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto22"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Порт Рояле
	sld = GetCharacter(NPC_GenerateCharacter("PortRoyal_Poorman", "panhandler_1", "man", "man", 5, ENGLAND, -1, false, F_CITY)));
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto28"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto7";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Форт-де-Франсе, Мартиника
	sld = GetCharacter(NPC_GenerateCharacter("FortFrance_Poorman", "panhandler_1", "man", "man", 5, FRANCE, -1, false, F_CITY)));
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.forStay.locator = "goto4"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto14";
	sld.forSit.locator1 = "goto10"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий на Невисе
	sld = GetCharacter(NPC_GenerateCharacter("Charles_Poorman", "panhandler_1", "man", "man", 5, ENGLAND, -1, false, F_CITY)));
	sld.city = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto19";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Порто Белло
	sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "PortoBello";
	sld.location	= "PortoBello_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto12";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Порт-о-Принс, Эспаньола
	sld = GetCharacter(NPC_GenerateCharacter("PortPax_Poorman", "panhandler_1", "man", "man", 5, FRANCE, -1, false, F_CITY)));
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14";
	sld.forStay.locator = "goto14"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto25";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto11";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("Santiago_Poorman", "panhandler_1", "man", "man", 5, SPAIN, -1, false, F_CITY)));
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto28";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Мариго, Сан Мартин
	sld = GetCharacter(NPC_GenerateCharacter("Marigo_Poorman", "panhandler_1", "man", "man", 5, HOLLAND, -1, false, F_CITY)));
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto4"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto9";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//нищий в Тортуге
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Poorman", "panhandler_1", "man", "man", 5, FRANCE, -1, false, F_CITY)));
	sld.city = "Tortuga";
	sld.location	= "Tortuga_town";
	sld.location.group = "goto";
	sld.location.locator = "goto23";
	sld.forStay.locator = "goto23"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto18"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Порт Спейне, Тринидад
	sld = GetCharacter(NPC_GenerateCharacter("PortSpein_Poorman", "panhandler_1", "man", "man", 5, ENGLAND, -1, false, F_CITY)));
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

//ищем город определенной нации, проверять наличие ростовщика и тавернщика
string GetQuestNationsCity(int _nation)
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == _nation && GiveArealByLocation(loadedLocation) != colonies[n].island) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && GetCharacterIndex(colonies[n].id + "_usurer") > 0)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

//ищем не вражескую колонию, куда можно доплыть
string SelectNotEnemyColony(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

//ищем любую национальную колонию, куда можно доплыть
string SelectAnyColony(string _City)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string SelectAnyColony2(string _City1, string _City2)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City1) != colonies[n].islandLable && GetIslandByCityName(_City2) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

//отдать забытый судовой журнал. помещаем в город кэпа, который приплыл к назначенной колонии
void SetCapitainFromSeaToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг в городе
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	sld.location	= sld.City + "_PortOffice";
	sld.location.group = "goto";
	sld.location.locator = "goto"+(rand(2)+1);
	LAi_SetCitizenType(sld);

	//таймер через сколько опять выйти в море
	int Qty = rand(4)+3;
	string name = "Timer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetCapitainFromCityToSea";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп в городе
	AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас в городе. Кажется, его зовут " + GetFullName(sld) + ". Он сейчас должнен быть у начальника порта.", 
		"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно застать у начальника порта.", 
		"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то идите прямоком к начальнику порта. " + GetFullName(sld) + " сейчас там..."), sld.City, Qty, 1, "none");
}
//отдать забытый судовой журнал. записть в квестбук из слухов
void PortmansBook_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;	
		string sTitle = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//разыскать кэпа-вора. помещаем в город кэпа, который приплыл к назначенной колонии
void SetRobberFromMapToSea(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InPort"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города

	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);

	//таймер через сколько опять выйти на карту
	int Qty = rand(5)+4;
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetRobberFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп на рейде
	AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' стоит в порту на рейде. Кажется, его зовут " + GetFullName(sld) + ". Странный тип, скажу я вам, на берег не сходит вообще.", 
		"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно встретить, только если выйти на шлюпке в порт. Корабль стоит на рейде, но капитан в город не выходит, предпочитает оставаться на корабле. И и недоело ему?..", 
		"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то выходите в порт. " + GetFullName(sld) + " вроде бы его зовут... В общем, он бросил якорь в порту, но на берег не сходит. Настоящий морской волк, даже с палубной качкой расставаться не хочет."), sld.City, Qty, 1, "none");
}
//разыскать кэпа-вора. запись в квестбук из слухов
void PortmansSeekShip_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;	
		ref npchar = &characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")];
		string sTitle = npchar.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "3");
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName)));
		AddQuestUserData(sTitle, "sShipName", sld.Ship.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		iTemp = RealShips[sti(sld.Ship.Type)].basetype;
		AddQuestUserData(sTitle, "sSexWord", GetShipSexWord(ShipsTypes[iTemp].name, "ушел", "ушла"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//розыск кэпов горожанами
void CitizCapFromMapToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города
	if (rand(1))
	{	//ходит в городе
		sld.location	= sld.City + "_town";
		sld.location.group = "goto";
		sld.location.locator = "goto"+(rand(5)+1);
		LAi_SetCitizenType(sld);
		string slai_group = GetNationNameByType(sti(colonies[iColony].nation))  + "_citizens";
		LAi_group_MoveCharacter(sld, slai_group);
		//даем слух, что кэп на рейде
		AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' в городе. Кажется, его зовут " + GetFullName(sld) + ".", 
			"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно застать в городе.", 
			"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то поищите его в на улицах. " + GetFullName(sld) + " вроде бы его зовут..."), sld.City, Qty, 1, "none");
	}
	else
	{	//стоит на рейде в порту
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_AddCharacter(sGroup, sld.id);			
		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
		Group_SetTaskNone(sGroup);
		//даем слух, что кэп на рейде
		AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' находится в порту на рейде. Кажется, его зовут " + GetFullName(sld) + ".", 
			"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно застать в нашем порту. Его корабль стоит на рейде.", 
			"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то поищите его корабль в нашем порту. " + GetFullName(sld) + " вроде бы его зовут..."), sld.City, Qty, 1, "none");
	}
	//таймер через сколько опять выйти на карту
	int Qty = rand(7)+5; //через сколько дней выйдем на карту
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "CitizCapFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//разыск кэпа от горожан. запись в квестбук из слухов
void CitizSeekCap_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)];
		string sTitle = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "3");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//таймер
void SetShowTimer(float time)
{
	pchar.showTimer = time + 0.99;
	pchar.quest.ClearTimer.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ClearTimer.win_condition.l1.location = pchar.location;
	pchar.quest.ClearTimer.function = "ClearTimer";
}

void ClearTimer(string qName)
{
	DeleteAttribute(pchar, "showTimer");
	ClearAllLogStrings();
}

//создание резервной базы на абордажников для юза нефритового черепа
void CopyPassForAztecSkull()
{
	if (CheckCharacterItem(pchar, "totem_32"))
	{	
        //сносим старую базу
		DeleteAttribute(pchar, "totem_32");
		pchar.totem_32 = "";
		//заполняем архивную базу 
		string sTemp;
		aref	arFromBox, arToBox;
    	makearef(arFromBox, pchar.fellows.passengers.officers);
		makearef(arToBox, pchar.totem_32);
		CopyAttributes(arToBox, arFromBox);
	}
}

bool IsAztecSkullOfficer(ref sld)
{
	if (!CheckAttribute(pchar, "totem_32.id1")) return false;
	string sTemp;
	aref arOfficer;
    makearef(arOfficer, pchar.totem_32);
    for (i=1; i<=3; i++)
    {
		sTemp = "id" + i;
		if (arOfficer.(sTemp) == sld.index)
		{
			return true;
		}
	}
	return false;
}

// --> ugeen 20.06.09 - проверка на наличие карт у ГГ
bool CheckMainHeroMap(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )	
	{
		return true;
	}
	return false;	
}
// <-- ugeen
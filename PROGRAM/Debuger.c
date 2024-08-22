// BOAL нажатие на F12 вызывает этот код. Его можно править с alt-tab в игре, изменения будут сразу
void ActiveF7Control()
{
	// Warship. Убить боижайшего персонажа
	int characterIndex = LAi_FindNearestVisCharacter(PChar, 25);
	ref characterRef;
	
    if(characterIndex != -1)
	{
		characterRef = &Characters[characterIndex];
		
		if(!LAi_IsImmortal(characterRef)) // Квестовые
		{
			LAi_KillCharacter(characterRef);
			Log_Info("Убили персонажа с ID == " + characterRef.Id);
		}
		else	
		{
			Log_Info("Нельзя убить персонажа с ID == " + characterRef.Id);
		}
	}
}

void ActiveF10Control()
{
	SetCharacterModelAndAnimation(pchar, "hunter_3", "man");
}

///  статы персонажа в близи
void ActiveF12Control()
{
    ref mainCh = GetMainCharacter();
    
	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	
	
	string dopinfo = "";
	
    //Найти ближайшего видимого персонажа в заданном радиусе
    int res = LAi_FindNearestVisCharacter(mainCh, 15);
    if (res != -1)
    {
		ref findCh = GetCharacter(res);
		if(CheckAttribute(findCh, "NoF12")) return;
		
		bool bChar = findCh.chr_ai.group == LAI_GROUP_PLAYER || bBettaTestMode;//Экку Korsar - некоторую инфу можно узнать только, если персонаж в команде игрока.
		
		if(CharIsMushketer(findCh)) dopinfo = " (Мушкетёр)";
		else
		{
		    if(CheckAttribute(findCh, "equip.blade")) dopinfo = " (Фехтовальщик)";
		}
		
		string sEBG = "";
		if(bBettaTestMode) sEBG = " Индекс: " + findCh.index;
		
    	ref rIFID;
		
        res = findCh.chr_ai.hp;
        Log_SetStringToLog("" + GetFullName(findCh) + dopinfo);
        Log_SetStringToLog(""+ XI_ConvertString("Rank") +" " + findCh.rank + " "+ XI_ConvertString("Health") +" "+ res + "/" + LAi_GetCharacterMaxHP(findCh) + sEBG);
		
		if (bChar && CheckAttribute(findCh, "equip.blade"))
        {
			sEBG = GetCharacterEquipByGroup(findCh, BLADE_ITEM_TYPE);
    	    rIFID = ItemsFromID(sEBG);
            Log_SetStringToLog("Клинок - " + GetAssembledString(LanguageConvertString(lngFileID, rIFID.name), rIFID));
        }
		
        if (bChar && CheckAttribute(findCh, "equip.gun"))
        {
			sEBG = GetCharacterEquipByGroup(findCh, GUN_ITEM_TYPE);
    	    rIFID = ItemsFromID(sEBG);
            Log_SetStringToLog("Огнестрел - " + GetAssembledString(LanguageConvertString(lngFileID, rIFID.name), rIFID));
        }

        if(findCh.chr_ai.group == LAI_GROUP_PLAYER || bBettaTestMode)
        {
            if (CheckAttribute(findCh, "chr_ai.bullet"))
            {
	            Log_SetStringToLog("Патрон - " + GetAssembledString(LanguageConvertString(lngFileID, Items[GetItemIndex(findCh.chr_ai.bullet)].name), Items[GetItemIndex(findCh.chr_ai.bullet)]));
	        }

    	    if(CheckAttribute(findCh, "chr_ai.gunpowder"))
            {
		        if(findCh.chr_ai.gunpowder != "")
	            {
        	       Log_SetStringToLog("Порох используется");
	            }
		        else
	            {
    	            Log_SetStringToLog("Порох не требуется");	
	    	    }
	        }
        }

	    if (bBettaTestMode)
        {
            Log_SetStringToLog("Айди - " + findCh.id);
            Log_SetStringToLog("Индекс - " + findCh.index);
            
            if(CheckAttribute(findCh, "LifeDay")) Log_Info("Дней живёт - " + findCh.LifeDay);

	        if(CheckAttribute(findCh, "City")) Log_Info("Город - " + findCh.City);
			
			if(CheckAttribute(findCh, "Greeting")) Log_Info("Приветствие - " + findCh.Greeting);
			
            Log_SetStringToLog("Модель - " + findCh.model);
            Log_SetStringToLog("Портрет - " + findCh.faceId);
            Log_SetStringToLog("Тип персонажа - " + findCh.chr_ai.type);
            Log_SetStringToLog("Группа локаторов - "+findCh.location.group + " локатор - " + findCh.location.locator);
			
            if(CheckAttribute(findCh, "chr_ai.FencingType"))
            {
                Log_SetStringToLog("Тип клинка - " + findCh.chr_ai.FencingType));
            }
            else
            {
                Log_SetStringToLog("Нет типа фехтования - error");
            }

		    Log_SetStringToLog("Нация: " + NationNameNominative(sti(findCh.nation)));
		    Log_SetStringToLog("Фракция: " + FractionNameNominative(sti(findCh.fraction)));
	    	Log_SetStringToLog("Пол: " + findCh.sex);
			
	    	if(CheckAttribute(findCh, "chr_ai.group")) Log_SetStringToLog("Группа: " + findCh.chr_ai.group);
	    	if(CheckAttribute(findCh, "chr_ai.tmpl")) Log_SetStringToLog("Темплейт: " + findCh.chr_ai.tmpl);

            mainCh.SystemInfo.OnlyShowCharacter = true;
	    	LaunchCharacter(findCh);
        }
        else
        {
            if (MOD_BETTATESTMODE == "Test")
	        {
	            Log_SetStringToLog("Id - " + findCh.id);
	        }
        }
    }
	LanguageCloseFile(lngFileID);
}

///////////////////////////// test //////////////
void TestColonyCommanders()
{
	int iChar;

	string sColony;

	int i;
	float x, y, z;  // boal

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // необитайки
		// зададим базовых мэров городов
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // мэр есть
        	Log_Info("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        	trace("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        }

		// добавить проверку на пиратов, у них нет фортов, нафиг им коммандер?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
			continue;
		}
		iChar = GetCharacterIndex(colonies[i].id + " Fort Commander");
		Log_Info("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
  		trace("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
	}
}
// проверка ликвидности товара - цена-вес, что выгоднее - выводим в компил.лог список, строим заполняя трюм товаром по одной пачке
void TestGoodsLiquidity()
{
	int i, j, idx;
	float fMaxCost;
	
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		SetCharacterGoods(pchar, i, sti(Goods[i].Units));
	}
	trace("======= TestGoodsLiquidity ======== start ");
	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1; 
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(pchar, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight)) 
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				} 
			}
		}
		if (fMaxCost > 0)
		{
			SetCharacterGoods(pchar, idx, 0);	
			trace(Goods[idx].Name + " = " + fMaxCost);
			Log_info(Goods[idx].Name + " = " + fMaxCost);
		}
	}
	trace("======= TestGoodsLiquidity ======== end ");
}

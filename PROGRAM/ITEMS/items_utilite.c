bool IsQuestUsedItem(string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return false;
	if( CheckAttribute(arItm,"price") && sti(arItm.price)>0 ) return false;
	return true;
}

void DoCharacterUsedItem(ref chref, string itmID)
{
	aref arItm;
	int  idLngFile, iTime, iHealth;
	bool CanUse = true;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	if( Items_FindItem(itmID,&arItm)<0 ) return;
	
	if(CheckAttribute(arItm, "potion.special") && CheckAttribute(arItm, "potion.special.effect"))
	{
	    if(CheckAttribute(chref, "SpeciaPotionEffect."+arItm.potion.special.effect))
    	{
	        if(chref.id == pchar.id) Log_TestInfo("Куда второе одинаковое уберзелье пьёшь?!");
	        return;
    	}
	}
		
	TakeItemFromCharacter(chref,itmID);

	 // Warship 13.06.09 fix - если только отравлен, а жизни полные (а такое бывает), то нечего и строку в лог выводить об прибавлении жизней
	if(CheckAttribute(arItm,"potion.health") && LAi_GetCharacterHP(chref) < LAi_GetCharacterMaxHP(chref))
	{
		if(CheckAttribute(chref, "chr_ai.NoAntidotes"))
		{
			CanUse = false;
			if(CheckAttribute(arItm, "potion.antidote"))
			{
				if(!CheckAttribute(chref, "chr_ai.NoMixtureTime"))
				{
			    	chref.chr_ai.DrinkedMixtures = sti(chref.chr_ai.DrinkedMixtures) + 1;
			    	Log_TestInfo("Выпито микстур - " + sti(chref.chr_ai.DrinkedMixtures));
			    	if(sti(chref.chr_ai.DrinkedMixtures) >= 1) CanUse = true;
				}
				else Log_TestInfo("Время действия анти-антидота для микстур ещё не прошло!");
			}
		}
		
		if(CanUse)
		{
		    LAi_UseHealthBottle(chref,stf(arItm.potion.health));
		    if(sti(chref.index)==GetMainCharacterIndex())
	    	{
    			Log_SetStringToLog( XI_ConvertString("Health Up"));
		    }
	    	// boal
    		if( CheckAttribute(arItm,"potion.health.speed") )
    		{
    			LAi_UseHealthBottleSpeed(chref, stf(arItm.potion.health.speed));
    		}
		}
	}
	
	// Спешлы
	if(CheckAttribute(arItm, "potion.special") && CheckAttribute(arItm, "potion.special.effect"))
	{
		if(CheckAttribute(arItm, "potion.special.time")) iTime = arItm.potion.special.time;
		else iTime = -1;
		
		if(CheckAttribute(arItm, "potion.special.Health")) iHealth = arItm.potion.special.Health;
		else iHealth = 0;
		
		if(sti(chref.index) == GetMainCharacterIndex())
		{
			Log_SetStringToLog("Использовано спец-зелье "+ LanguageConvertString(idLngFile, arItm.name));
		}
		else
		{
			Log_SetStringToLog("Персонажем " + GetFullName(chref) + " использовано спец-зелье "+ LanguageConvertString(idLngFile, arItm.name));
		}
		
		LAi_UseSpecialPotion(chref, arItm.potion.special.effect, iHealth, iTime);
	}
	
	// Warship 13.06.09 fix - если не отравлен, то нечего и строку в лог выводить
	if(CheckAttribute(arItm,"potion.antidote") && LAi_IsPoison(chref))
	{
		//Экку Korsar - Взрыв мозга с пропиской временного запрета выпивания противоядий и микстур при отравлении легендарными ядами...
		if(CheckAttribute(chref, "chr_ai.NoAntidotes"))
		{
			CanUse = false;
			if(CheckAttribute(arItm, "potion.health"))
			{
				if(!CheckAttribute(chref, "chr_ai.NoMixtureTime"))
				{
			    	if(sti(chref.chr_ai.DrinkedMixtures) >= 1) CanUse = true;
				}
				else Log_TestInfo("Время действия анти-антидота для микстур ещё не прошло!");
			}
			else
			{
				if(!CheckAttribute(chref, "chr_ai.NoAntidoteTime"))
				{
	    			chref.chr_ai.DrinkedAntidotes = sti(chref.chr_ai.DrinkedAntidotes) + 1;
	    			Log_TestInfo("Выпито противоядий - " + sti(chref.chr_ai.DrinkedAntidotes));
	    			if(sti(chref.chr_ai.DrinkedAntidotes) >= 2) CanUse = true;
	    		}
				else Log_TestInfo("Время действия анти-антидота для противоядий ещё не прошло!");
			}
		}
		
		if(CanUse)
		{
		    LAi_UseAtidoteBottle(chref);
		    if(sti(chref.index)==GetMainCharacterIndex())
	    	{
	   			Log_SetStringToLog( XI_ConvertString("You are cured from poison") );
    		}
		    else
	    	{
	   			Log_SetStringToLog(GetFullName(chref) + XI_ConvertString("are cured from poison") );
   			}
		}
	}
	
	//navy --> алкоголь
	if (CheckAttribute(arItm, "potion.drunk") && !IsCharacterEquippedTalisman(chref, "totem_09"))
	{
		LAi_AlcoholSetDrunk(chref, stf(arItm.potion.drunk), stf(arItm.potion.drunk.time));
		if(sti(chref.index)==GetMainCharacterIndex())
		{
			Log_SetStringToLog( XI_ConvertString("You're get drunk") );
		}
	}
	//<--
	if( CheckAttribute(arItm,"potion.sound") )
	{
		PlaySound(arItm.potion.sound);
	}
	LanguageCloseFile(idLngFile);
}

float MinHealthPotionForCharacter(ref chref)
{
	float ftmp;
	bool isFinded = false;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if(CheckAttribute(&Items[n],"potion.health"))
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					if(isFinded)
					{
						if( stf(Items[n].potion.health)<ftmp )
						{
							ftmp = stf(Items[n].potion.health);
						}
					}
					else
					{
						ftmp = stf(Items[n].potion.health);
						isFinded = true;
					}
				}
			}
		}
	}
	if(!isFinded) return 0.0;
	return ftmp;
}

string FindHealthForCharacter(ref chref,float fHealth)
{
	string sret = "";
	float fdelta = fHealth + 100.0;
	float ftmp;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if( CheckAttribute(&Items[n],"potion.health") )
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					ftmp = stf(Items[n].potion.health);
					if( ftmp<fHealth )	{ftmp = fHealth - ftmp;}
					else	{ftmp = ftmp - fHealth;}
					if(ftmp<fdelta)
					{
						fdelta = ftmp;
						sret = Items[n].id;
					}
				}
			}
		}
	}

	return sret;
}

int FindPotionFromChr(ref chref, ref arFind, int startIdx)
{
	int i;
	aref arItm;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"potion") && GetCharacterItem(chref,Items[i].id) > 0 )
		{
			arFind = arItm;
			return i;
		}
	}
	return -1;
}

int UseBestPotion(ref chref, bool needAntidote)
{
	int i;
	int curPotionID = -1;
	int curPotionHealAmt = 0;
	int newPotionHealAmt = 0;
	bool potionTooGood = false;
	bool bValidPot;
	bool bSpecial = false;
	int reqHealAmt = LAi_GetCharacterMaxHP(chref) - LAi_GetCharacterHP(chref);
	reqHealAmt = makeint(MakeFloat(reqHealAmt) * 1.2)
	
	aref arItm;
	for(i=1; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		bValidPot = false;

		if (!needAntidote && CheckAttribute(arItm,"potion.health") && !CheckAttribute(arItm,"potion.antidote")) 
		{
			bValidPot = true;
		}
		else 
		{
			if (needAntidote && CheckAttribute(arItm,"potion.antidote")) 
			{
				bValidPot = true;
			}
		}
		if( bValidPot && (GetCharacterItem(chref,arItm.id) > 0))
		{
			if (CheckAttribute(arItm,"potion.health"))
				newPotionHealAmt = arItm.potion.health;
			else
				newPotionHealAmt = 0;
								
			if (potionTooGood) 
			{
				if (newPotionHealAmt < curPotionHealAmt) 
				{
					curPotionID = i;
					curPotionHealAmt = newPotionHealAmt;
				}
			}
			else
			{
				if ((newPotionHealAmt + 1) > curPotionHealAmt) 
				{
					if (curPotionHealAmt == 0 || newPotionHealAmt <= reqHealAmt) 
					{
						curPotionID = i;
						curPotionHealAmt = newPotionHealAmt;
					}
				}
			}
			if (curPotionHealAmt > reqHealAmt) 
			{
				potionTooGood = true;
			}
		}
	}
	
	switch(chref.GenQuest.Potion_choice.variant)
	{
		case "v1":
		    chref.GenQuest.Potion_choice.variant = "";
		    if (CheckCharacterItem(pchar, chref.GenQuest.Potion_choice.v1))
	   		{
                arItm = ItemsFromID(chref.GenQuest.Potion_choice.v1);
				if(CheckAttribute(arItm, "potion.special")) bSpecial = true;

		    	if(bSpecial)
                {
                    DoCharacterUsedItem(pchar, chref.GenQuest.Potion_choice.v1);
	   		        return 1;
                }
	   	    }
	   		else
		    {
                if(chref.GenQuest.Potion_choice.v1 == "")
                {
                    
                }
                else
                {
			        PlaySound("interface\notebook.wav");
			        log_info("Выбранное зелье отсутствует в инвентаре!");
			        log_info("Активирован автоматический выбор зелья");
			        chref.GenQuest.Potion_choice.v1 == "";
			        return 0;
                }
		    }
		break;
			
		case "v2":
		    chref.GenQuest.Potion_choice.variant = "";
		    if (CheckCharacterItem(pchar, chref.GenQuest.Potion_choice.v2))
	   		{
		    	if(bSpecial) 
                {
                    DoCharacterUsedItem(pchar, chref.GenQuest.Potion_choice.v2);
	   		        return 1;
                }
	   	    }
	   		else
		    {
			    if(chref.GenQuest.Potion_choice.v2 == "")
                {
                    
                }
                else
                {
			        PlaySound("interface\notebook.wav");
			        log_info("Выбранное зелье отсутствует в инвентаре!");
			        log_info("Активирован автоматический выбор зелья");
			        chref.GenQuest.Potion_choice.v2 == "";
			        return 0;
                }
		    }
		break;
	}

    if (reqHealAmt <= 0 && !needAntidote) 
	{
	     return -1;
	}

	if (curPotionID > 0) 
	{
		DoCharacterUsedItem(pchar, Items[curPotionID].id);
		return 1;
	}
	else return 0;
}

int FindQuestUsableItem(ref arFind, int startIdx)
{
	int i;
	aref arItm;
	bool bSeaInterface = bSeaActive && !bAbordageStarted;

	if(startIdx<0) startIdx=0;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"quest") && CheckAttribute(arItm,"quest.tex"))// boal 16.03.2004
		{
			if( bSeaInterface && arItm.quest.tex=="QuestCommands" )
			{
				arFind = arItm;
				return i;
			}
		}
	}

	return -1;
}

bool EnablePotionUsing(ref mc, aref arItm)
{
	if( CheckAttribute(arItm,"potion.health") )
	{
		if( LAi_GetCharacterHP(mc)<LAi_GetCharacterMaxHP(mc) )
		{
			return true;
		}
	}
	
	return false;
}

// Warship 13.06.09 Для противоядий
bool EnableAntidoteUsing(ref _char, aref _item)
{
	if(CheckAttribute(_item, "potion.antidote") && LAi_IsPoison(_char) && CheckCharacterItem(_char, _item.Id))
	{
		return true;
	}
	
	return false;
}

bool FindCharacterAntidote(ref _char, ref _itemId)
{
	int itemIndex;
	ref item;
	
	for(itemIndex = 0; itemIndex < ITEMS_QUANTITY; itemIndex++)
	{
		item = &Items[itemIndex];
		
		if(EnableAntidoteUsing(_char, item))
		{
			_itemID = item.ID;
			return true;
		}
	}
	
	return false;
}

int FindItem(string sItemID)
{	
	// Warship 07.07.09 Перевел на движковую функцию - по-идее, так должно работать быстрее
	return NativeFindCharacter(&Items, sItemID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Warship 08.05.09 НОВАЯ СИСТЕМА ПРЕДМЕТОВ -->
//      Ugeen --> 10.02.10 добавлена первичная генерация предметов и выбор из массива сгенерированных предметов
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ugeen --> вернем случайный ID сгенерированного зараннее предмета
string GetGeneratedItem(string _itemId)
{
	return GenerateItem(_itemID);
}

// Создадим предмет, вернет АйДи нового предмета
String GenerateItem(String _itemId)
{
	int defItemIndex;
	ref item, realItem;
	float MinAttack = 0;
	float MaxAttack = 0;
	
	float Block = 0;
	float Piercing = 0;
	float BlockResult = 0;
	float PiercingResult = 0;
	float FTypeMultiplier = 0;
	float QTypeMultiplier = 0;
	
	if(!IsGenerableItem(_itemId))
	{ // Генерящийся ли предмет
		return _itemID;
	}
	
	int itemIndex = FindFirstEmptyItem();
	if(itemIndex == -1)
	{ // mitrokosta нету свободных слотов - расширим массив предметов
		ExpandItemsArray();
		itemIndex = FindFirstEmptyItem();
	}
	
	defItemIndex = GetItemIndex(_itemId);
	item = &Items[defItemIndex];
	realItem = &Items[itemIndex];
	
	CopyAttributes(realItem, item); // Копируем аттрибуты

	realItem.ID = _itemId + "_" + itemIndex; // Новый АйДи предмету
	realItem.Index = itemIndex; // Новый индекс
	realItem.Generated = true; // Сгенерированный предмет
	realItem.DefItemID = _itemId; // Запомним АйДи и индекс начального предмета
	realItem.DefItemIndex = defItemIndex;
	
	switch (realItem.FencingType) 
	{
		case "Light" :
			realItem.Weight 	= 2.0 + fRandSmall(1.0); 
			MinAttack		= Light_MinAttack;
			MaxAttack		= Light_MaxAttack;
			FTypeMultiplier = 0.5;
		break;
		
		case "Middle" :
			realItem.Weight 	= 2.4 + fRandSmall(1.2);		
			MinAttack		= Middle_MinAttack;
			MaxAttack		= Middle_MaxAttack;
			FTypeMultiplier = 1.0;
		break;
		
		case "Heavy" :
			realItem.Weight 	= 3.0 + fRandSmall(1.5); 
			MinAttack		= Heavy_MinAttack;
			MaxAttack		= Heavy_MaxAttack;
			FTypeMultiplier = 1.5;
		break;
	}
	
	switch (realItem.SubType) 
	{
		case "Placeholder" :
			Block = 1;
			Piercing = 1;
		break;
		
		case "Spear" :
		    Block = 2;
			Piercing = 13;
		break;
		
		case "Dagger" :
			Block = 1;
			Piercing = 10;
		break;
		
		case "Rapier" :
			Block = 5;
			Piercing = 6;
		break;
		
		case "LightSword" :
			Block = 6;
			Piercing = 8;
		break;
		
		case "SmallSword" :
			Block = 5;
			Piercing = 7;
		break;
		
		case "Pickaxe" :
			Block = 1;
			Piercing = 12;
		break;
		
		case "Saber" :
			Block = 6;
			Piercing = 7;
		break;
		
		case "Cleaver" :
			Block = 7;
			Piercing = 7;
		break;
		
		case "LightAxe" :
			Block = 3;
			Piercing = 9;
		break;
		
		case "Bastard" :
			Block = 8;
			Piercing = 8;
		break;
		
		case "Tomahawk" :
			Block = 3;
			Piercing = 7;
		break;
		
		case "LightFalchion" :
			Block = 8;
			Piercing = 9;
		break;
		
		case "Klewang" :
			Block = 9;
			Piercing = 9;
		break;
		
		case "Katana" :
			Block = 12;
			Piercing = 10;
		break;
		
		case "Falchion" :
			Block = 11;
			Piercing = 12;
		break;
		
		case "HeavyAxe" :
			Block = 5;
			Piercing = 15;
		break;
		
		case "Godendag" :
			Block = 4;
			Piercing = 10;
		break;
		
		case "Sword" :
			Block = 10;
			Piercing = 11;
		break;
		
		case "HeavySmallSword" :
			Block = 7;
			Piercing = 8;
		break;
		
		case "Broadsword" :
			Block = 10;
			Piercing = 9;
		break;
		
		case "Ngala" :
			Block = 4; 
			Piercing = 15;
		break;
		
		case "Macuahuitl" :
			Block = 7; 
			Piercing = 15;
		break;
	}
	
	switch (realItem.quality)
	{
		case "poor":
			realItem.dmg_min 	= sti(MinAttack) + sti(rand(sti(MinAttack)) * frandsmall(0.4));
			realItem.dmg_max 	= MaxAttack * (0.5 + frandsmall(0.1));			
			realItem.rare 	 	= "common";
			QTypeMultiplier = 1.0;
		break;
		case "Ordinary":
			realItem.dmg_min 	= sti(MinAttack) + sti(rand(sti(MinAttack)) * (0.4 + frandsmall(0.1)));
			realItem.dmg_max 	= MaxAttack * (0.6 + frandsmall(0.15));
			realItem.rare 	 	= "rare";
			QTypeMultiplier = 1.25;
		break;
		case "Good":
			realItem.dmg_min 	= sti(MinAttack) + sti(rand(sti(MinAttack)) * (0.4 + frandsmall(0.2)));
			realItem.dmg_max 	= MaxAttack * (0.7 + frandsmall(0.2));
			realItem.rare 	 	= "epic";
			QTypeMultiplier = 1.50;
		break;
		case "Excellent":
			realItem.dmg_min 	= MinAttack;
			realItem.dmg_max 	= MaxAttack;
			realItem.rare 	 	= "Legendary";
			QTypeMultiplier = 2.0;
		break;
	}
	
	BlockResult = sti((Block * FTypeMultiplier) * QTypeMultiplier)*5;
	PiercingResult = sti((Piercing * FTypeMultiplier) * QTypeMultiplier)*5;
	
	if(BlockResult <= 1) BlockResult = 1;
	if(PiercingResult <= 1) PiercingResult = 1;
	
	if(BlockResult >= 100) BlockResult = 100;
	if(PiercingResult >= 100) PiercingResult = 100;
	
	realItem.piercing = PiercingResult;
	realItem.block = BlockResult;
	
	realItem.price = 500;
	
	GENERATED_ITEMS++;
	
	return realItem.ID;
}

// расширить вдвое массив предметов 
void ExpandItemsArray()
{
	TOTAL_ITEMS *= 2;
	SetArraySize(&Items, TOTAL_ITEMS);
}

// Найдем первый пустой слот для предмета
int FindFirstEmptyItem()
{
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID") || Items[i].ID == "0")
		{
			return i;
		}
	}	
	return -1;
}

// Проверим на пустые предметы и удалим их
// Метод выполняется долго - лучше вызывать его при переходах между локациями (как щас и сделано)
void RefreshGeneratedItems()
{
	// оптимизация ленивого удаления
	if (GENERATED_ITEMS < makeint((TOTAL_ITEMS - ITEMS_QUANTITY) * 0.5))
	{
		trace("Удаление пустых предметов не было выполнено, количество сгенерированных = " + GENERATED_ITEMS);
		return;
	}
	
	int curGeneratedCount = GENERATED_ITEMS;

	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID")) continue; // Пустой слот
		RefreshGeneratedItem(i);
	}
	
	trace("Произведено удаление пустых предметов");
	trace("Количество сгенерированных (было/стало) = (" + curGeneratedCount + "/"+ GENERATED_ITEMS + ")");
}

// Метод рефреша для конкретного предмета. Вернет булево значение - удалился предмет или нет
bool RefreshGeneratedItem(int itemIndex)
{
	int i, j;
	string _itemID = Items[itemIndex].id;
	String curSimpleBox, curPrivateBox;
	ref reference;
	
	if(itemIndex == -1) return false;

	for(i = 0; i < nLocationsNum; i++)
	{
		reference = &Locations[i];
		
		for(j = 1; j < MAX_HANDLED_BOXES; j++)
		{
			curSimpleBox = "box" + j;
			curPrivateBox = "private" + j;
			
			if(!CheckAttribute(reference, curSimpleBox) && !CheckAttribute(reference, curPrivateBox)) break;
			
			// Симпл боксы
			if(CheckAttribute(reference, curSimpleBox + ".Items." + _itemID))
			{
				return false;
			}
			
			// Приваты
			if(CheckAttribute(reference, curPrivateBox + ".Items." + _itemID))
			{
				return false;
			}
		}
	}
	
	for(i = 0; i < TOTAL_CHARACTERS; i++)
	{
		reference = &Characters[i];
			
		// Проверка на торговца, у которого уже можно отобрать предметы
		if(CheckAttribute(reference, "Merchant") && CheckNPCQuestDate(reference, "Item_date"))
		{
			DeleteAttribute(reference, "items");
			continue;
		}
		
		if(CheckAttribute(reference, "Items." + _itemID))
		{
			return false;
		}
	}

	DeleteAttribute(&Items[itemIndex], ""); // Потрем все аттрибуты
	
	GENERATED_ITEMS--;
	
	return true;
}

// Проверка, уникален ли каждый предмет "серии", или же идентичен
bool IsGenerableItem(String _itemID)
{
	int itemIndex = GetItemIndex(_itemID);
	ref itemRef;
	
	if(itemIndex == -1)
	{
		return false;
	}
	
	itemRef = &Items[itemIndex];
	
	if(CheckAttribute(itemRef, "Generable") && itemRef.Generable == true && !CheckAttribute(itemRef, "Generated"))
	{
		return true;
	}
	
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										<-- Warship НОВАЯ СИСТЕМА ПРЕДМЕТОВ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Warship Проверка на оружие
bool IsBlade(String _itemID)
{
	int itemIndex = GetItemIndex(_itemID);
	ref item;
	
	if(itemIndex == -1)
	{
		return false;
	}
	
	item = &Items[itemIndex];

	if(CheckAttribute(&item, "groupID"))
	{
		if(item.groupID == BLADE_ITEM_TYPE)
		{
			return true;
		}
	}
	
	return false;
}

// eddy -->
/////////////////////// ==> Items-методы
int GetItemIndex(string _ItemID)
{
	return FindItem(_ItemID);
}

ref ItemsFromID(string _Items)
{
	if(GetItemIndex(_Items) == -1) 
	{
		trace("Bad index for item : " + _Items);
	}
	return &items[GetItemIndex(_Items)];
}

void ChangeItemDescribe(string _Items, string _Describe)
{
    Items[GetItemIndex(_Items)].describe = _Describe;
}

void BackItemDescribe(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.describe = "itmdescr_" + ItemAR.id;
}

void ChangeItemName(string _Items, string _Name)
{
    Items[GetItemIndex(_Items)].name = _Name;
}

void BackItemName(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.name = "itmname_" + ItemAR.id;
}
///////////////////////  Items-методы <--


void QuestCheckEnterLocItem(aref _location, string _locator) /// <<<проверка вхождения ГГ в локаторы группы Item.<<<
{
	ref sld;
	int i;
	//======> Генератор инквизиции.
	if (_location.id == "Santiago_Incquisitio" && CheckNPCQuestDate(_location, "AttackGuard_date") && sti(Colonies[FindColony(_location.fastreload)].nation) == SPAIN && findsubstr(_locator, "detector" , 0) != -1) 
	{
		SetNPCQuestDate(_location, "AttackGuard_date"); //одна засада в день.
		LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
		StartIncquisitioAttack();
	}
	//======> Генератор маяка Порт Рояля.
	if (_location.id == "Mayak3") 	
	{
		int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(_location)));
		if(iNation == -1) return;
		string sGroup = GetNationNameByType(iNation)  + "_mayak";
		LAi_group_AttackGroup(sGroup, LAI_GROUP_PLAYER);
	}
	//======> детектор в тюрьме, вторжение без разрешения
	if (_location.type == "jail" && !sti(pchar.questTemp.jailCanMove) && _locator == "detector1")
	{	
		pchar.questTemp.jailCanMove = true; //чтобы не срабатывало 2 раза
		if (!LAi_grp_alarmactive && !IsLocationCaptured(_location.id))
		{
			string slai_group = GetNationNameByType(GetCityNation(_location.parent_colony)) + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
		}
	}
}

void QuestCheckExitLocItem(aref _location, string _locator) /// <<<проверка выхода ГГ из локаторов группы Item.<<<
{

}

//проверка взятия предметов из локатора item
void QuestCheckTakeItem(aref _location, string _itemId)
{
	
}

void StartIncquisitioAttack()
{
	ref sld;
    for (int i=1; i<=5; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("IncqAddGuard_"+i, "sold_spa_1", "man", "man", 35, SPAIN, 1, true, F_MILITARY));
		FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8, 80, 70, BLADE_LONG, "pistol4", "grapeshot", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
        ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", LAi_FindRandomLocator("goto"));
    }
}

int InitStdBlade(int ItemIndex, string ModelID, string picTexture, int picIndex, string Quality, string TargetGroup, string BladeType, string BladeSubType, bool isGenerable, bool isGenerablePrice, int Price)
{
	ref	blade;
	int	bladeIndex;
	string sRare;
	
	bladeIndex = ItemIndex;
	makeref(blade, Items[bladeIndex]);
	
	blade.id				= ModelID;		
	blade.groupID 			= BLADE_ITEM_TYPE;
	blade.model				= ModelID;
	blade.name				= "itmname_" + ModelID;
	blade.describe			= "itmdescr_" + ModelID;		
	blade.folder 			= "items";
	blade.picTexture		= picTexture;
	blade.picIndex			= picIndex;
	blade.param.time 		= 0.1;
	blade.param.colorstart 	= argb(64, 64, 64, 64);
	blade.param.colorend 	= argb(0, 32, 32, 32);
	blade.ItemType 			= "WEAPON";
 	blade.FencingType       = BladeType;
 	blade.SubType           = BladeSubType; //Новое - вид оружия
	blade.quality			= Quality;
	blade.target			= TargetGroup;
	blade.Generable			= isGenerable;
	blade.GenerablePrice 	= isGenerablePrice; // Флаг "генерить цену"	
	
	blade.dmg_min = 1;
	blade.dmg_max = 15;
	
	
	blade.piercing = 1;
	blade.block = 0;
	
	blade.price = 0;
 	
	switch(Quality)
	{
		case "poor":      sRare = "common"; break;
		case "ordinary":  sRare = "rare"; break;
		case "good":      sRare = "epic"; break;
		case "Excellent": sRare = "Legendary"; break;
	}
	blade.rare 				= sRare;

	bladeIndex++;
	return bladeIndex;
}

int InitStdGun(int ItemIndex, string id, string ModelID, string picTexture, int	picIndex, string TargetGroup, int Price, float DmgMin, float DmgMax, bool MultiDamage, float Accuracy, float Weight, int Charges, int Quality)
{
	ref	gun;
	int	gunIndex;
	string Rare
	
	gunIndex = ItemIndex;
	makeref(gun, Items[gunIndex]);
	
	gun.id				= id;		
	gun.groupID			= GUN_ITEM_TYPE;
	gun.name			= "itmname_" + id;
	gun.describe		= "itmdescr_" + id;		
	gun.model			= ModelID;
	gun.folder 			= "items";
	gun.chargeQ			= Charges;
	gun.picTexture		= picTexture;
	gun.picIndex		= picIndex;
	gun.dmg_min			= DmgMin;
	gun.dmg_max			= DmgMax;
	gun.price			= Price;	
	gun.ItemType 		= "WEAPON";
	gun.quality 		= Quality;
	gun.target			= TargetGroup;
	gun.Weight 			= Weight;
	gun.multidmg        = MultiDamage;
	gun.Accuracy        = Accuracy;
	gun.accuracy 		= 50.0; // by default
	gun.ChargeSpeed 	= 10.0; // by default
	
	switch(Quality)
	{
		case "poor":      Rare = "common"; break;
		case "ordinary":  Rare = "rare"; break;
		case "good":      Rare = "epic"; break;
		case "Excellent": Rare = "Legendary"; break;
	}
	gun.rare 				= Rare;
	
	gunIndex++;
	return gunIndex;
}

void InitGunChargeExt(string id, string sAttr, string sBullet, string sGunPowder, int ChargeSpeed, bool isDefault)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).bullet 		= sBullet;
	gun.type.(sAttr).gunpowder 		= sGunPowder;
	gun.type.(sAttr).ChargeSpeed    = ChargeSpeed;
	gun.type.(sAttr).Default        = isDefault;
}

// mitrokosta переинициализировать предмет с индексом - не использовать
void InitItem(int n)
{
	ref itm;
	makeref(itm, Items[n]);
	DeleteAttribute(itm, "");
	itm.id = "EmptyItem_" + (n + 1);
	itm.describe = "";
	itm.index = n;
	itm.model = "";
	itm.Weight = 0.0; // boal
	itm.uniq  = false;
	itm.price = 1;
	itm.ItemType = "VARIETY";
	itm.used = false; // mitrokosta новая система предметов
}

// удалить квестовый предмет - вызывать это только если этого предмета ни у кого уже нет!!!
void DeleteItem(string itmID)
{
	int idx = GetItemIndex(itmID);
	if (idx < 0)
	{
		trace("DeleteItem: " + itmID + " does not exist!!!");
		return;
	}
	InitItem(idx);
}

// mitrokosta теперь эта функция генерит оружие из указанной группы
string SelectGeneratedItem(string TargetGroup, string Quality, string BladeType, string BladeSubType)
{
	ref item;
	int itemsQty = 0;
	string eligibleItems[ITEMS_QUANTITY];
	bool bOk1, bOk2, bOk3, bOk4;
	
	if(TargetGroup == "" && Quality == "" && BladeType == "" && BladeSubType == "") return "";
	
	for(int i = 0; i < ITEMS_QUANTITY; i++)
	{
		item = &Items[i];
		if(CheckAttribute(item, "groupID") && (item.groupID == BLADE_ITEM_TYPE))
		{		
			bOk1 = HasSubStr(item.target, TargetGroup) || TargetGroup == "";
			bOk2 = item.quality == Quality || Quality == "";
			bOk3 = item.FencingType == BladeType || BladeType == "";
			bOk4 = item.SubType == BladeSubType || BladeSubType == "";
		
			if(bOk1 && bOk2 && bOk3 && bOk4)
			{
				eligibleItems[itemsQty] = Items[i].ID;
				itemsQty++;
			}
		}	
	}

	if(itemsQty == 0)
	{
		return ""; // Ничего не нашлось
	}
	
	return GenerateItem(eligibleItems[rand(itemsQty - 1)]);
}

// mitrokosta теперь эта функция генерит оружие из указанной группы
string SelectGun(string TargetGroup, string Quality)
{
	ref item;
	int itemsQty = 0;
	string eligibleItems[ITEMS_QUANTITY];
	bool bOk1, bOk2;
	
	if(TargetGroup == "" && Quality == "") return "";
	
	for(int i = 0; i < ITEMS_QUANTITY; i++)
	{
		item = &Items[i];
		if(CheckAttribute(item, "groupID") && (item.groupID == GUN_ITEM_TYPE))
		{		
			bOk1 = HasSubStr(item.target, TargetGroup) || TargetGroup == "";
			bOk2 = item.quality == Quality || Quality == "";
		
			if(bOk1 && bOk2)
			{
				eligibleItems[itemsQty] = Items[i].ID;
				itemsQty++;
			}
		}	
	}

	if(itemsQty == 0)
	{
		return ""; // Ничего не нашлось
	}
	
	return GenerateItem(eligibleItems[rand(itemsQty - 1)]);
}

int InitStdItem(int	ItemIndex, string id, string ModelID, string picTexture, int picIndex, string Rare, int MinLevel, int Price, int	PriceDublon, float Weight)
{
	ref	rItem;
	int	itmIndex;
	
	itmIndex = ItemIndex;
	makeref(rItem, Items[itmIndex]);
	
	rItem.id				= id;		
	rItem.model				= ModelID;
	rItem.name				= "itmname_" + id;
	rItem.describe			= "itmdescr_" + id;		
	rItem.picTexture		= picTexture;
	rItem.picIndex			= picIndex;	
	rItem.price				= Price;	
	rItem.rare 				= Rare;
	rItem.minlevel 			= MinLevel;
	rItem.Weight 			= Weight;
	
	if(PriceDublon > 0) 
	{
		rItem.PriceDublon				= PriceDublon;	
	}
	
	itmIndex++;
	return itmIndex;
}

void DoCharacterUsedPoison(ref chref, string itmID)
{
	aref arItm;
	int  idLngFile, iTime, iHealth;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	if( Items_FindItem(itmID, &arItm) < 0) return;
	
	string weaponID = GetCharacterEquipByGroup(chref, BLADE_ITEM_TYPE);
    aref weapon;
    Items_FindItem(weaponID, &weapon);
	
	if(CheckAttribute(weapon, "isPoisoned"))
	{
		PlaySound("interface\knock.wav");
		Log_TestInfo("Ты дурак? Клинок уже отравлен другим ядом!");
		return;
	}
	
	weapon.isPoisoned = true; // атрибут отравленного клинка
	weapon.isPoisoned.poison = arItm.id; // Каким ядом нанесесено
	if(CheckAttribute(arItm, "poison.hitsQ"))
	{
		weapon.isPoisoned.poisonQunatity = arItm.poison.hitsQ; // максимально допустимое количество ударов, которыми можно отравить соперника
	}
	
	if(CheckAttribute(arItm, "poison.duration"))
	{
		weapon.isPoisoned.poisonduration = arItm.poison.duration; // длительность отравления
	}
	
	if(CheckAttribute(arItm, "poison.chance"))
	{
		weapon.isPoisoned.poisonchance = arItm.poison.chance; // шанс отравления
	}
	
	if(CheckAttribute(arItm, "poison.damage"))
	{
		weapon.isPoisoned.poisondamage = arItm.poison.damage; // урон отравления
	}
	
	if(CheckAttribute(arItm, "poison.dmgBonus"))
	{
		weapon.isPoisoned.dmgBonus = arItm.poison.dmgBonus; // бонусный урон
	}
	
	if(CheckAttribute(arItm, "poison.InstantKill"))
	{
		weapon.isPoisoned.InstantKill = arItm.poison.InstantKill; // шанс мгновенного убийства
	}
	
	if(CheckAttribute(arItm, "poison.time") && arItm.poison.time > 0)
	{
		SetPoisonTimerFunctionParam("RemovePoisonEffectFromCharBlade_"+chref.id, "RemovePoisonEffectFromCharBlade", 0, 0, 0, sti(GetTime() + sti(arItm.poison.time)), chref, weapon.id);
	}
	
	if(CheckAttribute(pchar, "GenQuest.Poison_choise") && GetCharacterItem(pchar, itmID) == 1)
		DeleteAttribute(pchar, "GenQuest.Poison_choise");
	RemoveItems(pchar, itmID, 1);
	Log_TestInfo("Яд - '"+LanguageConvertString(idLngFile, arItm.name)+"' нанесён на текущий экипированный клинок!");
	PlaySound("interface\poison.wav");
	
	LanguageCloseFile(idLngFile);
}

int InitStdAmulet(int ItemIndex, string id, string 	ModelID, string picTexture, int picIndex, int Price, string Rare, float Weight, int MinLevel, string kind)
{
	ref	amulet;
	int	amuletIndex;
	
	amuletIndex = ItemIndex;
	makeref(amulet, Items[amuletIndex]);
	
	amulet.id				= id;		
	amulet.groupID			= TALISMAN_ITEM_TYPE;
	amulet.name				= "itmname_" + id;
	amulet.describe			= "itmdescr_" + id;		
	amulet.model			= ModelID;
	amulet.picTexture		= picTexture;
	amulet.picIndex			= picIndex;
	amulet.price			= Price;
	amulet.rare 			= Rare;
	amulet.minlevel 		= MinLevel;
	amulet.Weight 			= Weight;
	amulet.ItemType 		= "ARTEFACT";
	
	if(kind != "") amulet.kind	= kind;	
	
	amuletIndex++;
	return amuletIndex;
}

int InitStdSuit(int	ItemIndex, string id, string ModelID, string picTexture, int picIndex, int Price, float Weight, string Rare, int MinLevel, bool isClothes, float CirassLevel_blade, float CirassLevel_gun, float Critical)
{
	ref	suit;
	int	suitIndex;
	
	suitIndex = ItemIndex;
	makeref(suit, Items[suitIndex]);
	
	suit.id					= id;		
	suit.groupID			= CIRASS_ITEM_TYPE;
	suit.name				= "itmname_" + id;
	suit.describe			= "itmdescr_" + id;		
	suit.folder 			= "items";
	suit.model				= ModelID;
	suit.picTexture			= picTexture;
	suit.picIndex			= picIndex;
	suit.price				= Price;	
	suit.rare 				= Rare;
	suit.minlevel 			= MinLevel;
	suit.Weight 			= Weight;
	suit.Clothes 			= isClothes;
	suit.B_CirassLevel 		= CirassLevel_blade;
	suit.G_CirassLevel 		= CirassLevel_gun;
	
	if(Critical > 0.0)
	{
		suit.critical			= Critical;
	}	
	
	suit.ItemType 			= "SUPPORT";
	
	suitIndex++;
	return suitIndex;
}

void InitMultiObject(string id,	string sAttr, string component_id, string component_use, int component_qty)
{
	ref rItem = ItemsFromID(id);
	rItem.component.(sAttr).id 	=  component_id;
	rItem.component.(sAttr).use =  component_use;
	rItem.component.(sAttr).qty =  component_qty;
}

int InitStdRecipies(int ItemIndex, string id, string result, int Price)
{
	ref	recipe;
	int	recipeIndex;
	
	recipeIndex = ItemIndex;
	makeref(recipe, Items[recipeIndex]);
	
	recipe.id			= id;	
	recipe.result 		= result;
	recipe.groupID		= SPECIAL_ITEM_TYPE;
	recipe.name			= "itmname_recipe";
	recipe.describe		= "itmdescr_recipe";		
	recipe.model		= "letter";
	recipe.picTexture	= "ITEMS_QUEST1";
	recipe.picIndex		= 1;
	recipe.price		= Price;	
	recipe.rare 		= "Epic";
	recipe.minlevel 	= 1;
	recipe.Weight 		= 0.1;
	recipe.ItemType 	= "SUPPORT";
	recipe.special_item = true;
	
	recipeIndex++;
	return recipeIndex;
}

void SetItemNeededCraftPerk(string _Items, string _Perk)
{
    Items[GetItemIndex(_Items)].CraftCondition.(_Perk) = true;
}

int SetLocatorRandItemDrop(ref rndItm, string _Items, int _Index, int MaxQ, int MaxChestQ, string _LocType, string _LocIslandId)
{
	int iIndex;
	
	iIndex = _Index;
    makeref(rndItm, RandItems[iIndex]);
	
	rndItm.id = _Items;
	rndItm.LocType = _LocType;
	rndItm.islandId = _LocIslandId;
	rndItm.maxQuantity = MaxQ;
	
	items[FindItem(_Items)].maxChestQuantity = MaxChestQ;
	
	iIndex++;
	return iIndex;
}

string SelectRandItem(string LocationType, string LocationIslandId)
{
	ref item, item2;
	int itemsQty = 0;
	string eligibleItems[RANDITEMS_QUANTITY];
	bool bOk1, bOk2;
	
	if(LocationType == "" && LocationIslandId == "") return "";
	
	for(int i = 0; i < RANDITEMS_QUANTITY; i++)
	{
		makeref(item, RandItems[i]);
		
		if(CheckAttribute(item, "LocType") && CheckAttribute(item, "islandId"))
		{
			bOk1 = HasSubStr(item.LocType, LocationType) || LocationType == "";
		
			if(LocationIslandId != "" && item.islandId != "") bOk2 = HasSubStr(item.islandId, LocationIslandId) || LocationIslandId == "";
			else bOk2 = LocationIslandId == "";
		
			if(bOk1 && bOk2)
			{
				eligibleItems[itemsQty] = RandItems[i].ID;
				itemsQty++;
			}	
		}
	}

	if(itemsQty == 0)
	{
		return ""; // Ничего не нашлось
	}
	
	return GenerateItem(eligibleItems[rand(itemsQty - 1)]);
}

void InitStdItemRarity(string id, string sAttr, int minQ, int maxQ)
{
	ref rItem = ItemsFromID(id);
	rItem.(sAttr).min   =  minQ;
	rItem.(sAttr).max 	=  maxQ;
}	
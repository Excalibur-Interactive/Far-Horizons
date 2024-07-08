// тестовый интерфейс, для разных нужд
#include "interface\character_all.h"

string sFavVariant = "";

void InitInterface_R(string iniName, ref _char)
{
	GameInterface.title = "TitleTest";

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("ExitFavouriteMenu","ExitFavouriteMenu",0);
	SetEventHandler("FavouriteChange","FavouriteChange",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ExitFavouriteMenu","ExitFavouriteMenu",0);
	
	SetVariable();
}

void SetVariable()
{
	SetFormatedText("GOLD_BAR_TEXT", MakeMoneyShow(sti(pChar.Money), MONEY_SIGN,MONEY_DELIVER));
	SetFormatedText("WEIGHT_BAR_TEXT", FloatToString(GetItemsWeight(pChar), 1) + " / "+sti(GetMaxItemsWeight(pChar)));
	SetFormatedText("LEVEL_TEXT", pChar.rank);
	SetNodeUsing("INFO_PIC", false);

	GameInterface.StatusLine.LEVEL_BAR.Max = GetCharacterRankRate(pChar);
    GameInterface.StatusLine.LEVEL_BAR.Min = 0;
    GameInterface.StatusLine.LEVEL_BAR.Value = GetCharacterRankRateCur(pChar);
	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LEVEL_BAR",0);
	// сортировка -->
	SortItems(pchar);
	// сортировка -->
	SetControlsTabMode(1);
}

void FillItemsSelected() 
{
	int i;
	string sGood;
	int iLastGunItem;
	ref rLastGunItem;
	
	// Скроем по умолчанию
	SetNodeUsing("ICON_BLADE", false);
	SetNodeUsing("ICON_PISTOL", false);
	SetNodeUsing("ICON_SPYGLASS", false);
	SetNodeUsing("ICON_CUIRASS", false);
	SetNodeUsing("ICON_TALISMAN", false);
	SetNodeUsing("ICON_MUSHKET", false);
	SetNodeUsing("ICON_POTION1", false);
	SetNodeUsing("ICON_POTION2", false);
	SetNodeUsing("ICON_POISON", false);
	
    for (i = 0; i< TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		sGood = Items[i].id;
		
		if (GetCharacterItem(pchar, sGood) > 0)
		{
			/// экипировка
			if (IsEquipCharacterByItem(pchar, sGood))
			{
				switch (Items[i].groupID) 
				{
					case BLADE_ITEM_TYPE:
						SetNewGroupPicture("ICON_BLADE", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ICON_BLADE" , true);
					break;
 					case GUN_ITEM_TYPE:
						if(CheckAttribute(pchar, "IsMushketer"))
						{
							iLastGunItem = GetItemIndex(pchar.IsMushketer.LastGunID);
							// Покажем картинку старого пистоля, если он еще есть
							if(iLastGunItem != -1 && GetCharacterItem(pchar, pchar.IsMushketer.LastGunID) > 0)
							{
								rLastGunItem = &Items[iLastGunItem];
								SetNewGroupPicture("ICON_PISTOL", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
								SetNodeUsing("ICON_PISTOL" , true);
							}
							rLastGunItem = &Items[GetItemIndex(pchar.IsMushketer.MushketID)];
							SetNodeUsing("ICON_MUSHKET", true);
							SetNewGroupPicture("ICON_MUSHKET", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
						}
						else
						{
							SetNewGroupPicture("ICON_PISTOL", Items[i].picTexture, "itm" + Items[i].picIndex);
							SetNodeUsing("ICON_PISTOL" , true);
							SetNodeUsing("ICON_MUSHKET" , false); // Мушкет не юзается - уберем картинку
						}
					break;
 					case SPYGLASS_ITEM_TYPE:
						SetNewGroupPicture("ICON_SPYGLASS", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ICON_SPYGLASS" , true);
					break;
 					case CIRASS_ITEM_TYPE:
						SetNewGroupPicture("ICON_CUIRASS", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ICON_CUIRASS" , true);
					break;
					case TALISMAN_ITEM_TYPE:
						SetNewGroupPicture("ICON_TALISMAN", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ICON_TALISMAN" , true);
					break;
				}
			}
			
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v1") && pchar.GenQuest.Potion_choice.v1 == Items[i].id)
			{
				SetNewGroupPicture("ICON_POTION1", Items[i].picTexture, "itm" + Items[i].picIndex);
				SetNodeUsing("ICON_POTION1" , true);
			}
			
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v2") && pchar.GenQuest.Potion_choice.v2 == Items[i].id)
			{
				SetNewGroupPicture("ICON_POTION2", Items[i].picTexture, "itm" + Items[i].picIndex);
				SetNodeUsing("ICON_POTION2" , true);
			}
			
			if(CheckAttribute(pchar, "GenQuest.Poison_choise") && pchar.GenQuest.Poison_choise == Items[i].id)
			{
				SetNewGroupPicture("ICON_POISON", Items[i].picTexture, "itm" + Items[i].picIndex);
				SetNodeUsing("ICON_POISON" , true);
			}
		}			
	}
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode( 2 );
		return;
	}
	
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabMode( 3 );
		return;
	}
	
	if( sNodName == "TABBTN_4" )
	{
		SetControlsTabMode( 4 );
		return;
	}
	
	if( sNodName == "TABBTN_5" )
	{
		SetControlsTabMode( 5 );
		return;
	}
	
	if( sNodName == "TABBTN_6" )
	{
		SetControlsTabMode( 6 );
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	string sPic1 = "All_off";
	string sPic2 = "Gear_off";
	string sPic3 = "Potion_off";
	string sPic4 = "Ingredients_off";
	string sPic5 = "Quest_off";
	string sPic6 = "Other_off";

	switch (nMode)
	{
		case 1: //
			sPic1 = "All_on";
		break;
		case 2:
			sPic2 = "Gear_on";
		break;
		case 3:
			sPic3 = "Potion_on";
		break;
		case 4:
			sPic4 = "Ingredients_on";
		break;
		case 5:
			sPic5 = "Quest_on";
		break;
		case 6:
			sPic6 = "Other_on";
		break;
	}
    
	SetNewGroupPicture("TABBTN_1", "TABS_NEW", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS_NEW", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS_NEW", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS_NEW", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS_NEW", sPic5);
	SetNewGroupPicture("TABBTN_6", "TABS_NEW", sPic6);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: FillItemsTable(1); break;  // все
	    case 2: FillItemsTable(2); break;  // снаряжение
	    case 3: FillItemsTable(3); break;  // зелья и яды
	    case 4: FillItemsTable(4); break;  // ингредиенты
		case 5: FillItemsTable(5); break;  // особое
		case 6: FillItemsTable(6); break;  // разное
	}
}

void FillItemsTable(int _mode)
{
	int n, i;
	string row;
	string sGood;
	string groupID;
	string itemType;
	int  idLngFile;
	bool ok, ok1, ok2, ok3, ok4;
	aref rootItems, arItem;
	aref  curItem;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_ITEMS", false, true, false);
	
	switch(_mode)
	{
		case 1:
		    SetFormatedText("INFO_TEXT_SORT", "Всё");
		break;
		
		case 2:
		    SetFormatedText("INFO_TEXT_SORT", "Снаряжение");
		break;
		
		case 3:
		    SetFormatedText("INFO_TEXT_SORT", "Зелья и яды");
		break;
		
		case 4:
		    SetFormatedText("INFO_TEXT_SORT", "Ингредиенты");
		break;
		
		case 5:
		    SetFormatedText("INFO_TEXT_SORT", "Особое");
		break;
		
		case 6:
		    SetFormatedText("INFO_TEXT_SORT", "Разное");
		break;
	}
	
	// Заполним вещами от нас
	makearef(rootItems, pchar.Items);
    for (i = 0; i < GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		itemType = "";

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{
			row = "tr" + n;
			sGood = arItem.id;
			
			if(CheckAttribute(arItem, "groupID")) groupID = arItem.groupID;
			if(CheckAttribute(arItem, "itemType")) itemType = arItem.itemType;
			
			// Снаряжение -->
			ok = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
				 (groupID == GUN_ITEM_TYPE)	||		// огнестрельное оружие
                 (groupID == SPYGLASS_ITEM_TYPE) || // подзорные трубы
				 (groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
				 (groupID == AMMO_ITEM_TYPE) ||        // боеприпасы
				 (groupID == TALISMAN_ITEM_TYPE);        // талисманы
				 
			// Зелья -->
			ok1 = (CheckAttribute(arItem, "potion")) || (CheckAttribute(arItem, "poison"));
			
			// Ингредиенты -->
			ok2 = (HasSubStr(arItem.id, "ingredient")) && (!CheckAttribute(arItem, "special_item"));
			
			// особое -->
			ok3 = (itemType == "QUESTITEMS") || (CheckAttribute(arItem, "special_item")); //важное
			
			// Разное -->
			ok4 = (HasSubStr(arItem.id, "mineral")) || (HasSubStr(arItem.id, "jewelry")); // разное
			
			//if(_mode == 1) continue;
			if(_mode == 2 && !ok) continue;
			if(_mode == 3 && !ok1) continue;
			if(_mode == 4 && !ok2) continue;
			if(_mode == 5 && !ok3) continue;
			if(_mode == 6 && !ok4) continue;
			
			if (GetCharacterItem(pchar, sGood) > 0)
			{
				GameInterface.TABLE_ITEMS.(row).index = GetItemIndex(arItem.id);
				
				GameInterface.TABLE_ITEMS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "2, 2";
				GameInterface.TABLE_ITEMS.(row).td1.icon.width = 32;
				GameInterface.TABLE_ITEMS.(row).td1.icon.height = 32;
				GameInterface.TABLE_ITEMS.(row).td1.textoffset = "40,0";
				GameInterface.TABLE_ITEMS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_ITEMS.(row).td1.scale = 0.85;
				
				GameInterface.TABLE_ITEMS.(row).td2.str   = GetCharacterItem(pchar, sGood);
				GameInterface.TABLE_ITEMS.(row).td2.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td2.textoffset = "0,0";
				
				n++;
			}
		}
    }
	
	//Костыльно, но работает :)
	CurTable = "TABLE_ITEMS";
	CurRow = "tr1";
	SetItemInfo();
	
	if(sti(GameInterface.(CurTable).(CurRow).index) == 0)
	{
		HideItemInfo();
	}
    
	Table_UpdateWindow("TABLE_ITEMS");
	LanguageCloseFile(idLngFile);
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    
    // отрисовка инфы
    SetItemInfo();
}

void SetItemInfo()
{
	if(CurTable != "TABLE_ITEMS") return;
	
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	int nColor1 = argb(255,255,255,255);
	int nColor2 = argb(255,255,255,255);
	string describeStr, describeStr2;
	ref arItem;
	
	SetFormatedText("INFO_TEXT_NAME", GetConvertStr(Items[iGoodIndex].name, "ItemsDescribe.txt"));
	SetNewGroupPicture("INFO_PIC", Items[iGoodIndex].picTexture, "itm" + Items[iGoodIndex].picIndex);
	SetNodeUsing("INFO_PIC", true);
	SetNodeUsing("INFO_TEXT_NAME", true);
	SetNodeUsing("INFO_TEXT_TYPE", true);
	SetVAligmentFormatedText("INFO_TEXT_NAME");
	SetVAligmentFormatedText("INFO_TEXT_SUBTYPE");
	SetVAligmentFormatedText("INFO_TEXT_DMG");
	SetVAligmentFormatedText("INFO_TEXT_DESC");
	SetVAligmentFormatedText("INFO_TEXT_WEIGHT");
	SetNodeUsing("INFO_TEXT_SUBTYPE", false);
	SetNodeUsing("INFO_TEXT_DMG", false);
	SetNodeUsing("INFO_TEXT_DESC", false);
	SetNodeUsing("INFO_TEXT_WEIGHT", false);
		
	if(CheckAttribute(Items[iGoodIndex], "groupID"))
	{
		switch(Items[iGoodIndex].groupID)
		{
			case BLADE_ITEM_TYPE:
			    if (CheckAttribute(Items[iGoodIndex], "FencingType"))
	    		{
	   	     	    Items[iGoodIndex].FencingTypeName = XI_ConvertString(Items[iGoodIndex].FencingType);
	    	    	SetFormatedText("INFO_TEXT_TYPE", GetAssembledString( LanguageConvertString(lngFileID,"weapon blade type1"), Items[iGoodIndex]));
	    		}
	    		else
	    		{
	    			SetFormatedText("INFO_TEXT_TYPE", "Error");
    	    	}
				
				if(CheckAttribute(Items[iGoodIndex], "subtype"))
		    	{
		    		SetFormatedText("INFO_TEXT_SUBTYPE", XI_ConvertString(Items[iGoodIndex].subType));
		    		SetNodeUsing("INFO_TEXT_SUBTYPE", true);
		    	}
				
				if(CheckAttribute(Items[iGoodIndex], "dmg_min") && CheckAttribute(Items[iGoodIndex], "dmg_max"))
				{
					SetFormatedText("INFO_TEXT_DMG", GetAssembledString( LanguageConvertString(lngFileID, "weapon blade parameters1"), Items[iGoodIndex]));
					SetNodeUsing("INFO_TEXT_DMG", true);
				}
			break;
			
			case GUN_ITEM_TYPE:
			    if(CheckAttribute(Items[iGoodIndex], "id"))
	    		{
	   	     	    if(HasSubStr(Items[iGoodIndex].id, "Pistol")) SetFormatedText("INFO_TEXT_TYPE", "Пистолет");
	   	     	    else if(HasSubStr(Items[iGoodIndex].id, "Mushket")) SetFormatedText("INFO_TEXT_TYPE", "Мушкет");
	   	     	    else SetFormatedText("INFO_TEXT_TYPE", "Error");
					
					if(Items[iGoodIndex].id == "pistol1" || Items[iGoodIndex].id == "pistol2" || Items[iGoodIndex].id == "pistol5" || Items[iGoodIndex].id == "pistol7" || Items[iGoodIndex].id == "pistol10" || Items[iGoodIndex].id == "mushket_matchlock" || Items[iGoodIndex].id == "mushket_Bayonet" || Items[iGoodIndex].id == "mushket_Shtuzer")
			    	{
			    		SetFormatedText("INFO_TEXT_SUBTYPE", "Одноствольный");
			    		SetNodeUsing("INFO_TEXT_SUBTYPE", true);
		    		}
					else
					{
						if(Items[iGoodIndex].id == "pistol4" || Items[iGoodIndex].id == "pistol6" || Items[iGoodIndex].id == "pistol8" || Items[iGoodIndex].id == "pistol7" || Items[iGoodIndex].id == "pistol10" || Items[iGoodIndex].id == "mushket_2x2")
						{
					    	SetFormatedText("INFO_TEXT_SUBTYPE", "Многоствольный");
		    		    	SetNodeUsing("INFO_TEXT_SUBTYPE", true);
						}
						else
						{
							if(Items[iGoodIndex].id == "pistol3" || Items[iGoodIndex].id == "pistol9" || Items[iGoodIndex].id == "mushket_Arquebus" || Items[iGoodIndex].id == "mushket_Portuguese")
							{
								SetFormatedText("INFO_TEXT_SUBTYPE", "Картечница");
		    	    		    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
							}
						    else
			    	        {
								if(Items[iGoodIndex].id == "pistol11")
								{
									SetFormatedText("INFO_TEXT_SUBTYPE", "Револьвер");
		    	    		        SetNodeUsing("INFO_TEXT_SUBTYPE", true);
								}
		    	            	else
								{
									if(Items[iGoodIndex].id == "mushket_sklopetta" || Items[iGoodIndex].id == "mushket_Bombard")
									{
										SetFormatedText("INFO_TEXT_SUBTYPE", "Бомбарда");
		    	         		        SetNodeUsing("INFO_TEXT_SUBTYPE", true);
									}
								    else SetNodeUsing("INFO_TEXT_SUBTYPE", false);
								}
			    	        }
						}
					}
					
					if(CheckAttribute(Items[iGoodIndex], "dmg_min") && CheckAttribute(Items[iGoodIndex], "dmg_max"))
				    {
			    		SetFormatedText("INFO_TEXT_DMG", GetAssembledString( LanguageConvertString(lngFileID, "weapon gun parameters1"), Items[iGoodIndex]));
			    		SetNodeUsing("INFO_TEXT_DMG", true);
			    	}
	    		}
			break;
			
			case SPYGLASS_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Подзорная труба");
				if(CheckAttribute(Items[iGoodIndex], "scope.zoom"))
		    	{
		    		SetFormatedText("INFO_TEXT_SUBTYPE", NewStr() + "Дальность обзора " + sti(Items[iGoodIndex].scope.zoom) + "х");
		    		SetNodeUsing("INFO_TEXT_SUBTYPE", true);
		    	}
			break;
			
			case CIRASS_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Защита");
				if(CheckAttribute(Items[iGoodIndex], "id"))
			   {
					switch(Items[iGoodIndex].id)
					{
						case "cirass1":
						    describeStr = "Броня +5%";
							describeStr2 = "Шанс блока крита 10%";
						break;
						
						case "cirass2":
						    describeStr = "Броня +15%";
							describeStr2 = "Шанс блока крита 15%";
						break;
						
						case "cirass3":
						    describeStr = "Броня +25%";
							describeStr2 = "Шанс блока крита 25%";
						break;
						
						case "cirass4":
						    describeStr = "Броня +35%";
							describeStr2 = "Шанс блока крита 35%";
						break;
						
						case "cirass5":
						    describeStr = "Броня +50%";
							describeStr2 = "Шанс блока крита 50%";
						break;
						
						case "cirass6":
						    describeStr = "Броня +45%";
							describeStr2 = "Шанс блока крита 45%";
						break;
						
						case "cirass7":
						    describeStr = "Броня +45%";
							describeStr2 = "Шанс блока крита 45%";
						break;
					}
				}
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			break;
			
			case SPECIAL_ITEM_TYPE:
			   if(HasSubStr(Items[iGoodIndex].id, "purse")) SetFormatedText("INFO_TEXT_TYPE", "Драгоценность");
			   else SetFormatedText("INFO_TEXT_TYPE", "Особый предмет");
			   
			   if(CheckAttribute(Items[iGoodIndex], "potion.special"))
			   {
					switch(Items[iGoodIndex].potion.special.effect)
					{
						case "Jaguar":
						    describeStr = "Меткость +15%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "potion6":
						    describeStr = "Полностью восстанавливает статус здоровья";
							describeStr2 = "";
						break;
						
						case "ishtab":
						    describeStr = "Здоровье +30%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "itzamma":
						    describeStr = "Энергия +15%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "eekatl":
						    describeStr = "Макс. вес +15%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "berserker_potion":
						    describeStr = "Эффект 'Берсерк'";
							describeStr2 = "Действует 12 секунд";
						break;
						
						case "quetzalcoatl":
						    describeStr = "Крепость здоровья +15%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часов";
						break;
						
						case "tlaloc":
						    describeStr = "Восст. энергии +15%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часов";
						break;
						
						case "loa":
						    describeStr = "Знач. прирост силы";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "legba":
						    describeStr = "Знач. прирост ловкости";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "huitzilopochtli":
						    describeStr = "Сила удара +25%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].potion.special.time) + " часа";
						break;
						
						case "mictlantecuhtli":
						    describeStr = NewStr()+ "Однократно спасает от гибели";
							describeStr2 = "";
						break;
					}
				}
				
				if(CheckAttribute(Items[iGoodIndex], "id"))
			    {
					switch(Items[iGoodIndex].id)
					{
						case "purse1":
						    describeStr = NewStr()+ "Содержит случайное дублонов";
							describeStr2 = "";
						break;
					}
				}
				
				if(findsubstr(Items[iGoodIndex].id, "recipe_" , 0) != -1)
				{
					describeStr = NewStr() + LanguageConvertString(lngFileID, "Itmname_"+Items[iGoodIndex].result);
					describeStr2 = "";
					arItem = ItemsFromID(Items[iGoodIndex].result);
					switch(arItem.rare)
					{
						case "common":
						    nColor1 = argb(255, 255, 255, 255);
						break;
						
						case "rare":
						    nColor1 = argb(255, 72, 180, 216);
						break;
						
						case "epic":
						    nColor1 = argb(255, 210, 0, 255);
						break;
						
						case "Legendary":
						    nColor1 = argb(255, 255, 136, 0);.
						break;
					}
				}
				
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			break;
			
			case POISON_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Яд");
				if(CheckAttribute(Items[iGoodIndex], "poison.time"))
				{
					switch(Items[iGoodIndex].id)
					{
						case "poison1":
						    describeStr = "Шанс отравления 30%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.time) + " часа";
						break;
					
						case "poison2":
						    describeStr = "Шанс отравления 50%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.time) + " часа";
						break;
					
						case "poison3":
						    describeStr = "Бонусный урон 5%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.hitsQ) + " ударов";
						break;
							
						case "poison5":
						    describeStr = "Шанс отравления 75%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.time) + " часа";
						break;
					
						case "poison6":
						    describeStr = "Бонусный урон 15%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.hitsQ) + " ударов";
						break;
					
						case "poison7":
						    describeStr = "Шанс отравления 100%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.time) + " часа";
						break;
					
						case "poison8":
						    describeStr = "Бонусный урон 25%";
							describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.hitsQ) + " ударов";
						break;
					    
				    	case "poison9":
			    		    describeStr = "Мгновенное убийство";
		    				describeStr2 = "Действует " + sti(Items[iGoodIndex].poison.hitsQ) + " удар";
	    				break;
    				}
				}
				
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			break;
			
			case RATPOISON_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Яд");
				
				if(Items[iGoodIndex].id == "poison4")
				{
				    describeStr = "Избавляет от крыс";
				    describeStr2 = "Действует 30 дней";
				}
				
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			break;
			
			case AMMO_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Боеприпасы");
				switch(Items[iGoodIndex].id)
				{
					case "bullet":
					    describeStr = NewStr() + "Требуется для стрельбы из оружия";
						describeStr2 = "";
					break;
					
					case "GunPowder":
					    describeStr = NewStr() + "Требуется для заряжания оружия";
						describeStr2 = "";
					break;
					
					case "grapeshot":
					    describeStr = NewStr() + "Урон по площади";
						describeStr2 = "";
					break;
					
					case "Cartridge":
					    describeStr = NewStr() + "Перезарядка х2";
						describeStr2 = "";
					break;
					
					case "GunEchin":
					    describeStr = "Урон по площади х2";
						describeStr2 = "Перезярядка х2";
					break;
					
					case "Grenade":
					    describeStr = "Урон по площади";
						describeStr2 = "Снаряд для бомбарды";
					break;
					
					case "Petard":
					    describeStr = "Оглушение по площади";
						describeStr2 = "Снаряд для бомбарды";
					break;
					
					case "Poison_bomb":
					    describeStr = "Отравление по площади";
						describeStr2 = "Снаряд для бомбарды";
					break;
					
					case "silver_bullet":
					    describeStr = NewStr() + "Урон по нежити х2";
						describeStr2 = "";
					break;
					
					case "Silver_cartridge":
				        describeStr = "Урон по нежити х2";
						describeStr2 = "Перезарядка х2";
					break;
				}
				
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			break;
			
			case TALISMAN_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Талисман");
				
				switch(Items[iGoodIndex].kind)
				{
					case "MainHero":
					    describeStr = NewStr() + "Только для главного героя";
						describeStr2 = "";
					break;
					
					case "navigator":
					    describeStr = NewStr() + "Может использоваться штурманом";
						describeStr2 = "";
					break;
					
					case "doctor":
					    describeStr = NewStr() + "Может использоваться врачом";
						describeStr2 = "";
					break;
					
					case "carpenter":
					    describeStr = NewStr() + "Может использоваться плотником";
						describeStr2 = "";
					break;
					
					case "cannoner":
					    describeStr = NewStr() + "Может использоваться канониром";
						describeStr2 = "";
					break;
					
					case "treasurer":
					    describeStr = NewStr() + "Может использоваться казначеем";
						describeStr2 = "";
					break;
					
					case "boatswain":
					    describeStr = NewStr() + "Может использоваться квартирмейстером";
						describeStr2 = "";
					break;
				}
				
				if(!CheckAttribute(Items[iGoodIndex], "kind"))
				{
					describeStr = NewStr() + "Может использоваться кем угодно";
					describeStr2 = "";
				}
				
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			break;
		}
	}
	else
	{
		if(HasSubStr(Items[iGoodIndex].id, "potion"))
		{
			if (CheckAttribute(Items[iGoodIndex], "potion"))
			{
				SetFormatedText("INFO_TEXT_TYPE", "Зелье");
				if (CheckAttribute(Items[iGoodIndex], "potion.health") && CheckAttribute(Items[iGoodIndex], "potion.antidote"))
				{
					describeStr += "";
					if (stf(Items[iGoodIndex].potion.health) >= 0)
					{	
						describeStr += "+" + sti(Items[iGoodIndex].potion.health);
					} 
					else
					{	
						describeStr += "" + sti(Items[iGoodIndex].potion.health);
					}
					describeStr += " здоровья";
					
					if(CheckAttribute(Items[iGoodIndex], "potion.antidote"))
					{
						describeStr2 = "Снимает отравление";
					}
				}
				else
				{
					if (CheckAttribute(Items[iGoodIndex], "potion.antidote"))
					{
						describeStr += NewStr()+ "Снимает отравление";
					}
					else
					{
						if (CheckAttribute(Items[iGoodIndex], "potion.health"))
						{
							describeStr += NewStr()+ "";
							if (stf(Items[iGoodIndex].potion.health) >= 0)
							{	
								describeStr += "+" + sti(Items[iGoodIndex].potion.health);
							} 
							else
							{	
								describeStr += "" + sti(Items[iGoodIndex].potion.health);
							}
							describeStr += " здоровья";
						}
					}
				}
				
				SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			    SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		        SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    	SetNodeUsing("INFO_TEXT_DMG", true);
		    	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			}
		}
	    else if(Items[iGoodIndex].id == "gold_dublon" || HasSubStr(Items[iGoodIndex].id, "jewelry") || Items[iGoodIndex].id == "peso_earring")
		{
			SetFormatedText("INFO_TEXT_TYPE", "Драгоценность");
			switch(Items[iGoodIndex].id)
			{
			    case "gold_dublon":
		    		describeStr = NewStr() + "Стоит ровно 100 песо";
		    		describeStr2 = "";
		    	break;
			}
			
			SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		    SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    SetNodeUsing("INFO_TEXT_DMG", true);
		    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			if(describeStr == "" && describeStr2 == "") SetFormatedText("INFO_TEXT_TYPE", NewStr() + "Драгоценность");
	    }
		else if(HasSubStr(Items[iGoodIndex].id, "cannabis") || HasSubStr(Items[iGoodIndex].id, "ingredient") || HasSubStr(Items[iGoodIndex].id, "cannabis"))
		{
			SetFormatedText("INFO_TEXT_TYPE", "Ингредиент");
			if(Items[iGoodIndex].id == "ingredient14" || Items[iGoodIndex].id == "ingredient13" || Items[iGoodIndex].id == "ingredient12")
			{
				describeStr = NewStr() + "Редкий ингредиент";
		    	describeStr2 = "";
				nColor1 = argb(255, 255, 136, 0);
			}
			SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		    SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    SetNodeUsing("INFO_TEXT_DMG", true);
		    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
			if(describeStr == "" && describeStr2 == "") SetFormatedText("INFO_TEXT_TYPE", NewStr() + "Ингредиент");
	    }	
		else if(Items[iGoodIndex].id == "lockpick" || HasSubStr(Items[iGoodIndex].id, "key") || Items[iGoodIndex].id == "DutTradeLicence" || Items[iGoodIndex].id == "Chest_open" || HasSubStr(Items[iGoodIndex].id, "Instrument"))
		{
			SetFormatedText("INFO_TEXT_TYPE", "Особый предмет");
			switch(Items[iGoodIndex].id)
			{
			    case "Instrument1":
		    		describeStr = NewStr() + "Требуется для создания особых боеприпасов";
		    		describeStr2 = "";
		    	break;
				
				case "Instrument2":
		    		describeStr = NewStr() + "Требуется для создания особых зелий и ядов";
		    		describeStr2 = "";
		    	break;
				
				case "Instrument3":
		    		describeStr = NewStr() + "Требуется для создания особых боеприпасов";
		    		describeStr2 = "";
		    	break;
				
				case "Instrument4":
		    		describeStr = "Требуется для создания особых снарядов, зелий и ядов";
		    		describeStr2 = "";
		    	break;
				
				case "Instrument5":
		    		describeStr = "Требуется для создания особых снарядов, зелий и ядов";
		    		describeStr2 = "";
		    	break;
				
				case "Instrument6":
		    		describeStr = NewStr() + "Требуется для создания особых снарядов и ядов";
		    		describeStr2 = "";
		    	break;
				
				case "Instrument7":
		    		describeStr = NewStr() + "Требуется для создания особых зелий";
		    		describeStr2 = "";
		    	break;
				
				case "lockpick":
		    		describeStr = NewStr() + "Требуется для взлома замков";
		    		describeStr2 = "";
		    	break;
				
				case "key1":
		    		describeStr = NewStr() + "Позволяет открывать простые замки";
		    		describeStr2 = "";
		    	break;
				
				case "key2":
		    		describeStr = "Позволяет открывать замки средней сложности";
		    		describeStr2 = "";
		    	break;
				
				case "key3":
		    		describeStr = NewStr() + "Позволяет открывать сложные замки";
		    		describeStr2 = "";
		    	break;
				
				case "key4":
		    		describeStr = NewStr() + "Этот предмет необходим для задания";
		    		describeStr2 = "";
		    	break;
				
				case "DutTradeLicence":
		    		describeStr = NewStr() + "Действует 90 дней";
		    		describeStr2 = "";
		    	break;
			}
			if(describeStr == "" && describeStr2 == "") SetFormatedText("INFO_TEXT_TYPE", NewStr() + "Особый предмет");
			
			SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
			 	
		    SetFormatedText("INFO_TEXT_DMG", describeStr2);
		    SetNodeUsing("INFO_TEXT_DMG", true);
		    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
	    }
		else if(HasSubStr(Items[iGoodIndex].id, "mineral"))
		{
			SetFormatedText("INFO_TEXT_TYPE", "Разное");
			switch(Items[iGoodIndex].id)
			{
			    case "mineral4":
		    		describeStr = NewStr() + "-10 везение";
		    		describeStr2 = "";
					nColor1 = argb(255, 255,125,125);
		    	break;
				
				case "mineral16":
		    		describeStr = NewStr() + "-10 авторитет";
		    		describeStr2 = "";
					nColor1 = argb(255, 255,125,125);
		    	break;
			}
			if(describeStr == "" && describeStr2 == "") SetFormatedText("INFO_TEXT_TYPE", NewStr() + "Разное");
			
			SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
			SetNodeUsing("INFO_TEXT_SUBTYPE", true);
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);
				
		    SetFormatedText("INFO_TEXT_DMG", describeStr2);
			SetNodeUsing("INFO_TEXT_DMG", true);
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
	    }
		else SetFormatedText("INFO_TEXT_TYPE", "Нет группы");
	}
	
	SetFormatedText("INFO_TEXT_DESC", GetAssembledString(LanguageConvertString(lngFileID, Items[iGoodIndex].describe), Items[iGoodIndex]));
	SetNodeUsing("INFO_TEXT_DESC", true);
	
	SetFormatedText("INFO_TEXT_WEIGHT", "Вес: " + FloatToString(stf(Items[iGoodIndex].Weight), 1));
	SetNodeUsing("INFO_TEXT_WEIGHT", true);
	
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
	
	SetNodeUsing("EQUIP_BUTTON", ThisItemCanBeEquip(&Items[iGoodIndex]));
}

void HideItemInfo()
{
	SetNodeUsing("INFO_TEXT_NAME", false);
	SetNodeUsing("INFO_TEXT_TYPE", false);
	SetNodeUsing("INFO_TEXT_SUBTYPE", false);
	SetNodeUsing("INFO_PIC", false);
	SetNodeUsing("INFO_TEXT_SUBTYPE", false);
	SetNodeUsing("INFO_TEXT_DMG", false);
	SetNodeUsing("INFO_TEXT_DESC", false);
	SetNodeUsing("INFO_TEXT_WEIGHT", false);
	
	//SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	//SetSelectable("EQUIP_BUTTON",false);
	SetNodeUsing("EQUIP_BUTTON", false);
}

bool ThisItemCanBeEquip(aref arItem)
{
	if(!CheckAttribute(arItem,"groupID"))
	{
		return false;
	}
	
	if(!IsCanEquiping(pchar, arItem.groupID))
	{
		return false;
	}
	
	if (arItem.groupID == AMMO_ITEM_TYPE) 
	{
		if (arItem.ID == "GunPowder") return false;
	}
	
	if (arItem.groupID == GUN_ITEM_TYPE) 
	{
		if (!CheckAttribute(arItem,"chargeQ"))
		{
			return false;
		}
		int chrgQ = sti(arItem.chargeQ);,
	
		if (chrgQ >= 2 && !IsCharacterPerkOn(pchar,"Musketeer"))
		{
			return false;
		}
		
		// Для мушкетов нужен соответствующий перк
		if(HasSubStr(arItem.id, "mushket") && !IsCharacterPerkOn(pchar,"Breter"))
		{
			return false;
		}
		
		// Нельзя экипировать мушкет в непредназначенных для этого локациях (Таверна)
		if(HasSubStr(arItem.id, "mushket") && !CanEquipMushketOnLocation(PChar.Location))
		{
			return false;
		}
		
		// Если это не главный герой, то мушкет экипировать нельзя
		if(HasSubStr(arItem.id, "mushket") && !IsMainCharacter(pchar))
		{
			return false;
		}
	}
    
    if (IsEquipCharacterByItem(pchar, arItem.id))
	{
		if(arItem.groupID == BLADE_ITEM_TYPE)
		{
			return false;
		}
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
	}
	else
	{
		if (arItem.groupID == CIRASS_ITEM_TYPE && arItem.Clothes == false)
	    {
			if(arItem.id == "cirass4" || arItem.id == "cirass5")
			{
				if(!IsCharacterPerkOn(pchar, "Knight")) return false;
			}
			
			if(arItem.id == "cirass2" || arItem.id == "cirass3")
			{
				if(!IsCharacterPerkOn(pchar, "BasicDefense")) return false;
			}
	    }
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	
	if(CheckAttribute(PChar, "IsMushketer"))
	{
		if(arItem.ID == PChar.IsMushketer.MushketID)
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
			return true;
		}
		
		if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == SPYGLASS_ITEM_TYPE || arItem.groupID == GUN_ITEM_TYPE || arItem.groupID == CIRASS_ITEM_TYPE)
		{
			return false;
		}
	}
	
	return true;
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
    switch(nodName)
	{
		case "EQUIP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
			}
		break;
		
		case "ICON_KEY_F":
			if (comName=="activate" || comName=="click")
			{
				FavouriteChange("Potion1");
			}
		break;
		
		case "ICON_KEY_C":
			if (comName=="activate" || comName=="click")
			{
				FavouriteChange("Potion2");
			}
		break;
		
		case "ICON_KEY_X":
			if (comName=="activate" || comName=="click")
			{
				FavouriteChange("Poison");
			}
		break;
		
		case "TAKE_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				FavouriteEquipPress();
			}
		break;
	}
}

void EquipPress()
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	int  i;
	
	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		switch (itmGroup)
		{
	    	case SPECIAL_ITEM_TYPE:
			    if (findsubstr(itmRef.id, "recipe_" , 0) != -1) // рецепты
				{
					if (isMultiObjectKnown(itmRef.result))
					{
						PlaySound("interface\knock.wav");
						log_info("Вам уже известен этот рецепт!");
					}
					else
					{
						RemoveItems(pchar, itmRef.id, 1);
						AddQuestRecordInfo("Recipe", itmRef.result);
						SetAlchemyRecipeKnown(itmRef.result);
					}
				}
				
				if (itmRef.id == "purse1") // кошель
				{
					int irand = (rand(91)+12)
					RemoveItems(pchar, itmRef.id, 1);
					TakeNItems(pchar, "gold_dublon", irand);
					PlaySound("Ambient\Tavern\monetki_taverna_001.wav");
					log_info("Получено "+irand+" дублонов");
				}
				
				if(CheckAttribute(itmRef, "potion.special") && itmRef.potion.special.effect != "")
				{
					if(CheckAttribute(pchar, "SpeciaPotionEffect."+itmRef.potion.special.effect))
					{
						PlaySound("interface\knock.wav");
					}
					else
					{
				        DoCharacterUsedItem(pchar, itmRef.id);
					}
				}
				
				if (itmRef.id == "Chest_closed" && pchar.id == pchar.id)
                {
                    pchar.questTemp.Lockpicking.ID = itmRef.id;
                    IDoExit(RC_INTERFACE_LOCKPICKING);
                    return;
                }
				SetVariable();
				return;
	    	break;
			case POISON_ITEM_TYPE:
			    DoCharacterUsedPoison(pchar, itmRef.id);
				
				SetVariable();
				return;
	    	break;
	    	case RATPOISON_ITEM_TYPE:
			    if(!CheckAttribute(pchar, "questTemp.arsenic"))
				{
			        pchar.questTemp.arsenic = true;
		    		RemoveItems(pchar, itmRef.id, 1);
	    			Log_TestInfo("Мышьяк у персонажа "+pchar.id+" активирован!");
    				SetRatPoisonTimerFunctionParam(pchar.id + "_RemoveRatPoisonEffectFromCharacter", "RemoveRatPoisonEffectFromCharacter", 0, 0, 30, pchar);
				}
				else
				{
					Log_TestInfo("Куда второй мышьяк этому персу-то? ("+pchar.id+")");
					PlaySound("interface\knock.wav");
				}
				SetVariable();
				return;
	    	break;
			
			case AMMO_ITEM_TYPE:
				string sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
				if (itmRef.ID == "bullet" || itmRef.ID == "cartridge" || itmRef.ID == "silver_bullet" || itmRef.ID == "Silver_cartridge")
				{
					if (sGun == "pistol2" || sGun == "pistol4" || sGun == "pistol8" || sGun == "pistol9" || sGun == "mushket_Arquebus" || sGun == "mushket_Portuguese")
					{
						PlaySound("interface\knock.wav");
						return;
					}
				}
				if (itmRef.ID == "grapeshot"|| itmRef.ID == "gunechin")
				{	
					if (sGun != "pistol2" && sGun != "pistol4" && sGun != "pistol9" && sGun != "mushket_Arquebus" && sGun != "mushket_Portuguese")
					{
						PlaySound("interface\knock.wav");
						return;
					}
				}
				if (itmRef.ID == "petard" || itmRef.ID == "grenade" || itmRef.ID == "Poison_bomb")
				{	
					if (sGun != "mushket_sklopetta" && sGun != "mushket_Bombard")
					{
						PlaySound("interface\knock.wav");
						return;
					}
				}
				LAi_SetCharacterUseBullet(pchar, itmRef.ID);
				LAi_GunSetUnload(pchar);
				log_info("Выбран боеприпас - "+GetConvertStr(itmRef.name, "ItemsDescribe.txt")+"");
				PlaySound("People Fight\reload1.wav");
				RemoveCharacterEquip(pchar, itmGroup);
				SetVariable();
				return;
	    	break;
		}
		
		if(HasSubStr(itmRef.id, "Mushket") && (pchar.sex != "woman") ) // Пытаемся одеть мушкет... на тетку не оденеться, нет анимации
		{
		    if(!CheckAttribute(PChar, "IsMushketer")) // Не мушкетер. Делаем мушкетером
		    {
		        SetMainCharacterToMushketer(itmRef.id, true);
		    }
		    else // Мушкетер. Делаем обычным фехтовальщиком
		    {
		        SetMainCharacterToMushketer("", false);
		    }
		}
		else
		{
    	    if(IsEquipCharacterByItem(pchar, itmRef.id))
	        {
			    RemoveCharacterEquip(pchar, itmGroup);
		    }
    	    else
	        {
			    EquipCharacterByItem(pchar, itmRef.id);
		    }
		}
		FillItemsSelected();
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
		SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
	}
}

void FavouriteChange(string sVar)
{
	sFavVariant = sVar;
    XI_WindowShow("FAVOURITE_WINDOW", true);
	XI_WindowDisable("FAVOURITE_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	FillFavouriteTable();
	SetCurrentNode("TABLE_FAVOURITE");
}

void ExitFavouriteMenu()
{
	sFavVariant = "";
	XI_WindowShow("FAVOURITE_WINDOW", false);
	XI_WindowDisable("FAVOURITE_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_ITEMS");
	FillItemsSelected();
}

void FillFavouriteTable()
{
	int n, i;
	string row;
	string sGood;
	int  idLngFile;
	aref rootItems, arItem;
	aref  curItem;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_FAVOURITE", false, true, false);
	
    if(sFavVariant == "Potion1" || sFavVariant == "Potion2") SetFormatedText("INFO_TEXT_FAVOURITE", "Зелья");
	else SetFormatedText("INFO_TEXT_FAVOURITE", "Яды");
	
	// Заполним вещами от нас
	makearef(rootItems, pchar.Items);
    for (i = 0; i < GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{
			row = "tr" + n;
			sGood = arItem.id;

			if(sFavVariant == "Potion1" || sFavVariant == "Potion2")
			{
				if(!CheckAttribute(arItem, "potion")) continue;
			}
			else if(arItem.groupID != POISON_ITEM_TYPE) continue;
			
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v1") && pchar.GenQuest.Potion_choice.v1 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v1") && pchar.GenQuest.Potion_choice.v2 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v2") && pchar.GenQuest.Potion_choice.v2 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v2") && pchar.GenQuest.Potion_choice.v1 == arItem.id) continue;
			
			if (GetCharacterItem(pchar, sGood) > 0)
			{
				GameInterface.TABLE_FAVOURITE.(row).index = GetItemIndex(arItem.id);
				
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.offset = "2,4";
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.width = 52;
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.height = 52;
				GameInterface.TABLE_FAVOURITE.(row).td1.textoffset = "60,0";
				GameInterface.TABLE_FAVOURITE.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_FAVOURITE.(row).td1.scale = 1;
				
				GameInterface.TABLE_FAVOURITE.(row).td2.str   = GetCharacterItem(pchar, sGood);
				GameInterface.TABLE_FAVOURITE.(row).td2.scale = 1;
				GameInterface.TABLE_FAVOURITE.(row).td2.textoffset = "15,0";
				
				n++;
			}
		}
    }
	GameInterface.TABLE_FAVOURITE.select = 1;
	GameInterface.TABLE_FAVOURITE.top = 0;
	
	CurTable = "TABLE_FAVOURITE";
	CurRow = "tr1";
    
	Table_UpdateWindow("TABLE_FAVOURITE");
	LanguageCloseFile(idLngFile);
	
	if(GameInterface.TABLE_FAVOURITE.tr1.index <= 0)
	{
		SetSelectable("TAKE_BUTTON",false);
	}
}

void FavouriteEquipPress()
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	
	if (sFavVariant != "")
	{
		switch (sFavVariant)
		{
	    	case "Potion1":
			    pchar.GenQuest.Potion_choice.v1 = itmRef.id;
			break;
			
			case "Potion2":
			    pchar.GenQuest.Potion_choice.v2 = itmRef.id;
			break;
			
			case "Poison":
			    pchar.GenQuest.Poison_choise = itmRef.id;
			break;
		}
		FillFavouriteTable();
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"TAKE_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	ExitFavouriteMenu();
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_TEST);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("ExitFavouriteMenu","ExitFavouriteMenu");
	DelEventHandler("FavouriteChange","FavouriteChange");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ExitFavouriteMenu","ExitFavouriteMenu");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}
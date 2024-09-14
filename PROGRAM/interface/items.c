#include "interface\character_all.h"

bool canMove = true;
float fOffsetX, fOffsetY;
string effects[5];
int qItems[5];

string sFavVariant = "";
int curMode;
int idLngFile;
string MoveQueue;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ИНИЦИАЛИЗАЦИЯ
////////////////////////////////////////////////////////////////////////////

void InitInterface(string iniName)	// основной инит
{
	GameInterface.title = "TitleTest";
	InterfaceStack.SelectMenu_node = "LaunchItems";
	
	GetXYWindowOffset(&fOffsetX, &fOffsetY);
	StartSetEventHandlers();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	XI_RegistryExitKey("IExit_F2");
	XI_RegistryExitKey("IExit_Escape");

	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	
	for(int i=0; i<5; i++)
		qItems[i] = 0;
	curMode = 1;
	
	StartHideNodes();
    StartFillNodes();
	MoveQueue = "";
}

void StartSetEventHandlers()	// выставление эвентов
{
	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("ExitFavouriteMenu","ExitFavouriteMenu",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);

	SetEventHandler("RemovePistol","RemovePistol",0);
	SetEventHandler("RemoveMushket","RemoveMushket",0);
	SetEventHandler("RemoveSpyglass","RemoveSpyglass",0);
	SetEventHandler("RemoveCuirass","RemoveCuirass",0);
	SetEventHandler("RemoveTalisman","RemoveTalisman",0);
	SetEventHandler("RemovePotion1","RemovePotion1",0);
	SetEventHandler("RemovePotion2","RemovePotion2",0);
	SetEventHandler("RemovePoison","RemovePoison",0);
	
	SetEventHandler("MoveFinished","MoveFinished",0);
	
	SetEventHandler("Event_SelectNode","SelectNode",0);
	SetEventHandler("Event_UnselectNode","UnselectNode",0);
	
	SetEventHandler("OpenEffects","OpenEffects",0);
	SetEventHandler("CloseEffects","CloseEffects",0);
	
	SetEventHandler("Interface_PressControl", "Interface_PressControl", 0);
	
	SetEventHandler("SetNodeMoveListPosition", "SetNodeMoveListPosition", 0);
}

void SetNodeMoveListPosition()	// стартовые позиции для мувлиста
{
	string sNode = GetEventData();
	int MLindex = GetEventData();
	int x1 = GetEventData();
	x1 -= makeint(fOffsetX);
	int y1 = GetEventData();
	int x2 = GetEventData();
	x2 -= makeint(fOffsetX);
	int y2 = GetEventData();
	AddNodeToMoveList(MLindex, sNode, x1, y1, x2, y2);
}	

void StartHideNodes()	// стартовое выключение лишнего
{
	SetNodeUsing("EFFECT_EQUIP", false);
	SetNodeUsing("VIDEOFRAME_EQUIP", false);
	SetNodeUsing("EFFECTS_CLOSE",false);
	SetNodeUsing("GLOW_BLADE", false);
	SetNodeUsing("GLOW_PISTOL", false);
	SetNodeUsing("GLOW_MUSHKET", false);
	SetNodeUsing("GLOW_CUIRASS", false);
	SetNodeUsing("GLOW_SPYGLASS", false);
	SetNodeUsing("GLOW_TALISMAN", false);
	SetNodeUsing("INFO_TEXT_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_NAME_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_NAME_FALSE", false);
	SetNodeUsing("TITLE_ITEMS_FALSE", false);
}

void StartFillNodes()	// стартовое заполнение таблиц
{
	CurRow = "";
	GameInterface.TABLE_ITEMS.hr.td1.str = "Название";
	GameInterface.TABLE_ITEMS.hr.td1.textoffset = "45,0";
	GameInterface.TABLE_ITEMS.hr.td2.str = "Кол-во";
	GameInterface.TABLE_ITEMS.hr.td3.str = "Вес";
	GameInterface.TABLE_FAVOURITE.hr.td1.str = "";
	GameInterface.TABLE_FAVOURITE.hr.td2.str = "Название";
//	GameInterface.TABLE_FAVOURITE.hr.td2.textoffset = "36,0";
	GameInterface.TABLE_FAVOURITE.hr.td3.str = "Кол-во";
	RefreshHeroParams();
	ResetItems();
	CheckButtons();
}

void ProcessExitCancel()	// основной выход
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)	// выход
{
	ExitDelEventHandlers();
	
	ClearMoveList(1);
	ClearMoveList(2);
	ClearMoveList(3);
	
	LanguageCloseFile(idLngFile);

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void ExitDelEventHandlers()	// удаление эвентов
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("ExitFavouriteMenu","ExitFavouriteMenu");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	
	DelEventHandler("OpenEffects","OpenEffects");
	DelEventHandler("CloseEffects","CloseEffects");
	DelEventHandler("Interface_PressControl","Interface_PressControl");
	DelEventHandler("MoveFinished","MoveFinished");
	DelEventHandler("Event_SelectNode","SelectNode");
	DelEventHandler("Event_UnselectNode","UnselectNode");
	
	DelEventHandler("SetNodeMoveListPosition", "SetNodeMoveListPosition");
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ОСНОВНАЯ ОБРАБОТКА
////////////////////////////////////////////////////////////////////////////

void ProcessCommandExecute()	// считывание команд
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
		
		case "EQUIP_BUTTON_GUN":
			if (comName=="activate" || comName=="click")
			{
				EquipAmmo("pistol");
			}
		break;
		
		case "EQUIP_BUTTON_MUS":
			if (comName=="activate" || comName=="click")
			{
				EquipAmmo("musket");
			}
		break;
		
		case "REMOVE_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				RemovePress();
			}
		break;
		
		case "REMOVE_BUTTON_GUN":
			if (comName=="activate" || comName=="click")
			{
				RemoveAmmo("pistol");
			}
		break;
		
		case "REMOVE_BUTTON_MUS":
			if (comName=="activate" || comName=="click")
			{
				RemoveAmmo("musket");
			}
		break;
		
		case "USE_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				UsePress();
			}
		break;
		
		case "ICON_KEY_F":
			if (comName=="activate" || comName=="click")
			{
				if(sFavVariant == "")
					FavouriteChange("Potion1");
				else
				{
					if(sFavVariant != "Potion1")
					{
						sFavVariant = "Potion1";
						ActivateEffect("potion1");
						RefreshFavouriteMenu();
					}
					else
						ExitFavouriteMenu();
				}
			}
		break;
		
		case "ICON_KEY_C":
			if (comName=="activate" || comName=="click")
			{
				if(sFavVariant == "")
					FavouriteChange("Potion2");
				else
				{
					if(sFavVariant != "Potion2")
					{
						sFavVariant = "Potion2";
						ActivateEffect("potion2");
						RefreshFavouriteMenu();
					}
					else
						ExitFavouriteMenu();
				}
			}
		break;
		
		case "ICON_KEY_X":
			if (comName=="activate" || comName=="click")
			{
				if(sFavVariant == "")
					FavouriteChange("Poison");
				else
				{
					if(sFavVariant != "Poison")
					{
						sFavVariant = "Poison";
						ActivateEffect("poison");
						RefreshFavouriteMenu();
					}
					else
						ExitFavouriteMenu();
				}
			}
		break;
		
		case "TAKE_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				FavouriteEquipPress();
			}
		break;
		
		case "TITLE_CHARACTERS":
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", "I_CHARACTER", 2);
				return;
			}
		break;
		case "TITLE_SHIPS":
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", "I_SHIP", 2);
				return;
			}
		break;
		case "TITLE_JOURNAL":
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", "I_QUESTBOOK", 2);
				return;
			}
		break;
		case "FRAME_BLADE":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("blade");
				SetSortOffPictures();
				FillItemsTable(7);
			}
		break;
		case "FRAME_PISTOL":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("pistol");
				SetSortOffPictures();
				FillItemsTable(8);
			}
		break;
		case "FRAME_PISTOL_AMMO":
			if(comName=="activate" || comName=="click")
			{
				if(sFavVariant == "")
					FavouriteChange("Pistol_ammo");
				else
				{
					if(sFavVariant != "Pistol_ammo")
					{
						sFavVariant = "Pistol_ammo";
						ActivateEffect("pistol_ammo");
						RefreshFavouriteMenu();
					}
					else
						ExitFavouriteMenu();
				}
			}
		break;
		case "FRAME_SPYGLASS":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("spyglass");
				SetSortOffPictures();
				FillItemsTable(9);
			}
		break;
		case "FRAME_CUIRASS":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("cuirass");
				SetSortOffPictures();
				FillItemsTable(10);
			}
		break;
		case "FRAME_TALISMAN":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("talisman");
				SetSortOffPictures();
				FillItemsTable(11);
			}
		break;
		case "FRAME_MUSHKET":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("mushket");
				SetSortOffPictures();
				FillItemsTable(12);
			}
		break;
		case "FRAME_MUSHKET_AMMO":
			if(comName=="activate" || comName=="click")
			{
				if(sFavVariant == "")
					FavouriteChange("Mushket_ammo");
				else
				{
					if(sFavVariant != "Mushket_ammo")
					{
						sFavVariant = "Mushket_ammo";
						ActivateEffect("mushket_ammo");
						RefreshFavouriteMenu();
					}
					else
						ExitFavouriteMenu();
				}
			}
		break;
		case "FRAME_HAT":
			if(comName == "click")
			{
				if(sFavVariant != "")
					ExitFavouriteMenu();
				ActivateEffect("hat");
				SetSortOffPictures();
				FillItemsTable(13);
			}
		break;
	}
}

void TableSelectChange()	// обработка выбора ячейки в таблице
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    
    // отрисовка инфы
	if(CurTable == "TABLE_ITEMS")
	{
		SetItemInfo();
		return;
	}
	if(CurTable == "TABLE_FAVOURITE")
	{
		if(GameInterface.TABLE_FAVOURITE.(CurRow).UserData.equip == true)
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"TAKE_BUTTON",0, "#"+XI_ConvertString("Remove that"));
		}
		else
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"TAKE_BUTTON",0, "#"+XI_ConvertString("Equip that"));
		}
		SetFavouriteInfo();
	}
}

void procTabChange()	// нажатие на кнопку сортировки
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode(1);
		return;
	}
	
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode(2);
		return;
	}
	
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabMode(3);
		return;
	}
	
	if( sNodName == "TABBTN_4" )
	{
		SetControlsTabMode(4);
		return;
	}
	
	if( sNodName == "TABBTN_5" )
	{
		SetControlsTabMode(5);
		return;
	}
	
	if( sNodName == "TABBTN_6" )
	{
		SetControlsTabMode(6);
		return;
	}
}

void Interface_PressControl()	// обработка нажатия хоткеев
{
	string sKey = GetEventData();
	switch(sKey)
	{
		case "F":	FavouriteChange("Potion1");		break;
		case "C":	FavouriteChange("Potion2");		break;
		case "X":	FavouriteChange("Poison");		break;
	}
}

void MoveFinished()	// обработка конца движения группы нод
{
	int mIdx = GetEventData();
	string tag = GetEventData();
	switch(mIdx)
	{
		case 1:
			if(tag == "close")
			{
			//	XI_WindowShow("FAVOURITE_WINDOW", false);
			//	XI_WindowDisable("FAVOURITE_WINDOW", true);
			//	XI_WindowDisable("MAIN_WINDOW", false);

				SetCurrentNode("TABLE_ITEMS");
			}
			if(tag == "open")
			{
				SetNodeUsing("TAKE_BUTTON", true);
				SetNodeUsing("INFO_TEXT_FAVOURITE", true);
				SetNodeUsing("INFO_TEXT_FAVOURITE_FALSE", false);
				SetNodeUsing("INFO_TEXT_NAME_FAVOURITE", true);
				SetNodeUsing("INFO_TEXT_NAME_FAVOURITE_FALSE", false);
			}
		break;
		
		case 2:
			if(tag == "open")
			{
				SetNodeUsing("EFFECTS_OPEN", false);
				SetNodeUsing("EFFECTS_CLOSE", true);
			}
			if(tag == "close")
			{
				SetNodeUsing("EFFECTS_OPEN", true);
				SetNodeUsing("EFFECTS_CLOSE", false);
			}
		break;
		
		case 3:
			if(tag == "open")
			{
				SetCurrentNode("TABLE_ITEMS");
				SetNodeUsing("INFO_TEXT_NAME_FALSE", false);
				SetNodeUsing("TITLE_ITEMS_FALSE", false);
				SetNodeUsing("INFO_TEXT_NAME", true);
				SetNodeUsing("TITLE_ITEMS", true);
			}
			if(tag == "close")
			{
				SetCurrentNode("TABLE_FAVOURITE");
			}
		break;
	}
	canMove = true;
	if(MoveQueue != "")
	{
		if(MoveQueue == "inventory")
			ExitFavouriteMenu();
		else
			FavouriteChange(MoveQueue);
	}
}

void SelectNode()	// наведение курсора на ноду
{
	string sNode = GetEventData();
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_BLADE", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_PISTOL", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_PISTOL_AMMO", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_SPYGLASS", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_CUIRASS", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_TALISMAN", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_MUSHKET", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_MUSHKET_AMMO", 4, argb(0,255,255,255));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "FRAME_HAT", 4, argb(0,255,255,255));
	switch(sNode)
	{
		case "FRAME_BLADE":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_PISTOL":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_PISTOL_AMMO":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_SPYGLASS":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_CUIRASS":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_TALISMAN":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_MUSHKET":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_MUSHKET_AMMO":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "FRAME_HAT":
			SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255,255,255,255) );
		break;
		case "EFFECT_ICON1":
			ShowEffectInfo(1);
		break;
		case "EFFECT_ICON2":
			ShowEffectInfo(2);
		break;
		case "EFFECT_ICON3":
			ShowEffectInfo(3);
		break;
		case "EFFECT_ICON4":
			ShowEffectInfo(4);
		break;
	}
}

void UnselectNode()	// с ноды убран курсор
{
	string sNode = GetEventData();
	switch(sNode)
	{
		case "FRAME_BLADE":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_PISTOL":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_PISTOL_AMMO":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_SPYGLASS":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_CUIRASS":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_TALISMAN":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_MUSHKET":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_MUSHKET_AMMO":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "FRAME_HAT":
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 4, argb(0,255,255,255) );
		break;
		case "EFFECT_ICON1":
			HideEffectInfo(1);
		break;
		case "EFFECT_ICON2":
			HideEffectInfo(2);
		break;
		case "EFFECT_ICON3":
			HideEffectInfo(3);
		break;
		case "EFFECT_ICON4":
			HideEffectInfo(4);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ОСНОВНОЙ ЭКРАН
////////////////////////////////////////////////////////////////////////////

void RefreshHeroParams()	// обновление параметров героя (деньги, вес, ранг, опыт)
{
	SetFormatedText("GOLD_BAR_TEXT", MakeMoneyShow(sti(pChar.Money), MONEY_SIGN,MONEY_DELIVER));
	SetFormatedText("WEIGHT_BAR_TEXT", FloatToString(GetItemsWeight(pChar), 1) + " / "+sti(GetMaxItemsWeight(pChar)));
	SetFormatedText("LEVEL_TEXT", pChar.rank);
	
	GameInterface.StatusLine.LEVEL_BAR.Max = GetCharacterRankRate(pChar);
    GameInterface.StatusLine.LEVEL_BAR.Min = 0;
    GameInterface.StatusLine.LEVEL_BAR.Value = GetCharacterRankRateCur(pChar);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LEVEL_BAR",0);
}

void ResetItems()	// заполнение предметов с проверкой фильтров
{
	SetNodeUsing("INFO_PIC", false);
	SortItems(pchar);
	CheckForEmptySort();
	if(curMode != 1 && qItems[curMode-2] == 0)
		curMode = 1;
	SetControlsTabMode(curMode);
	FillItemsSelected();
}

void CheckForEmptySort()
{
	int i;
	int nItems[5];
	for (i=0; i<5; i++)
		nItems[i] = 0;
	string groupID;
	string itemType;
	aref rootItems, arItem;
	aref  curItem;
	makearef(rootItems, pchar.Items);
    for (i = 0; i < GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		itemType = "";
		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{			
			if(CheckAttribute(arItem, "groupID")) groupID = arItem.groupID;
			if(CheckAttribute(arItem, "itemType")) itemType = arItem.itemType;
			
			if((groupID == BLADE_ITEM_TYPE) || (groupID == GUN_ITEM_TYPE) || (groupID == MUSKET_ITEM_TYPE) || (groupID == SPYGLASS_ITEM_TYPE) || (groupID == CIRASS_ITEM_TYPE) || (groupID == AMMO_ITEM_TYPE) || (groupID == TALISMAN_ITEM_TYPE))
			{
				nItems[0]++;
			}
			if((CheckAttribute(arItem, "potion")) || (CheckAttribute(arItem, "poison")))
			{
				nItems[1]++;
			}
			if((HasSubStr(arItem.id, "ingredient")) && (!CheckAttribute(arItem, "special_item")))
			{
				nItems[2]++;
			}
			if((itemType == "QUESTITEMS") || (CheckAttribute(arItem, "special_item")))
			{
				nItems[3]++;
			}
			if((HasSubStr(arItem.id, "mineral")) || (HasSubStr(arItem.id, "jewelry")))
			{
				nItems[4]++;
			}
		}
    }
	string sNode;
	for(i=0; i<5; i++)
	{
		qItems[i] = nItems[i];
		if(qItems[i] == 0)
		{
			sNode = "TABBTN_"+(i+2);
			SendMessage(&GameInterface,"lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(100,128,128,128));
			SendMessage(&GameInterface,"lslll", MSG_INTERFACE_MSG_TO_NODE, sNode, -1, 1, false);
		}
	}
}

void SetControlsTabMode(int nMode)	// установка сортировки с заполнением таблицы
{
	string sPic1 = "All_off";
	string sPic2 = "Gear_off";
	string sPic3 = "Potion_off";
	string sPic4 = "Ingredients_off";
	string sPic5 = "Quest_off";
	string sPic6 = "Other_off";

	switch (nMode)
	{
		case 1:		sPic1 = "All_on";			break;
		case 2:		sPic2 = "Gear_on";			break;
		case 3:		sPic3 = "Potion_on";		break;
		case 4:		sPic4 = "Ingredients_on";	break;
		case 5:		sPic5 = "Quest_on";			break;
		case 6:		sPic6 = "Other_on";			break;
	}
	ActivateEffect("");
	SetNewGroupPicture("TABBTN_1", "TABS_NEW", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS_NEW", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS_NEW", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS_NEW", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS_NEW", sPic5);
	SetNewGroupPicture("TABBTN_6", "TABS_NEW", sPic6);
	FillItemsTable(nMode);
}

void RefreshItems()	// обновление предметов без обнуления
{
	FillItemsSelected();
/*	string sRow = GameInterface.TABLE_ITEMS.select;
	string ssTop = GameInterface.TABLE_ITEMS.top;
	FillItemsTable(curMode);
	Event("TableSelectChange", "sll", "TABLE_ITEMS", iSelected, 0);
	GameInterface.TABLE_ITEMS.select = sRow;
	GameInterface.TABLE_ITEMS.top = ssTop;
	Table_UpdateWindow("TABLE_ITEMS");	*/
	SetItemInfo();
}

void FillItemsTable(int _mode)	// заполнение таблицы предметов (1-6 - обычная сортировка, 7-11 - специальная)
{
	int n, i;
	string row;
	string sGood;
	string groupID;
	string itemType;
	bool ok[14];
	ok[1] = true;
	aref rootItems, arItem;
	aref  curItem;
	n = 1;

	Table_Clear("TABLE_ITEMS", false, true, false);
	
	switch(_mode)
	{
		case 1:		SetFormatedText("INFO_TEXT_SORT", "Всё");				break;
		case 2:	    SetFormatedText("INFO_TEXT_SORT", "Снаряжение");		break;
		case 3:	    SetFormatedText("INFO_TEXT_SORT", "Зелья и яды");		break;
		case 4:	    SetFormatedText("INFO_TEXT_SORT", "Ингредиенты");		break;
		case 5:	    SetFormatedText("INFO_TEXT_SORT", "Особое");			break;
		case 6:	    SetFormatedText("INFO_TEXT_SORT", "Разное");			break;
		// evganat - специальная сортировка
		case 7:		SetFormatedText("INFO_TEXT_SORT", "Клинки");			break;
		case 8:		SetFormatedText("INFO_TEXT_SORT", "Пистолеты");			break;
		case 9:		SetFormatedText("INFO_TEXT_SORT", "Подзорные трубы");	break;
		case 10:	SetFormatedText("INFO_TEXT_SORT", "Кирасы");			break;
		case 11:	SetFormatedText("INFO_TEXT_SORT", "Талисманы");			break;
		case 12:	SetFormatedText("INFO_TEXT_SORT", "Мушкеты");			break;
		case 13:	SetFormatedText("INFO_TEXT_SORT", "Головные уборы");	break;
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
			ok[2] = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
					(groupID == GUN_ITEM_TYPE)	||		// пистолеты
					(groupID == MUSKET_ITEM_TYPE)	||		// мушкеты
					(groupID == SPYGLASS_ITEM_TYPE) || // подзорные трубы
					(groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
					(groupID == AMMO_ITEM_TYPE) ||        // боеприпасы
					(groupID == TALISMAN_ITEM_TYPE);        // талисманы	 
			// Зелья -->
			ok[3] = (CheckAttribute(arItem, "potion")) || (CheckAttribute(arItem, "poison"));
			// Ингредиенты -->
			ok[4] = (HasSubStr(arItem.id, "ingredient")) && (!CheckAttribute(arItem, "special_item"));
			// особое -->
			ok[5] = (itemType == "QUESTITEMS") || (CheckAttribute(arItem, "special_item")); //важное
			// Разное -->
			ok[6] = (HasSubStr(arItem.id, "mineral")) || (HasSubStr(arItem.id, "jewelry")); // разное
			// Специальная сортировка -->
			ok[7] = (groupID == BLADE_ITEM_TYPE);
			ok[8] = (groupID == GUN_ITEM_TYPE);
			ok[9] = (groupID == SPYGLASS_ITEM_TYPE);
			ok[10] = (groupID == CIRASS_ITEM_TYPE);
			ok[11] = (groupID == TALISMAN_ITEM_TYPE);
			ok[12] = (groupID == MUSKET_ITEM_TYPE);
			ok[13] = (groupID == HAT_ITEM_TYPE);
			
			if(!ok[_mode]) continue;
			
			if (GetCharacterItem(pchar, sGood) > 0)
			{
				GameInterface.TABLE_ITEMS.(row).index = GetItemIndex(arItem.id);
				
				GameInterface.TABLE_ITEMS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "2, 2";
				GameInterface.TABLE_ITEMS.(row).td1.icon.width = 32;
				GameInterface.TABLE_ITEMS.(row).td1.icon.height = 32;
				GameInterface.TABLE_ITEMS.(row).td1.textoffset = "45,0";
				GameInterface.TABLE_ITEMS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_ITEMS.(row).td1.scale = 1.1;
				
				int nItems = GetCharacterItem(pchar, sGood);
				GameInterface.TABLE_ITEMS.(row).td2.str   = nItems;
				GameInterface.TABLE_ITEMS.(row).td2.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td2.textoffset = "0,0";
				
				GameInterface.TABLE_ITEMS.(row).td3.str   = FloatToString(nItems*stf(arItem.Weight), 1);
				GameInterface.TABLE_ITEMS.(row).td3.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td3.textoffset = "0,0";
				
				n++;
			}
		}
    }
	
	if(!CheckAttribute(&GameInterface, "TABLE_ITEMS."+CurRow+".index") || curMode != _mode)
	{
		GameInterface.TABLE_ITEMS.select = 1;
		SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_ITEMS", 3);
		GameInterface.TABLE_ITEMS.top = 0;
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_ITEMS",0.0);
		CurRow = "tr1";
	}
	curMode = _mode;
    
	Table_UpdateWindow("TABLE_ITEMS");

/*	if (_mode == 1)
	{
		FillItemsSelected();
	}	*/
	CurTable = "TABLE_ITEMS";
		
	
	if(!CheckAttribute(&GameInterface, CurTable+"."+CurRow+".index") || sti(GameInterface.(CurTable).(CurRow).index) == 0)
		HideItemInfo();
	else
		SetItemInfo();
}

void FillItemsSelected()	// заполнение слотов экипировки
{
	int i;
	string sGood;
	int iLastGunItem;
	ref rLastGunItem;
	
	// Скроем по умолчанию
	SetEquipDefaultPicture("blade");
	SetEquipDefaultPicture("pistol");
	SetEquipDefaultPicture("pistol_ammo");
	SetEquipDefaultPicture("spyglass");
	SetEquipDefaultPicture("cuirass");
	SetEquipDefaultPicture("talisman");
	SetEquipDefaultPicture("mushket");
	SetEquipDefaultPicture("mushket_ammo");
	SetEquipDefaultPicture("hat");
	SetEquipDefaultPicture("potion1");
	SetEquipDefaultPicture("potion2");
	SetEquipDefaultPicture("poison");
	
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
						SetRareGlow("GLOW_BLADE", Items[i].rare);
						SetNodeUsing("GLOW_BLADE" , true);
					break;
 					case GUN_ITEM_TYPE:
						SetNewGroupPicture("ICON_PISTOL", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetRareGlow("GLOW_PISTOL", Items[i].rare);
						SetNodeUsing("GLOW_PISTOL" , true);
					break;
					case MUSKET_ITEM_TYPE:
						SetNewGroupPicture("ICON_MUSHKET", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetRareGlow("GLOW_MUSHKET", Items[i].rare);
						SetNodeUsing("GLOW_MUSHKET" , true);
					break;
 					case SPYGLASS_ITEM_TYPE:
						SetNewGroupPicture("ICON_SPYGLASS", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetRareGlow("GLOW_SPYGLASS", Items[i].rare);
						SetNodeUsing("GLOW_SPYGLASS" , true);
					break;
 					case CIRASS_ITEM_TYPE:
						SetNewGroupPicture("ICON_CUIRASS", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetRareGlow("GLOW_CUIRASS", Items[i].rare);
						SetNodeUsing("GLOW_CUIRASS", true);
					break;
					case TALISMAN_ITEM_TYPE:
						SetNewGroupPicture("ICON_TALISMAN", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetRareGlow("GLOW_TALISMAN", Items[i].rare);
						SetNodeUsing("GLOW_TALISMAN", true);
					break;
				}
			}
			
			if(CheckAttribute(&Items[i], "groupID") && Items[i].groupID == AMMO_ITEM_TYPE)
			{
				if(CheckAttribute(pchar, "bullets.pistol") && pchar.bullets.pistol == sGood)
				{
					SetNewGroupPicture("ICON_PISTOL_AMMO", Items[i].picTexture, "itm" + Items[i].picIndex);
				}
				if(CheckAttribute(pchar, "bullets.musket") && pchar.bullets.musket == sGood)
				{
					SetNewGroupPicture("ICON_MUSHKET_AMMO", Items[i].picTexture, "itm" + Items[i].picIndex);
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
	UpdateRareGlow();
}

void SetItemInfo()	// отображение информации, проверка экипируемости выбранного
{
	if(CurTable != "TABLE_ITEMS") return;
	
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	int nColor1 = argb(255,255,255,255);
	int nColor2 = argb(255,255,255,255);
	string describeStr, describeStr2;
	describeStr = "";
	describeStr2 = "";
	ref arItem, itmRef;
	makeref(itmRef, Items[iGoodIndex]);
	aref arParam;
	
	SetFormatedText("INFO_TEXT_NAME", GetConvertStr(itmRef.name, "ItemsDescribe.txt"));
	SetFormatedText("INFO_TEXT_NAME_FALSE", GetConvertStr(itmRef.name, "ItemsDescribe.txt"));
	SetNewGroupPicture("INFO_PIC", itmRef.picTexture, "itm" + itmRef.picIndex);
	SetNodeUsing("INFO_PIC", true);
	SetNodeUsing("INFO_TEXT_NAME", true);
//	SetNodeUsing("INFO_TEXT_TYPE", true);
	SetVAligmentFormatedText("INFO_TEXT_NAME");
	SetVAligmentFormatedText("INFO_TEXT_NAME_FALSE");
	SetVAligmentFormatedText("INFO_TEXT_SUBTYPE");
	SetVAligmentFormatedText("INFO_TEXT_DMG");
	SetVAligmentFormatedText("INFO_TEXT_DESC");
	SetVAligmentFormatedText("INFO_TEXT_WEIGHT");
	SetNodeUsing("INFO_TEXT_SUBTYPE", false);
	SetNodeUsing("INFO_TEXT_DMG", false);
	SetNodeUsing("INFO_TEXT_DESC", false);
	SetNodeUsing("INFO_TEXT_WEIGHT", false);
		
	if(CheckAttribute(itmRef, "groupID"))
	{
		switch(itmRef.groupID)
		{
			case BLADE_ITEM_TYPE:
			    if (CheckAttribute(itmRef, "FencingType"))
	    		{
	   	     	    itmRef.FencingTypeName = XI_ConvertString(itmRef.FencingType);
	    	    	SetFormatedText("INFO_TEXT_TYPE", GetAssembledString( LanguageConvertString(idLngFile,"weapon blade type1"), itmRef));
	    		}
	    		else
	    			SetFormatedText("INFO_TEXT_TYPE", "Error");
				
				if(CheckAttribute(itmRef, "subtype"))
		    		describeStr = XI_ConvertString(itmRef.subType);
				
				if(CheckAttribute(itmRef, "dmg_min") && CheckAttribute(itmRef, "dmg_max"))
					describeStr2 = GetAssembledString(LanguageConvertString(idLngFile, "weapon blade parameters1"), itmRef);
			break;
			
			case GUN_ITEM_TYPE:
   	     	    SetFormatedText("INFO_TEXT_TYPE", "Пистолет");
 				if(CheckAttribute(itmRef, "subtype"))
		    		describeStr = LanguageConvertString(idLngFile, itmRef.subtype);
				if(CheckAttribute(itmRef, "dmg_min") && CheckAttribute(itmRef, "dmg_max"))
		    		describeStr2 = GetAssembledString(LanguageConvertString(idLngFile, "weapon gun parameters1"), itmRef);
			break;
			
			case MUSKET_ITEM_TYPE:
				SetFormatedText("INFO_TEXT_TYPE", "Мушкет");
				if(CheckAttribute(itmRef, "subtype"))
			    	describeStr = LanguageConvertString(idLngFile, itmRef.subtype);
				if(CheckAttribute(itmRef, "dmg_min") && CheckAttribute(itmRef, "dmg_max"))
		    		describeStr2 = GetAssembledString(LanguageConvertString(idLngFile, "weapon gun parameters1"), itmRef);
			break;
			
			case SPYGLASS_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Подзорная труба");
				if(CheckAttribute(itmRef, "scope.zoom"))
		    		describeStr = NewStr() + "Дальность обзора " + sti(itmRef.scope.zoom) + "х";
			break;
			
			case CIRASS_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Защита");
				
				makearef(arParam, itmRef.info);
				describeStr = GetAssembledString(LanguageConvertString(idLngFile, "cuirass armor"), arParam);
				describeStr2 = GetAssembledString(LanguageConvertString(idLngFile, "cuirass block"), arParam);
			break;
			
			case SPECIAL_ITEM_TYPE:
				if(HasSubStr(itmRef.id, "purse")) SetFormatedText("INFO_TEXT_TYPE", "Драгоценность");
				else SetFormatedText("INFO_TEXT_TYPE", "Особый предмет");
			   
				if(CheckAttribute(itmRef, "potion.special"))
				{
					if(CheckAttribute(itmRef, "potion.special.sec"))
						describeStr2 = "Действует " + sti(itmRef.potion.special.sec) + " " + GetQuantStringGen("second", sti(itmRef.potion.special.sec));
					if(CheckAttribute(itmRef, "potion.special.time"))
						describeStr2 = "Действует " + sti(itmRef.potion.special.time) + " " + GetQuantStringGen("hour", sti(itmRef.potion.special.time));
				//	if(!CheckAttribute(itmRef, "potion.special.sec") && !CheckAttribute(itmRef, "potion.special.time"))
				//		describeStr = newStr();
					describeStr += LanguageConvertString(idLngFile, "subdescr_"+itmRef.potion.special.effect);
				}	
				
				if(CheckAttribute(itmRef, "subdescribe"))
				    describeStr = NewStr()+ LanguageConvertString(idLngFile, "subdescr_"+itmRef.id);
				
				if(HasSubStr(itmRef.id, "recipe_"))
				{
					describeStr = NewStr() + LanguageConvertString(idLngFile, "Itmname_"+itmRef.result);
					arItem = ItemsFromID(itmRef.result);
					switch(arItem.rare)
					{
						case "common":		nColor1 = argb(255, 255, 255, 255);		break;
						case "rare":		nColor1 = argb(255, 72, 180, 216);		break;
						case "epic":		nColor1 = argb(255, 210, 0, 255);		break;
						case "Legendary":	nColor1 = argb(255, 255, 136, 0);		break;
					}
				}
			break;
			
			case POISON_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Яд");
				makearef(arParam, itmRef.poison);
				if(CheckAttribute(itmRef, "poison.chance"))
					describeStr = GetAssembledString(LanguageConvertString(idLngFile, "poison chance"), arParam);
				if(CheckAttribute(itmRef, "poison.dmgBonus"))
					describeStr = "Бонусный урон +" + makeint(stf(itmRef.poison.dmgBonus)*100 - 100) +"%";
				if(CheckAttribute(itmRef, "poison.InstantKill") && sti(itmRef.poison.InstantKill) == 100)
					describeStr = "Мгновенное убийство";
				if(CheckAttribute(itmRef, "poison.time") && sti(itmRef.poison.time) != -1)
					describeStr2 = "Действует " + sti(itmRef.poison.time) + " " + GetQuantStringGen("hour", sti(itmRef.poison.time));
				if(CheckAttribute(itmRef, "poison.hitsQ"))
					describeStr2 = "Действует " + sti(itmRef.poison.hitsQ) + " " + GetQuantStringGen("attack", sti(itmRef.poison.hitsQ));
			break;
			
			case RATPOISON_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Яд");
				
				if(itmRef.id == "poison4")
				{
				    describeStr = "Избавляет от крыс";
				    describeStr2 = "Действует 30 дней";
				}
			break;
			
			case AMMO_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Боеприпасы");
				describeStr2 = LanguageConvertString(idLngFile, "subdescr2_"+itmRef.id);
				if(describeStr2 == "")
					describeStr = newStr();
				describeStr += LanguageConvertString(idLngFile, "subdescr_"+itmRef.id);
			break;
			
			case TALISMAN_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE", "Талисман");
				string sRole = "any officer";
				if(CheckAttribute(itmRef, "kind"))
					sRole = itmRef.kind;
				describeStr = NewStr() + XI_ConvertString("Can be used by "+sRole);
			break;
		}
	}
	else
	{
		if(HasSubStr(itmRef.id, "potion"))
		{
			if (CheckAttribute(itmRef, "potion"))
			{
				SetFormatedText("INFO_TEXT_TYPE", "Зелье");
				if (CheckAttribute(itmRef, "potion.health"))
				{
					if (stf(itmRef.potion.health) >= 0)
						describeStr += "+" + sti(itmRef.potion.health) + " здоровья";
					else
						describeStr += "" + sti(itmRef.potion.health) + " здоровья";
				}
				if(CheckAttribute(itmRef, "potion.antidote"))
					describeStr2 = "Снимает отравление";
				
				string sTemp;
				if(describeStr == "" || describeStr2 == "")
				{
					if(describeStr != "")
						describeStr = newStr() + describeStr;
					else
					{
						sTemp = newStr() + describeStr2;
						describeStr2 = describeStr;
						describeStr = sTemp;
					}
				}
			}
		}
	    else if(CheckAttribute(itmRef, "jewel"))
		{
			if(itmRef.id == "gold_dublon")
			{
	    		describeStr = NewStr() + "Стоит ровно " + itmRef.price + " песо";
				SetFormatedText("INFO_TEXT_TYPE", "Драгоценность");
			}
			else
				SetFormatedText("INFO_TEXT_TYPE", "Драгоценность");
	    }
		else if(HasSubStr(itmRef.id, "cannabis") || HasSubStr(itmRef.id, "ingredient"))
		{
			SetFormatedText("INFO_TEXT_TYPE", "Ингредиент");
			if(CheckAttribute(itmRef, "special_item"))
			{
				describeStr = NewStr() + "Редкий ингредиент";
				nColor1 = argb(255, 255, 136, 0);
			}
	    }	
		else if(itmRef.id == "lockpick" || HasSubStr(itmRef.id, "key") || itmRef.id == "DutTradeLicence" || HasSubStr(itmRef.id, "Instrument"))
		{
			SetFormatedText("INFO_TEXT_TYPE", "Особый предмет");
			if(CheckAttribute(itmRef, "days"))
				describeStr = "Действует " + itmRef.days + " " + GetQuantStringGen("day", sti(itmRef.days));
			else
				describeStr = LanguageConvertString(idLngFile, "subdescr_"+itmRef.id);
	    }
		else if(HasSubStr(itmRef.id, "mineral"))
		{
			SetFormatedText("INFO_TEXT_TYPE", "Разное");
			switch(itmRef.id)
			{
			    case "mineral4":
		    		describeStr = NewStr() + "-10 везение";
					nColor1 = argb(255, 255,125,125);
		    	break;
				
				case "mineral16":
		    		describeStr = NewStr() + "-10 авторитет";
					nColor1 = argb(255, 255,125,125);
		    	break;
			}
		//	if(describeStr == "" && describeStr2 == "") SetFormatedText("INFO_TEXT_TYPE", NewStr() + "Разное");
	    }
		else SetFormatedText("INFO_TEXT_TYPE", "Нет группы");
	}

	SetFormatedText("INFO_TEXT_SUBTYPE", describeStr);
	SetNodeUsing("INFO_TEXT_SUBTYPE", true);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE", 8,0, nColor1);

	SetFormatedText("INFO_TEXT_DMG", describeStr2);
	SetNodeUsing("INFO_TEXT_DMG", true);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG", 8,0, nColor2);
		
	SetFormatedText("INFO_TEXT_DESC", GetAssembledString(LanguageConvertString(idLngFile, itmRef.describe), itmRef));
	SetNodeUsing("INFO_TEXT_DESC", true);
	
	SetFormatedText("INFO_TEXT_WEIGHT", "Вес: " + FloatToString(stf(itmRef.Weight), 1));
	SetNodeUsing("INFO_TEXT_WEIGHT", true);
	
	CheckButtons();
}

void HideItemInfo()	// прячем информацию
{
	SetFormatedText("INFO_TEXT_NAME", "");
	SetFormatedText("INFO_TEXT_NAME_FALSE", "");
//	SetNodeUsing("INFO_TEXT_NAME", false);
	SetNodeUsing("INFO_TEXT_TYPE", false);
	SetNodeUsing("INFO_PIC", false);
	SetNodeUsing("INFO_TEXT_SUBTYPE", false);
	SetNodeUsing("INFO_TEXT_DMG", false);
	SetNodeUsing("INFO_TEXT_DESC", false);
	SetNodeUsing("INFO_TEXT_WEIGHT", false);
	SetNodeUsing("EQUIP_BUTTON", false);
	SetNodeUsing("EQUIP_BUTTON_GUN", false);
	SetNodeUsing("EQUIP_BUTTON_MUS", false);
	SetNodeUsing("EQUIP_TEXT_GUN", false);
	SetNodeUsing("EQUIP_TEXT_MUS", false);
	SetNodeUsing("REMOVE_BUTTON", false);
	SetNodeUsing("REMOVE_BUTTON_GUN", false);
	SetNodeUsing("REMOVE_BUTTON_MUS", false);
	SetNodeUsing("REMOVE_TEXT_GUN", false);
	SetNodeUsing("REMOVE_TEXT_MUS", false);
	SetNodeUsing("USE_BUTTON", false);
}

void EquipPress()	// экипировать
{
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	
	if (CheckAttribute(itmRef, "groupID") && itmRef.groupID != AMMO_ITEM_TYPE)
	{
		string itmGroup = itmRef.groupID;
	    EquipCharacterByItem(pchar, itmRef.id);
	}
	RefreshItems();
}

void EquipAmmo(string sType)
{
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	if(itmRef.groupID != AMMO_ITEM_TYPE)
		return;
	pchar.bullets.(sType) = itmRef.id;
	LAi_SetCharacterUseBullet(pchar, sType, itmRef.ID);
	LAi_GunSetUnload(pchar, sType);
	log_info("Выбран боеприпас - "+GetConvertStr(itmRef.name, "ItemsDescribe.txt")+"");
	PlaySound("People Fight\reload1.wav");
	RefreshItems();
}

void RemovePress()	// снять
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	if(!CheckAttribute(itmRef, "groupID"))
		return;
	if(itmRef.groupID == AMMO_ITEM_TYPE)
	{
		if(CheckAttribute(pchar, "IsMushketer"))
		{
			DeleteAttribute(pchar, "bullets.musket");
		}
		else
		{
			DeleteAttribute(pchar, "bullets.pistol");
		}
	}
	RemoveCharacterEquip(pchar, itmRef.groupID);
	RefreshItems();
}

void RemoveAmmo(string sType)
{
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	if(itmRef.groupID != AMMO_ITEM_TYPE)
		return;
	DeleteAttribute(pchar, "bullets."+sType);
	LAi_GunSetUnload(pchar, sType);
	RefreshItems();
}

void UsePress()	// использовать
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	if(CheckAttribute(itmRef, "groupID"))
	{
		switch(itmRef.groupID)
		{
			case SPECIAL_ITEM_TYPE:
			    if(HasSubStr(itmRef.id, "recipe_")) // рецепты
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecordInfo("Recipe", itmRef.result);
					SetAlchemyRecipeKnown(itmRef.result);
				}
				if(itmRef.id == "purse1") // кошель
				{
					int irand = (rand(91)+12)
					RemoveItems(pchar, itmRef.id, 1);
					TakeNItems(pchar, "gold_dublon", irand);
					PlaySound("Ambient\Tavern\monetki_taverna_001.wav");
					log_info("Получено "+irand+" дублонов");
				}
				if(CheckAttribute(itmRef, "potion.special") && itmRef.potion.special.effect != "")
				{
					DoCharacterUsedItem(pchar, itmRef.id);
					if(itmRef.potion.special != "potion6" && CheckAttribute(pchar, "SpeciaPotionEffect.count") && sti(pchar.SpeciaPotionEffect.count) > 3)
					{
						ProcessExitCancel();
						return;
					}
					ShowSpecialEffects();
				}
				if (itmRef.id == "Chest_closed" && pchar.id == pchar.id)
                {
                    pchar.questTemp.Lockpicking.ID = itmRef.id;
                    IDoExit(RC_INTERFACE_LOCKPICKING);
                    return;
                }
				RefreshHeroParams();
				ResetItems();
				return;
	    	break;
			case POISON_ITEM_TYPE:
			    DoCharacterUsedPoison(pchar, itmRef.id);
				RefreshHeroParams();
				ResetItems();
				ShowSpecialEffects();
	    	break;
	    	case RATPOISON_ITEM_TYPE:
		        pchar.questTemp.arsenic = true;
	    		RemoveItems(pchar, itmRef.id, 1);
    			Log_TestInfo("Мышьяк у персонажа "+pchar.id+" активирован!");
   				SetRatPoisonTimerFunctionParam(pchar.id + "_RemoveRatPoisonEffectFromCharacter", "RemoveRatPoisonEffectFromCharacter", 0, 0, 30, pchar);
				RefreshHeroParams();
				ResetItems();
	    	break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// НАЗНАЧЕНИЕ ЗЕЛИЙ, ЯДОВ, БОЕПРИПАСОВ
////////////////////////////////////////////////////////////////////////////

void FavouriteChange(string sVar)	// выезд шторки, заполнение таблицы
{
	ActivateEffect(sVar);
	if(canMove)
	{
		if(MoveQueue != "")
			MoveQueue = "";
		if(sFavVariant == "")
		{
			CurTable = "TABLE_FAVOURITE";
			MoveAllNodesToDirSoftly(1, "down", 15, 650, "open");
			MoveAllNodesToDirSoftly(3, "up", 15, 650, "close");
			canMove = false;
			SetNodeUsing("EQUIP_BUTTON", false);
			SetNodeUsing("EQUIP_BUTTON_GUN", false);
			SetNodeUsing("EQUIP_BUTTON_MUS", false);
			SetNodeUsing("EQUIP_TEXT_GUN", false);
			SetNodeUsing("EQUIP_TEXT_MUS", false);
			SetNodeUsing("REMOVE_BUTTON", false);
			SetNodeUsing("REMOVE_BUTTON_GUN", false);
			SetNodeUsing("REMOVE_BUTTON_MUS", false);
			SetNodeUsing("REMOVE_TEXT_GUN", false);
			SetNodeUsing("REMOVE_TEXT_MUS", false);
			SetNodeUsing("USE_BUTTON", false);
			SetNodeUsing("TAKE_BUTTON", false);
			SetNodeUsing("INFO_TEXT_NAME_FALSE", true);
			SetNodeUsing("TITLE_ITEMS_FALSE", true);
			SetNodeUsing("INFO_TEXT_NAME", false);
			SetNodeUsing("TITLE_ITEMS", false);
			sFavVariant = sVar;
		//	XI_WindowShow("FAVOURITE_WINDOW", true);
		//	XI_WindowDisable("FAVOURITE_WINDOW", false);
		//	XI_WindowDisable("MAIN_WINDOW", true);
			FillFavouriteTable();
			SetCurrentNode("TABLE_FAVOURITE");	
			if(CheckAttribute(&GameInterface, "TABLE_FAVOURITE.tr1.UserData.equip") && GameInterface.TABLE_FAVOURITE.tr1.UserData.equip == true)
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"TAKE_BUTTON",0, "#"+XI_ConvertString("Remove that"));
			}
			else
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"TAKE_BUTTON",0, "#"+XI_ConvertString("Equip that"));
			}
		}
		else
		{
			if(sVar == sFavVariant)
				ExitFavouriteMenu();
			else
			{
				sFavVariant = sVar;
				RefreshFavouriteMenu();
			}
		}
	}
	else
	{
		MoveQueue = sVar;
	}
}

void ExitFavouriteMenu()	// уезд шторки, заполнение экипировки
{
	ActivateEffect("");
	if(canMove)
	{
		CurTable = "TABLE_ITEMS";
		if(MoveQueue != "")
			MoveQueue = "";
		SetNodeUsing("INFO_TEXT_FAVOURITE", false);
		SetNodeUsing("INFO_TEXT_FAVOURITE_FALSE", true);
		SetNodeUsing("INFO_TEXT_NAME_FAVOURITE", false);
		SetNodeUsing("INFO_TEXT_NAME_FAVOURITE_FALSE", true);
		MoveAllNodesToDirSoftly(1, "up", 15, 650, "close");
		MoveAllNodesToDirSoftly(3, "down", 15, 650, "open");
		canMove = false;
		SetNodeUsing("EQUIP_BUTTON", false);
		SetNodeUsing("EQUIP_BUTTON_GUN", false);
		SetNodeUsing("EQUIP_BUTTON_MUS", false);
		SetNodeUsing("EQUIP_TEXT_GUN", false);
		SetNodeUsing("EQUIP_TEXT_MUS", false);
		SetNodeUsing("REMOVE_BUTTON", false);
		SetNodeUsing("REMOVE_BUTTON_GUN", false);
		SetNodeUsing("REMOVE_BUTTON_MUS", false);
		SetNodeUsing("REMOVE_TEXT_GUN", false);
		SetNodeUsing("REMOVE_TEXT_MUS", false);
		SetNodeUsing("USE_BUTTON", false);
		SetNodeUsing("TAKE_BUTTON", false);
		sFavVariant = "";
		FillItemsSelected();
	}
	else
	{
		MoveQueue = "inventory";
	}
}

void RefreshFavouriteMenu()
{
	FillItemsSelected();
	FillFavouriteTable();
}

void FillFavouriteTable()	// заполнение таблицы
{
	int n, i;
	string row;
	string sGood;
	aref rootItems, arItem;
	aref  curItem;
	n = 1;
	Table_Clear("TABLE_FAVOURITE", false, true, false);
	
	switch(sFavVariant)
	{
		case "Potion1":			SetFormatedText("INFO_TEXT_FAVOURITE", "Зелья");		SetFormatedText("INFO_TEXT_FAVOURITE_FALSE", "Зелья");			break;
		case "Potion2":			SetFormatedText("INFO_TEXT_FAVOURITE", "Зелья");		SetFormatedText("INFO_TEXT_FAVOURITE_FALSE", "Зелья");			break;
		case "Poison":			SetFormatedText("INFO_TEXT_FAVOURITE", "Яды");			SetFormatedText("INFO_TEXT_FAVOURITE_FALSE", "Яды");			break;
		case "Pistol_ammo":		SetFormatedText("INFO_TEXT_FAVOURITE", "Боеприпасы");	SetFormatedText("INFO_TEXT_FAVOURITE_FALSE", "Боеприпасы");		break;
		case "Mushket_ammo":	SetFormatedText("INFO_TEXT_FAVOURITE", "Боеприпасы");	SetFormatedText("INFO_TEXT_FAVOURITE_FALSE", "Боеприпасы");		break;
	}
	
	// Заполним вещами от нас
	makearef(rootItems, pchar.Items);
	bool ok = false;
	
	if(sFavVariant == "Potion1" && CheckAttribute(pchar, "GenQuest.Potion_choice.v1") && Items_FindItem(pchar.GenQuest.Potion_choice.v1, &arItem) >= 0 )
	{
		sGood = arItem.id;
		if (GetCharacterItem(pchar, sGood) > 0)
			ok = true;
	}
	if(sFavVariant == "Potion2" && CheckAttribute(pchar, "GenQuest.Potion_choice.v2") && Items_FindItem(pchar.GenQuest.Potion_choice.v2, &arItem) >= 0 )
	{
		sGood = arItem.id;
		if (GetCharacterItem(pchar, sGood) > 0)
			ok = true;
	}
	if(sFavVariant == "Poison" && CheckAttribute(pchar, "GenQuest.Poison_choise") && Items_FindItem(pchar.GenQuest.Poison_choise, &arItem) >= 0 )
	{
		sGood = arItem.id;
		if (GetCharacterItem(pchar, sGood) > 0)
			ok = true;
	}
	if(sFavVariant == "Pistol_ammo" && CheckAttribute(pchar, "bullets.pistol") && Items_FindItem(pchar.bullets.pistol, &arItem) >= 0 )
	{
		sGood = arItem.id;
		if (GetCharacterItem(pchar, sGood) > 0)
			ok = true;
	}
	if(sFavVariant == "Mushket_ammo" && CheckAttribute(pchar, "bullets.musket") && Items_FindItem(pchar.bullets.musket, &arItem) >= 0 )
	{
		sGood = arItem.id;
		if (GetCharacterItem(pchar, sGood) > 0)
			ok = true;
	}
	
	if(ok)
	{
		row = "tr" + n;
		GameInterface.TABLE_FAVOURITE.(row).index = GetItemIndex(arItem.id);
		GameInterface.TABLE_FAVOURITE.(row).UserData.equip = true;
		GameInterface.TABLE_FAVOURITE.(row).td1.icon.group = arItem.picTexture;
		GameInterface.TABLE_FAVOURITE.(row).td1.icon.image = "itm" + arItem.picIndex;
		GameInterface.TABLE_FAVOURITE.(row).td1.icon.offset = "2,4";
		GameInterface.TABLE_FAVOURITE.(row).td1.icon.width = 32;
		GameInterface.TABLE_FAVOURITE.(row).td1.icon.height = 32;
		GameInterface.TABLE_FAVOURITE.(row).td2.align = "center";
		GameInterface.TABLE_FAVOURITE.(row).td2.valign = "center";
		GameInterface.TABLE_FAVOURITE.(row).td2.str = LanguageConvertString(idLngFile, arItem.name);
		GameInterface.TABLE_FAVOURITE.(row).td2.scale = 1;
		GameInterface.TABLE_FAVOURITE.(row).td3.str   = GetCharacterItem(pchar, sGood);
		GameInterface.TABLE_FAVOURITE.(row).td3.scale = 1;
		GameInterface.TABLE_FAVOURITE.(row).td3.align = "center";
		GameInterface.TABLE_FAVOURITE.(row).td3.valign = "center";
		GameInterface.TABLE_FAVOURITE.(row).td3.textoffset = "0,0";
		n++;
	}
	
    for (i = 0; i < GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 )
		{
			ok = true;
			row = "tr" + n;
			sGood = arItem.id;
			switch(sFavVariant)
			{
				case "Potion1":			if(!CheckAttribute(arItem, "potion")) ok = false;		break;
				case "Potion2":			if(!CheckAttribute(arItem, "potion")) ok = false;		break;
				case "Poison":			if(!CheckAttribute(arItem, "groupID") || arItem.groupID != POISON_ITEM_TYPE) ok = false;	break;
				case "Pistol_ammo":		if(!CheckAttribute(&arItem, "groupID") || arItem.groupID != AMMO_ITEM_TYPE) ok = false;		break;
				case "Mushket_ammo":	if(!CheckAttribute(&arItem, "groupID") || arItem.groupID != AMMO_ITEM_TYPE) ok = false;		break;
			}
			if(!ok) continue;
			
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v1") && pchar.GenQuest.Potion_choice.v1 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v1") && pchar.GenQuest.Potion_choice.v2 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v2") && pchar.GenQuest.Potion_choice.v2 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Potion_choice.v2") && pchar.GenQuest.Potion_choice.v1 == arItem.id) continue;
			if(CheckAttribute(pchar, "GenQuest.Poison_choise") && pchar.GenQuest.Poison_choise == arItem.id) continue;
			if(sFavVariant == "Pistol_ammo" && CheckAttribute(pchar, "bullets.pistol") && pchar.bullets.pistol == arItem.id) continue;
			if(sFavVariant == "Mushket_ammo" && CheckAttribute(pchar, "bullets.musket") && pchar.bullets.musket == arItem.id) continue;
			
			if (GetCharacterItem(pchar, sGood) > 0)
			{
				if(sFavVariant == "Pistol_ammo" || sFavVariant == "Mushket_ammo")
				{
					string sGun;
					if(sFavVariant == "Pistol_ammo")
					{
						sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
						if(sGun == "pistol2" && arItem.id == "gunechin")
							continue;
					}
					else
					{
						sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
					}
					aref arGun;
					Items_FindItem(sGun, &arGun);
					if(arGun.ammo_type != arItem.ammo_type)
						continue;
				}
				GameInterface.TABLE_FAVOURITE.(row).index = GetItemIndex(arItem.id);
				GameInterface.TABLE_FAVOURITE.(row).UserData.equip = false;
				
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.offset = "2,4";
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.width = 32;
				GameInterface.TABLE_FAVOURITE.(row).td1.icon.height = 32;
				GameInterface.TABLE_FAVOURITE.(row).td2.align = "center";
				GameInterface.TABLE_FAVOURITE.(row).td2.valign = "center";
				GameInterface.TABLE_FAVOURITE.(row).td2.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_FAVOURITE.(row).td2.scale = 1;
				
				GameInterface.TABLE_FAVOURITE.(row).td3.str   = GetCharacterItem(pchar, sGood);
				GameInterface.TABLE_FAVOURITE.(row).td3.scale = 1;
				GameInterface.TABLE_FAVOURITE.(row).td3.align = "center";
				GameInterface.TABLE_FAVOURITE.(row).td3.valign = "center";
				GameInterface.TABLE_FAVOURITE.(row).td3.textoffset = "0,0";
				
				n++;
			}
		}
    }
	GameInterface.TABLE_FAVOURITE.select = 1;
	GameInterface.TABLE_FAVOURITE.top = 0;
	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_FAVOURITE", 3);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_FAVOURITE",0.0);
	
	CurTable = "TABLE_FAVOURITE";
	CurRow = "tr1";
    
	Table_UpdateWindow("TABLE_FAVOURITE");

	
	if(!CheckAttribute(&GameInterface, "TABLE_FAVOURITE.tr1.index") || GameInterface.TABLE_FAVOURITE.tr1.index <= 0)
	{
		SetSelectable("TAKE_BUTTON",false);
	}
	else
	{
		SetSelectable("TAKE_BUTTON",true);
	}
	
	if(!CheckAttribute(&GameInterface, CurTable+"."+CurRow+".index") || sti(GameInterface.(CurTable).(CurRow).index) == 0)
		HideFavouriteInfo();
	else
		SetFavouriteInfo();
}

void FavouriteEquipPress()	// назначение предмета, закрытие шторки
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	
	if (sFavVariant != "")
	{
		switch (sFavVariant)
		{
	    	case "Potion1":
				if(CheckAttribute(pchar,"GenQuest.Potion_choice.v1") && pchar.GenQuest.Potion_choice.v1 == itmRef.id)
				{
					DeleteAttribute(pchar,"GenQuest.Potion_choice.v1");
				}
				else
				{
					pchar.GenQuest.Potion_choice.v1 = itmRef.id;
				}
			break;
			
			case "Potion2":
				if(CheckAttribute(pchar,"GenQuest.Potion_choice.v2") && pchar.GenQuest.Potion_choice.v2 == itmRef.id)
				{
					DeleteAttribute(pchar,"GenQuest.Potion_choice.v2");
				}
				else
				{
					pchar.GenQuest.Potion_choice.v2 = itmRef.id;
				}
			break;
			
			case "Poison":
				if(CheckAttribute(pchar,"GenQuest.Poison_choise") && pchar.GenQuest.Poison_choise == itmRef.id)
				{
					DeleteAttribute(pchar,"GenQuest.Poison_choise");
				}
				else
				{
					pchar.GenQuest.Poison_choise = itmRef.id;
				}
			break;
			
			case "Pistol_ammo":
				if(CheckAttribute(pchar,"bullets.pistol") && pchar.bullets.pistol == itmRef.id)
				{
					DeleteAttribute(pchar,"bullets.pistol");
				}
				else
				{
					pchar.bullets.pistol = itmRef.id;
				}
			break;
			
			case "Mushket_ammo":
				if(CheckAttribute(pchar,"bullets.musket") && pchar.bullets.musket == itmRef.id)
				{
					DeleteAttribute(pchar,"bullets.musket");
				}
				else
				{
					pchar.bullets.musket = itmRef.id;
				}
			break;
		}
		FillFavouriteTable();
	//	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"TAKE_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	ExitFavouriteMenu();
}

void SetFavouriteInfo()	// отображение информации
{
	if(CurTable != "TABLE_FAVOURITE") return;
	
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	int nColor1 = argb(255,255,255,255);
	int nColor2 = argb(255,255,255,255);
	string describeStr, describeStr2;
	describeStr = "";
	describeStr2 = "";
	ref arItem, itmRef;
	makeref(itmRef, Items[iGoodIndex]);
	aref arParam;
	
	SetFormatedText("INFO_TEXT_NAME_FAVOURITE", GetConvertStr(itmRef.name, "ItemsDescribe.txt"));
	SetFormatedText("INFO_TEXT_NAME_FAVOURITE_FALSE", GetConvertStr(itmRef.name, "ItemsDescribe.txt"));
	SetNewGroupPicture("INFO_PIC_FAVOURITE", itmRef.picTexture, "itm" + itmRef.picIndex);
	SetNodeUsing("INFO_PIC_FAVOURITE", true);
	SetNodeUsing("INFO_TEXT_TYPE_FAVOURITE", true);
	SetVAligmentFormatedText("INFO_TEXT_NAME_FAVOURITE");
	SetVAligmentFormatedText("INFO_TEXT_NAME_FAVOURITE_FALSE");
	SetVAligmentFormatedText("INFO_TEXT_SUBTYPE_FAVOURITE");
	SetVAligmentFormatedText("INFO_TEXT_DMG_FAVOURITE");
	SetVAligmentFormatedText("INFO_TEXT_DESC_FAVOURITE");
	SetNodeUsing("INFO_TEXT_SUBTYPE_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_DMG_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_DESC_FAVOURITE", false);
		
	if(CheckAttribute(itmRef, "groupID"))
	{
		switch(itmRef.groupID)
		{
			case SPECIAL_ITEM_TYPE:
				SetFormatedText("INFO_TEXT_TYPE_FAVOURITE", "Особый предмет");
			   
				if(CheckAttribute(itmRef, "potion.special"))
				{
					if(CheckAttribute(itmRef, "potion.special.sec"))
						describeStr2 = "Действует " + sti(itmRef.potion.special.sec) + " " + GetQuantStringGen("second", sti(itmRef.potion.special.sec));
					if(CheckAttribute(itmRef, "potion.special.time"))
						describeStr2 = "Действует " + sti(itmRef.potion.special.time) + " " + GetQuantStringGen("hour", sti(itmRef.potion.special.time));
					describeStr += LanguageConvertString(idLngFile, "subdescr_"+itmRef.potion.special.effect);
				}	
				
				if(CheckAttribute(itmRef, "subdescribe"))
				    describeStr = NewStr()+ LanguageConvertString(idLngFile, "subdescr_"+itmRef.id);
			break;
			
			case POISON_ITEM_TYPE:
			    SetFormatedText("INFO_TEXT_TYPE_FAVOURITE", "Яд");
				makearef(arParam, itmRef.poison);
				if(CheckAttribute(itmRef, "poison.chance"))
					describeStr = GetAssembledString(LanguageConvertString(idLngFile, "poison chance"), arParam);
				if(CheckAttribute(itmRef, "poison.dmgBonus"))
					describeStr = "Бонусный урон +" + makeint(stf(itmRef.poison.dmgBonus)*100 - 100) +"%";
				if(CheckAttribute(itmRef, "poison.InstantKill") && sti(itmRef.poison.InstantKill) == 100)
					describeStr = "Мгновенное убийство";
				if(CheckAttribute(itmRef, "poison.time") && sti(itmRef.poison.time) != -1)
					describeStr2 = "Действует " + sti(itmRef.poison.time) + " " + GetQuantStringGen("hour", sti(itmRef.poison.time));
				if(CheckAttribute(itmRef, "poison.hitsQ"))
					describeStr2 = "Действует " + sti(itmRef.poison.hitsQ) + " " + GetQuantStringGen("attack", sti(itmRef.poison.hitsQ));
			break;
			
			case AMMO_ITEM_TYPE:
				SetFormatedText("INFO_TEXT_TYPE_FAVOURITE", "Боеприпас");
				describeStr2 = LanguageConvertString(idLngFile, "subdescr2_"+itmRef.id);
				if(describeStr2 == "")
					describeStr = newStr();
				describeStr += LanguageConvertString(idLngFile, "subdescr_"+itmRef.id);
			break;
		}
	}
	else
	{
		if(HasSubStr(itmRef.id, "potion"))
		{
			if (CheckAttribute(itmRef, "potion"))
			{
				SetFormatedText("INFO_TEXT_TYPE_FAVOURITE", "Зелье");
				if (CheckAttribute(itmRef, "potion.health"))
				{
					if (stf(itmRef.potion.health) >= 0)
						describeStr += "+" + sti(itmRef.potion.health) + " здоровья";
					else
						describeStr += "" + sti(itmRef.potion.health) + " здоровья";
				}
				if(CheckAttribute(itmRef, "potion.antidote"))
					describeStr2 = "Снимает отравление";
				
				string sTemp;
				if(describeStr == "" || describeStr2 == "")
				{
					if(describeStr != "")
						describeStr = newStr() + describeStr;
					else
					{
						sTemp = newStr() + describeStr2;
						describeStr2 = describeStr;
						describeStr = sTemp;
					}
				}
			}
		}
	}

	SetFormatedText("INFO_TEXT_SUBTYPE_FAVOURITE", describeStr);
	SetNodeUsing("INFO_TEXT_SUBTYPE_FAVOURITE", true);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_SUBTYPE_FAVOURITE", 8,0, nColor1);

	SetFormatedText("INFO_TEXT_DMG_FAVOURITE", describeStr2);
	SetNodeUsing("INFO_TEXT_DMG_FAVOURITE", true);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT_DMG_FAVOURITE", 8,0, nColor2);
		
	SetFormatedText("INFO_TEXT_DESC_FAVOURITE", GetAssembledString(LanguageConvertString(idLngFile, itmRef.describe), itmRef));
	SetNodeUsing("INFO_TEXT_DESC_FAVOURITE", true);
	
	SetNodeUsing("TAKE_BUTTON", true);
}

void HideFavouriteInfo()
{
	SetFormatedText("INFO_TEXT_NAME_FAVOURITE", "");
	SetFormatedText("INFO_TEXT_NAME_FAVOURITE_FALSE", "");
	SetNodeUsing("INFO_TEXT_TYPE_FAVOURITE", false);
	SetNodeUsing("INFO_PIC_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_SUBTYPE_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_DMG_FAVOURITE", false);
	SetNodeUsing("INFO_TEXT_DESC_FAVOURITE", false);
	SetNodeUsing("TAKE_BUTTON", false);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ОКНО ЭФФЕКТОВ
////////////////////////////////////////////////////////////////////////////

void OpenEffects()	// открываем окно эффектов
{
	if(canMove)
	{
		MoveAllNodesToDirSoftly(2, "left", 10, 75, "open");
		canMove = false;
		ShowSpecialEffects();
	}
}

void CloseEffects()	// закрываем окно эффектов
{
	if(canMove)
	{
		MoveAllNodesToDirSoftly(2, "right", 10, 75, "close");
		canMove = false;
	}
}

void ShowSpecialEffects()	// отображение эффектов
{
	SetNodeUsing("EFFECT_ICON1", false);
	SetNodeUsing("EFFECT_ICON2", false);
	SetNodeUsing("EFFECT_ICON3", false);
	SetNodeUsing("EFFECT_ICON4", false);
	
	aref arEffects, arEffect, arItem;
	string sEffect, sNode, sGroup, sPicture, sItem;
	string weaponID = GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE);
    aref weapon;
    Items_FindItem(weaponID, &weapon);
	int m = 1;
	if(CheckAttribute(weapon, "isPoisoned"))
	{
		string poisonID = weapon.isPoisoned.poison;
		Items_FindItem(poisonID, &arItem);
		sNode = "EFFECT_ICON1";
		sGroup = arItem.picTexture;
		sPicture = "itm" + arItem.picIndex;
		SetNodeUsing(sNode, true);
		SetNewGroupPicture(sNode, sGroup, sPicture);
		effects[0] = poisonID;
		m++;
	}
	
	makearef(arEffects, pchar.SpeciaPotionEffect);
	int n = GetAttributesNum(arEffects);
	for(int i=0; i<n; i++)
	{
		arEffect = GetAttributeN(arEffects, i);
		sEffect = GetAttributeName(arEffect);
		sItem = "potion"+sEffect;
		if(Items_FindItem(sItem, &arItem) < 0)
			continue;
		sNode = "EFFECT_ICON"+(m);
		sGroup = arItem.picTexture;
		sPicture = "itm" + arItem.picIndex;
		SetNodeUsing(sNode, true);
		SetNewGroupPicture(sNode, sGroup, sPicture);
		effects[m] = sEffect;
		m++;
	}
}

void ShowEffectInfo(int iEff)	// инфо об эффекте
{
	if(iEff == 1 && ShowPoisonInfo())
	{
		return;
	}
	string sEffect = effects[iEff];
	string qName = "RemoveSpecialPotionEffectFromChar_"+pchar.id+"_"+sEffect;
	aref arItem;
	string sItem = "potion"+sEffect;
	Items_FindItem(sItem, &arItem);
	int iMinutes = sti(arItem.potion.special.time)*60 - GetQuestPastMinutesParam(qName);
	int iHours = iMinutes/60;
	int x1,y1,x2,y2;
	x1 = 736;
	x2 = 886;
	switch(iEff)
	{
		case 1:		y1 = 230; y2 = 290;		break;
		case 2:		y1 = 283; y2 = 343;		break;
		case 3:		y1 = 336; y2 = 396;		break;
		case 4:		y1 = 389; y2 = 449;		break;
	}
	string sInfo = ColorTextLine(GetConvertStr("itmname_potion"+sEffect, "ItemsDescribe.txt"), "gold");
	int iLen = (strlen(sInfo)+1)/2;
	if(iLen > 13)
		x1 -= 30;
	if(iLen > 18)
		x1 -= 30;
	if(iLen > 23)
		x1 -= 30;
	if(iLen > 28)
		x1 -= 30;
	sInfo += "\nвремя действия:\n";
	if(iMinutes < 60)
		sInfo += "меньше часа";
	else
	{
		sInfo += iHours + " " + GetQuantStringGen("hour", iHours);
	}
	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"EFFECT_INFO_FRAME", -1, 4, makeint(x1+fOffsetX), makeint(y1+fOffsetY), makeint(x2+fOffsetX), makeint(y2+fOffsetY));
	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"EFFECT_INFO_TEXT", -1, 4, makeint(x1+fOffsetX), makeint(y1+fOffsetY)+5, makeint(x2+fOffsetX), makeint(y2+fOffsetY));
	SetFormatedText("EFFECT_INFO_TEXT", sInfo);
	SetNodeUsing("EFFECT_INFO_FRAME", true);
	SetNodeUsing("EFFECT_INFO_TEXT", true);
}

bool ShowPoisonInfo()	// инфо о яде
{
	aref weapon, poison;
	string weaponID = GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE);
	Items_FindItem(weaponID, &weapon);
	if(!CheckAttribute(weapon, "isPoisoned"))
		return false;
	
	string poisonID = effects[0];
	Items_FindItem(poisonID, &poison);
	string qName, sTag;
	string sHits = "";
	string sTime = "";
	int iTmp, iMinutes, iHours;
	if(CheckAttribute(weapon, "isPoisoned.poisonQunatity"))
	{
		iTmp = sti(weapon.isPoisoned.poisonQunatity);
		if(iTmp%100 >= 11 && iTmp%100 <= 19)
			sHits = "\nосталось "+iTmp+" ударов";
		else
		{
			if(iTmp%10 == 1)
				sHits = "\nостался "+iTmp+" удар";
			else
			{
				if(iTmp%10 >=2 && iTmp%10 <= 4)
					sHits = "\nосталось "+iTmp+" удара";
				else
					sHits = "\nосталось "+iTmp+" ударов";
			}
		}
	}
	if(CheckAttribute(poison, "poison.time") && sti(poison.poison.time) != -1)
	{
		qName = "RemovePoisonEffectFromCharBlade_"+pchar.id;
		iMinutes = sti(poison.poison.time)*60 - GetQuestPastMinutesParam(qName);
		iHours = iMinutes/60;
		sTime = "\nвремя действия:\n";
		if(iMinutes < 60)
			sTime += "меньше часа";
		else
		{
			if(iHours%100 >= 11 && iHours%100 <= 19)
				sTime += iHours + " часов";
			else
			{
				if(iHours%10 == 1)
					sTime += iHours + " час";
				else
				{
					if(iHours%10 >=2 && iHours%10 <= 4)
						sTime += iHours + " часа";
					else
						sTime += iHours + " часов";
				}
			}
		}
	}
	
	int x1,y1,x2,y2;
	x1 = 736;
	x2 = 886;
	y1 = 270; 
	y2 = 290;	
	if(sHits != "")
		y1 -= 20;
	if(sTime != "")
		y1 -= 40;
	
	string sInfo = ColorTextLine(GetConvertStr(poison.name, "ItemsDescribe.txt"), "green");
	int iLen = (strlen(sInfo)+1)/2;
	if(iLen > 13)
		x1 -= 30;
	if(iLen > 18)
		x1 -= 30;
	if(iLen > 23)
		x1 -= 30;
	if(iLen > 28)
		x1 -= 30;
	
	sInfo += sHits + sTime;
	
	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"EFFECT_INFO_FRAME", -1, 4, makeint(x1+fOffsetX), makeint(y1+fOffsetY), makeint(x2+fOffsetX), makeint(y2+fOffsetY));
	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"EFFECT_INFO_TEXT", -1, 4, makeint(x1+fOffsetX), makeint(y1+fOffsetY)+5, makeint(x2+fOffsetX), makeint(y2+fOffsetY));
	SetFormatedText("EFFECT_INFO_TEXT", sInfo);
	SetNodeUsing("EFFECT_INFO_FRAME", true);
	SetNodeUsing("EFFECT_INFO_TEXT", true);
}

void HideEffectInfo(int iEff)	// спрятать инфо
{
	SetNodeUsing("EFFECT_INFO_FRAME", false);
	SetNodeUsing("EFFECT_INFO_TEXT", false);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
////////////////////////////////////////////////////////////////////////////

void UpdateRareGlow()	// обновление свечения
{
	if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
		SetNodeUsing("GLOW_BLADE", false);
	if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "")
		SetNodeUsing("GLOW_PISTOL", false);
	if(GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) == "")
		SetNodeUsing("GLOW_MUSHKET", false);
	if(GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE) == "")
		SetNodeUsing("GLOW_SPYGLASS", false);
	if(GetCharacterEquipByGroup(pchar, CIRASS_ITEM_TYPE) == "")
		SetNodeUsing("GLOW_CUIRASS", false);
	if(GetCharacterEquipByGroup(pchar, TALISMAN_ITEM_TYPE) == "")
		SetNodeUsing("GLOW_TALISMAN", false);
	
	// evganat - заглушка под шляпы
	SetNodeUsing("GLOW_HAT", false);	// TODO: включить шляпы
}

void SetRareGlow(string sNode, string rarity)	// выставление свечения
{
	switch(rarity)
	{
		case "common":		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,sNode, 0, "interfaces\light.tga");		break;
		case "rare":		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,sNode, 0, "interfaces\lightR.tga");		break;
		case "epic":		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,sNode, 0, "interfaces\lightE.tga");		break;
		case "Legendary":	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,sNode, 0, "interfaces\lightL.tga");		break;
	}
}

// снятие экипировки по двойному клику -->
void RemovePistol()
{
	DeleteAttribute(pchar, "bullets.pistol");
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	RefreshItems();
}

void RemoveMushket()
{
	DeleteAttribute(pchar, "bullets.musket");
	RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
	RefreshItems();
}

void RemoveSpyglass()
{
	RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
	RefreshItems();
}

void RemoveCuirass()
{
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RefreshItems();
}

void RemoveTalisman()
{
	RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
	RefreshItems();
}

void RemovePotion1()
{
	DeleteAttribute(pchar, "GenQuest.Potion_choice.v1");
	RefreshItems();
}

void RemovePotion2()
{
	DeleteAttribute(pchar, "GenQuest.Potion_choice.v2");
	RefreshItems();
}

void RemovePoison()
{
	DeleteAttribute(pchar, "GenQuest.Poison_choise");
	RefreshItems();
}
// снятие экипировки <--

void SetEquipDefaultPicture(string sType)	// выставление дефолтной картинки для экипировки
{
	string sNode = "ICON_"+sType;
	if(sType == "potion1" || sType == "potion2")
		sType = "potion";
	if(sType == "pistol_ammo")
		sType = "pistol";
	if(sType == "mushket_ammo")
		sType = "mushket";
	SetNewGroupPicture(sNode, "EQUIPMENT", sType);
}

void SetSortOffPictures()	// выставление выключенных картинок для сортировки
{
	SetNewGroupPicture("TABBTN_1", "TABS_NEW", "All_off");
	SetNewGroupPicture("TABBTN_2", "TABS_NEW", "Gear_off");
	SetNewGroupPicture("TABBTN_3", "TABS_NEW", "Potion_off");
	SetNewGroupPicture("TABBTN_4", "TABS_NEW", "Ingredients_off");
	SetNewGroupPicture("TABBTN_5", "TABS_NEW", "Quest_off");
	SetNewGroupPicture("TABBTN_6", "TABS_NEW", "Other_off");
}

void ActivateEffect(string sType)	// свистоперделки при выделении ноды
{
	if(sType == "")
	{
		SetNodeUsing("EFFECT_EQUIP", false);
		SetNodeUsing("VIDEOFRAME_EQUIP", false);
		return;
	}
	int x1,y1,x2,y2;
	switch(sType)
	{
		case "blade":
			x1=590;	y1=184; x2=652; y2=246;
		break;
		case "pistol":
			x1=615;	y1=267; x2=677; y2=329;
		break;
		case "spyglass":
			x1=778;	y1=261; x2=840; y2=323;
		break;
		case "cuirass":
			x1=700;	y1=198; x2=762; y2=260;
		break;
		case "talisman":
			x1=778;	y1=128; x2=840; y2=190;
		break;
		case "mushket":
			x1=667;	y1=341; x2=729; y2=403;
		break;
		case "hat":
			x1=615;	y1=96; x2=677; y2=158;
		break;
		case "potion1":
			x1=652;	y1=444; x2=700; y2=492;
		break;
		case "potion2":
			x1=706;	y1=444; x2=754; y2=492;
		break;
		case "poison":
			x1=760;	y1=444; x2=808; y2=492;
		break;
		case "pistol_ammo":
			x1=678;	y1=294; x2=713; y2=329;
		break;
		case "mushket_ammo":
			x1=730;	y1=368; x2=765; y2=403;
		break;
	}
	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"VIDEOFRAME_EQUIP", -1, 4, makeint(x1-3+fOffsetX), makeint(y1-3+fOffsetY), makeint(x2+3+fOffsetX), makeint(y2+3+fOffsetY));
	SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"EFFECT_EQUIP", -1, 4, makeint(x1+fOffsetX)-33, makeint(y1+fOffsetY), makeint(x2+fOffsetX), makeint(y2+fOffsetY));
	SetNodeUsing("EFFECT_EQUIP", true);
	SetNodeUsing("VIDEOFRAME_EQUIP", true);
}

void CheckButtons()	// проверка доступности кнопок "экипировать", "снять" и "использовать"
{
	SetNodeUsing("EQUIP_BUTTON", false);
	SetNodeUsing("EQUIP_BUTTON_GUN", false);
	SetNodeUsing("EQUIP_BUTTON_MUS", false);
	SetNodeUsing("EQUIP_TEXT_GUN", false);
	SetNodeUsing("EQUIP_TEXT_MUS", false);
	SetNodeUsing("REMOVE_BUTTON", false);
	SetNodeUsing("REMOVE_BUTTON_GUN", false);
	SetNodeUsing("REMOVE_BUTTON_MUS", false);
	SetNodeUsing("REMOVE_TEXT_GUN", false);
	SetNodeUsing("REMOVE_TEXT_MUS", false);
	SetNodeUsing("USE_BUTTON", false);
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef;
	makeref(itmRef, Items[iGoodIndex]);
	if(IsEquipCharacterByItem(pchar, itmRef.id))	// все экипированные, кроме клинка
	{
		if(CheckAttribute(itmRef, "groupID") && itmRef.groupID == BLADE_ITEM_TYPE)
			return;
		SetNodeUsing("REMOVE_BUTTON", true);
		return;
	}
	if(CheckAttribute(itmRef, "groupID") && IsCanEquiping(pchar, itmRef.groupID))
	{
		switch(itmRef.groupID)
		{
			case BLADE_ITEM_TYPE:
				SetNodeUsing("EQUIP_BUTTON", true);
				return;
			break;
			case TALISMAN_ITEM_TYPE:
				SetNodeUsing("EQUIP_BUTTON", true);
				return;
			break;
			case SPYGLASS_ITEM_TYPE:
				SetNodeUsing("EQUIP_BUTTON", true);
				return;
			break;
			case HAT_ITEM_TYPE:
				SetNodeUsing("EQUIP_BUTTON", true);
				return;
			break;
			case SPECIAL_ITEM_TYPE:
				if(HasSubStr(itmRef.id, "recipe_") && isMultiObjectKnown(itmRef.result)) return;
				if(CheckAttribute(itmRef, "potion.special") && itmRef.potion.special.effect != "")
				{
					if(CheckAttribute(pchar, "SpeciaPotionEffect."+itmRef.potion.special.effect)) return;
				}
				SetNodeUsing("USE_BUTTON", true);
				return;
			break;
			case POISON_ITEM_TYPE:
				string sBlade = GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE);
				aref arBlade;
				Items_FindItem(sBlade, &arBlade);
				if(!CheckAttribute(arBlade, "isPoisoned"))
				{
					SetNodeUsing("USE_BUTTON", true);
					return;
				}
			break;
			case RATPOISON_ITEM_TYPE:
				if(!CheckAttribute(pchar, "questTemp.arsenic"))
				{
					SetNodeUsing("USE_BUTTON", true);
					return;
				}
			break;
			case AMMO_ITEM_TYPE:
				if (itmRef.ID == "GunPowder") return;
				bool bGun = false;
				bool bMus = false;
				string sGunNodeTag, sMusNodeTag;
				int gunx1, gunx2, musx1, musx2;
				gunx1 = makeint(194+fOffsetX);
				gunx2 = makeint(347+fOffsetX);
				musx1 = makeint(375+fOffsetX);
				musx2 = makeint(528+fOffsetX);
				string sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
				if(sGun != "")
				{
					aref arGun;
					Items_FindItem(sGun, &arGun);
					if(itmRef.ammo_type == arGun.ammo_type)	// тип боеприпаса подходит
					{
						if(itmRef.ID != "gunechin" || sGun != "pistol2")
						{
							if(CheckAttribute(pchar, "bullets.pistol") && pchar.bullets.pistol == itmRef.id)
							{
								SetNodeUsing("REMOVE_BUTTON_GUN", true);
								SetNodeUsing("REMOVE_TEXT_GUN", true);
								sGunNodeTag = "REMOVE";
							}
							else
							{
								SetNodeUsing("EQUIP_BUTTON_GUN", true);
								SetNodeUsing("EQUIP_TEXT_GUN", true);
								sGunNodeTag = "EQUIP";
							}
							bGun = true;
						}
					}
				}
				string sMus = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
				if(sMus != "")
				{
					aref arMus;
					Items_FindItem(sMus, &arMus);
					if(itmRef.ammo_type == arMus.ammo_type)	// тип боеприпаса подходит
					{
						if(CheckAttribute(pchar, "bullets.musket") && pchar.bullets.musket == itmRef.id)
						{
							SetNodeUsing("REMOVE_BUTTON_MUS", true);
							SetNodeUsing("REMOVE_TEXT_MUS", true);
							sMusNodeTag = "REMOVE";
						}
						else
						{
							SetNodeUsing("EQUIP_BUTTON_MUS", true);
							SetNodeUsing("EQUIP_TEXT_MUS", true);
							sMusNodeTag = "EQUIP";
						}
						bMus = true;
					}
				}
				if(bGun || bMus)
				{
					if(!bMus)
					{
						gunx1 = makeint(274+fOffsetX);
						gunx2 = makeint(427+fOffsetX);
					}
					if(!bGun)
					{
						musx1 = makeint(274+fOffsetX);
						musx2 = makeint(427+fOffsetX);
					}
					SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, sGunNodeTag+"_BUTTON_GUN", -1, 4, gunx1, 522, gunx2, 552);
					SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, sGunNodeTag+"_TEXT_GUN", -1, 4, gunx1 + 40, 522, gunx2 - 40, 552);
					SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, sMusNodeTag+"_BUTTON_MUS", -1, 4, musx1, 522, musx2, 552);
					SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, sMusNodeTag+"_TEXT_MUS", -1, 4, musx1 + 40, 522, musx2 - 40, 552);
				}
			break;
			case GUN_ITEM_TYPE:
				if(!CheckAttribute(itmRef,"chargeQ")) return;
				int chrgQ = sti(itmRef.chargeQ);
				if(chrgQ >= 2 && !IsCharacterPerkOn(pchar,"Musketeer")) return;
				SetNodeUsing("EQUIP_BUTTON", true);
			break;
			case MUSKET_ITEM_TYPE:
				if(!CheckAttribute(itmRef,"chargeQ")) return;
				if(IsCharacterPerkOn(pchar,"Breter"))// && CanEquipMushketOnLocation(PChar.Location))
					SetNodeUsing("EQUIP_BUTTON", true);
			break;
			case CIRASS_ITEM_TYPE:
				if(sti(itmRef.Clothes) == 0) return;
				if(itmRef.needPerk != "" && !IsCharacterPerkOn(pchar, itmRef.needPerk)) return;
				SetNodeUsing("EQUIP_BUTTON", true);
				return;
			break;
		}
	}
	else
	{
		if(HasSubStr(itmRef.id, "potion"))
			SetNodeUsing("USE_BUTTON", true);
	}
}

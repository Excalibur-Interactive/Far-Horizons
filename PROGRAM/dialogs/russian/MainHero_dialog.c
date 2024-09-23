void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sMusket, sBullet, attrL;
	aref rType;
    
	int iST;
	
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индех в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Если вы читаете эти строки, значит, где-то явный баг в коде";
			Link.l1 = "Выход";
			Link.l1.go = "exit";
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("Жаркая была схватка... Теперь можно позвать разбежавшихся трусов.", "Ха! Это было просто. А эти сухопутные крысы разбежались!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Хм... Что бы мне сейчас хотелось сделать?", "Чем бы заняться?");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Вызвать компаньона.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Зачислить рабов в команду";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
	        {
	            Link.l6 = "Начать захват ближайшего города.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
	        if(!bDisableMapEnter && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait"))
	        {
	        	Link.l7 = "Мне бы не помешало отдохнуть...";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.pistol.bulletNum") && sti(pchar.chr_ai.pistol.bulletNum) > 1)
				{
					Link.l8 = "Хочу выбрать тип боеприпаса для пистолета.";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "Хочу выбрать тип боеприпаса для мушкета.";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "Хочу выбрать приоритетное оружие для боя.";
					Link.l10.go = "SetPriorityMode";
			}
			
			link.l11 = "Получить предметы";
			link.l11.go = "GetItems";
			
			link.l12 = "Увеличить умение";
			link.l12.go = "GetSkill";
			
			link.l13 = "Получить офицеров";
			link.l13.go = "GetOfficer";
			
			link.l14 = "Сменить корабль";
			link.l14.go = "ChangeShip";

	        
			Link.l15 = RandPhraseSimple("Не сейчас. Нет времени.", "Некогда. Дела ждут.");
			Link.l15.go = "exit";
		break;
		
		case "ChangeShip":
			iST = sti(pchar.Ship.Type);
			iST = sti(RealShips[iST].basetype)
			sAttr = "Корабль типа "+iST;
			if(iST < SHIP_TYPES_QUANTITY)
			{
				iST++;
			}
			else
			{
				iST = 0;
			}
			dialog.text = sAttr + " сменился на корабль типа "+iST;
			link.l1 = "";
			link.l1.go = "exit";
			pchar.Ship.Type = GenerateShipExt(iST, 0, pchar);
			SetBaseShipData(pchar);
		break;
		
		case "GetOfficer":
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg1", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "navigator";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_0"+(rand(4)+1);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "blade_"+(rand(5)+34);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
		//	EquipCharacterByItem(chr, sGun);
			sGun = "blade_"+(rand(5)+17);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
		//	EquipCharacterByItem(chr, sGun);
		//	sGun = "blade_0"+(rand(8)+1);
		//	TakeNItems(chr, sGun, 1);
		//	EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg2", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "boatswain";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg3", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "boatswain";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg4", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "cannoner";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg5", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "doctor";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg6", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "doctor";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg7", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "cannoner";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg8", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "carpenter";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg9", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "carpenter";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg10", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "navigator";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
		//	EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg11", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "navigator";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
		//	EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
			
			chr = GetCharacter(NPC_GenerateCharacter("TestPsg12", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(31)+3;
			chr.sea_spec = "navigator";
			chr.skill.fencing = rand(99)+1;
			chr.skill.pistol = rand(99)+1;
			chr.skill.athletics = rand(99)+1;
			sGun = "blade_"+(rand(40)+10);
			TakeNItems(chr, GetGeneratedItem(sGun), 1);
		//	EquipCharacterByItem(chr, sGun);
			sGun = "pistol"+(rand(10)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "cirass"+(rand(6)+1);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			sGun = "totem_"+(rand(22)+10);
			TakeNItems(chr, sGun, 1);
			EquipCharacterByItem(chr, sGun);
			AddPassenger(pchar, chr, false);
		/*	chr = GetCharacter(NPC_GenerateCharacter("TestOff1", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			chr.isfree = 1;
			pchar.Fellows.Passengers.navigator = sti(chr.index);
			chr.officer.role = "navigator";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff2", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			chr.isfree = 1;
			pchar.Fellows.Passengers.boatswain = sti(chr.index);
			chr.officer.role = "boatswain";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff3", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			chr.isfree = 1;
			pchar.Fellows.Passengers.doctor = sti(chr.index);
			chr.officer.role = "doctor";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff4", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			chr.isfree = 1;
			pchar.Fellows.Passengers.carpenter = sti(chr.index);
			chr.officer.role = "carpenter";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff5", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			chr.isfree = 1;
			pchar.Fellows.Passengers.cannoner = sti(chr.index);
			chr.officer.role = "cannoner";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff6", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			chr.isfree = 1;
			pchar.Fellows.Passengers.treasurer = sti(chr.index);
			chr.officer.role = "treasurer";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff7", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			SetOfficersIndex(pchar, 1, sti(chr.index));	
			chr.officer.role = "navigator";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff8", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			SetOfficersIndex(pchar, 2, sti(chr.index));	
			chr.officer.role = "treasurer";
			
			chr = GetCharacter(NPC_GenerateCharacter("TestOff9", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(chr.id);
			chr.Dialog.Filename = "Enc_Officer_dialog.c";
			LandEnc_OfficerHired();
			SetOfficersIndex(pchar, 3, sti(chr.index));	
			chr.officer.role = "treasurer";	*/
			
			
		/*	chr = GetCharacter(NPC_GenerateCharacter("EasterPris11", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			AddPassenger(pchar, chr, true);
			chr = GetCharacter(NPC_GenerateCharacter("EasterPsg11", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			AddPassenger(pchar, chr, false);
			chr = GetCharacter(NPC_GenerateCharacter("EasterPris12", "Pirate_1", "man", "man", 10, PIRATE, -1, false, "abc"));
			chr.FaceId = rand(176);
			AddPassenger(pchar, chr, true);
			*/
			DialogExit_Self();
		break;
		
		case "GetSkill":
			AddCharacterExpToSkill(pchar, "Speechcraft", 1000);
			DialogExit_Self();
		break;
		
		case "GetItems":
			TakeNItems(pchar, "recipe_potionjaguar", 2);	
			TakeNItems(pchar, "recipe_berserker_potion", 2);	
			TakeNItems(pchar, "recipe_potionloa", 2);	
			TakeNItems(pchar, "purse3", 2);	
			for(int ijg=10; ijg<=50; ijg++)
			{
				TakeNItems(pchar, GetGeneratedItem("blade_"+ijg), 1);
			}
			
			TakeNItems(pchar, "poison1", 1);
			TakeNItems(pchar, "poison2", 1);
			TakeNItems(pchar, "poison3", 1);
			TakeNItems(pchar, "poison4", 1);
			TakeNItems(pchar, "poison5", 1);
			TakeNItems(pchar, "poison6", 1);
			TakeNItems(pchar, "poison7", 1);
			TakeNItems(pchar, "poison8", 1);
			TakeNItems(pchar, "poison9", 1);
			
			TakeNItems(pchar, "totem_30", 3);
			TakeNItems(pchar, "totem_31", 3);
			
			TakeNItems(pchar, "cirass6", 1);	
			TakeNItems(pchar, "pistol4", 1);	
			TakeNItems(pchar, "mushket_Bombard", 1);
			TakeNItems(pchar, "mushket_matchlock", 1);			
			TakeNItems(pchar, "potionrum", 1);	
			TakeNItems(pchar, "berserker_potion", 1);	
			TakeNItems(pchar, "potiontlaloc", 1);	
			TakeNItems(pchar, "potionlegba", 1);	
			TakeNItems(pchar, "spyglass4", 1);	
			SetCharacterPerk(pchar, "Musketeer");
			SetCharacterPerk(pchar, "Breter");
			SetCharacterPerk(pchar, "Knight");
			SetCharacterPerk(pchar, "BasicDefense");
			SetCharacterPerk(pchar, "Shooter");	
			
			DialogExit_Self();
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.pistol.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "pistol", sBullet);
			LAi_GunSetUnload(pchar, "pistol");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sMusket = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sMusket);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sMusket = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sMusket);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "В начале боя я буду доставать:";
			Link.l1 = "Холодное оружие";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Мушкет";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.chr_ai.priority_mode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.chr_ai.priority_mode = 2;
			DialogExit_Self();
		break;

		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Начать захват, конечно, можно, да вот только корабль под залпами форта долго не продержится. И десант высадить не успеем.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
	                if (pchar.location == "Panama_ExitTown")
					{
						Dialog.Text = "Не-е-ет, я не сумасшедший. Это же Панама! Взять ее НЕВОЗМОЖНО!!! Надо валить отсюда, а то точно дождусь черной метки...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = "Напасть на город " + GetCityName(chr.City) + ".";
		    			Link.l1 = "К оружию!";
		    			Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Отставить!";
		    			Link.l2.go = "exit";
					}
	    		}
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Эх! Команды маловато, нужно хотя бы 500 человек.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Не разбредаться! Продолжаем атаку!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Никто из рабов не хочет идти в команду.";
	            Link.l1 = "Ну и не нужно!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "На корабле нет места для новых матросов.";
	                Link.l1 = "Эх! Нужно переместить часть экипажа на другой корабль.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "В команду желают пойти " + pchar.GenQuest.SlavesToCrew+ " рабов. Взять их?";
	                Link.l1 = "Да";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Нет";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
	        AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0));
			
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Теперь этот отличный корабль мой, и я здесь капитан! Жаль, пришлось вырезать всю команду.";
			Link.l1 = "Пора на берег...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Кого из компаньонов вызвать?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "В другой раз.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--	
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}

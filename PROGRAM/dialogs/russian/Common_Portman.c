#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn;
    ref chref;
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			//homo
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Приветствую вас, " + GetAddress_Form(NPChar) + ". Мы, кажется, не знакомы. Я "  + GetFullName(npchar)+ " - начальник порта.";
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я " + GetFullName(PChar) + ", капитан корабля '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Вы ко мне по делу?",
                                    "Здравствуйте, " + GetFullName(Pchar) + ". Я видел, как ваш корабль вошел в порт, и был уверен, что вы ко мне зайдете.",
                                    "А, капитан " + GetFullName(Pchar) + ". Что привело вас ко мне?");
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я хочу с вами поговорить.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
			Link.l2 = "Здесь можно подыскать работу? Или контракт?";
			Link.l2.go = "node_4";
			Link.l13 = LinkRandPhrase("К вам наверняка обращаются купцы, подыскивающие сопровождение для своих кораблей. Нет ли таких сегодня?","Нет ли у вас на примете пассажиров, желающих добраться до другой колонии?","У меня отличный корабль, и я хочу подзаработать эскортом купцов или доставкой пассажиров. Нет ли у вас таких?"));
			Link.l13.go = "work_PU";
			Link.l3 = "Могу я оставить один из своих кораблей на время?";
			Link.l3.go = "ShipStock_1";
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Я хочу забрать свой корабль обратно.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			link.l6 = "Меня интересуют капитаны, которые отмечались в вашем портовом управлении.";
			link.l6.go = "CapitainList";
			link.l8 = "Я по другому вопросу.";
			link.l8.go = "quests";										
			Link.l15 = "Благодарю. До свидания.";
			Link.l15.go = "exit";
		break;

		case "node_4":
			dialog.text = "Губернатор радеет за благополучие города - у него всегда есть работа. Потом, в таверне могут быть заинтересованные купцы, ну и магазин иногда фрахтует капитанов.";
			Link.l1 = "Еще один вопрос.";
			Link.l1.go = "node_2";
			Link.l2 = "Благодарю. До свидания.";
			Link.l2.go = "exit";
		break;


		/////////////////////////////////////////////////////////==========================/////////////////////////////////////////////////////
		//эскорт-пассажиры
		case "work_PU":
			dialog.text = "А корабль твой где? Ты что - на собственном горбу пассажиров возить собрал"+ GetSexPhrase("ся","ась") +"?";
			link.l1 = "Хм, и то верно...";
			link.l1.go = "exit";
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			dialog.text = "У меня в списках нет капитанов, способных вас заинтересовать.";
			link.l1 = "Понятно. Спасибо за информацию.";
			link.l1.go = "node_2";
		break;
		
		case "ShipStock_1":
            if (sti(NPChar.Portman) >= 3)
			{
                dialog.text = "Вообще-то, да. Но сейчас я не могу принять корабль. Нет мест в доках.";
    			Link.l1 = "Очень жаль.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Какой именно корабль вы хотите оставить?";
	    			for(i=1; i<COMPANION_MAX; i++)
	                {
	        	        cn = GetCompanionIndex(PChar, i);
	        	        if( cn >0 )
	        	        {
	        		        chref = GetCharacter(cn);
	                        if (!GetRemovable(chref)) continue;
	
	        		        attrL = "l"+i;
	        		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
	        		        Link.(attrL).go = "ShipStockMan_" + i;
	        		    }
	        	    }
	    			Link.l9 = "Спасибо, не нужно.";
	    			Link.l9.go = "exit";
    			}
    			else
    			{
					dialog.text = "Хм. Я не вижу ваших кораблей в порту.";
	    			Link.l1 = "Да, я просто хотел"+ GetSexPhrase("","а") +" узнать о возможности стоянки.";
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Посмотрим что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
//            		NPChar.MoneyForShip =  GetPortManPrice(sti(RealShips[sti(chref.Ship.Type)].Price), NPChar);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', класс " + RealShips[sti(chref.Ship.Type)].Class +
                     ", стоимость стоянки " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " в месяц, оплата за месяц вперед.";
			Link.l1 = "Да. Это меня устраивает.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Меня тоже все устроит, если у вас будет нужная сумма.";
			Link.l1 = "Упс... зайду позже.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
            AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчета
            chref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";

            NPChar.Portman    = sti(NPChar.Portman) + 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			dialog.text = "Хорошо. Заберете, когда будет нужно.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Какой именно корабль вы заберете?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
	            	{
	            		makeref(chref, Characters[i]);
	            		if (CheckAttribute(chref, "ShipInStockMan"))
	            		{
	                        if (chref.ShipInStockMan == NPChar.id)
	        		        {
	                            attrL = "l"+cn;
	            		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
	            		        Link.(attrL).go = "ShipStockManBack_" + i;
	            		        cn++;
	        		        }
	            		}
	                }
	
	    			Link.l9 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
	    			Link.l9.go = "exit";
				}
				else
				{
	                dialog.text = "Нет ли у вас места для еще одного корабля?";
	    			Link.l1 = "Да, точно. Спасибо.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Хм. Я не вижу вашего флагмана в порту. А забрать свои корабли вы можете только здесь.";
    			Link.l1 = "Хорошо, я прибуду за ними позднее.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Забираете? С вас за хранение еще " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "Забираете?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Да.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
            AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		break;
	}
}
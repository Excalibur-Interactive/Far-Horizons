
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Не о чем говорить.";
			link.l1 = "Ладно...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Давай, приятель, выворачивай карманы.";
			link.l1 = "Чего?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Того! Давай быстрей, без разговоров. Не люблю я этого...";
			link.l1 = "Вот это подстава!! А " + pchar.questTemp.different.FackWaitress.Name + " с тобой в паре работает, что ли?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "В паре, в паре... Выворачивай карманы, не то зарежу ведь!";
			link.l1 = "Черта с два! За свои карманы я сам кого хочешь зарежу...";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Забирай, паршивец! Но это вам так просто с рук не сойдет...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Конечно, не сойдет, кто же спорит? Ну, прощай дружище. И помни - не такой ты красавец, чтобы на тебя официантки с ходу вешались. Впредь будешь умней!";
			link.l1 = "Это точно!..";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Ну, как знаешь...";
			link.l1 = "Знаю, знаю, приятель...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "А вот и я! Не соскучился, красавчик?";
			link.l1 = "Не успел...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Ну, тогда не будем терять времени!";
			link.l1 = "Хе, согласен!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Здравствуйте. Меня зовут " + GetFullName(npchar) + ". Я капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + "'."; 
			link.l1 = "Отлично! Наконец-то я тебя наш"+ GetSexPhrase("ел","ла") +"...";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Наш"+ GetSexPhrase("ел","ла") +"?!";
			link.l1 = "Ага. В общем, я привез"+ GetSexPhrase("","ла") +" тебе твой судовой журнал. Который ты забыл у начальника порта " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Дьявол, так вот где я его 'посеял'! Да уж, эта пропажа чуть было не привела к бунту на корабле...";
			link.l1 = "Ну, все хорошо, что хорошо кончается. Забирай свой журнал и давай поговорим о моем гонораре за труды.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Новый журнал я еще не завел, как раз собирался, поэтому заплачу максимум из того, что могу себе позволить. " + FindRussianMoneyString(sti(npchar.quest.money)) + " и немного моих личных драгоценностей.";
				link.l1 = "Ну, неплохо. Забирай свой журнал.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Хм, ты знаешь, я уже завел новый журнал. Тем не менее, старый журнал мне нужен еще, необходимо все перенести в новый. Так что я могу забрать его за " + FindRussianMoneyString(sti(npchar.quest.money)) + ". и немного моих личных драгоценностей.";
					link.l1 = "Ну что же, договорились. Забирай свой журнал!";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Так я завел новый журнал уже. И все записи старого по памяти перенес туда, два дня сидел и писал. Так что мне старый журнал теперь попросту не нужен. И ничего заплатить за него я не могу.";
					link.l1 = "Вообще ничего? Что я, зря за тобой гонял"+ GetSexPhrase("ся","ась") +"?";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Спасибо тебе. Ну, всего хорошего, "+ GetSexPhrase("приятель","подруга") +".";
			link.l1 = "И тебе того же...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Хе, если уж взял"+ GetSexPhrase("ся","ась") +" догонять, то надо быть расторопней.";
			link.l1 = "Гм, тоже верно... Ну ладно, забирай свой журнал просто так.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Приветствую тебя на палубе моего судна. Честно говоря, я уж, было, испугался - решил, что это Одноглазый Стид Хантер решил поохотиться за мной...";
				link.l1 = "Де нет, приятель, сегодня я добр"+ GetSexPhrase("ый","ая") +". Я разыскивал"+ GetSexPhrase("","а") +" тебя, чтобы помочь.";
			}
			else
			{
				dialog.text = "Приветствую тебя на моей палубе! Что ты хотел"+ GetSexPhrase("","а") +"?";
				link.l1 = "Разыскивал"+ GetSexPhrase("","а") +" тебя, приятель. Еле нагнал"+ GetSexPhrase("","а") +"...";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Разыскивал"+ GetSexPhrase("","а") +"? А зачем?";
			link.l1 = "Ты забыл свой судовой журнал у начальника порта " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ". Журнал у меня! Поэтому и разыскивал"+ GetSexPhrase("","а") +", чтобы отдать.";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Черт, так, значит, вот где я его потерял!.. Это ценная услуга, "+ GetSexPhrase("дружище, ","") +"нет слов. А то я чуть капитанского статуса не лишился... Большое тебе спасибо.";
				link.l1 = "Как насчет вознаграждения?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Черт, так, значит, вот где я его потерял!.. Спасибо тебе, конечно, но дело в том, что ты долго меня искал"+ GetSexPhrase("","а") +", и я уже завел новый. Однако, перенести кое-что мне оттуда нужно, поэтому я заберу журнал у тебя. Но много заплатить не могу...";
					link.l1 = "А сколько можешь?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Черт, так, значит, вот где я его потерял!.. Спасибо тебе, конечно, но дело в том, что ты долго меня искал"+ GetSexPhrase("","а") +", и я уже завел новый. Старые записи перенес по памяти, так что мне он не нужен.";
					link.l1 = "Что, вообще тебе старый журнал не нужен? Совсем?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Я готов выплатить тебе " + FindRussianMoneyString(sti(npchar.quest.money)) + " и дать впридачу немного своих личных драгоценностей. Это все, что я могу себе позволить.";
			link.l1 = "Ну, хорошо. Вот твой журнал.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Спасибо еще раз. Прощай, "+ GetSexPhrase("дружище, ","") +"и будь здоров"+ GetSexPhrase("","а") +".";
			link.l1 = "И тебе здоровья.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "Абсолютно"+ GetSexPhrase(", дружище","") +". Ты слишком долго меня искал"+ GetSexPhrase("","а") +", нужно было поторопиться.";
			link.l1 = "Хех, нужно было не терять журнала, тогда и я бы не мотал"+ GetSexPhrase("ся","ась") +" без толку. Ну да ладно, забирай свой журнал даром, мне он тоже не нужен.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Вроде, все решили уже.";
			link.l1 = "Да, это верно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Приветствую. Что тебе нужно у меня на корабле?";
			link.l1 = "Да так, новостями обменяться хотел"+ GetSexPhrase("","а") +". Может, что продается у тебя...";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Ничего не продается, и новостей у меня нет. И вообще, честно говоря, твое присутствие у меня на палубе нежелательно. Надеюсь, ясно выразился?";
			link.l1 = "Да куда уж ясней... Ну ладно, бывай, дружище.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Сказал же, что тебе тут делать нечего!";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Зачем ты напал"+ GetSexPhrase("","а") +" на нас?!!";
			link.l1 = "Я долж"+ GetSexPhrase("ен","на") +" вернуть корабль его владельцу.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Какому владельцу?! Я и есть владелец!";
			link.l1 = "Нет, это не так. Кто владеет кораблем - и я сам"+ GetSexPhrase("","а") +" не знаю, но я знаю, что корабль украден со стоянки одного из портов. Я долж"+ GetSexPhrase("ен","на") +" его вернуть на место.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Дьявол! Ну, для меня еще не все потеряно. Я все-таки попытаюсь отправить тебя на тот свет...";
			link.l1 = "Ну, попытайся...";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		//--------------------------- ночное бдение в церкви --------------------------------
		case "ChurchBerglar":
			dialog.text = "Вот это да! Ты чего это тут делаешь?!";
			link.l1 = "Я? Церковь охраняю.";
			link.l1.go = "ChurchBerglar_1";
		break;
		case "ChurchBerglar_1":
			dialog.text = "Хе, ну надо же... И как успехи?";
			link.l1 = "Похоже, что есть.";
			link.l1.go = "ChurchBerglar_2";
		break;
		case "ChurchBerglar_2":
			dialog.text = "Ты, конечно, извини, "+ GetSexPhrase("дружище","подруга") +", но жив"+ GetSexPhrase("ым","ой") +" тебе отсюда не уйти. Мне очень жаль, не надо было тебе браться за эту охрану...";
			link.l1 = "Ха! А вот мне не жаль. Церкви грабить - это перебор. Так что без всяких угрызений отправлю тебя к праотцам.";
			link.l1.go = "ChurchBerglar_fight";
		break;
		case "ChurchBerglar_fight":
			LAi_LocationFightDisable(&locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------- поиск кэпов, дача квеста горожанином --------------------------------
		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Здравствуйте, капитан. Хочу просить вас помочь мне.", 
				"Капитан! Не окажете мне услугу? Дело в том, что я нуждаюсь в помощи.", 
				"Капитан, я прошу вас о помощи!");
			link.l1 = RandPhraseSimple("Я занят"+ GetSexPhrase("","а") +", не сегодня!", "В данный момент у меня нет времени вас выслушивать.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Что у вас стряслось?", "Излагайте суть проблемы. Возможно, я сумею помочь.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Год назад один капитан взялся доставить меня " + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + ". Но на борту его корабля я был брошен в трюм, а потом продан в рабство. Из этой переделки я выбрался с огромным трудом, несколько раз находился на грани жизни и смерти... В общем, я хочу напомнить моему 'другу', что я еще жив.";
					link.l1 = "В смысле? Точнее опишите, что вы желаете.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Дело в том, что у меня похитили жену. Один капитан, пират по слухам, ухлестывал тут за ней, как только мог. Жена одно время даже не выходила из дома, настолько он был назойлив. Я пытался привлечь городские власти к этой проблеме - безрезультатно. И вот дождались, называется...";
					link.l1 = "Чего дождались?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Вы знаете, я ищу своего земляка, с которым три года назад мы отправились сюда из Старого света в поисках новой жизни. Так случилось, что в дороге мы потеряли друг друга. Но недавно я узнал, что мой земляк стал торговым капитаном! Я пытался его найти, но сам с этим справиться не могу.";
					link.l1 = "Почему? Множество капитанов, включая меня, могут доставить вас куда угодно.";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Я хочу, чтобы вы нашли его и отправили на тот свет. Я настолько хочу отомстить, что просто кушать не могу...";
			link.l1 = "Понятно... Думаю, что смогу вам помочь при случае. Назовите мне имя капитана и корабль, на котором он ходит.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Извините, меня это не интересует.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Капитана зовут " + npchar.quest.SeekCap.capName + ". Ходит на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'. Я заплачу вам за эту работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " и все свои личные драгоценности.";
			link.l1 = "Ясно. Ну что же, я буду внимател"+ GetSexPhrase("ен","ьна") +" при передвижениях по Карибскому морю. Если встречу этого кэпа, то ему крышка...";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "За такие деньги я и пальцем не пошевельну. Ищи дурака в другом месте.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Фуф-ф, это то, что я так жаждал услышать!.. О-о, уже и кушать могу! Надо бы перекусить...";
			link.l1 = "Давай, приятель. Как выполню работу - найду тебя здесь, в городе.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Хорошо, я буду ждать вас в местной церкви. Тогда и рассчитаюсь с вами.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "Мое относительное бездействие привело к печальным результатам. Этот мерзавец похитил мою жену и увез ее на своем корабле в море. Я прошу вас найти этого негодяя!";
			link.l1 = "Хм, ну и зачем мне ссориться с коллегами?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Я небогат, но с радостью отдам все, что у меня есть! Если вы освободите мою жену и доставите ее ко мне, то я заплачу вам " + FindRussianMoneyString(sti(npchar.quest.money)) + " и отдам все свои личные драгоценности.";
			link.l1 = "Хм, ну что же, я готов"+ GetSexPhrase("","а") +" заняться этим делом. Как зовут этого любвеобильного кэпа, какой у него корабль? Да, и как зовут вашу жену?";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Нет, приятель, за такие деньги я не возьмусь за это дело. Сожалею...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Ее зовут " + npchar.quest.SeekCap.name + ". Мерзавца-капитана зовут " + npchar.quest.SeekCap.capName + ", плавает он на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Плавают известные продукты жизнедеятельности человека, приятель. А капитаны - ходят...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Да-да, конечно, извините! Я ведь не моряк, так что сами понимаете...";
			link.l1 = "Да все нормально, не переживайте. В общем, теперь ожидайте меня с результатами поисков.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Спасибо вам огромное! Я буду ждать вас в местной церкви. Только я умоляю вас - быстрее. Я очень опасаюсь за жену...";
			link.l1 = "Сделаю все, что смогу. Ждите.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "Дело в том, что мой земляк так и не обзавелся здесь недвижимостью. Его дом - это его корабль. Поэтому мне очень сложно его отловить, он постоянно в движении. А я не могу позволить себе тратить время на бесполезные путешествия, я вынужден зарабатывать себе на жизнь.";
			link.l1 = "Если у вас нет денег, то я ничем не смогу вам помочь...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Я могу заплатить вам за работу " + FindRussianMoneyString(sti(npchar.quest.money)) + " и отдам все свои личные драгоценности. Это все, что я могу себе позволить на данный момент.";
			link.l1 = "Сумма меня устраивает, я готов"+ GetSexPhrase("","а") +" взяться за это дело. Вы, кстати, можете пойти ко мне пассажиром, тогда вам не придется ездить к земляку, когда он будет найден.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Это слишком мало для меня. Так что поищите кого-нибудь другого для этого дела.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Нет, я, пожалуй, останусь здесь. Неизвестно, сколько продлятся поиски, и у меня может просто не хватить денег. А здесь у меня есть работа.";
			link.l1 = "Понимаю. Ну что же, теперь расскажите мне, кто ваш друг и какой у него корабль.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "Его зовут " + npchar.quest.SeekCap.capName + ". Насколько мне известно, он имеет " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Ясно. Ну что же, как только встречу вашего земляка, то обязательно расскажу ему, что вы его ищете.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Спасибо вам. Я буду ждать вашего прибытия в местной церкви. Полагаю, что деньги мне нужно будет отдать после того, как работа будет выполнена.";
			link.l1 = "Конечно. Ну, всего хорошего, ожидайте результата поисков.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("","а"));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Здравствуйте, капитан. Есть какие-нибудь результаты по моему делу?";
			link.l1 = "Напомни, что там у тебя?..";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "По вашему виду догадываюсь, что я наконец-то отомщен. Это так?";
					link.l1 = "Именно. " + npchar.quest.SeekCap.capName + " мертв, а его " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " на дне.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Вы разыскали мою жену! Это правда?!";
					link.l1 = "Правда. Она у меня на корабле в качестве пассажира. Можете ее забирать, если " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " и есть ваша жена...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Здравствуйте, капитан. Вы нашли моего земляка?";
					link.l1 = "Наш"+ GetSexPhrase("ел","ла") +" и рассказал"+ GetSexPhrase("","а") +", что вы его ждете здесь. Так что все вышло удачно.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Как, вы забыли, что я нанял вас отомстить капитану по имени " + npchar.quest.SeekCap.capName + " за год, проведенный мной в рабстве?!";
					link.l1 = "Да ничего я не забыл"+ GetSexPhrase("","а") +". Занимаюсь этим, жди.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Ушам не верю! Вы забыли, что обещали мне разыскать и освободить мою жену? Ее похитил пират по имени " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "Не забыл"+ GetSexPhrase("","а") +" я о твоей жене. Просто розыски пока не принесли результата. Все это не так просто, жди...";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Подождите... Вы что, забыли о своем обещании найти моего земляка, торгового капитана по имени " + npchar.quest.SeekCap.capName + "?";
					link.l1 = "Не забыл"+ GetSexPhrase("","а") +", но пока не наш"+ GetSexPhrase("ел","ла") +". Жди...";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Превосходно, я в вас не ошибался! Итак, как мы и договаривались, вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. Спасибо за труд.";
			link.l1 = "Хм, да не за что...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+drand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Боже мой, вы буквально вернули меня к жизни! Извольте получить свои " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. И знайте, что мы будем молиться за вас до конца жизни!";
			link.l1 = "Молитесь, я не против.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+drand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Отлично!.. Вот то, что я вам обещал - " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. И спасибо вам, капитан.";
			link.l1 = "Не за что, дружище. Прощай...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+drand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Здравствуйте, капитан. Я хотела попросить вас об одном одолжении.", 
				"Капитан! Помогите женщине, будьте так добры...", 
				"Капитан, не откажите "+ GetSexPhrase("даме","мне") +" в помощи.");
			link.l1 = RandPhraseSimple("Я занят"+ GetSexPhrase("","а") +", красавица, не сегодня!", "Прошу прощения, " + GetAddress_FormToNPC(NPChar) + ", но в данный момент я не имею времени...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Что у вас стряслось, " + GetAddress_FormToNPC(NPChar) + "?", "Излагайте суть проблемы, " + GetAddress_FormToNPC(NPChar) + ". Я постараюсь вам помочь.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Мой муж занимается коммерцией - доставляет грузы торговцам по всей округе. Так вот, он ушел в море уже больше трех месяцев назад, и до сих пор не вернулся!";
					link.l1 = "Вы думаете, с ним что-то случилось?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+ GetSexPhrase("Капитан, вот смотрю я на вас и вижу бравого капитана, отменного головореза","Капитан, я вижу вы сильная и отважная женщина, любого мужика за пояс заткнете") +"...";
					link.l1 = "Это вы к чему, " + GetAddress_FormToNPC(NPChar) + "?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Капитан, помогите мне, умоляют вас! Мой муж попал к пиратам! Вы можете спасти его?";
					link.l1 = "Подождите, что-то я не очень понимаю, кто к кому попал...";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "Не знаю, но очень надеюсь, что он просто занят по работе. Хотя мог бы отправить весточку, знает ведь, что я волнуюсь!";
			link.l1 = "В море сейчас неспокойно, всякое может случиться...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Вот! Вы понимаете, о чем я говорю. По виду вы "+ GetSexPhrase("капитан бравый","девушка бравая") +", поэтому я и хотела попросить вас о том, чтобы вы нашли моего мужа. За это я готова заплатить вам " + FindRussianMoneyString(sti(npchar.quest.money)) + " и отдам свои драгоценности.";
			link.l1 = "Хорошо. Если я встречу вашего мужа в море или где-нибудь еще, то сообщу ему о вашем беспокойстве. И скажите мне, как зовут вашего супруга и что у него за корабль.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Такие деньги меня не интересуют. К сожалению, я вынужден"+ GetSexPhrase("","а") +" отказаться...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Его зовут " + npchar.quest.SeekCap.capName + ". А работает он на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Понятно. Ну что же, теперь ожидайте. И постарайтесь находиться преимущественно в церки, чтобы я не искал"+ GetSexPhrase("","а") +" вас по городу...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+ GetSexPhrase("Это я к тому, любезный, что я хочу нанять вас по прямому назначению, так сказать... ","Я хочу, чтобы вы помогли мне. Надеюсь, что вы меня поймете, как женщина. ") +"Мне порядком досадил один капитан, я желаю, чтобы он умер.";
			link.l1 = "О-хо-хо! Вот это да! И что же он вам сделал, этот несчастный?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Этот мерзавец обманул меня. Он делал вид, что я ему нравлюсь, даже ухаживал за мной. А оказалось, что ему нужно кое-что от моего мужа! И когда этот проходимец получил кредит, вдруг оказалось, что ничего такого он не имел в виду...";
			link.l1 = "Хм, а может, и имел?..";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Я что, по-вашему, дура?! Не умею отличить ухаживания от пустой болтовни?";
			link.l1 = "Да нет, что вы...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Он просто воспользовался мной, этот мерзавец! Никогда ему этого не прощу!..";
			link.l1 = "Хм... "+ GetSexPhrase("а","да, мужчины на это способны. Но,") +" может, вы остынете? Ну, пройдет день-другой, и все изменится...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Изменится?! "+ GetSexPhrase("Да вы моралист какой-то, а не пират","Видимо, вы никогда не бывали в такой ситуации! Ну да, кто бы рискнул... а я всего лишь слабая женщина...") +"!";
			link.l1 = ""+ GetSexPhrase("Ну что вы! ","") +"Я просто хочу знать, насколько ваши намерения серьезны.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Черт возьми, "+ GetSexPhrase("вы просто не знаете, что такое месть отвергнутой женщины","вы же женщина, и должны понимать, каково это - быть отвергнутой! Я хочу отомстить") +"!..";
			link.l1 = ""+ GetSexPhrase("Это верно, как-то не довелось","Ну, знаете, некоторые просто поплачут и все") +"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+ GetSexPhrase("Считайте, что вам повезло. Отвергнутая и обманутая в своих ожиданиях женщина - это фурия, дьявол в юбке! Нет ничего, способного смягчить ее гнев","А вот я не такая. И нет ничего, что может смягчить мой гнев") +"!\nТак что я хочу, чтобы вы убили его лично. А перед смертью он должен узнать, кто все это организовал...";
			link.l1 = "Хм, даже не знаю что сказать... И сколько вы готовы за это заплатить?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Все, что у меня есть. Я отдам вам мои драгоценности и " + FindRussianMoneyString(sti(npchar.quest.money)) + "! Устроит?";
			link.l1 = "Ну что же, мне это интересно. Расскажите мне, кто ваш обидчик, капитаном какого корабля он является?";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = ""+ GetSexPhrase("Пожалуй, я проявлю мужскую солидарность. ","") +"Извините, без меня...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "Этого негодяя зовут " + npchar.quest.SeekCap.capName + ", он является капитаном " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Считайте, что ваш заказ принят к исполнению, " + GetAddress_FormToNPC(NPChar) + ". А теперь ждите меня в местной церкви. Надеюсь, теперь вас хоть немного отпустит...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("ен","на"));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("","а"));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Сейчас я вам объясню. Дело в том, мой муж, совершенно обычный человек, был захвачен пиратами! Они убивали всех, никого не щадили...";
			link.l1 = "Значит, капитан посмел оказать сопротивление. Если бы они сдались, никого бы не тронули.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Может быть, но мой муж тут совершенно ни при чем. Он был простым пассажиром на этом корабле. Так вот, чтобы спасти свою жизнь, ему пришлось сказать, что он сказочно богат. Пираты его пощадили, и даже не бросили в трюм.";
			link.l1 = "А откуда вы знаете?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Мужу удалось отправить мне письмо, где он пишет, что с ним все в порядке. Его держат в каюте, не как других пленников.";
			link.l1 = "И что вы намерены делать? Так долго продолжаться не может. Рано или поздно пираты его раскусят.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Вы ведь тоже пират? Да-да, я знаю... Умоляю вас, помогите нам, спасите моего мужа! В письме он описал пиратский корабль и назвал имя капитана. Вам ведь будет достаточно просто найти его!";
			link.l1 = "Не так это и просто, как вам кажется. Все пленники - законный приз захватившего корабль кэпа. Да и не могу я сделать это за короткий срок.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Но вы же можете попытаться! К тому же, время на поиски есть. Мой муж далеко не дурак, он назвался негоциантом из Старого света, так что пираты не требуют за него денег немедленно - ехать за ними очень далеко. Если вы освободите его, то я отдам вам все, что у меня есть!";
			link.l1 = "И что у вас есть?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Немного, " + FindRussianMoneyString(sti(npchar.quest.money)) + " и все мои драгоценности... Но я буду молиться за вашу душу до конца жизни!";
			link.l1 = "Да уж, действительно немного... Ну да ладно, я готов"+ GetSexPhrase("","а") +" помочь вам при случае.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Сожалею, но это слишком мало для того, чтобы я напал"+ GetSexPhrase("","а") +" на своего коллегу, члена Берегового братства.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Спасибо вам, спасибо!!";
			link.l1 = "Если все получится, тогда и будете благодарить, а пока не стоит. Расскажите-ка лучше, как зовут вашего мужа и все, что вы знаете об этих пиратах.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "Мужа зовут " + GetFullName(forName) + ". Капитана пиратов зовут " + npchar.quest.SeekCap.capName + ", он промышляет на " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + " с именем '" + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = "Ясно. Ну что же, теперь ожидайте и надейтесь, что мне повезет с поисками. Постарайтесь находиться в церкви, чтобы я мог"+ GetSexPhrase("","ла") +" вас там быстро найти.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("","а"));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Ой, капитан, я так рада вас видеть! Расскажите мне быстрей, что вы узнали по моему делу?";
			link.l1 = "Хм, напомните, " + GetAddress_FormToNPC(NPChar) + ", о каком деле идет речь?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ах, капитан, я получила письмо от мужа! В нем он пишет, что вы нашли его.";
					link.l1 = "Да, все верно, " + GetAddress_FormToNPC(NPChar) + ". Ваш муж, " + npchar.quest.SeekCap.capName + ", жив и здоров. Он просто заработался, так сказать...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Что скажете, капитан? Вы сделали то, о чем я вас просила? Капитан " + npchar.quest.SeekCap.capName + " мертв?";
					link.l1 = "Да, он мертв, " + GetAddress_FormToNPC(NPChar) + ". Перед смертью он узнал, кто стал причиной его смерти. Последнее, что он слышал в этой жизни - ваше имя.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Вы все-таки освободили моего мужа! Умоляю вас, скажите мне, это так?!!";
					link.l1 = "Да, сейчас он находится у меня на корабле. Можете его забирать, если " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " и есть ваш муж...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Вы что, забыли, что обещали мне найти моего мужа? Его зовут " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "О-о, да, конечно... Ничего я не забыл"+ GetSexPhrase("","а") +", просто я пока так и не сумел"+ GetSexPhrase("","а") +" его разыскать.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Я что-то не поняла! Вы забыли, что должны отправить на тот свет моего обидчика, капитана по имени " + npchar.quest.SeekCap.capName + "?!";
					link.l1 = "Ну что вы, " + GetAddress_FormToNPC(NPChar) + ", ни в коем разе. Ваш заказ в работе, ожидайте...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Господи, капитан, вы забыли, что обещали вызволить моего мужа из плена?!";
					link.l1 = "Я ничего не забыл"+ GetSexPhrase("","а") +", работаю над этим. Ждите, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Боже мой, как я вам благодарна! Да, кстати, вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + ". И еще раз спасибо!";
			link.l1 = "Хм, да не за что...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+drand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Отлично! Ну что же, вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + " и драгоценности. Прощайте.";
			link.l1 = "Прощайте...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+drand(8));
			TakeNItems(pchar, "jewelry14", rand(3));
			TakeNItems(pchar, "jewelry13", rand(3));
			TakeNItems(pchar, "jewelry10", rand(3));
			TakeNItems(pchar, "jewelry15", rand(3));
			TakeNItems(pchar, "jewelry16", rand(3));
			TakeNItems(pchar, "jewelry18", rand(3));
			TakeNItems(pchar, "jewelry6", rand(3));
			TakeNItems(pchar, "jewelry7", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Конечно, это он!!! Господи, капитан, как же я вам благодарна! Вот ваши " + FindRussianMoneyString(sti(npchar.quest.money)) + ". Я буду молиться за вас каждый день, пока жива!";
			link.l1 = "Это приятно, молитесь...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+drand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Приветствую коллегу. Что ты хотел"+ GetSexPhrase(", дружище","а, подруга") +"?";
					link.l1 = "Тебя зовут " + GetFullName(npchar) + ", не так ли?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Да, это верно!";
			link.l1 = "Тогда тебе не повезло. Я сейчас назову тебе одно имя, а ты постарайся вспомнить этого человека. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Не припоминаешь?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Хм, припоминаю...";
			link.l1 = "Так вот, он очень на тебя обижен, приятель. Так что пришло время рассчитаться за то, что ты продал свободного человека в рабство.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Рассчитаться?! Это ты о чем?";
			link.l1 = "О том, что я прикончу тебя прямо здесь.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Ты подумай, "+ GetSexPhrase("дружище","подруга") +", ради кого ты стараешься! Это же совершенно ничтожный человечишка. Ему самое место - на плантациях тростника!";
			link.l1 = "Ну, не тебе места распределять. Так что придется ответить за содеянное!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Хо! Ну что же, отвечу, как умею!";
			link.l1 = "Давай-давай...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "Что тебе нужно у меня на палубе?";
			link.l1 = "Хочу спросить тебя, не занимаешься ли ты извозом пассажиров?";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "А тебе какое дело?";
			link.l1 = "Да просто так спрашиваю...";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Просто так... Слушай, убирайся-ка ты отсюда, пока даю тебе такую возможность. Не нравишься ты мне!";
			link.l1 = "Ладно, ладно, не кипятись. Уже ухожу...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Поговорили уже, не нарывайся!";
			link.l1 = "Да я не нарываюсь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Приветствую коллегу! Ты что-то хотел"+ GetSexPhrase(", дружище","а, подруга") +",?";
			link.l1 = "Я хотел"+ GetSexPhrase("","а") +" узнать, не ты ли забрал из " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " женщину, по имени " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Хех, так и есть, она у меня в каюте! Хороша, чертовка!.. А зачем ты спрашиваешь?";
			link.l1 = "Приятель, эта дама замужем. Ты похитил замужнюю женщину!";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "Ну и что с того? Она мне нравится, и дело с концом. И я не позволю какому-то оборванцу вмешиваться в наши отношения только потому, что он ее муж, видите ли!..";
			link.l1 = "Позволю себе заметить, что Береговое Братство такие вот фортеля не поощряет.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Ты что, мораль мне тут читать надумал"+ GetSexPhrase("","а") +"? Береговое Братство к этому делу никакого отношения не имеет, так что твои разговоры ни к чему не приведут. Она моя, и точка!";
			link.l1 = "Не заводись, я просто поинтересовал"+ GetSexPhrase("ся","ась") +"... Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Поговорили уже о женщинах. Больше не желаю это обсуждать!";
			link.l1 = "Ладно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Рад приветствовать коллегу у себя на палубе! Что ты хотел"+ GetSexPhrase("","а") +" обсудить со мной, "+ GetSexPhrase("дружище","подруга") +"?";
			link.l1 = "Я хотел"+ GetSexPhrase("","а") +" узнать, не ты ли забрал из " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " женщину, по имени " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Хех, так и есть, она у меня в каюте! Хороша, чертовка!.. А зачем ты спрашиваешь?";
			link.l1 = "Приятель, эта дама замужем. Ты похитил замужнюю женщину!";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "Ну и что с того? Она мне нравится, и дело с концом. И я не позволю какому-то оборванцу вмешиваться в наши отношения только потому, что он ее муж, видите ли!..";
			link.l1 = "Позволю себе заметить, что Береговое Братство такие вот фортеля не поощряет.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Ты что, мораль мне тут читать надумал"+ GetSexPhrase("","а") +"? Береговое Братство к этому делу никакого отношения не имеет, так что твои разговоры ни к чему не приведут. Она моя, и точка!";
			link.l1 = "Не заводись, я просто поинтересовал"+ GetSexPhrase("ся","ась") +"... В общем, бывай, приятель.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Что тебе нужно, каналья?!!";
			link.l1 = "Я приш"+ GetSexPhrase("ел","ла") +" за женщиной, что ты украл у мужа. Вспомни " + XI_ConvertString("Colony"+npchar.quest.cribCity) + "! Ее зовут " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Дьявол!! Тебе не видать ее как своих ушей!";
			link.l1 = "Ха, идиот!! Свои уши я вижу в зеркале! А твои сейчас обрежу...";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "philistine_1"; //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Кто вы?";
			link.l1 = "Здравствуйте. Я приш"+ GetSexPhrase("ел","ла") +" за вами по поручению вашего мужа. Теперь, когда вы свободны, мне нужно отвезти вас к нему.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Неужели это не сон?! Это правда?!";
			link.l1 = "Чистейшая правда, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Слава Господу Всемогущему!!! Я готова, давайте быстрей уйдем отсюда!";
			link.l1 = "Хорошо, " + GetAddress_FormToNPC(NPChar) + ", готовьтесь к возвращению домой, к мужу.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Здравствуйте! Рад приветствовать капитана, коллегу, так сказать, на суше...";
			link.l1 = TimeGreeting() + " А я наш"+ GetSexPhrase("ел","ла") +" вас по делу.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Дело в том, что вас ищет ваш земляк, с которым вы отправились сюда из Старого света. " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ", знакомое имя?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ха, еще бы! А где он живет?";
			link.l1 = "В " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ". Я предлагал"+ GetSexPhrase("","а") +" ему отправиться со мной, но он отказался. Просит вас заехать к нему.";
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = "Конечно, я это сделаю. Большое вам спасибо!.. Вы знаете, по вашему виду я сказал бы, что вы пират!";
			link.l1 = "Так и есть. Но я сегодня добр"+ GetSexPhrase("ый","ая") +", так что тебе не о чем беспокоится. Всего хорошего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Все нормально, без проблем? Извините, я немного переживаю...";
			link.l1 = "Все в порядке, приятель.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting() + ". Что вам нужно от меня? Я всего лишь торговый капитан, и...";
			link.l1 = "Я знаю, приятель. Не нервничай так, говорят, это вредно для здоровья. Я к тебе по делу.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "По какому делу?";
			link.l1 = "Тебя ищет твой земляк " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Знаешь такого?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "О-о-о, нашелся все-таки! Очень хорошо... Вы меня извините за грубый прием, я, знаете ли, грешным делом подумал, что вы пират.";
			link.l1 = "Так и есть. Но тебе пока ничего не угрожает. Меня просили передать тебе сообщение, что я и сделал"+ GetSexPhrase("","а") +". Твой земляк, кстати, живет и работает в " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ".";
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Вот это да!.. Вы - "+ GetSexPhrase("благородный человек","благородная девушка") +". Спасибо вам!";
			link.l1 = "Не за что. Прощай и будь здоров, приятель.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Здравствуйте. Вы что-то хотели?";
			link.l1 = "Вас зовут " + GetFullName(npchar) + ", не так ли?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Да, это я.";
			link.l1 = "Это, конечно, звучит глупо, но ваша жена просила меня передать, что очень за вас волнуется.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ха! Ну, это понятно... Вообще-то я настолько закрутился с работой, что мне не до нее сейчас. Выгодные предложения следуют одни за другими, я не могу упускать возможную выгоду только потому, что моя жена волнуется.";
			link.l1 = "Это конечно, но вы могли хотя бы написать ей, что с вами все в порядке.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Да, вы правы. Немедленно ей отпишу!.. Спасибо вам огромное за участие в наших семейных делах!";
			link.l1 = "Не за что, дружище.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Здравствуйте. Чему обязан за честь видеть вас у себя на корабле?";
			link.l1 = "Вас зовут " + GetFullName(npchar) + ", не так ли?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Да, это я.";
			link.l1 = "Это, конечно, звучит глупо, но ваша жена просила меня передать, что очень за вас волнуется.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Фу, черт! А я, честно говоря, испугался - решил, что это знаменитый охотник за призами - Одноглазый Стид Хантер за мной увязался. Ну, хорошо, что ошибся...\nВы знаете, я настолько закрутился с работой, что мне не до нее сейчас. Выгодные предложения следуют одни за другими, я не могу упускать возможную выгоду только потому, что моя жена волнуется.";			
			link.l1 = "Это конечно, но вы могли хотя бы написать ей, что с вами все в порядке.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Да, вы правы. Я это обязательно сделаю в первом же порту на разгрузке... Спасибо вам огромное за участие в наших семейных делах!";
			link.l1 = "Не за что, дружище.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Еще раз примите мою благодарность...";
			link.l1 = "Да не стоит, все в порядке.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Рад видеть вас в этом городишке, капитан. Вам что-то нужно от меня?";
			link.l1 = ""+ GetSexPhrase("Знаете, капитан... Фуф, даже не знаю, как это сказать!","Да, нужно.") +"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+ GetSexPhrase("Говорите, как есть.","Интересно, и что же?") +"";
			link.l1 = ""+ GetSexPhrase("Хм, так и поступлю... В общем, у","У") +" меня к вам вопрос. Вы знакомы с дамой по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Хех, ну да, знаком. Имел, так сказать, несчастие общаться с ней. Вздорная дура, могу вам сказать...";
			link.l1 = "Гм... Так вот, эта вздорная дура наняла меня убить вас"+ GetSexPhrase(", дружище. Вот так-то..","") +".";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Ну, это уже просто смешно...";
			link.l1 = ""+ GetSexPhrase("Если бы не было так грустно... Сожалею, но за вашу","Ничего смешного в этом нет. За вашу") +" голову назначена награда. И я намерен"+ GetSexPhrase("","а") +" ее получить.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Хо-хо!.. Вы не шутите, капитан?";
			link.l1 = ""+ GetSexPhrase("Нет, друг мой...","Даже не думала!") +"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+ GetSexPhrase("Да какой ты мне друг, идиот?! Ты и капитаном-то назваться не можешь. Так, прихвостень на побегушках у вздорной фурии","Черт возьми! Одна вздорная фурия наняла другую! Что же это за дела такие творятся?") +"!";
			link.l1 = ""+ GetSexPhrase("Вот как?!","Ты использовал ее в своих корыстных целях, так что нечего удивляться тому, что она решила отомстить.") +"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+ GetSexPhrase("Ну а как ты хотел, чтобы я тебя называл? Хоть как назови, суть-то не изменится...","Женская солидарность, да?!") +"";
			link.l1 = ""+ GetSexPhrase("","Знаешь, пожалуй, и это тоже. ") +"Доставай свой клинок!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "С тобой у меня уже был разговор. "+ GetSexPhrase("Пошел вон, прохвост","Убирайся, злыдня") +"...";
			link.l1 = ""+ GetSexPhrase("Прохвост","Злыдня") +"?! Ну ладно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Рад видеть вас у меня на палубе, капитан. Зачем пожаловали?";
			link.l1 = "У меня к вам вопрос. Вы знакомы с дамой по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Хех, ну да, знаком. Имел, так сказать, несчастие общаться с ней. Вздорная дура, могу вам сказать...";
			link.l1 = "Хех, так вот эта вздорная дура наняла меня убить вас"+ GetSexPhrase(", дружище. Вот так-то..","") +".";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Хи-хи... Капитан, не смешите меня. Если у вас больше нет ко мне дел, то прощайте.";
			link.l1 = "Ну что же, прощайте. Но имейте в виду то, что я вам сказал"+ GetSexPhrase("","а") +".";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Обязательно, капитан, как же иначе?!";
			link.l1 = "Всего хорошего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Я больше не хочу говорить на эту тему, капитан. Это смешно.";
			link.l1 = "Ну, как знаете...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Что происходит, черт возьми?! Зачем вы напали на мой корабль?!";
			link.l1 = "По поручению "+ GetSexPhrase("некой дамы,","женщины") +" по имени " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Эта особа вам знакома?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Дьявол!!! Поверить не могу..."+ GetSexPhrase(""," Одна злобная фурия наняла другую!") +"";
			link.l1 = ""+ GetSexPhrase("А придется.","Пришло тебе время ответить за свои подлые делишки!") +"";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Ну что же, я так просто умирать не намерен. За разговор спасибо, он прибавил мне сил. "+ GetSexPhrase("Но прихвостня ","И подружку ") +"этой фурии я хочу все-таки отправить на тот свет!";
			link.l1 = "Попробуйте, что я еще могу сказать?..";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Рад видеть вас у меня на палубе. Я чем-то могу помочь вам?";
			link.l1 = "Наверное, да. Я ищу человека, по имени " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Этот человек - мой пленник, и я планирую получить за него хороший выкуп.";
			link.l1 = "Я хочу его получить.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Сожалею, но это невозможно. Если это все, то я прошу вас покинуть мой корабль.";
			link.l1 = "Хорошо, капитан, как скажете.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Мы уже говорили о моем пленнике. Ничего не изменилось.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Приветствую, капитан. Я чем-то могу вам помочь?";
			link.l1 = "Наверное, да. Я ищу человека, по имени " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Этот человек - мой пленник, и я планирую получить за него хороший выкуп.";
			link.l1 = "Я хочу его получить.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Сожалею, но это невозможно.";
			link.l1 = "Жаль...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Дьявол! Какого черта?!!";
			link.l1 = "Мне нужен твой пленник, по имени " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ха! Ну уж нет, только через мой труп...";
			link.l1 = "Как вам будет угодно.";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "burgher_1"; //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Кто вы?";
			link.l1 = "Я капитан " + GetFullName(pchar) + ". Вы не волнуйтесь, я приш"+ GetSexPhrase("ел","ла") +" за вами для того, чтобы отвезти к жене.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Черт возьми, неужели это не сон?!";
			link.l1 = "Уверяю вас, это не сон... Ну что же, дело сделано, теперь уходим отсюда.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//несчастный мушкетер
		case "OffMushketer":
			dialog.text = "Приветствую "+ GetSexPhrase("гостя","прекрасную гостью") +" в моем доме. Что вы хотели здесь?";
			link.l1 = "Познакомиться. Меня зовут капитан " + GetFullName(pchar) + ".";
			link.l1.go = "OffM_1";
		break;
		case "OffM_1":
			dialog.text = "Рад знакомству, капитан. Чем я могу вам помочь?";
			link.l1 = "Да так, ничем особенным... А вы по виду человек военный. Еще на службе состоите?";
			link.l1.go = "OffM_2";
		break;
		case "OffM_2":
			dialog.text = "Уже нет, уволен.";
			link.l1 = "Понятно. А кем были в армии?";
			link.l1.go = "OffM_4";
		break;
		case "OffM_4":
			dialog.text = "Мушкетером. Я был лучшим стрелком в полку!";
			link.l1 = "Ха, такие люди мне нужны. Не желаете пойти служить офицером ко мне в команду?";
			link.l1.go = "OffM_5";
		break;
		case "OffM_5":
			dialog.text = "Спасибо за предложение, но вынужден отказаться.";
			link.l1 = "Скажите, а почему? Если не секрет, конечно...";
			link.l1.go = "OffM_6";
		break;
		case "OffM_6":
			dialog.text = "Все дело в психической травме. Не могу брать в руки оружие!";
			link.l1 = "Странно все это. А как же вы воевали в армии?";
			link.l1.go = "OffM_7";
		break;
		case "OffM_7":
			dialog.text = "Понимаете, мне в свое время достался английский мушкет, каких мало. Два ствола, усовершенствованная казенная часть, позволяющая заряжать быстрее. В общем, настоящее произведение искусства, работа мастера.\n"+
				"И так я к этому оружию привязался, что другого ничего не признаю.";
			link.l1 = "И где этот чудо-мушкет сейчас?";
			link.l1.go = "OffM_8";
		break;
		case "OffM_8":
			dialog.text = "Эх-х, даже вспоминать больно... Когда я плыл сюда из Старого Света, на нас напали пираты. Я хотел открыть по ним огонь, и поверьте мне, уложил бы немало этих головорезов. Но наша же команда набросилась на меня и скрутила!..";
			link.l1 = "Поверь мне, они поступили правильно. Вы хотя бы остались живы.";
			link.l1.go = "OffM_9";
		break;
		case "OffM_9":
			dialog.text = "Жив, но без моего мушкета! А что это за жизнь!..";
			link.l1 = "Ну, может другой найдется, подобный...";
			link.l1.go = "OffM_10";
		break;
		case "OffM_10":
			dialog.text = "Найдется?.. Хм, послушайте, если вы найдете мой двуствольный мушкет, то я пойду к вам в офицеры. Обещаю.";
			link.l1 = "Ну что же, я вас понял"+ GetSexPhrase("","а") +". А кто захватил ваш корабль, когда это было?";
			link.l1.go = "OffM_11";
		break;
		case "OffM_11":
			dialog.text = "Было это уже пару лет назад, с тех пор и маюсь. Кто были те пираты - я не видел, лежал связанным с мешком на голове. Команда о какой-то стреле вопила, но что это такое - мне не известно.";
			link.l1 = "М-да, ситуация... Ну что же, как говорится, будем искать. Если мне ваш мушкет попадется, то обязательно принесу его сюда.";
			link.l1.go = "OffM_12";
		break;
		case "OffM_12":
			dialog.text = "Спасибо вам. Буду ждать с нетерпением.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			pchar.questTemp.mushket2x2 = true;
			AddQuestRecord("SeekDoubleMushket", "1");
			NextDiag.TempNode = "OffM_result";	
		break;

		case "OffM_result":
			dialog.text = "Вы нашли мой мушкет?";
			if (CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "Да, дружище, наш"+ GetSexPhrase("ел","ла") +". Вот он, двуствольный мушкет, другого такого нет.";
				link.l1.go = "OffM_result_1";
			}
			else
			{
				link.l1 = "Нет еще. Но я занимаюсь этим.";
				link.l1.go = "exit";
			}
		break;
		case "OffM_result_1":
			dialog.text = "Отлично! Ну, жизнь только начинается!";
			link.l1 = "Хорошо. Теперь я жду исполнения вашего обещания стать моим офицером.";
			link.l1.go = "OffM_result_2";
			TakeItemFromCharacter(pchar, "mushket2x2");
			Npchar.quest.OfficerPrice = sti(pchar.rank)*300;
		break;
		case "OffM_result_2":
			dialog.text = "Мое слово железное. Я готов. Только давайте обсудим размер моего гонорара. За свою верную службу я хочу получать " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + " в месяц.";
			link.l1 = "А вам не кажется, что это чересчур?";
			link.l1.go = "OffM_trade";
			link.l1 = "Ну, хорошо, я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_trade":
			dialog.text = "Нет, я стою гораздо больше.";
			link.l1 = "Ну, хорошо, я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_Ok":
			Npchar.quest.OfficerPrice.add = sti(pchar.rank)*1000;
			dialog.text = "Хорошо. Но это еще не все. Я требую единовременного пособия, так сказать. Поиздержался без работы, вот и надо оплатить долги. Думаю, что " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + " меня устроят.";
			link.l1 = "Чего?!!";
			link.l1.go = "OffM_Ok_1";
		break;
		case "OffM_Ok_1":
			dialog.text = "Того! И никак иначе... В общем, решайте.";
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = "Нет у меня таких денег.";
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = "Это очень дорого для меня.";
				link.l1.go = "OffM_noMoney";
				link.l2 = "Хорошо, я соглас"+ GetSexPhrase("ен","на") +".";
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
		case "OffM_noMoney":
			dialog.text = "Значит, приходите, как разбогатеете. Удачи.";
			link.l1 = "Спасибо...";
			link.l1.go = "exit";
		break;
		case "OffM_Ok_3":
			dialog.text = "Вот, теперь совсем другое дело! Я готов вам служить верой и правдой.";
			link.l1 = "Отлично. Добро пожаловать в команду.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			AddQuestRecord("SeekDoubleMushket", "3");
			CloseQuestHeader("SeekDoubleMushket");
			AddMoneyToCharacter(pchar, -sti(Npchar.quest.OfficerPrice.add));
			npchar.model = "MusketeerEnglish_2";
			npchar.model.animation = "mushketer";
			npchar.MusketerDistance = 5;
			npchar.greeting = "Gr_questOfficer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
		case "OffM_TWO":
			dialog.text = "Ну что, как там у вас дела с финансами? Напомню, что я хочу " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + " единовременного пособия и " + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + " ежемесячного заработка.";
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = "Нет, не потяну пока...";
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = "Это очень дорого для меня.";
				link.l1.go = "OffM_noMoney";
				link.l2 = "Хорошо, я соглас"+ GetSexPhrase("ен","на") +".";
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_" + npchar.index, "", "man", "man", Rank, iNation, -1, true, F_PIRATE));
	switch (npchar.quest.SeekCap)
	{
		case "manSlave": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
		break;
		case "manRapeWife": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
		break;
		case "manFriend": 
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			sld.fraction = F_TRADER;
		break;
		case "womanHasband": 
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			sld.fraction = F_TRADER;
		break;
		case "womanRevenge": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
		break;
		case "womanPirates": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.gem = GenQuestCitizen_GenerateGem(); //камешки
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestCitizen_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry4"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry17"; 
		break;
	}
	return itemID;
}
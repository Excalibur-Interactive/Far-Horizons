// диалоги по ивенту "Моряки желают развлечений"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "sailor_decline_exit":
			DialogExit();
			AddDialogExitQuestFunction("SailorEvent_DeclineExit");
		break;
		
		case "sailor_default_exit":
			DialogExit();
			AddDialogExitQuestFunction("SailorEvent_DefaultExit");
		break;
		
		case "sailor_out_of_brothel":
			DialogExit();
			Pchar.Event.SailorEvent = "BrothelOut"
			AddDialogExitQuestFunction("SailorEvent_GetOut");
		break;
		
		case "sailor_pier1":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i = 1; i < 3; i++)
			{
				sld = characterFromID("Sailor_" + i);
				CharacterTurnByChr(sld, pchar);
			}
			if(sti(TEV.SB_Counter) == 2)
			{
				switch(rand(2))
				{
					case 0:
						TEV.SB_Counter.Var = 0;
						dialog.text = "Капитан, у нас к вам есть одна просьба...";
						link.l1 = "Bien sur! И чисто случайно в этой колонии, где мы бросили якорь, находится бордель. Совпадение? Очень сомневаюсь."; //sûr
						link.l1.go = "sailor_pier5_1";
					break;
					
					case 1:
						TEV.SB_Counter.Var = 1;
						dialog.text = "Капитан, парни соскучились по женской ласке...";
						link.l1 = "Можешь не продолжать. Я знаю, что вам нужно.";
						link.l1.go = "sailor_pier5_1";
					break;
					
					case 2:
						TEV.SB_Counter.Var = 2;
						dialog.text = "Капитан, разрешите обратиться к вам с просьбой?";
						link.l1 = "Обращайтесь, только я по вашим голодным взглядам уже вижу, что вам нужно.";
						link.l1.go = "sailor_pier5_1";
					break;
				}
				break;
			}
			dialog.text = "(взволнованно) Капитан, разрешите обратиться к вам...";
			link.l1 = "Quoi?! Что случилось? Обращайся.";
			link.l1.go = "sailor_pier2";
		break;
		
		case "sailor_pier2":
			dialog.text = "Тут такое дело... Не знаю, с чего начать...";
			link.l1 = "Говори же, не тяни змею за хвост!";
			link.l1.go = "sailor_pier3";
		break;
		
		case "sailor_pier3":
			dialog.text = "В общем, мы с парнями хотели бы потратить в этом городе заработанное серебро. Здесь есть... (запинаясь) одно место, куда мы хотели бы сходить.";
			link.l1 = "Clair, в бордель вам нужно, да? И вы боитесь спрашивать, потому что я тоже женщина.";
			link.l1.go = "sailor_pier4";
		break;
		
		case "sailor_pier4":
			dialog.text = "Да-да, всё верно, капитан.";
			link.l1 = "Запомните, я в первую очередь для вас - капитан, а уже затем всё остальное.";
			link.l1.go = "sailor_pier5";
		break;
		
		case "sailor_pier5":
			dialog.text = "Так точно, мы запомним... Ну, так что, капитан, вы позволите нам побыть в городе пару деньков? Чтобы мы могли как следует покувырк... Эээм... Отдохнуть. А затем снова в бой!";
			link.l1 = "(вздох) Bien. Можете отдохнуть пару дней.";
			link.l1.go = "sailor_agree1";
			if(sti(pchar.money) >= GetPartyCrewQuantity(pchar, true)*30)
			{
				link.l2 = "Знаете, у меня есть идея получше. Я беру все расходы на себя, а вы управитесь с 'отдыхом' за несколько часов.";
				link.l2.go = "sailor_default1";
			}
			link.l3 = "Нет, у нас есть много других дел. Придётся вам потерпеть, ребята.";
			link.l3.go = "sailor_decline_exit";
		break;
		
		case "sailor_pier5_1":
			switch(sti(TEV.SB_Counter.Var))
			{
				case 0:
					dialog.text = "(улыбаясь) Вы очень догадливы, капитан. Мы, правда, хотели попросить вас дать нам отдохнуть пару деньков. Каков ваш ответ?";
				break;
				
				case 1:
					dialog.text = "Значит, вы позволите нам отдохнуть пару дней в борделе?";
				break;
				
				case 2:
					dialog.text = "Правда, капитан? Тогда вы разрешите нам отдохнуть пару дней с девушками в борделе?";
				break;
			}
			link.l1 = "Bien. Вы можете отдохнуть и потратить свои деньги.";
			link.l1.go = "sailor_agree1";
			if(sti(pchar.money) >= GetPartyCrewQuantity(pchar, true)*30)
			{
				link.l2 = "У меня есть идея получше. Я плачу за вас деньги, а вы удовлетворяете все свои потребности всего за несколько часов. Вас это устроит?";
				link.l2.go = "sailor_default1_1";
			}
			link.l3 = "Нет, у нас есть много других дел.";
			link.l3.go = "sailor_decline_exit";
		break;
		
		case "sailor_agree1":
			dialog.text = "(радостно) Спасибо, капитан. Вся команда будет вам безмерно благодарна.";
			link.l1 = "Только будьте ласковы с ними. Если я узнаю, что хоть один из вас ударил или как-то иначе обидел девушку, то следующий выход в море этот негодяй проведёт за бортом, развлекаясь с акулами. Вам ясно?";
			link.l1.go = "sailor_agree2";
		break;
		
		case "sailor_agree1_1":
			dialog.text = "Спасибо и на этом, капитан. Команда всё равно будет вам безмерно благодарна.";
			link.l1 = "Только будьте ласковы с ними. Если я узнаю, что хоть один из вас ударил или как-то иначе обидел девушку, то следующий выход в море этот негодяй проведёт за бортом, развлекаясь с акулами. Вам ясно?";
			link.l1.go = "sailor_agree2";
		break;
		
		case "sailor_agree2":
			dialog.text = "(улыбаясь) Приказ ясен - быть ласковыми! Разрешите порадовать парней на корабле?";
			link.l1 = "Передайте там, что я тоже остаюсь пока на берегу. Вахта должна сменяться регулярно, так что кое-кому придётся на время воздержаться от блуда. Свободны. Уйдите с глаз моих, пока я не передумала. Marche! En avant!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SailorEvent_AgreeExit");
		break;
		
		case "sailor_default1":
			dialog.text = "(радостно) Капитан, я не верю своим ушам! Вы оплатите наш отдых?";
			link.l1 = "Да, ты не ослышался, я оплачу ваш отдых. Возвращайтесь на корабль. Скоро ваши 'дамы сердца' будут там.";
			link.l1.go = "sailor_default_exit";
			link.l2 = "Знаешь, я передумала тратить свои деньги, но я позволю вам отдохнуть, как вы и хотели изначально.";
			link.l2.go = "sailor_agree1_1";
			link.l3 = "Нет, я передумала. У нас слишком много дел, чтобы тратить время на ваши прихоти. Возвращайтесь на корабль. Marche! En avant!";
			link.l3.go = "sailor_decline_exit";
		break;
		
		case "sailor_default1_1":
			dialog.text = "Конечно, устроит. Каждый будет рад получить девушку, не потратив при этом ни гроша.";
			link.l1 = "Хорошо, тогда возвращайтесь на корабль и ждите, когда к вам пришлют девушек из борделя.";
			link.l1.go = "sailor_default_exit";
			link.l2 = "Знаешь, я передумала платить за вас, но я разрешаю вам остаться в борделе на пару дней.";
			link.l2.go = "sailor_agree1_1";
			link.l3 = "Я тут вспомнила, что у нас слишком много дел. Возвращайтесь на корабль. Marche! En avant!";
			link.l3.go = "sailor_decline_exit";
		break;
		
		case "sailor_in_brothel":
			NextDiag.TempNode = "sailor_in_brothel";
			switch(rand(2))
			{
				case 0:
					dialog.text = "Капитан, спасибо вам огромное, что позволили нам отдохнуть. Кто знает, что ждёт нас в море.";
					link.l1 = "Развлекайтесь на здоровье. Только не забывайте сменять вахтенных. Дисциплина на корабле должна соблюдаться.";
					link.l1.go = "exit";
					link.l2 = "К сожалению, я вынуждена прервать ваш отдых. Attention! Все живо на корабль!";
					link.l2.go = "sailor_out_of_brothel"; //to_do: пусть хоть попросят остаться, а не молча выполнят приказ, слезинки не уронив
				break;
				
				case 1:
					dialog.text = "Давненько мы так не веселились, капитан. Не желаете ли выпить с нами?";
					link.l1 = "Нет, парни, в другой раз. Веселитесь сами, только помните, что скоро снова в море.";
					link.l1.go = "exit";
					link.l2 = "Сейчас не до пьянок. Приказываю всем вернуться на корабль! Va! Allez!";
					link.l2.go = "sailor_out_of_brothel";
				break;
				
				case 2:
					dialog.text = "Сейчас выпью, а затем, когда настанет моя очередь, поднимусь наверх с одной из этих красоток... Капитан, рад вас видеть!";
					link.l1 = "Смотри, не переусердствуй с алкоголем, а то опозоришь всю команду.";
					link.l1.go = "exit";
					link.l2 = "Увы, сегодня не твой день, приятель. Всем вернуться на борт!";
					link.l2.go = "sailor_out_of_brothel";
				break;
			}
		break;
	}
}

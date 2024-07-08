// диалог дворян
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Хм. Ты ходишь под флагом "+NationNameGenitive(sti(pchar.nation))+", приятель. Какого чёрта ты делаешь здесь, в нашем городе? Убирайся!", 
					"Я не желаю, чтобы меня заподозрили в связи с "+NationNameAblative(sti(pchar.nation))+"! Проваливай, не то точно страже доложу!", 
					"Даю тебе последний шанс убраться прочь. Потом - пеняй на себя.",
					"Ну, я тебя предупреждал. Теперь ты поплатишься за свою дерзость, негодяй!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Тоже мне, патриот выискался...", 
					"Ладно-ладно, не кипятись. Ухожу.",
					"Не шуми, я уже ушёл...", 
					"Что?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Ну надо же! И как только стража позволяет таким мерзавцам расхаживать по нашему городу? Невероятно...", 
					"Проваливайте, я не желаю даже разговаривать с вами! Висельник...", 
					"Даю тебе последний шанс убраться прочь. Потом - пеняй на себя.",
					"Ну, я тебя предупреждал. Теперь ты поплатишься за свою дерзость, негодяй!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Но-но, сударь, проявляйте больше уважения!", 
					"На себя посмотри, святоша...",
					"Не шуми...", 
					"Что?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Здравствуйте, "+GetAddress_Form(NPChar)+". Вы что-то от меня хотели?", "Что вам угодно, сударь?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Я не задержу вас надолго, просто хочу спросить у вас...";
				link.l1.go = "quests";
				link.l2 = "В принципе, ничего.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Что? Опять? Нет у меня на вас времени. Поищите для болтовни кого-нибудь другого. Тут полно бездельников, слоняющихся по улицам. А мне пора - вечером приём у губернатора, надо готовиться...", 
				"Нет, это уже начинает действительно утомлять! Вы что, не понимаете с первого раза? Вы тугодум?", 
					"Сударь, я начинаю подозревать то, что вы не тупица, а банальный невежа и хам. Предупреждаю: не лезьте на рожон!",
					"Так, ну всё. Теперь я проучу тебя, наглец!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Понятно. Всего доброго.", 
					"Да-да, я помню, просто забыл спросить вот что...",
					"Вы меня неправильно поняли...", 
					"Что?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}
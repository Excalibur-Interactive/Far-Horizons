void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

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
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":		
			dialog.text = RandPhraseSimple("Я начальник тюрьмы. Что вам нужно здесь?", "Что вам нужно? Зачем вы явились в тюрьму?");
			link.l1 = "Да ничего особенного, осматриваю город, знаете ли. Вот и забрел"+ GetSexPhrase("","а") +" сюда по случаю.";
			link.l1.go = "exit";
			link.l2 = "Хочу поговорить по делу.";
			link.l2.go = "quests";

			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Я хочу пройти внутрь тюрьмы.";
				link.l4.go = "ForGoodMove";		
			}
		NextDiag.TempNode = "First_officer";
		break;

        case "ForGoodMove":
			dialog.text = NPCStringReactionRepeat("Но зачем вам это? Поверьте мне, там нет ничего достойного внимания, одни воры и бандиты.", "Мы уже обсуждали это ваше желание.", 
				"Опять о том же? Уже дважды мы с вами говорили об этом!", "Гм, опять...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Тем не менее, я хотел"+ GetSexPhrase("","а") +" бы провести экскурс по вашим казематам. Мне очень интересно!", "Да, именно так. Но я хотел"+ GetSexPhrase("","а") +" еще поговорить на эту тему.", 
				"Ну, может в третий раз...", "Надежда посмотреть на ваших узников не покидает меня...", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = (rand(15)+10)*100;
			if (sti(colonies[FindColony(npchar.city)].jail) && sti(pchar.money) >= sti(pchar.questTemp.jailCanMove.money))
			{
				dialog.text = "Ну что же, не вижу причины вам отказывать. " + FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.money)) + " - и пока вы не покинете тюрьму, вы можете беспрепятственно ходить по коридорам и даже разговаривать с заключенными.";
				link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +", вот ваши монеты!";
				link.l1.go = "ForGoodMove_agree";
				link.l2 = "Не пойдет, слишком дорого для бесцельного хождения по коридорам.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Нет, это категорически запрещено уставом. Вам здесь что, цирк? Уходите, и не отвлекайте меня от несения службы.", "Я не могу позволить расхаживать по тюрьме посторонним людям. Прошу вас, не мешайте мне!");
				link.l1 = "Хорошо, как скажете...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Ну что же, вы можете приступать к своему, так сказать, экскурсу...";
			link.l1 = "Спасибо, офицер.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.money));
		break;
		
		//---------------- Протектор ------------------
        case "First_protector":
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Вы можете пройти, начальник разрешил...", "Получен приказ начальника тюрьмы. Вы можете свободно проходить.");
				link.l1 = "Ну, вот и чудно.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Проходить далее без разрешения начальника тюрьмы категорически запрещено!", "Я подчиняюсь только начальнику тюрьмы. Если ты попытаешься пройти дальше без его разрешения - тебе конец!");
				link.l1 = RandPhraseSimple("Понятно", "Ясно") + ", солдат.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Я на посту, не отвлекайте меня.", "Проходите мимо, я не могу с вами разговаривать.");
			link.l1 = "Хорошо, солдат.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Хо-хо, до чего же весело!!", "Режь их, "+ GetSexPhrase("приятель","подруга") +", режь!!!", "Эх, дьявол! Уж не думал, что увижу труп своего надсмотрщика!");
				link.l1 = RandPhraseSimple("Хех!", "Аргх...");
				link.l1.go = "NoMoreTalkExit";
				if (drandEx(10, true) > 7 && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander"))
				{
					dialog.text = RandPhraseSimple("Постой, "+ GetSexPhrase("дружище","подруга") +"!! Выпусти меня!", "Послушай, "+ GetSexPhrase("приятель","подруга") +", будь так добр"+ GetSexPhrase("","а") +", открой камеру.");
					link.l1 = "С какой это стати?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Меня взяли за грабеж, дело шьют...", "Агрх, холен"+ GetSexPhrase("ый","ая") +" ты... Тебя бы ко мне в камеру на недельку! Кхе-хе-хе...", "Я ни в чем не виноват!");
				link.l1 = RandPhraseSimple("Заткнись!", "Мне нет до тебя дела...");
				link.l1.go = "NoMoreTalkExit";
				if (drandEx(10, true) > 7 && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn))
				{
					dialog.text = RandPhraseSimple("Постой, "+ GetSexPhrase("приятель","подруга") +", не проходи мимо моей камеры так быстро!", "Не торопись, "+ GetSexPhrase("дружище","подруга") +", давай поговорим.");
					link.l1 = "С какой это стати?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
	}
}

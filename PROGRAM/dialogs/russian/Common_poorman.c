#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Здравствуйте. Меня зовут " + GetFullName(npchar) + ". Не думаю, что вам было бы приятно со мной познакомиться, но, возможно, вы запомните мое имя...", 
					"Приветствую вас, " + GetAddress_Form(NPChar) +  ". Меня зовут " + GetFullName(npchar) + ".", 
					"Мое имя - " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". Рад с вами познакомиться.");
				link.l1 = RandPhraseSimple("Приветствую.", "Здравствуйте.");
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Эх, вот видишь, до чего докатился...", 
					"Жить подаянием непросто...", 
					"Хотелось бы мне вырваться из нищеты!",
					"Опять ты?..", "block", 1, npchar, Dialog.CurrentNode);
				//----------------------------------------------------------------
				link.l1 = HeroStringReactionRepeat("Вижу. Ну, ничего страшного.", 
					"Оно и понятно. На эти деньги не разгуляешься, поди...",
					"Тогда тебе нужно не протирать здесь штаны, а что-то делать для этого.", 
					"Ага. Неужели "+ GetSexPhrase("надоел","надоела") +"?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Что тебе нужно?", "Чего ты хочешь?");
				link.l2.go = "Whants";
				link.l3 = LinkRandPhrase("Что-нибудь интересное мне расскажешь?", 
					"Что нового в городе?", "Эх, с удовольствием "+ GetSexPhrase("послушал","послушала") +" бы последние сплетни...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Да нет, почему сразу "+ GetSexPhrase("надоел","надоела") +"? Я не особо занят, как ты "+ GetSexPhrase("сам","сама") +" видишь...", 
				"Не "+ GetSexPhrase("надоел","надоела") +", но порядком "+ GetSexPhrase("утомил","утомила") +". Я хоть и нищий, но тоже человек.");
			link.l1 = "Хех, ясно...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Хм, " + GetAddress_Form(NPChar) +  ", о вас ходят нехорошие слухи. Но я верю в людей, даже в таких, как вы. Я прошу дать мне денег на еду и питье, сжальтесь.",
					"Прошу вас, " + GetAddress_Form(NPChar) +  "! Не обойдите вниманием несчастного человека, подайте на пропитание...");
				link.l1 = RandPhraseSimple("Ничего тебе не дам.", "Обойдешься.");
				link.l1.go = "exit";
				Link.l2 = "Хорошо. И сколько тебе нужно денег?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("От тебя? Ничего.", "Ничего не нужно, " + GetAddress_Form(NPChar) + ", спасибо.");
				link.l1 = RandPhraseSimple("Хм, ну ладно.", "Знать хорошо живется тебе, приятель.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "И от гроша ломаного не откажусь, " + GetAddress_Form(NPChar) + ". Сколько вам позволят ваши кошелек и милосердие...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Грешно смеяться надо больными людьми...";
				link.l1 = "Ха-ха-ха, а ты что думал, юродивый, я тебе денег дам?!";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Спасибо за " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". Я куплю хлеба на эти деньги...";
				link.l1 = "Давай, иди подкрепись, бродяга.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100 && iTemp <= 1000)
			{
				dialog.text = "Спасибо вам, " + GetAddress_Form(NPChar) + ". Этих денег мне хватит на неделю!";
				link.l1 = ""+ GetSexPhrase("Рад был","Рада была") +" помочь.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Благодарю вас, " + GetAddress_Form(NPChar) + ". Я всем расскажу о вашей доброте!";
				link.l1 = "Ну, это не обязательно...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 5000 && iTemp <= 50000)
			{
				dialog.text = "Спасибо вам, досточтим"+ GetSexPhrase("ый","ая") +" " + GetAddress_Form(NPChar) + ". Да хранит вас Господь...";
				link.l1 = "Да, покровительство Господа мне не помешает уж точно!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 50000 && iTemp <= 100000)
			{
				dialog.text = "Спасибо вам, "+ GetSexPhrase("досточтимый","досточтимая") +" " + GetAddress_Form(NPChar) + ". Желаю вам удачи!";
				link.l1 = "Спасибо, приятель.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100000)
			{
				dialog.text = "Послушайте, " + GetAddress_Form(NPChar) + ", вы в своем уме? Вы отдаете мне " + FindRussianMoneyString(iTemp) + "! Я не возьму такие деньги, чувствую, здесь какой-то подвох... Уходите!";
				link.l1 = "Ну, как знаешь...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
		break;
	}
}

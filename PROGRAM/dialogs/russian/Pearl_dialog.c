
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Не о чем говорить!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ==> глава поселения
		case "HeadMan":
			NextDiag.TempNode = "HeadMan";
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Добро пожаловать к нам на промысел. Рад видеть подданн"+ GetSexPhrase("ого","ую") +" " + NationNameGenitive(sti(npchar.nation)) + ". Могу я узнать ваше имя?"; 
				link.l1 = "Меня зовут " + GetFullName(pchar) + ". Я капитан собственного судна.";
				link.l1.go = "HeadMan_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Рад вас видеть вновь у себя в доме. Вы по делу?", 
					"Опять вы? Мы уже все проговорили, капитан.", 
					"Капитан, вам еще что-нибудь нужно?",
					"Капитан, я прошу вас не отвлекать меня!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Нет, " + GetAddress_FormToNPC(NPChar) + ", просто так заскочил"+ GetSexPhrase("","а") +"...", 
					"Да, конечно.",
					"Нет, " + GetAddress_Form(NPChar) + ", простите...", 
					"Хорошо...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";			
			}
		break;

		// >------- жемчужный генератор Шарпа
		case "HeadMan_1":
			dialog.text = "Могу я узнать, что вы делаете в этой глуши?";
			link.l1 = "Обследую территории, возможно, в будущем эти знания мне пригодятся.";
			link.l1.go = "HeadMan_2";
		break;
		case "HeadMan_2":
			dialog.text = "Значит, вы "+ GetSexPhrase("исследователь","исследовательница") +". Что же, великолепно. Хочу ввести вас в курс дела относительно существующего у нас положения вещей.";
			link.l1 = "Слушаю внимательно.";
			link.l1.go = "HeadMan_3";
		break;
		case "HeadMan_3":
			dialog.text = "Жемчужные промыслы в данный момент принадлежат " + NationNameGenitive(sti(npchar.nation)) + ", поэтому никто не может здесь покупать или продавать жемчуг.";
			link.l1 = "Понятно.";
			link.l1.go = "HeadMan_4";
		break;
		case "HeadMan_4":
			dialog.text = "Если вы попытаетесь проникнуть в мои сундуки - кара постигнет вас незамедлительно.";
			link.l1 = "Это тоже понятно.";
			link.l1.go = "HeadMan_5";
		break;
		case "HeadMan_5":
			dialog.text = "Ну что же, великолепно. Примите мои заверения в искреннем расположении к вам, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "Благодарю вас.";
			link.l1.go = "exit";
		break;
		// ==> часовой у поселения
		case "GuardMan":
			NextDiag.TempNode = "GuardMan";
			dialog.text = NPCStringReactionRepeat("Здравствуйте! Позвольте представиться, меня зовут " + GetFullName(npchar) + ". Моя задача - предупредить поселение ловцов жемчуга о возможном нападении. Пираты, знаете ли... А вы кто?", 
				"Приветствую еще раз!", 
				"Стою тут один целыми днями, скучно, поговорить не с кем...",
                "Эх, черт возьми, приятная отдушина в наряде!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Меня зовут " + GetFullName(pchar) + ". Я капитан, осматриваю эти земли.", 
				"И я тебя тоже...",
                "Понимаю.", 
				"Хех...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GuardMan_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "GuardMan_1":
			dialog.text = "Если вы в наше поселение, то добро пожаловать.";
			link.l1 = "Спасибо, приятель.";
			link.l1.go = "GuardMan_2";
		break;
		case "GuardMan_2":
			chrDisableReloadToLocation = false;
			npchar.quest.TalkOk = true; //флаг разговор состоялся, все ОК.
			LAi_SetCitizenTypeNoGroup(npchar);
			DialogExit();
		break;

		case "GuardManAllarm":
			dialog.text = "Тревога!! Это пират!!!";
			link.l1 = "Дьявол! Надо было тебя прикончить...";
			link.l1.go = "GuardManAllarm_1";
		break;
		case "GuardManAllarm_1":
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
		break;
		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Приветствую! Меня зовут " + GetFullName(npchar) + ". Чем я могу тебе помочь?", 
				"Приветствую еще раз!", 
				"В нашей глуши гости очень редки...",
                "Эх, приятно поболтать с новым человеком! А то эти морды уже опротивели.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да ничем особенным...", 
				"И я тебя тоже...",
                "Понимаю.", 
				"Хех...", npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Мы тут жемчуг добываем, служим " + NationNameGenitive(sti(npchar.nation)) + ", такое вот дело...";
			link.l1 = "Да, я в курсе...";
			link.l1.go = "exit";
			link.l2 = "Слушай, а нельзя ли прикупить немного этих безделушек у производителя, так сказать, а?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Да нет, что ты!!! За кражу даже одной маленькой жемчужины - смерть!";
				link.l1 = "Хех, порядки тут у вас жестокие...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "У нас с этим делом жестко, можно запросто лишиться головы. Я этим не занимаюсь, но могу посоветовать тебе обратиться к местным индейцам, что работают вместе с нами. Им есть куда бежать в случае чего, они посмелее нас будут...";
				link.l1 = "Понятно, ну спасибо тебе.";
				link.l1.go = "exit";
			}
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Бледнолицый","Белая скво") +" хочет говорить?", 
				"Снова ты, "+ GetSexPhrase("бледнолицый","белая скво") +".", 
				""+ GetSexPhrase("Бледнолицый любит говорить. Он похож на скво.","Белая скво любит говорить.") +"",
                "Духи привели ко мне бледнолиц"+ GetSexPhrase("его брата","ую сестру") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да.", 
				"Да, снова я.",
                "Очень поэтично.", 
				"Я тоже рад"+ GetSexPhrase("","а") +" тебя видеть.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Говори, зачем приш"+ GetSexPhrase("ел","ла") +".";
			link.l1 = "Да ничего особенного, послушать тебя хотел"+ GetSexPhrase("","а") +"...";
			link.l1.go = "exit";
			link.l2 = "У тебя есть жемчуг на продажу?";
			link.l2.go = "IndPearlMan_2";
		break;
		
		//продажа жемчуга
		case "IndPearlMan_2":
			if (!CheckAttribute(npchar, "quest.pearl")) npchar.quest.pearl = rand(1);
			if (sti(npchar.quest.pearl) == 0 || CheckAttribute(pchar, "quest.PearlToShore_ForSale.id"))
			{
				dialog.text = "Почему я должен развязать свой язык перед "+ GetSexPhrase("бледнолицым","бледнолицей") +"? Нет.";
				link.l1 = "Ничего не скажешь? Ну, как знаешь...";
				link.l1.go = "exit";
			}
			else
			{
				bOk = false;
				int num = FindNearCharacters(npchar, 5.0, -1.0, -1.0, 1.0, false, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						iTemp = chrFindNearCharacters[i].index;
						if (iTemp == GetMainCharacterIndex()) continue;
						sTemp = characters[iTemp].id;
						if (findsubstr(sTemp, "FightMan" , 0) != -1)
						{
							bOk = true;
							break;
						}
					}
				}				
				if (bOk)
				{
					dialog.text = "У меня есть слезы богов. А бледнолицый лает, как собака, все слышат, все хотят дать пинка. Я ухожу...";
					link.l1 = "Чего?..";
					link.l1.go = "IndPearlMan_4";
				}
				else
				{
					dialog.text = "У меня есть слезы богов. Приходи к большой воде рядом, я буду там до первой луны.";
					link.l1 = "Понятно. Ближайшая бухта, до полуночи. Приду обязательно.";
					link.l1.go = "IndPearlMan_3";
				}
			}
		break;
		case "IndPearlMan_3":
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "IndPearlMan_Sale";
			LAi_SetActorTypeNoGroup(NPChar);
			if (npchar.location == "Pearl_town_2")
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore51", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			else
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore49", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			pchar.quest.PearlToShore_ForSale.idx = npchar.index;
			npchar.quest.Pearl.bigQty = rand(30) + 10;
			npchar.quest.Pearl.smallQty = rand(60) + 20;
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		case "IndPearlMan_4":
			npchar.LifeDay = 0;
			LAi_group_Attack(NPChar, Pchar);
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			DialogExit();
		break;

		case "IndPearlMan_Sale":
			dialog.text = "Ты "+ GetSexPhrase("пришел","пришла") +"...";
			link.l1 = "Ну да, а цена какая?";
			link.l1.go = "IndPearlMan_Sale_1";
		break;
		case "IndPearlMan_Sale_1":
			dialog.text = "Десять - за большую слезу, пять - за маленькую.";
			link.l1 = "Беру, сколько у тебя есть?";
			link.l1.go = "IndPearlMan_Sale_2";
			link.l2 = "Нет, не буду брать, передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_2":
			dialog.text = npchar.quest.Pearl.bigQty + " большая, " + npchar.quest.Pearl.smallQty + " маленькая.";
			link.l1 = "Хорошо, беру все!";
			link.l1.go = "IndPearlMan_Sale_3";
		break;
		case "IndPearlMan_Sale_3":
			int iTemp = (sti(npchar.quest.Pearl.bigQty)*10) + (sti(npchar.quest.Pearl.smallQty)*5);
			if (sti(pchar.money) >= iTemp)
			{
				dialog.text = "Духи улыбнулись мне, я доволен...";
				link.l1 = "Бывай, приятель...";
				AddMoneyToCharacter(pchar, -iTemp);
				TakeNItems(pchar, "jewelry11", sti(npchar.quest.Pearl.bigQty));
				TakeNItems(pchar, "jewelry12", sti(npchar.quest.Pearl.smallQty)); 
			}
			else
			{
				dialog.text = "Ты "+ GetSexPhrase("должен","должна") +" мне " + iTemp + " денег. У тебя нет денег, у меня нет слез богов. Прощай.";
				link.l1 = "Эх, жаль...";
			}
			link.l1.go = "IndPearlMan_Sale_Out";	
		break;
		case "IndPearlMan_Sale_Out":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			DialogExit();
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", -1);
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break; 
	}
}

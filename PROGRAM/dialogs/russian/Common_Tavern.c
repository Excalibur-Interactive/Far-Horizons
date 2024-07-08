#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират!","") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "exit";
				break;
			}				
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = "Добро пожаловать в таверну '" + XI_ConvertString(NPChar.City + "TavernName") + "', " + GetAddress_Form(NPChar) + ". Еда, выпивка и развлечения - всё по умеренным ценам! Меня зовут " + GetFullName(npchar) + ", я владелец этой таверны.";
				Link.l1 = "" + TimeGreeting() + ", " + npchar.name + ". Я " + GetFullName(pchar) + ", капитан корабля '" + pchar.ship.name + "'.";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = LinkRandPhrase("Эй, " + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    "О, какие у нас гости! Рад видеть вас, " + GetAddress_Form(NPChar) + " " + PChar.name + ". Таверна '" + XI_ConvertString(NPChar.City + "TavernName") + "' всегда к вашим услугам.",
                                    "Хорошо, что вы заглянули ко мне, " + GetFullName(pchar) + ". Каков будет сегодня ваш заказ?");
				Link.l1 = "Есть на острове парни, готовые уйти в плавание?";
				Link.l1.go = "crew hire";
				Link.l2 = "Я надеюсь, ты сможешь ответить на пару вопросов.";
				Link.l2.go = "int_quests";
				Link.l3 = pcharrepphrase("Есть ли в твоём клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
			    Link.l3.go = "room";
				Link.l4 = "Пожалуй, загляну к тебе попозже.";
			    Link.l4.go = "exit";
			}
		break;
		
		case "Meeting":
			dialog.Text = LinkRandPhrase("Внимательно слушаю вас, капитан.","Что вам предложить, капитан?","Слушаю, кэп! Каков будет ваш заказ?");
			Link.l1 = "Мне нужна команда, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", давай поговорим...";
			Link.l2.go = "int_quests";
			Link.l3 = pcharrepphrase("Есть ли в твоём клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
			Link.l3.go = "room";
			Link.l4 = "Пожалуй, загляну к тебе попозже.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "А на что тебе матросы? Что-то не вижу твоего корабля в порту.";
				link.l1 = RandPhraseSimple("Точно... я его пришвартовал"+ GetSexPhrase("","а") +" не в том месте.", "Забыл"+ GetSexPhrase("","а") +" войти в порт...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Обычно у меня в таверне полно людей, желающих стать матросами, но сейчас слишком поздно, и они начнут появляться только утром. Может быть, вы хотите снять комнату, и подождать их?";
				link.l1 = "Хорошо. У тебя есть свободные комнаты?";
				link.l1.go = "room";
				link.l2 = "Меня не интересует комната на данный момент. До встречи.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "А ты думаешь, к тебе кто-то пойдет, когда ты с нами во вражде? Скажи спасибо, что стражу не зову.";
					link.l1 = "Спасибо.";
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Извините, но сейчас нет никого. Все ушли с отважным кэпом " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "Эх, жаль!";
						link.l1.go = "exit";
					}
					else
					{
						if((Partition_GetSetting("Partition_on") == true))
						{	
							if((Partition_GetSetting("Part_Crew") == 0) || GetPartitionAmount("CrewPayment") > 0)
							{
								dialog.text = "Капитан, поговаривают, что вы скуповаты. У меня нет желающих пойти в вашу команду.";
								link.l1 = "Понятно...";
								link.l1.go = "exit";
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();							
							}
						}
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();
						}
					}
				}
			}
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Я весь внимание.";
			//homo 15/06/06 слухи
			link.l1 = LinkRandPhrase("Расскажи мне последние новости?","Что новенького в этих краях?",
                                    "Как течет жизнь на суше?");
			link.l1.go = "rumours_tavern";
			//homo
			link.l2 = "Я по другому делу.";
			link.l2.go = "quests";
			link.l3 = "Спасибо, ничего. До свидания.";
			link.l3.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Сейчас комната занята, " + GetAddress_Form(NPChar) + ", ничем не могу помочь.";
				link.l1 = "Жаль, очень жаль...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "На какой срок вы планируете остановиться?";
			if(!isDay())
			{
				link.l1 = "До утра.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "До ночи.";
				link.l1.go = "room_night";
				link.l2 = "До следующего утра.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Это обойдется вам в 5 песо.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати, не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_day_wait";
			link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
			link.l3.go = "int_quests";
		break;

		case "room_day_next":
			dialog.text = "Это обойдется вам в 10 песо.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати, не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_day_wait";
			link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
			link.l3.go = "int_quests";
		break;

		case "room_night":
			dialog.text = "Это обойдется вам в 5 песо.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_night_wait";
			link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
			link.l3.go = "int_quests";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = "Убирайся, оборван"+ GetSexPhrase("ец","ка") +"! Нечего тут в общей зале просиживать за бесплатно.";
				link.l1 = "Ладно, ладно... уже ухожу.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = "Убирайся, оборван"+ GetSexPhrase("ец","ка") +"! Нечего тут в общей зале просиживать за бесплатно.";
				link.l1 = "Ладно, ладно... уже ухожу.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Уважаемые, прошу вас прекратить это безобразие в моей таверне, или я позову стражников!";
			link.l1 = "Ладно, ладно, я уже ухожу.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
	}
}

// boal 25/04/04 общий диалог Usurer
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
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
			//<<-- дача квеста найти потерянный драгоценный камень
			dialog.text = NPCStringReactionRepeat("Здравствуйте, " + GetAddress_Form(npchar) + ". Чем я могу вам помочь?", 
				"О, это опять вы? Добро пожаловать, " + GetAddress_Form(npchar) + " Что вы хотите на этот раз?", 
				"Хм, снова вы, " + GetAddress_Form(npchar) + "... Ну что же, рад вас видеть который уже раз за день. Что вы желаете?",
                "Эх, " + GetAddress_Form(npchar) + ", вы себе представить не можете, до чего порой бывают навязчивы клиенты... Что вам угодно?" , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ничем, я просто заш"+ GetSexPhrase("ел","ла") +" посмотреть и поговорить.", 
				"Опять я. И опять просто так поговорить решил"+ GetSexPhrase("","а") +".",
                "Ага, снова я. И снова без конкретного дела заш"+ GetSexPhrase("ел","ла") +" поговорить.", 
				"Да-а-а, тяжело приходится ростовщикам порой... А мне от вас ничего не нужно, просто поболтать хотел"+ GetSexPhrase("","а") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Я хочу обсудить наши финансовые взаимоотношения.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Мне нужна кое-какая информация... В общем, есть вопрос.";
			link.l3.go = "quests";//(перессылка в файл города)
			NextDiag.TempNode = "First time";
		break;

		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Нет, ничем не могу помочь. В нашем неспокойном месте я могу предложить только услуги хранения денег.";
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Хорошо, давайте определимся с суммой.";
	                Link.l1.go = "deposit";
				}
                Link.l2 = "Мне это не интересно.";
				link.l2.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "Ты ведь " + GetFullName(pchar)+ ", не так ли? О тебе " +
                              RandPhraseSimple("ходят ужасные слухи","говорят не лучшим образом") + ", я не хочу иметь с тобой дело.";
				link.l1 = RandPhraseSimple("Эх.. стоит человеку оступиться, и все будут в него плевать.", RandSwear() + "Ну и не надо!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "О, всегда пожалуйста. Какая сумма вам необходима?";
			Link.l1 = "Совсем небольшая.";
			Link.l1.go = "Small";
			Link.l2 = "Весьма значительная.";
			Link.l2.go = "Medium";
			Link.l3 = "Чем больше, тем лучше.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Отлично. С небольшими суммами всегда проще - меньше риска. Я могу предложить вам " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint(GetSummonSkillFromName(pchar, "Speechcraft")/5);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Не проблема. Надеюсь, что " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " помогут вам решить ваши проблемы. Это вполне значительная сумма.";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint(GetSummonSkillFromName(pchar, "Speechcraft")/5);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "М-да... Рискованно... Но ладно, я готов предоставить вам заем на сумму в " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". Как вы понимаете, капитан, это действительно крупные деньги. Очень прошу вас серьезно отнестись к этому делу.";
			Link.l1 = "Договорились. Под какие проценты?";
			Link.l1.go = "Interest";
			Link.l2 = "Увы, эта сумма не годится. Давайте-ка ее изменим.";
			Link.l2.go = "Loan";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint(GetSummonSkillFromName(pchar, "Speechcraft")/5);
		break;

		case "Interest":
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + "% в месяц. Основываясь на том, что я о вас знаю, я не могу предложить вам сейчас лучших условий."; 
			Link.l1 = "Меня это вполне устраивает. Осталось обговорить срок.";
			Link.l1.go = "Period";
			Link.l3 = "Думаю, мне лучше не влезать в долги. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Учитывая то, что я о вас слышал, " + Pchar.name + ", я буду ждать возврата этого кредита " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". После чего, как вы понимаете, я приму меры."; 
			Link.l1 = "Что же, я с удовольствием принимаю ваши условия... И ваши деньги.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Увы, мы с вами не договорились. До свидания.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Искренне этому рад. Но позвольте мне вас предупредить. Я давно занимаюсь своим делом и знаю, как вернуть вложенные средства. Так что если у вас и были какие мысли прикарманить мои деньги, лучше оставьте их\nНе хочу вас обидеть - просто предупреждаю.";
			Link.l1 = "Хм... Ну-ну. Всего хорошего.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "Ну, смотрите... Проценты капают. Да и времени у вас осталось не так уж много.";
			Link.l1 = "Не волнуйтесь. До встречи.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("О, это просто чудесно! В любое время, как вам понадобятся деньги - я к вашим услугам.", "Благодарю. Очень приятно иметь дело с деловым человеком, умеющим вовремя вернуть долг. А то знаете, разное бывает...",  "О, не зря я был в вас столь уверен, " + GetAddress_Form(NPChar) + "! Надеюсь, это не последний раз, когда вы прибегаете к моим услугам!");
			Link.l1 = LinkRandPhrase("Я хочу занять денег.", "Мне срочно понадобилась пара-другая песо.", "Как насчет небольшого кредита?");
			Link.l1.go = "loan";
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Я бы хотел"+ GetSexPhrase("","а") +" отдать деньги в рост.","Примете на хранение пиратскую добычу?", "Серебришко на чёрный день оставить можно?");
				Link.l2.go = "deposit";				
			}
			Link.l3 = "До свидания, " + NPchar.name + ".";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Я слышу разумного человека! Так сколько денег вы готовы отдать в рост?", "Хорошо. Поверьте мне, та сумма, что вы мне отдаете, будет ждать вас в целости и сохранности, и даже с процентами... А, кстати, какова эта сумма?", "Я смотрю, вы понимаете, что к чему в этой жизни. Сколько вы хотите отдать мне на хранение?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;

		case "result":
			Pchar.QuestTemp.Deposits.(NPC_Area).Interest = makeint(GetSummonSkillFromName(pchar, "Speechcraft")/20.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(NPC_Area).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Хм, извините, ошибочка вышла..";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Хм, таких денег у вас при себе нет, к сожалению. Давайте без глупостей...";
				link.l1 = "Гм... хорошо.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Хорошо. Процентов под эту сумму я готов вам предложить... мм... скажем, " + Pchar.QuestTemp.Deposits.(NPC_Area).Interest + ". Разумеется, в месяц.";
			Link.l1 = "Меня это устраивает.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Лучше я изменю сумму.";
			Link.l2.go = "Deposit";
			Link.l3 = "Кажется, мне не стоит расставаться с деньгами. Всего хорошего.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)+".Result"))
			{
			    Pchar.Quest.Deposits.(NPC_Area).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Извините меня, капитан, но эта сумма слишком велика для провинциального банка. Мне просто негде организовать оборот таких денег, чтобы иметь возможность выплачивать проценты по вашему депозиту. Да и отсутствие достойной охраны, знаете ли... ну, надеюсь, вы меня правильно понимаете? В общем, я могу принять от вас в целом не более " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Очень жаль, придется обратиться к другому ростовщику.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Теперь вы можете быть уверены, что даже самая жестокая буря не оставит вас без средств к существованию. Если же вы решите забрать вклад, то приходите в любое время.";
				Link.l1 = "Хорошо. Всего хорошего.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			Pchar.Quest.Deposits.(NPC_Area).Interest = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Pchar.Quest.Deposits.(NPC_Area).Sum      = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum);

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.Quest.Deposits.(NPC_Area).Sum);
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			DialogExit();
		break;

		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Исходя из процентов, которые мы оговорили в прошлый раз, и учитывая прошедшее время, я подсчитал, что должен вам " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)) + "... Вы уверены, что хотите забрать эти деньги";
			Link.l1 = "Абсолютно. Давайте их сюда.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Знаете, вы правы. Пусть они еще немного полежат. Всего хорошего.";			
			Link.l2.go = "Exit";		
		break;

		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			dialog.text = "Ох... Даже жаль с ними расставаться. Я к ним уже как-то привык. Что же - приходите ко мне еще.";			
			Link.l1 = "Если понадобится - приду. Счастливо оставаться.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			dialog.text = "Вы еще живы? Наверное, хотите вернуть мне деньги? К черту! Из-за вас я потерял столько, сколько вы мне в жизни не возместите! Я не успокоюсь, пока не увижу ваш труп!";
            Link.l1 = "Я как раз хочу уладить наши дела мирно.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Ну, давай посмотрим! Только учти, что ты и сам легко можешь стать трупом!", "Угрожаешь мне?! Ну хорошо, посмотрим, что ты предпримешь...", "Деньги - не главное в жизни. Так что не стоит тебе ради них так убиваться самому и убивать других.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":
			dialog.text = "Убирайтесь из моего дома! Глаза мои вас бы не видели!";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Да? И что вы предлагаете?";
			Link.l1 = "На сегодня я долж"+ GetSexPhrase("ен","на") +" вам сумму в " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". Предлагаю ее вам.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Чтобы наладить отношения, предлагаю вернуть вам сумму долга в размере " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Это другое дело! С вами все же можно иметь дела.";
			Link.l1 = "Спасибо. Больше не подведу.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;																			
	}	
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "burgher_1", "man", "man", 10, sti(npchar.nation), -1, false, F_CITY));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{		
		for(n=0; n<MAX_COLONIES; n++)
		{			
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));	
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1; 
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "burgher_1", "man", "man", 10, sti(colonies[nation].nation), -1, false, F_CITY));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
            if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}		
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}
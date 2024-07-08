// boal 25/04/04 общий диалог церковь
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {
	
        npchar.quest.BadMeeting = "";
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("Сын мой","Дочь моя") +", к сожалению, я не могу дать тебе убежища. Беги!", "Вся городская стража рыщет по городу в поисках тебя, "+ GetSexPhrase("сын мой","дочь моя") +". Церковь открыта для страждущих, но я не могу предоставить тебе убежища...", ""+ GetSexPhrase("Сын мой","Дочь моя") +", тебе надо бежать! Прошу тебя, не медли с этим!"), 
					LinkRandPhrase("Что ты делаешь в церкви, падшая душа? Я требую, чтобы ты удалил"+ GetSexPhrase("ся","ась") +" немедленно, пока солдаты не ворвались и не устроили здесь резню!", "Немедленно покинь храм, безбожни"+ GetSexPhrase("к","ца") +"! Я не заступлюсь за так"+ GetSexPhrase("ого","ую") +", как ты!", "Немедленно покинь храм Божий! Мне не нужны здесь убийства!!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Да ладно тебе, падре...", "Да не нужна мне твоя помощь..."), 
					LinkRandPhrase("Святой отец, лучше не путайся под ногами...", "Уйду, не беспокойся...", "Падре, не суетись, не до тебя, ей богу"));
				link.l1.go = "fight";
				break;
			} 
			
            if (npchar.quest.BadMeeting != lastspeak_date)
			{				
				Dialog.Text = "Добро пожаловать под сень святой обители, "+ GetSexPhrase("сын мой","дочь моя") +".";
				link.l1 = "Здравствуйте, святой отец.";
				link.l1.go = "node_3";
				Link.l2 = "Ты мне не отец, и не смей так больше обращаться.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Покинь храм Господа, богохульни"+ GetSexPhrase("к","ца") +"! Нам с тобой не о чем говорить!";
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Ах, ты богохульни"+ GetSexPhrase("к","ца") +"! А ну прочь отсюда, дабы не осквернять своим присутствием храм Божий!";
			link.l1 = "Да я и так не собирал"+ GetSexPhrase("ся","ась") +" здесь задерживаться.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = "Да благословит Господь вас и дела ваши... Вы пришли ко мне с какой-то целью?";
    		link.l1 = RandPhraseSimple("Я хочу внести пожертвования.", "Хочу пожертвовать на благое дело.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Думаю, настало время исповеди.","Мне нужно покаяться, "+RandPhraseSimple("падре.", "святой отец."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("У меня к вам дело, " + RandPhraseSimple("падре.", "святой отец."),
                                        "Я прибыл"+ GetSexPhrase("","а") +" по делу, " + RandPhraseSimple("падре.", "святой отец."));
    		link.l3.go = "work";//"quest lines";
			link.l6 = "Извините, мне пора идти.";
			link.l6.go = "exit";
		break;

	//================================================================================================================
		
		
		case "donation":
			dialog.Text = "Конечно, "+ GetSexPhrase("сын мой","дочь моя") +". Сколько ты желаешь пожертвовать Святой Церкви?";
			Link.l1 = "Простите, святой отец, но пожертвования не будет.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Моя лепта будет скромной. Всего 100 песо.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 песо. Я думаю, этого хватит.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Мне везет с деньгами, поэтому я пожертвую 5000 песо.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Святой отец, я хочу сделать пожертвование не от себя. Я делаю это по поручению.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Хм... Это ваше решение, и вы вправе его изменить. Но не забывайте, что это зачтется вам на Страшном Суде.";
			Link.l1 = "И не только это. Давайте лучше сменим тему.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "От лица Святой Церкви благодарю вас, "+ GetSexPhrase("сын мой","дочь моя") +", за ваш дар.";
			Link.l1 = "Мне надо поговорить с вами, святой отец.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "От лица Святой Церкви благодарю вас, "+ GetSexPhrase("сын мой","дочь моя") +", за ваш дар.";
            Link.l1 = "Мне надо поговорить с вами, святой отец.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "От лица Святой Церкви благодарю вас, "+ GetSexPhrase("сын мой","дочь моя") +", за ваш дар.";
            Link.l1 = "Мне надо поговорить с вами, святой отец.";
			Link.l1.go = "node_3";
			Link.l2 = "Извините, святой отец, мне пора.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Конечно же, "+ GetSexPhrase("сын мой","дочь моя") +", я тебя слушаю.";
			link.l1 = "Я передумал"+ GetSexPhrase("","а") +". Может быть в другой раз.";
			link.l1.go = "exit";
			link.l2 = "Я так греш"+ GetSexPhrase("ен","на") +", святой отец. Чтобы перечислить все мои прегрешения, не хватит целого дня...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Все мы грешны, дитя моё...";
			link.l1 = "Да, но на моей совести тяжким бременем лежит груз тысяч смертей. Я грабил"+ GetSexPhrase("","а") +" и топил"+ GetSexPhrase("","а") +" корабли...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Я надеюсь, среди них не было таких, что ходили под флагом " + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = "Нет, конечно, святой отец.";
			link.l1.go = "ispoved_3";
			link.l2 = "Всякие были, святой отец... всякие.";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Тогда Господь простит тебе эти грехи. Ибо век наш жесток, и уничтожая недругов своего государя, ты спасаешь жизни верных его подданных.";
			link.l1 = "Спасибо, святой отец, вы меня очень утешили... я пойду.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Господь никогда не простит такого греха! Молись и кайся, кайся и молись! Одна тебе дорога - в монастырь!";
			link.l1 = "С монастырём придётся погодить. Не в этой жизни, по крайней мере. Прощайте...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
			dialog.text = "Какое дело привело тебя, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Я хотел"+ GetSexPhrase("","а") +" бы задать вам один вопрос, падре...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Я хочу поговорить о работе на благо церкви " + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        "Как идут дела в приходе, не нужна ли какая помощь?");
			link.l2.go = "prihod";
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Я нуждаюсь в исцелении.";
                link.l4.go = "healthAdd_1";
            }
			link.l99 = "Я передумал"+ GetSexPhrase("","а") +", меня ждут дела.";
			link.l99.go = "exit";
		break;

		case "prihod":
            dialog.text = "У нас в приходе все спокойно, "+ GetSexPhrase("сын мой","дочь моя") +". Спасибо за предложение.";
    		link.l2 = "Ну, раз все хорошо, я пойду по своим делам.";
    		link.l2.go = "exit";
		break;
	}

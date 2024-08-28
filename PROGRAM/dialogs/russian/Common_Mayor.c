// boal 25/04/04 общий диалог мэры
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool   bOk;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Вы посмели явиться к губернатору?! Смелый шаг...", "Как эти бездельники допустили, чтобы ко мне ворвался враг?! Уму непостижимо...", "Да уж, моя охрана немногого стоит, раз "+ GetSexPhrase("какой-то бездельник","какая-то бездельница") +" бегает в моей резиденции..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Мои солдаты уже взяли твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моей резиденции! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Солдатня мало чего стоит...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Вот что я тебе скажу, приятель: сиди тихо, и будешь жить..."));
				link.l1.go = "fight";
				break;
			} 
			
			if (sti(NPChar.nation) == PIRATE)
            {
				dialog.text = "Нам не о чем говорить, я занят.";
				link.l1 = "Ну и ладно.";
				link.l1.go = "Exit";

				break;
			}	
        
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) >= 15)
            {
                dialog.text = "О! Кто пришел! Это же сам"+ GetSexPhrase("","а") +" " + GetFullName(pchar) + ". Мы как раз недавно высылали охотников за головами, чтобы они привели вас сюда. И знаете, это уже встало нам в кругленькую сумму.";
                if (sti(pchar.Money) >= ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000)
                {
                    link.l1 = "Я как раз хочу уладить наши разногласия.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Э... пожалуй, мне пора.";
				link.l2.go = "arest_1";
				break;
            }
			
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Враг в резиденции! Тревога!!";
				link.l1 = "А-ать, дьявол!";
				link.l1.go = "fight"; 
				break;
			}			

            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Я слышал, что вы очень настойчиво просили аудиенции. Меня зовут " + GetFullName(npchar) +
                              ". Я губернатор города "+ GetCityName(NPChar.city) + " подданства " + NationKingsName(npchar)+
                              ". А теперь соблаговолите сообщить цель вашего визита, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "Мое имя " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
                {
                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "Мы вроде все уже обсудили, не так ли?";
                        link.l1 = "Все верно - не стану вас более задерживать.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Должен вас огорчить, но в данный момент у меня нет времени, чтобы принять вас. Как вы, наверное, уже знаете, на нашу колонию напали "+NationNamePeople(sti(aData.nation))+". И мне необходимо организовать оборону города.";
                        link.l1 = "Так я как раз хотел"+ GetSexPhrase("","а") +" предложить свою помощь в обороне форта.";
                        link.l1.go = "siege_task";
                        link.l2 = "Тогда не стану вас более задерживать.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterReputation(PChar, 10);
                        //--> слухи
                        SiegeRumour("Поговаривают, что вы помогли нам отбиться от "+NationNameSK(sti(aData.nation))+"ой эскадры - и отстоять нашу колонию! Мы так благодарны вам, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Ах, это вы, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", рад вас видеть. Добрые вести для нашей колонии - мы отбились от "+NationNameSK(sti(aData.nation))+"их захватчиков. В этом есть и ваша заслуга, вот ваша награда "+(sti(aData.iSquadronPower)*1500)+" песо. Извольте получить.";
                        link.l1 = "Спасибо, " + GetAddress_FormToNPC(NPChar) + ", приятно иметь с вами дело!";
                        link.l1.go = "exit";
                    }
                    else
                    {				
						dialog.text = RandPhraseSimple("А, это опять вы? По какому вопросу на этот раз?",
                                      "Опять отрываете меня от дел управления городом? Что вам угодно, " +GetAddress_Form(NPChar)+"?");
        				link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation))+".";
        				link.l1.go = "work";
						
        				link.l2 = "Нужно поговорить с вами об одном деле.";
						link.l2.go = "quests";   //(перессылка в файл города)
						
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Мне нужно сдать пленного капитана властям.";
        				    link.l3.go = "sell_prisoner";
        				}
        				link.l7 = "Я бы хотел"+ GetSexPhrase("","а") +" узнать, где сейчас находится генерал-губернатор " + NationNameGenitive(sti(NPChar.nation)) + ".";
        				link.l7.go = "Where_guber";
        				link.l8 = "Может, вы хотите немного передохнуть от важных дел? Могу предложить провести время за игрой.";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Прошу простить меня, но меня ждут дела.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Мы вроде все уже обсудили, не так ли?";
                    link.l1 = "Все верно - не стану вас более задерживать.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Должен вас огорчить, но в данный момент у меня нет времени, чтобы принять вас. Как вы, наверное, уже знаете, на нашу колонию напали "+NationNamePeople(sti(aData.nation))+". И мне необходимо организовать оборону города.";
                    link.l1 = "Так я как раз хотел"+ GetSexPhrase("","а") +" предложить свою помощь в обороне форта.";
                    link.l1.go = "siege_task";
                    link.l2 = "Тогда не стану вас более задерживать.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterReputation(PChar, 10);
                    //--> слухи
                    SiegeRumour("Поговаривают, что вы помогли нам отбиться от "+NationNameSK(sti(aData.nation))+"ой эскадры - и отстоять нашу колонию! Мы так благодарны вам, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ах, это вы, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", рад вас видеть. Добрые вести для нашей колонии - мы отбились от "+NationNameSK(sti(aData.nation))+"их захватчиков. В этом есть и ваша заслуга, вот ваша награда "+(sti(aData.iSquadronPower)*1500)+" песо. Извольте получить.";
                    link.l1 = "Спасибо, " + GetAddress_FormToNPC(NPChar) + ", приятно иметь с вами дело!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Так какая причина заставила вас прийти сюда и отвлекать меня от важных государственных дел?";
        			link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation))+".";
        			link.l1.go = "work";
        			link.l2 = "Нужно поговорить с вами об одном деле.";
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Мне нужно сдать пленного капитана властям.";
        			    link.l3.go = "sell_prisoner";
        			}
        			link.l4 = "Я бы хотел"+ GetSexPhrase("","а") +" узнать, где сейчас находится генерал-губернатор " + NationNameGenitive(sti(NPChar.nation)) + ".";
        			link.l4.go = "Where_guber";
        			link.l5 = "Может, вы хотите немного передохнуть от важных дел?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Это просто визит вежливости и ничего более, " + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			dialog.text = "Хм, и какие игры вы предпочитаете?";
			link.l1 = "Перекинемся в карты на солидный интерес?";
			link.l1.go = "Card_Game";
   			link.l2 = "Погремим костями в покер-джокер?";
			link.l2.go = "Dice_Game";
			link.l10 = "Прошу простить меня, но меня ждут дела.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Я не буду играть в азартные игры с разными проходимцами!";
    			link.l1 = "Как вам будет угодно.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Давайте! Отдых никогда не вредил здоровью... только кошельку...";
	    			link.l1 = "Замечательно.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "По каким правилам игра?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Нет, с меня довольно на сегодня. Дела ждут.";
	    			link.l1 = "Как вам будет угодно.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Что ж, давайте начнем!";
			link.l1.go = "Cards_begin";
			link.l3 = "Нет, это не для меня...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Давайте определимся со ставкой.";
			link.l1 = "Играем по 1000 монет.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Давайте по 5000 песо.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Изволите шутить, " + GetAddress_Form(NPChar) + "? У вас нет денег!";
                link.l1 = "Бывает.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Все! Нужно завязывать с картами, а то запишут в растратчики и сместят с поста...";
                link.l1 = "Жаль.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 1000 монет.";
			link.l1 = "Начали!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
                link.l1 = "Давайте по более низким ставкам?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Извините, мне пора.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Изволите шутить, " + GetAddress_Form(npchar) + "? У вас нет 15000 песо!";
                link.l1 = "Будут!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Нет, такие ставки не доведут до добра казну города.";
                link.l1 = "Как угодно.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 5000 монет.";
			link.l1 = "Начали!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "Я не буду играть в азартные игры с разными проходимцами!";
    			link.l1 = "Как вам будет угодно.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Давайте! Отдых никогда не вредил здоровью... только кошельку...";
	    			link.l1 = "Замечательно.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "По каким правилам игра?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Нет, с меня довольно на сегодня. Дела ждут.";
	    			link.l1 = "Как вам будет угодно.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Что ж, давайте начнем!";
			link.l1.go = "Dice_begin";
			link.l3 = "Нет, это не для меня...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Давайте определимся со ставкой.";
			link.l1 = "Играем по 500 монет за кубик.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Давайте по 2000 песо за кубик.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Изволите шутить, " + GetAddress_Form(NPChar) + "? У вас нет денег!";
                link.l1 = "Бывает.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Все! Нужно завязывать с играми, а то запишут в растратчики и сместят с поста...";
                link.l1 = "Жаль.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 500 монет.";
			link.l1 = "Начали!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
                link.l1 = "Давайте по более низким ставкам?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Извините, мне пора.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Изволите шутить, " + GetAddress_Form(NPChar) + "? У вас нет 15000 песо!";
                link.l1 = "Будут!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Нет, такие ставки не доведут до добра казну города.";
                link.l1 = "Как угодно.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Хорошо, играем по 2000 монет за кубик.";
			link.l1 = "Начали!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.snd = "Voice\CHMA\CHMA004";
			dialog.text = "В таком случае, я попрошу вас покинуть мой кабинет и более не мешать мне работать.";
			link.l1 = "Да, да, конечно, извините, что потревожил"+ GetSexPhrase("","а") +" вас.";
			link.l1.go = "exit";
		break;

		case "Where_guber":
            offref = characterFromID(NationShortName(sti(NPChar.nation))+"_guber");
			
			if(NPChar.location == "Havana_townhall" && offref.location == "Havana_GovernorGeneralTownhall")
			{
				dialog.text = "Его " + RandPhraseSimple("Милость", "Светлость") + " генерал-губернатор "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
						  " располагается в своём поместье, вход туда ведёт через сад.";
				link.l1 = "Большое спасибо!";
				link.l1.go = "exit";
				break;
			}
            if (NPChar.location == offref.location)
            {
                dialog.text = "Раскрой глаза, невежа!! Его " + RandPhraseSimple("Милость", "Светлость") + " генерал-губернатор "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                              " находится прямо здесь в комнате!";
    			link.l1 = "Спасибо. Простите мою бестактность.";
    			link.l1.go = "exit";
            }
            else
            {
                if (bBettaTestMode || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) > rand(5) || CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))))// когда патен всегда
                {
                    cn = FindLocation(offref.location);
                	if(cn < 0)
                    {
                        attrLoc = "error";
                        dialog.text = "Его " + RandPhraseSimple("Милость", "Светлость") + " генерал-губернатор "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                      " отбыл с визитом в Европу.";
                    }
                	else
                	{
                	    attrLoc = locations[cn].islandId;
                	    if (attrLoc == "Mein")
                	    {
        			    	dialog.text = "Его " + RandPhraseSimple("Милость", "Светлость") + " генерал-губернатор "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(" находится сейчас на материке ",
                                            " занимается важными государственными делами на материке ",
                                            " находится с визитом на материке ") + " в городе " + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
						else
						{
						    dialog.text = "Его " + RandPhraseSimple("Милость", "Светлость") + " генерал-губернатор "+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(" находится сейчас на острове ",
                                            " занимается важными государственными делами на острове ",
                                            " находится с визитом на острове ") + GetConvertStr(attrLoc, "LocLables.txt") + " в городе " + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
                    }
        			link.l1 = "Огромное спасибо!";
        			link.l1.go = "exit";
    			}
    			else
    			{
                    dialog.text = "Почему это я должен открывать вам важную государственную тайну? Откуда я знаю, что вы не шпион?";
        			link.l1 = "Нет, что вы. Прошу меня простить.";
        			link.l1.go = "exit";
    			}
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "Это есть баг, известите Эдди о наличие оного.";
        	link.l1 = "Хорошо, приятель!";
        	link.l1.go = "exit";
            //navy -->
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "Увы, на сегодня у меня заданий больше нет. Последнее выполнил " + GetFullName(&Characters[i])
					+ ". Зайдите завтра, может что-то появится.";
				link.l1 = "Ах, черт!!! Не везет...";
				link.l1.go = "exit";
				break;
			}
            //navy <--
			dialog.text = LinkRandPhrase("Сегодня я уже ничего не могу предложить в качестве работы.", "На сегодня работы для вас уже нет.", "На сегодня уже все, работы нет. Все вопросы по поводу работы - завтра.");
			link.l1 = RandPhraseSimple("Жаль...", "Эх, очень жаль, "+ GetAddress_FormToNPC(NPChar) + ". ");
        	link.l1.go = "exit";
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Кого вы хотите отпустить за выкуп?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Никого.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "Итак, это капитан " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " Я готов выкупить соотечественника за " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " Я могу дать за этого висельника " + FindRussianMoneyString(qty) + ". И мы сразу же казним негодяя.";
                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " За этого человека я могу заплатить не более " + FindRussianMoneyString(qty) + ".";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "По рукам. Он полностью ваш, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Нет. Не пойдет.";
			link.l3.go = "exit";
		break;

		case "sell_prisoner_3":
			dialog.text = "Вот и славно.";
			link.l1 = "Всего хорошего.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterReputation(pchar, -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // все, все свободны

            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Вы уже все забрали. Что вам еще нужно?";
                Link.l1 = "Да, точно, ошиб"+ GetSexPhrase("ся","лась") +" городом.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернем диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Какая неслыханная наглость! Скоро прибудет подкрепление из форта, и вам не поздоровится!";
                Link.l2 = "Я не собираюсь торчать тут до его прихода. Заплати мне, и мы покинем этот город.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "На этот раз ваша взяла, но знайте, что скоро прибудет наша эскадра, и от вас мокрого места не останется.";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Поговори еще! Этот город отныне принадлежит мне, а вашу эскадру я отправлю на свидание к морскому дьяволу. Эй, парни, возьмите эту свинку и посадите за решетку.";
	    				}
	    				else
	    				{
	    					Link.l1 = "Этот город отныне принадлежит мне, и как его защитить - я решу сам"+ GetSexPhrase("","а") +". Эй, парни, уберите этого выскочку.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Десант? Хм... Заплати мне - и мы покинем этот город.";
				}
				else
				{
	            	Link.l2 = "Эскадра... Хммм... Заплати мне - и мы покинем этот город.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Это неслыханная наглость! Как вы посмели напасть на колонию, принадлежащую " + NationNameGenitive(sti(NPChar.nation)) + "?! Вы дорого заплатите за кровь, бессмысленно пролитую вами, и за ущерб, нанесенный нашей державе.";
	                Link.l1 = "С этого момента колония принадлежит мне, а если кто-то попытается в этом усомниться, то отправится прямиком на небеса.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Я представляю интересы " + NationNameGenitive(sti(PChar.nation)) + " и официально заявляю, что отныне эта колония принадлежит " + NationKingsCrown(PChar) + "!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Нам следует обсудить размеры выкупа. Если же вы будете упрямствовать, то мы превратим ваш чудесный город в груду пепла, а вас повесим на городской площади.";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("Все корабли отремонтированы.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
			
			if (NPChar.City == "Havana") HavanaResGatesUnlock();
        break;

        case "City_patent":
            ChangeCharacterReputation(GetMainCharacter(), -20); // пираты мы, но у нас патент
            dialog.Text = "На этот раз ваша взяла, но знайте, скоро прибудет наша эскадра, и от вас мокрого места не останется.";
			Link.l1 = "Поговори ещё! Эта колония отныне принадлежит мне, а вашу эскадру я отправлю на свидание к морскому дьяволу. Эй, парни, возьмите эту свинку и посадите за решётку.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Что вам от меня еще нужно?";
            Link.l1 = "Смотрю, все ли я забрал"+ GetSexPhrase("","а") +"...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернем диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Мне больше ничего не остается, как согласиться на ваши условия. Забирайте свои кровавые деньги и немедленно покиньте воды нашей колонии.";
            Link.l1 = "Позвольте откланяться.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
			
			if (NPChar.City == "Havana")
			{
				pchar.questTemp.HavanaResGatesLock.win_condition.l1 = "MapEnter";
				pchar.questTemp.HavanaResGatesLock.function = "HavanaResGatesLock";
			}
        break;

        case "Summ_patent":
            dialog.Text = "Хорошо, вы можете диктовать свои условия...";
            Link.l1 = "Да, по праву победителя. Где мои деньги?";
            Link.l1.go = "Summ";
            ChangeCharacterReputation(GetMainCharacter(), -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Что ж, мы отдаемся на милость победителей.";
			Link.l1 = "Советую вам побыстрее покинуть пределы города, еще неизвестно, как на вашем здоровье отразятся грядущие перемены. Прощайте.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterReputation(GetMainCharacter(), 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не дает, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернем диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			
			if (NPChar.City == "Havana")
			{
				pchar.questTemp.HavanaResGatesLock.win_condition.l1 = "MapEnter";
				pchar.questTemp.HavanaResGatesLock.function = "HavanaResGatesLock";
			}
	    break;
	    
	    case "Prison":
			dialog.Text = "Что вам от меня еще надо, негодяй"+ GetSexPhrase("","ка") +"?";
            Link.l3 = "Посмотрел"+ GetSexPhrase("","а") +", как ваше сиятельство поживает. Ну, а теперь мне пора!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Уладить? Как вы себе это представляете?";
            link.l1 = "Я думаю, сумма в " + ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000 + " песо может меня спасти?";
			link.l1.go = "arestFree_2";
			link.l2 = "Никак, мне пора. Всего доброго.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSPECIAL(PChar, SPECIAL_L) >= rand(7))
            {
    			dialog.text = "Пожалуй, можно уладить наш инцидент таким способом.";
    		    link.l1 = "Замечательно!";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
            }
            else
            {
    			dialog.text = "Нет! Ваши злодеяния можно искупить только единственным способом. Стража! Отведите е"+ GetSexPhrase("го","е") +" в форт.";
    		    link.l1 = "Постойте!";
    		    link.l1.go = "arest_2";
            }
		break;

		case "arest_1":
			dialog.text = "Конечно пора, вас проводят. Стража! Взять е"+ GetSexPhrase("го","е") +"!";
		    link.l1 = "Ну, уж нет!";
		    link.l1.go = "fight";
		break;   
	}
}

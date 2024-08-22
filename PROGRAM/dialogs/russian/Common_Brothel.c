void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1,iColony;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			NextDiag.TempNode = "First time";
			
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("Милый-дорогой, какие девочки?! За тобой половина гарнизона гонится, а он в бордель пожаловал!","Шла бы ты отсюда... За тобой половина гарнизона гонится!") +"", "Вся городская стража рыщет по городу в поисках тебя. Я не идиотка, привечать тебя в такой момент...", "Попрошу удалиться из моего заведения, тебе здесь делать нечего!"), 
					LinkRandPhrase(""+ GetSexPhrase("Попробуй только дотронуться до моих девочек - я с тебя живого шкуру сдеру!","Убирайся отсюда, мерзавка!") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего заведения! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Помолчала бы лучше, дура...", "Заткнись, не то хуже будет..."));
				link.l1.go = "exit";
				break;
			}
			
			// "Моряки желают развлечений" -->
			if(CheckAttribute(NPChar, "SailorEvent_PenaltyPaid"))
			{
				dialog.text = "Капитан, я рада, что мы пришли к взаимопониманию. Ваши деньги пойдут на возмещение моих убытков.";
				link.l1 = "Разумеется. Надеюсь, скоро здесь всё станет, как и прежде.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(NPChar, "SailorEvent_Block"))
			{
				npchar.quest.meeting = "1";
				dialog.text = "(недовольно) Ох, наконец-то вы явились, девушка! Не хотите ничего мне сказать?";
				link.l1 = "Хм, а что я должна сказать вам? Вы ждёте извинений?";
				link.l1.go = "SailorEvent_Angry_1";
				break;
			}
			
			if(CheckAttribute(PChar, "Event.SailorEvent") && NPChar.id == PChar.Event.SailorEvent.City + "_Hostess")
			{
				npchar.quest.meeting = "1";
				switch(PChar.Event.SailorEvent)
				{
					case "InBrothel":
						if(!CheckAttribute(&TEV, "SB_Counter.Massage"))
						{
							dialog.text = "Капитан, позвольте поблагодарить вас за огромное количество клиентов. Мои девочки работают не покладая рук, чтобы доставить удовольствие вашим подчинённым. Признайтесь, вы решились отправить их всех к нам, когда увидели, как кто-то из моряков смотрит на вас с вожделением?";
							link.l1 = "Ah non! Ca ne va pas! Если бы такое произошло, то этому моряку бы очень не поздоровилось."
							link.l1.go = "Hostess_Massage_1";
						}
						else
						{
							switch(rand(2))
							{
								case 0:
									dialog.text = "Капитан, я очень рада вас видеть в стенах моего скромного заведения! Вашим морякам здесь хорошо и уютно. А чего желаете вы?";
								break;
								case 1:
									dialog.text = "Здравствуйте, капитан. Пришли проведать своих ребят? Не беспокойтесь, они в надёжных и ласковых руках моих девушек. Может, вы тоже чего-нибудь хотите?";
								break;
								case 2:
									dialog.text = "Капитан, благодаря вашим морякам у меня будет двухнедельная выручка за два дня. Благодарю вас за это. Может, я могу оказать вам какую-нибудь услугу?";
								break;
							}
							link.l1 = "Нет, ничего не нужно. Я просто зашла посмотреть, как отдыхают мои матросы."
							link.l1.go = "exit";
							link.l2 = "Раз мои моряки отдыхают, то и мне бы не мешало. Мне бы хотелось... (шёпотом) Хотелось бы воспользоваться услугой массажа."
							link.l2.go = "Hostess_Massage_Repeat";
						}
					break;
					
					case "BrothelOut":
						dialog.text = "Капитан, мы весьма разочарованы тем, что вы были вынуждены вернуть свой экипаж обратно на корабль. Неужели вас не удовлетворила работа моих девочек?";
						link.l1 = "Дело не в них, просто у нас появились неотложные дела.";
						link.l1.go = "exit";
					break;
					
					case "AfterMassage":
						dialog.text = "Вас ещё что-то интересует, капитан?"
						link.l1 = "Нет, ничего. Просто смотрю, как тут отдыхают мои моряки.";
						link.l1.go = "exit";
					break;
				}
				break;
			}
			// <-- "Моряки желают развлечений"
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Добро пожаловать в дом терпимости. Меня зовут " + npchar.name + ", я здесь заведую всем. "+ GetSexPhrase("Чем могу быть полезна?, " + GetAddress_Form(NPChar) + "","Признаюсь, немного удивлена видеть вас здесь, " + GetAddress_Form(NPChar) + ", но смею заверить: мы оказываем услуги не только мужчинам.") +"",
				                               TimeGreeting() + ". Приветствую вас, "+ GetSexPhrase("незнакомец","девушка") +", в моем скромном заведении. Позвольте представится, я "+ NPChar.Name + " - владелица этого приюта обиженных лаской мужчин. "+ GetSexPhrase("Чем я могу быть вам полезна?","Хотя для женщин у нас тоже кое-что есть...") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Чем я могу вам помочь, " + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + ". Что я могу для вас сделать, " + GetAddress_Form(NPChar) + "?");
			}
			link.l2 = npchar.name + ", я хочу провести время с одной из твоих девушек.";
			link.l2.go = "Hostess_1";
			// Rebbebion - а смысл, если корабля нет?
			if (sti(pchar.ship.type) != SHIP_NOTUSED)
			{
				link.l3 = "Давно я не баловал"+ GetSexPhrase("","а") +" своих парней. Можно сделать оптовый заказ на девочек?";
				link.l3.go = "ForCrew";
			}
			link.l4 = "У меня есть вопрос.";
            link.l4.go = "quests";	
			link.l9 = "Ничем. Я уже ухожу.";
			link.l9.go = "exit";
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("Мы всегда рады клиенту. Скажи мне, дорогой, ты уже присмотрел кого-то или тебе все равно?","Ну что же, мои девочки вполне смогут тебе... помочь. Ты присмотрела кого-нибудь, или тебе все равно?") +"";
					Link.l1 = ""+ GetSexPhrase("Хех, мне нужна девка и немедленно, а кто она такая - наплевать. У тебя все они симпатичные...","Да любая, лишь бы дело свое знала...") +"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Да, есть одна, "+ GetSexPhrase("что мне приглянулась...","с ней было бы приятнее...") +"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Сегодня я уже не могу дать тебе девочку, кроме тебя у меня еще есть клиенты. Приходи завтра, обслужим как следует!";
					Link.l1 = "Эх, жаль"+ GetSexPhrase(", я только вошел во вкус","") +"... Ну да ладно.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Хм, ты уже оплатил"+ GetSexPhrase("","а") +" девушку. Так что займись ею вплотную, так сказать, и не отвлекай меня по пустякам.";
				Link.l1 = "Хорошо, уже иду.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Сейчас у меня нет свободных девушек, тебе нужно будет зайти сюда через пару дней.";
				Link.l1 = "Хорошо, как скажешь.";
				Link.l1.go = "exit";	
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Ну что, жеребец, превосходно!","У меня они все умелые, можешь не сомневаться.") +" Могу предложить прекрасную девушку по имени " + GetFullName(sld) + ", она сейчас свободна. Стоить это удовольствие будет " + FindRussianMoneyString(sti(sld.quest.price)) + ". Соглас"+ GetSexPhrase("ен","на") +"?";
				Link.l1 = "Нет, пожалуй, откажусь. Дороговато...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= sti(sld.quest.price))
				{
					Link.l2 = "Конечно, соглас"+ GetSexPhrase("ен","на") +", какие могут быть вопросы?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Агрх, нет у меня сейчас таких денег...";
					Link.l1.go = "exit";
				}
			}
		break;
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= sti(sld.quest.price))
			{
				dialog.text = "Отлично, дорог"+ GetSexPhrase("ой","уша") +". " + sld.name + " будет ждать тебя в комнате для уединения на втором этаже.";
				Link.l1 = ""+ GetSexPhrase("Хех, ну я пошел","Ну, я побежала") +"...";
				Link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -sti(sld.quest.price));
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n = 0; n < MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
			}
			else
			{
				dialog.text = "Все бы было хорошо, но дело в том, что " + sld.name + " - девушка недешевая, стоит " + FindRussianMoneyString(sti(sld.quest.price)) + ". А у тебя, насколько я вижу, таких денег нет. Приходи как разбогатеешь"+ GetSexPhrase(", родной","") +"...";
				Link.l1 = "Эх, вот так всегда...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Я всегда рада, когда между девочками и клиентами возникают теплые чувства... Назови мне ее имя.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Хм, ты ошибаешься, у меня нет такой девочки в заведении. Возможно, ты неверно называешь ее имя.";
				Link.l1 = "Хм, но я только что с ней разговаривал"+ GetSexPhrase("","а") +".";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Пожалуй, мне лучше уточнить ее имя. Я позже переговорю с тобой на эту тему.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + ", ты о ней говоришь?";
				Link.l1 = "Ага, именно о ней.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Нет, не о ней.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
        case "Hostess_Choice_2":
			dialog.text = "Тогда тебе нужно назвать ее имя еще раз, возможно я пойму, о ком идет речь.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Пожалуй, мне лучше уточнить ее имя. Я позже переговорю с тобой на эту тему.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Хмм.. На всю команду? Значит, решил"+ GetSexPhrase("","а") +" 'сбросить пар' у ребят? Что ж, у меня есть несколько высоко квалифицированных девочек, способных на такое... С тебя " + FindRussianMoneyString(GetCrewQuantity(pchar)*30) + ".";
			link.l1 = "Хорошо, я соглас"+ GetSexPhrase("ен","на") +" заплатить эти деньги.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Думаю, они обойдутся как-нибудь...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*30 && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*30));
	            AddCrewMorale(Pchar, 10);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "Это, конечно, не мое дело, но мне кажется, что тебе сначала нужно заработать на команду, а потом думать о ее морали.";
			    link.l1 = "Пожалуй, да...";
			    link.l1.go = "exit";
		    }
		break;
		
		// "Моряки желают развлечений" -->
		case "SailorEvent_Wholesale_1":
			npchar.quest.meeting = "1";
			dialog.text = "Мои девушки только что вернулись, уставшие, но довольные. Заказывайте их почаще, если хотите, чтобы у ваших моряков был всегда поднят моральный дух.";
			link.l1 = "И не только дух... Благодарю вас за оказанную услугу.";
			link.l1.go = "exit_setOwner";
		break;
		
		case "Hostess_Massage_1":
			TEV.SB_Counter.Massage = 0; //флаг массажа для диалогов при повторении ивента
			dialog.text = "Зачем же так строго? Они мужчины, в них природой заложено любить женщин... А как же вы, капитан?";
			link.l1 = "(удивлённо) Quoi?! Что 'я'?";
			link.l1.go = "Hostess_Massage_2";
		break;
		
		case "Hostess_Massage_2":
			dialog.text = "Вы же девушка и, без сомнений, вам тоже хочется тепла и ласки. У нас в борделе есть специальная услуга для женщин. Мы предоставляем её во время особых случаев. Думаю, сегодня как раз такой случай.";
			link.l1 = "Если вы думаете, что я поклонница творчества поэтессы Сапфо и её Дома Муз на острове Лесбос, то вы глубоко ошибаетесь.";
			link.l1.go = "Hostess_Massage_3";
		break;
		
		case "Hostess_Massage_3":
			dialog.text = "Нет-нет, я вовсе не пытаюсь склонить вас к греховной любви. Речь идёт об обычном расслабляющем массаже, который я делаю собственными руками. (говоря шёпотом) Скажу вам по секрету, даже местные дворянки иногда пользуются нашими услугами. Только прошу, никому об этом ни слова, иначе мы пострадаем... Так что вы решили, капитан, желаете получить массаж или нет? Первый раз за счёт заведения.";
			link.l1 = "Благодарю за предложение, но нет, пожалуй, не в этот раз.";
			link.l1.go = "Hostess_Massage_Refuse";
			link.l2 = "Почему бы и нет, если это простой массаж, причём бесплатный.";
			link.l2.go = "Hostess_Massage_4";
		break;
		
		case "Hostess_Massage_Refuse":
			NextDiag.TempNode = "Hostess_Massage_Ask";
			dialog.text = "Очень жаль, но вы можете ещё передумать. Я всегда буду рада оказать вам эту услугу.";
			link.l1 = "Merci. Если моя... хм... спина вдруг захочет массажа, то я непременно к вам обращусь.";
			link.l1.go = "exit";
		break;
		
		case "Hostess_Massage_Ask":
			dialog.text = "Вы передумали, капитан? Предложение насчёт массажа ещё в силе.";
			link.l1 = "Нет, просто решила проведать вас. Всего хорошего.";
			link.l1.go = "exit";
			link.l2 = "Да, пожалуй, я хочу попробовать."
			if(sti(TEV.SB_Counter.Massage) && sti(pchar.money) >= sti(PChar.Event.SailorEvent.MassagePrice))
				 link.l2.go = "Hostess_Massage_Repeat_1";
			else link.l2.go = "Hostess_Massage_4";
		break;
		
		case "Hostess_Massage_4":
			dialog.text = "(улыбаясь) Вы не пожалеете! Сейчас комната занята вашими моряками и моими девочками, но позже, когда у них наступит перерыв, они приберутся там, и мы сможем уединиться для массажа.";
			link.l1 = "Bien, только чтобы мои ребята ничего не увидели. Им вряд ли объяснишь, что это всего лишь массаж.";
			link.l1.go = "exit";
			AddDialogExitQuest("SailorEvent_Massage_Frame");
		break;
		
		case "Hostess_Massage_5":
			if(!CheckAttribute(TEV, "SensualMassage")) //первый массаж
			{
				dialog.text = "Вы готовы?";
				link.l1 = "Да, я готова... Назад дороги нет.";
				link.l1.go = "Hostess_Massage_6";
			}
			else
			{
				TEV.SensualMassage = 2;
				TEV.SensualMassage.Bonus = "";
				dialog.text = "Капитан, можете раздеться и лечь животом на кровать. Вам понравится.";
				link.l1 = "Я помню, что нужно делать. Приступим.";
				link.l1.go = "exit";
				AddDialogExitQuest("PlaySex_1");
			}
		break;
		
		case "Hostess_Massage_6":
			TEV.SensualMassage = 1;
			TEV.SensualMassage.Bonus = "";
			dialog.text = "(улыбаясь) Тогда раздевайтесь, ложитесь животом на кровать, а затем мы приступим к массажу. Вам понравится.";
			link.l1 = "(вздох) Надеюсь, я не пожалею об этом.";
			link.l1.go = "exit";
			AddDialogExitQuest("PlaySex_1");
		break;
		
		case "Hostess_Massage_7":
			npchar.greeting = "hostess"; //вертаем
			if(sti(TEV.SensualMassage) == 1)
			{
				dialog.text = "По вашему лицу, капитан, я вижу, что вы очень довольны.";
				link.l1 = "Да, действительно, я и не думала, что можно получить столько удовольствия от... массажа. Благодарю вас.";
			}
			else
			{
				dialog.text = "По вашему сияющему лицу я вижу, что вы остались довольны.";
				link.l1 = "Да, мне определённо понравился этот массаж. Благодарю вас.";
			}
			link.l1.go = "Hostess_Massage_8";
		break;
		
		case "Hostess_Massage_8":
			NextDiag.TempNode = "First time";
			PChar.Event.SailorEvent = "AfterMassage";
			if(sti(TEV.SensualMassage) == 1)
			{
				dialog.text = "Не стоит благодарности, ведь это моя работа. Приходите ещё раз на массаж, если выпадет случай.";
				link.l1 = "Непременно им воспользуюсь. А пока, всего вам хорошего.";
			}
			else
			{
				dialog.text = "Не стоит благодарности. Вы заплатили деньги за услугу и получили её. Приходите ещё раз, вместе со всем экипажем. Мы всегда рады гостям.";
				link.l1 = "Как только моим морякам снова захочется отдохнуть, то мы будем у вас. Всего вам наилучшего.";	
			}
			link.l1.go = "exit";
			AddDialogExitQuest("SailorEvent_Massage_Over");
		break;
		
		case "Hostess_Massage_Repeat":
			TEV.SB_Counter.Massage = 1;
			dialog.text = "(тихо) Хорошо, я могу лично его сделать для вас. Это будет стоить вам " + FindRussianMoneyString(sti(PChar.Event.SailorEvent.MassagePrice)) + ". Только прошу, никому ни слова, иначе мы можем пострадать.";
			if(sti(pchar.money) >= sti(PChar.Event.SailorEvent.MassagePrice))
			{
				link.l1 = "Bien. Меня устраивает.";
				link.l1.go = "Hostess_Massage_Repeat_1";	
			}
			link.l2 = "Нет, слишком дорого. Я приду в другой раз. Всего вам наилучшего.";
			link.l2.go = "Hostess_Massage_Refuse";
		break;
		
		case "Hostess_Massage_Repeat_1":
			AddMoneyToCharacter(Pchar, -sti(PChar.Event.SailorEvent.MassagePrice));
			dialog.text = "(улыбаясь) Прекрасно, тогда нам нужно подождать, пока комната освободится, а затем мы сразу приступим.";
			link.l1 = "Bien, только прошу, чтобы не было никаких лишних глаз. ";
			link.l1.go = "exit";
			AddDialogExitQuest("SailorEvent_Massage_Frame");
		break;
		
		case "SailorEvent_Angry_1":
			dialog.text = "Разумеется, и не только их. Ваши безумные моряки едва не разнесли в клочья мой бордель, когда узнали, что вы их бросили. Ещё немного, и они бы покалечили моих девушек, если бы к нам на помощь вовремя не прибежала стража. Я требую от вас компенсации за ущерб, нанесённый вашими буйными моряками.";
			link.l1 = "Они больше не мои моряки, но всё равно скажите, сколько вам нужно денег. Я подумаю над этим.";
			link.l1.go = "SailorEvent_Angry_2";
		break;
		
		case "SailorEvent_Angry_2":
			NextDiag.TempNode = "SailorEvent_Angry_3";
			dialog.text = "Я требую от вас возмещения ущерба в размере " + FindRussianMoneyString(sti(NPChar.SailorEvent_Block)) + ". Именно столько мне пришлось потратить, чтобы восстановить все окна и поломанную мебель.";
			if(sti(pchar.money) >= sti(NPChar.SailorEvent_Block))
			{
				link.l1 = "Bien, я всё оплачу. И примите от меня извинения за всё случившееся.";
				link.l1.go = "SailorEvent_Pay_Penalty";
			}
			link.l2 = "Нет. У меня нет желания платить деньги за то, что ваши девушки не могут ласками умиротворить толпу мужчин.";
			link.l2.go = "exit";
		break;
		
		case "SailorEvent_Angry_3":
			dialog.text = "Неужели вы передумали? Напомню, что мне нужно " + FindRussianMoneyString(sti(NPChar.SailorEvent_Block)) + ".";
			if(sti(pchar.money) >= sti(NPChar.SailorEvent_Block))
			{
				link.l1 = "Bien, теперь я могу всё оплатить.";
				link.l1.go = "SailorEvent_Pay_Penalty";
			}
			link.l2 = "Нет, моих денег вы пока не получите.";
			link.l2.go = "exit";
		break;
		
		case "SailorEvent_Pay_Penalty":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			AddMoneyToCharacter(pchar, -sti(NPChar.SailorEvent_Block));
			NPChar.SailorEvent_PenaltyPaid = "";
			sTemp = NPChar.id;
			TEV.BrothelAfterPenalty.(sTemp) = NPChar.index;
			SetTimerFunction("SailorEvent_BrothelAfterPenalty", 0, 0, 1);
			DeleteAttribute(NPChar, "SailorEvent_Block");
		break;
		// <-- "Моряки желают развлечений"
		
		case "Woman_FackYou":
			dialog.text = "Мил"+ GetSexPhrase("ый","ая") +", ты куда это полез"+ GetSexPhrase("","ла") +"?! Надо же, а казал"+ GetSexPhrase("ся","ась") +" порядочн"+ GetSexPhrase("ым капитаном","ой девушкой") +"\nНу а теперь так просто тебе не уйти, красав"+ GetSexPhrase("чик","ица") +". Подрежут тебе крылышки...";
			link.l1 = "Заткнись, дура...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			NextDiag.TempNode = "Horse_talk";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Вам лучше уйти из заведения!", "Вся городская стража рыщет по городу! Вам лучше уйти...", "Надебоширили - и к нам?! Нет уж, в другой раз..."), 
					LinkRandPhrase("Убирайся!!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон отсюда! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Хех, ну и дура же ты...", "Заткнись, не то хуже будет..."));
				link.l1.go = "exit";
				break;
			}
			
			// "Моряки желают развлечений" -->
			if(CheckAttribute(CharacterFromId(NPChar.City + "_Hostess"), "SailorEvent_PenaltyPaid"))
			{
				switch(rand(3))
				{
					case 0:
						dialog.text = "Капитан, спасибо вам, что возместили мадам деньги, потраченные на ремонт нашего здания.";
						link.l1 = "Я не могла поступить иначе.";
						link.l1.go = "exit";
					break;
				
					case 1:
						dialog.text = "Мы рады, что вы помирились с мадам.";
						link.l1 = "Мы и не ссорились, просто ей нужны были деньги.";
						link.l1.go = "exit";
					break;
				
					case 2:
						dialog.text = "Капитан, я не сомневалась в вашей честности. Теперь нам не придётся работать круглые сутки без отдыха, чтобы вернуть потраченные на ремонт деньги. Спасибо.";
						link.l1 = "Не за что. Можете не перетруждаться.";
						link.l1.go = "exit";
					break;
					
					case 3:
						dialog.text = "Капитан, ваши моряки были безмозглыми дикарями, а вы - человек чести. Наверное, потому что вы девушка?";
						link.l1 = "Нет, это потому что я дворянка. Мужчина из моего сословия поступил бы точно так же.";
						link.l1.go = "exit";
					break;
				}
				break;
			}
			
			if(CheckAttribute(CharacterFromId(NPChar.City + "_Hostess"), "SailorEvent_Block"))
			{
				switch(rand(3))
				{
					case 0:
						dialog.text = "Капитан, после всего, что здесь произошло, нам запрещено разговаривать с вами. Поговорите с мадам.";
						link.l1 = "Хорошо. Так я и сделаю.";
						link.l1.go = "exit";
					break;
				
					case 1:
						dialog.text = "К сожалению, мы не можем говорить с вами. Ваши моряки устроили пьяную драку и едва не разгромили здесь всё. Если бы не стражники, то не знаю, что бы с нами случилось. Вас хочет видеть мадам.";
						link.l1 = "Я рада, что вы в порядке. Прошу извинить за происшествие.";
						link.l1.go = "exit";
					break;
				
					case 2:
						dialog.text = "Я до сих пор не могу отойти от того ужаса, что здесь сотворили эти пьяные матросы. Вам следовало бы научить их манерам... И, прошу вас, поговорите с мадам.";
						link.l1 = "К счастью, они больше не часть моей команды.";
						link.l1.go = "exit";
					break;
					
					case 3:
						dialog.text = "Капитан, как вы могли бросить своих моряков? Эти мужчины, они же как дети, которых оставили без просмотра. Мне нельзя говорить с вами, но я скажу, что вы поступили очень-очень неправильно. А теперь извольте проведать мадам.";
						link.l1 = "Так вышло, ничего не поделаешь. Главное, что никто не пострадал, кроме самих моряков.";
						link.l1.go = "exit";
					break;
				}
				break;
			}
			
			if (CheckAttribute(pchar, "Event.SailorEvent") && NPChar.City == PChar.Event.SailorEvent.City)
			{
				if (pchar.Event.SailorEvent == "BrothelOut")
				{
					switch(rand(2))
					{
						case 0:
							dialog.text = "Может, не стоило этого делать? Мужчины только вошли во вкус, а вы прервали их на самом интересном месте.";
							link.l1 = "У них есть свои обязанности, которые они должны выполнять.";
							link.l1.go = "exit";
						break;
					
						case 1:
							dialog.text = "Зачем вы выгнали отсюда всех моряков? С кем нам теперь работать?";
							link.l1 = "Уверена, ты найдёшь себе занятие, милочка.";
							link.l1.go = "exit";
						break;
					
						case 2:
							dialog.text = "Мы настроились работать всё это время. Кто нам теперь заплатит?";
							link.l1 = "Найдутся другие. Поверь, на девушек твоей профессии спрос будет всегда.";
							link.l1.go = "exit";
						break;
					}
					break;
				}
				
				switch(rand(2))
				{
					case 0:
						dialog.text = "Ваши моряки такие напористые. Как только вы с ними управляетесь?";
						link.l1 = "При помощи кнута и рома.";
						link.l1.go = "exit";
					break;
				
					case 1:
						dialog.text = "У меня от этих моряков забот полон рот.";
						link.l1 = "И, похоже, не только этим.";
						link.l1.go = "exit";
					break;
				
					case 2:
						dialog.text = "Пришли посмотреть, как здесь отдыхают ваши моряки?";
						link.l1 = "Вижу, им здесь хорошо.";
						link.l1.go = "exit";
					break;
				}
				break;
			}
			// <-- "Моряки желают развлечений"
			
			dialog.text = NPCStringReactionRepeat("Здравствуйте, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase("",", хи-хи-хи..") +". Вам нужно обратиться к хозяйке заведения, все заказы проходят через нее.", 
				"Ой, это опять вы. Простите, но вам нужно сначала уладить все вопросы с хозяйкой. Прошу вас пройти к ней.", 
				"Послушайте, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", я очень надеюсь, что вы так же упрямы и в других делах, а не только в разговорах... Еще","я еще") +" раз прошу вас пройти к хозяйке заведения.", 
				"Ах, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", какой же вы... настойчивый!",", хи-хи-хи... Вы, однако, натойчивы.") +" Вам нужно пройти к хозяйке заведения для оформления заказа.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Хорошо, "+ GetSexPhrase("красавица, ","") +"я понял"+ GetSexPhrase("","а") +".", "А-а, да, конечно...",
                      ""+ GetSexPhrase("Можешь не сомневаться, красавица, я упрям и силен, как бык!","Да-да...") +"", ""+ GetSexPhrase("Вот дьявол, что-то упустил... Прости, милая.","Хорошо, хорошо.") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "А где она находится?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("Аргх, красавица, в твоих глазах можно утонуть...","Ты выглядишь просто замечательно, малышка!") +"", ""+ GetSexPhrase("Знаешь, я давно не видел такой красивой женщины!","Знаешь, я давненько не встречала такой симпатяшки!") +"", ""+ GetSexPhrase("Эх, милая, ты невероятно прелестна.","Эх, надоели все эти неотесаные мужланы... А ты просто прелесть!") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
		break;
        case "Horse_1":
			dialog.text = "Она в своем кабинете, вы можете пройти к ней отсюда через дверь, противоположную выходу на улицу, либо через улицу с другой стороны дома. Ее зовут " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = "Понятно, "+ GetSexPhrase("милая","дорогуша") +", спасибо.";
			Link.l1.go = "exit";			
		break;
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Ах, боже мой, до чего приятно слышать такое! Слушай, я сейчас свободна, так что если ты выберешь меня, то не пожалеешь...", "Ты действительно так считаешь? Мне очень и очень приятно... Послушай, я сейчас свободна, так что ты можешь выбрать меня."+ GetSexPhrase(" Я обещаю тебе море любви и океан ласки...","") +"", ""+ GetSexPhrase("Вот как?! Хм, не скрою, я польщена, не часто приходится слышать в свой адрес такие слова...","Эх, девушка... как меня достали эти мужики...") +" Слушай, я не занята в данный момент, так что я предлагаю тебе выбрать меня. Обещаю, что ты останешься довол"+ GetSexPhrase("ен","ьна") +"...");
				link.l1 = "Хех, именно тебя и выбираю!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+ GetSexPhrase("Не-е-ет, это был просто комплимент прекрасной даме","Это был просто комплимент") +".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Знаешь что я тебе скажу, милый мой? Не нужно мне пустых разговоров. Займись делом!","Ну вот только этого мне не хватало - комплиментов от женщин!") +"", ""+ GetSexPhrase("Ты тоже воображаешь, что все женщины любят ушами? Хм, это очень зря... Если хочешь меня - плати хозяйке заведения, а трепотня мне не нужна.","Девушка, не растрачивайтесь на пустые слова. Хотите дел - платите...") +"", ""+ GetSexPhrase("Еще один любитель чувственности... Плати - и я буду твоей, но только без этого нежного бреда!","Ты чего, дорогуша? Хочешь удовольствия - плати, а не занимайся болтовней!") +"");
				link.l1 = "Ого, какая хватка!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " все оформляет в своем кабинете. Иди к ней"+ GetSexPhrase(", мой герой,","") +" и назови мое имя - " + npchar.name + ". Я буду тебя ждать...";
			Link.l1 = "Понятно, милая, скоро буду...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
        case "Horse_4":
			dialog.text = NPCStringReactionRepeat("Ты уже оплатил"+ GetSexPhrase("","а") +" девушку, она ждет тебя, поднимайся наверх.", 
				"Я же тебе сказала - поднимайся к ней.", 
				"Слушай внимательно, еще раз повторяю - поднимайся к ней...", 
				"Бесполезно говорить, не доходит...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, я знаю.", "Я помню.",
                      "Можешь не повторять, о ней я помню.", "Хм, о чем это ты?..", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Что-то я тебя не пойму."+ GetSexPhrase(" То комплименты делаешь, то вдруг на попятную идешь. Странный тип...","") +"", 
					"Опять со своим комплиментами? Хм, иди к хозяйке, с ней все решай.", 
					"Хм, и не надоело тебе? Сказала же - иди к хозяйке заведения.", 
					"Нам нельзя здесь оскорблять клиентов, но ты нарываешься, мил"+ GetSexPhrase("ый","ая") +"...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Так вышло, знаешь ли...", "Хорошо, я так и сделаю.",
						"Да-да, я понял"+ GetSexPhrase("","а") +"...", "Хм, извини, дорогуша.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Спасибо за комплимент. Если ты хочешь взять меня, то иди к хозяйке заведения. Все как всегда...";
				Link.l1 = "Понятно.";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Милый, мы все оговорили. ","") +"Не заставляй меня долго ждать...", 
						""+ GetSexPhrase("Хм, послушай, милый, мне","Мне") +" очень приятны все твои слова, но пора уже и за дело браться...", 
						"Послушай, может ты всё-таки уладишь все с хозяйкой?..", 
						"Хм, даже не знаю, что и сказать...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Да ни за что на свете!", "Обязательно!",
							"Да, конечно!", "Бегу, бегу к хозяйке...", npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Я тебя ждала, а ты так и не взял"+ GetSexPhrase("","а") +" меня! Не могу сказать, что я в восторге от этого...";
					Link.l1 = "Гм, так получилось...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Ах-х, это опять ты, мо"+ GetSexPhrase("й славный корсар","я славная девушка") +"! Если тебе опять нужна я, то иди к хозяйке - не пожалеешь..."+ GetSexPhrase(" Кстати, я тебя узнала, дорогой, только мы вынуждены обращаться ко всем клиентам стандартно, ты уж извини...","") +"";
				Link.l1 = "Подожди меня совсем чуть-чуть, "+ GetSexPhrase("красавица","милашка") +", и мы снова с тобой уединимся.";
				Link.l1.go = "exit";
				Link.l2 = "Мне очень приятно, что ты меня запомнила, но сейчас провести с тобой ночь я, сожалению, не могу.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
        case "HorseChoice_2":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Вот что,"+ GetSexPhrase(" милый друг,","") +" займись-ка лучше делом. Это полезней будет, чем языком чесать.", 
					""+ GetSexPhrase("Хм, странный ты,","Ну что ты") +" талдычишь одно и тоже...", 
					"Послушай, может хватит уже?!", 
					"Хм, ну надо же, ничего нового"+ GetSexPhrase(", опять глупые попытки очаровать. Хочешь со мной переспать - иди к хозяйке заведения, недоумок!","...") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Да, слышал"+ GetSexPhrase("","а") +"...", "Хм, вот так оно и выходит...",
						"Хм, может хватит, а может и нет...", "Осторожней в выражениях"+ GetSexPhrase(", коза","") +"...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "А-а-а, это опять ты! "+ GetSexPhrase("И снова с глупыми хвалебными речами, ничего не меняется в этом мире... Е","Напоминаю, е") +"сли хочешь "+ GetSexPhrase("переспать","побаловаться") +" со мной - плати хозяйке заведения, а слова твои мне безразличны...";
				Link.l1 = "Хех, кто бы сомневался...";
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1_Add":
			dialog.text = "Хм, не скажу, что меня это обрадовало... Очень жаль.";
			Link.l1 = "Извини...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		//===>> секс
        case "Horse_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Очень рада видеть тебя в комнате уединения. "+ GetSexPhrase("И чем мы дальше займемся?","Ну что же, будем развлекаться?") +"", "Проходи, не стесняйся"+ GetSexPhrase(", чувствуй себя как дома на ближайшие два часа.",". Я сумею тебя... развлечь, не переживай.") +"");
					Link.l1 = RandPhraseSimple("Скучать не будем, полагаю...", ""+ GetSexPhrase("Давай повеселимся, детка!","Не будем терять времени!") +"");
				break;
				case "1":
					dialog.text = "Ах, вот и ты, мо"+ GetSexPhrase("й славный корсар! Я кое-что обещала тебе и готова сдержать свое слово","я славная девушка! Следующие два часа ты не забудешь никогда") +"...";
					Link.l1 = "Ух, как заманчиво звучит...";	
				break;
				case "2":
					dialog.text = "А-а-а, приш"+ GetSexPhrase("ел","ла") +", наконец-то. Ну, не будем терять времени!";
					Link.l1 = ""+ GetSexPhrase("Не будем, киска...","Ну, покажи мне, что ты можешь...") +"";
				break;
			}
			Link.l1.go = "exit";
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");
			
			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = LinkRandPhrase("Тебе понравилось?", "Ну, что скажешь? Все в порядке?", "Как дела,"+ GetSexPhrase(" корсар, все"," все") +" нормально?");
					Link.l1 = RandPhraseSimple(""+ GetSexPhrase("Конечно, все в порядке","А ты и впрямь... умеешь") +".", ""+ GetSexPhrase("Все в норме, крошка","Ты знаешь, я вполне довольна") +".");
					Link.l1.go = "exit";
				break;
				
				case "1":
					dialog.text = LinkRandPhrase("Ну что, я выполнила обещание?", "Ну, как"+ GetSexPhrase(" я тебе, понравилась",", тебе понравилось") +"?", "Я надеюсь, "+ GetSexPhrase("ты доволен, потому что я о-о-очень довольна","ты довольна. Я старалась") +"...");
					Link.l1 = RandPhraseSimple("Да, мне все очень понравилось.", ""+ GetSexPhrase("Отлично покувыркались, ты была на высоте!","Все было просто замечательно!") +"");	
					Link.l1.go = "exit";
				break;
				
				case "2":
					dialog.text = RandPhraseSimple("Ну все, тебе пора.", "Время вышло,"+ GetSexPhrase(" корсар,","") +" тебе пора на выход.");
					Link.l1 = RandPhraseSimple("Ага, пока...", "До свидания и спасибо тебе...");
					Link.l1.go = "exit";
				break;
			}
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
        case "Horse_AfterSex_2":
            dialog.text = LinkRandPhrase("Заходи к нам еще как-нибудь...", "До свидания и до новых встреч...", "Будем рады видеть тебя у нас еще...");
			Link.l1 = "Ладно...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		case "exit_setOwner":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}

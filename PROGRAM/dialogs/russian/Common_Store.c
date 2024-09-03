// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)
	
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	}
	
	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","гнусная дрянь") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}			
            dialog.text = NPCharRepPhrase(npchar, "Новый клиент - новое золото. "
							+ LinkRandPhrase("Деньги не имеют запаха. ", "Песо не пахнут. ","Одной добродетелью сыт не будешь! ")+
							+GetFullName(npchar)+  " к вашим услугам!",
			                + LinkRandPhrase("Приятно познакомиться с новым клиентом, ", "Рад новому клиенту, ", "Добро пожаловать, ")
							+ GetAddress_Form(NPChar)+ ". Моё имя "  + GetFullName(npchar)+
							+ RandPhraseSimple(", мой магазин к вашим услугам.",", я полностью в вашем распоряжении."));
			link.l1 = "Позвольте представиться. " +RandPhraseSimple("Меня зовут ","Я - ")+ "капитан "+ GetFullName(pchar)+".";
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."), 
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","гнусная дрянь") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."), 
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			dialog.text = NPCharRepPhrase(npchar,
			                 pcharrepphrase(LinkRandPhrase("Капитан ", "Да это "+ GetSexPhrase("сам","сама") +" ", "Кого я вижу? Это же ") +GetFullName(pchar)+"! "
							                 + LinkRandPhrase("Тебя еще не вздернули на рее? Ха-ха!","Говорят, ты "+ GetSexPhrase("был","была") +" в гостях у морского дьявола!", "А я слышал, тебя повесили в Порт-Рояле.")
											  + RandPhraseSimple(" Рад тебя видеть!", " Добро пожаловать!"),
							                LinkRandPhrase("Здравствуйте, ", "Добро пожаловать, ", "Добрый день, ") + "капитан"
											+ RandPhraseSimple(". Вам понравился ",". Приглянулся ли вам ")+" наш"+ RandPhraseSimple(" остров? "," городок? ")
											+ LinkRandPhrase("Тут совсем не плохо,","Отличное место,", ""+ GetSexPhrase("Здесь красивые девушки,","У нас гостеприимный народ,") +"")+RandPhraseSimple(" не правда ли?", " не так ли?")),
							 pcharrepphrase(LinkRandPhrase("Капитан ","Ах, это опять вы, ","Вы меня напугали, ") + GetFullName(pchar)
							 				+ LinkRandPhrase(". Вашим именем матери уже стращают непослушных детей!",". Я надеюсь, у вас нет трений с законом?",". Ваша репутация оставляет желать лучшего.")
											 +LinkRandPhrase(" Чему обязан за ваш визит?"," Что вам угодно?", " Зачем вы пришли?"),
							                "Добро пожаловать, капитан " +GetFullName(pchar)+ LinkRandPhrase("! Немного штормит сегодня",
											"! Похоже, собирается шторм","! Поднимается сильный ветер") +", не правда ли?"));

			link.l1 = NPCharRepPhrase(npchar,
			            pcharrepphrase(LinkRandPhrase("Ты все еще жив, ", "И я тебе "+ GetSexPhrase("рад","рада") +", ","Мы с тобой знали времена и получше, ")
									  +LinkRandPhrase("каналья!","дружище!","морской волк!") +" А я "+ GetSexPhrase("думал","думала") +", "
									  +LinkRandPhrase("твоя жена уже сгрызла тебя с элем!","тебя сожрали термиты!", "твоя старуха сжила тебя со свету!"),
						               LinkRandPhrase("Добрый день, ","Доброго здоровья, ","Привет, ") + GetAddress_FormToNPC(NPChar)+" " +GetFullName(Npchar)
									   +RandPhraseSimple(". Вы правы, ",". Совершенно "+ GetSexPhrase("согласен","согласна") +", ")
									   +LinkRandPhrase("а местные "+ GetSexPhrase("мулатки просто очаровательны","жители очень доброжелательны") +"", "с этим трудно спорить", "а "+ GetSexPhrase("здешние дамы вскружат голову кому угодно","горожане и впрямь весьма любезны") +"")+ "."),
						pcharrepphrase(RandPhraseSimple("К черту такие разговоры, ","Поворачивай на другой галс, ") +GetFullName(Npchar)+ "! "
						              +LinkRandPhrase("Болтаешь, как попугай!", "И не морочь мне голову!","Твои слова не дороже сухаря!")
						              +RandPhraseSimple(" Я "+ GetSexPhrase("пришел","пришла") +" в магазин!"," А зачем ты здесь сидишь?"),
						               "Добрый день, " + GetAddress_FormToNPC(NPChar)+ "! Да, но вчера " + LinkRandPhrase("был полный штиль.",
									    "была отличная погода.", "не было ни ветерка.")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("Свистать всех наверх! ","Трюм к осмотру! ") +LinkRandPhrase("Что нужно "+ GetSexPhrase("джентльмену","джентльмену, ой, пардон, леди") +" удачи в моем магазине, хе-хе?",
													                                 "Какой приятный сюрприз для бедного старого торговца! Хе-хе!", "Каким попутным ветром тебя занесло в мой магазин?"),
            														LinkRandPhrase("Открыть порты!", "Крючья к борту!","Держать прямо по курсу!")+RandPhraseSimple(" У меня вы найдете"," В моем магазине")
																	+LinkRandPhrase(" самые лучшие цены на острове."," прекрасный выбор товаров."," товары самого высшего качества.")
																	+RandPhraseSimple(" Я к вашим услугам"," Все, что пожелаете")+", капитан!"),
													 pcharrepphrase(RandPhraseSimple("Любые товары для "+ GetSexPhrase("джентльменов","джентльменов и леди") +" удачи! Хе-хе! Пока их не повесили сушиться на солнышке!",
													                                 "Ветер качает повешенных в порту и разносит звон цепей. Но песо не пахнут, верно?!"),
                 												"Желаете " +LinkRandPhrase("купить лучшие товары " + NationNameGenitive(sti(NPChar.nation)),"купить или продать груз", "получить выгодный фрахт")
																	+RandPhraseSimple("? Я полностью в вашем распоряжении!","? Мой магазин к вашим услугам!")
																	+RandPhraseSimple(" Рад вас видеть"," Располагайтесь") +", капитан!")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("Мой тебе совет, кэп: не жалей денег на картечь. Обыскивать проще мертвых!",
													                "Я с первого взгляда увидел, что ты "+ GetSexPhrase("ловкий малый","ловкая малая") +". " +RandPhraseSimple("Но теперь я вижу, что ты прямо "+ GetSexPhrase("герой","сорвиголова") +".", "Ты "+ GetSexPhrase("молод","молода") +", но "
																	+RandPhraseSimple("ум у тебя острый.", "тебя не обманешь."))),
													 pcharrepphrase("Я готов покупать у вас весь груз с захваченных призов. Хотите купить золото или серебро? Оно всегда в цене!",
													                "Торговое мореплавание - выгодный бизнес, капитан " + GetFullName(pchar)+", не так ли?")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("Все семьдесят пять не вернулись домой! Они потонули в пучине морской! " ,
													   RandPhraseSimple("Пятнадцать человек на сундук мертвеца!","Пей, и дьявол тебя доведет до конца!") +" Йо-хо-хо! И бутылка рома. ")
													   +RandPhraseSimple("Чего надо, кэп?", "Что вы хотите купить, капитан?"),
													 pcharrepphrase("А вы любите поторговаться, капитан " + GetFullName(pchar)+". Как постоянному клиенту, я предлагаю вам очень выгодные цены!",
													                "Ну хорошо, капитан " + GetFullName(pchar)+", из уважения к вам я готов еще немного уступить в цене! Что вы хотите?")),
												  NPCharRepPhrase(npchar,
												     "Клянусь, мне тошно разговаривать с тобой. "
													 +LinkRandPhrase("Купи два-три земляных ореха. Их так любят свиньи. ","Ты ждешь, что здесь тебе сапоги будут чистить ромом? ",
													 pcharrepphrase("Знаю я вашего брата. Налакаетесь рому - и на виселицу.","Как это твоя мамаша отпустила тебя в море! В море!!! Уж лучше бы ты "+ GetSexPhrase("стал портным","стала портнихой") +"...")),
													 pcharrepphrase(RandPhraseSimple("Я полагал, ","Я надеялся, ")+RandPhraseSimple("что вы покинули наш остров.","что больше никогда вас не увижу.")
													 +RandPhraseSimple(" Мертвецы висят у вас на шее, как мельничные жернова..."," Скольких моряков вы отправили гнить среди кораллов?!"),
													 "Капитан " + GetFullName(pchar)+", ваша страсть к коммерции превосходит все мои ожидания!"
													 +RandPhraseSimple(" Хотите сделать последние покупки перед отплытием?", " Вы хотите купить что-то особенное?"))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Давай, показывай, что у тебя есть, старый пират!",
													               "Я всего лишь хочу посмотреть на ваши товары, любезный."),
													pcharrepphrase("Клянусь виселицей, " +GetFullName(npchar)+", я не позволю тебе водить меня за нос! Живо показывай свои товары!",
													               "Давайте посмотрим ваши товары, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Это точно! Мертвые не кусаются! Ну, что у тебя в трюме есть?",
													               "Вы, милейший, лучше займитесь своим делом. Какие товары можете мне предложить?"),
												    pcharrepphrase("Однажды и ты станешь моим призом, хе-хе. Шучу. Давай свои товары.",
													               "Давайте обсудим торговые дела, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Что мне надо? Хочу купить кое-что!",
													               "Пьянство вас сведет в могилу, " +GetFullName(npchar)+ ". Мне нужно посмотреть ваши товары."),
												    pcharrepphrase("Знаю я твои скидки! Два фунта какао по цене трех! Живо показывай свои товары",
													               "Это всегда приятно. Давайте поторгуемся.")),
											  "Показывай товары, меньше слов и больше дела. Я тороплюсь.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Эх, так бы и "+ GetSexPhrase("прирезал","прирезала") +" кого-нибудь! Ладно, давай к делу.",
													               "Перейдем к другим делам, милейший"),
													pcharrepphrase("Каррамба! Я совсем по другому делу!",
													               "Мне нужно с вами поговорить по делу, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("У меня к тебе дело, старый пират!",
													               "Перейдем к делам, милейший!"),
													pcharrepphrase("Клянусь дьяволом, тебе меня не обмануть, мошенник! У меня другое дело!",
													               "Полностью "+ GetSexPhrase("согласен","согласна") +", " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", я хочу обсудить с вами иные дела.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Уже надрался, приятель?! У меня к тебе дело.",
													               "Я "+ GetSexPhrase("пришел","пришла") +" не торговать, любезный. У меня другое дело."),
													pcharrepphrase("Разрази тебя гром с твоими ценами, негодяй! У меня дело к тебе.",
													               "Скидки всегда приятны, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", но я по другому делу.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Придержи язык, старый пьяница, у меня дело к тебе",
													               "Тошнит вас от рома, я полагаю. Впрочем, я от вас тоже не в восторге. Перейдем к делу."),
													pcharrepphrase("Ты и так уже обобрал меня до нитки, мошенник! У меня к тебе дело.",
													               "Ваша ирония неуместна, у меня к вам дело иного порядка")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Сначала дело, потом веселье. Хочу у тебя узнать кое-что.",
													               "Не сейчас, мне нужна информация."),
													pcharrepphrase("К черту цены! Сначала ты скажешь все, что мне нужно.",
													               "С удовольствием. Я хочу узнать кое-что.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Спасибо за совет, старый убийца. Мне надо кое-что узнать.",
													               "У меня определенный вопрос."),
												    pcharrepphrase("Золото подождет. Я хочу узнать кое-что.",
													               "Да, я "+ GetSexPhrase("согласен","согласна") +". Хочу вас спросить кое о чем.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Я думаю, ты знаешь, о чем я хочу спросить.",
													               "Я надеюсь, вы ответите мне на мой вопрос."),
													pcharrepphrase("У тебя в голове есть что-нибудь кроме ценников? Об этом я и хочу спросить.",
													               "Речь не об этом. Мне нужна кое-какая информация.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Не кипятись, старина! Я просто хочу спросить тебя.",
													               "Не волнуйтесь так, вас хватит удар. Ответьте мне на вопрос, и я уйду"),
													pcharrepphrase("Не жду от тебя умного слова - ум у тебя тараканий. Но ты кое-что знаешь.",
													               "Я не задержу вас надолго. Всего один вопрос.")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Пока, старый пропойца.",
													               "Всего доброго, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Каррамба! Никуда не уходи. Я еще зайду.",
													               "Приятно было вас видеть, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! До свидания!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Отдать швартовы!",
													               "До свидания, милейший."),
													pcharrepphrase("Эй! Ты что там прячешь? Ром? Нет!?! Ну ладно, пойду, горло промочу.",
													               "Прошу меня извинить, у меня срочные дела в городе.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Хех! Еще увидимся!",
													               "Мне надо идти. Прощайте, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("И не смей мне перечить! Недосуг мне тут с тобой спорить!",
													               "Пожалуй, стоит проверить, как дела на корабле. Прощайте, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Что с тобой, старина? Это же я - " +GetFullName(pchar)+ "! Проспись, я потом зайду.",
													               "Боюсь, ваша печень прикончит вас раньше, чем я еще раз зайду сюда."),
													pcharrepphrase("Считай свои песо, пройдоха! Я еще зайду.",
													               ""+ GetSexPhrase("Рад был","Рада была") +" вас видеть, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Извините, но я сейчас занят. Другие клиенты! Заходите завтра.";
				link.l1 = "Да что вы говорите! Ладно, зайду попозже.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("У меня есть сабли, пистолеты, пушечные ядра, ценная древесина и другие товары! Что вас интересует?", "Хотите купить золото или серебро? Или, может, присмотреть отличный клинок?");
			link.l1 = pcharrepphrase(LinkRandPhrase("В моем трюме полно добычи! Песо не пахнут, не так ли?",
			                         "Мне нужно освободить свой трюм от добычи и набить его твоим золотом. Ха-ха!",
									 "За полновесные дублоны ты и родную мать продашь! Но мне всего лишь нужно пополнить запасы."),
									 LinkRandPhrase("Хочу продать груз и пополнить запасы.",
			                         "Я хочу купить товар на продажу.",
									 "Покажи мне ядра, бомбы и прочие товары."));
			link.l1.go = "trade_1";
			link.l2 = LinkRandPhrase("Покажи мне сабли, пистолеты, и что там у тебя еще есть?",
			                         "Мне не помешает пара новых пистолетов, пули и красивый перстень.",
									 "Драгоценные камни, диковинные идолы - вот что меня интересует.");
			link.l2.go = "items";
			link.l3 = pcharrepphrase(RandPhraseSimple("Отчаливаю без торговли. Бывай!",
			                                          "Пойду, горло промочу. Никуда не уходи."),
									 RandPhraseSimple("Нет, мне сейчас не до покупок. Прощайте.",
									                  "Извините, у меня срочное дело. До свидания!"));
			link.l3.go = "exit";
		break;

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Pearl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "С вас за аренду еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Хорошо, сейчас оплачу аренду.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Я зайду попозже.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Проходите.";
				link.l1 = "Спасибо.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Нет, "+ GetSexPhrase("уважаемый","мэм") +", стоит - вас дожидается. Я как знал, что вы не оставите этого предложения.";
			link.l1 = "Это хорошо. Я его арендую.";
			link.l1.go = "storage_1";
			link.l2 = "Да нет, я просто так вспомнил"+ GetSexPhrase("","а") +". Может когда и понадобится...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Как вы помните - оплата за месяц вперёд.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Помню - держите.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Вот чёрт. Сейчас деньги принесу.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Неужели освобождаете? Ай-яй-яй, такое великолепное место, такие выгодные условия. Уверяю - больше нигде на Карибах вам не предложат подобных услуг.";
			link.l1 = "Я же сказал"+ GetSexPhrase("","а") +" - освобождаю. Или вы предлагаете мне платить за хранение воздуха? Можете искать другого арендатора.";
			link.l1.go = "storage_4";
			link.l2 = "Нигде не предложат, говорите? Ладно, оставлю пока за собой. Но цена аренды, долж"+ GetSexPhrase("ен","на") +" сказать... немаленькая, одним словом.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "С вас за аренду еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Хорошо.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Забирайте свой товар и я закрою склад.";
				link.l1 = "Хорошо.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "business":
			iTest = 0;	
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Была у меня работёнка, но " + GetFullName(&Characters[iTmp]) + " уже взялся выполнить ее для меня.";
				link.l1 = "Да что вы говорите! Ладно, зайду попозже.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Дела?! Выкладывай всё по порядку!","Я вас слушаю. О каком деле идёт речь?");
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Расскажешь мне последние сплетни? Все равно торчишь тут целый день.",
                                                          "Не суетись, старый мошенник, а лучше расскажи, как течет жизнь на суше?"),
                                        RandPhraseSimple("Кажется, что провел"+ GetSexPhrase("","а") +" в море целую вечность. Что новенького в ваших краях?",
                                                         "Вы, наверное, знаете все последние новости? Что важного произошло?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage"))
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Проводите меня в пакгауз. Я хочу взглянуть на состояние своего склада.";
						link.l7.go = "storage_0";
						link.l8 = "Я решил"+ GetSexPhrase("","а") +" освободить пакгауз. Он мне больше без надобности.";
						link.l8.go = "storage_04";
					}
				}				
				// <-- ugeen
				
				// <-- homo
				link.l99 = "Впрочем, сейчас не до разговоров.";
    			link.l99.go = "no_quests";
		break;
		
		case "no_quests":
			dialog.text = "В данный момент я не нуждаюсь в ваших услугах.";
			link.l1 = "Очень жаль. Тогда давайте поговорим о другом.";
			link.l1.go = "node_1";
		break;
		
		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

// ugeen --> 
//--> расчет аренды склада
int GetStoragePriceExt(ref NPChar, ref chref)
{
	float fSpeechcraft = 1.5 - GetSummonSkillFromName(pchar, SKILL_SPEECHCRAFT)/120.0;
	
	int price = makeint(15000 * MOD_SKILL_ENEMY_RATE * fSpeechcraft * fSpeechcraft);
	
	return price;
}
//<-- расчет аренды склада

// --> перемещаем остатки груза со склада на корабль ГГ с перегрузом, пусть сам разбирается что делать со всем этим барахлом
void SetStorageGoodsToShip(ref pStorage)
{
	int iStoreQ;
	for (int i = 0; i< GOODS_QUANTITY; i++)
	{
		iStoreQ = GetStorageGoodsQuantity(pStorage, i); 
		if (iStoreQ == 0) continue;
		SetCharacterGoods(pchar, i, GetCargoGoods(pchar, i) + iStoreQ);// перегруз
	}
}
// <-- ugeen


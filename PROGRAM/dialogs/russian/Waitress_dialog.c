
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
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
		
		case "First time":
            NextDiag.TempNode = "First time";
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Прости, "+ GetSexPhrase("красавчик","красавица") +", я занята. Хороший день для таверны - не всегда хороший день для разговора!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Пожалуйста, капитан, не устраивайте дебошей! После них так трудно наводить порядок!";
					link.l1 = ""+ GetSexPhrase("Кхм... Вроде и не собирался.","Я что, похожа на дебоширку?") +"";
					link.l1.go = "exit";
				break;

				case 2:
					dialog.text = ""+ GetSexPhrase("О, капитан! Вы хотели бы попасть в мои объятья сегодня? Я не люблю хвастаться, но ...","Присаживайтесь, капитан. Настоящей морской волчице здесь всегда рады.") +"";
					link.l1 = ""+ GetSexPhrase("Увы, сейчас я спешу! Давай в другой раз!","Cпасибо, милашка.") +"";
					link.l1.go = "exit";
				break;

				case 3:
					dialog.text = "Если вы хотите что-либо заказать - обратитесь, пожалуйста, к хозяину. Он стоит за стойкой.";
					link.l1 = "Спасибо за совет.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Если вы хотите как следует отдохнуть и поправить здоровье - снимите комнату на ночь. Ночевка в общей зале вряд ли прибавит вам сил.";
					link.l1 = "Благодарю.";
					link.l1.go = "exit";
				break;
			}		
			link.l9 = "Я хочу задать тебе пару вопросов.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Вы очнулись?";
			link.l1 = "М-м-м.";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Вам плохо? Болит голова?";
			link.l1 = "Где я, черт возьми?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Так вы ничего не помните? Даже то, как вас ограбили?";
			link.l1 = "Что? Ох... моя голова... Кто посмел?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Откуда мне знать? Пришли, пригрозили убить, обшарили карманы и ушли.";
			link.l2 = "Ладно, что пропало, то пропало.";
			link.l2.go = "exit";
		break;
	}
}
 

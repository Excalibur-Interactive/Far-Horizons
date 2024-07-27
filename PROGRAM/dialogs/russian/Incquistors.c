
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Братья, в Инквизиции враг!!!", "Поднимайте тревогу, братья!!!");
					link.l1 = "Да уж, враги Инквизиции не дремлют...";
					link.l1.go = "fight";			
			}
			else
			{				
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Здравствуй, "+ GetSexPhrase("сын мой","дочь моя") +". Какими судьбами у нас?..", "Рад видеть тебя в нашей обители, "+ GetSexPhrase("сын мой","дочь моя") +". Зачем пожаловал"+ GetSexPhrase("","а") +"?"),
							""+ GetSexPhrase("Сын мой","Дочь моя") +", мы уже говорили с тобой сегодня. Тебе нужно что-то еще?", ""+ GetSexPhrase("Сын мой","Дочь моя") +", послушников нашего ордена не отличает терпение. Еще раз тебя спрашиваю: тебе что-нибудь нужно?",
							RandPhraseSimple("Негоже находится в праздности самому и отвлекать других от работы. Более я не произнесу ни слова...", ""+ GetSexPhrase("Сын мой","Дочь моя") +", я не желаю вести бессмысленные разговоры. Тебе я не скажу более ни слова."), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Да так, заскочил"+ GetSexPhrase("","а") +" по делам, святой отец...", "Все по делам, падре. Тружусь, аки пчела - "+ GetSexPhrase("весь","вся") +" в заботах..."), 
							"Да нет, святой отец...", "Нет, падре, просто хотел"+ GetSexPhrase("","а") +" поболтать...", RandPhraseSimple("Хм...", "Ну, как знаете, святой отец..."), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Черт возьми, это шпион! Держи его!!!";
					link.l1 = "Каррамба!!";
					link.l1.go = "fight";
					StartIncquisitioAttack();
				}
				else
				{
					dialog.text = LinkRandPhrase("Это охраняемая камера, вход сюда категорически запрещен!!!", "Даже и не думай сюда входить - карается смертью.", "Один шаг внутрь этой камеры - и тебе конец...");
					link.l1 = RandPhraseSimple("Ясно, солдат.", "Понятно...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Хо-хо, до чего же весело смотреть, как 'святоши' отправляются прямиком в ад!", "Господи, неужели хоть кто-то осмелился бросить им вызов!!", "Я уже не жилец на этом свете - пытки... Но ты доставил"+ GetSexPhrase("","а") +" мне последнее удовольствие в жизни. Спасибо...");
					link.l1 = RandPhraseSimple("Хех!", "Аргх...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Нет ничего людского у этих 'святош'. Попомни мое слово - гореть им в аду за наши муки...", "Ежедневные истязания и пытки! А ведь я же ни в чем не виноват перед Господом!!!", "Вчера умер мой сосед по камере, они два дня пытали его на дыбе... А сколько мне осталось?..");
					link.l1 = RandPhraseSimple("Хм... Ну, не знаю...", "Что же, понимаю...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "SoldierNotBlade":
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if(sti(pchar.nation) == PIRATE)
				{
					dialog.text = RandPhraseSimple("Пираты в городе?! Ну дела... Хватай е" + GetSexPhrase("го", "ё") + "!!", "Это пират!! Держи е" + GetSexPhrase("го", "ё") + "!!!");
					link.l1 = RandPhraseSimple("Пират, ну и что?..", "Хех, попробуйте схватить.");
					link.l1.go = "fight";
					break;
				}
				dialog.text = RandPhraseSimple("Шпион? Сдать оружие!! Следовать за мной!", "Вражеский агент!! Немедленно схватить е" + GetSexPhrase("го", "ё")  + "!");
				link.l1 = RandPhraseSimple("Заткнись, малахольный!", "Как бы не так!");
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = LinkRandPhrase("Чего вы клинком размахиваете?! Немедленно уберите оружие!", "Приказываю вам немедленно убрать оружие!", "Эй, " + GetAddress_Form(NPChar) + ", не пугайте народ! Уберите оружие.");
				link.l1 = LinkRandPhrase("Хорошо, убираю...", "Уже убрал"+ GetSexPhrase("","а") +".", "Как скажешь...");
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) != RELATION_ENEMY) link.l1.go = "exit";
				else link.l1.go = "First Time"; //Не миновать нам проверки!
				link.l2 = LinkRandPhrase("Черта с два!", "Сейчас пущу его в дело!", "Уберу, когда время придёт.");
				link.l2.go = "fight";
				NextDiag.TempNode = "First Time";
				if (CheckAttribute(NPChar, "protector")) NPChar.greeting = "soldier_arest";
				else NPChar.greeting = "soldier_common";
			}
		break;
}

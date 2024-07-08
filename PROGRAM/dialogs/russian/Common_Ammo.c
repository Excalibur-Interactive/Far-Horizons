// диалог коменданта форта
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = RandPhraseSimple("Я комендант форта. Что вам нужно здесь?", "Что вам нужно? Зачем вы явились в форт?");
			link.l1 = "Да ничего особенного, осматриваю окрестности, знаете ли. Вот и забр"+ GetSexPhrase("ёл","ела") +" сюда по случаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
	}
}
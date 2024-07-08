void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("Господи, как хорошо, что я вас встретила!",
				"Наконец-то хоть кто-то появился здесь!!",
				"Боже мой, как я рада вас видеть!");
			Link.l1 = LinkRandPhrase("Что случилось, крошка?",
				"Какие проблемы, дорогуша?",
				"Не надо так волноваться, это вредно для женского организма. Расскажи-ка мне быстренько, что там у тебя стряслось?");
			Link.l1.go = "Exit";			
		break;
	}
}
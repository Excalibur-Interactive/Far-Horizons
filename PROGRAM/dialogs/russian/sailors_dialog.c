// реплики солдат на палубе при разговоре в море
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "On_Deck":
			dialog.text = "Поговорите с нашим капитаном. Мне нечего вам сказать.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
		break;
	}
}

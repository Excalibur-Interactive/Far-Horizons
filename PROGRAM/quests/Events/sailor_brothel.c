// Моряки желают развлечений -->
void SailorEvent_DefaultExit()
{
	ref sld;
	
	AddPartyCrewMorale(Pchar, 10);
	
	for (int i = 1; i < 4; i++) 
	{
		sld = characterFromID("Sailor_" + i);
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "none", "none");
	}
	
	LAi_MethodDelay("SailorEvent_BrothelFrame", 1.0);
}

void SailorEvent_BrothelFrame()
{
	SetLaunchFrameFormParam("Прошло несколько часов...", "SailorEvent_MamanTalk_1", 0, 5);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 0);
	RefreshLandTime();
	RecalculateJumpTable();
}

void SailorEvent_DeclineExit()
{
	ref sld;
	
	AddPartyCrewMorale(pchar, -1); //to_do: по красноречию
	DeleteAttribute(pchar, "Event.SailorEvent");
	
	for (int i = 1; i < 4; i++)
	{
		sld = characterFromID("Sailor_" + i);
		sld.lifeday = 0;
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "SailorEvent_EraseSailors", -1);
	}
}

void SailorEvent_AgreeExit()
{
	SetLaunchFrameFormParam("Спустя час...", "SailorEvent_ToBrothel", 0, 1);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 0);
	RefreshLandTime();
	RecalculateJumpTable();
}

void SailorEvent_GetOut()
{
	ref sld;
	pchar.quest.SailorEvent_LeftTeam.over = "yes"; //снимаем прерывания
	pchar.quest.SailorEvent_Finish.over = "yes";
	SetTimerFunction("SailorEvent_BrothelToNormal", 0, 0, 1);
	chrDisableReloadToLocation = true;
	for (int i = 1; i < 4; i++)
	{
		sld = characterFromID("Sailor_" + i);
		sld.lifeday = 0;
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "SailorEvent_EraseSailors", -1); //to_do: подправить reload1_back в Blender
	}
	sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
	sld.dialog.currentnode = "First time"; //если была заглушка после отказа от массажа
	DoQuestCheckDelay("SailorEvent_NakedSailor", 4.0);
}

void SailorEvent_BrothelToNormal(string qName)
{
	DeleteAttribute(pchar, "Event.SailorEvent");
}

void SailorEvent_BrothelAfterPenalty(string qName)
{
	//А что если мы выплатили штраф сразу в двух-трёх борделях подряд?
	//тогда нужно разблокировать каждый бордель... иначе вечные заглушки
	aref aHostess;
	makearef(aHostess, TEV.BrothelAfterPenalty);
	int n = GetAttributesNum(aHostess);
	for(int i = 0; i < n; i++) DeleteAttribute(GetCharacter(sti(GetAttributeN(aHostess, i))), "SailorEvent_PenaltyPaid");
}

void SailorEvent_Finish(string qName)
{
	int iTemp;
	string sTemp, sAnsw;
	pchar.quest.SailorEvent_LeftTeam.over = "yes"; //снимаем прерывание
	if(bSeaActive) //FindLocation(pchar.location) нельзя в море
	{
		SailorEvent_LeftTeam("");
		return;
	}
	ref loc = &locations[FindLocation(pchar.location)];
	bool bTown = !CheckAttribute(loc, "townsack") || loc.townsack != PChar.Event.SailorEvent.City;		//мы не в городе и
	if(pchar.location.from_sea != Colonies[FindColony(PChar.Event.SailorEvent.City)].from_sea && bTown)	//при этом корабль не в порту
	{
		SailorEvent_LeftTeam("");	
	}
	else
	{
		if(GetCompanionQuantity(pchar) > 1) sTemp = "в эскадру";
		else sTemp = "на корабль";
		Log_Info("Матросы вернулись " + sTemp);
		
		//слухи после ивента -->
		SailorEvent_DeleteRumours();
		for(int i = 0; i < 3; i++)
		{
			switch(i)
			{
				case 1:
					sTemp = "Вы слышали о том, что целая команда моряков заняла местный бордель и несколько дней развлекалась с тамошними барышнями? Куда только смотрит церковь, не видя такое распутство у себя под носом...";
					sAnsw = "Они ведь мужчины, у которых жизнь полна опасностей, и поэтому им нужно иногда отдохнуть.";
				break;
				case 3:
					sTemp = "Совсем недавно все соседи местного борделя не могли уснуть ночью из-за того, что это гнездо разврата заняли моряки какого-то судна, бросившего якорь у нас в порту. Вы не знаете их капитана?";
					sAnsw = "Нет, не знаю. Кто же это мог быть?";
				break;
				case 5:
					sTemp = "Говорят, в нашем борделе недавно была большая пьянка моряков. Там творился такой разврат, что весь город о нём слышал. Эх, хотелось бы мне там побывать, хоть на пару минут.";
					sAnsw = "Уверена, вы бы управились за это время.";
				break;
			}
			iTemp = FindRumour(AddSimpleRumourCityTip(sTemp, PChar.Event.SailorEvent.City, 30, 1, "citizen", ""));
			Rumour[iTemp].link.l1 = sAnsw;
			Rumour[iTemp].link.l1.go = "new question";
			Rumour[iTemp].link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.", "Всего хорошего.");
			Rumour[iTemp].link.l2.go = "exit";
			Rumour[iTemp].sex = "man";
			Rumour[iTemp].group = "SailorEvent";
		}
		//<-- слухи после ивента
		
		sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
		sld.dialog.currentnode = "First time"; //если была заглушка после отказа от массажа
		DeleteAttribute(pchar, "Event.SailorEvent");
		DoQuestCheckDelay("SailorEvent_EraseSailors", 0.0);
		SailorEvent_CrewToShip();
		AddQuestRecord("SailorEvent", "Holiday_End");
		CloseQuestHeader("SailorEvent");
	}
}

void SailorEvent_LeftTeam(string qName)
{
	ref sld;
	int iTemp;
	string sSay, sAnsw;
	
	AddPartyCrewMorale(Pchar, -3);
	Log_Info("Мораль команды упала!");
	
	AddQuestRecord("SailorEvent", "Left_Team");
	CloseQuestHeader("SailorEvent");
	
	pchar.quest.SailorEvent_Finish.over = "yes"; //снимаем прерывание
	
	//специальные слухи -->
	SailorEvent_DeleteRumours();
	for(int i = 0; i < 3; i++)
	{
		switch(i)
		{
			case 0:
				sSay = "Недавно какой-то капитан оставил в нашем борделе половину своего экипажа развлекаться с девками, а сам взял да и уплыл куда глаза глядят. Эти моряки, узнав о том, что капитан их бросил, очень огорчились, начали громить всё вокруг и бить всех, кто попадался под руки. Хорошо, что стража их быстро уняла.";
				sAnsw = "Печально. Может, у этого капитана были неотложные дела, поэтому им не следовало так переживать? Впрочем, ничего уже нельзя изменить. (про себя) Да уж, не нужно было их оставлять.";
			break;
			
			case 1:
				sSay = "Вы уже слышали о том, что банда пьяных моряков устроила бунт в местном борделе? Слава Богу, наша доблестная стража быстро разобралась с ними. Теперь эти наглецы будут отбывать наказание на каторге.";
				sAnsw = "Нет, не слышала. Знаете, некоторым морякам каторга может показаться раем по сравнению с корабельной службой.";
			break;
			
			case 2:
				sSay = "У нас в городе все только и говорят о том, что какой-то капитан решил интересным способом избавиться от части экипажа, чтобы не платить им жалование. Он оставил их в борделе, развлекаться с девушками, а сам сел на корабль и ушёл за горизонт.";
				sAnsw = "Возможно, всё это вышло случайно. Хотя кому теперь какое дело.";
			break;
		}
		iTemp = FindRumour(AddSimpleRumourCityTip(sSay, PChar.Event.SailorEvent.City, 30, 1, "citizen", ""));
		Rumour[iTemp].link.l1 = sAnsw;
		Rumour[iTemp].link.l1.go = "new question";
		Rumour[iTemp].link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.", "Всего хорошего.");
		Rumour[iTemp].link.l2.go = "exit";
		Rumour[iTemp].group = "SailorEvent";
	}
	//<-- специальные слухи
	
	//Пересчёт оставленных моряков для штрафа
	aref aReserve;
	makearef(aReserve, TEV.TeamReserve);
	int penalty = 0;
	int n = GetAttributesNum(aReserve);
	for(i = 0; i < n; i++) penalty += sti(GetAttributeN(aReserve, i));
	
	sld = characterFromID(PChar.Event.SailorEvent.City + "_Hostess");
	sld.SailorEvent_Block = penalty*60;
	sld.dialog.currentnode = "First time"; //если была заглушка после отказа от массажа
	
	DoQuestCheckDelay("SailorEvent_EraseSailors", 0.0);
	DeleteAttribute(pchar, "Event.SailorEvent");
	DeleteAttribute(&TEV, "TeamReserve");
}

void SailorEvent_CrewToShip()
{
	ref sld;
	aref aReserve;
	string sTemp, sPlace;
	int i, n, idx;
	int overage = 0;
	
	//Сначала распихиваем команды на свои корабли
	for(i = 0; i < COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(GetMainCharacter(),i);
		if(idx >= 0)
		{
			sld = &Characters[idx];
			sTemp = sld.Ship.Type;
			if(GetRemovable(sld) && CheckAttribute(&TEV, "TeamReserve." + sTemp))
			{
				n = sti(TEV.TeamReserve.(sTemp));
				if(GetFreeCrewQuantity(sld) >= n)
					AddCharacterCrew(sld, n);
				else
				{
					overage += n - GetFreeCrewQuantity(sld);
					SetCrewQuantityFull(sld);
				}
				DeleteAttribute(&TEV, "TeamReserve." + sTemp);
			}
		}
	}
	
	//Если корабли продавались, их команда идёт на общее распределение
	makearef(aReserve, TEV.TeamReserve);
	n = GetAttributesNum(aReserve);
	for(i = 0; i < n; i++) overage += sti(GetAttributeN(aReserve, i));
	
	//Потом распихиваем на свободные, если команды менялись / корабли продавались,
	//и какие-то матросы не поместились на родных кораблях
	for(i = 0; i < COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(GetMainCharacter(),i);
		if(idx >= 0)
		{
			sld = &Characters[idx];
			if(GetRemovable(sld) && GetFreeCrewQuantity(sld) != 0)
			{
				if(GetFreeCrewQuantity(sld) >= overage)
				{
					AddCharacterCrew(sld, overage);
					overage = 0;
					break;
				}
				else
				{
					overage -= GetFreeCrewQuantity(sld);
					SetCrewQuantityFull(sld);
				}
			}
		}
	}
	
	if(overage > 0)
	{
		if(GetCompanionQuantity(pchar) > 1) sPlace = "в эскадре";
		else sPlace = "на корабле";
		sTemp = FindRussianSailorString(overage, "Acc");
		Log_SetStringToLog("Для " + sTemp + " не нашлось места " + sPlace + ". Команда недовольна!")
		AddPartyCrewMorale(pchar, -2);
	}
	
	DeleteAttribute(&TEV, "TeamReserve");
}

void SailorEvent_MassageEffectOver(string qName)
{
	Log_TestInfo("Эффект массажа больше не действует!");
}

void SailorEvent_DeleteRumours()
{
	for(int i = 0; i < MAX_RUMOURS; i++)
	{
		if(CheckAttribute(&Rumour[i], "group") && Rumour[i].group == "SailorEvent")
		{
			DeleteRumour(FindRumour(Rumour[i].id));
		}
	}
}

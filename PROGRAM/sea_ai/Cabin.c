// BOAL 09.09.03 Каюта капитана
bool	bCabinStarted = false;
bool	bDeckBoatStarted = false;

void Cabin_ReloadStartFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	LayerFreeze(SEA_EXECUTE,true);
	LayerFreeze(SEA_REALIZE,true);
	LayerFreeze(SEA_REFLECTION2,true);
	LayerFreeze(EXECUTE,false);
	LayerFreeze(REALIZE,false);

	MoveWeatherToLayers(EXECUTE, REALIZE);
	MoveSeaToLayers(EXECUTE, REALIZE);
	HideGrass();

	SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
    // fix -->
    ClearAllFire();
    // fix <--
	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade");

	fOldMaxSeaHeight = stf(Sea.MaxSeaHeight);
	Sea.MaxSeaHeight = 1.2;						// set maxinum sea height for ship abordage
}

void Cabin_ReloadEndFade()
{
	// Delete current cannonballs
	AIBalls.Clear = "";

 	PauseParticles(true);
    //DeleteParticles(); // boal fix костры нах

	// start Cabin location
 	int a = GetEventData();
	aref reload_fader = GetEventData();
	
	Cabin_Start();
	
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void Sea_CabinStartNow()
{
	if (!bCabinStarted)
	{
        bSeaReloadStarted = true;

        Set_My_Cabin();
        
    	object reload_fader;
    	CreateEntity(&reload_fader, "fader");
    	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);
    	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade", 0);
		
    	SendMessage(&reload_fader, "ls", FADER_PICTURE0, Get_My_Cabin_Pic());
    	SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
    	SendMessage(&reload_fader, "l", FADER_STARTFRAME);

    	PauseAllSounds();
		ResetSound(); // new

    	bAbordageStarted = true;
    	bCabinStarted = true;
    	Sea.AbordageMode = true;
	}
	else
	{
	   Return2SeaAfterCabin();
	}
}

//////////////
int cabin_officers;
void Cabin_Start()
{
 //ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	int i;
	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();
	
	ref mchr = GetMainCharacter();
	
	string deckID = "";
	deckID = Get_My_Cabin();
	
	int locID = -1;
	locID = FindLocation(deckID);
	if(locID < 0)
	{
		Trace("Cabin: ship location not found <" + deckID + ">, set default");
	    deckID = "";
	    return;
	}
	//Выставим  и запомним адреса
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	
	//Стартуем
	LAi_boarding_process = false;
	Cabin_LoadLocation(deckID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//Загрузить локацию абордажа
void Cabin_LoadLocation(string locationID)
{
	Log_TestInfo("Cabin_LoadLocation " + locationID);
	ReloadProgressStart();
	//Ищем локацию
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		mchr.location.locator = "loc0";

		//Перегружаемся в локацию
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if(LoadLocation(&Locations[locIndex]))
		{
			//Расставляем персонажей
            SetOfficersInCabin();
			//Запретим диалог
			dialogDisable = false;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
}
void SetOfficersInCabin()
{
    //Устанавливаем офицеров, если такие есть
    ref chr, mchr;
    int i;
    int idx;
    
    mchr = GetMainCharacter();
	for (i = 1; i < 4; i++)
	{
		idx = GetOfficersIndex(mchr, i);
		if (idx < 1) continue;
		chr = &Characters[idx];
		PlaceCharacter(chr, "rld", mchr.location);
	}
}
void SetOfficersLocationToNone()
{
    //Устанавливаем офицеров, если такие есть
    ref chr, mchr;
    int i;
    int idx;

    mchr = GetMainCharacter();
	for (i = 1; i < 4; i++)
	{
		idx = GetOfficersIndex(mchr, i);
		if (idx < 1) continue;
		chr = &Characters[idx];
		chr.location = "none";
	}
}
/////////////
void Return2SeaAfterCabin()
{
	Log_TestInfo("Return2SeaAfterCabin");
	
 	Return2SeaClearNPC();

    //Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter", 0);
	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "loading\sea.tga");

	float fadeOutTime = RELOAD_TIME_FADE_OUT;

	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}


void Return2SeaClearNPC()
{
	if (bDeckBoatStarted)
    {
        // палуба
    	DeleteNPCfromDeck();
	}
	else
	{
    	SetOfficersLocationToNone(); // офицеры в сад
    	SetPrisonerLocationToNone(); //пленных туда же
    	SetOfficersInCampusToNone():
		CompanionSaveTasks(); //компаньонов тоже.
    	DeleteQuestAttribute("SetNPCInShipDeck");
    	DeleteQuestAttribute("SetNPCInShipCabin");
    	DeleteQuestAttribute("SetNPCInShipCampus");
	}
	DeleteAttribute(pchar, "GenQuest.CaptainId");
}

void Cabin_ReloadStartFadeAfter()
{
	//Выгружаем локацию
	ResetSound(); // new
	PauseAllSounds();
	
	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void Cabin_ReloadEndFadeAfter()
{
	ref sld;
	//Загружаем следующую локацию
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	boarding_location = -1;
	//Настроим интерфейс
	Log_SetActiveAction("Nothing");
	EndBattleLandInterface();
	//Востановим адреса
	ref mchr = GetMainCharacter();
	mchr.location = boarding_adr[0].location;
	mchr.location.group = boarding_adr[0].group;
	mchr.location.locator = boarding_adr[0].locator;
	
	// если бой, то ломаем корпус -->
	if (bDisableMapEnter) //идет бой
	{
	    mchr.Ship.HP = makefloat(stf(mchr.Ship.HP) - GetCharacterShipHP(mchr) * 0.01);
	    if (stf(mchr.Ship.HP) < 0) mchr.Ship.HP = 0;
	} 
	// если бой, то ломаем корпус <--
	
	
	//Выгружаемся в интерфейс		
	LAi_boarding_process = false;

 	LayerFreeze(EXECUTE, true);
	LayerFreeze(REALIZE, true);

	LayerFreeze(SEA_REFLECTION2, false);
	LayerFreeze(SEA_EXECUTE, false);
	LayerFreeze(SEA_REALIZE, false);

	MoveWeatherToLayers(SEA_EXECUTE, SEA_REALIZE);
	MoveSeaToLayers(SEA_EXECUTE, SEA_REALIZE);
	ShowGrass();

	Sea.MaxSeaHeight = fOldMaxSeaHeight;		// restore old MaxSeaHeight
	bAbordageStarted = false;
	bCabinStarted    = false;
	bDeckBoatStarted = false;
	Sea.AbordageMode = false;

	InitBattleInterface();
	StartBattleInterface();
	RefreshBattleInterface();

	SetSchemeForSea();

	PauseParticles(false);

	bSeaReloadStarted = false;

	Ship_RecreateStaticSounds();
	// <--
	// boal 24.04.04 ругаем группы тут -->
	if (CheckAttribute(mchr, "StartBattleAfterDeck"))
	{
        Ship_NationAgressivePatent(characterFromID(mchr.StartBattleMainCaptanId));  //патент
        Ship_FlagRefresh(characterFromID(mchr.StartBattleMainCaptanId)); //флаг на лету
        SetCharacterRelationBoth(GetCharacterIndex(mchr.StartBattleMainCaptanId), GetMainCharacterIndex(), RELATION_ENEMY);
	    Group_SetTaskAttack(mchr.StartBattleEncGroupName, PLAYER_GROUP);

	    SetNationRelation2MainCharacter(sti(Characters[GetCharacterIndex(mchr.StartBattleMainCaptanId)].nation), RELATION_ENEMY);
	    UpdateRelations();
	    RefreshBattleInterface();
	    DeleteAttribute(mchr, "StartBattleAfterDeck"); // очищаем начало битвы
	    DoQuestCheckDelay("NationUpdate", 3.0);
	}
	// <-- ugeen
	// boal 24.04.04 ругаем группы тут <--
	
	// fix огней
	DeleteParticles();
	CreateParticleEntity();
}


/////////// диалог на палубе ////////////
void Sea_DeckBoatStartNow(ref _iShipsCharacter)
{
	string boat_pic = "loading\boat.tga";	
	if(CheckAttribute(pchar, "TownEscape")) boat_pic = "loading\Start_Loading.tga";
	
	if (!bAbordageStarted)
	{
	    bSeaReloadStarted = true;

		object reload_fader;
		CreateEntity(&reload_fader, "fader");
		SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);  // одинаковый с каютой
		SetEventHandler("FaderEvent_EndFade", "DeckBoat_ReloadEndFade", 0);
		
		SendMessage(&reload_fader, "ls", FADER_PICTURE0, boat_pic);
		SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
		SendMessage(&reload_fader, "l", FADER_STARTFRAME);

        MakeCloneShipDeck(_iShipsCharacter, false); // подмена палубы
		SetSailorDeck_Ships(_iShipsCharacter);

		PauseAllSounds();
	 	//ResetSoundScheme();
		ResetSound(); // new

	    //PlaySound("Abandon_0");// шлюпки на воду!

		bAbordageStarted = true;
		bDeckBoatStarted = true;
		Sea.AbordageMode = true;
	}

}

void DeckBoat_ReloadEndFade()
{
	// Delete current cannonballs
	AIBalls.Clear = "";
 	PauseParticles(true);
    //DeleteParticles(); // boal fix костры нах

	// start DeckBoat location
	int a = GetEventData();
	aref reload_fader = GetEventData();

	DeckBoat_Start();

	DelEventHandler("FaderEvent_EndFade", "DeckBoat_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}
void DeckBoat_Start()
{
 //ResetSoundScheme();
	//ResetSound(); // new
	//PauseAllSounds();
	int i;
	//Настроим интерфейс
	DeleteBattleInterface();
	StartBattleLandInterface();
    if(!CheckAttribute(GetMainCharacter(), "TownEscape")) 
	{
		PlaySound("Abandon_0");// шлюпки на воду!
	}	
	ref mchr = GetMainCharacter();

	string DeckBoatID = "";
	DeckBoatID = "Deck_Near_Ship";


	int locID = -1;
	locID = FindLocation(DeckBoatID);
	if(locID < 0)
	{
		Trace("Boarding: ship location not found <" + DeckBoatID + ">, set default");
	    DeckBoatID = "";
	    return;
	}
	//Выставим  и запомним адреса
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group = "";
			boarding_adr[i].locator = "";
			continue;
		}
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group = Characters[idx].location.group;
		boarding_adr[i].locator = Characters[idx].location.locator;
	}

	//Стартуем
	LAi_boarding_process = false;
	DeckBoat_LoadLocation(DeckBoatID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//Загрузить локацию абордажа
void DeckBoat_LoadLocation(string locationID)
{
	ReloadProgressStart();
	//Ищем локацию
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();

		DeleteAttribute(mchr, "StartBattleAfterDeck"); // очищаем начало битвы

		mchr.location = locationID;
		mchr.location.group = "goto";
		mchr.location.locator = "goto5";


		//Перегружаемся в локацию
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if(LoadLocation(&Locations[locIndex]))
		{
			//Запретим диалог
			dialogDisable = false;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
}
void Sea_DeckBoatLoad(int ShipsCharacter)
{
	if (bSeaActive == false) { return; }
	ref rCharacter = GetCharacter(ShipsCharacter);

	if (LAi_IsDead(rCharacter)) return;  // нефиг, а то в списке есть трупы
	
	Sea_DeckBoatStartNow(rCharacter);
}

void SetSailorDeck_Ships(ref Chref)
{
	String characterID = Chref.id;
	ref sld;
    string  ani, model;
    int cn, Rank = 10;

	// здесь настоящий кэп, не клон
	LAi_SetWarriorType(Chref);
	LAi_warrior_DialogEnable(Chref, true);
	LAi_SetLoginTime(Chref, 0.0, 24.0); // фикс, чтоб были всегда
	// запоминаем старый диалог
	if (CheckAttribute(Chref, "Dialog.Filename"))
	{
	    Chref.Bak.Dialog.Filename    = Chref.Dialog.Filename;
	    Chref.Bak.Dialog.CurrentNode = Chref.Dialog.CurrentNode;
	}
	else
	{
	    Chref.Bak.Dialog.Filename    = "";
	    Chref.Bak.Dialog.CurrentNode = "First time";
	}
	
	if (!CheckAttribute(Chref,"DeckDialogNode"))
	{
	    Chref.Dialog.Filename = "captains_dialog.c";
		Chref.greeting = "Gr_Commander";
		Chref.Dialog.CurrentNode = "First time";
	}
	else
	{
	    Chref.Dialog.CurrentNode = Chref.DeckDialogNode;
	}
	
	// boal кусок кода для запрета повторных наездов на капитана -->
	if (CheckAttribute(Chref, "talk_date_Go_away") && Chref.talk_date_Go_away == LastSpeakDate())
	{
	    Chref.Dialog.CurrentNode = "Go_away";
    }
	
	// boal кусок кода для запрета повторных наездов на капитана <--
    ChangeCharacterAddressGroup(Chref, "Deck_Near_Ship", "goto", "goto9");

    for (int i = 1; i < 5; i++)
    {
        model = LAi_GetBoardingModel(Chref, &ani);
		cn = NPC_GenerateCharacter("sailor_" + i, model, "man", ani, Rank, sti(Chref.nation), 0, true, "soldier");
		sld = &Characters[cn];
        LAi_SetWarriorType(sld); // участвуют в расстреле - переинитим тип
    	LAi_warrior_DialogEnable(sld, true);
	    sld.name    = "Матрос";
	    sld.lastname = "";
        sld.Dialog.Filename = "sailors_dialog.c";
    	sld.Dialog.CurrentNode = "On_Deck";
    	sld.greeting = "sea_sailors";
	}

	ChangeCharacterAddressGroup(characterFromID("sailor_1"), "Deck_Near_Ship", "goto", "goto8");
	ChangeCharacterAddressGroup(characterFromID("sailor_2"), "Deck_Near_Ship", "goto", "goto3");
	ChangeCharacterAddressGroup(characterFromID("sailor_3"), "Deck_Near_Ship", "goto", "goto6");
	ChangeCharacterAddressGroup(characterFromID("sailor_4"), "Deck_Near_Ship", "goto", "goto7");
}

void DeleteNPCfromDeck()
{
    int i;
    ref Cref;
	
    for (i=0; i< TOTAL_CHARACTERS; i++)
    {
        Cref = GetCharacter(i);

        if (CheckAttribute(Cref, "location"))
        {
            if (Cref.location == "Deck_Near_Ship")
            {
               Cref.location = "none";
               // диалог в зад
               if (CheckAttribute(Cref, "Dialog.Filename") && Cref.Dialog.Filename == "captains_dialog.c")
               {
                   Cref.Dialog.Filename    = Cref.Bak.Dialog.Filename;
                   Cref.Dialog.CurrentNode = Cref.Bak.Dialog.CurrentNode;
               }
            }
        }
    }
}

///////////////// пленный в трюме //////////////////
void SetPrisonerLocationToNone()
{
    ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
	            {
			        offref.location = "none";
                }
            }
        }
    }
}

void SetPrisonerInHold()
{
    //Устанавливаем пленных, если такие есть
	ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
	            {
                    PlaceCharacter(offref, "goto", mchr.location);
                }
            }
        }
    }
}
//////////////////  кампус /////////////////
void SetOfficersInCampusToNone()
{
    ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if (!CheckAttribute(offref,"prisoned") || sti(offref.prisoned) == false)
            {
	            if (GetRemovable(offref) && !IsOfficer(offref))  // не боевики и квестовые
	            {
			        offref.location = "none";
                }
            }
        }
    }
}
void SetOfficersInCampus()
{
    //Устанавливаем пассажиров офов, если такие есть
	ref offref;
    int i, cn;

    ref mchr = GetMainCharacter();

    for (i=0; i < GetPassengersQuantity(mchr); i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if (!CheckAttribute(offref,"prisoned") || sti(offref.prisoned) == false)
            {
	            if (GetRemovable(offref) && !IsOfficer(offref))  // не боевики и квестовые
	            {
                    LAi_SetCitizenType(offref);
					PlaceCharacter(offref, "goto", mchr.location);
                }
            }
        }
    }

	//navy --> компаньоны
 	if (!bDisableMapEnter) //не идет бой
	{
		for (i = 1; i < GetCompanionQuantity(PChar); i++)
		{
			if (!CheckAttribute(GetCharacter(GetCompanionIndex(PChar, i)), "Tasks.Clone"))
			{
				PlaceCompanionCloneNearMChr(i, true);
			}
		}
	}
	//navy <-- 19.02.08
}
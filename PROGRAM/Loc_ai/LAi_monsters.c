//Создать фантома основываясь на характуристиках данного персонажа в самом дальнем углу
void LAi_GenerateFantomFromMe(aref chr)
{
	//Проверяем возможность генерации фантома в данной локации
	if(!TestRef(loadedLocation)) return;
	if(!IsEntity(loadedLocation)) return;
	if(LAi_LocationIsFantomsGen(loadedLocation) == false) return;
	//Проверяем возможность перерождения персонажа
	if(LAi_CharacterIsReincarnation(chr) == false) return;
	//Проверяем какую модельку использовать для перерождения
	bool isGen = LAi_CharacterReincarnationMode(chr);
	if(CheckAttribute(chr, "model") == false) isGen = true;
	if(CheckAttribute(chr, "model.animation") == false) isGen = true;
	if(chr.model == "") isGen = true;
	if(chr.model.animation == "") isGen = true;
	string model, ani;
	if(isGen)
	{
		int nat = GetLocationNation(loadedLocation)
		if(nat < 0) nat = PIRATE;
		if(nat >= MAX_NATIONS) nat = PIRATE;
		if(CheckAttribute(&Nations[nat], "fantomModel") == false)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include fantoms");
			return;
		}
		aref fantoms;
		makearef(fantoms, Nations[nat].fantomModel);
		int num = GetAttributesNum(fantoms);
		if(num <= 0)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include have fantoms");
			return;
		}
		num = rand(num - 1);
		string m = GetAttributeName(GetAttributeN(fantoms, num));
		model = fantoms.(m);
		ani = "man";
		m = m + ".ani";
		if(CheckAttribute(fantoms, m) != false)
		{
			ani = fantoms.(m);
		}
	}else{
		model = chr.model;
		ani = chr.model.animation;
	}
	//Сохраняем параметры персонажа
	object tmp;
	CopyAttributes(&tmp, chr);
	//Создаём фантома	
	if(ani == "mushketer")
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", chr.rank, sti(chr.nation), sti(chr.lifeDay), false, sti(chr.fraction)));
		sld.id = "GenChar_" + sld.index;
		sld.reputation = chr.reputation;
		sld.City = chr.City;
        sld.CityType = chr.CityType;
		sld.RebirthPhantom = true; 
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";
		LAi_CharacterReincarnation(sld, true, true);
		LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(sld, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); // бравые орлы
		}
		LAi_SetLoginTime(sld, 6.0, 23.0); //а ночью будет беготня от патруля :)		
		sld.dialog.filename = chr.dialog.filename;
		sld.dialog.currentnode = chr.dialog.currentnode;
		SetRandomNameToCharacter(sld);
		LAi_SetPatrolType(sld);
		LAi_group_MoveCharacter(sld, chr.chr_ai.group);
		PlaceCharacter(sld, "patrol", "random_free");
		
		if(CheckAttribute(sld, "chr_ai.poison"))
		{
			DeleteAttribute(sld, "chr_ai.poison");
			DeleteAttribute(sld, "chr_ai.poisondmg");
			DeleteAttribute(sld, "chr_ai.NoAntidoteTime");
	        DeleteAttribute(sld, "chr_ai.DrinkedAntidotes");
		}
	}
	else
	{
		ref fnt = LAi_CreateFantomCharacterEx(model, ani, LAi_CharacterReincarnationGroup(chr), "");
		string curidx = fnt.index;
		//Устанавливаем параметры предыдущего персонажа
		CopyAttributes(fnt, &tmp);
		// boal оружие дать! 19.01.2004 -->
		// фантомы точные клоны SetFantomParam(fnt);  
		//--> eddy. шаг на увеличение ранга фантома.
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(fnt, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); // бравые орлы
			characters[sti(fnt.baseIndex)].rank = fnt.rank; //в структуру прародителя ранг с наворотом
		}
		else //не даем падать рангу от SetFantomParam
		{
			LAi_NPC_Equip(fnt, sti(fnt.rank), true, true);
			LAi_SetCurHPMax(fnt);
		}
		// boal 19.01.2004 <--
		if(CheckAttribute(fnt, "chr_ai.group"))
		{
			LAi_group_MoveCharacter(fnt, fnt.chr_ai.group);
		}else{
			LAi_group_MoveCharacter(fnt, "");
		}
		//Сохраняем модельку и анимацию
		fnt.model = model;
		fnt.model.animation = ani;
		//Инициализируем тип
		if(!CheckAttribute(fnt, "chr_ai.type")) fnt.chr_ai.type = "";
		string chrtype = fnt.chr_ai.type;
		SetRandomNameToCharacter(fnt);
		fnt.id = tmp.id;
		fnt.index = curidx;
		LAi_tmpl_stay_InitTemplate(fnt);
		fnt.chr_ai.type = "";
		if(chrtype != "")
		{
			chrtype = "LAi_type_" + chrtype + "_Init";
			call chrtype(fnt);
		}
		SetNewModelToChar(fnt);   // fix
		
		if(CheckAttribute(fnt, "chr_ai.poison"))
		{
			DeleteAttribute(fnt, "chr_ai.poison");
			DeleteAttribute(fnt, "chr_ai.poisondmg");
			DeleteAttribute(fnt, "chr_ai.NoAntidoteTime");
	        DeleteAttribute(fnt, "chr_ai.DrinkedAntidotes");
		}
	}
}

bool LAi_CreateEncounters(ref location)
{
	aref grp, st, at;
	ref chr, rCharacter;
	string encGroup, str, locator, sAreal, sCity;
	int num, i, iChar, iNation, iRank, n, iTemp, iMassive, iRnd, iRand;
	string model[10];
	if (!bLandEncountersGen) //если прерывание на локацию, энкаунтеров не генерим
	{		
		bLandEncountersGen = true;
		return false;
	}
	
	//Можем ли генерить
	if(CheckAttribute(location, "DisableEncounters")) return false;
	if(!CheckAttribute(location, "locators.encdetector") || !CheckNPCQuestDate(location, "Enc_date") || bDisableLandEncounters) return false;
	if(CheckAttribute(location, "fastreload")) return false; //отсекаем локации exitTown у пиратских городов
    //boal 02.09.06 пауза случаек на один раз -->
	if (CheckAttribute(pchar, "GenQuest.Enc2Pause"))
	{
	    DeleteAttribute(pchar, "GenQuest.Enc2Pause");
	    return false;
	}
	// boal <--
	//--> если бухта и в ней контра, то не ставим никого
	if (location.type == "seashore") 
	{
		makearef(st, location.models.always);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);	
			str = GetAttributeName(at);
			if(st.(str) == "smg")
			{
				return false;
			}
		}			
	}
	//<-- если бухта и в ней контра, то не ставим никого
	SetNPCQuestDate(location, "Enc_date"); //запись на дату не сегодня
	//Установить нацию патруля 
	
	sAreal = GiveArealByLocation(location);
	if (sAreal == "none") return false;
	
	// На необитаемых этого всего нету, но там нету и этих квестов
	if(!CheckAttribute(location, "onUninhabitedIsland"))
	{
		sCity = GetCityNameByIsland(sAreal);
		if (sCity == "none") return false;
		iNation = GetCityNation(sCity);
		if (iNation == -1 || iNation == PIRATE) return false;
	}
	
	// Warship 10.08.09 Если прерывание на локацию - не генерим энкаунтеров, иначе погло накладываться, судя по всму
	// bLandEncountersGen устанавливался вручную и не гарантиварол избежание пересечений квест-энкаункеры
	if(!isLocationFreeForQuests(location.Id)) return false;
	
	//группа, куда будем помещать фантомов
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, location.(str));
	if(CheckAttribute(location, "onUninhabitedIsland") || CheckAttribute(location, "deadlocked")) 
	{
		iRand = rand(1) + 5;
	}	
	else
	{	
		iRand = rand(4);		
	}	
	switch (iRand)
	{
		case 0:
			Log_TestInfo("Encounter Placeholder");
		break;
	}
	return true;
}
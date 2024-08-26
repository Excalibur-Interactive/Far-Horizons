#include "scripts\colony.c"
#include "scripts\food.c"
#include "scripts\Rumour_Init.c" // homo 23/06/06
#include "scripts\islandships.c"
#include "scripts\officers.c"
#include "scripts\companions.c"
#include "scripts\ShipsUtilites.c"
#include "scripts\Crew.c"
#include "scripts\bountyhunters.c"
#include "scripts\tavern.c"
#include "scripts\idioms.c"
#include "scripts\smuggling.c"
#include "scripts\PsHero.c" // navy
#include "scripts\duel.c" // navy
#include "scripts\MerchantOnMap.c" // homo 29/07/06
#include "scripts\Siege.c" // homo 09/09/06 Осады
#include "scripts\Treasure.c"  // boal 02.09.06 клады
#include "scripts\CompanionTravel.c" // Warship 17.07.08 Методы для свободного плавания компаньонов
#include "scripts\GameModeCondition.c" // Warship. Обраобтка прерывания, выполняющегося в каждом фрейме

#define MAN 0
#define WOMAN 1

#define WITHOUT_SHIP 0
#define WITH_SHIP 1

#define WARRIOR 0
#define CITIZEN 1
#define TRADER 2
#define BOSS	3
#define FORT_COMMANDER	4
#define BOUNTY_HUNTER	5
#define SHAMAN	6
#define SOLDIER	7
#define OFFICER	8

#define QUEST_NOT_ACCEPTED	0
#define QUEST_ACCEPTED	1
#define QUEST_COMPLETED	2

void SetNames()
{
	for(int i = 1; i <MAX_CHARACTERS; i++)
	{
		if (!CheckAttribute(&Characters[i], "name") || Characters[i].name == "none")
		{
			SetRandomNameToCharacter(&Characters[i]);
		}
	}
}

void SetNationRelations()
{
    Nations_SetAllFriends();
	
	SetNationRelationBoth(ENGLAND, FRANCE, RELATION_NEUTRAL);
	SetNationRelationBoth(ENGLAND, HOLLAND, RELATION_ENEMY);
	SetNationRelationBoth(ENGLAND, SPAIN, RELATION_NEUTRAL);
	SetNationRelationBoth(ENGLAND, PIRATE, RELATION_ENEMY);
	
	SetNationRelationBoth(FRANCE, ENGLAND, RELATION_NEUTRAL);
	SetNationRelationBoth(FRANCE, HOLLAND, RELATION_NEUTRAL);
	SetNationRelationBoth(FRANCE, SPAIN, RELATION_ENEMY);
	SetNationRelationBoth(FRANCE, PIRATE, RELATION_ENEMY);

	SetNationRelationBoth(SPAIN, ENGLAND, RELATION_NEUTRAL);
    SetNationRelationBoth(SPAIN, FRANCE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, HOLLAND, RELATION_NEUTRAL);
	SetNationRelationBoth(SPAIN, PIRATE, RELATION_ENEMY);

    SetNationRelationBoth(HOLLAND, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(HOLLAND, FRANCE, RELATION_NEUTRAL);
    SetNationRelationBoth(HOLLAND, SPAIN, RELATION_NEUTRAL);
	SetNationRelationBoth(HOLLAND, PIRATE, RELATION_ENEMY);
    
	// ГГ отношения от нации
	pchar = GetMainCharacter();
	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(sti(pchar.nation), ENGLAND));
	SetNationRelation2MainCharacter(FRANCE,  GetNationRelation(sti(pchar.nation), FRANCE));
	SetNationRelation2MainCharacter(SPAIN,   GetNationRelation(sti(pchar.nation), SPAIN));
	SetNationRelation2MainCharacter(PIRATE,  GetNationRelation(sti(pchar.nation), PIRATE));
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(sti(pchar.nation), HOLLAND));
}

// метод установки отношений по дипломату
void ChangeNationRelationFromRelationAgent(aref chr)
{
	int iNation = sti(chr.quest.relation);

    int iDays = rand(10) + 5;
	string sQuest = "Change_Relation_for_Nation_" + GetNationNameByType(iNation) + "_by_relation_agent_" + iDays;
	
	SetTimerCondition(sQuest, 0, 0, iDays, false);
	pchar.quest.(sQuest).function = "ChangeNationRelationFromRelationAgentComplete";
	pchar.quest.(sQuest).nation = iNation;
}

void ChangeNationRelationFromRelationAgentComplete(string sQuest)
{
	int iNation = sti(pchar.quest.(sQuest).nation);
    string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
    
	SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
	ChangeCharacterNationReputation(pchar, iNation, sti(Pchar.GenQuest.(sNation)));
	sti(Pchar.GenQuest.(sNation)) = 0; // чтоб второй раз не было
	sNation = "RelationAgent" + GetNationNameByType(iNation);
    Pchar.GenQuest.(sNation) = false;
    
	Log_Info("Дипломат выполнил свою работу.");
}

int CalculateRelationSum(int iNation)
{
	string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
	Pchar.GenQuest.(sNation) = abs(ChangeCharacterNationReputation(pchar, iNation, 0))
	int iSumm = sti(Pchar.GenQuest.(sNation)) * 1500 +  makeint(stf(Pchar.rank)/stf(Pchar.reputation)*100000);

	//iSumm = iSumm * (1.0 + (0.1 * MOD_SKILL_ENEMY_RATE));
	
	return iSumm;
}
// to_do del нигде не используется
bool CreateParticleSystemOnLocator(string _location_id, string _locatorName, string _particleName)
{
	aref locator;
	if (!FindLocator(_location_id, _locatorName, &locator, true))
		return false;

	CreateParticleSystemX(_particleName,stf(locator.x),stf(locator.y),stf(locator.z), stf(locator.vz.x),stf(locator.vz.y),stf(locator.vz.z),0);
	return true;
}

void GenerateMaps(aref ch, int iProbability1, int iProbability2)
{
	int rank = sti(PChar.rank);
	
	if(rand(10) == 1) AddItems(ch, "map_bad", 1);
	if(rand(40) == 1 && rank >= 4) AddItems(ch, "map_normal", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) AddItems(ch, "map_jam", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) AddItems(ch, "map_cayman", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) AddItems(ch, "map_barbados", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) AddItems(ch, "map_trinidad", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) AddItems(ch, "map_Curacao", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) AddItems(ch, "map_martiniqua", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) AddItems(ch, "map_dominica", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) AddItems(ch, "map_puerto", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) AddItems(ch, "map_cuba", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) AddItems(ch, "map_hisp", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) AddItems(ch, "map_nevis", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) AddItems(ch, "map_guad", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) AddItems(ch, "map_antigua", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) AddItems(ch, "map_TORTUGA", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) AddItems(ch, "map_terks", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) AddItems(ch, "map_sm", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) AddItems(ch, "map_bermudas", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) AddItems(ch, "map_Pearl", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) AddItems(ch, "map_beliz", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) AddItems(ch, "map_santa", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) AddItems(ch, "map_maine_1", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) AddItems(ch, "map_maine_2", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) AddItems(ch, "map_panama", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) AddItems(ch, "map_maracaibo", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) AddItems(ch, "map_cumana", 1);
}

void GiveItemToTrader(aref ch)
{
	int i, j, irand;
	String itemID;
	int rank = sti(PChar.rank); // makeint(pchar.rank) - и так было везде... Нет бы сразу переменную завести - это ведь быстрее будет в разы
	ref itm; // ref itm = ItemsFromID("map_LSC"); - тоже самое... Че за бред, заводить переденную внутри блока иф?
	
	DeleteAttribute(ch, "items");
	// boal зачем они в продаже?  ДЛЯ ОТЛАДКИ  -->
	if(bBettaTestMode)
	{
    	for(i = 0; i < ITEMS_QUANTITY; i++)
    	{
			itemID = Items[i].ID;
			irand = rand(2) + 1;
			
			// Warship переделка
			if(IsGenerableItem(itemID)) // Уникальные предметы, которые сначало нужно генерить
			{
				GenerateAndAddItems(ch, itemID, irand);
				continue;
			} 
			
            AddItems(ch, itemID, irand);
    	}
		
		return;
	}
			
}

string PlaceCharacter(aref ch, string group, string location) //boal change
{  // location = "random"  "random_free"  и "random_must_be" - должен быть, даже если все занято  random_must_be_near - рядом
	float locx;
	float locy;
	float locz;
	string homelocator;
	bool ok;
	
	GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
	if (location == "random_free") location = "random"; // совместимость с пред. правкой
	
	if (location == "random" || location == "random_must_be")
	{
		homelocator = LAi_FindFreeRandomLocator(group);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	else
	{
		homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
		if (location == "random_must_be_near")
		{
		    ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
		}
		else
		{
			ChangeCharacterAddressGroup(ch, location, group, homelocator);
		}
	}

	if (homelocator == "" && location == "random_must_be") // дело плохо, свободных уже нет, но НПС-то нужен, ищем затяный
	{
	    homelocator = LAi_FindFarLocator(group, locx, locy, locz);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	if (homelocator == "" && location == "random_must_be_near") // дело плохо, свободных уже нет, но НПС-то нужен, ищем затяный
	{
	    homelocator = LAi_FindNearestLocator(group, locx, locy, locz);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
    return homelocator; // boal нужно проверять куда его занесло
}

void PrepareVisitCity()
{
	string sQuest;
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if (Colonies[i].nation != "none")
		{
			sQuest = "VisitColony_" + Colonies[i].id;
			pchar.quest.(sQuest).win_condition.l1 = "location";
			pchar.quest.(sQuest).win_condition.l1.location = Colonies[i].id + "_town";
			pchar.quest.(sQuest).win_condition = "FirstVisitCity";
			pchar.quest.(sQuest).function      = "FirstVisitCity";
			pchar.quest.(sQuest).colonyId = Colonies[i].id;
		}
	}
}

void FirstVisitCity(string sQuest)
{
	string sColony = pchar.quest.(sQuest).colonyId;
	Colonies[FindColony(sColony)].visited = true;
}

// переделал 25.09.06 метод не зависит от ГГ, просто ранд корабли для порта
int SearchForMaxShip(aref chr, int isLock, int _tmp)
{
	int iType;
	
	if (sti(chr.nation) != PIRATE)
	{
		if (rand(100) > 70)
		{
			iType = rand(SHIP_FRIGATE);	
		}
		else
		{
			iType = rand(SHIP_BRIG);	
		}
	}
	else
	{
	 	if (rand(100) > 70)
		{
			iType = rand(SHIP_BATTLESHIP);	
		}
		else
		{
			iType = rand(SHIP_GALEON_L);	
		}
	}
	iType = GenerateShip(iType, isLock);
	return iType;
}

int FindFirstEmptyCharacter()
{
	for(int i = GlobalCharacters; i<TOTAL_CHARACTERS; i++)
	{
		if (characters[i].id == "0")
		{
			if (i >= MAX_CHARACTERS) MAX_CHARACTERS = i+1; //сдвигаем планку НПС
			return i;
		}
	}		
	return -1;
}

void AddGeometryToLocation(string LocationID, string ModelName)
{
	ref LocationRef;
	int n = 1;
	string str;
	locationRef = &locations[FindLocation(LocationID)];

	for(n = 1; n < 10; n++)
	{
		str = "l" + n;
		if(!CheckAttribute(LocationRef, "models.always." + str))
		{
			LocationRef.models.always.(str) = ModelName;
			LocationRef.models.always.(str).tech = "dLightModel";
			break;
		}
	}
}	

void RemoveGeometryFromLocation(string LocationID, string ModelName)
{
	ref LocationRef;
	int n = 1;
	string str;
	//trace("FUNCTION RemoveGeometryFromLocation reports: Current location ID is " + LocationID + " and geometry " + ModelName + " should be removed");
	if(FindLocation(LocationID) != -1)
	{
		locationRef = &locations[FindLocation(LocationID)];
	}
	else
	{
		return;
	}

	for(n = 1; n < 10; n++)
	{
		str = "l" + n;
		//trace("FUNCTION RemoveGeometryFromLocation reports: Checking Geometry name for n = " + str + ". It is " + LocationRef.models.always.(str));
		if(CheckAttribute(LocationRef, "models.always." + str) && LocationRef.models.always.(str) == ModelName)
		{
			DeleteAttribute(LocationRef, "models.always." + str);
			break;
		}
	}
}	


void CreateModel(int iChar, string sType, int iSex)
{
	int iNation = sti(characters[iChar].nation);
	
	string sBody = "";
	string sPrefix = "";
	int iNumber = -1;
		
	switch (sType)
	{
		case "pofficer":
			sBody = "officer";
			iNumber = 1;
		break;

		case "officer":
			sBody = "off";
			iNumber = 1;
		break;
		
		case "soldier":
			sBody = "sold";
			iNumber = (rand(7) + 1);
		break;
		
		// ветераны
		case "veteran":
			sBody = "sold";
			iNumber = (rand(7) + 9);
		break;
		
		case "pirate":
			sBody = "pirate";
			iNumber = (rand(15) + 1);
		break;

		case "trader":
			sBody = "trader";
			iNumber = 1;
		break;
		
		case "citizen":
			if(iSex == MAN)
			{
				sBody = "burgher";
				iNumber = (rand(7) + 1);
			}
			else
			{
				sBody = "philistine";
				iNumber = (rand(7) + 1);
			}
		break;

		case "whore":
			sBody = "whore";
			iNumber = (rand(7) + 1);
		break;
		
		// гуляющие матросы
		case "sailor":
			sBody = "sailor";
			iNumber = (rand(15) + 1);
		break;
		
		// пьяницы
		case "drunkard":
			sBody = "drunkard";
			iNumber = (rand(3) + 1);
		break;
		
		// контрики
		case "smuggler":
			sBody = "smuggler";
			iNumber = (rand(7) + 1);
		break;
		
		// дворяне
		case "noble":
			if (iSex == MAN)
			{
				sBody = "nobleman";
				iNumber = (rand(5) + 1);
			}
			else
			{
				sBody = "noblewoman";
				iNumber = (rand(5) + 1);
			}
		break;
		
		// старухи
		case "oldwoman":
			sBody = "oldwoman";
			iNumber = (rand(3) + 1);
		break;
	}

	sPrefix = "_";
	
	if(sType == "officer" || sType == "soldier" || sType == "veteran")
	{
		switch (iNation)
		{
			case ENGLAND:
				sPrefix = "_eng_";
			break;
			
			case FRANCE:
				sPrefix = "_fra_";
			break;
			
			case SPAIN:
				sPrefix = "_spa_";
			break;
			
			case HOLLAND:
				sPrefix = "_dut_";
			break;
			
			case PIRATE:
				sPrefix = "";
			break;
		}
	}
	
	string sResult = "";
	
	sResult = sBody+sPrefix+iNumber;
	
	characters[iChar].model = sResult;

	FaceMaker(&characters[iChar]);
}

// метод вернет случайный дружественный iNation город, неравный  sBeginColony _checkPort - Проверка порта
int FindNonEnemyColonyForAdventure(int iNation, string sBeginColony, bool _checkPort)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none")
		{
			if (_checkPort && CheckAttribute(&Colonies[i], "HasNoFort")) continue;  // без форта не берем
			
			if (GetNationRelation(sti(Colonies[i].nation), iNation) != RELATION_ENEMY && Colonies[i].id != sBeginColony && colonies[i].id != "Panama")
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return -1;
	}
	
	m = rand(m-1);
	m = iArray[m];
	return m;
}

int FindNonEnemyColonyForNation(int iNation, bool _checkPort)
{
	return FindNonEnemyColonyForAdventure(iNation, "NOT_IN_USE", _checkPort);
}

string FindAlliedColonyForNation(int iNation, bool _checkPort)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none" && colonies[i].id != "Panama")
		{
			if (_checkPort && CheckAttribute(&Colonies[i], "HasNoFort")) continue;  // без форта не берем
			if (sti(Colonies[i].nation)== iNation)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return "-1";
	}
	
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;
}

string FindAlliedColonyForNationExceptColony(string sHomeColony)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";

	int iNation = sti(colonies[FindColony(sHomeColony)].nation);
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if(colonies[i].nation != "none" && colonies[i].id != sHomeColony && colonies[i].id != "Panama")
		{
			if (sti(Colonies[i].nation) == iNation)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return "-1";
	}
	
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;
}

string FindColonyWithMayakExceptIsland(string sIsland)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none" && GetMayakByCityName(colonies[i].id) != "" && GetArealByCityName(colonies[i].id) != sIsland)	
		{
			iArray[m] = i;
			m++;		
		}
	}
	if (m == 0)
	{
		return "-1";
	}
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;	
}

// to_do
string SelectQuestDestinationAnyNationExceptColony(string sColony)
{
	int m;

	string sTempColony = sColony;

	while(sTempColony == sColony)
	{
		m = rand(MAX_COLONIES-1);
		if(colonies[m].nation != "none")
		{
			sTempColony = Colonies[m].id;
		}
	}

	return sTempColony;
}

// ugeen --> выбор случайной бухты на острове, где находится ГГ
string SelectQuestShoreLocation() 
{
    ref CurIsland;
	int n, i;
	string TargetLocation = "";
	
	i = 0;
	n = GetCharacterCurrentIsland(pchar);
	if (n < 0) 
	{
		TargetLocation = "";
	}
	else
	{
		CurIsland = GetIslandByIndex(n);
		while(TargetLocation == "" && i < 10)
		{
			TargetLocation = GetIslandRandomShoreId(CurIsland.id);
			if (!isLocationFreeForQuests(TargetLocation)) 
			{
				TargetLocation = ""; i++;
			}	
		}		
    }
	if(TargetLocation == "") TargetLocation = GetIslandRandomShoreId(CurIsland.id);
	Log_QuestInfo("TargetLocation = " + TargetLocation);
    return TargetLocation;
}

string SelectQuestShoreLocationFromSea(string CurIsland)
{
	string TargetLocation = "";
	int n, i;
	ref rIsland;
	
	i = 0;
	n = FindIsland(CurIsland);
	if (n < 0) 
	{
		TargetLocation = "None";
	}	
	else
	{
		rIsland = GetIslandByIndex(n);
		while(TargetLocation == "" && i < 10)
		{
			TargetLocation = GetIslandRandomShoreId(rIsland.id);
			if (!isLocationFreeForQuests(TargetLocation)) 
			{
				TargetLocation = ""; i++;
			}	
		}		
	}
	if(TargetLocation == "") TargetLocation = GetIslandRandomShoreId(rIsland.id);
	Log_QuestInfo("TargetLocation = " + TargetLocation);
	return TargetLocation;
} 
// ugeen

void EmptyAbordageCharacters()
{
	for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
	{
		if (CheckAttribute(&characters[i], "AboardFantom"))	InitCharacter(&characters[i], i);		
	}
}

void EmptyAllFantomCharacter()
{
	if (bAbordageStarted) return; // иначе трутся НПС при переходе в каюте
	int cn = -1;
	for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
	{
		// отдельный код зачистки boal -->
		if (LAi_IsDead(&characters[i]) && !CheckAttribute(&characters[i], "RebirthPhantom"))
		{
      			if(GetCompanionQuantity(&characters[i]) > 1) // Хм, а у фантомов есть компаньоны как у взрослых ГГ? оставлю на всяк случай (для ПГГ)
				{
					for(int k = 0; k < COMPANION_MAX; k++)
					{
						cn = GetCompanionIndex(&characters[i], k);
						if(cn != -1)
						{
							InitCharacter(&characters[cn], cn);
						}
					}
				}
				else
				{
     				InitCharacter(&characters[i], i);
				}
		}
		else
		{
			if (CheckAttribute(&characters[i], "LifeDay") &&
			    GetNpcQuestPastDayParam(&characters[i], "LifeTimeCreate") >= sti(characters[i].LifeDay) &&
				characters[i].location != pchar.location) // не трем, если ГГ в локации,иначе горожане пропадают на лету
			{ // время вышло
				InitCharacter(&characters[i], i);  // тут проверку на компаньонов не нужно, тк они все одинаковые по времени
			}
		}
		// boal <--
	}
}

// метод оставлен для совместимости со старым кодом К3
int GenerateCharacter(int iNation, int isShip, string sModel, int iSex, int isLock, int CharacterType)
{
    int iChar = NPC_GeneratePhantomCharacter(sModel, iNation, iSex, -isLock); // -isLock) == -1 || 0

	if (IsShip == WITH_SHIP)
	{
		// to_do del
		if(CharacterType == FORT_COMMANDER)
		{
			characters[iChar].ship.type = GenerateShip(SHIP_FORT, isLock);
			Fantom_SetRandomCrewExp(&characters[iChar], "war");
		}
		else
		{
			characters[iChar].ship.type = SearchForMaxShip(&characters[iChar], isLock, CharacterType);
			Fantom_SetRandomCrewExp(&characters[iChar], "war");
			
		}
		
		SetBaseShipData(&characters[iChar]);
		
		SetRandomNameToShip(&characters[iChar]);
	}
	else
	{
		characters[iChar].ship.type = SHIP_NOTUSED;
		DeleteAttribute(&characters[iChar], "ship.upgrades");
	}
	return iChar;
}

int GetRandomNationForMapEncounter(string sIslandID, bool bMerchant)
{   // boal: метод соверненно не понятен, убрал из него массив НатионСтайт, заменив на 1.0, раз работало - пусть будет как было, но логика чумовая
	int iNation = -1;
	if(sIslandID != "")
	{
		int iIsland = FindIsland(sIslandID);
		for(int i = 0; i < MAX_COLONIES; i++)
		{
			if(colonies[i].island == sIslandID)
			{
				if (colonies[i].nation != "none")
				{
					iNation = sti(colonies[i].nation);
					break;
				}
			}
		}
	}

	float fEngland  = 1.0;
	float fFrance   = 1.0;
	float fSpain    = 1.0;
	float fHolland  = 1.0;
	float fPirate   = 1.0;

	// бонус за ближ город
	if(iNation != -1)
	{
	    switch (iNation )
		{
			case ENGLAND:
				fEngland += 0.2;
			break;
			case FRANCE:
    			fFrance += 0.2;
			break;
			case SPAIN:
    			fSpain += 0.2;
			break;
			case HOLLAND:
    			fHolland += 0.2;
			break;
			case PIRATE:
    			fPirate += 0.2;
			break;
		}
	}

	float fProbablyNation;
	if(bMerchant)
	{
		fProbablyNation = fEngland + fFrance + fSpain + fHolland;
	}
	else
	{
		fProbablyNation = fEngland + fFrance + fSpain + fHolland + fPirate;
	}

	fProbablyNation = frand(fProbablyNation);

	fFrance   = fFrance  + fEngland;
	fSpain    = fFrance  + fSpain;
	fHolland  = fSpain   + fHolland;
	fPirate   = fHolland + fPirate;

	if(bMerchant == 0)
	{
		if(fProbablyNation >= fFrance && fProbablyNation < fSpain)
		{
			return FRANCE;
		}

		if(fProbablyNation >= fSpain && fProbablyNation < fHolland)
		{
			return SPAIN;
		}

		if(fProbablyNation >= fHolland && fProbablyNation < fPirate)
		{
			return HOLLAND;
		}

		if(fEngland <= fProbablyNation)
		{
			return ENGLAND;
		}
	}
	else
	{
		if (rand(2) == 1) return HOLLAND; //голланцев на карту
		
		if(fProbablyNation >= fFrance && fProbablyNation < fSpain)
		{
			return FRANCE;
		}

		if(fProbablyNation >= fSpain && fProbablyNation < fHolland)
		{
			return SPAIN;
		}

		if(fProbablyNation >= fHolland && fProbablyNation < fPirate)
		{
			return HOLLAND;
		}

		if(fEngland <= fProbablyNation)
		{
			return ENGLAND;
		}
	}

	return PIRATE;
}


string CheckingTranslate(int idLngFile, string idString)
{
	string retString = LanguageConvertString ( idLngFile, idString );
	if(retString=="")
	{
		trace("Warning! No text for lable <" + idString + "> into language file <LocLables.txt>");
	}
	return retString;
}

// to_do
void LaunchMoneyGraphCollect()
{
	string sYear = "year" + worldMap.date.year;
	string sMonth = "month" + worldMap.date.month;

	pchar.MoneyGraph.(sYear).(sMonth) = pchar.money;
}

string FindNearestFreeLocator(string group)
{
	float locx;
	float locy;
	float locz;
	string homelocator;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
	
	return homelocator;
}

string SetModelFlag(aref chr)
{
	string sResult = "";

	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		return "";
	}

	if(CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") )
	{
		if(sti(InterfaceStates.EnabledQuestsMarks) == 0)
		{
			return "";
		}
	}

	if(CheckAttribute(chr, "quest.questflag"))
	{
		switch(sti(chr.quest.questflag))
		{
			case 1:
				sResult = "exclamationmarkY";
			break;
			
			case 2:
				sResult = "questionmarkY";
			break;

			case 3:
				sResult = "questionmarkW";
			break; 
		}
	}

	chr.quest.questflag.technique = GetTechNameForSign();

	return sResult;
}

string GetTechNameForSign()
{
	return "RandItem";
}

void CheckQuestForCharacter(aref chr)
{

}

////////////////////////// boal набор методов для генерации фантомов
// boal -->
void InitCharacter(ref ch, int n)
{
	DeleteNPCInRumourGroups(ch);
    //DeleteAttribute(ch,"act");
	DeleteAttribute(ch,"");
	//Logic data
	ch.id = "0";
	ch.index = n;
	ch.name 	= "none";
	ch.lastname = "none";
	ch.sex = "man";
	//Model data
	ch.model = "none";
	ch.model.entity = "NPCharacter";
	ch.model.animation = "";
	//Address
	ch.location = "none";
	ch.location.group = "";
	ch.location.locator = "";
	ch.location.from_sea = "";
	//Ship data
	ch.Ship.Type = SHIP_NOTUSED;
	//Quest data
	ch.Dialog.CurrentNode = "First time";
	ch.Dialog.TempNode = "First time";
	ch.quest.meeting = "0";
	ch.quest = "True";
	ch.quest_date = 0;
	//Misc data
	ch.nation = ENGLAND;
	ch.skill.freeskill = 0;
	ch.perks.freepoints = 0;
	ch.rank = 1;
	ch.reputation = REPUTATION_NEUTRAL;
	ch.reputation.france = 0;
	ch.reputation.england = 0;
	ch.reputation.spain = 0;
	ch.reputation.holland = 0;
	ch.reputation.pirate = 0;
	ch.reputation.smuggler = 0;
	ch.reputation.trader = 0;
	ch.fame = 1;
	// boal -->
    SetRandSPECIAL(ch);
    //InitStartParam(ch);
    SetSelfSkill(ch, 1, 1);
    SetShipSkill(ch, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	ch.Skill.FreeSPECIAL  = 0;
    ch.Health.HP        = 60.0; // отличное
	ch.Health.maxHP     = 60.0;
	ch.Health.Damg      = 0.0;
	ch.Health.weekDamg  = 0.0;
	ch.Health.TotalDamg = 0.0;
	// <--
	ch.rank = 1;
	ch.experience = 0;

	ch.Fellows.Passengers.id0 = n; // свой пассажир

	ch.Fellows.Passengers.boatswain = "-1";
	ch.Fellows.Passengers.navigator = "-1";
	ch.Fellows.Passengers.doctor = "-1";
	ch.Fellows.Passengers.cannoner = "-1";
	ch.Fellows.Passengers.treasurer = "-1";
	ch.Fellows.Passengers.carpenter = "-1";

	//ch.prisoned = false;

	ch.money = "0";
	// battle hp
	//LAi_SetLoginTime(ch, 6.0, 21.98333);
	LAi_SetLoginTime(ch, 0.0, 24.0); // круглосуточно
 	LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP_MAX);
}
// boal <--
// метод ищет или создает НПС с указанным ID. Для последуешего применения
int NPC_FindOrCreateCharacter(string _id)
{
	int ci = GetCharacterIndex(_id);
	if (ci == -1)
    { // не нашли
        ci = FindFirstEmptyCharacter();
        if (ci != -1)
		{
			InitCharacter(&Characters[ci], ci);
			Characters[ci].id = _id;
		}
    }
    return ci;
}
// _ani нужно для двух рас пкм + к3
// _LifeDay - сколько дней живет, если -1, то вечный, если 0, то трется при выходе из локации
// _equip - экипировка саблями, перки все равно раздадутся
int NPC_GenerateCharacter(string _id, string _model, string _sex, string _ani, int _rank, int _nation, int _LifeDay, bool _equip, string _fraction)
{
    int iChar = NPC_FindOrCreateCharacter(_id);
	ref ch;
	if (iChar == -1) return -1;
	
    ch = &Characters[iChar];
	ch.rank 	= _rank;
    ch.nation   = _nation;
    ch.sex      = _sex;
    ch.model    = _model;
	ch.fraction = _fraction;
    if(ch.sex == "man")
	{
		ch.model.height = 1.8;
	}else{
		ch.model.height = 1.75;
	}
	ch.model.animation = _ani;
	FaceMaker(ch);
	SetRandomNameToCharacter(ch);
	SetFantomParamFromRank(ch, _rank, _equip);
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	return  iChar;
}
// сгенерим разового фантома - нашего моряка (в  форме, если патент)
ref GetOurSailor(string _id) // моежт быть нужно несколько
{
    string  smodel;
    ref     CrOur;
    string  ani;
    int     i;

    smodel = LAi_GetBoardingModel(GetMainCharacter(), &ani);
    
	i = NPC_GenerateCharacter(_id, smodel, "man", ani, 10, sti(pchar.nation), 0, true, F_SAILOR);
	CrOur = GetCharacter(i);
	CrOur.name     = "Матрос";
	CrOur.lastname = "";
	
	return CrOur;
}

int NPC_GeneratePhantomCharacter(string sType, int iNation, int iSex, int _LifeDay)//, int CharacterType)
{
    int iChar = FindFirstEmptyCharacter();
    ref ch;

	if (iChar == -1) return -1;
	ch = &Characters[iChar];
    InitCharacter(ch, iChar);
    
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	
	ch.PhantomType = sType; // не нужно пока для дела, впрок

	if(iSex == MAN)
	{
		ch.sex = "man";
		ch.model.animation = "man";
		ch.model.height = 1.80
	}
	else
	{
		ch.sex = "woman";
		ch.model.animation = "towngirl";
		ch.model.height = 1.70
	}

	ch.nation = iNation;
	
	// Rebbebion, ставим фракцию персонажу
	string sFraction;
	switch (sType)
	{
		case "citizen":		sFraction = F_CITY;			break;
		case "soldier":		sFraction = F_MILITARY;		break;
		case "veteran":		sFraction = F_MILITARY;		break;
		case "sailor":		sFraction = F_SAILOR;		break;
		case "pofficer":	sFraction = F_OFFICER;		break;
		case "noble":		sFraction = F_CITY;			break;
		case "oldwoman":	sFraction = F_CITY;			break;
		case "drunkard":	sFraction = F_CITY;			break;
		case "trader":		sFraction = F_TRADER;		break;
		case "slave":		sFraction = F_SLAVE;		break;
		case "creole":		sFraction = F_CREOLE;		break;
		case "pirate":		sFraction = F_PIRATE;		break;
		case "mercenary":	sFraction = F_MERCENARY;	break;
		case "smuggler":	sFraction = F_SMUGGLER;		break;
		case "indian":		sFraction = F_INDIAN;		break;
		case "catholics":	sFraction = F_CATHOLICS;	break;
		case "monster":		sFraction = F_MONSTER;		break;
		case "other":		sFraction = F_OTHER;		break;
	}
	
	ch.fraction = sFraction;

	SetRandomNameToCharacter(ch);
    ch.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
	ch.id = "GenChar_" + iChar;
	
    CreateModel(iChar, sType, iSex);
    SetFantomParam(ch);
    
    if (sType == "citizen")
		LAi_NPC_Equip(ch, sti(ch.rank), false, false);
	else
		LAi_NPC_Equip(ch, sti(ch.rank), true, true);
	
	return  iChar;
}

// boal prison count -->
int GetPrisonerQty()
{
    ref offref;
    int i, cn, iMax;
    ref mchr = GetMainCharacter();
    int qty = 0;

    iMax = GetPassengersQuantity(mchr);
    for(i=0; i < iMax; i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
	            {
                    qty++;
                }
            }
        }
    }
    return qty;
}
int SetCharToPrisoner(ref refEnemyCharacter)
{
    ref  rChTo, refMyCharacter;

    refMyCharacter =  GetMainCharacter();

    int  iNextPrisoner = FindFirstEmptyCharacter();
	
	if (iNextPrisoner != -1)
	{
	    rChTo = &Characters[iNextPrisoner];
	    InitCharacter(rChTo, iNextPrisoner);

		ChangeAttributesFromCharacter(rChTo, refEnemyCharacter, false);   // было четкое копирование, но что-то наследовалось от той жижни и в море вел по АИ убегания
	    rChTo.index = iNextPrisoner;
	    rChTo.id = "prisoner_" + iNextPrisoner;
	    rChTo.Dialog.Filename = "Ransack_captain_dialog.c";
	    rChTo.Dialog.CurrentNode = "First time";
	    DeleteAttribute(rChTo, "items");
		DeleteAttribute(rChTo, "equip");
		DeleteAttribute(rChTo, "LifeDay"); // постоянный
		DeleteAttribute(rChTo, "ship");
		DeleteAttribute(rChTo, "ShipSails.gerald_name");

		DeleteAttribute(rChTo, "AlwaysEnemy");
		DeleteAttribute(rChTo, "ShipTaskLock");
		DeleteAttribute(rChTo, "WatchFort");
		DeleteAttribute(rChTo, "AnalizeShips");

	    rChTo.ship.type = SHIP_NOTUSED;
		GiveItem2Character(rChTo, "unarmed");
	    EquipCharacterByItem(rChTo, "unarmed");

	    rChTo.greeting = "Gr_Ransack";
		
	    LAi_SetCitizenTypeNoGroup(rChTo);
	    LAi_group_MoveCharacter(rChTo, "Prisoner");
	    LAi_SetLoginTime(rChTo, 0.0, 24.0);
	    LAi_NoRebirthEnable(rChTo);

	    SetCharacterRemovable(rChTo, true);
	    AddPassenger(refMyCharacter,rChTo,true);
    }
    return iNextPrisoner;
}

void ReleasePrisoner(ref NPChar)
{
    DeleteAttribute(NPChar,"prisoned"); // освободили пленника
	RemovePassenger(PChar, NPChar);
	NPChar.LifeDay = 0; // трем
}

void FreeSitLocator(string location, string locator)
{	
	ref rCharacter; //ищем
	int n;

	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "location"))
		{
            if (rCharacter.location == location && rCharacter.location.locator == locator)
            {
            	ChangeCharacterAddressGroup(rCharacter, "none", "none", "none"); // в никуда
            }
            else
            {
            	if (rCharacter.location == "none") // офы, которые уже наняты, но сидят
            	{
            		//Если загруженны, то выйдем из локации
					LogoffCharacter(rCharacter);
            	}
            }
		}
    }
}

bool CheckFreeLocator(string location, string locator, int idxDontSee)
{
	return LAi_CheckLocatorFree("sit", locator);
}
// boal <--

int RandFromThreeDight(int _Num1, int _Num2, int _Num3)
{
	switch (rand(2))
	{
		case 0: return _Num1; break;
		case 1: return _Num2; break;
		case 2: return _Num3; break;
	}
}

// Отключить на время форт (потом сам восстановится)
void MakeFortDead(string _ColonyFort)
{
	int ind = GetCharacterIndex(_ColonyFort + " Fort Commander");
	if(ind == -1) return;
	ref FC = &Characters[ind];
	FC.Fort.Mode = FORT_DEAD;
	// data of fort die
	FC.Fort.DieTime.Year = GetDataYear();
	FC.Fort.DieTime.Month = GetDataMonth();
	FC.Fort.DieTime.Day = GetDataDay();
	FC.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(FC.index));
}

// ugeen --> получить наиболее дальний из группы локаторов для постановки квестовых  кораблей
string GetSeaQuestShipFarLocator(ref _loc, string group, float x, float y, float z)
{
	if(CheckAttribute(_loc, group) == 0) return "";
	aref grp;
	makearef(grp, _loc.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d >= dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}				
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

// ugeen --> получить наиболее ближний из группы локаторов для постановки квестовых  кораблей
string GetSeaQuestShipNearestLocator(ref _loc, string group, float x, float y, float z)
{
	if(CheckAttribute(_loc, group) == 0) return "";
	aref grp;
	makearef(grp, _loc.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d < dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

int GetCostForChangeHull(ref refShip, int iType)
{
	int iCurrentType = sti(refShip.Ship.Upgrades.Hull);
	if(iCurrentType == iType)
	{
		return 0;
	}
	
	int iSum = 0;
	int iBaseClass = 7;
	
	if(CheckAttribute(refShip, "Class")) { iBaseClass = sti(refShip.Class); } 
	
	iType *= 350;
	int iClass = 7000 / iBaseClass;
	iSum = iClass + iType;
	
	if(iSum > 25000) { iSum = 25000; } 
	if(iSum < 0) { iSum = 0; } 
	
	
	return iSum;
}

/////////////////////////////////////////////////////////////////////////////////
// Злобные крабы в бухтах (Rebbebion, перенесено из КПС)
/////////////////////////////////////////////////////////////////////////////////
void SetCrabsToShore(ref loc)
{
	if(loc.type != "seashore" && loc.type != "mayak" && loc.id != "LaVega_port") return;
	if(CheckAttribute(loc, "DisableCrabs")) return; // пока не надо, но пусть будет

	int iQuantity = 2 + rand(3);

	ref sld;
	
	for (int i = 1; i <= iQuantity; i++)
	{
		if (GetCharacterIndex("FantomShoreCrab_"+i) == -1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("FantomShoreCrab_" + i, "crabSmall", "crab", "crabSmall", 1, PIRATE, -1, false, F_MONSTER));
			sld.name = "Краб";
			sld.lastname = "";
			DeleteAttribute(sld, "items");
			sld.items = "";
			sld.SaveItemsForDead = true;
			
			LAi_SetHP(sld, 10, 10);
			LAi_CharacterDisableDialog(sld);
			LAi_SetCitizenTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		}
		else
		{
			sld = &Characters[GetCharacterIndex("FantomShoreCrab_" + i)];
		}
		
		PlaceCharacter(sld, "goto", "random_free");
	}
}

//////////////////////// boal SLiB (Rebbebion, перенёс сюда) ////////////////////////////////
void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) // boal
	{
		// проверка на наличие кому платить -->
		int nPaymentQ = 0;
		int i, cn;
		ref chref;
		
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) // считаем только своих, а то вских сопровождаемых кормить!!!
				{
					nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}
		
		// проверка на наличие кому платить <--
		NullCharacter.SalayPayMonth = GetDataMonth(); // boal
		if (nPaymentQ > 0)
		{
			if( CheckAttribute(pchar,"CrewPayment") )
			{
				nPaymentQ += makeint(pchar.CrewPayment); // а тут помним все до копейки!
			}
			if( CheckAttribute(pchar,"Partition.MonthPart") )
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); // доля за месяц
				DeleteAttribute(pchar,"Partition.MonthPart")
			}
			
			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();
			
			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted) // можно показать
			{
				LaunchSalaryScreen("");
			}
			else
			{
				Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
				PChar.quest.LaunchSalaryScreen.win_condition    = "LaunchSalaryScreen";
				PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
			}
		}
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int iStep = GetEventData();
	float dayRandom;

	switch(iStep)
	{
			case 0:
				DeleteAttribute(pchar, "SkipEshipIndex");// boal
				DailyEatCrewUpdate(); // boal
				Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");
				
				dayRandom = Random();
				PChar.DayRandom = dayRandom;
				Log_TestInfo("dayRandom == " + dayRandom);
				
				// Массив рандомных дробей -->
				DeleteAttribute(PChar, "Random");
				PChar.Random = (rand(9)+1);
				string yy;
				for(int y = 0; y < sti(PChar.Random); y++)
				{
					yy = y; //через its() не хочет
					PChar.Random.nums.(yy) = Random();
				}
				// Массив рандомных дробей <--
			break;
		
			case 1:
				Whr_RainFogGenerator(); // генератор дождей и туманов в локациях
				SalaryNextDayUpdate();  // запрлата
				Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");
			break;
		
			case 2:
				ProcessDayRepair();
			break;
		
			case 3:
				Group_FreeAllDead();
			break;
		
			case 4:
				QuestActions(); //eddy
			break;
		
			case 5:
				wdmEmptyAllOldEncounter();// homo чистка энкоутеров
			break;
		
			case 6:
				UpdateCrewExp();  // изменение опыта команды
			break;
			
			case 7:
				UpdateCrewInColonies(); // пересчет наемников в городах
			break;
			
			case 8:
				if(IsEntity(worldMap))
				{
					EmptyAllFantomCharacter(); // трем НПС
					wdmEmptyAllDeadQuestEncounter();
				}
			break;
			
			case 9:
				UpdateFame();   // это теперь известность репутации
				GenerateRumour() //homo 05/07/06
			break;
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}

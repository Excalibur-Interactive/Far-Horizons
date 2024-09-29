string	sEnManFaces = "30,35,10,6,32,33,42,43";
string	sFrManFaces = "19,27,29,31,32,33,43,43";
string	sSpManFaces = "25,37,38,44,7,32,33,42,43";
string	sHoManFaces = "11,26,28,36,32,33,42,43";
string	sPoManFaces = "12,30,39,32,33,42,43";
string	sPiManFaces = "0,1,13,14,2,23,24,3,40,5";

void SetRandomFaceToCharacter(ref rCharacter)
{
	string sFaceID = "1";
	if (rCharacter.sex == "man")
	{
		switch (sti(rCharacter.nation))
		{
			case ENGLAND:	
				sFaceID = GetRandSubString(sEnManFaces); 
			break;
			case FRANCE:	
				sFaceID = GetRandSubString(sFrManFaces); 
			break;
			case SPAIN:		
				sFaceID = GetRandSubString(sSpManFaces); 
				break;
			case PIRATE:	
				sFaceID = GetRandSubString(sPiManFaces); 
				break;
			case HOLLAND:	
				sFaceID = GetRandSubString(sHoManFaces); 
				break;
		}
	}
	else
	{
		sFaceID = "16";
	}
	
	rCharacter.FaceId = sti(sFaceID);
}

void FaceMaker(aref rCharacter)
{
	switch (rCharacter.model)
	{
		// заглушка
		case "beatrice":		rCharacter.FaceId = 0; break;
		
		// главная героиня - Катерина д'Эсте (знаю, что номер уже указан в HeroDescribe, но на всякий пожарный оставлю и здесь, чем чёрт не шутит)
		// не забыть поменять название модели, когда своя появится
		case "PGG_Angellica":   rCharacter.FaceId = 1; break;
		
		// пираты
		case "pirate_1":        rCharacter.FaceId = 4; break;
		case "pirate_2":        rCharacter.FaceId = 18; break;
		case "pirate_3":        rCharacter.FaceId = 5; break;
		case "pirate_4":        rCharacter.FaceId = 6; break;
		case "pirate_5":        rCharacter.FaceId = 7; break;
		case "pirate_6":        rCharacter.FaceId = 8; break;
		case "pirate_7":        rCharacter.FaceId = 9; break;
		case "pirate_8":        rCharacter.FaceId = 10; break;
		case "pirate_9":        rCharacter.FaceId = 11; break;
		case "pirate_10":       rCharacter.FaceId = 12; break;
		case "pirate_11":       rCharacter.FaceId = 13; break;
		case "pirate_12":       rCharacter.FaceId = 14; break;
		case "pirate_13":       rCharacter.FaceId = 3; break;
		case "pirate_14":       rCharacter.FaceId = 15; break;
		case "pirate_15":       rCharacter.FaceId = 16; break;
		case "pirate_16":       rCharacter.FaceId = 17; break;
		
		// пираты (мушкетёры)
		case "mush_pir_1":        rCharacter.FaceId = 14; break;
		case "mush_pir_2":        rCharacter.FaceId = 3; break;
		case "mush_pir_3":        rCharacter.FaceId = 4; break;
		case "mush_pir_4":        rCharacter.FaceId = 16; break;
		case "mush_pir_5":        rCharacter.FaceId = 17; break;
		case "mush_pir_6":        rCharacter.FaceId = 7; break;
		
		// испанцы (лёгкая пехота)
		case "sold_spa_1":         rCharacter.FaceId = 19; break;
		case "sold_spa_2":         rCharacter.FaceId = 21; break;
		case "sold_spa_3":         rCharacter.FaceId = 20; break;
		case "sold_spa_4":         rCharacter.FaceId = 22; break;
		case "sold_spa_5":         rCharacter.FaceId = 23; break;
		case "sold_spa_6":         rCharacter.FaceId = 24; break;
		case "sold_spa_7":         rCharacter.FaceId = 25; break;
		case "sold_spa_8":         rCharacter.FaceId = 26; break;
		
		// испанцы (тяжёлая пехота)
		case "sold_spa_9":          rCharacter.FaceId = 27; break;
		case "sold_spa_10":         rCharacter.FaceId = 34; break;
		case "sold_spa_11":         rCharacter.FaceId = 33; break;
		case "sold_spa_12":         rCharacter.FaceId = 32; break;
		case "sold_spa_13":         rCharacter.FaceId = 31; break;
		case "sold_spa_14":         rCharacter.FaceId = 29; break;
		case "sold_spa_15":         rCharacter.FaceId = 30; break;
		case "sold_spa_16":         rCharacter.FaceId = 28; break;
		
		// гуляющие матросы
		case "sailor_1":            rCharacter.FaceId = 35; break;
		case "sailor_2":            rCharacter.FaceId = 36; break;
		case "sailor_3":            rCharacter.FaceId = 37; break;
		case "sailor_4":            rCharacter.FaceId = 38; break;
		case "sailor_5":            rCharacter.FaceId = 39; break;
		case "sailor_6":            rCharacter.FaceId = 40; break;
		case "sailor_7":            rCharacter.FaceId = 41; break;
		case "sailor_8":            rCharacter.FaceId = 42; break;
		case "sailor_9":            rCharacter.FaceId = 43; break;
		case "sailor_10":           rCharacter.FaceId = 44; break;
		case "sailor_11":           rCharacter.FaceId = 45; break;
		case "sailor_12":           rCharacter.FaceId = 46; break;
		case "sailor_13":           rCharacter.FaceId = 47; break;
		case "sailor_14":           rCharacter.FaceId = 48; break;
		case "sailor_15":           rCharacter.FaceId = 49; break;
		case "sailor_16":           rCharacter.FaceId = 50; break;
	}
	
	if(!CheckAttribute(rCharacter, "FaceId")) rCharacter.FaceId = 0; //Экку Korsar - Если айди портрета нету, то ставим плейсхолдер
}

// boal 22.04.04 выбор модели зависимо от типа. Rebbebion, 10.11.23 - новое разделение моделек в зависимости от класса корабля и его принадлежности (торговец, военный, пират)
void SetCaptanModelByEncType(ref Chref, string sFantomType)
{
	int st = GetCharacterShipType(Chref);	
	
	if (st != SHIP_NOTUSED)
	{
		ref rBaseShip = GetRealShip(sti(Chref.Ship.Type));
		int shClass = sti(rBaseShip.Class);
		
		switch (sFantomType)
		{
			case "trade":
			ModelPirate = "trader_1";
		    break;
			
			case "war":
			if (shClass >= 4) ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(2) + 1);
			if (shClass < 4 && shClass > 1) ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(5) + 4);
		    break;
			
			case "pirate":
            ModelPirate = "officer_1";
		    break;
		}
	}
	else
	{
		string ModelPirate = "Albermal"; // значит баг
	}
	
	Chref.model = ModelPirate;
	FaceMaker(Chref);
}

void SetModelPirate(ref ChrefPirate)
{
    string ModelPirate;
    
    ModelPirate = "pirate_" + (rand(15) + 1);
    
    ChrefPirate.model = ModelPirate;
    FaceMaker(ChrefPirate);
}

#define PARSE_STRING	"PARSE_STRING"

#event_handler(PARSE_STRING, "ParseString");

int AddStr2Array(ref rNames, int iNum, string sStr)
{
	SetArraySize(rNames, iNum + 1);
	rNames[iNum] = sStr;
	iNum++;
	return iNum;
}

String GetRussianNumberString(int _num)
{
	if(_num < -999 || _num > 999) return "Error";
	if(_num == 0) return XI_ConvertString("zero");
	
	String numString = its(abs(_num));
	
	int strLength = strlen(numString);
	
	String ones = GetSymbol(numString, strLength - 1);
	String tens = GetSymbol(numString, strLength - 2) + "0";
	String hundreds = GetSymbol(numString, strLength - 3) + "00";
	
	numString = "";
	
	if(_num < 0)
	{
		numString = XI_ConvertString("minus") + " ";
	}
	
	if(tens == "10")
	{
		tens = "";
		ones = "1" + ones;
	}
	
	ones = XI_ConvertString(ones);
	
	if(tens != "")
	{
		tens = XI_ConvertString(tens) + " ";
	}
	
	if(hundreds != "")
	{
		hundreds = XI_ConvertString(hundreds) + " ";
	}
	
	return numString + hundreds + tens + ones;
}

string NewStr()
{
    int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    string sTemp;
    sTemp = LanguageConvertString(idLngFile,"new_string");
    LanguageCloseFile(idLngFile);

    return sTemp;
}

string  xiStr(string _str) // сокращение
{
	return XI_ConvertString(_str);
}

string  xiDStr(string _str) // сокращение
{
	return GetConvertStr(_str, "DialogSource.txt");
}

float GetDotProduct(float fA1, float fA2)
{
    return cos(fA2 - fA1);  // boal бешенная оптимизация моря
}

void ParseString()
{
	int		i, iLen;
	string	sParams[2];
	string	sDst = "";

	aref aRes = GetEventData();
	string rSourceString = GetEventData();
	int	iNumParameters = GetEventData();

	//Trace("parser started: " + rSourceString + ", params = " + iNumParameters);

	if (iNumParameters == 0)
	{
		aRes.Str = rSourceString;
		return;
	}

	SetArraySize(&sParams, iNumParameters + 1);
	for (i=0; i<iNumParameters; i++) { sParams[i] = GetEventData();	}

	iLen = strlen(&rSourceString);
	for (i=0; i<iLen; i++)
	{
		string sChar = GetSymbol(&rSourceString, i);
		if (sChar == "%")
		{
			if (GetSymbol(&rSourceString, i + 1) == "%")
			{
				sDst = sDst + "%"; 
				i++;
				continue;
			}
			// get parameter number 
			string sNumber = "";
			i++;
			while (i < iLen)
			{
				string sTmp = GetSymbol(&rSourceString, i);
				if (!isDigit(&sTmp, 0)) { break; }
				sNumber = sNumber + sTmp;
				i++;
			}
			sDst = sDst + sParams[sti(sNumber) - 1]; i--;
			continue;
		}
		sDst = sDst + sChar;
	}

	aRes.Str = sDst;
}

float GetDistance2D(float x1, float y1, float x2, float y2)
{
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

// Warship 21.07.09 Расстояние в 3D
float GetDistance3D(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2)
{
	return sqrt(sqr(_x1 - _x2) + sqr(_y1 - _y2) + sqr(_z1 - _z2));
}

void RotateAroundY(ref rX, ref rZ, float fCos, float fSin)
{
	float xxx = rX;
	float zzz = rZ;
	float xx = xxx * fCos + zzz * fSin;
	float zz = zzz * fCos - xxx * fSin;
	rX = xx;
	rZ = zz;
}

int Tonnes2CWT(int iTonnes)
{
	int a = iTonnes * 10000 / 508;
	a = 100 * ((a + 99) / 100);
	return a;
}

int i_min(int a1, int a2)
{
	if (a1 < a2) { return a1; }
	return a2;
}

// boal -->
string GetVerNum()
{
 	string  VERSION_STR = VERSION_NUMBER2;

    if (MOD_BETTATESTMODE == "On")
    {
       VERSION_STR = VERSION_STR + "  DEV";
    }
    if (MOD_BETTATESTMODE == "Test")
    {
       VERSION_STR = VERSION_STR + "  TST";
    }
    return VERSION_STR;
}

void Log_Info(string _str)
{
    Log_SetStringToLog(_str);
}

void Log_TestInfo(string logtext)
{
	if (bBettaTestMode)
	{
		Log_SetStringToLog(logtext);
		trace("TestInfo: " + GetQuestBookDataDigit() + " " + logtext)
	}
}
void Log_QuestInfo(string _info)
{
    if (bQuestLogShow)
	{
		Log_SetStringToLog(_info);
	}
}

Object objGrass[5];	// evganat - трава
// evganat - трава
void CreateGrass(string sDataFile, string sTextureFile, float fScale, float fW,float fH, float fMinDist,float fMaxDist, float fMinLod, int curGrass)	
{
	CreateEntity(&objGrass[curGrass],"Grass");
	if( bSeaActive && !bAbordageStarted )
	{
		LayerAddObject(SEA_EXECUTE,&objGrass[curGrass],1000);
		LayerAddObject(SEA_REALIZE,&objGrass[curGrass],1000);
	}
	else
	{
		LayerAddObject(EXECUTE,&objGrass[curGrass],1000);
		LayerAddObject(REALIZE,&objGrass[curGrass],1000);
	}	
	SendMessage(objGrass[curGrass],"ls",41666, sTextureFile); // #define MSG_GRASS_SET_TEXTURE 41666
	SendMessage(objGrass[curGrass],"lffffff",42666, fScale, fW,fH, fMinDist,fMaxDist, fMinLod); // #define MSG_GRASS_SET_PARAM 42666
	SendMessage(objGrass[curGrass],"ls",40666, sDataFile); // #define MSG_GRASS_LOAD_DATA 40666
}

void DeleteGrass(int curGrass)
{
	if(curGrass != -1)
	{
		if (IsEntity(&objGrass[curGrass]))
		{
			DeleteClass(&objGrass[curGrass]); // boal грохнуть конкретный объект
		}
	}
	else
	{
		for(int i=0; i<5; i++)
		{
			if (IsEntity(&objGrass[i]))
			{
				DeleteClass(&objGrass[i]); // boal грохнуть конкретный объект
			}
		}			
		DeleteEntitiesByType("Grass");
	}	
}

void HideGrass()
{
	for(int i=0; i<5; i++)
	{
		if (IsEntity(&objGrass[i]))
		{
			LayerDelObject(EXECUTE, &objGrass[i]);
			LayerDelObject(REALIZE, &objGrass[i]);
			LayerDelObject(SEA_EXECUTE, &objGrass[i]);
			LayerDelObject(SEA_REALIZE, &objGrass[i]);
		}
	}
}

void ShowGrass()
{
	for(int i=0; i<5; i++)
	{
		if (IsEntity(&objGrass[i]))
		{
			LayerAddObject(SEA_EXECUTE, &objGrass[i], 1000);
			LayerAddObject(SEA_REALIZE, &objGrass[i], 1000);
		}
	}
}

// boal 16.03.2004 -->
void CalcLocalTime(float _inc)
{
	if (locTmpTime >= _inc)
	{
        locTmpTime = 0.0;
    }
}
void RefreshWeather()
{
    Whr_UpdateWeather();
}
void RefreshLandTime()
{
    objLandInterface.textinfo.datatext.text = XI_convertString("Date:") + GetQuestBookData();
}

void ResetTimeScale()
{
    SetTimeScale(1.0);
	TimeScaleCounter = 0;
	if(IsPerkIntoList("TimeSpeed"))
	{	DelPerkFromActiveList("TimeSpeed");
	}
}

void FreeChangeFlagMode(string _tmp)
{
	DeleteAttribute(pchar, "DisableChangeFlagMode");
}

void Dev_Trace(string _str) // логи только в дев версии
{
    if (MOD_BETTATESTMODE	==	"On")	Trace(_str);
}

// Просто сокращения
void Log_AStr(string _str) // Постоянная строка. С экрана никуда не изчезнет
{
	Log_SetEternalString(_str);
}

void Log_TestAStr(string _str)
{
	if (bBettaTestMode)
	{
		Log_AStr(_str);
		trace("TestInfo: " + GetQuestBookDataDigit() + " " + _str)
	}
}

void Log_Clear()
{
	ClearAllLogStrings();
}

int GetCurrentModelrNumber()
{
	int n = 0;
	aref arModel;
	if (FindEntity(&arModel, "modelr")) 
	{
		n++;
		while (FindEntityNext(&arModel)) 
		{
			n++;
		}
	}
	trace("GetCurrentModelrNumber   n : " + n);
	return n;
}

string GetSailsType(int _type)
{
	switch (_type)
	{
	    case 1 : return "Пенька";  break;
	    case 2 : return "Лён";     break;
	    case 3 : return "Хлопок";  break;
	}
	return "Пенька";
}

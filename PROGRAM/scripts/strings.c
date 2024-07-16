// Количество подстрок, разделитель запятая
int GetCountSubString(string sStr)
{
	int iFindPos = findSubStr(&sStr, ",", 0);
	if (iFindPos < 0) return 1; //Нет запятой - подстрока одна
	
	int iNumFind = 1;
    while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
	}

	return iNumFind;
}

// Взять подстроку по номеру, разделитель запятая
string GetSubStringByNum(string sStr, int iSelect)
{
	string sTemp;
	int iFindPos = findSubStr(&sStr, ",", 0);
	if (iFindPos < 0) return sStr;	// one word in string
	int iNumFind = 1;
    while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
	}
	if (iNumFind <= iSelect)
	{
        return GetSubStringByNum(sStr, 0);
	}
	int	iLastPos = 0;
	iFindPos = 0;
	for (int i=0; i<iNumFind; i++)
	{
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
		if (i == iSelect)
		{
			if (iFindPos < 0)
            {
                iFindPos = strlen(&sStr);
            }
            if (iLastPos >=  iFindPos) iFindPos = iLastPos + 2;
			sTemp = strcut(&sStr, iLastPos, iFindPos - 1);
			return sTemp;
		}
		iLastPos = iFindPos + 1;
	}

	return GetSubStringByNum(sStr, 0);
}

// Чуть видоизмененная функция GetSubStringByNum: в качестве разделителя sDiv, можно указывать любой символ, не только запятую
// Возвращает часть строки sText перед указанным в iSelect (отсчёт с нуля) разделителем sDiv
string GetSubStr(string sText, string sDiv, int iSelect)
{
	if (strlen(sText) <= 0)
		return "";

	if (sDiv == "")
		sDiv = ",";

	int i, iNumFind = 1;
	int iLastPos = 0;
	int iFindPos = findSubStr(&sText, sDiv, 0);

	string sTemp;

	if (iFindPos < 0)
		return sText;

	while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sText, sDiv, iFindPos + 1);
	}

	if (iNumFind <= iSelect)
		return GetSubStr(sText, sDiv, 0);

	iFindPos = 0;

	for (i = 0; i < iNumFind; i++)
	{
		iFindPos = findSubStr(&sText, sDiv, iFindPos + 1);

		if (i == iSelect)
		{
			if (iFindPos < 0)
				iFindPos = strlen(&sText);

			if (iLastPos >= iFindPos)
				iFindPos = iLastPos + 2;

			sTemp = strcut(&sText, iLastPos, iFindPos - 1);

			return sTemp;
		}

		iLastPos = iFindPos + 1;
	}

	return GetSubStr(sText, sDiv, 0);
}

string GetRandSubString(string sStr)
{
	string sTemp;

    if (strlen(sStr) > 0)//fix
    {
    	//int iFindPos = findSubStr(&sStr, ",", 0);
    	int iFindPos = findSubStr(sStr, ",", 0);
    	if (iFindPos < 0) return sStr;	// one word in string
    	int iNumFind = 1;
    	while (iFindPos > 0)
    	{
    		iNumFind++;
    		//iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
    		iFindPos = findSubStr(sStr, ",", iFindPos + 1);
    	}
    	int iSelect = rand(iNumFind - 1);
    	int	iLastPos = 0;
    	iFindPos = 0; // вот где собака порылась!!!!! считай я убил Вано :) Boal
    	for (int i=0; i<iNumFind; i++)
    	{
    		iFindPos = findSubStr(sStr, ",", iFindPos + 1);
    		if (i == iSelect)
    		{
    			if (iFindPos == -1)
                {
                    iFindPos = strlen(sStr);
                }
                // заколебало!!!
                if (iLastPos >=  iFindPos) return "";
    			sTemp = strcut(sStr, iLastPos, iFindPos - 1);
    			return sTemp;
    		}
    		iLastPos = iFindPos + 1;
    	}

    	return "If you see this, you can kick Vano :)";
	}
	return   "";
}

string stripblank(string str)
{
	string retstr = "";
	int iMax = strlen(str);
	for(int i = 0; i < iMax; i++) {
		if(GetSymbol(str,i) != " ") { retstr += GetSymbol(str,i); }}
	return retstr;
}

String FindStringAfterChar(string _string, string _char)
{
	int i = FindSubStr(_string, _char , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, i+1, strlen(_string)-1);
	return sRetStr;
}

String FindStringBeforeChar(string _string, string _char)
{
	int i = FindSubStr(_string, _char , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, 0, i-1);
	return sRetStr;
}

bool HasSubStr(string _Str, string _sFindStr)
{
	bool bHas = FindSubStr(_Str, _sFindStr, 0) != -1;
	return bHas;
}

string strleft(string str, int num)
{
	if (num < 1) return "";
	int len = strlen(str);
	if (num > len) num = len;
	return strcut(str,0,num-1);
}

string strright(string str, int num)
{
	if (num < 1) return "";
	int len = strlen(str);
	int start = len - num;
	if (start < 0) start = 0;
	return strcut(str,start,len-1);
}

string StrReplace(string strSource, string from, string into)
{
	int pos = findSubStr(strSource, from, 0);
	if (pos < 0) return strSource;
	if (HasSubStr(into, from)) return strSource;
	string ret = "";
	if (pos > 0) ret = strcut(strSource, 0, pos - 1);
	ret += into;
	if (pos + strlen(from) <= strlen(strSource) - 1) ret += strcut(strSource, pos + strlen(from), strlen(strSource) - 1);
	return strreplace(ret, from, into);
}

// bIs == true > if (str1 == str2) ...; bIs == false > if (HasStr(str1, str2)) ...
bool StrHasStr(string str1, string str2, bool bIs)
{
	str1 = GetStrSmallRegister(str1);
	str2 = GetStrSmallRegister(str2);
	
	bool bResult = false;
	int q = KZ|Symbol(str2, ",");
	
	for (int i = 0; i <= q; i++)
	{
		string temp = GetSubStr(str2, ",", i);
		
		if (temp == "")
			continue;
		
		if (bIs)
		{
			if (str1 == temp)
				bResult = true;
		}
		else
		{
			if (HasStr(str1, temp))
				bResult = true;
		}
	}
	
	return bResult;
}

int KZ|Symbol(string str, string sym)
{
	if (sym == "")
		return 0;
	
	int n, q = 0;
	int len = strlen(str);
	string tmp;
	
	if (len > 0)
	{
		for (n = 0; n < len; n++)
		{
			tmp = GetSymbol(&str, n);
			
			if (tmp == sym)
				q++;
		}
	}
	
	return q;
}

// Сокращение HasSubStr, есть ли в строке sText то, что указано в sAttr
bool HasStr(string sText, string sAttr)
{
	bool bHas = FindSubStr(GetStrSmallRegister(sText), GetStrSmallRegister(sAttr), 0) != -1;
	return bHas;
}

// csmHasStringMassive --> апгрейднутый вариант HasStr, рассчитанный на массовый чек значений sAttrs в строке sText
// Есть ли в строке sText всё или что-то из указанного в sAttrs, разделённое символом sDiv
// В качестве sCond задаётся "=" (условие "=="; чувствительно к регистру, прочие два нет), "&" (условие "&&") и "|" или любой другой символ (условие "||")
bool HasStrMass(string sText, string sAttrs, string sDiv, string sCond)
{
	if (strlen(sText) <= 0 || strlen(sAttrs) <= 0)
		return false;

	if (sDiv == "")
		sDiv = ",";

	if (HasStr(sCond, "&"))
		sCond = "&";
	else
	{
		if (HasSubStr(sCond, "="))
			sCond = "=";
		else 
			sCond = "|";
	}

	int i, iAttrs = KZ|Symbol(sAttrs, sDiv);
	int n = -1;

	string sT;

	for (i = 0; i <= iAttrs; i++)
	{
		sT = GetSubStr(sAttrs, sDiv, i);
		
		if (sT == "")
		{
			continue;
		}
		
		switch (sCond)
		{
			case "=":
				if (HasSubStr(sText, sT))
					n++;
				else
					return false;
			break;
			case "&":
				if (HasStr(sText, sT))
					n++;
				else
					return false;
			break;
			case "|":
				if (HasStr(sText, sT))
					return true;
			break;
		}
	}

	if (n >= iAttrs)
		return true;

	return false;
}

// > разделитель всегда запятая
bool HasStrEx(string str, string attr, string cond)
{
	return HasStrMass(str, attr, ",", cond);
}

// csmGetRandMassive --> чуть видоизмененная функция GetRandSubString: в качестве разделителя sDiv, можно указывать любой символ, не только запятую
// Возвращает случайную из частей строки sText, отделенных разделителем sDiv
string GetRandStr(string sText, string sDiv)
{
	int i, iSelect, iFindPos;
	int iNumFind = 1;
	int iLastPos = 0;

	string sTemp;

	if (sDiv == "")
		sDiv = ",";

	if (strlen(sText) > 0)
	{
		iFindPos = findSubStr(sText, sDiv, 0);

		if (iFindPos < 0)
			return sText;

		while (iFindPos > 0)
		{
			iNumFind++;
			iFindPos = findSubStr(sText, sDiv, iFindPos + 1);
		}

		iSelect = rand(iNumFind - 1);

		iFindPos = 0;

		for (i = 0; i < iNumFind; i++)
		{
			iFindPos = findSubStr(sText, sDiv, iFindPos + 1);

			if (i == iSelect)
			{
				if (iFindPos == -1)
					iFindPos = strlen(sText);

				if (iLastPos >= iFindPos)
					return "";

				sTemp = strcut(sText, iLastPos, iFindPos - 1);

				return sTemp;
			}

			iLastPos = iFindPos + 1;
		}
	}

	return "";
}

// Дополненный stripblank: удалить из строки sText все символы sDel (в компанию к strlen() и strcut())
string strdel(string sText, string sDel)
{
	int i, iMax = strlen(sText);

	string sR = "";

	if (iMax <= 0)
		return sR;

	if (sDel == " ")
		return stripblank(sText);

	for (i = 0; i < iMax; i++)
	{
		if (GetSymbol(sText, i) != sDel)
			sR += GetSymbol(sText, i);
	}

	return sR;
}

string GetStrSmallRegister(string sBase)
{
	string sResult, Simbol;
	sResult = "";
	int qty = strlen(sBase);
	for (int i=0; i<qty; i++)
	{
		Simbol = GetSymbol(sBase, i);
		switch (Simbol)
		{
			case "А": sResult += "а"; continue; break;
			case "Б": sResult += "б"; continue; break;
			case "В": sResult += "в"; continue; break;
			case "Г": sResult += "г"; continue; break;
			case "Д": sResult += "д"; continue; break;
			case "Е": sResult += "е"; continue; break;
			case "Ё": sResult += "ё"; continue; break;
			case "Ж": sResult += "ж"; continue; break;
			case "З": sResult += "з"; continue; break;
			case "И": sResult += "и"; continue; break;
			case "Й": sResult += "й"; continue; break;
			case "К": sResult += "к"; continue; break;
			case "Л": sResult += "л"; continue; break;
			case "М": sResult += "м"; continue; break;
			case "Н": sResult += "н"; continue; break;
			case "О": sResult += "о"; continue; break;
			case "П": sResult += "п"; continue; break;
			case "Р": sResult += "р"; continue; break;
			case "С": sResult += "с"; continue; break;
			case "Т": sResult += "т"; continue; break;
			case "У": sResult += "у"; continue; break;
			case "Ф": sResult += "ф"; continue; break;
			case "Х": sResult += "х"; continue; break;
			case "Ц": sResult += "ц"; continue; break;
			case "Ч": sResult += "ч"; continue; break;
			case "Ш": sResult += "ш"; continue; break;
			case "Щ": sResult += "щ"; continue; break;
			case "Э": sResult += "э"; continue; break;
			case "Ю": sResult += "ю"; continue; break;
			case "Я": sResult += "я"; continue; break;
			
			case "A": sResult += "a"; continue; break;
			case "B": sResult += "b"; continue; break;
			case "C": sResult += "c"; continue; break;
			case "D": sResult += "d"; continue; break;
			case "E": sResult += "e"; continue; break;
			case "F": sResult += "f"; continue; break;
			case "G": sResult += "g"; continue; break;
			case "H": sResult += "h"; continue; break;
			case "I": sResult += "i"; continue; break;
			case "J": sResult += "j"; continue; break;
			case "K": sResult += "k"; continue; break;
			case "L": sResult += "l"; continue; break;
			case "M": sResult += "m"; continue; break;
			case "N": sResult += "n"; continue; break;
			case "O": sResult += "o"; continue; break;
			case "P": sResult += "p"; continue; break;
			case "Q": sResult += "q"; continue; break;
			case "R": sResult += "r"; continue; break;
			case "S": sResult += "s"; continue; break;
			case "T": sResult += "t"; continue; break;
			case "U": sResult += "u"; continue; break;
			case "V": sResult += "v"; continue; break;
			case "W": sResult += "w"; continue; break;
			case "X": sResult += "x"; continue; break;
			case "Y": sResult += "y"; continue; break;
			case "Z": sResult += "z"; continue; break;
		}
		sResult += Simbol;
	}
	return sResult;
}

String ToUpper(String _text)
{
	String retString, symbol;
	retString = "";
	int length = strlen(_text);
	
	for(int i = 0; i < length; i++)
	{
		symbol = GetSymbol(_text, i);
		
		switch(symbol)
		{
			case "а": retString += "А"; continue; break;
			case "б": retString += "Б"; continue; break;
			case "в": retString += "В"; continue; break;
			case "г": retString += "Г"; continue; break;
			case "д": retString += "Д"; continue; break;
			case "е": retString += "Е"; continue; break;
			case "ё": retString += "Ё"; continue; break;
			case "ж": retString += "Ж"; continue; break;
			case "з": retString += "З"; continue; break;
			case "и": retString += "И"; continue; break;
			case "й": retString += "Й"; continue; break;
			case "к": retString += "К"; continue; break;
			case "л": retString += "Л"; continue; break;
			case "м": retString += "М"; continue; break;
			case "н": retString += "Н"; continue; break;
			case "о": retString += "О"; continue; break;
			case "п": retString += "П"; continue; break;
			case "р": retString += "Р"; continue; break;
			case "с": retString += "С"; continue; break;
			case "т": retString += "Т"; continue; break;
			case "у": retString += "У"; continue; break;
			case "ф": retString += "Ф"; continue; break;
			case "х": retString += "Х"; continue; break;
			case "ц": retString += "Ц"; continue; break;
			case "ч": retString += "Ч"; continue; break;
			case "ш": retString += "Ш"; continue; break;
			case "щ": retString += "Щ"; continue; break;
			case "э": retString += "Э"; continue; break;
			case "ю": retString += "Ю"; continue; break;
			case "я": retString += "Я"; continue; break;
			
			case "a": retString += "A"; continue; break;
			case "b": retString += "B"; continue; break;
			case "c": retString += "C"; continue; break;
			case "d": retString += "D"; continue; break;
			case "e": retString += "E"; continue; break;
			case "f": retString += "F"; continue; break;
			case "g": retString += "G"; continue; break;
			case "h": retString += "H"; continue; break;
			case "i": retString += "I"; continue; break;
			case "j": retString += "J"; continue; break;
			case "k": retString += "K"; continue; break;
			case "l": retString += "L"; continue; break;
			case "m": retString += "M"; continue; break;
			case "n": retString += "N"; continue; break;
			case "o": retString += "O"; continue; break;
			case "p": retString += "P"; continue; break;
			case "q": retString += "Q"; continue; break;
			case "r": retString += "R"; continue; break;
			case "s": retString += "S"; continue; break;
			case "t": retString += "T"; continue; break;
			case "u": retString += "U"; continue; break;
			case "v": retString += "V"; continue; break;
			case "w": retString += "W"; continue; break;
			case "x": retString += "X"; continue; break;
			case "y": retString += "Y"; continue; break;
			case "z": retString += "Z"; continue; break;
		}
		
		retString += symbol;
	}
	
	return retString;
}

// Первый символ в верхний регистр
String UpperFirst(String _text)
{
	String firstSymbol = GetSymbol(_text, 0);
	firstSymbol = ToUpper(firstSymbol);
	
	return firstSymbol + strcut(_text, 1, strlen(_text) - 1);
}

// Первый символ в нижний регистр
String LowerFirst(String _text)
{
	String firstSymbol = GetSymbol(_text, 0);
	firstSymbol = GetStrSmallRegister(firstSymbol);
	
	return firstSymbol + strcut(_text, 1, strlen(_text) - 1);
}

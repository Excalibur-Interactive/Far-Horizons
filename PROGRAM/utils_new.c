//Получить название текущей анимации персонажа
string GetCharCurAni(ref chr)
{
	string sAniCaseName;
	SendMessage(chr, "le", MSG_CHARACTER_GETCURANIMATION, &sAniCaseName);
	return sAniCaseName;
}

// > сообщения в логе со звуковым сопровождением; отделяя знаком "&" можно задать несколько str и snd
void LogSound(string str, string snd)
{
	int n;
	string tmp;
	int q = KZ|Symbol(str, "&");
	
	for (n = 0; n <= q; n++)
	{
		tmp = GetSubStr(str, "&", n);
		
		if (tmp != "")
			Log_Info(tmp);
	}
	
	q = KZ|Symbol(snd, "&");
	
	for (n = 0; n <= q; n++)
	{
		tmp = GetSubStr(snd, "&", n);
		
		if (tmp != "")
			PlaySound(tmp);
	}
}

// KZ > из ЧМ для КС от Cheatsurfer взял наиболее интересные методы; местами внесены правки и дополнения, убраны приписки csm, нейминг функций приведён в более читабельный вид
// csmCheckAttributeMassive --> CheckAttribute, рассчитанный на массовый, но простенький чек аттрибутов у объекта
// sBranch не обязателен, если в нем нет нужды (в таком случае, кавычки оставлять пустыми)
// В sLeaves через запятую и без пробелов можно указывать перечень аттрибутов к проверке у объекта oTree
// В качестве sCond задаётся "&" (условие "&&") и "|" или любой другой символ (условие "||")
// to_do: добавить чек значений (sValues), с локальными условиями (!=, >, <= и т.д.)
bool CheckAttributeMass(object oTree, string sBranch, string sLeaves, string sCond)
{
	if (sLeaves == "")
		return false;

	// Автоудаление пробелов, сейчас оставлено так на случай, если они там быть должны
	//sBranch = stripblank(sBranch);
	//sLeaves = stripblank(sLeaves);
	sCond = stripblank(sCond);

	if (sBranch != "")
		sBranch += ".";

	if (HasStr(sCond, "&"))
		sCond = "&";
	else
		sCond = "|";

	int i, iAttrs = KZ|Symbol(sLeaves, ",");
	int n = -1;

	string sT;

	for (i = 0; i <= iAttrs; i++)
	{
		sT = GetSubStr(sLeaves, ",", i);

		switch (sCond)
		{
			case "&":
				if (CheckAttribute(&oTree, sBranch + sT))
					n++;
				else
					return false;
			break;
			case "|":
				if (CheckAttribute(&oTree, sBranch + sT))
					return true;
			break;
		}
	}

	if (n >= iAttrs)
		return true;

	return false;
}

// > без sBranch
bool CheckAttributeEx(object _obj, string _str, string _cond)
{
	return CheckAttributeMass(&_obj, "", _str, _cond);
}

// > подсчёт указанных атрибутов объекта
int GetAttributeQty(object obj, string coreStr, string subStr)
{
	int i, res = 0;
	
	if (coreStr != "")
		coreStr += ".";
	
	for (i = 0; i <= KZ|Symbol(subStr, ","); i++)
	{
		if (CheckAttribute(&obj, coreStr + GetSubStr(subStr, ",", i)))
			res++;
	}
	
	return res;
}

// csmDeleteAttributeMassive --> DeleteAttribute, рассчитанный на массовое удаление аттрибутов у объекта
// sBranch не обязателен, если в нем нет нужды (в таком случае, следует оставить кавычки пустыми)
// В sLeaves через запятую и без пробелов можно указывать перечень аттрибутов к удалению у объекта oTree
void DeleteAttributeMass(object oTree, string sBranch, string sLeaves)
{
	int iA, iLeaves = KZ|Symbol(sLeaves, ",");

	if (sLeaves == "")
		return;

	if (sBranch != "")
		sBranch += ".";

	// Автоудаление пробелов, сейчас оставлено так на случай, если они там быть должны
	//sBranch = stripblank(sBranch);
	//sLeaves = stripblank(sLeaves);

	for (iA = 0; iA <= iLeaves; iA++)
	{
		DeleteAttribute(&oTree, sBranch + GetSubStr(sLeaves, ",", iA));
	}
}

// > без sBranch
void DeleteAttributeEx(object obj, string str)
{
	DeleteAttributeMass(&obj, "", str);
}

//Rosarak. Помогает не плодить лишние bool'ы
bool Con(bool a, bool b) {return a && b;} //КОНЪЮНКЦИЯ
bool Dis(bool a, bool b) {return a || b;} //ДИЗЪЮНКЦИЯ

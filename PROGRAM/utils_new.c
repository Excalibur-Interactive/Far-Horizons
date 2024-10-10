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

//Rosarak. Лотерея для целочисленных массивов (она же развесовка)
//Здесь нет проверки валидности, так как массив предварительно подготавливается в WeightRandom
int WeightRandomMethod(ref iMassive, string sRandType)
{
	int i, n;
	int Size = GetArraySize(iMassive);
	int Summ = -1; //чтобы рандомило от 0 до Summ-1
	for(i = 0; i < Size; i++) Summ += iMassive[i];
	n = call sRandType(Summ);
	for(i = 0; n >= 0; i++) n -= iMassive[i]; //Определяем победителя
	return i-1; //После победителя был инкремент, поэтому -1
}

//Rosarak. Подготовка участников лотереи
int WeightRandom(aref Lottery, string sRandType)
{
	aref participant;
	string sNumber; //Для конвертации
	int num = GetAttributesNum(Lottery);
	if(num == 0) return -1; //Нет участников
	int iMassive[2]; //Меньше 2 нельзя!
	int k = 0;
	SetArraySize(&iMassive, num);
	for(int i = 0; i < num; i++)
	{
		participant = GetAttributeN(Lottery,i);
		if(CheckAttribute(participant, "weight") && sti(participant.weight) > 0)
		{
			sNumber = k;
			TEV.LotteryProcess.(sNumber) = i; //Общий номер участника
			iMassive[k] = sti(participant.weight); //Сколько билетов купил
			k++;
		}
	}
	if(k == 0) return -1; //Нет валидных участников
	SetArraySize(&iMassive, k); //Срезаем лишнее
	sNumber = WeightRandomMethod(&iMassive, sRandType); //Проводим лотерею
	sNumber = TEV.LotteryProcess.(sNumber);
	DeleteAttribute(&TEV, "LotteryProcess");
	return sti(sNumber); //Победил атрибут под номером sNumber!
}

//Rosarak. Покупка лотерейных билетов (TO_DO)
void SetWeightParameters(aref Lottery, string sCase)
{
	//Если нужно корректировать веса в зависимости от места, где проходит лотерея,
	//то можно прописать соответствующую логику здесь и в аналогичных функциях
}

//Rosarak. Получить ссылку на победителя лотереи
aref GetRandomAttrByWeight(aref Lottery, string sRandType)
{
	aref aError;
	makearef(aError, TEV.Error);
	int iWinner = WeightRandom(Lottery, sRandType);
	if (iWinner == -1) return aError;
	return GetAttributeN(Lottery, iWinner);
}

//Rosarak. Для согласования кол-ва аргументов в общем вызове через call
int drandex_f(int n) {return drandex(n, false);}
int drandex_t(int n) {return drandex(n, true);}

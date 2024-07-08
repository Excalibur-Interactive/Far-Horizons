// Warship. методы для работы с числами
// Большую часть попереносил из других файлов, чтобы все в одном месте было

#define PI 3.14159265
#define PIm2 6.28318530
#define PId2 1.57079632

float FRAND(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

// boal
float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

// Warship 30.07.09. -->
// рандом 0.0 ... 1.0
float Random()
{
	return rand(32768) / 32768.0; // 65536
}

// коммент - не нравится мне cRand() - он возвращает не псевдослучайное число,
// а зависящее от конкретного дня месяца, да еще и подряд может быть несколько
// одинаковых чисел, например, cRand(5) будет давать 5 дней подряд одно и тоже.
// функция ниже вернет псевдослучайное число, потом запоминает его в PChar и пока не наступит
// новый день будет возвращать его-же. PChar.dayRandom устанавливается в первом шаге обновления дня
int dRand(int _max)
{
    // Если вызывается раньше WorldSituationsUpdate -->
    if(!CheckAttribute(pchar, "dayRandom"))
    {
        float dayRandom;
        dayRandom = Random();
        PChar.dayRandom = dayRandom;
        if(PChar.dayRandom == 1.0) return _max;
        return MakeInt(stf(PChar.dayRandom) * (_max + 1));
    }
    // <--
    
    if(PChar.dayRandom == 1.0) return _max;
    return MakeInt(stf(PChar.dayRandom) * (_max + 1)); // Rosarak. fix для равномерного распределения
}
// <-- Warship 30.07.09

// cRand() - античитовый рандом Ёдди. юзать не рекомендуется, за место него - dRand()
//античитовый рендом
int cRand(int num)
{
	if (num < 1) return 0;
	if (num > 30) return rand(num);
	int sResult = num;
	int iData = GetDataDay();

	int iDel = 30.0 / (num + 1) + 0.5; //делитель месяца
	int step = iDel; //шаг увеличения уровня сравнения в месяце

	for (i=0; i<num; i++)
	{
		if (iData < iDel) 
		{
			sResult = i;
			break;
		}
		else iDel += step;
	}
	return sResult;
}

// радианы в градусы
float Radian2Degree(float _rad) 
{
	return 180 / PI * _rad;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}

// Rosarak. Циклическая смена суточного рандома при смене аргумента
// При false, если аргумент уже использовался, вернёт первое значение на нём
int dRandEx(int _num, bool next)
{
    // Если вызывается раньше WorldSituationsUpdate -->
    if(!CheckAttribute(pchar, "Random"))
    {
        PChar.Random = (rand(9)+1);
        string yy;
        for(int y = 0; y < sti(PChar.Random); y++)
        {
            yy = y;
            PChar.Random.nums.(yy) = Random();
        }
    }
    // <--
            
    // Первая запись
    if(!CheckAttribute(PChar,"Random.args"))
    {
        PChar.Random.args.0 = _num;
        PChar.Random.args.last = 0;
        if(stf(PChar.Random.nums.0) != 1.0)
        {
            PChar.Random.args.0.value = MakeInt(stf(PChar.Random.nums.0) * (_num + 1));
            return sti(PChar.Random.args.0.value);
        }
        PChar.Random.args.0.value = _num;
        return _num;
    }
    
    int arg_i = 0; string arg = 0;
    if(!next) // Был ли такой аргумент
    {
        while( CheckAttribute(PChar,"Random.args."+arg) )
        {
            if(sti(PChar.Random.args.(arg)) == _num)
            {
                if(arg == "0") return sti(PChar.Random.args.0.value); // через скобки между атрибутами 0 нельзя
                return sti(PChar.Random.args.(arg).value);
            }
            arg_i++;
            arg = arg_i;
        }
    }
    
    // Новый аргумент
    arg_i = (sti(PChar.Random.args.last)+1);
    arg = arg_i;
    PChar.Random.args.(arg) = _num;
    PChar.Random.args.last = arg_i;
    string cycle = (arg_i % sti(PChar.Random)); // Двигаемся по кругу
    if(stf(PChar.Random.nums.(cycle)) != 1.0)
    {
        PChar.Random.args.(arg).value = MakeInt(stf(PChar.Random.nums.(cycle)) * (_num + 1));
        return sti(PChar.Random.args.(arg).value);
    }
    PChar.Random.args.(arg).value = _num;
    return _num;
}

//Mett: универсальная функция для диапазона чисел
void wRange(ref _num, ref _min, ref _max)
{
    if(_num < _min) _num = _min; //мин порог
    if(_num > _max) _num = _max; //макс порог
}

//Mett: диапазон чисел для float
float wRangeFloat(float _num, float _min, float _max)
{
    if(_num < _min) _num = _min; //мин порог
    if(_num > _max) _num = _max; //макс порог
    return _num;
}

//Mett: диапазон чисел для int
int wRangeInt(int _num, int _min, int _max)
{
    if(_num < _min) _num = _min; //мин порог
    if(_num > _max) _num = _max; //макс порог
    return _num;
}

//Mett: расчет процентов от числа для float
float wPercentFloat(float _num, float _percent)
{
    float _value = _num * _percent * 0.01;
    return _value;
}

//Mett: расчет процентов от числа для int
int wPercentInt(int _num, int _percent)
{
    int _value = _num * _percent / 100;
    return _value;
}

// evganat - функции округления -->
int round_up(float x) // evganat - округление вверх
{
	if (makefloat(makeint(x)) == x)
	{
		return makeint(x);
	}
	if (x > 0)
	{
		return makeint(x+1.0);
	}
	return makeint(x-1.0);
}

int round_near(float x) // evganat - округление до ближайшего
{
	if (makefloat(makeint(x)) == x)
	{
		return makeint(x);
	}
	if (abs(x) - makefloat(makeint(abs(x))) >= 0.5)
	{
		return round_up(x);
	}
	return makeint(x);
}
// evganat - функции округления <--
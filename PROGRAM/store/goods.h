// Rebbebion, полная переработка товаров (наконец-то, спустя двадцать лет)
#define GOODS_QUANTITY  43

// стратегически важные товары
#define GOOD_BALLS          0 // ядра
#define GOOD_GRAPES         1 // картечь
#define GOOD_KNIPPELS       2 // книппели
#define GOOD_POWDER         3 // порох
#define GOOD_WEAPON         4 // оружие
#define GOOD_FOOD           5 // провиант
#define GOOD_MEDICAMENT     6 // лекарства
#define GOOD_RUM            7 // ром
#define GOOD_ALE            8 // эль
#define GOOD_WINE           9 // вино
#define GOOD_PLANKS         10 // доски
#define GOOD_SAILCLOTH      11 // парусина

// второй ряд текстуры
#define GOOD_BRICKS         12 // кирпичи
#define GOOD_FABRICS        13 // ткани
#define GOOD_LEATHER        14 // кожа
#define GOOD_OIL            15 // масла
#define GOOD_SILK           16 // шёлк
#define GOOD_MAHOGANY       17 // красное дерево

// третий ряд текстуры
#define GOOD_EBONY          18 // чёрное дерево
#define GOOD_CITRUSES       19 // цитрусы
#define GOOD_COPRA          20 // копра
#define GOOD_WHEAT          21 // пшеница
#define GOOD_SUGAR          22 // сахарный тростник
#define GOOD_COTTON         23 // хлопок

// четвёртый ряд текстуры
#define GOOD_CINNAMON       24 // корица
#define GOOD_PAPRIKA        25 // паприка
#define GOOD_DYES           26 // красители
#define GOOD_CACAO          27 // какао
#define GOOD_TOBACCO        28 // табак
#define GOOD_COFFEE         29 // кофе
#define GOOD_TEA            30 // чай
#define GOOD_IRON           31 // железо

// пятый ряд текстуры
#define GOOD_COPPER         32 // медь
#define GOOD_SALTPETER      33 // селитра
#define GOOD_SILVER         34 // серебро
#define GOOD_GOLD           35 // золото
#define GOOD_SLAVES         36 // рабы

// пушки (пока старые, потом заменим [надеюсь])
#define GOOD_CANNON_8    	37 // 8ф пушки
#define GOOD_CANNON_12   	38 // 12ф пушки
#define GOOD_CANNON_16   	39 // 16ф пушки
#define GOOD_CANNON_24   	40 // 24ф пушки
#define GOOD_CANNON_32   	41 // 32ф пушки
#define GOOD_CANNON_42   	42 // 42ф пушки

object  Goods[GOODS_QUANTITY];

ref GetGoodByType(int iGoodType)
{
	return &Goods[iGoodType];
}

int FindGood(string sGood)
{
	for (int i=0; i<GOODS_QUANTITY; i++) { if (Goods[i].Name == sGood) return i; }
	return -1;
}

ref GetGoodByID(string sGood)
{
	for (int i=0; i<GOODS_QUANTITY; i++) { 
		if (Goods[i].Name == sGood) {return &Goods[i];}
	}
	trace("WARNING! Goods ID (" + sGood +") not found!");
}

int GetGoodWeightByType(int iGoodType,int quantity)
{
	int unitSize = sti(Goods[iGoodType].Units);
	int unitQuantity = (quantity+unitSize-1)/unitSize;
	int weight = makeint(unitQuantity*stf(Goods[iGoodType].Weight) + 0.05);
	return weight;
}

int GetGoodQuantityByWeight(int iGoodType,int weight)
{
	int unitSize = sti(Goods[iGoodType].Units);
	int uqnt = makeint( weight / stf(Goods[iGoodType].Weight) );
	return unitSize*uqnt;
}
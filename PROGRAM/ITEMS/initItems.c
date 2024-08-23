int InitItems()
{
	ref itm;
	int n;

	for(n=0; n<ITEMS_QUANTITY; n++)
	{
		InitItem(n);
	}
	n = 0;
	// в начате идут все без заполнения трупов
	
	//Легкое оружие
	n = InitStdBlade(n, "unarmed",  "items_CommonWeapon",  1, "quest",     "Quest",                          "Light",  "Placeholder",    false,false, 1); //Кулаки
	
	n = InitStdBlade(n, "blade_01", "items_CommonWeapon", 1, "poor",      "Pirate,Slave",                    "Light",  "Spear",          true, false, 1); //Гарпун
	n = InitStdBlade(n, "blade_02", "items_CommonWeapon", 2, "poor",      "Citizen",                         "Light",  "Dagger",         true, false, 1); //Стилет
	n = InitStdBlade(n, "blade_03", "items_CommonWeapon", 3, "poor",      "Soldier,Citizen",                 "Light",  "Rapier",         true, false, 1); //Итальянская рапира
	n = InitStdBlade(n, "blade_04", "items_CommonWeapon", 4, "poor",      "Pirate,Soldier,Citizen",          "Light",  "LightSword",     true, false, 1); //Корд
	n = InitStdBlade(n, "blade_05", "items_CommonWeapon", 5, "poor",      "Pirate,Soldier,Citizen",          "Light",  "SmallSword",     true, false, 1); //Эспадрон
	
	n = InitStdBlade(n, "blade_06", "items_RareWeapon", 1,  "ordinary",  "Indian",                         "Light",  "Spear",          true, false, 1); //Нааб-Те
	n = InitStdBlade(n, "blade_07", "items_RareWeapon", 2,  "ordinary",  "Officer",                        "Light",  "Dagger",         true, false, 1); //Ханджар
	n = InitStdBlade(n, "blade_08", "items_RareWeapon", 3,  "ordinary",  "Officer",                        "Light",  "Rapier",         true, false, 1); //Колишемард
	n = InitStdBlade(n, "blade_09", "items_RareWeapon", 4,  "ordinary",  "Officer",                        "Light",  "LightSword",     true, false, 1); //Саксонский клинок
	n = InitStdBlade(n, "blade_10", "items_RareWeapon", 5,  "ordinary",  "Officer",                        "Light",  "SmallSword",     true, false, 1); //Бильбо
	
	n = InitStdBlade(n, "blade_11", "ITEMS_LIGHTWEAPONS", 17, "good",      "Elite",                          "Light",  "Dagger",         true, false, 1); //Чинкуэда
	n = InitStdBlade(n, "blade_12", "ITEMS_LIGHTWEAPONS", 18, "good",      "Elite",                          "Light",  "Rapier",         true, false, 1); //Бретта
	n = InitStdBlade(n, "blade_13", "ITEMS_LIGHTWEAPONS", 19, "good",      "Elite",                          "Light",  "LightSword",     true, false, 1); //Ятаган
	
	n = InitStdBlade(n, "blade_14", "items_LegendaryWeapon", 1, "Excellent", "Quest",                          "Light",  "Dagger",         true, false, 1); //Джамбия
	n = InitStdBlade(n, "blade_15", "items_LegendaryWeapon", 2, "Excellent", "Quest",                          "Light",  "LightSword",     true, false, 1); //Фламбердж
	n = InitStdBlade(n, "blade_16", "items_LegendaryWeapon", 3, "Excellent", "Quest",                          "Light",  "SmallSword",     true, false, 1); //Саксенфедер
	
	//Среднее оружие
	n = InitStdBlade(n, "blade_17", "items_CommonWeapon",  9,   "poor",       "Slave",                         "Middle",      "Pickaxe",         true, false, 1); //Кирка
	n = InitStdBlade(n, "blade_18", "items_CommonWeapon",  10,  "poor",      "Pirate,Slave",                   "Middle",      "Saber",           true, false, 1); //Дюсcак
	n = InitStdBlade(n, "blade_19", "items_CommonWeapon",  11,  "poor",      "Pirate,Slave",                   "Middle",      "Cleaver",         true, false, 1); //Мачете
	n = InitStdBlade(n, "blade_20", "items_CommonWeapon",  12,  "poor",      "Pirate,Slave,Citizen",           "Middle",      "LightAxe",        true, false, 1); //Клевец
	n = InitStdBlade(n, "blade_21", "items_CommonWeapon",  13,  "poor",      "Pirate,Soldier,Citizen",         "Middle",      "Bastard",         true, false, 1); //Кортелас 
	n = InitStdBlade(n, "blade_22", "items_CommonWeapon",  14,  "poor",      "Slave",                          "Middle",      "Tomahawk",        true, false, 1); //Томагавк
	
	n = InitStdBlade(n, "blade_23", "items_RareWeapon", 6,  "ordinary",  "Pirate,Soldier",                "Middle",      "Saber",           true, false, 1); //Морская сабля
	n = InitStdBlade(n, "blade_24", "items_RareWeapon", 7,  "ordinary",  "Pirate,Soldier",                "Middle",      "Cleaver",         true, false, 1); //Морской тесак
	n = InitStdBlade(n, "blade_25", "items_RareWeapon", 9,  "ordinary",  "Indian",                        "Middle",      "LightAxe",        true, false, 1); //Тлакомакан
	n = InitStdBlade(n, "blade_26", "items_RareWeapon", 10, "ordinary",  "Officer",                       "Middle",      "Bastard",         true, false, 1); //Кракемарт
	n = InitStdBlade(n, "blade_27", "items_RareWeapon", 11, "ordinary",  "Officer",                       "Middle",      "LightFalchion",   true, false, 1); //Сторта
	
	n = InitStdBlade(n, "blade_28", "ITEMS_MEDIUMWEAPONS", 17, "good",      "Elite",                          "Middle",      "Saber",           true, false, 1); //Карабела
	n = InitStdBlade(n, "blade_29", "ITEMS_MEDIUMWEAPONS", 18, "good",      "Elite",                          "Middle",      "Cleaver",         true, false, 1); //Кацтбальгер
	n = InitStdBlade(n, "blade_30", "ITEMS_MEDIUMWEAPONS", 19, "good",      "Elite",                          "Middle",      "Bastard",         true, false, 1); //Скаллоп
	
	n = InitStdBlade(n, "blade_31", "items_LegendaryWeapon", 4, "Excellent", "Quest",                          "Middle",      "Saber",           true, false, 1); //Скимитар
	n = InitStdBlade(n, "blade_32", "items_LegendaryWeapon", 5, "Excellent", "Quest",                          "Middle",      "Klewang",         true, false, 1); //Сингапурский клеванг
	n = InitStdBlade(n, "blade_33", "items_LegendaryWeapon", 6, "Excellent", "Quest",                          "Middle",      "Katana",          true, false, 1); //Катана
	
	//Тяжелое оружие
	n = InitStdBlade(n, "blade_34", "items_CommonWeapon", 17,  "poor",      "Soldier",                        "Heavy", "Falchion",        true, false, 1); //Французский фальчион
	n = InitStdBlade(n, "blade_35", "items_CommonWeapon", 18,  "poor",      "Pirate,Slave,Soldier,Citizen",   "Heavy", "HeavyAxe",        true, false, 1); //Боевой топор
	n = InitStdBlade(n, "blade_36", "items_CommonWeapon", 19,  "poor",      "Pirate,Soldier,Citizen",         "Heavy", "Godendag",        true, false, 1); //Годендаг
	n = InitStdBlade(n, "blade_37", "items_CommonWeapon", 20,  "poor",      "Soldier,Citizen",                "Heavy", "Sword",           true, false, 1); //Гросс-мессер
	n = InitStdBlade(n, "blade_38", "items_CommonWeapon", 21,  "poor",      "Soldier",                        "Heavy", "HeavySmallSword", true, false, 1); //Ритершверт
	n = InitStdBlade(n, "blade_39", "items_CommonWeapon", 22,  "poor",      "Pirate,Soldier",                 "Heavy", "Broadsword",      true, false, 1); //Морской палаш
	
	n = InitStdBlade(n, "blade_40", "items_RareWeapon", 12,  "ordinary",  "Officer",                       "Heavy", "HeavyAxe",        true, false, 1); //Секира
	n = InitStdBlade(n, "blade_41", "items_RareWeapon", 13, "ordinary",  "Indian",                         "Heavy", "Macuahuitl",      true, false, 1); //Макуауитль
	n = InitStdBlade(n, "blade_42", "items_RareWeapon", 14, "ordinary",  "Officer",                        "Heavy", "Sword",           true, false, 1); //Голландский меч
	n = InitStdBlade(n, "blade_43", "items_RareWeapon", 15, "ordinary",  "Officer",                        "Heavy", "HeavySmallSword", true, false, 1); //Скьявона
	n = InitStdBlade(n, "blade_44", "items_RareWeapon", 16, "ordinary",  "Officer",                        "Heavy", "Broadsword",      true, false, 1); //Клэйбэг
	
	n = InitStdBlade(n, "blade_45", "ITEMS_HEAVYWEAPONS", 17, "good",      "Elite",                          "Heavy", "Sword",           true, false, 1); //Клеймор
	n = InitStdBlade(n, "blade_46", "ITEMS_HEAVYWEAPONS", 18, "good",      "Elite",                          "Heavy", "Sword",           true, false, 1); //Мальтийский меч
	
	n = InitStdBlade(n, "blade_47", "items_LegendaryWeapon", 7, "Excellent", "Quest",                          "Heavy", "Ngala",           true, false, 1); //Нгала
	n = InitStdBlade(n, "blade_48", "items_LegendaryWeapon", 9, "Excellent", "Quest",                          "Heavy", "Sword",           true, false, 1); //Танат
	n = InitStdBlade(n, "blade_49", "items_LegendaryWeapon", 10, "Excellent", "Quest",                          "Heavy", "Broadsword",      true, false, 1); //Кханда
	n = InitStdBlade(n, "blade_50", "items_LegendaryWeapon", 11, "Excellent", "Quest",                          "Heavy", "HeavyAxe",        true, false, 1); //Скандинавский лабрис
	
	
	n = InitStdGun(n, "pistol1",  "pistol1", "items_placeholder", 3, "Soldier,Officer", 800, "single-barrel",	20.0, 120.0, false,  50, 2.0, 1,	"poor"); //Пуффер
	n = InitStdGun(n, "pistol2",  "pistol2", "items_placeholder", 3, "Soldier,Officer", 800, "single-barrel",	20.0, 120.0, false,  50, 2.0, 1,	"poor"); //Кремниевый пистолет
	n = InitStdGun(n, "pistol3",  "pistol3", "items_placeholder", 3, "Soldier,Officer", 800, "grapeshooter",  20.0, 120.0, true,   50, 2.0, 1,       "poor"); //Тромбон
	n = InitStdGun(n, "pistol4",  "pistol4", "items_placeholder", 3, "Officer",         800, "multi-barrel",   20.0, 120.0, false,  50, 2.0, 2,   "ordinary"); //Бок-пистолет 
	n = InitStdGun(n, "pistol5",  "pistol5", "items_placeholder", 3, "Officer",         800, "single-barrel",	20.0, 120.0, false,  50, 2.0, 1,"ordinary"); //Дуэльный пистолет 
	n = InitStdGun(n, "pistol6",  "pistol6", "items_placeholder", 3, "Elite",           800, "multi-barrel",   20.0, 120.0, false,  50, 2.0, 3,       "good"); //Трёхствольный пистолет 
	n = InitStdGun(n, "pistol7",  "pistol7", "items_placeholder", 3, "Elite",           800, "single-barrel",	20.0, 120.0, false,  50, 2.0, 1,       "good"); //Кавалерийский пистолет 
	n = InitStdGun(n, "pistol8",  "pistol8", "items_placeholder", 3, "Elite",           800, "multi-barrel",   20.0, 120.0, false,  50, 2.0, 4,       "good"); //Четырёхствольный пистолет 
	n = InitStdGun(n, "pistol9",  "pistol9", "items_placeholder", 3, "Quest",           800, "grapeshooter",  20.0, 120.0, true,   50, 2.0, 1,  "Excellent"); //Бландербуз 
	n = InitStdGun(n, "pistol10", "pistol10","items_placeholder", 3, "Quest",           800, "single-barrel",	20.0, 120.0, false,  50, 2.0, 1,"Excellent"); //Двузарядный пистолет 
	n = InitStdGun(n, "pistol11",	"pistol11", "items_placeholder", 3,  "Quest",       800, "revolver",   20.0, 120.0, false,  50, 2.0, 5,  "Excellent"); //Револьвер
	
	n = InitStdGun(n, "mushket_matchlock",  "mushket1", "items_placeholder", 2,  "Mushketer",       10000, "single-barrel", 60.0, 180.0, false, 50, 10.0, 1,      "poor"); //Фитильный мушкет
	n = InitStdGun(n, "mushket_Arquebus",   "mushket2", "items_placeholder", 2,  "Mushketer",       10000, "grapeshooter", 60.0, 180.0, true,  50, 10.0, 1,  "ordinary"); //Аркебуза
	n = InitStdGun(n, "mushket_Bayonet",    "mushket3", "items_placeholder", 2,  "Mushketer",       10000, "single-barrel", 60.0, 180.0, false, 50, 10.0, 1,  "ordinary"); //Штыковой карабин
	n = InitStdGun(n, "mushket_Portuguese", "mushket4", "items_placeholder", 2,  "Q_Mush",          10000, "grapeshooter", 60.0, 180.0, false, 50, 10.0, 1,      "good"); //Португальский мушкетон
	n = InitStdGun(n, "mushket_sklopetta",  "mushket5", "items_placeholder", 2,  "Q_Mush",          10000, "bombard", 60.0, 180.0, true,  50, 10.0, 1,      "good"); //Склопетта
	n = InitStdGun(n, "mushket_Shtuzer",    "mushket6", "items_placeholder", 2,  "Quest",           10000, "single-barrel", 60.0, 180.0, false, 50, 10.0, 1, "Excellent"); //Винтовальный штуцер
	n = InitStdGun(n, "mushket_2x2",        "mushket7", "items_placeholder", 2,  "Quest",           10000, "multi-barrel", 60.0, 180.0, false, 50, 10.0, 1, "Excellent"); //Двуствольный штуцер
	n = InitStdGun(n, "mushket_Bombard",    "mushket8", "items_placeholder", 2,  "Quest",           10000, "bombard", 60.0, 180.0, true,  50, 10.0, 1, "Excellent"); //Итальянская бомбарда
	
	n = InitStdSuit(n, "cirass1", "0", "items_placeholder", 11, 1500, 5, "common",    1, false, 0.05, 0.0, 0.9, "");   //Кожаный корсет
	n = InitStdSuit(n, "cirass2", "0", "items_placeholder", 11, 1500, 5, "rare",      1, false, 0.15, 0.15, 0.85, "BasicDefence"); //Укреплённая бригантина
	n = InitStdSuit(n, "cirass3", "0", "items_placeholder", 11, 1500, 5, "epic",      1, false, 0.25, 0.25, 0.75, "BasicDefense"); //Миланская кираса
	
	n = InitStdSuit(n, "cirass4", "0", "items_placeholder", 11, 1500, 5, "rare",      1, false, 0.35, 0.35, 0.65, "Knight"); //Траншейный доспех
	n = InitStdSuit(n, "cirass5", "0", "items_placeholder", 11, 1500, 5, "Epic",      1, false, 0.5, 0.5, 0.5, "Knight");    //Рейтарский доспех
	
	n = InitStdSuit(n, "cirass6", "0", "items_placeholder", 11, 1500, 5, "Legendary", 1, true, 0.55, 0.55, 0.55, "");  //Доспех королевского мушкетёра
	n = InitStdSuit(n, "cirass7", "0", "items_placeholder", 11, 1500, 5, "Legendary", 1, true, 0.55, 0.55, 0.55, "");  //Костюм Лиги Теней
	
	//(Все коммоны, кроме "Трозо" падают со всех, кроме Вуду и индианов) (На земле и в сундуках)
	n = InitStdAmulet(n, "totem_01", "purseL", "ITEMS_TALISMAN", 1, 1500, "common",    0.5, 1, "");          //Гонтер
	n = InitStdAmulet(n, "totem_02", "purseL", "ITEMS_TALISMAN", 2, 1500, "common",    0.5, 1, "MainHero");  //Джокер
	n = InitStdAmulet(n, "totem_03", "purseL", "ITEMS_TALISMAN", 3, 1500, "common",    0.5, 1, "boatswain"); //Нефритовая черепашка
	n = InitStdAmulet(n, "totem_04", "purseL", "ITEMS_TALISMAN", 4, 1500, "common",    0.5, 1, "");          //Бронзовый крестик
	n = InitStdAmulet(n, "totem_05", "purseL", "ITEMS_TALISMAN", 5, 1500, "common",    0.5, 1, "MainHero");  //Индейская Антара
	n = InitStdAmulet(n, "totem_06", "purseL", "ITEMS_TALISMAN", 6, 1500, "common",    0.5, 1, "navigator"); //Серьга Морехода
	n = InitStdAmulet(n, "totem_07", "purseL", "ITEMS_TALISMAN", 7, 1500, "common",    0.5, 1, "");          //Амулет 'Эль Трозо' (Меджик пипл - вуду пипл)
	
	//(В сундуках)
	n = InitStdAmulet(n, "totem_08", "purseL", "ITEMS_TALISMAN", 8,  1500, "rare",      0.5, 1, "doctor");    //Икона Св. Николаса (Все "позитивные" фракции)
	n = InitStdAmulet(n, "totem_09", "purseL", "ITEMS_TALISMAN", 9,  1500, "rare",      0.5, 1, "MainHero");  //Маска Майяуэль (Мискито)
	n = InitStdAmulet(n, "totem_10", "purseL", "ITEMS_TALISMAN", 10, 1500, "rare",      0.5, 1, "MainHero");  //Статуэтка Кошкотли (Мискито)
	n = InitStdAmulet(n, "totem_11", "purseL", "ITEMS_TALISMAN", 11, 1500, "rare",      0.5, 1, "carpenter"); //Каменная Маска Шипе-Тотеку (Мискито)
	n = InitStdAmulet(n, "totem_12", "purseL", "ITEMS_TALISMAN", 12, 1500, "rare",      0.5, 1, "cannoner");  //Амулет Шиутекутли (Мискито)
	n = InitStdAmulet(n, "totem_13", "purseL", "ITEMS_TALISMAN", 13, 1500, "rare",      0.5, 1, "treasurer"); //Календарь ацтеков (Мискито)
	n = InitStdAmulet(n, "totem_14", "purseL", "ITEMS_TALISMAN", 14, 1500, "rare",      0.5, 1, "navigator"); //Идол Эхекатля (Мискито)
	n = InitStdAmulet(n, "totem_15", "purseL", "ITEMS_TALISMAN", 15, 1500, "rare",      0.5, 1, "MainHero");  //Идол Великой матери (Мискито, индианы)
	n = InitStdAmulet(n, "totem_16", "purseL", "ITEMS_TALISMAN", 16, 1500, "rare",      0.5, 1, "");          //Идол Морхахтулака (Мискито)
	n = InitStdAmulet(n, "totem_17", "purseL", "ITEMS_TALISMAN", 17, 1500, "rare",      0.5, 1, "");          //Ритуальный нож ацтеков (Мискито)
	n = InitStdAmulet(n, "totem_18", "purseL", "ITEMS_TALISMAN", 18, 1500, "rare",      0.5, 1, "MainHero");  //Порошок мумии ("Уникальный")
	
	// (Все, кроме упытя, мишкоатля и спиногрыза - "позитивные" фракции)
	n = InitStdAmulet(n, "totem_19", "purseL", "ITEMS_TALISMAN", 19, 1500, "Epic",      0.5, 1, "boatswain"); //Спиногрыз (Вуду)
	n = InitStdAmulet(n, "totem_20", "purseL", "ITEMS_TALISMAN", 20, 1500, "Epic",      0.5, 1, "");          //Тотем Мишкоатля (Индиан)
	n = InitStdAmulet(n, "totem_21", "purseL", "ITEMS_TALISMAN", 26, 1500, "Legendary", 0.5, 1, "carpenter"); //Брошь Вёлунда
	n = InitStdAmulet(n, "totem_22", "purseL", "ITEMS_TALISMAN", 21, 1500, "Epic",      0.5, 1, "");          //Упырь (Вуду)
	n = InitStdAmulet(n, "totem_23", "purseL", "ITEMS_TALISMAN", 22, 1500, "Epic",      0.5, 1, "navigator"); //Крест Св. Брендана
	n = InitStdAmulet(n, "totem_24", "purseL", "ITEMS_TALISMAN", 30, 1500, "Legendary", 0.5, 1, "");          //Меч Св. Михаила
	n = InitStdAmulet(n, "totem_25", "purseL", "ITEMS_TALISMAN", 24, 1500, "Epic",      0.5, 1, "");          //Клеврет
	n = InitStdAmulet(n, "totem_26", "purseL", "ITEMS_TALISMAN", 25, 1500, "Legendary", 0.5, 1, "treasurer"); //Крысиный бог
	
	n = InitStdAmulet(n, "totem_27", "purseL", "ITEMS_TALISMAN", 27, 1500, "Legendary", 0.5, 1, "");          //Чёрная лилия
	n = InitStdAmulet(n, "totem_28", "purseL", "ITEMS_TALISMAN", 28, 1500, "Legendary", 0.5, 1, "navigator"); //Молот Тора
	n = InitStdAmulet(n, "totem_29", "purseL", "ITEMS_TALISMAN", 29, 1500, "Legendary", 0.5, 1, "boatswain"); //Янычар
	n = InitStdAmulet(n, "totem_30", "purseL", "ITEMS_TALISMAN", 23, 1500, "Epic",      0.5, 1, "");          //Пушечное ядро
	n = InitStdAmulet(n, "totem_31", "purseL", "ITEMS_TALISMAN", 31, 1500, "Legendary", 0.5, 1, "doctor");    //Глаз Гора
	n = InitStdAmulet(n, "totem_32", "purseL", "ITEMS_TALISMAN", 32, 1500, "Legendary", 0.5, 1, "MainHero");  //Нефритовый череп
	
	// Rebbebion, яды (Сундук)
	makeref(itm,Items[n]); // простейшая отрава
	itm.id = "poison1";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison1";
	itm.describe = "itmdescr_poison1";
	itm.model = "potion";
	itm.picIndex = 18;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = 24;
	itm.poison.duration = 30;
	itm.poison.chance = 30;
	itm.poison.damage = 2;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // сильнодействующая отрава
	itm.id = "poison2";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison2";
	itm.describe = "itmdescr_poison2";
	itm.model = "potion";
	itm.picIndex = 19;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = 24;
	itm.poison.duration = 60;
	itm.poison.chance = 50;
	itm.poison.damage = 4;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // змеиный яд
	itm.id = "poison3";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison3";
	itm.describe = "itmdescr_poison3";
	itm.model = "potion";
	itm.picIndex = 20;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = -1;
	itm.poison.hitsQ = 50;
	itm.poison.dmgBonus = 1.05;
	itm.poison.InstantKill = 5;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // мышьяковый яд
	itm.id = "poison4";
	itm.groupID = RATPOISON_ITEM_TYPE;
	itm.name = "itmname_poison4";
	itm.describe = "itmdescr_poison4";
	itm.model = "potion";
	itm.picIndex = 21;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.rare = "epic";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // смертельный яд
	itm.id = "poison5";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison5";
	itm.describe = "itmdescr_poison5";
	itm.model = "potion";
	itm.picIndex = 22;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = 24;
	itm.poison.duration = 90;
	itm.poison.chance = 75;
	itm.poison.damage = 6;
	itm.rare = "epic";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // яд листолаза
	itm.id = "poison6";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison6";
	itm.describe = "itmdescr_poison6";
	itm.model = "potion";
	itm.picIndex = 23;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = -1;
	itm.poison.hitsQ = 30;
	itm.poison.dmgBonus = 1.15;
	itm.poison.InstantKill = 10;
	itm.rare = "epic";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // яд кураре
	itm.id = "poison7";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison7";
	itm.describe = "itmdescr_poison7";
	itm.model = "potion";
	itm.picIndex = 24;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = 24;
	itm.poison.duration = 90;
	itm.poison.chance = 100;
	itm.poison.damage = 6;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // яд листоеда
	itm.id = "poison8";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison8";
	itm.describe = "itmdescr_poison8";
	itm.model = "potion";
	itm.picIndex = 25;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = -1;
	itm.poison.hitsQ = 15;
	itm.poison.dmgBonus = 1.25;
	itm.poison.InstantKill = 15;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // яд огненной саламандры
	itm.id = "poison9";
	itm.groupID = POISON_ITEM_TYPE;
	itm.name = "itmname_poison9";
	itm.describe = "itmdescr_poison9";
	itm.model = "potion";
	itm.picIndex = 26;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.minlevel = 1;
	itm.poison.time = 24;
	itm.poison.hitsQ = 1;
	itm.poison.InstantKill = 100;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// Заскриптованные предметы ТОЛЬКО ЗДЕСЬ -->
	////////////////////////////////////////////////////////////////////////////////////////////
	iScriptItemStartNum = n; // Начальный номер заскриптованных предметов
	
	iScriptItemEndNum = n; // Конечный номер заскриптованных предметов
	iScriptItemCount = iScriptItemStartNum-iScriptItemEndNum; // Всего заскриптованных предметов
	////////////////////////////////////////////////////////////////////////////////////////////
	// <-- Заскриптованные предметы ТОЛЬКО ЗДЕСЬ
	////////////////////////////////////////////////////////////////////////////////////////////

	// <<<< ---------------  QUEST ITEMS  --------------------

	makeref(itm,Items[n]); //Песо
	itm.id = "gold";
	itm.name = "itmname_gold";
	itm.describe = "itmdescr_gold";
	itm.model = "";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_JEWELRY";
	itm.price = 0;
	itm.rare = "common";
	n++;
	
	makeref(itm,Items[n]); // серьга с песо
	itm.id = "peso_earring";
	itm.name = "itmname_peso_earring";
	itm.describe = "itmdescr_peso_earring";
	itm.model = "pursel";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_JEWELRY";
	itm.price = 3;
	itm.jewel = true;
	itm.Weight = 0.1;
	itm.rare = "common";
	n++;
	
	makeref(itm,Items[n]); // Дублон
	itm.id = "gold_dublon";
	itm.name = "itmname_gold_dublon";
	itm.describe = "itmdescr_gold_dublon";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_JEWELRY";
	itm.price = 100;
	itm.Weight = 0.1;
	itm.rare = "rare";
	itm.jewel = true;
	itm.multiobject = true;
	itm.multiobject.qty = 150;
	itm.fixedprice = true;
	n++;
	
	// Кошель
	makeref(itm,Items[n]);
	itm.id = "purse1";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_purse1";
	itm.describe = "itmdescr_purse1";
    itm.model = "purseM";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_JEWELRY";
	itm.price = 0;
	itm.subdescribe = true;
	itm.Weight = 1.0;
	itm.rare = "rare";
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); //Лицензия ГВИК
	itm.id = "DutTradeLicence";
	itm.name = "itmname_DutTradeLicence";
	itm.describe = "itmdescr_DutTradeLicence";
	itm.model = "pursel";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_QUEST1";
	itm.price = 0;
	itm.Weight = 0.1;
	itm.days = 90;
	itm.rare = "Legendary";
	itm.ItemType = "QUESTITEMS";
	n++;
    
    makeref(itm,Items[n]); //Отмычки
	itm.id = "lockpick";
	itm.name = "itmname_lockpick";
	itm.describe = "itmdescr_lockpick";
	itm.model = "keygrand";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_QUEST1";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.rare = "common";
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); // Ключ простой
	itm.id = "key1";
	itm.name = "itmname_Key1";
	itm.describe = "itmdescr_Key1";
	itm.model = "keysimple";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_QUEST1";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.rare = "common";
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); // Ключ средний
	itm.id = "key2";
	itm.name = "itmname_Key2";
	itm.describe = "itmdescr_Key2";
	itm.model = "keymiddle";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_QUEST1";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.rare = "rare";
	itm.ItemType = "QUESTITEMS";
	n++;

	makeref(itm,Items[n]); // Ключ сложный
	itm.id = "key3";
	itm.name = "itmname_Key3";
	itm.describe = "itmdescr_Key3";
	itm.model = "keygrand";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_QUEST1";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.rare = "Epic";
	itm.ItemType = "QUESTITEMS";
	n++;
	
	makeref(itm,Items[n]); // Ключ необыкновенный
	itm.id = "key4";
	itm.name = "itmname_Key4";
	itm.describe = "itmdescr_Key4";
	itm.model = "keygrand";
	itm.picIndex = 8;
	itm.picTexture = "ITEMS_QUEST1";
	itm.Weight = 0.0;
	itm.price = 0;
	itm.rare = "Legendary";
	itm.ItemType = "QUESTITEMS";
	n++;
	
	// Tравки - тоже сюда, чтобы можно было собирать гербарий
	makeref(itm,Items[n]); // 1-5 Трава дьявола (дурман)
	itm.id = "cannabis1";
	itm.name = "itmname_cannabis1";
	itm.describe = "itmdescr_cannabis1";
    itm.model = "flower";
	itm.picIndex = 2;
	itm.picTexture = "items_Ingredients";
	itm.price = 30;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // 1-5 Борец
	itm.id = "cannabis2";
	itm.name = "itmname_cannabis2";
	itm.describe = "itmdescr_cannabis2";
    itm.model = "flower";
	itm.picIndex = 1;
	itm.picTexture = "items_Ingredients";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // 1-5 Вербена
	itm.id = "cannabis3";
	itm.name = "itmname_cannabis3";
	itm.describe = "itmdescr_cannabis3";
    itm.model = "flower";
	itm.picIndex = 5;
	itm.picTexture = "items_Ingredients";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // 1-5 Ипекакуана (рвотный корень)
	itm.id = "cannabis4";
	itm.name = "itmname_cannabis4";
	itm.describe = "itmdescr_cannabis4";
    itm.model = "flower";
	itm.picIndex = 4;
	itm.picTexture = "items_Ingredients";
	itm.price = 7;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // 1-3 Гуарана
	itm.id = "cannabis5";
	itm.name = "itmname_cannabis5";
	itm.describe = "itmdescr_cannabis5";
    itm.model = "flower";
	itm.picIndex = 15;
	itm.picTexture = "items_Ingredients";
	itm.price = 12;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // 1-5 Ямайский перец
	itm.id = "cannabis6";
	itm.name = "itmname_cannabis6";
	itm.describe = "itmdescr_cannabis6";
    itm.model = "flower";
	itm.picIndex = 3;
	itm.picTexture = "items_Ingredients";
	itm.price = 10;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // 1-1 Конопля
	itm.id = "cannabis7";
	itm.name = "itmname_cannabis7";
	itm.describe = "itmdescr_cannabis7";
    itm.model = "durman";
	itm.picIndex = 27;
	itm.picTexture = "items_Ingredients";
	itm.price = 500;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // 1-3 Дамиана
	itm.id = "cannabis8";
	itm.name = "itmname_cannabis8";
	itm.describe = "itmdescr_cannabis8";
    itm.model = "flower";
	itm.picIndex = 16;
	itm.picTexture = "items_Ingredients";
	itm.price = 500;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // 1-3 Корень кошачьей петрушки
	itm.id = "cannabis9";
	itm.name = "itmname_cannabis9";
	itm.describe = "itmdescr_cannabis9";
    itm.model = "flower";
	itm.picIndex = 14;
	itm.picTexture = "items_Ingredients";
	itm.price = 500;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // 1-1 (Тобаго, Кумана, Каракас) Стебель стрихноса
	itm.id = "cannabis10";
	itm.name = "itmname_cannabis10";
	itm.describe = "itmdescr_cannabis10";
    itm.model = "flower";
	itm.picIndex = 24;
	itm.picTexture = "items_Ingredients";
	itm.price = 500;
	itm.Weight = 0.5;
	itm.minlevel = 1;
	itm.rare = "epic";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	ItemsForLocators_end = n; //конечный номер для спец. предметов

    //  ЗАПОЛНЕНИЕ ТРУПОВ
    ItemDeadStartCount = n;
    trace("Заполнение трупов с предмета "+ItemDeadStartCount);
	
    //SPYGLASSES
	makeref(itm,Items[n]); // Позорная труба
	itm.id = "spyglass1";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass1";
	itm.describe = "itmdescr_spyglass1";
	itm.picIndex = 1;
	itm.picTexture = "Items_Spyglass";
	// boal 19.01.2004 -->
	itm.price = 1500;
	itm.Weight = 1.5;
    // boal 19.01.2004 <--
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.scope.texture = "eye_CommonTub.tga";
	itm.scope.zoom = 4.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 0;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 0;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 0;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 0;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 0;
	itm.scope.show.mushketshot = 0;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.ItemType = "SUPPORT";
	itm.quality = "ordinary";
	n++;

	makeref(itm,Items[n]);
	itm.id = "spyglass2";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass2";
	itm.describe = "itmdescr_spyglass2";
	itm.picIndex = 2;
	itm.picTexture = "Items_Spyglass";
	itm.price = 4500;
	// boal 19.01.2004 -->
	itm.Weight = 2;
    // boal 19.01.2004 <--
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.scope.texture = "eye_GoodTub.tga";
	itm.scope.zoom = 7.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 0;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 0;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 0;
	itm.scope.show.mushketshot = 1;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.ItemType = "SUPPORT";
	itm.quality = "good";
	n++;

	makeref(itm,Items[n]);
	itm.id = "spyglass3";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass3";
	itm.describe = "itmdescr_spyglass3";
	itm.picIndex = 3;
	itm.picTexture = "Items_Spyglass";
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.price = 12000;
	// boal 19.01.2004 -->
	itm.Weight = 4;
    // boal 19.01.2004 <--
	itm.scope.texture = "eye_BestTub.tga";
	itm.scope.zoom = 10.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 1;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 1;
	itm.scope.show.cannontype = 0;
	itm.scope.show.captain_skills = 1;
	itm.scope.show.mushketshot = 1;
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.ItemType = "SUPPORT";
	itm.quality = "good";
	n++;
	
	makeref(itm,Items[n]);
	itm.id = "spyglass4";
	itm.groupID = SPYGLASS_ITEM_TYPE;
	itm.name = "itmname_spyglass4";
	itm.describe = "itmdescr_spyglass4";
	itm.picIndex = 4;
	itm.picTexture = "Items_Spyglass";
	itm.folder = "items";
	itm.model = "spyglass4";
	itm.price = 75000;
	// boal 19.01.2004 -->
	itm.Weight = 7;
    // boal 19.01.2004 <--
	itm.scope.texture = "eye_BestTub.tga";
	itm.scope.zoom = 15.0;
	itm.scope.time_activate = 500;
	itm.scope.time_update = 150;
	itm.scope.show.nation = 1;
	itm.scope.show.cannons = 1;
	itm.scope.show.ship_name = 1;
	itm.scope.show.ship_type = 1;
	itm.scope.show.hull = 1;
	itm.scope.show.sail = 1;
	itm.scope.show.crew = 1;
	itm.scope.show.speed = 1;
	itm.scope.show.charge = 1;
	itm.scope.show.cannontype = 1;
	itm.scope.show.captain_skills = 1;
	itm.scope.show.mushketshot = 1;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.ItemType = "SUPPORT";
	itm.quality = "excellent";
	n++;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//							ЛЕЧИЛКИ И ТРАВЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	makeref(itm,Items[n]); // Зелье
	itm.id = "potion1";
	itm.name = "itmname_potion1";
	itm.describe = "itmdescr_potion1";
	itm.model = "potion";
	itm.picIndex = 1;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.health = 50.0;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]); // Эликсир
	itm.id = "potion2";
	itm.name = "itmname_potion2";
	itm.describe = "itmdescr_potion2";
	itm.model = "potionbig";
	itm.picIndex = 2;
	itm.picTexture = "items_potions";
	itm.price = 500;
	itm.Weight = 1;
	itm.potion.pic = 22;
	itm.potion.tex = 0; 
	itm.potion.health = 100.0;
	itm.potion.health.speed = 8;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);  // Противоядие
	itm.id = "potion3";
	itm.name = "itmname_potion3";
	itm.describe = "itmdescr_potion3";
	itm.model = "Antidote";
	itm.picIndex = 3;
	itm.picTexture = "items_potions";
	itm.price = 200;
	itm.Weight = 0.4;
	itm.potion.pic = 23;
	itm.potion.tex = 0; 
	itm.potion.antidote = true;
	itm.minlevel = 1;
	itm.rare = "common";	
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]);  // Микстура
	itm.id = "potion4";
	itm.name = "itmname_potion4";
	itm.describe = "itmdescr_potion4";
	itm.model = "balsam";
	itm.picIndex = 4;
	itm.picTexture = "items_potions";
	itm.price = 900;
	itm.Weight = 0.4;
	itm.potion.pic = 24;
	itm.potion.tex = 0; 
	itm.potion.health = 80.0;
	itm.potion.health.speed = 6;
	itm.potion.antidote = true;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]); // Выпили, суки ром!
	itm.id = "potionrum";
	itm.name = "itmname_potionrum";
	itm.describe = "itmdescr_potionrum";
    itm.model = "vodka";
	itm.picIndex = 22;
	itm.picTexture = "items_Ingredients";
	itm.price = 150;
	itm.Weight = 2;
	itm.potion.pic = 10;
	itm.potion.tex = 0; 
	itm.potion.health = 10.0;
	itm.potion.antidote = true;
	//navy -->
	itm.potion.drunk = 51;
	itm.potion.drunk.time = 5600;
	//<--
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

	makeref(itm,Items[n]); // Вино разбавленное
	itm.id = "potionwine";
	itm.name = "itmname_potionwine";
	itm.describe = "itmdescr_potionwine";
    itm.model = "balsam";
	itm.picIndex = 21;
	itm.picTexture = "items_Ingredients";
	itm.price = 500;
	itm.Weight = 1;
	itm.potion.pic = 26;
	itm.potion.tex = 0; 
	itm.potion.health = 20.0;
	//navy -->
	itm.potion.drunk = 15;
	itm.potion.drunk.time = 8000;
	//<--
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;

    makeref(itm,Items[n]); // Имбирный корень
	itm.id = "potion5";
	itm.name = "itmname_potion5";
	itm.describe = "itmdescr_potion5";
    itm.model = "balsam";
	itm.picIndex = 6;
	itm.picTexture = "items_Ingredients";
	itm.price = 30;
	itm.Weight = 0.4;
	itm.potion.pic = 27;
	itm.potion.tex = 0; 
	itm.potion.health = 25.0;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	// Rebbebion, новые лечилки
	makeref(itm,Items[n]); // пресная вода
	itm.id = "potionwater";
	itm.name = "itmname_potionwater";
	itm.describe = "itmdescr_potionwater";
	itm.model = "pursel";
	itm.picIndex = 8;
	itm.picTexture = "items_Ingredients";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.health = 5.0;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // кокос
	itm.id = "potioncoconut";
	itm.name = "itmname_potioncoconut";
	itm.describe = "itmdescr_potioncoconut";
	itm.model = "coconut";
	itm.picIndex = 7;
	itm.picTexture = "items_Ingredients";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.health = 5.0;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // гуайява
	itm.id = "potionguava";
	itm.name = "itmname_potionguava";
	itm.describe = "itmdescr_potionguava";
	itm.model = "pursel";
	itm.picIndex = 18;
	itm.picTexture = "items_Ingredients";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.health = 10.0;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // отвар Ягуара
	itm.id = "potionjaguar";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionjaguar";
	itm.describe = "itmdescr_potionjaguar";
	itm.model = "";
	itm.picIndex = 6;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "Jaguar";
	itm.potion.special.time = 3;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // Слёзы Иш-Чель
	itm.id = "potion6";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potion6";
	itm.describe = "itmdescr_potion6";
    itm.model = "balsam";
	itm.picIndex = 7;
	itm.picTexture = "items_potions";
	itm.price = 3000;
	itm.Weight = 0.2;
	itm.potion.special = true;
	itm.potion.special.effect = "potion6";
	itm.potion.special.Health = 10;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // эликсир Иш-Таб
	itm.id = "potionishtab";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionishtab";
	itm.describe = "itmdescr_potionishtab";
	itm.model = "";
	itm.picIndex = 8;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "ishtab"; 
	itm.potion.special.time = 3;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // зелье Ицамна
	itm.id = "potionitzamna";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionitzamna";
	itm.describe = "itmdescr_potionitzamna";
	itm.model = "";
	itm.picIndex = 9;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "itzamna"; 
	itm.potion.special.time = 3;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // эссенция Эекатля
	itm.id = "potioneekatl";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potioneekatl";
	itm.describe = "itmdescr_potioneekatl";
	itm.model = "";
	itm.picIndex = 10;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "eekatl"; 
	itm.potion.special.time = 3;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "rare";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // Тинктура Бонди
	itm.id = "berserker_potion";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_berserker_potion";
	itm.describe = "itmdescr_berserker_potion";
    itm.model = "balsam";
	itm.picIndex = 11;
	itm.picTexture = "items_potions";
	itm.price = 8000;
	itm.Weight = 1;
	itm.potion.special = true; 
	itm.potion.special.effect = "berserker_potion";
	itm.potion.special.sec = 12;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // благословение Кетцалькоатля
	itm.id = "potionquetzalcoatl";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionquetzalcoatl";
	itm.describe = "itmdescr_potionquetzalcoatl";
	itm.model = "";
	itm.picIndex = 12;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "quetzalcoatl"; 
	itm.potion.special.time = 6;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // сила Тлалока
	itm.id = "potiontlaloc";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potiontlaloc";
	itm.describe = "itmdescr_potiontlaloc";
	itm.model = "";
	itm.picIndex = 13;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "tlaloc";
	itm.potion.special.time = 6;
	itm.potion.special.Health = -1;
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // Отличное вино
	itm.id = "potionwineGood";
	itm.name = "itmname_potionwineGood";
	itm.describe = "itmdescr_potionwineGood";
    itm.model = "balsam";
	itm.picIndex = 5;
	itm.picTexture = "items_potions";
	itm.price = 500;
	itm.Weight = 1;
	itm.potion.pic = 26;
	itm.potion.tex = 0; 
	itm.potion.health = 175.0;
	itm.potion.health.speed = 10;
	itm.potion.antidote = true;
	//navy -->
	itm.potion.drunk = 15;
	itm.potion.drunk.time = 8000;
	//<--
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.SortIndex = 2;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // поддержка Лоа
	itm.id = "potionloa";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionloa";
	itm.describe = "itmdescr_potionloa";
	itm.model = "";
	itm.picIndex = 14;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0;
	itm.potion.special = true; 
	itm.potion.special.effect = "loa";
	itm.potion.special.time = 24;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // дух Легбы
	itm.id = "potionlegba";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionlegba";
	itm.describe = "itmdescr_potionlegba";
	itm.model = "";
	itm.picIndex = 15;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "legba";
	itm.potion.special.time = 24;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // дар Уицилопочтли
	itm.id = "potionhuitzilopochtli";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionhuitzilopochtli";
	itm.describe = "itmdescr_potionhuitzilopochtli";
	itm.model = "";
	itm.picIndex = 16;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "huitzilopochtli";
	itm.potion.special.time = 24;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // длань Миктлантекутли
	itm.id = "potionmictlantecuhtli";
	itm.groupID		= SPECIAL_ITEM_TYPE;
	itm.name = "itmname_potionmictlantecuhtli";
	itm.describe = "itmdescr_potionmictlantecuhtli";
	itm.model = "";
	itm.picIndex = 17;
	itm.picTexture = "items_potions";
	itm.price = 100;
	itm.Weight = 0.8;
	itm.potion.pic = 21;
	itm.potion.tex = 0; 
	itm.potion.special = true; 
	itm.potion.special.effect = "mictlantecuhtli";
	itm.potion.special.time = 24;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.SortIndex = 2;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
    
    makeref(itm,Items[n]); // Пуля
	itm.id = "bullet";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_bullet";
	itm.describe = "itmdescr_bullet";
	itm.model = "pursel";
	itm.picIndex = 1;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.ammo_type = "bullet";
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // Порох
	itm.id = "GunPowder";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_GunPowder";
	itm.describe = "itmdescr_GunPowder";
	itm.model = "pursel";
	itm.picIndex = 2;
	itm.picTexture = "items_ammunition";
	itm.Weight = 0.1;
	itm.price = 8;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.ammo_type = "powder";
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // Картечь
	itm.id = "grapeshot";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_grapeshot";
	itm.describe = "itmdescr_grapeshot";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.ammo_type = "grape";
	itm.SortIndex = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // Бум. патрон
	itm.id = "Cartridge";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_Cartridge";
	itm.describe = "itmdescr_Cartridge";
	itm.model = "pursel";
	itm.picIndex = 4;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.ammo_type = "bullet";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // Ежовый заряд
	itm.id = "GunEchin";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_GunEchin";
	itm.describe = "itmdescr_GunEchin";
	itm.model = "pursel";
	itm.picIndex = 5;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "common";
	itm.ammo_type = "grape";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // Granate!
	itm.id = "Grenade";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_Grenade";
	itm.describe = "itmdescr_Grenade";
	itm.model = "pursel";
	itm.picIndex = 6;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.ammo_type = "bomb";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]);  // Petarde!
	itm.id = "Petard";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_Petard";
	itm.describe = "itmdescr_Petard";
	itm.model = "pursel";
	itm.picIndex = 7;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "Epic";
	itm.ammo_type = "bomb";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); // Ядовитая бомба
	itm.id = "Poison_bomb";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_Poison_bomb";
	itm.describe = "itmdescr_Poison_bomb";
	itm.model = "pursel";
	itm.picIndex = 10;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.ammo_type = "bomb";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); //Серебрянная пуля
	itm.id = "silver_bullet";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_silver_bullet";
	itm.describe = "itmdescr_silver_bullet";
	itm.model = "pursel";
	itm.picIndex = 8;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.ammo_type = "bullet";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); //Серебряный картридж
	itm.id = "Silver_cartridge";
	itm.groupID		= AMMO_ITEM_TYPE;
	itm.name = "itmname_Silver_cartridge";
	itm.describe = "itmdescr_Silver_cartridge";
	itm.model = "pursel";
	itm.picIndex = 9;
	itm.picTexture = "items_ammunition";
	itm.price = 4;
	itm.Weight = 0.1;
	itm.minlevel = 1;
	itm.rare = "Legendary";
	itm.ammo_type = "bullet";
	itm.SortIndex = 1;
	itm.multiobject = true;		
	itm.multiobject.qty = 1;
	itm.ItemType = "SUPPORT";
	n++;
	
	makeref(itm,Items[n]); //Слесарные инструменты
	itm.id = "Instrument1";
	itm.name = "itmname_Instrument1";
	itm.describe = "itmdescr_Instrument1";
	itm.model = "pursel";
	itm.picIndex = 7;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 1500;
	itm.Weight = 5.0;
	itm.rare = "Legendary";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;
	
	makeref(itm,Items[n]); //Сундук алхимика
	itm.id = "Instrument2";
	itm.name = "itmname_Instrument2";
	itm.describe = "itmdescr_Instrument2";
	itm.model = "pursel";
	itm.picIndex = 6;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 1500;
	itm.Weight = 5.0;
	itm.rare = "Legendary";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;
	
	makeref(itm,Items[n]); //тигель
	itm.id = "Instrument3";
	itm.name = "itmname_Instrument3";
	itm.describe = "itmdescr_Instrument3";
	itm.model = "pursel";
	itm.picIndex = 5;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 2000;
	itm.Weight = 2.0;
	itm.rare = "rare";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;
	
	makeref(itm,Items[n]); //медный кувшин
	itm.id = "Instrument4";
	itm.name = "itmname_Instrument4";
	itm.describe = "itmname_Instrument4";
	itm.model = "pursel";
	itm.picIndex = 1;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 50;
	itm.Weight = 0.2;
	itm.rare = "common";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;
	
	makeref(itm,Items[n]); //ступка с пестиком
	itm.id = "Instrument5";
	itm.name = "itmname_Instrument5";
	itm.describe = "itmname_Instrument5";
	itm.model = "pursel";
	itm.picIndex = 3;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 50;
	itm.Weight = 0.2;
	itm.rare = "rare";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;	
	
	makeref(itm,Items[n]); //бронзовая лампадка
	itm.id = "Instrument6";
	itm.name = "itmname_Instrument6";
	itm.describe = "itmname_Instrument6";
	itm.model = "pursel";
	itm.picIndex = 4;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 50;
	itm.Weight = 3.0;
	itm.rare = "common";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;
	
	makeref(itm,Items[n]); //серебряный кувшин
	itm.id = "Instrument7";
	itm.name = "itmname_Instrument7";
	itm.describe = "itmname_Instrument7";
	itm.model = "pursel";
	itm.picIndex = 2;
	itm.picTexture = "ITEMS_TOOLS";
	itm.price = 50;
	itm.Weight = 0.6;
	itm.rare = "rare";
	itm.ItemType = "SUPPORT";
	itm.special_item = true;
	n++;
	
	n = InitStdItem( n,   "mineral1", 	  "pursel", "items_minerals",  1,     "common",   0,   130, 0,   0.1); // черепаховый гребень 
	n = InitStdItem( n,   "mineral2", 	  "pursel", "items_minerals",  3,     "common",   0,    10, 0,   1.0); // свеча                  
	n = InitStdItem( n,   "mineral3", 	  "pursel", "items_minerals",  7,     "common",   0,   140, 0,   0.8); // трубка                       
	n = InitStdItem( n,   "mineral4", 	  "pursel", "items_minerals",  2,     "common",   4,    30, 0,   1.0); // старый башмак                  
	n = InitStdItem( n,   "mineral5", 	  "pursel", "items_minerals",  8,     "common",   2,    80, 0,   1.0); // глиняная кружка              
	n = InitStdItem( n,   "mineral6", 	  "pursel", "items_minerals",  9,     "common",   4,   180, 0,   0.6); // глиняный кувшин              
	n = InitStdItem( n,   "mineral7", 	  "pursel", "items_minerals",  11,    "common",   1,   120, 0,   0.4); // коробка с курительным табаком
	n = InitStdItem( n,   "mineral8", 	  "pursel", "items_minerals",  15,    "common",   1,   100, 0,   0.1); // письменные принадлежности   
	//n = InitStdItem( n,   "mineral9", 	  "pursel", "items_minerals",  16,    "common",   1,    20, 0,   0.1); // шпагат	                   
	n = InitStdItem( n,  "mineral10", 	  "pursel", "items_minerals",  13,    "common",   1,    30, 0,   0.1); // игральные карты              
	n = InitStdItem( n,  "mineral11", 	  "pursel", "items_minerals",  4,     "common",   1,   220, 0,   6.0); // лютня                       
	n = InitStdItem( n,  "mineral12", 	  "pursel", "items_minerals",  5,     "common",   1,    15, 0,  0.25); // старое ведро                
	n = InitStdItem( n,  "mineral13", 	  "pursel", "items_minerals",  6,     "common",   1,    40, 0,  0.25); // коралл                        
	n = InitStdItem( n,  "mineral14", 	  "pursel", "items_minerals",  10,    "common",   1,    60, 0,   0.3); // мешочек соли              
	n = InitStdItem( n,  "mineral15", 	  "pursel", "items_minerals",  12,    "common",   1,   200, 0,   0.1); // серебряный кубок   
	n = InitStdItem( n,  "mineral16", 	  "pursel", "items_minerals",  14,    "common",   1,    20, 0,   0.2); // баклан            
	
	n = InitStdItem( n,  "ingredient1",  "pursel", "items_Ingredients",   9,   "common",      1,   10, 0,   0.2); // склянка                
	n = InitStdItem( n,  "ingredient2",  "pursel", "items_Ingredients",   10,  "common",      1,   15, 0,   0.3); // флакон                  
	n = InitStdItem( n,  "ingredient3",  "pursel", "items_Ingredients",   11,  "rare",        1,   75, 0,   0.1); // бурдюк
	n = InitStdItem( n,  "ingredient4",  "pursel", "items_Ingredients",   23,  "rare",        1,   90, 0,   0.1); // алебастровый сосуд
	n = InitStdItem( n,  "ingredient5",  "pursel", "items_Ingredients",   17,  "rare",        1,   55, 0,   0.1); // железы сурукуку
	n = InitStdItem( n,  "ingredient6",  "pursel", "items_Ingredients",   25,  "epic",        1,  120, 0,   0.1); // кожица ужасного листолаза
	n = InitStdItem( n,  "ingredient7",  "pursel", "items_Ingredients",   26,  "Legendary",   1,  120, 0,   0.1); // личинки жука-листоеда
	n = InitStdItem( n,  "ingredient8",  "pursel", "items_Ingredients",   19,  "rare",        1,   60, 0,   0.1); // сок Агавы 
	n = InitStdItem( n,  "ingredient9",  "pursel", "items_Ingredients",   20,  "rare",        1,   30, 0,   0.1); // миндальный орех
	n = InitStdItem( n,  "ingredient10", "pursel", "items_Ingredients",   28,  "epic",        1,  100, 0,   0.1); // мышьяк (необработанный)
	n = InitStdItem( n,  "ingredient11", "pursel", "items_Ingredients",   12,  "common",      1,    5, 0,   0.1); // гвоздь
	n = InitStdItem( n,  "ingredient15", "pursel", "items_Ingredients",   13,  "common",      1,   20, 0,   0.1); // шпагат
	
	n = InitStdItem( n,  "ingredient12", "pursel", "ITEMS_QUEST1",    9,    "epic",        1, 1000, 0,   0.1); // Метеоритный камень
	n = InitStdItem( n,  "ingredient13", "pursel", "ITEMS_QUEST1",    10,   "epic",        1, 1000, 0,   0.1); // Вулканическое стекло
	n = InitStdItem( n,  "ingredient14", "pursel", "ITEMS_QUEST1",    11,   "Legendary",   1, 1000, 0,   0.1); // Панцирь гигантского краба
	
	itm = ItemsFromID("ingredient12");
	itm.special_item = true;
	
	itm = ItemsFromID("ingredient13");
	itm.special_item = true;
	
	itm = ItemsFromID("ingredient14");
	itm.special_item = true;
	
	n = InitStdItem( n,   "jewelry1", 	 "pursel", "ITEMS_JEWELRY",   9,    "Epic",        0,  130, 0,   0.1); //Золотой самородок                              
	n = InitStdItem( n,   "jewelry2", 	 "pursel", "ITEMS_JEWELRY",   10,   "rare",        0,  130, 0,   0.1); //Серебряный самородок                         
	n = InitStdItem( n,   "jewelry3", 	 "pursel", "ITEMS_JEWELRY",   11,   "Legendary",   0,  130, 0,   0.1); //Алмаз                                             
	n = InitStdItem( n,   "jewelry4", 	 "pursel", "ITEMS_JEWELRY",   12,   "Epic",        0,  130, 0,   0.1); //Рубин                                        
	n = InitStdItem( n,   "jewelry5", 	 "pursel", "ITEMS_JEWELRY",   13,   "Epic",        0,  130, 0,   0.1); //Сапфир                                          
	n = InitStdItem( n,   "jewelry6", 	 "pursel", "ITEMS_JEWELRY",   14,   "Epic",        0,  130, 0,   0.1); //Изумруд                                                 
	n = InitStdItem( n,   "jewelry7", 	 "pursel", "ITEMS_JEWELRY",   15,   "rare",        0,  130, 0,   0.1); //Аметист                                               
	n = InitStdItem( n,   "jewelry8", 	 "pursel", "ITEMS_JEWELRY",   16,   "common",      0,  130, 0,   0.1); //Янтарь                                               
	n = InitStdItem( n,   "jewelry9", 	 "pursel", "ITEMS_JEWELRY",   17,   "common",      0,  130, 0,   0.1); //Серебряное кольцо                                   
	n = InitStdItem( n,   "jewelry10",   "pursel", "ITEMS_JEWELRY",   18,   "rare",        0,  130, 0,   0.1); //Серебряное кольцо с сапфиром                         
	n = InitStdItem( n,   "jewelry11",   "pursel", "ITEMS_JEWELRY",   19,   "rare",        0,  130, 0,   0.1); //Золотое кольцо с изумрудом                           
	n = InitStdItem( n,   "jewelry12",   "pursel", "ITEMS_JEWELRY",   20,   "rare",        0,  130, 0,   0.1); //Золотое кольцо с сапфирами                         
	n = InitStdItem( n,   "jewelry13",   "pursel", "ITEMS_JEWELRY",   21,   "rare",        0,  130, 0,   0.1); //Золотое кольцо с рубином                             
	n = InitStdItem( n,   "jewelry14",   "pursel", "ITEMS_JEWELRY",   22,   "common",      0,  130, 0,   0.1); //Золотая брошь                                        
	n = InitStdItem( n,   "jewelry15",   "pursel", "ITEMS_JEWELRY",   23,   "common",      0,  130, 0,   0.1); //Изумрудные подвески                                  
	n = InitStdItem( n,   "jewelry16",   "pursel", "ITEMS_JEWELRY",   24,   "common",      0,  130, 0,   0.1); //Камея                                                
	n = InitStdItem( n,   "jewelry17",   "pursel", "ITEMS_JEWELRY",   25,   "common",      0,  130, 0,   0.1); //Малая жемчужина                                       
	n = InitStdItem( n,   "jewelry18",   "pursel", "ITEMS_JEWELRY",   26,   "rare",        0,  130, 0,   0.1); //Большая жемчужина                                     
	n = InitStdItem( n,   "jewelry19",   "pursel", "ITEMS_JEWELRY",   27,   "common",      0,  130, 0,   0.1); //Браслет конкистадоров                               
	n = InitStdItem( n,   "jewelry20",   "pursel", "ITEMS_JEWELRY",   28,   "rare",        0,  130, 0,   0.1); //Золотой украшенный кубок                             
	n = InitStdItem( n,   "jewelry21",   "pursel", "ITEMS_JEWELRY",   29,   "Epic",        0,  130, 0,   0.1); //Церемониальная маска Майя // (Только аборигены с Мэйна)
	n = InitStdItem( n,   "jewelry22",   "pursel", "ITEMS_JEWELRY",   30,   "Epic",        0,  130, 0,   0.1); //Статуэтка Ацтеков // (Только аборигены с Мэйна)      
	n = InitStdItem( n,   "jewelry23",   "pursel", "ITEMS_JEWELRY",   31,   "Epic",        0,  130, 0,   0.1); //Золотой браслет Инков // (Только аборигены с Мэйна)  
	
	// пошли рецепты. Боеприпасы...
	n = InitStdRecipies(n, "recipe_cartridge", "cartridge", 450);
	n = InitStdRecipies(n, "recipe_Grenade", "Grenade", 450);
	n = InitStdRecipies(n, "recipe_Petard", "Petard", 450);
	n = InitStdRecipies(n, "recipe_Poison_bomb", "Poison_bomb", 450);
	
	// яды...
	n = InitStdRecipies(n, "recipe_poison1", "poison1", 450);
	n = InitStdRecipies(n, "recipe_poison2", "poison2", 450);
	n = InitStdRecipies(n, "recipe_poison3", "poison3", 450);
	n = InitStdRecipies(n, "recipe_poison4", "poison4", 450);
	n = InitStdRecipies(n, "recipe_poison5", "poison5", 450);
	n = InitStdRecipies(n, "recipe_poison6", "poison6", 450);
	n = InitStdRecipies(n, "recipe_poison7", "poison7", 450);
	n = InitStdRecipies(n, "recipe_poison8", "poison8", 450);
	
	// лечилки...
	n = InitStdRecipies(n, "recipe_potion1", "potion1", 450);
	n = InitStdRecipies(n, "recipe_potion2", "potion2", 450);
	n = InitStdRecipies(n, "recipe_potion3", "potion3", 450);
	n = InitStdRecipies(n, "recipe_potion4", "potion4", 450);
	n = InitStdRecipies(n, "recipe_potion6", "potion6", 450);
	
	// ... и уникальные зелья
	n = InitStdRecipies(n, "recipe_potionjaguar", "potionjaguar", 450);
	n = InitStdRecipies(n, "recipe_potionishtab", "potionishtab", 450);
	n = InitStdRecipies(n, "recipe_potionitzamna", "potionitzamna", 450);
	n = InitStdRecipies(n, "recipe_potioneekatl", "potioneekatl", 450);
	n = InitStdRecipies(n, "recipe_berserker_potion", "berserker_potion", 450);
	n = InitStdRecipies(n, "recipe_potionquetzalcoatl", "potionquetzalcoatl", 450);
	n = InitStdRecipies(n, "recipe_potiontlaloc", "potiontlaloc", 450);
	n = InitStdRecipies(n, "recipe_potionloa", "potionloa", 450);
	n = InitStdRecipies(n, "recipe_potionlegba", "potionlegba", 450);
	n = InitStdRecipies(n, "recipe_potionhuitzilopochtli", "potionhuitzilopochtli", 450);
	n = InitStdRecipies(n, "recipe_potionmictlantecuhtli", "potionmictlantecuhtli", 450);
	
	trace("Всего предметов (размерность массива) "+n);
	trace("Всего заскриптованных предметов - " + iScriptItemCount);
	trace("Начальный специальный предмет: " + Items[ItemsForLocators_start].id);
	trace("Конечный специальный предмет: " + Items[ItemsForLocators_end].id);
	
	InitGunChargeExts();
	InitMultiObjectAmulets();
	InitItemsCraftingPerks();
	InitRandItems();
	InitItemsRarity();
	
	return n;
}

void InitItemsRarity()
{
	InitStdItemRarity("peso_earring", F_CITY, 1, 3);
	InitStdItemRarity("gold_dublon", F_CITY, 1, 15);
	
	InitStdItemRarity("purse1", F_CITY, 1, 1);
	
	InitStdItemRarity("lockpick", F_CITY, 1, 6);
	
	InitStdItemRarity("spyglass1", F_CITY, 1, 1);
	
	InitStdItemRarity("mineral1", F_CITY, 1, 1);
	InitStdItemRarity("mineral2", F_CITY, 1, 5);
	InitStdItemRarity("mineral3", F_CITY, 1, 1);
	InitStdItemRarity("mineral4", F_CITY, 1, 1);
	InitStdItemRarity("mineral7", F_CITY, 1, 2);
	InitStdItemRarity("mineral8", F_CITY, 1, 1);
	//InitStdItemRarity("mineral9", F_CITY, 1, 2);
	InitStdItemRarity("mineral10", F_CITY, 1, 1);
	InitStdItemRarity("mineral13", F_CITY, 1, 3);
	InitStdItemRarity("mineral14", F_CITY, 1, 1);
	
	InitStdItemRarity("jewelry8", F_CITY, 1, 1);
	InitStdItemRarity("jewelry9", F_CITY, 1, 1);
	InitStdItemRarity("jewelry14", F_CITY, 1, 1);
	InitStdItemRarity("jewelry15", F_CITY, 1, 1);
	InitStdItemRarity("jewelry16", F_CITY, 1, 1);
	InitStdItemRarity("jewelry17", F_CITY, 1, 1);
	InitStdItemRarity("jewelry19", F_CITY, 1, 1);
	
	//InitStdItemRarity("", "", 1, 1);
}

void InitRandItems()
{
	ref rnditem;
	int n = 0;
	
	//Potions
	n = SetLocatorRandItemDrop(rnditem, "potion1", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potion2", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potion3", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potion4", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potion5", n, 1, 5, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potionrum", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potionwine", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potioncoconut", n, 1, 5, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potionguava", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "potionwater", n, 1, 5, "Jungle,Seashore,Chest", "");
	
	//Instruments
	n = SetLocatorRandItemDrop(rnditem, "Instrument3", n, 1, 1, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Instrument4", n, 1, 1, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Instrument5", n, 1, 1, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Instrument6", n, 1, 1, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Instrument7", n, 1, 1, "Chest", "");
	
	//Minerals
	n = SetLocatorRandItemDrop(rnditem, "mineral1", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral2", n, 1, 30, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral3", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral4", n, 1, 4, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral5", n, 1, 5, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral6", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral7", n, 1, 5, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral8", n, 1, 2, "Chest", "");
	//n = SetLocatorRandItemDrop(rnditem, "mineral9", n, 1, 5, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral10", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral11", n, 1, 1, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral12", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral13", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral14", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral15", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "mineral16", n, 1, 1, "Jungle,Seashore,Chest", "");
	
	//Ingredients
	n = SetLocatorRandItemDrop(rnditem, "ingredient1", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient2", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient3", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient4", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient5", n, 1, 2, "Jungle,Seashore", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient6", n, 1, 1, "Jungle,Seashore", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient7", n, 1, 1, "Jungle,Seashore", "Mein");
	n = SetLocatorRandItemDrop(rnditem, "ingredient8", n, 1, 1, "Jungle,Seashore", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient9", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient10", n, 1, 1, "Cave", "");
	n = SetLocatorRandItemDrop(rnditem, "ingredient11", n, 1, 50, "Jungle,Seashore,Chest", "");
	
	n = SetLocatorRandItemDrop(rnditem, "jewelry1", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry2", n, 1, 4, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry3", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry4", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry5", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry6", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry7", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry8", n, 1, 5, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry9", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry10", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry11", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry12", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry13", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry14", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry15", n, 1, 2, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry16", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry17", n, 1, 30, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry18", n, 1, 15, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry19", n, 1, 3, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "jewelry20", n, 1, 1, "Jungle,Seashore,Chest", "");
	
	n = SetLocatorRandItemDrop(rnditem, "totem_01", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "totem_02", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "totem_03", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "totem_04", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "totem_05", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "totem_06", n, 1, 1, "Jungle,Seashore,Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "totem_07", n, 1, 1, "Jungle,Seashore,Chest", "");
	
	n = SetLocatorRandItemDrop(rnditem, "poison1", n, 1, 1, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "gold", n, 1, 121, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "gold_dublon", n, 1, 1, "Chest", "");
	
	n = SetLocatorRandItemDrop(rnditem, "purse1", n, 1, 1, "Jungle,Seashore,Chest", "");
	
	
	n = SetLocatorRandItemDrop(rnditem, "bullet",    n, 1, 5, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "gunpowder", n, 1, 5, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "grapeshot", n, 1, 5, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Cartridge", n, 1, 5, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "GunEchin",  n, 1, 5, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Grenade",   n, 1, 2, "Chest", "");
	n = SetLocatorRandItemDrop(rnditem, "Petard",    n, 1, 2, "Chest", "");
	
    trace("Всего рандомных предметов (размерность массива) " + n);
}

void InitGunChargeExts()
{
	ref rGun;
	InitGunChargeExt("pistol1", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol1", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol1", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol1", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol1");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol2", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol2", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol2", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol2", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol2");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol3", "t1", "grapeshot", "gunpowder", 10, 1);
	rGun = ItemsFromID("pistol3");
	rGun.ammo_type = "grape";
	
	InitGunChargeExt("pistol4", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol4", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol4", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol4", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol4");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol5", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol5", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol5", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol5", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol5");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol6", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol6", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol6", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol6", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol6");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol7", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol7", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol7", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol7", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol7");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol8", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol8", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol8", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol8", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol8");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol9", "t1", "grapeshot", "gunpowder", 10, 1);
	InitGunChargeExt("pistol9", "t2", "GunEchin", "", 10, 1);
	rGun = ItemsFromID("pistol9");
	rGun.ammo_type = "grape";
	
	InitGunChargeExt("pistol10", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol10", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol10", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol10", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol10");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("pistol11", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("pistol11", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("pistol11", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("pistol11", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("pistol11");
	rGun.ammo_type = "bullet";
	
	
	InitGunChargeExt("mushket_matchlock", "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("mushket_matchlock", "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("mushket_matchlock", "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("mushket_matchlock", "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("mushket_matchlock");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("mushket_Arquebus",  "t1", "grapeshot", "gunpowder", 10, 1);
	InitGunChargeExt("mushket_Arquebus",  "t2", "GunEchin", "", 10, 0);
	rGun = ItemsFromID("mushket_Arquebus");
	rGun.ammo_type = "grape";
	
	InitGunChargeExt("mushket_Bayonet",   "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("mushket_Bayonet",   "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("mushket_Bayonet",   "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("mushket_Bayonet",   "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("mushket_Bayonet");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("mushket_Portuguese","t1", "grapeshot", "gunpowder", 10, 1);
	InitGunChargeExt("mushket_Portuguese","t2", "GunEchin", "", 10, 0);
	rGun = ItemsFromID("mushket_Portuguese");
	rGun.ammo_type = "grape";
	
	InitGunChargeExt("mushket_sklopetta", "t1", "Grenade", "", 10, 1);
	InitGunChargeExt("mushket_sklopetta", "t2", "Petard", "", 10, 0);
	InitGunChargeExt("mushket_sklopetta", "t3", "Poison_bomb", "", 10, 0);
	rGun = ItemsFromID("mushket_sklopetta");
	rGun.ammo_type = "bomb";
	
	InitGunChargeExt("mushket_Shtuzer",   "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("mushket_Shtuzer",   "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("mushket_Shtuzer",   "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("mushket_Shtuzer",   "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("mushket_Shtuzer");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("mushket_2x2",       "t1", "bullet", "gunpowder", 10, 1);
	InitGunChargeExt("mushket_2x2",       "t2", "cartridge", "", 5, 0);
	InitGunChargeExt("mushket_2x2",       "t3", "silver_bullet", "gunpowder", 10, 0);
	InitGunChargeExt("mushket_2x2",       "t4", "Silver_cartridge", "", 5, 0);
	rGun = ItemsFromID("mushket_2x2");
	rGun.ammo_type = "bullet";
	
	InitGunChargeExt("mushket_Bombard",   "t1", "Grenade", "", 10, 1);
	InitGunChargeExt("mushket_Bombard",   "t2", "Petard", "", 10, 1);
	InitGunChargeExt("mushket_Bombard",   "t3", "Poison_bomb", "", 10, 1);
	rGun = ItemsFromID("mushket_Bombard");
	rGun.ammo_type = "bomb";
}

void InitMultiObjectAmulets()
{	
	// Бумажный патрон
	InitMultiObject(  	  	"cartridge",	"t1",  	     "bullet",    "Component", 	  1); // пуля
	InitMultiObject(  	  	"cartridge",	"t2",     "gunpowder",    "Component", 	  1); // гранулированный порох
	
	// Ежовый (бедный ёжик XD) заряд
	InitMultiObject(  	  	"GunEchin",	"t1",  	  "gunpowder",         "Component", 	  1); // порох
	InitMultiObject(  	  	"GunEchin",	"t2",     "ingredient11",      "Component", 	 10); // гвоздь
	InitMultiObject(  	  	"GunEchin",	"t3",     "Instrument3",       "AlchemyTool", 	  1); // тигель
	InitMultiObject(  	  	"GunEchin",	"t4",     "Instrument6",       "AlchemyTool", 	  1); //Лампада
	
	// Граната
	InitMultiObject(  	  	"Grenade",	"t1",  	  "bullet",                    "Component", 	 10); // пуля
	InitMultiObject(  	  	"Grenade",	"t2",     "gunpowder",                 "Component", 	 10); // гранулированный порох
	InitMultiObject(  	  	"Grenade",	"t3",     "ingredient15",              "Component", 	  1); // шпагат
	InitMultiObject(  	  	"Grenade",	"t4",     "Instrument1",               "AlchemyTool", 	  1); //Слесарные инструменты
	
	// пЭтарда
	InitMultiObject(  	  	"Petard",	"t1",  	  "Instrument4",               "Component", 	  1); // медный кувшин
	InitMultiObject(  	  	"Petard",	"t2",     "gunpowder",                 "Component", 	 10); // гранулированный порох
	InitMultiObject(  	  	"Petard",	"t3",     "ingredient15",              "Component", 	  1); // шпагат
	InitMultiObject(  	  	"Petard",	"t4",     "Instrument1",               "AlchemyTool", 	  1); //Слесарные инструменты
	
	// Ядовитая Бомба
	InitMultiObject(  	  	"Poison_bomb",	"t1",  	  "poison1",               "Component", 	  1); // пуля
	InitMultiObject(  	  	"Poison_bomb",	"t2",  	  "gunpowder",             "Component",      10);// гранулированный порох
	InitMultiObject(  	  	"Poison_bomb",	"t3",     "ingredient15",          "Component", 	  1); // шпагат
	InitMultiObject(  	  	"Poison_bomb",	"t4",     "Instrument4",           "Component", 	  1); // медный кувшин
	InitMultiObject(  	  	"Poison_bomb",	"t5",     "Instrument1",           "AlchemyTool", 	  1); //Слесарные инструменты
	
	// Серебрянные пули
	InitMultiObject(  	  	"silver_bullet",	"t1",  	     "jewelry2",       "Component", 	  1); // порох
	InitMultiObject(  	  	"silver_bullet",	"t2",          "bullet",       "Component", 	 10); // гвоздь
	InitMultiObject(  	  	"silver_bullet",	"t3",     "Instrument3",       "AlchemyTool", 	  1); // тигель
	InitMultiObject(  	  	"silver_bullet",	"t4",     "Instrument6",       "AlchemyTool", 	  1); //Лампада
	
	// Серебряный картридж
	InitMultiObject(  	 "Silver_cartridge",	"t1", "silver_bullet",    "Component", 	  1); // серебрянная пуля
	InitMultiObject(  	 "Silver_cartridge",	"t2",     "gunpowder",    "Component", 	  1); // гранулированный порох
	
	// Rebbebion, новые рецепты к новым (и не очень) предметам
	// простейшая отрава
	InitMultiObject(		"poison1",	    "t1",     "cannabis2", 	    "Component",   1); // борец
	InitMultiObject(		"poison1",	    "t2",     "potionwater",    "Component",   1); // пресная вода
	InitMultiObject(		"poison1",	    "t3",     "ingredient1",    "Component",   1); // склянка
	InitMultiObject(  		"poison1",	    "t4",     "Instrument4",    "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison1",	    "t5",     "Instrument5",    "AlchemyTool",   1); // ступка с пестиком
	
	// сильнодействующая отрава
	InitMultiObject(		"poison2",	    "t1",     "cannabis2", 	"Component", 	  1); // борец
	InitMultiObject(		"poison2",	    "t2",     "cannabis9",  "Component", 	  1); // корень кошачьей петрушки
	InitMultiObject(		"poison2",	    "t3",     "potionwater",  "Component", 	  1); // пресная вода
	InitMultiObject(		"poison2",	    "t4",     "ingredient2",  "Component", 	  1); // флакон
	InitMultiObject(  		"poison2",	    "t5",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison2",	    "t6",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// змеиный яд
	InitMultiObject(		"poison3",	    "t1",     "ingredient5", 	"Component", 	  1); // железы сурукуку
	InitMultiObject(		"poison3",	    "t2",     "potionwater",  "Component", 	  1); // пресная вода
	InitMultiObject(		"poison3",	    "t3",     "ingredient2",  "Component", 	  1); // флакон
	InitMultiObject(  		"poison3",	    "t4",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison3",	    "t5",     "Instrument6",  "AlchemyTool",   1); // лампадка
	
	// мышьяковый яд
	InitMultiObject(		"poison4",	    "t1",     "ingredient10", 	"Component", 	  1); // мышьяк (необработанный)
	InitMultiObject(		"poison4",	    "t2",     "ingredient2",  "Component", 	  1); // флакон
	InitMultiObject(  		"poison4",	    "t3",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	InitMultiObject(  		"poison4",	    "t4",     "Instrument6",  "AlchemyTool",   1); // лампадка
	
	// смертельная отрава
	InitMultiObject(		"poison5",	    "t1",     "ingredient9", 	"Component", 	  1); // миндальный орех
	InitMultiObject(		"poison5",	    "t2",     "cannabis9",    "Component", 	  1); // корень кошачьей петрушки
	InitMultiObject(		"poison5",	    "t3",     "cannabis2",       "Component", 	  1); // борец
	InitMultiObject(		"poison5",	    "t4",     "potionwater",    "Component", 	  1); // пресная вода
	InitMultiObject(		"poison5",	    "t5",     "ingredient2",     "Component", 	  1); // флакон
	InitMultiObject(  		"poison5",	    "t6",     "Instrument2",    "AlchemyTool",   1); // набор алхимика
	InitMultiObject(  		"poison5",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison5",	    "t8",     "Instrument6",  "AlchemyTool",   1); // лампадка
	InitMultiObject(  		"poison5",	    "t9",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// яд листолаза
	InitMultiObject(		"poison6",	    "t1",     "ingredient6", 	"Component", 	  1); // кожица ужасного листолаза
	InitMultiObject(		"poison6",	    "t2",     "cannabis2",    "Component", 	  1); // борец
	InitMultiObject(		"poison6",	    "t3",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"poison6",	    "t4",     "ingredient1",    "Component", 	  1); // склянка
	InitMultiObject(  		"poison6",	    "t6",     "Instrument2",    "AlchemyTool",   1); // набор алхимика
	InitMultiObject(  		"poison6",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison6",	    "t8",     "Instrument6",  "AlchemyTool",   1); // лампадка
	InitMultiObject(  		"poison6",	    "t9",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// яд кураре
	InitMultiObject(		"poison7",	    "t1",     "cannabis10", 	"Component", 	  1); // стебель стрихноса
	InitMultiObject(		"poison7",	    "t2",     "cannabis2",    "Component", 	  1); // борец
	InitMultiObject(		"poison7",	    "t3",     "cannabis9",    "Component", 	  1); // корень кошачьей петрушки
	InitMultiObject(		"poison7",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"poison7",	    "t5",     "ingredient1",    "Component", 	  1); // склянка
	InitMultiObject(  		"poison7",	    "t6",     "Instrument2",    "AlchemyTool",   1); // набор алхимика
	InitMultiObject(  		"poison7",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison7",	    "t8",     "Instrument6",  "AlchemyTool",   1); // лампадка
	InitMultiObject(  		"poison7",	    "t9",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// яд листоеда
	InitMultiObject(		"poison8",	    "t1",     "ingredient7", 	"Component", 	  1); // личинки жука-листоеда
	InitMultiObject(		"poison8",	    "t2",     "cannabis2",    "Component", 	  1); // борец
	InitMultiObject(		"poison8",	    "t3",     "cannabis9",    "Component", 	  1); // корень кошачьей петрушки
	InitMultiObject(		"poison8",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"poison8",	    "t5",     "ingredient1",    "Component", 	  1); // склянка
	InitMultiObject(  		"poison8",	    "t6",     "Instrument2",    "AlchemyTool",   1); // набор алхимика
	InitMultiObject(  		"poison8",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"poison8",	    "t8",     "Instrument6",  "AlchemyTool",   1); // лампадка
	InitMultiObject(  		"poison8",	    "t9",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// лечебное зелье
	InitMultiObject(		"potion1",	    "t1",     "cannabis1", 	"Component", 	  2); // трава дьявола (дурман)
	InitMultiObject(		"potion1",	    "t2",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potion1",	    "t3",     "ingredient1",    "Component", 	  1); // склянка
	InitMultiObject(  		"potion1",	    "t4",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	
	// эликсир
	InitMultiObject(		"potion2",	    "t1",     "cannabis1", 	"Component", 	  3); // трава дьявола (дурман)
	InitMultiObject(		"potion2",	    "t2",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potion2",	    "t3",     "ingredient2",     "Component", 	  1); // флакон
	InitMultiObject(  		"potion2",	    "t4",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potion2",	    "t5",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// противоядие
	InitMultiObject(		"potion3",	    "t1",     "cannabis4", 	"Component", 	  1); // ипекакуана (рвотный корень)
	InitMultiObject(		"potion3",	    "t2",     "cannabis6", 	"Component", 	  1); // ямайский перец
	InitMultiObject(		"potion3",	    "t3",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potion3",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potion3",	    "t5",     "ingredient2",     "Component", 	  1); // флакон
	InitMultiObject(  		"potion3",	    "t6",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potion3",	    "t7",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// микстура
	InitMultiObject(		"potion4",	    "t1",     "cannabis4", 	"Coаmponent", 	  1); // ипекакуана (рвотный корень)
	InitMultiObject(		"potion4",	    "t3",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potion4",	    "t3",     "potion5", 	"Component", 	  1); // имбирный корень
	InitMultiObject(		"potion4",	    "t3",     "cannabis1", 	"Component", 	  1); // трава дьявола (дурман)
	InitMultiObject(		"potion4",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potion4",	    "t3",     "ingredient3", 	"Component", 	  1); // бурдюк
	InitMultiObject(  		"potion4",	    "t6",     "Instrument7",  "AlchemyTool",   1); // серебряный кувшин
	InitMultiObject(  		"potion4",	    "t7",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// отвар Ягуара
	InitMultiObject(		"potionjaguar",	    "t1",     "cannabis5", 	"Component", 	  1); // гуарана
	InitMultiObject(		"potionjaguar",	    "t3",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potionjaguar",	    "t3",     "potionguava", 	"Component",  1); // гуайява
	InitMultiObject(		"potionjaguar",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potionjaguar",	    "t3",     "ingredient1", 	"Component", 	  1); // склянка
	InitMultiObject(  		"potionjaguar",	    "t6",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potionjaguar",	    "t7",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// слёзы Иш-Чель
	InitMultiObject(		"potion6",	    "t1",     "cannabis8", 	"Component", 	  1); // дамиана
	InitMultiObject(		"potion6",	    "t2",     "cannabis4", 	"Component", 	  1); // ипекакуана (рвотный корень)
	InitMultiObject(		"potion6",	    "t3",     "cannabis5", 	"Component", 	  1); // гуарана
	InitMultiObject(		"potion6",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potion6",	    "t5",     "ingredient3", 	"Component", 	  1); // бурдюк
	InitMultiObject(  		"potion6",	    "t6",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potion6",	    "t7",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// эликсир Иш-Таб
	InitMultiObject(		"potionishtab",	    "t1",     "cannabis8", 	"Component", 	  1); // дамиана
	InitMultiObject(		"potionishtab",	    "t2",     "cannabis1", 	"Component", 	  2); // трава дьявола (дурман)
	InitMultiObject(		"potionishtab",	    "t3",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potionishtab",	    "t4",     "ingredient2", 	"Component", 	  1); // флакон
	InitMultiObject(  		"potionishtab",	    "t5",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potionishtab",	    "t6",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// зелье Ицамна
	InitMultiObject(		"potionitzamna",	    "t1",     "cannabis8", 	"Component", 	  1); // дамиана
	InitMultiObject(		"potionitzamna",	    "t2",     "cannabis6", 	"Component", 	  1); // ямайский перец
	InitMultiObject(		"potionitzamna",	    "t3",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potionitzamna",	    "t4",     "potionwater",       "Component", 	  1); // пресная вода
	InitMultiObject(		"potionitzamna",	    "t5",     "ingredient1", 	"Component", 	  1); // склянка
	InitMultiObject(  		"potionitzamna",	    "t6",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potionitzamna",	    "t7",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// эссенция Эекатля
	InitMultiObject(		"potioneekatl",	    "t1",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potioneekatl",	    "t2",     "potionguava", 	"Component", 	  1); // гуайява
	InitMultiObject(		"potioneekatl",	    "t3",     "potion5", 	"Component", 	  1); // имбирный корень
	InitMultiObject(		"potioneekatl",	    "t4",     "potionwater",       "Component",  1); // пресная вода
	InitMultiObject(		"potioneekatl",	    "t5",     "ingredient5", 	"Component", 	  1); // флакон
	InitMultiObject(  		"potioneekatl",	    "t6",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potioneekatl",	    "t7",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	
	// тинктура Бонди
	InitMultiObject(		"berserker_potion",	    "t1",     "cannabis4", 	"Component", 	  1); // ипекакуана (рвотный корень)
	InitMultiObject(		"berserker_potion",	    "t2",     "potion5", 	"Component", 	  1); // имбирный корень
	InitMultiObject(		"berserker_potion",	    "t3",     "potionguava", 	"Component", 	  1); // гуайява
	InitMultiObject(		"berserker_potion",	    "t4",     "cannabis5",       "Component",  1); // гуарана
	InitMultiObject(		"berserker_potion",	    "t5",     "potionrum", 	"Component", 	  1); // ром
	InitMultiObject(		"berserker_potion",	    "t6",     "ingredient4", 	"Component", 	  1); // алебастровый сосуд
	InitMultiObject(  		"berserker_potion",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"berserker_potion",	    "t8",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"berserker_potion",	    "t9",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	
	// благословение Кетцалькоатля
	InitMultiObject(		"potionquetzalcoatl",	    "t1",     "ingredient8", 	"Component", 	  1); // сок Агавы
	InitMultiObject(		"potionquetzalcoatl",	    "t2",     "potion5", 	"Component", 	  1); // имбирный корень
	InitMultiObject(		"potionquetzalcoatl",	    "t3",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potionquetzalcoatl",	    "t4",     "cannabis1",       "Component",  1); // трава дьявола (дурман)
	InitMultiObject(		"potionquetzalcoatl",	    "t5",     "potioncoconut", 	"Component", 	  1); // кокос
	InitMultiObject(		"potionquetzalcoatl",	    "t6",     "ingredient4", 	"Component", 	  1); // алебастровый сосуд
	InitMultiObject(  		"potionquetzalcoatl",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potionquetzalcoatl",	    "t8",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"potionquetzalcoatl",	    "t9",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	
	// сила Тлалока
	InitMultiObject(		"potiontlaloc",	    "t1",     "ingredient8", 	"Component", 	  1); // сок Агавы
	InitMultiObject(		"potiontlaloc",	    "t2",     "cannabis5", 	"Component", 	  1); // гуарана
	InitMultiObject(		"potiontlaloc",	    "t3",     "cannabis6", 	"Component", 	  1); // ямайский перец
	InitMultiObject(		"potiontlaloc",	    "t4",     "cannabis8",       "Component",  1); // дамиана
	InitMultiObject(		"potiontlaloc",	    "t5",     "potioncoconut", 	"Component", 	  1); // кокос
	InitMultiObject(		"potiontlaloc",	    "t6",     "ingredient4", 	"Component", 	  1); // алебастровый сосуд
	InitMultiObject(  		"potiontlaloc",	    "t7",     "Instrument4",  "AlchemyTool",   1); // медный кувшин
	InitMultiObject(  		"potiontlaloc",	    "t8",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"potiontlaloc",	    "t9",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	
	// поддержка Лоа
	InitMultiObject(		"potionloa",	    "t1",     "cannabis7", 	"Component", 	  1); // конопля
	InitMultiObject(		"potionloa",	    "t2",     "cannabis5", 	"Component", 	  1); // гуарана
	InitMultiObject(		"potionloa",	    "t3",     "potionguava", 	"Component", 	  1); // гуайява
	InitMultiObject(		"potionloa",	    "t4",     "cannabis1",       "Component",  2); // трава дьявола (дурман)
	InitMultiObject(		"potionloa",	    "t5",     "potionwine", 	"Component", 	  1); // вино
	InitMultiObject(		"potionloa",	    "t6",     "ingredient3", 	"Component", 	  1); // бурдюк
	InitMultiObject(  		"potionloa",	    "t7",     "Instrument7",  "AlchemyTool",   1); // серебряный кувшин
	InitMultiObject(  		"potionloa",	    "t8",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"potionloa",	    "t9",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	
	// дух Легбы
	InitMultiObject(		"potionlegba",	    "t1",     "cannabis7", 	"Component", 	  1); // конопля
	InitMultiObject(		"potionlegba",	    "t2",     "potion5", 	"Component", 	  1); // имбирный корень
	InitMultiObject(		"potionlegba",	    "t3",     "cannabis6", 	"Component", 	  2); // ямайский перец
	InitMultiObject(		"potionlegba",	    "t4",     "cannabis3",       "Component",  1); // вербена
	InitMultiObject(		"potionlegba",	    "t5",     "potionrum", 	"Component", 	  1); // ром
	InitMultiObject(		"potionlegba",	    "t6",     "ingredient3", 	"Component", 	  1); // бурдюк
	InitMultiObject(  		"potionlegba",	    "t7",     "Instrument7",  "AlchemyTool",   1); // серебряный кувшин
	InitMultiObject(  		"potionlegba",	    "t8",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"potionlegba",	    "t9",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	
	// дар Уицилопочтли
	InitMultiObject(		"potionhuitzilopochtli",	    "t1",     "cannabis7", 	"Component", 	  1); // конопля
	InitMultiObject(		"potionhuitzilopochtli",	    "t2",     "potion5", 	"Component", 	  1); // имбирный корень
	InitMultiObject(		"potionhuitzilopochtli",	    "t3",     "potionguava", 	"Component", 	  1); // гуайява
	InitMultiObject(		"potionhuitzilopochtli",	    "t4",     "ingredient8",       "Component",  1); // сок агавы
	InitMultiObject(		"potionhuitzilopochtli",	    "t5",     "cannabis8", 	"Component", 	  1); // дамиана
	InitMultiObject(		"potionhuitzilopochtli",	    "t6",     "potionrum", 	"Component", 	  1); // ром
	InitMultiObject(		"potionhuitzilopochtli",	    "t7",     "ingredient4", 	"Component", 	  1); // алебастровый сосуд
	InitMultiObject(  		"potionhuitzilopochtli",	    "t8",     "Instrument7",  "AlchemyTool",   1); // серебряный кувшин
	InitMultiObject(  		"potionhuitzilopochtli",	    "t9",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"potionhuitzilopochtli",	    "t10",     "Instrument2",  "AlchemyTool",   1); // набор алхимика
	
	// длань Миктлантекутли
	InitMultiObject(		"potionmictlantecuhtli",	    "t1",     "cannabis7", 	"Component", 	  1); // конопля
	InitMultiObject(		"potionmictlantecuhtli",	    "t2",     "cannabis6", 	"Component", 	  1); // ямайский перец
	InitMultiObject(		"potionmictlantecuhtli",	    "t3",     "cannabis3", 	"Component", 	  1); // вербена
	InitMultiObject(		"potionmictlantecuhtli",	    "t4",     "cannabis5",       "Component",  1); // гуарана
	InitMultiObject(		"potionmictlantecuhtli",	    "t5",     "cannabis4", 	"Component", 	  1); // ипекакуана (рвотный корень)
	InitMultiObject(		"potionmictlantecuhtli",	    "t6",     "potionwineGood", 	"Component", 	  1); // вино
	InitMultiObject(		"potionmictlantecuhtli",	    "t7",     "ingredient4", 	"Component", 	  1); // алебастровый сосуд
	InitMultiObject(  		"potionmictlantecuhtli",	    "t8",     "Instrument7",  "AlchemyTool",   1); // серебряный кувшин
	InitMultiObject(  		"potionmictlantecuhtli",	    "t9",     "Instrument5",  "AlchemyTool",   1); // ступка с пестиком
	InitMultiObject(  		"potionmictlantecuhtli",	    "t10",    "Instrument2",  "AlchemyTool",   1); // набор алхимика
}

//Экку Korsar - Установка предметам требуемых для их крафта перков
void InitItemsCraftingPerks()
{
	//SetItemNeededCraftPerk(_Items, _Perk);
	
	SetItemNeededCraftPerk("GunEchin", "BeginnerAlchemist");
	SetItemNeededCraftPerk("silver_bullet", "BeginnerAlchemist");
	
	
	SetItemNeededCraftPerk("poison2", "BeginnerAlchemist");
	SetItemNeededCraftPerk("poison3", "BeginnerAlchemist");
	
	
	SetItemNeededCraftPerk("Potion4", "BeginnerAlchemist");
	SetItemNeededCraftPerk("potionjaguar", "BeginnerAlchemist");
	SetItemNeededCraftPerk("potion6", "BeginnerAlchemist");
	SetItemNeededCraftPerk("potionishtab", "BeginnerAlchemist");
	SetItemNeededCraftPerk("potionitzamna", "BeginnerAlchemist");
	SetItemNeededCraftPerk("potioneekatl", "BeginnerAlchemist");
	
	
	SetItemNeededCraftPerk("berserker_potion", "SkilledAlchemist");
	SetItemNeededCraftPerk("potionquetzalcoatl", "SkilledAlchemist");
	SetItemNeededCraftPerk("potiontlaloc", "SkilledAlchemist");
	
	SetItemNeededCraftPerk("Poison4", "Poisoner");
	SetItemNeededCraftPerk("Poison4", "SkilledAlchemist");
	
	SetItemNeededCraftPerk("Poison5", "Poisoner");
	SetItemNeededCraftPerk("Poison5", "SkilledAlchemist");
	
	SetItemNeededCraftPerk("Poison6", "Poisoner");
	SetItemNeededCraftPerk("Poison6", "SkilledAlchemist");
	
	SetItemNeededCraftPerk("Grenade", "Pyrotechnician");
	SetItemNeededCraftPerk("Petard", "Pyrotechnician");
	
	
	SetItemNeededCraftPerk("Poison_bomb", "Poisoner");
	SetItemNeededCraftPerk("Poison_bomb", "MasterOfAlchemy");
	
	SetItemNeededCraftPerk("Poison7", "MasterOfAlchemy");
	SetItemNeededCraftPerk("Poison7", "SkilledAlchemist");
	
	SetItemNeededCraftPerk("Poison8", "MasterOfAlchemy");
	SetItemNeededCraftPerk("Poison8", "SkilledAlchemist");
	
	SetItemNeededCraftPerk("potionloa", "MasterOfAlchemy");
	SetItemNeededCraftPerk("potionlegba", "MasterOfAlchemy");
	SetItemNeededCraftPerk("potionhuitzilopochtli", "MasterOfAlchemy");
	SetItemNeededCraftPerk("potionmictlantecuhtli", "MasterOfAlchemy");
}
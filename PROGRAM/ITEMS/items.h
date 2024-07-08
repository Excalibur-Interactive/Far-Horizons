#define GOLD					"gold"

//TEMP
#define BLADE_SABER				"blade_18" // Rebbebion, замена (временная или нет - хз, остальное тоже надо бы проверить)
#define BLADE_LONG				"blade_10"// boal 27.03.2004

#define GUN_COMMON				"pistol1"
#define CHEAP_SPYGLASS			"spyglass1"
#define COMMON_SPYGLASS			"spyglass2"
#define GOOD_SPYGLASS			"spyglass3"
#define SUPERIOR_SPYGLASS		"spyglass4"
#define POTION					"potion1"
#define INVALID_SUIT			"NoSuit" // Warship 25.10.08

// items group id
#define GUN_ITEM_TYPE			"gun"
#define BLADE_ITEM_TYPE			"blade"
#define SPYGLASS_ITEM_TYPE		"spyglass"
#define CIRASS_ITEM_TYPE		"cirass"
#define SPECIAL_ITEM_TYPE		"special" // уникальные предметы
#define POISON_ITEM_TYPE		"poison" // яды
#define RATPOISON_ITEM_TYPE		"ratpoison" // мышьяк
#define AMMO_ITEM_TYPE		    "ammo" // боеприпасы
#define TALISMAN_ITEM_TYPE		"talisman" // амулеты и талисманы
#define HAT_ITEM_TYPE		    "hat" // головные уборы

// целевые группы
#define TGT_QUEST                 "quest"    // Квестовое оружие
#define TGT_SLAVE                 "Slave"    // Рабы, Креолы
#define TGT_CITIZEN               "Citizen"  // бедные горожане
#define TGT_PIRATE                "Pirate"   // мелкие пираты, контрики, Бандиты в джунглях
#define TGT_INDIAN                "Indian"   // Мискито, Итца, Караибы
#define TGT_ELITE                 "Elite"    // Адмиралы, губернаторы, адепты Лиги, квестовые NPC
#define TGT_SOLDIER               "soldier"  // бюргеры, мелкие торговцы, солдаты
#define TGT_OFFICER               "officer"  // Офицеры, коменданты форта и города, капитаны пиратов, главари бандитов, главари контриков, послушники Лиги, наёмники, богатые горожане, богатые торговцы, Иезуиты (послушники)

// indexes for items` array
#define START_ITEMS				  1025 // mitrokosta начальный размер массива предметов
#define ITEMS_QUANTITY			  350  // не забываем менять номер
#define MAX_BUTTONS               64
#define RANDITEMS_QUANTITY    	  100
#define BUTTON_ACTIVATION_TIME	  1000
#define ITEMS_LAYER				  65549
#define MAX_LOADED_RANDITEMS      10
#define MAX_HANDLED_BOXES 		  25
#define ITEM_PROBABILITY		  0.5
#define OBJECTS_IN_BOX			  9
#define MAPS_IN_ATLAS			  25 // ugeen 21.06.09  -не забываем увеличивать при появлении новых карт 	

#define FencingLight_MinAttack        10.0    // минимальная атака для легих клинков
#define FencingLight_MaxAttack        55.0    // максимальная атака для легих клинков

#define Fencing_MinAttack             15.0    // минимальная атака для средних клинков
#define Fencing_MaxAttack             75.0    // максимальная атака для средних клинков

#define FencingHeavy_MinAttack        20.0   // минимальная атака для тяжелых клинков
#define FencingHeavy_MaxAttack        100.0   // максимальная атака для тяжелых клинков

int GENERATED_ITEMS = 0; // кол-во живых нагенеренных, нужно для ленивой очистки
int TOTAL_ITEMS = 1000; // mitrokosta новая система предметов
object Items[START_ITEMS];
object RandItems[RANDITEMS_QUANTITY];
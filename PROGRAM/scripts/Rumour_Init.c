// README -->
// Rosarak. Пофиксил безобразие с пропажей слухов. Надо следить за каждым числом в каждой строчке!
// Длина стека слухов (55): уникальные + одноразовые + для нищих + небольшой резерв под AddRumorR
// Резерв из пустых элементов нужен, чтобы не исчезали слухи из конца массива при добавлении новых
// <-- README

#define MAX_RUMOURS 55  // длина стека слухов
#include "scripts\Rumour_templates.c"
#include "scripts\Rumour_func.c"
#include "scripts\Rumour_generate.c"
#include "scripts\Rumour_Data.h"

object Rumour[MAX_RUMOURS]; // стек слухов
object RumourParams;        // дерево переменных для шаблонных слухов

int id_counter;

void SetRumourDefaults()// заполняем стек начальными - простыми слухами
{
	int i;
	ref CurrentRumour;
	id_counter = 0;
	
	// СТАРТОВЫЕ ОДНОРАЗОВЫЕ
	/*for(i = 0; i < 31; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID слуха
		CurrentRumour.text = DEFAULT_TEXT[i];// Подгружаем начальные слухи в очередь
		CurrentRumour.state = "1"; // Сколько раз может повторять ся один и тот же слух
		CurrentRumour.tip = "citizen,capitan"; // типаж
		CurrentRumour.rep = "none" // репутация
		CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
		CurrentRumour.actualtime = (DateToInt(40));// Как долго могут ходить слухи = 40 дней
		CurrentRumour.event = "none"; // Действие - нет
		CurrentRumour.next = "none"; // Продолжение - нет
		id_counter++; // счетчик слухов
	}
	
	// НИЩИЕ
	for(i = 31; i < 41; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID слуха
		CurrentRumour.text = POOR_RUMOUR_TEXT[i];// Подгружаем начальные слухи в очередь
		CurrentRumour.state = "5"; // Сколько раз может повторять ся один и тот же слух
		CurrentRumour.tip = "poor"; // типаж
		CurrentRumour.rep = "none" // репутация
		CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
		CurrentRumour.actualtime = (DateToInt(300));// Как долго могут ходить слухи = 300 дней
		CurrentRumour.event = "none"; // Действие - нет
		CurrentRumour.next = "none"; // Продолжение - нет
		id_counter++; // счетчик слухов
	}*/
	
	// ПУСТЫЕ ЯЧЕЙКИ
	for(i = 0; i < 55; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = "";
		CurrentRumour.text = "";
		CurrentRumour.state = "";
		CurrentRumour.tip = "";
		CurrentRumour.rep = "";
		CurrentRumour.starttime = "";
		CurrentRumour.actualtime = "";
		CurrentRumour.event = "none";
		CurrentRumour.next = "none";
	}
}

void RumourInit();
{
	//Log_SetStringToLog("Слухи!");
	trace("Слухи!");
	TemplateLoad();
	SetRumourDefaults();
	// ==> отметка времени для осад homo 05/11/06
	SaveCurrentQuestDateParam("Siege_DailyUpdate");
}

// *******************************************************************
//  СЕКЦИЯ УСТАНОВКИ ПЕРСАМ ЗАДАЧИ ПОСЛЕ ДИАЛОГА
// *******************************************************************

#define ADA_FIGHT			"fight"
#define ADA_GROUP_FIGHT		"group_fight"
#define ADA_KILL			"kill"
#define ADA_GOTO			"goto"
#define ADA_RUNTO			"runto"
#define ADA_FOLLOW			"follow"
#define ADA_ENDQUESTMOVIE	"end_movie"
#define ADA_DISAPPEAR		"disappear"
#define ADA_DIALOG			"dialog"
#define ADA_STARTQUESTMOVIE	"start_quest_movie"

void SetAfterDialog_Task(ref _refCharacter, string taskID, bool expendable)
{
	DeleteAttribute(_refCharacter,"activity.afterDialog_task."+taskID);
	_refCharacter.activity.afterDialog_task.(taskID) = taskID;
	if(expendable)	_refCharacter.activity.afterDialog_task.(taskID).expendable = true;
}
void SetAfterDialog_Task_Num(ref _refCharacter, string taskID, int num, bool expendable)
{
	DeleteAttribute(_refCharacter,"activity.afterDialog_task."+taskID);
	_refCharacter.activity.afterDialog_task.(taskID) = taskID;
	if(expendable)	_refCharacter.activity.afterDialog_task.(taskID).expendable = true;
	_refCharacter.activity.afterDialog_task.(taskID).num = num;
}
void SetAfterDialog_Task_Character(ref _refCharacter, string taskID, string taskCharacterID, bool expendable)
{
	DeleteAttribute(_refCharacter,"activity.afterDialog_task."+taskID);
	_refCharacter.activity.afterDialog_task.(taskID) = taskID;
	if(expendable)	_refCharacter.activity.afterDialog_task.(taskID).expendable = true;
	_refCharacter.activity.afterDialog_task.(taskID).character = taskCharacterID;
}
void SetAfterDialog_Task_Group(ref _refCharacter, string taskID, string group, bool expendable)
{
	DeleteAttribute(_refCharacter,"activity.afterDialog_task."+taskID);
	_refCharacter.activity.afterDialog_task.(taskID) = taskID;
	if(expendable)	_refCharacter.activity.afterDialog_task.(taskID).expendable = true;
	_refCharacter.activity.afterDialog_task.(taskID).group = group;
}
void SetAfterDialog_Task_Point(ref _refCharacter, string taskID, string group, string locator, bool expendable)
{
	DeleteAttribute(_refCharacter,"activity.afterDialog_task."+taskID);
	_refCharacter.activity.afterDialog_task.(taskID) = taskID;
	if(expendable)	_refCharacter.activity.afterDialog_task.(taskID).expendable = true;
	if(group!="")	_refCharacter.activity.afterDialog_task.(taskID).group = group;
	_refCharacter.activity.afterDialog_task.(taskID).locator = locator;
}

void ExecuteAfterDialogTask(ref _refCharacter)
{

}


// *****************************************************************************
// Секция попадания в помеченные локации
// *****************************************************************************
bool SetEnterLocationQuest(string locationID, string ActivityCheckName, bool expendable)
{
	int idx = FindLocation(locationID);
	if(idx==-1) 
	{
		return false;
	}
	if(CheckAttribute(&Locations[idx],"QuestStack."+ActivityCheckName)) 
	{
		return false;
	}
	Locations[idx].QuestStack.(ActivityCheckName) = expendable;
	return true;
}

bool DeleteEnterLocationQuest(string locationID, string ActivityCheckName)
{
	int idx = FindLocation(locationID);
	if(idx==-1) return false;
	DeleteAttribute(&Locations[idx],"QuestStack."+ActivityCheckName);
	aref qsaref; makearef(qsaref,Locations[idx].QuestStack);
	if(GetAttributesNum(qsaref)==0) DeleteAttribute(&Locations[idx],"QuestStack");
	return true;
}

// *****************************************************************************
// Секция обработки попадания в локацию к ативным персонажам
// *****************************************************************************
bool SetActivityCharacter(string idCharacter, string ActivityCheckName, bool expendable)
{
	int idx = GetCharacterIndex(idCharacter);
	if(idx==-1) return false;
	ref chref = GetCharacter(idx);

	if(expendable) chref.Activity.GetIntoLocation.expendable = true;
	if(ActivityCheckName=="")	DeleteAttribute(chref,"Activity.GetIntoLocation");
	else	chref.Activity.GetIntoLocation = ActivityCheckName;
	return true;
}

void ExecuteLocationEntryActivity()
{
	int i;
	int idx = FindLoadedLocation();
	if(idx==-1) return;
	string idLoadedLocation = Locations[idx].id;
	if(CheckAttribute(&Locations[idx],"QuestStack"))
	{
		aref qsaref,tmparef; makearef(qsaref,Locations[idx].QuestStack);
		for(i=0; i<GetAttributesNum(qsaref); i++)
		{
			tmparef = GetAttributeN(qsaref,i);
			CompleteQuestName(GetAttributeName(tmparef), "");
			if(GetAttributeValue(tmparef)!="0")
			{
				DeleteAttribute(tmparef,"");
				i--;
			}
		}
	}
}



// *****************************************************************************
//  Секция обработки активных действий при выходе в другую локацию
// *****************************************************************************
bool SetCharacterActivity_FollowMe(string idCharacter, bool followMe, float minDist)
{
	int idx = GetCharacterIndex(idCharacter);
	if(idx==-1) return false;
	ref chref = GetCharacter(idx);

	if(followMe) chref.Activity.GoForMainCharacter = minDist;
	else DeleteAttribute(chref,"Activity.GoForMainCharacter");
	return true;
}
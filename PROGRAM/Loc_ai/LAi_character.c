//------------------------------------------------------------------------------------------
//Login
//------------------------------------------------------------------------------------------

//Установить время загрузки персонажа
void LAi_SetLoginTime(aref chr, float start, float end)
{
	if(start < 0) start = 0;
	if(start >= 24) start = 23.99999999;
	if(end < 0) end = 0;
	if(end >= 24) end = 23.99999999;
	chr.location.stime = start;
	chr.location.etime = end;
}

//Удалить время загрузки персонажа
void LAi_RemoveLoginTime(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "stime");
	DeleteAttribute(loc, "etime");
}

//Данный персонаж является верующим, и в определённое время находиться в церкви
void LAi_SetFanatic(aref chr, string churchID, string group, string locator, float start, float end)
{
	chr.location.church = churchID;
	chr.location.church.group = group;
	chr.location.church.locator = locator;
	chr.location.church.stime = start;
	chr.location.church.etime = end;
}

//Сделать обычным персонаж
void LAi_RemoveFanatic(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "church");
}

//Запретить перерождение персонажа после убийства
void LAi_NoRebirthEnable(aref chr)
{
	chr.location.norebirth = "1";
}

//Разрешить перерождение персонажа после убийства
void LAi_NoRebirthDisable(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "norebirth");
}

//Перерождение нпс со старым именем
void LAi_RebirthOldName(aref chr)
{
	chr.location.rebirthOldName = true;
}

//Разрешить/запретить персонажу загружаться в захваченную локацию
void LAi_LoginInCaptureTown(aref chr, bool isEnable)
{
	aref loc;
	makearef(loc, chr.location);
	if(isEnable)
	{
		loc.loadcapture = "1";
	}else{
		DeleteAttribute(loc, "loadcapture");
	}
}

//------------------------------------------------------------------------------------------
//Fight, hp
//------------------------------------------------------------------------------------------

//Установить хитпойнты
void LAi_SetHP(aref chr, float cur, float max)
{
	if(max < 1) max = 1;
	if(cur < 0) cur = 0;
	if(cur > max) cur = max;
	chr.chr_ai.hp = cur;
	chr.chr_ai.hp_max = max;
}

//Установить текущии хитпойнты
void LAi_SetCurHP(aref chr, float cur)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	if(cur < 0) cur = 0;
	if(cur > maxHP) cur = maxHP;
	chr.chr_ai.hp = cur;
	if (cur == 0.0 && CheckAttribute(chr, "PGGAi"))
	{
		PGG_CheckDead(chr);
	}
}

//Установить текущии хитпойнты и энергию максимальными
void LAi_SetCurHPMax(aref chr)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	chr.chr_ai.hp = maxHP;

	chr.chr_ai.energy    = LAi_GetCharacterMaxEnergy(chr); // восстановление там, где мах НР
}

//Скорость изменения хп в секунду
void LAi_SetDltHealth(aref chr, float healthPerSec)
{
	//if(healthPerSec < 0) healthPerSec = 0;
	chr.chr_ai.hp_dlt = healthPerSec;
}

//Использовать бутылочку-лечилку
void LAi_UseHealthBottle(aref chr, float healthInBottle)
{
	if(healthInBottle <= 0) return;	
	if(!CheckAttribute(chr, "chr_ai.hp_bottle"))
	{
		chr.chr_ai.hp_bottle = "0";
	}
	chr.chr_ai.hp_bottle = stf(chr.chr_ai.hp_bottle) + healthInBottle;
}
// boal
void LAi_UseHealthBottleSpeed(aref chr, float healthSpeed)
{
	if (healthSpeed <= 0) return;
	
	chr.chr_ai.hp_dlt_bottle = healthSpeed;
}

//navy -->
void LAi_AlcoholSetDrunk(aref chr, float alcoholDegree, float time)
{
	//эффекты не суммируются.
	if (CheckAttribute(chr, "chr_ai.drunk")) return;
	//float energyMax;

	chr.chr_ai.drunk = time;
	//много рома в таверне
	if (alcoholDegree > 70)
	{
		chr.chr_ai.drunk.skill.Fencing 	    = -20;
		chr.chr_ai.drunk.skill.Pistol       = -20;
		//chr.chr_ai.drunk.skill.Fortune      = -20;
		chr.chr_ai.drunk.skill.Sneak        = -20;
		chr.chr_ai.drunk.skill.Speechcraft   = -20;
	}
	else
	{
		//Ром
		if (alcoholDegree > 50)
		{
			//chr.chr_ai.drunk.skill.FencingLight = -10;
			//chr.chr_ai.drunk.skill.FencingHeavy = 10;
		}
		//вино
		else
		{
			//chr.chr_ai.drunk.skill.FencingLight = 10;
			//chr.chr_ai.drunk.skill.FencingHeavy = -10;
		}
		//chr.chr_ai.drunk.skill.Fortune = 5;
		chr.chr_ai.drunk.skill.Pistol = -20;
	}

	//думал бонус к макс энергии сделать, но оно по другому работает :) пока так.. а там видно будет.
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		chr.chr_ai.energy = stf(chr.chr_ai.energy) + 20;
	}
}

void LAi_SetAlcoholNormal(aref chr)
{
	if (CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");

	DeleteAttribute(chr, "chr_ai.drunk");
}
//<--

//Использовать бутылочку-противоядие
void LAi_UseAtidoteBottle(aref chr)
{
	DeleteAttribute(chr, "chr_ai.poison");
	DeleteAttribute(chr, "chr_ai.poisondmg");
	DeleteAttribute(chr, "chr_ai.NoAntidoteTime");
	DeleteAttribute(chr, "chr_ai.DrinkedAntidotes");
}

//Использовать бутылочку-спешл
void LAi_UseSpecialPotion(aref chr, string sSpecial, int iHealthChange, int iTime)
{
	if(CheckAttribute(chr, "SpeciaPotionEffect."+sSpecial))
	{
		if(chr.id == pchar.id) Log_TestInfo("Куда второе одинаковое уберзелье пьешь?!")
		return;
	}
	
	if(sSpecial != "potion6") // Ягуар, Иштаб, Ицамна, Еєкатль, Бонди Кецалькоатль, Тлалок, Лоа, Легба, Уицилопочтли, Миктлантекутли
	{
    	if(!CheckAttribute(chr, "SpeciaPotionEffect.count")) chr.SpeciaPotionEffect.count = 1;
    	else chr.SpeciaPotionEffect.count = sti(chr.SpeciaPotionEffect.count) + 1;
	
    	if(chr.id == pchar.id) Log_TestInfo("Дозировка Уберзелий - "+ chr.SpeciaPotionEffect.count +" из 3");

	
		if(chr.SpeciaPotionEffect.count > 3)
		{
			chr.chr_ai.hp = stf(chr.chr_ai.hp)-50;
			LAi_CheckKillCharacter(chr);
			if (stf(chr.Health.HP) <= 1) LAi_KillCharacter(chr);
		
			if(chr.id == pchar.id) Log_TestInfo("Бухать надо меньше, батенька!");
			return;
		}
    }
	
	if(iTime > 0)
	{
        chr.SpeciaPotionEffect.(sSpecial) = true;
	    
		if(sSpecial == "ishtab") 
		{
			chr.SpeciaPotionEffect.hp_ishtab_old = chr.chr_ai.hp;
			chr.SpeciaPotionEffect.hp_max_ishtab_old = chr.chr_ai.hp_max;
			
			chr.chr_ai.hp = sti(chr.chr_ai.hp)*1.30;
			chr.chr_ai.hp_max = sti(chr.chr_ai.hp_max)*1.30;
		}
		
		if(sSpecial == "itzamna") 
		{
			SetEnergyToCharacter(chr);
		}
		
		if(sSpecial == "mictlantecuhtli") 
		{
			LAi_SetCheckMinHP(chr, 1, false, "");
			chr.chr_ai.hpchecker.mictlan = true;
		}
		// evganat - правка питья зелий
        SetPotionTimerFunctionParam("RemoveSpecialPotionEffectFromChar_"+chr.id+"_"+sSpecial, "RemoveSpecialPotionEffectFromChar", 0, 0, 0, sti(GetTime()+iTime), chr, sSpecial);
		Log_TestInfo("Спец зелье продолжительного действия типа " + sSpecial + " у персонажа "+chr.id+" работает...");
	}
	else
	{
		DoInstantSpecialPotionEffect(chr, sSpecial);
	}
	
	AddCharacterHealth(chr, iHealthChange); //сносим (а может и добавляем) здоровье
}

//Использовать бутылочку-спешл
void DoInstantSpecialPotionEffect(aref chr, string sSpecial)
{
	if(sSpecial == "berserker_potion")
	{
		Log_Info("Использована тинктура Бонди! Сила возросла многократно!");
	    PlaySound("Interface\bottle_use.wav");
		chr.SpeciaPotionEffect.berserker_potion = true;
		DoPotionQuestFunctionDelay(chr.id+"_berserker_potion_disable", "berserker_potion_disable", chr, 12.0);
	}
	Log_TestInfo("Спец зелье мгновенного действия типа " + sSpecial + " у персонажа "+chr.id+" работает...");
}

//Отравлен
bool LAi_IsPoison(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.poison")) return true;
	return false;
}

//Сделать персонажа бессмертным
void LAi_SetImmortal(aref chr, bool isImmortal)
{
	if(isImmortal)
	{
		chr.chr_ai.immortal = "1";
	}
	else
	{
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "immortal");
	}
}

//Узнать отношение персонажа к бессмертию
bool LAi_IsImmortal(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		if(sti(chr.chr_ai.immortal) != 0)
		{
			return true;
		}
	}
	return false;
}


//Получить хп персонажа
float LAi_GetCharacterHP(aref chr)
{
	float curHp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp"))
	{
		curHp = stf(chr.chr_ai.hp);
	}
	float maxHp = LAi_GetCharacterMaxHP(chr);
	if(curHp > maxHp) curHp = maxHp;
	chr.chr_ai.hp = curHp;
	chr.chr_ai.hp_max = maxHp;
	return curHp;
}

//Получить максимальные хп персонажа
float LAi_GetCharacterMaxHP(aref chr)
{
	float max_hp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		max_hp = stf(chr.chr_ai.hp_max);
	}
	if(max_hp < 0.0) max_hp = 0.0;
	
	if(IsCharacterEquippedTalisman(chr, "totem_17"))
	{
		if(!CheckAttribute(chr, "chr_ai.hp_max_back"))
		{
			chr.chr_ai.hp_max_back = max_hp;
			max_hp = max_hp * 1.15; 	
		}
	}
	else
	{
		if(CheckAttribute(chr, "chr_ai.hp_max_back"))
		{
			max_hp = stf(chr.chr_ai.hp_max_back);
			DeleteAttribute(chr, "chr_ai.hp_max_back");
		}
	}
	
	chr.chr_ai.hp_max = max_hp;
	return max_hp;
}

//Получить относительные хп персонажа 0..1
float LAi_GetCharacterRelHP(aref chr)
{
	float hp = LAi_GetCharacterHP(chr);
	float maxhp = LAi_GetCharacterMaxHP(chr);
	if(maxhp <= 0.0) return 0.0;
	if(maxhp > 0.0)
	{
		return hp/maxhp;
	}
	return 0.0;
}

//Получить относительную энергию персонажа 0..1
float LAi_GetCharacterRelEnergy(aref chr)
{
	float energy = 0.0;
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		energy = stf(chr.chr_ai.energy);
		energy = energy / LAi_GetCharacterMaxEnergy(chr); // boal
	}
	return energy;
}
// boal
float LAi_GetCharacterMaxEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		return stf(chr.chr_ai.energyMax);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}

//Установить проверяльщик хп, если их становиться меньше чем, вызвать квест
void LAi_SetCheckMinHP(aref chr, float min, bool immortal, string quest)
{
	if(min < 0.9999999) min = 0.9999999;
	chr.chr_ai.hpchecker = min;
	chr.chr_ai.hpchecker.quest = quest;
	chr.chr_ai.hpchecker.immortal = immortal;
}

//Удалить проверяльщик хп
void LAi_RemoveCheckMinHP(aref chr)
{
	aref chr_ai;
	makearef(chr_ai, chr.chr_ai);
	DeleteAttribute(chr_ai, "hpchecker");	
}

//Убить персонажа
void LAi_KillCharacter(aref chr)
{
	chr.chr_ai.hp = "0";
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		string old = chr.chr_ai.immortal;
		chr.chr_ai.immortal = "0";
		LAi_CheckKillCharacter(chr);
		chr.chr_ai.immortal = old;
	}
	else
	{
		LAi_CheckKillCharacter(chr);
	}
}

//Убит ли персонаж
bool LAi_IsDead(aref chr)
{
	if(CheckAttribute(chr, "id") && chr.id == "0") return true; // boal если фантома нет, то НПС умер
	if(!CheckAttribute(chr, "chr_ai.hp") || stf(chr.chr_ai.hp) < 1.0) return true;
	return false;
}


//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Является ли персонаж управляемым
bool LAi_IsCharacterControl(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_PLAYER) return true;
	}
	return false;
}

//Запретить диалог с персонажем
void LAi_CharacterDisableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "1";
}

//Разрешить диалог с персонажем
void LAi_CharacterEnableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "0";
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnation(aref chr, bool isEnable, bool isUseCurModel)
{
	LAi_CharacterReincarnationEx(chr, isEnable, isUseCurModel, "");
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnationEx(aref chr, bool isEnable, bool isUseCurModel, string locgroup)
{
	if(isEnable)
	{
		if(isUseCurModel)
		{
			chr.chr_ai.reincarnation = "0";
		}else{
			chr.chr_ai.reincarnation = "1";
		}
		if(locgroup == "") locgroup = "goto";
		chr.chr_ai.reincarnation.group = locgroup;
	}else{
		chr.chr_ai = "";
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "reincarnation");
	}	
}

bool LAi_CharacterIsReincarnation(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false) return false;
	return true;
}

bool LAi_CharacterReincarnationMode(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation") == false)
	{
		Trace("LAi_CharacterReincarnationMode -> no field chr.chr_ai.reincarnation");
		return false;
	}
	if(sti(chr.chr_ai.reincarnation) != 0) return true;
	return false;
}

string LAi_CharacterReincarnationGroup(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.reincarnation.group") == false)
	{
		Trace("LAi_CharacterReincarnationGroup -> no field chr.chr_ai.reincarnation");
		return "goto";
	}
	if(chr.chr_ai.reincarnation.group != "") return chr.chr_ai.reincarnation.group;
	return "goto";
}

//eddy. установить установить шаг повышения ранга фантома при реинкарнации.
bool LAi_SetReincarnationRankStep(aref _chr, int _step) 
{
	if(CheckAttribute(_chr, "chr_ai.reincarnation"))
	{
		_chr.chr_ai.reincarnation.step = _step;
		_chr.baseIndex = _chr.index; //теперь все реинкарнированные фантомы будут помнить индекс своего прародителя.
		return true;
	}
	else Trace("LAi_SetReincarnationRankStep -> no field chr.chr_ai.reincarnation");
	return false;
}

//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Проиграть звук
void LAi_CharacterPlaySound(aref chr, string soundname)
{
	SendMessage(chr, "s", soundname);
}

//Переключиться в режим боя и обратно
void LAi_SetFightMode(aref chr, bool isFightMode)
{
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
}
// boal
void LAi_SetFightModeForOfficers(bool isFightMode)
{
    ref chr;
    int j, cn;
    for(j=1; j<4; j++)
    {
        cn = GetOfficersIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        chr = GetCharacter(cn);
	        LAi_type_officer_Init(chr);
	        //LAi_group_UpdateTargets(chr);
            SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
	    }
	}
}

//Заблокировать текущий режим (!!! сбрасывается при смене шаблона !!!)
void LAi_LockFightMode(aref chr, bool isLockFightMode)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", isLockFightMode);
}

//Получить режим боя (вытащена ли сабля)
bool LAi_CheckFightMode(aref chr)
{
	return SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode");
}

//------------------------------------------------------------------------------------------
//Weapons
//------------------------------------------------------------------------------------------


//Получить относительный заряд пистолета
float LAi_GetCharacterRelCharge(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		if(CheckAttribute(chr, "chr_ai.chargeprc"))
		{
			if(sti(chr.chr_ai.chargeprc))
			{
				if(!CheckAttribute(chr, "chr_ai.charge_max")) return 0.0;
				float charge = stf(chr.chr_ai.charge);
				float chargemax = stf(chr.chr_ai.charge_max);
				if(chargemax <= 0) return 0.0;
				if(charge >= chargemax) charge = chargemax;
				charge = charge/chargemax;
				if(charge < 0.0) charge = 0.0;
				if(charge > 1.0) charge = 1.0;
				return charge;
			}else{
				return 1.0;
			}
		}else{
			chr.chr_ai.chargeprc = "1";
		}
	}
	return 0.0;
}

//Получить максимальное количество зарядов пистолета
int LAi_GetCharacterChargeQuant(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge_max"))
	{
		return sti(chr.chr_ai.charge_max);
	}
	return 0;
}

//Получить текущее количество зарядов пистолета
int LAi_GetCharacterChargeCur(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.charge"))
	{
		float charge = stf(chr.chr_ai.charge);
		return MakeInt(charge);
	}
	return 0;
}

//Установить количество зарядов
void LAi_GunSetChargeQuant(aref chr, int quant)
{
	if(quant < 0) quant = 0;
	if(quant > 5) quant = 5;
	chr.chr_ai.charge_max = quant;
	
	int iCharge = iGetPistolChargeNum(chr, quant);
	chr.chr_ai.charge = iCharge;
	
	chr.chr_ai.chargeprc = "1";
}

void LAi_SetCharacterBulletType(ref rChar, string sBullet)
{
	switch(sBullet)
	{
		case "bullet":
			TakeNItems(rChar, sBullet, 30 + rand(20));
		break;
		case "cartridge":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "grapeshot":
			TakeNItems(rChar, sBullet, 10 + rand(5));
		break;
		case "Petard":
			TakeNItems(rChar, sBullet, 10 + rand(10));
		break;
		case "Poison_bomb":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "grenade":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "silver_bullet":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
		case "Silver_cartridge":
			TakeNItems(rChar, sBullet, 5 + rand(5));
		break;
	}
}

// ugeen --> получим тип пуль на одетом огнестрельном оружии
string LAi_GetCharacterBulletType(ref rChar)
{
	string sBulletType = "";	
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	
	if(sGun != "") 
	{
		if(CheckAttribute(rChar,"chr_ai.bullet"))		
		{
			sBulletType 	= rChar.chr_ai.bullet;
		}	
	}			
	return sBulletType;
}

// ugeen --> получим тип пороха на одетом огнестрельном оружии и известном типе пуль
string LAi_GetCharacterGunpowderType(ref rChar)
{
	string sGunpowderType = "";		
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	
	if(sGun != "") 
	{
		if(CheckAttribute(rChar,"chr_ai.gunpowder"))		
		{
			sGunPowderType  = rChar.chr_ai.gunpowder;
		}	
	}			
	return sGunpowderType;
}

string LAi_SetCharacterDefaultBulletType(ref rChar)
{
	string sAttr;
	string sBulletType = "";
	int iNum;
	bool isBulletSet = false;
	aref rType;
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	
	if(sGun != "") 
	{
		ref rItm = ItemsFromID(sGun); 
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);
		for (int i = 0; i < iNum; i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			if(sti(rItm.type.(sAttr).Default) > 0)
			{
				sBulletType = rItm.type.(sAttr).bullet;
				isBulletSet = LAi_SetCharacterUseBullet(rChar, sBulletType);
			}
		}
		if(!isBulletSet) trace("can't set default bullet for character id " + rChar.id);
	}			
	return sBulletType;
}

bool LAi_SetCharacterUseBullet(ref rChar, string sBullet)
{
	string 	sAttr;
	string 	sBulletType = "";
	int 	iNum;
	aref 	rType;
	
	string sGun = GetCharacterEquipByGroup(rChar, GUN_ITEM_TYPE);
	
	if(sGun != "") 
	{
		if(HasSubStr(sGun, "mushket"))
		{
			rChar.bullets.mushket = sBullet;
		}
		else
		{
			rChar.bullets.pistol = sBullet;
		}
		ref rItm = ItemsFromID(sGun); 
		makearef(rType, rItm.type);
		iNum = GetAttributesNum(rType);		
		for (int i = 0; i < iNum; i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBulletType = rItm.type.(sAttr).bullet;
			if(sBulletType == sBullet)
			{
				rChar.chr_ai.sGun			= sGun;
				rChar.chr_ai.bulletType		= sAttr;
				rChar.chr_ai.bulletNum 		= iNum;
				rChar.chr_ai.bullet 		= sBulletType;
				rChar.chr_ai.gunpowder		= rItm.type.(sAttr).gunpowder;
				rChar.chr_ai.chargespeed	= rItm.type.(sAttr).ChargeSpeed;
				rChar.chr_ai.MultiDmg       = rItm.multidmg;
				
				rItm.ChargeSpeed			= rItm.type.(sAttr).ChargeSpeed;
				
				if(CheckAttribute(rItm,"chargeQ"))										LAi_GunSetChargeQuant(rChar,sti(rItm.chargeQ));
				else																	LAi_GunSetChargeQuant(rChar, 0);						
				if(CheckAttribute(rItm,"chargespeed") && stf(rItm.chargespeed) > 0.0)	LAi_GunSetChargeSpeed(rChar, 1.0/stf(rItm.chargespeed));
				else																	LAi_GunSetChargeSpeed(rChar, 0.0);				
				if(CheckAttribute(rItm,"dmg_min"))										LAi_GunSetDamageMin(rChar,stf(rItm.dmg_min));
				else																	LAi_GunSetDamageMin(rChar, 0.0);				
				if(CheckAttribute(rItm,"dmg_max"))										LAi_GunSetDamageMax(rChar,stf(rItm.dmg_max));
				else																	LAi_GunSetDamageMax(rChar, 0.0);				
				if(CheckAttribute(rItm,"accuracy"))										LAi_GunSetAccuracy(rChar,stf(rItm.accuracy)*0.01);
				else																	LAi_GunSetAccuracy(rChar,0.0);
			
				return true;	
			}
		}
	}
	return false;
}

// Warship. Методы по зарядке пистоля -->
int iGetMinPistolChargeNum(ref rChar) // Чего меньше, пороха или пуль?
{
	string sBulletType = LAi_GetCharacterBulletType(rChar);	 					// узнаем тип пуль
	int iBulletQty = GetCharacterItem(rChar, sBulletType);   					// считаем кол-во пуль
	string sGunPowderType = LAi_GetCharacterGunpowderType(rChar); 				// тип пороха
	if(sGunPowderType != "")
	{
		int iGunPowderQty = GetCharacterItem(rChar, sGunPowderType); 				// кол-во пороха		
		int iChargeQty = func_min(iBulletQty, iGunPowderQty); 						// Узнаем, чего меньше
		return iChargeQty;
	}		
	return iBulletQty;
}

int iGetPistolChargeNum(ref rChar, int iQuant) // Скока можем зарядить
{
	int iChargeQty = iGetMinPistolChargeNum(rChar);

	if(iChargeQty == 0) return 0;
	if(iChargeQty >= iQuant) return iQuant;
	if(iChargeQty < iQuant) return iChargeQty;
}
// <-- Методы по зарядке пистоля

//Разрядить пистлет
void LAi_GunSetUnload(aref chr)
{
	chr.chr_ai.charge = "0";
	chr.chr_ai.chargeprc = "1";
}

//Установить скорость заряда пистолета
void LAi_GunSetChargeSpeed(aref chr, float speed)
{
	if(speed < 0.0) speed = 0.0;
	if(speed > 4.0) speed = 4.0;
	chr.chr_ai.charge_dlt = speed;
}

//Установить минимальный урон от пистолета
void LAi_GunSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmggunmin = min;
}

//Установить максимальный урон от пистолета
void LAi_GunSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmggunmax = max;
}

//Установить вероятность попадания на максимальной дальности стрельбы
void LAi_GunSetAccuracy(aref chr, float accuracy)
{
	if(accuracy < 0.0) accuracy = 0.0;
	if(accuracy > 1.0) accuracy = 1.0;
	chr.chr_ai.accuracy = accuracy;
}

//Установить минимальный урон от сабли
void LAi_BladeSetDamageMin(aref chr, float min)
{
	chr.chr_ai.dmgbldmin = min;
}

//Установить максимальный урон от сабли
void LAi_BladeSetDamageMax(aref chr, float max)
{
	chr.chr_ai.dmgbldmax = max;
}

//Установить вероятность пробивки
void LAi_BladeSetPiercing(aref chr, float piercing)
{
	if(piercing < 0.0) piercing = 0.0;
	if(piercing > 1.0) piercing = 1.0;
	chr.chr_ai.piercing = piercing;
}

//Установить вероятность неблокирования
void LAi_BladeSetBlock(aref chr, float block)
{
	if(block < 0.0) block = 0.0;
	if(block > 1.0) block = 1.0;
	chr.chr_ai.block = block;
}
// тип сабли boal
void LAi_BladeFencingType(aref chr, string FencingType)
{
	chr.chr_ai.FencingType = FencingType;
}

string LAi_GetBladeFencingType(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.FencingType"))
	{
        return chr.chr_ai.FencingType;
    }
    return SKILL_FENCING;
}

void LAi_BladeEnergyType(aref chr, float fEnergyType)
{
	chr.chr_ai.EnergyType = fEnergyType;
}

float LAi_GetBladeEnergyType(aref chr)
{
    if (CheckAttribute(chr, "chr_ai.EnergyType"))
	{
        return stf(chr.chr_ai.EnergyType);
    }
    return 1.0;
}

//------------------------------------------------------------------------------------------
//Internal
//------------------------------------------------------------------------------------------

//Процессируем всех загружекных персонажей
void LAi_AllCharactersUpdate(float dltTime)
{
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			//Персонаж
			aref chr_ai;
			makearef(chr_ai, Characters[idx].chr_ai);
			ref chr = &Characters[idx];
			if(LAi_IsDead(chr)) continue;
			//Востоновление жизни
			float dlthp = LAI_DEFAULT_DLTHP;
			float totaldlthp;
			if(CheckAttribute(chr_ai, "hp_dlt")) dlthp = stf(chr_ai.hp_dlt);
			
			totaldlthp = dlthp*dltTime;
			if(IsCharacterPerkOn(&Characters[idx], "Viking")) totaldlthp = totaldlthp* 1.1;
			
			float hp = stf(chr_ai.hp) + totaldlthp;
				
			float oldhp = hp;
			if(CheckAttribute(chr_ai, "hp_bottle"))
			{
				float bottle = stf(chr_ai.hp_bottle);
				if(bottle > 0)
				{
					//Скорость высасывания из бутылки
					float bottledlthp = LAI_DEFAULT_DLTBLTHP;
					if(CheckAttribute(chr_ai, "hp_dlt_bottle"))
					{
						bottledlthp = stf(chr_ai.hp_dlt_bottle);
					}
					//Количество вытянутых хп за текущий период времени
					bottledlthp = bottledlthp*dltTime;				
					if(bottledlthp > bottle)
					{
						bottledlthp = bottle;
					}
					bottle = bottle - bottledlthp;
					hp = hp + bottledlthp;
					chr_ai.hp_bottle = bottle;
				}
				else
				{
					//Нет больше бутылки
					DeleteAttribute(chr_ai, "hp_bottle");
					DeleteAttribute(chr_ai, "hp_dlt_bottle");//fix
				}
			}
			//Персонаж отравлен
			if(CheckAttribute(chr_ai, "poison"))
			{
				chr_ai.poison = stf(chr_ai.poison) - dltTime;
				
				if(CheckAttribute(chr_ai, "NoAntidotes"))
				{
					chr_ai.NoAntidoteTime = stf(chr_ai.NoAntidoteTime) - dltTime;
					
					chr_ai.NoMixtureTime = stf(chr_ai.NoMixtureTime) - dltTime;
					
					if(stf(chr_ai.NoAntidoteTime) <= 0.0)
			    	{
			    		DeleteAttribute(chr_ai, "NoAntidoteTime");
			        }
					
					if(stf(chr_ai.NoMixtureTime) <= 0.0)
			    	{
			    		DeleteAttribute(chr_ai, "NoMixtureTime");
			        }
				}
					
				if(stf(chr_ai.poison) <= 0.0)
				{
					DeleteAttribute(chr_ai, "poison");
					DeleteAttribute(chr_ai, "poisondmg");
					DeleteAttribute(chr_ai, "NoAntidoteTime");
					DeleteAttribute(chr_ai, "NoMixtureTime");
					DeleteAttribute(chr_ai, "DrinkedAntidotes");
					DeleteAttribute(chr_ai, "DrinkedMixtures");
				}
				else
				{
					hp = hp - dltTime*sti(chr_ai.poisondmg);
					if (!CheckAttribute(chr, "poison.hp") || hp < sti(chr.poison.hp) - 1.0)
					{
						chr.poison.hp = hp;
						SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, sti(chr.chr_ai.hp), sti(chr.chr_ai.hp_max));
					}
				}
			}
			
			//navy --> время действия бутылки
			if(CheckAttribute(chr_ai, "drunk"))
			{
				chr_ai.drunk = sti(chr_ai.drunk) - 1;
				if(sti(chr_ai.drunk) < 1) LAi_SetAlcoholNormal(chr);
			}
			//<--
			if(LAi_IsImmortal(chr))
			{
				if(hp < oldhp) hp = oldhp;
			}
			float maxhp = stf(chr_ai.hp_max);
			if(hp > maxhp)
			{
				hp = maxhp;
				DeleteAttribute(chr_ai, "bottle");
			}
			chr_ai.hp = hp;
			//Проверка квеста на hp
			LAi_ProcessCheckMinHP(chr);
			//Проверка на смерть
			LAi_CheckKillCharacter(chr);
			//Востоновление заряда
			float chargemax = 0.0;
			if(CheckAttribute(chr_ai, "charge_max"))
			{
				chargemax = stf(chr_ai.charge_max);
			}

			if(chargemax > 0.0)
			{
				if(sti(chr_ai.chargeprc))
				{
					// boal 22/07/05 зарядка не в бою. eddy.но если мушкетер, то пофиг
					if (IsCharacterPerkOn(chr, "Musketeer") || !LAi_IsFightMode(chr) || chr.model.animation == "mushketer")
					{
						float charge = stf(chr_ai.charge);
	                    // boal сюда добавть проверку на наличие пуль gun bullet-->
	                    if((iGetMinPistolChargeNum(chr) - charge) > 0) // Warship. Переделка, т.к. появился порох
		                {
							//zagolski. убираем тормоза при зарядке
							if(!CheckAttribute(chr_ai, "charge_pSkill"))
							{
							    //Скорость зарядки
								chr_ai.charge_pSkill = LAi_GunReloadSpeed(chr);
							}

							float dltcharge = stf(chr_ai.charge_pSkill);

							//Подзаряжаем пистолет
							charge = charge + dltcharge*dltTime;
							if(charge >= chargemax)
							{
								charge = chargemax;
								chr_ai.chargeprc = "0";
								DeleteAttribute(chr_ai, "charge_pSkill");

								// boal 24.04.04 озвучка зарядки пистоля -->
								if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
								{
									PlaySound("Reload");
								}
							}
						    chr_ai.charge = charge;
						}
						// boal сюда добавть проверку на наличие пуль gun bullet <--
					} // boal 22/07/05 зарядка не в бою
				}
			}
			else
			{
				chr_ai.charge = "0";
			}

			//Востоновление энергии
			if(CheckAttribute(chr_ai, "energy"))
			{
				float energy = Lai_UpdateEnergyPerDltTime(chr, stf(chr_ai.energy), dltTime);
				if(energy < 0.0)
				{
					energy = 0.0;
				}
				if(energy > LAi_GetCharacterMaxEnergy(chr))   // boal
				{
					energy = LAi_GetCharacterMaxEnergy(chr);
				}
				chr_ai.energy = energy;
			}
		}
	}
}

void LAi_ProcessCheckMinHP(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.hpchecker"))
	{
		float minhp = stf(chr.chr_ai.hpchecker);
		float hp = stf(chr.chr_ai.hp);
		if(hp < minhp)
		{
			if(sti(chr.chr_ai.hpchecker.immortal))
			{
				LAi_SetImmortal(chr, true);
				chr.chr_ai.hp = minhp;
			}
			if(chr.chr_ai.hpchecker.quest != "")
			{
				LAi_QuestDelay(chr.chr_ai.hpchecker.quest, 0.0);
			}
			
			if(CheckAttribute(chr, "chr_ai.hpchecker.mictlan"));
			{
				DeleteAttribute(chr,"SpeciaPotionEffect.mictlantecuhtli");
	
				if(CheckAttribute(chr, "SpeciaPotionEffect.count") && chr.SpeciaPotionEffect.count > 0) chr.SpeciaPotionEffect.count = sti(chr.SpeciaPotionEffect.count) - 1;
				else DeleteAttribute(chr, "SpeciaPotionEffect.count");

				if(chr.id == pchar.id) Log_TestInfo("Дозировка Уберзелий - "+ chr.SpeciaPotionEffect.count +" из 3");
				
				if(CheckAttribute(chr, "chr_ai.poison"))
				{
					DeleteAttribute(chr, "chr_ai.poison");
					DeleteAttribute(chr, "chr_ai.poisondmg");
					DeleteAttribute(chr, "chr_ai.NoAntidoteTime");
					DeleteAttribute(chr, "chr_ai.NoMixtureTime");
					DeleteAttribute(chr, "chr_ai.DrinkedAntidotes");
					DeleteAttribute(chr, "chr_ai.DrinkedMixtures");
				}
	
				LAi_SetCurHPMax(chr);
			}
			LAi_RemoveCheckMinHP(chr);
		}
	}
}

void LAi_CharacterSaveAy(aref chr)
{
	float ay = 0.0;
	if(GetCharacterAy(chr, &ay) == false) ay = 0.0;
	chr.chr_ai.type.ay = ay;	
}

void LAi_CharacterRestoreAy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.type.ay"))
	{
		float ay = stf(chr.chr_ai.type.ay);
		aref type;
		makearef(type, chr.chr_ai.type);
		DeleteAttribute(type, "ay");
		CharacterTurnAy(chr, ay);
	}
}

void RemoveSpecialPotionEffectFromChar(string qName)
{
	//PChar.quest.(qName).character                   = _chr.id;
    //PChar.quest.(qName).effect                      = _effect;
	
	ref chr = CharacterFromID(PChar.quest.(qName).character);
	if(CheckAttribute(chr, "SpeciaPotionEffect." + PChar.quest.(qName).effect))
	{
		DeleteAttribute(chr,"SpeciaPotionEffect." + PChar.quest.(qName).effect);
		Log_TestInfo("Эффект зелья "+PChar.quest.(qName).effect+" у персонажа "+PChar.quest.(qName).character+" выветрился!");
		
		if(PChar.quest.(qName).effect == "ishtab") 
		{
			
			chr.chr_ai.hp = chr.SpeciaPotionEffect.hp_ishtab_old;
			chr.chr_ai.hp_max = chr.SpeciaPotionEffect.hp_max_ishtab_old;
			DeleteAttribute(chr, "SpeciaPotionEffect.hp_ishtab_old")
			DeleteAttribute(chr, "SpeciaPotionEffect.hp_max_ishtab_old")
		}
		
		if(CheckAttribute(chr, "SpeciaPotionEffect.count") && chr.SpeciaPotionEffect.count > 0) chr.SpeciaPotionEffect.count = sti(chr.SpeciaPotionEffect.count) - 1;
	    else DeleteAttribute(chr, "SpeciaPotionEffect.count");
	}
	else
	{
		Log_TestInfo("Эффект зелья "+PChar.quest.(qName).effect+" у персонажа "+PChar.quest.(qName).character+" выветрился еще до этого!");
	}
	if(chr.id == pchar.id) Log_TestInfo("Дозировка Уберзелий - "+ chr.SpeciaPotionEffect.count +" из 3");
}

void berserker_potion_disable(string qName)
{
	ref chr = CharacterFromID(pchar.PostEventQuest.questDelay.(qName).character);
	
	DeleteAttribute(chr, "SpeciaPotionEffect.berserker_potion");
	chr.BerserkerPotionPenalty = true;
	
	if(CheckAttribute(chr, "SpeciaPotionEffect.count") && chr.SpeciaPotionEffect.count > 0) chr.SpeciaPotionEffect.count = sti(chr.SpeciaPotionEffect.count) - 1;
	else DeleteAttribute(chr, "SpeciaPotionEffect.count");
	
	if(chr.id == pchar.id)
	{
	    Log_TestInfo("Тинктура сдохла! Урон снова нормальный!");
    	Log_TestInfo("Дозировка Уберзелий - "+ chr.SpeciaPotionEffect.count +" из 3");
	}
	
	DoPotionQuestFunctionDelay(chr.id+"_berserker_potion_enable", "berserker_potion_enable", chr, 60.0);
}

void berserker_potion_enable(string qName)
{
	ref chr = CharacterFromID(pchar.PostEventQuest.questDelay.(qName).character);
	DeleteAttribute(chr, "BerserkerPotionPenalty");
}

void RemovePoisonEffectFromCharBlade(string qName)
{	
    ref itm = ItemsFromID(PChar.quest.(qName).blade);
	
	ref chr = CharacterFromID(PChar.quest.(qName).character);
	
	if(chr.id == pchar.id) Log_TestInfo("Действие яда " +itm.isPoisoned.poison+ " закончилось");
	DeleteAttribute(itm, "isPoisoned");
}

void RemoveRatPoisonEffectFromCharacter(string qName)
{
	ref chr = CharacterFromID(PChar.quest.(qName).character);
	
	Log_TestInfo("Действие мышьяка у " +chr.id+ " закончилось");
	DeleteAttribute(chr, "questTemp.arsenic");
}

void RemoveCityFearAttribute(string qName)
{
	Log_TestInfo("Время запугивания стражи в городе" + PChar.quest.(qName).city + " закончилось!");
	DeleteAttribute(pchar, "questTemp.Fear."+ PChar.quest.(qName).city);
}
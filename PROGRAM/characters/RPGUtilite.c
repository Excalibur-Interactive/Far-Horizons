// 11.08.05 Boal Модуль для новой РПГ системы S.P.E.C.I.A.L
// метод для совместимости с .ИНИ файлом (секция SKILLCHANGER)

// порог ранга
int GetCharacterRankRate(ref _refCharacter)
{
    return 35 - GetCharacterSPECIALSimple(_refCharacter, SPECIAL_I);
}
int GetCharacterRankRateCur(ref _refCharacter)
{
    if(!CheckAttribute(_refCharacter, "rank_exp"))
	{
		_refCharacter.rank_exp = 0;
	}
    return sti(_refCharacter.rank_exp);
}
// прирост НР
int GetCharacterAddHPValue(ref _refCharacter)
{
    int ret = makeint(2 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E) * 0.55 + 0.5);

	if (CheckCharacterPerk(_refCharacter, "StrengthOfSpirit"))
	{
		ret = ret + 1;
	}
	return ret;
}

int GetCharacterBaseHPValue(ref _refCharacter)
{
	int ret = makeint(30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_S)*GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E)*0.5);
	return ret;
}

float GetCharacterMaxEnergyValue(ref _refCharacter)
{
    float ret = (30.0 + GetCharacterSPECIAL(_refCharacter, SPECIAL_A)*10);
	if (CheckAttribute(_refCharacter, "PerkValue.Tireless"))
	{
  		ret = ret + stf(_refCharacter.PerkValue.Tireless);
	}
	
	if(CheckAttribute(_refCharacter, "SpeciaPotionEffect.itzamma"))
	{
		ret = ret * 1.15;
	}
	
	ret = ret * makeint(isEquippedTalismanUse(_refCharacter, "totem_16", 1, 1.15));
	
	return ret;
}

float GetCharacterMaxEnergyABSValue(ref _refCharacter)
{
    // проверки перков to_do
	float ret = (30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_A)*10);
	if (CheckAttribute(_refCharacter, "PerkValue.Tireless"))
	{
  		ret = ret + stf(_refCharacter.PerkValue.Tireless);
	}
	
	if(CheckAttribute(_refCharacter, "SpeciaPotionEffect.itzamma"))
	{
		ret = ret * 1.15;
	}
	
	ret = ret * makeint(isEquippedTalismanUse(_refCharacter, "totem_16", 1, 1.15));
	
	return ret;
}

void SetEnergyToCharacter(ref _refCharacter)
{
	_refCharacter.chr_ai.energyMax = GetCharacterMaxEnergyValue(_refCharacter);
	if (!CheckAttribute(_refCharacter, "chr_ai.energy"))
	{
		_refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	}
	else
	{
	    if (sti(_refCharacter.chr_ai.energy) > sti(_refCharacter.chr_ai.energyMax))
	    {
	        _refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	    }
	}
}

int GetCharacterMaxOfficersQty(ref _refCharacter)
{
    return GetCharacterSPECIAL(_refCharacter, SPECIAL_C)*2;
}

int AddCharacterExp(ref _refCharacter,int _exp)
{
	int retVal = false;
	// boal now use AddCharacterExpToSkill

	return retVal;
}

int CalculateExperienceFromRank(int _Rank)
{
	if(_Rank<2) return 0;
	int retVal = 100;//(MakeInt(1000 * pow(_Rank-1,2.3))/1000)*1000;
	return retVal;
}

int GetFreePoints_SelfRate(ref _chref)
{
    return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}

int GetFreePoints_ShipRate(ref _chref)
{
    return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}
/////////////////////////////////////////////////////////////////////////

void SetSelfSkill(ref _refCharacter, int _fl, int _f, int _fh, int _p, int _fr)
{
    _refCharacter.Skill.FencingLight  = _fl;
    _refCharacter.Skill.Fencing       = _f;
    _refCharacter.Skill.FencingHeavy  = _fh;
    _refCharacter.Skill.Pistol        = _p;
    _refCharacter.Skill.Fortune       = _fr;
}

void SetShipSkill(ref _refCharacter, int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn)
{
    _refCharacter.Skill.Leadership = _ld;
    _refCharacter.Skill.Commerce   = _cr;
    _refCharacter.Skill.Accuracy   = _ac;
    _refCharacter.Skill.Cannons    = _cn;
    _refCharacter.Skill.Sailing    = _sl;
    _refCharacter.Skill.Repair     = _re;
    _refCharacter.Skill.Grappling  = _gr;
    _refCharacter.Skill.Defence    = _de;
    _refCharacter.Skill.Sneak      = _sn;
}

void SetSPECIAL(ref _refCharacter, int _s, int _p, int _e, int _c, int _i, int _a, int _l)
{
    _refCharacter.SPECIAL.Strength   = _s;
    _refCharacter.SPECIAL.Perception = _p;
    _refCharacter.SPECIAL.Endurance  = _e;
    _refCharacter.SPECIAL.Charisma   = _c;
    _refCharacter.SPECIAL.Intellect  = _i;
    _refCharacter.SPECIAL.Agility    = _a;
    _refCharacter.SPECIAL.Luck       = _l;
}

void SetRandSPECIAL(ref _refCharacter)
{
    SetSPECIAL(_refCharacter,
               (3 + rand(7)),
               (3 + rand(7)),
               (3 + rand(7)),
               (2 + rand(8)),
               (4 + rand(6)),
               (4 + rand(6)),
               (2 + rand(8)));
}

// Rebbebion, новая функция установки PIRATES
void SetPIRATES(ref sld, int P, int I, int R, int A, int T, int E, int S)
{
	SetSPECIAL(sld, P, I, E, A, T, R, S);
}

// Rebbebion, новые функции для установки личных и корабельных умений соответственно. Ну что за фигня, блин, зачем в функцию распределения КОРАБЕЛЬНЫХ умений вносить СКРЫТНОСТЬ и АВТОРИТЕТ?? Да ещё и вразнобой... Переделываем...
void SetPersonalSkills(ref sld, int ld, int fl, int fs, int fh, int p, int fr, int sn)
{
	sld.Skill.Leadership = ld;
	sld.Skill.FencingL   = fl;
	sld.Skill.FencingS   = fs;
	sld.Skill.FencingH   = fh;
	sld.Skill.Pistol     = p;
	sld.Skill.Fortune    = fr;
    sld.Skill.Sneak      = sn;
}

void SetShipSkills(ref sld, int sl, int ac, int cn, int gr, int de, int re, int cr)
{
	sld.Skill.Sailing    = sl;
	sld.Skill.Accuracy   = ac;
	sld.Skill.Cannons    = cn;
	sld.Skill.Grappling  = gr;
	sld.Skill.Defence    = de;
	sld.Skill.Repair     = re;
    sld.Skill.Commerce   = cr;
}

/// влияет только на СПЕЦИАЛ
int ApplayNavyPenalty(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//пусть будет для компаньонов тоже sti(_refCharacter.index) == GetMainCharacterIndex()) // только для главного, чтоб не тормозить всю игру
    {
        int sailSkill;
        // общее умение навигации
        sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);
        
        int shipClass = GetCharacterShipClass(_refCharacter);
        int needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = makeint((needSkill - sailSkill)/10.0 + 0.9); // округление до мах всегда
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return  sumSkill;
}
// пенальти в скилы
int ApplayNavyPenaltyToSkill(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//пусть будет для компаньонов тоже sti(_refCharacter.index) == GetMainCharacterIndex()) // только для главного, чтоб не тормозить всю игру
    {
        int sailSkill;
		
        // общее умение навигации
        sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);

        int shipClass = GetCharacterShipClass(_refCharacter);
        int needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = needSkill - sailSkill;
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return  sumSkill;
}
// с пенальти и вещами +1
int GetCharacterSPECIAL(ref _refCharacter, string skillName)
{
    int skillN;

	skillN = GetCharacterSPECIALSimple(_refCharacter, skillName);

 	skillN = ApplayNavyPenalty(_refCharacter, skillName, skillN);

    return skillN;
}

int GetCharacterSPECIALSimple(ref _refCharacter, string skillName)
{
	if (!CheckAttribute(_refCharacter,"SPECIAL."+skillName) )
    {
        return 3;
    }
	int skillN = sti(_refCharacter.SPECIAL.(skillName));
    // Health
    if (sti(_refCharacter.index) == GetMainCharacterIndex() && MOD_SKILL_ENEMY_RATE > 1) // не халява
    {
		if(CheckCharacterPerk(_refCharacter, "RoyalHealth")) skillN = skillN + ((GetHealthNum(_refCharacter) - 6) * 0.5); // max -5
		else skillN = skillN + GetHealthNum(_refCharacter) - 6; // max -5
    }
	
	if(!CheckCharacterPerk(_refCharacter, "Paladin"))
	{
		skillN += ApplySPECIALCirassPenalty(_refCharacter, skillName);
    }
	skillN += ApplySpecialPotionSPECIAL(_refCharacter, skillName);
	
    // boal учет вещей -->
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SPECIAL_MAX ) skillN = SPECIAL_MAX;

	return skillN;
}


void InitRPGType()
{
    NullCharacter.SPECIALType.Strength = true;
    NullCharacter.SPECIALType.Perception = true;
    NullCharacter.SPECIALType.Endurance = true;
    NullCharacter.SPECIALType.Charisma = true;
    NullCharacter.SPECIALType.Intellect = true;
    NullCharacter.SPECIALType.Agility = true;
    NullCharacter.SPECIALType.Luck = true;
    
    NullCharacter.SelfType.Leadership = true;
	NullCharacter.SelfType.FencingLight = true;
    NullCharacter.SelfType.Fencing = true;
    NullCharacter.SelfType.FencingHeavy = true;
    NullCharacter.SelfType.Pistol = true;
    NullCharacter.SelfType.Fortune = true;
    NullCharacter.SelfType.Sneak = true;
    // остальные корабельные
    NullCharacter.ShipType.Commerce = true;
    NullCharacter.ShipType.Accuracy = true;
    NullCharacter.ShipType.Cannons = true;
    NullCharacter.ShipType.Sailing = true;
    NullCharacter.ShipType.Repair = true;
    NullCharacter.ShipType.Grappling = true;
    NullCharacter.ShipType.Defence = true;

}

bool isSPECIALTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SPECIALType." + _param);
}

bool isShipTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "ShipType." + _param);
}

bool isSelfTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SelfType." + _param);
}

string GetRPGText(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("RPGDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

string GetSkillNameByIdx(int idx)
{
    string ret = "";
    
    switch (idx)
    {
        case 1:    ret = SKILL_F_LIGHT;   break;
        case 2:    ret = SKILL_FENCING;   break;
        case 3:    ret = SKILL_F_HEAVY;   break;
        case 4:    ret = SKILL_PISTOL;    break;
        case 5:    ret = SKILL_FORTUNE;   break;
        
        case 6:    ret = SKILL_LEADERSHIP; break;
        case 7:    ret = SKILL_COMMERCE;   break;
        case 8:    ret = SKILL_ACCURACY;   break;
        case 9:    ret = SKILL_CANNONS;    break;
        case 10:   ret = SKILL_SAILING;    break;
        case 11:   ret = SKILL_REPAIR;     break;
        case 12:   ret = SKILL_GRAPPLING;  break;
        case 13:   ret = SKILL_DEFENCE;    break;
        case 14:   ret = SKILL_SNEAK;      break;
        
        case 15:   ret = SPECIAL_S;   break;
        case 16:   ret = SPECIAL_P;   break;
        case 17:   ret = SPECIAL_A;   break;
        case 18:   ret = SPECIAL_C;   break;
        case 19:   ret = SPECIAL_I;   break;
        case 20:   ret = SPECIAL_E;   break;
        case 21:   ret = SPECIAL_L;   break;
    }
    return ret;
}
//  _type   ShipType SelfType  SPECIALType
string GetSkillNameByTRIdx(string _type, int idx)
{
    string ret = "";

	switch (_type)
	{
		case "SelfType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_LEADERSHIP; break;
				case 2:    ret = SKILL_F_LIGHT;   break;
		        case 3:    ret = SKILL_FENCING;   break;
		        case 4:    ret = SKILL_F_HEAVY;   break;
		        case 5:    ret = SKILL_PISTOL;    break;
		        case 6:    ret = SKILL_FORTUNE;   break;
                case 7:    ret = SKILL_SNEAK;      break;
		    }
		break;
		
		case "ShipType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_SAILING; break;
				case 2:    ret = SKILL_ACCURACY;   break;
		        case 3:    ret = SKILL_CANNONS;   break;
		        case 4:    ret = SKILL_GRAPPLING;   break;
		        case 5:    ret = SKILL_DEFENCE;    break;
		        case 6:    ret = SKILL_REPAIR;   break;
                case 7:    ret = SKILL_COMMERCE;      break;
		    }
		break;
		
		case "SPECIALType" :
		    switch (idx)
		    {
                case 1:   ret = SPECIAL_S;   break;
		        case 2:   ret = SPECIAL_P;   break;
		        case 3:   ret = SPECIAL_A;   break;
		        case 4:   ret = SPECIAL_C;   break;
		        case 5:   ret = SPECIAL_I;   break;
		        case 6:   ret = SPECIAL_E;   break;
		        case 7:   ret = SPECIAL_L;   break;
		    }
		break;
    }
    return ret;
}
// по имени скила вернуть значение
int GetSkillValue(ref _refCharacter, string _type, string _skillName)
{
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        return sti(_refCharacter.(_type).(_skillName));
    }
    return 0;
}

float GetSkillValueExp(ref _refCharacter, string _skillName)
{
    string skillName_exp = _skillName + "_exp";
    if (!CheckAttribute(_refCharacter, "Skill."+skillName_exp))
	{
		_refCharacter.Skill.(skillName_exp) = 0;
	}
    return stf(_refCharacter.Skill.(skillName_exp));
}
int AddSPECIALValue(ref _refCharacter, string _skillName, int _add)
{
    string _type = SPECIAL_TYPE;
    
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        _refCharacter.(_type).(_skillName) = sti(_refCharacter.(_type).(_skillName)) + _add;
    }
    else
    {
        _refCharacter.(_type).(_skillName) = _add;
    }
    if (sti(_refCharacter.(_type).(_skillName)) < 1) {_refCharacter.(_type).(_skillName) = 1;}
    if (sti(_refCharacter.(_type).(_skillName)) > SPECIAL_MAX) {_refCharacter.(_type).(_skillName) = SPECIAL_MAX;}
    
    return sti(_refCharacter.(_type).(_skillName));
}

int AddCharacterSkill(ref _chref, string _skill, int _addValue)
{
    string  _skill_exp = _skill + "_exp";

    if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	}
    _chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	_chref.skill.(_skill_exp) = 0;
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
	return sti(_chref.skill.(_skill));
}

void AddCharacterSkillDontClearExp(ref _chref, string _skill, int _addValue)
{
	_chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
}

void ApplayNewSkill(ref _chref, string _skill, int _addValue)
{
    // трем кэш
    CheckAttribute(_chref, "BakSkill." + _skill);
    
	// boal 05.05.04 разделение по группам -->
    if (isSelfTypeSkill(_skill))
    {
       if(CheckAttribute(_chref,"perks.FreePoints_self_exp"))
       {
           _chref.perks.FreePoints_self_exp = sti(_chref.perks.FreePoints_self_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_self_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_self_exp) >= GetFreePoints_SelfRate(_chref))
       {
           _chref.perks.FreePoints_self_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_self"))
           {
               _chref.perks.FreePoints_self = sti(_chref.perks.FreePoints_self) + 1;
           }
           else
           {	_chref.perks.FreePoints_self = 1;
           }
           if (sti(_chref.index) == GetMainCharacterIndex())
           {
               Log_SetStringToLog(XI_ConvertString("Personal abilities") + " + 1");
           }
       }
    }
    else
    {
       if(CheckAttribute(_chref,"perks.FreePoints_ship_exp"))
       {
           _chref.perks.FreePoints_ship_exp = sti(_chref.perks.FreePoints_ship_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_ship_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_ship_exp) >= GetFreePoints_ShipRate(_chref))
       {
           _chref.perks.FreePoints_ship_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_ship"))
           {
               _chref.perks.FreePoints_ship = sti(_chref.perks.FreePoints_ship) + 1;
           }
           else
           {	_chref.perks.FreePoints_ship = 1;
           }
           if (sti(_chref.index) == GetMainCharacterIndex())
           {
               Log_SetStringToLog(XI_ConvertString("Ship abilities") + " + 1");
           }
       }
    }
    // boal 05.05.04 разделение по группам <--


    if(!CheckAttribute(_chref, "rank_exp"))
    {
      _chref.rank_exp = 0;
    }
    _chref.rank_exp = sti(_chref.rank_exp) + _addValue;

    if (sti(_chref.rank_exp) >= GetCharacterRankRate(_chref)) // use classic mode - 2 skill = 1 rank
    {
        _chref.rank_exp = 0;
        _chref.rank = sti(_chref.rank) + 1;
        float mhp = LAi_GetCharacterMaxHP(_chref) + GetCharacterAddHPValue(_chref);
        LAi_SetHP(_chref,mhp,mhp);

        if (CheckCharacterPerk(_chref, "Tireless"))
		{
		    if (!CheckAttribute(_chref, "PerkValue.Tireless"))
			{
		  		_chref.PerkValue.Tireless = 0;
			}
			_chref.PerkValue.Tireless = sti(_chref.PerkValue.Tireless) + 1;
			SetEnergyToCharacter(_chref);
		}

        // сообщение в лог
        if(IsOfficer(_chref) || IsCompanion(_chref))
        {
            AddMsgToCharacter(_chref,MSGICON_LEVELUP);
            Log_SetStringToLog(XI_ConvertString("Level Up"));
            PlayStereoSound("interface\new_level.wav");
        }
    }
}
// по специал распередить скилы
void InitStartParam(ref _chref)
{
    int i;
    string  skillName;
    
    ClearCharacterExpRate(_chref);
    
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        _chref.skill.(skillName) = makeint(MOD_EXP_RATE / GetCharacterExpRate(_chref, skillName) + 0.5);
    }
    LAi_SetHP(_chref, GetCharacterBaseHPValue(_chref), GetCharacterBaseHPValue(_chref));
}
// порог следующего скила (множетель)
float GetCharacterExpRate(ref _chref, string _skill)
{
    string  skill_rate = _skill + "_rate";

    if (!CheckAttribute(_chref, "skill." + skill_rate))
    {
        float  divBy = 1.0;

        switch (_skill)
        {
            case SKILL_F_LIGHT:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_P)*0.1;
            break;
            case SKILL_FENCING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_A)*0.4;
            break;
            case SKILL_F_HEAVY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.1;
            break;
            case SKILL_PISTOL:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
            case SKILL_FORTUNE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_L);
            break;
            
            case SKILL_LEADERSHIP:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.1 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.9;
            break;
            case SKILL_COMMERCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.2;
            break;
            case SKILL_ACCURACY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.2;
            break;
            case SKILL_CANNONS:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_S)*0.4;
            break;
            case SKILL_SAILING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8;
            break;
            case SKILL_REPAIR:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.8;
            break;
            case SKILL_GRAPPLING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.7 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.3;
            break;
            case SKILL_DEFENCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_C)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.5;
            break;
            case SKILL_SNEAK:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
        }
        _chref.skill.(skill_rate) = makefloat(MOD_EXP_RATE / divBy);
    }
    return  stf(_chref.skill.(skill_rate));
}

// table service
// table service
string GetReputationName(int reputation)
{
    if(reputation<11)
        return "REPUTATIONT_BAD_4";
    if(reputation<21)
        return "REPUTATIONT_BAD_3";
    if(reputation<31)
        return "REPUTATIONT_BAD_2";
    if(reputation<41)
        return "REPUTATIONT_BAD_1";
    if(reputation<51)
        return "REPUTATIONT_NEUTRAL";
    if(reputation<61)
        return "REPUTATIONT_GOOD_1";
    if(reputation<71)
        return "REPUTATIONT_GOOD_2";
    if(reputation<81)
        return "REPUTATIONT_GOOD_3";
    if(reputation<=90)
        return "REPUTATIONT_GOOD_4";

	return "REPUTATIONT_GOOD_4";
}
// to_do  del
string GetFameName(int fame)
{
   return "TO_DO for del";
}

string GetMoraleName(int morale)
{
	if(morale<10)
		return MoraleTable[MORALET_TREACHEROUS];
	if(morale<20)
		return MoraleTable[MORALET_AWFUL];
	if(morale<30)
		return MoraleTable[MORALET_LOW];
	if(morale<40)
		return MoraleTable[MORALET_POOR];
	if(morale<50)
		return MoraleTable[MORALET_NORMAL];
	if(morale<60)
		return MoraleTable[MORALET_ELATED];
	if(morale<70)
		return MoraleTable[MORALET_GOOD];
	if(morale<80)
		return MoraleTable[MORALET_HIGH];
	if(morale<90)
		return MoraleTable[MORALET_EXCELLENT];
	if(morale<=100)
		return MoraleTable[MORALET_HEROIC];
	return "";
}

string GetLoyalityName(int iLoyality)
{
	if(iLoyality<10)
		return LoyalityTable[MORALET_TREACHEROUS];
	if(iLoyality<20)
		return LoyalityTable[MORALET_AWFUL];
	if(iLoyality<30)
		return LoyalityTable[MORALET_LOW];
	if(iLoyality<40)
		return LoyalityTable[MORALET_POOR];
	if(iLoyality<50)
		return LoyalityTable[MORALET_NORMAL];
	if(iLoyality<60)
		return LoyalityTable[MORALET_ELATED];
	if(iLoyality<70)
		return LoyalityTable[MORALET_GOOD];
	if(iLoyality<80)
		return LoyalityTable[MORALET_HIGH];
	if(iLoyality<90)
		return LoyalityTable[MORALET_EXCELLENT];
	if(iLoyality<=100)
		return LoyalityTable[MORALET_HEROIC];
	return "";
}

// boal 15/01/04 учет вещей выношу в спец метод для простоты работы далее -->
int SetCharacterSkillByItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)
{
	int iRetValue = 0;

	if(_skillName == _itemSkillName && GetCharacterItem(_refCharacter, _item) > 0)
	{
		iRetValue = _addValue;
	}

	return iRetValue;
}

float AddMultiplySkillByEquippedItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, float _addValue)
{
	float fRetValue = 1.0;
	
	if(_skillName == _itemSkillName && IsCharacterEquippedTalisman(_refCharacter, _item))
	{
		fRetValue = _addValue;
	}
	
	return fRetValue;
}

int ApplySPECIALCirassPenalty(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return 0;

	switch(sSuit)
	{	
		case "cirass2":
			if(sSkillName == SPECIAL_E)			iValue = -1;
		break;
		
		case "cirass3":
			if(sSkillName == SPECIAL_E)			iValue = -1;
			if(sSkillName == SPECIAL_C)			iValue = +1;
		break;
		
		case "cirass4":
			if(sSkillName == SPECIAL_E)			iValue = -2;
			if(sSkillName == SPECIAL_A)			iValue = -2;
		break;
		
		case "cirass5":
			if(sSkillName == SPECIAL_E)			iValue = -2;
			if(sSkillName == SPECIAL_A)			iValue = -2;
			if(sSkillName == SPECIAL_C)			iValue = +1;
		break;
	}
		
	return iValue;
}

// Warship 25.10.08 Учет одежды
int SetCharacterSkillBySuit(ref rChar, String sSkillName)
{
	int iValue = 0;
	String sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return 0;
	
	switch(sSuit)
	{
		case "suit_1": // Обноски
			if(sSkillName == SKILL_SNEAK)
			{
				iValue = 20;
			}
		break;
		
		case "suit_2": // Одежда торговца
			if(sSkillName == SKILL_COMMERCE)
			{
				iValue = 20;
			}
		break;
		
		case "suit_3": // Платье дворянина
			if(sSkillName == SKILL_LEADERSHIP)
			{
				iValue = 20;
			}
		break;
	}
	
	return iValue;
}

// Jason: зелья мангаросы
int ApplySpecialPotionSPECIAL(ref rChar, String sSkillName) // 280313
{
	int iValue = 0;
	if (CheckAttribute(rChar, "SpeciaPotionEffect"))
	{
		if (CheckAttribute(rChar, "SpeciaPotionEffect.loa"))
		{
			if(sSkillName == SPECIAL_S)			iValue = 2;
			if(sSkillName == SPECIAL_E)			iValue = 2;
		}
		if (CheckAttribute(rChar, "SpeciaPotionEffect.Legba"))
		{
			if(sSkillName == SPECIAL_A)			iValue = 2;
			if(sSkillName == SPECIAL_P)			iValue = 2;
		}
	}
	return iValue;
}

int SetCharacterSkillBySpecialPotion(ref rChar, String sSkillName) // 280313
{
	int iValue = 0;
	if (CheckAttribute(rChar, "SpeciaPotionEffect"))
	{
		if (CheckAttribute(rChar, "SpeciaPotionEffect.loa"))
		{
			if(sSkillName == SKILL_F_HEAVY)		iValue = 15;
			if(sSkillName == SKILL_FENCING)		iValue = 5;
		}
		
		if (CheckAttribute(rChar, "SpeciaPotionEffect.Legba"))
		{
			if(sSkillName == SKILL_F_LIGHT)		iValue = 10;
			if(sSkillName == SKILL_PISTOL)		iValue = 10;
		}
	}
	
	return iValue;
}

// boal 15/01/04 учет вещей выношу в спец метод для простоты работы далее <--
float GetCharacterSkillToOld(ref _refCharacter, string skillName)
{
    return makefloat(GetCharacterSkill(_refCharacter, skillName) / SKILL_TO_OLD);
}

int GetCharacterSkill(ref _refCharacter, string skillName)
{
    int skillN;

    // boal 051104 метод тормозит страшно - проверка +1 вещей, будет опрос раз в 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 20)
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

	skillN = GetCharacterSkillSimple(_refCharacter, skillName);


    // 14.03.05 пенальти от класса корабля -->
 	skillN = ApplayNavyPenaltyToSkill(_refCharacter, skillName, skillN);
	// 14.03.05 пенальти от класса корабля <--

	_refCharacter.BakSkill.(skillName)      =  skillN; // значение
    _refCharacter.BakSkillCount.(skillName) = rand(5); // счетчик немного размажем пересчет

    return skillN;
}

int GetCharacterSkillSimple(ref _refCharacter, string skillName)
{
	if( !CheckAttribute(_refCharacter,"Skill."+skillName) ) return 1;
	int skillN = sti(_refCharacter.Skill.(skillName));

	bool   bHero = (sti(_refCharacter.index) == GetMainCharacterIndex());
	
    // boal учет вещей -->
    if (bHero || CheckAttribute(_refCharacter, "Payment"))
    {
        // Health
        if (bHero && MOD_SKILL_ENEMY_RATE > 1) // не халява
        {
            if (isSelfTypeSkill(skillName))
            {
                if(CheckCharacterPerk(_refCharacter, "RoyalHealth")) skillN = skillN + ((5*(GetHealthNum(_refCharacter) - 6)) * 0.5); // max -5
                else skillN = skillN + 5*(GetHealthNum(_refCharacter) - 6); // max -5
            }
        }
	
		//navy --> действие алкоголя
		if (CheckAttribute(_refCharacter, "chr_ai.drunk.skill." + skillName))
		{
			skillN += sti(_refCharacter.chr_ai.drunk.skill.(skillName));
		}
		//<--
		
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Mineral4", -10);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "Mineral16", -10);
		
		if(GetCharacterItem(_refCharacter, "totem_32"))
		{
			if(skillName == SKILL_FORTUNE) skillN = skillN * 0.5;
			if(skillName == SKILL_LEADERSHIP) skillN = skillN * 0.5;
		}
		
		if(IsEquipCharacterByItem(_refCharacter, "cirass3"))
		{
			if(skillName == SKILL_SNEAK) skillN = skillN * 0.85;
			if(skillName == SKILL_LEADERSHIP) skillN = skillN * 1.15;
		}
		
		if(IsEquipCharacterByItem(_refCharacter, "cirass4"))
		{
			if(skillName == SKILL_SNEAK) skillN = skillN * 0.85;
			if(skillName == SKILL_LEADERSHIP) skillN = skillN * 0.85;
		}
		
		if(IsEquipCharacterByItem(_refCharacter, "cirass5"))
		{
			if(skillName == SKILL_SNEAK) skillN = skillN * 0.85;
			if(skillName == SKILL_LEADERSHIP) skillN = skillN * 1.15;
		}
		
		if(IsEquipCharacterByItem(_refCharacter, "cirass6"))
		{
			if(skillName == SKILL_SNEAK) skillN = skillN * 0.5;
			if(skillName == SKILL_LEADERSHIP) skillN = skillN * 1.5;
		}
		
		if(IsEquipCharacterByItem(_refCharacter, "cirass7"))
		{
			if(skillName == SKILL_SNEAK) skillN = skillN * 1.5;
			if(skillName == SKILL_LEADERSHIP) skillN = skillN * 0.5;
		}
		
		skillN += SetCharacterSkillBySpecialPotion(_refCharacter, skillName);
		
		skillN = makeint(skillN * AddMultiplySkillByEquippedItem(_refCharacter, skillName, SKILL_ACCURACY,  "totem_12", 1.10));
		skillN = makeint(skillN * AddMultiplySkillByEquippedItem(_refCharacter, skillName, SKILL_COMMERCE,  "totem_13", 1.15));
		
		if(IsCharacterEquippedTalisman(_refCharacter, "totem_14"))
		{
			skillN += makeint(SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SAILING, "totem_14", 10));
	    }
		
		skillN = makeint(skillN * AddMultiplySkillByEquippedItem(_refCharacter, skillName, SKILL_FORTUNE,   "totem_15", 1.10));
		skillN = makeint(skillN * AddMultiplySkillByEquippedItem(_refCharacter, skillName, SKILL_LEADERSHIP,"totem_18", 1.15));
		
		if(CheckAttribute(_refCharacter, "SpeciaPotionEffect.Jaguar") && skillName == SKILL_ACCURACY) 
		{
			skillN = skillN * 1.15;
		}
		
		if(CheckAttribute(_refCharacter, "SpeciaPotionEffect.Jaguar") && skillName == SKILL_PISTOL) 
		{
			skillN = skillN * 1.15;
		}
		
    	// boal учет перегруза 19.01.2004 -->
    	if ( GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter) && !IsCharacterEquippedTalisman(_refCharacter, "totem_01"))
    	{
   	        skillN -= 20;
    	}
    	// boal учет перегруза 19.01.2004 <--
	}
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SKILL_MAX ) skillN = SKILL_MAX;

	return skillN;
}
// boal 20.03.2004 -->
int GetShipClassNavySkill(int shipClass)
{
    int needSkill = 0;

    switch (shipClass)
    {
            case 1 : needSkill = 95; break;
            case 2 : needSkill = 80; break;
            case 3 : needSkill = 65; break;
            case 4 : needSkill = 40; break;
            case 5 : needSkill = 25; break;
            case 6 : needSkill = 1; break;
            case 7 : needSkill = 0; break;
    }
    return needSkill;
}
// boal 20.03.2004 <--
void DelBakSkillAttr(ref _refCharacter) // boal оптимизация скилов
{
    DeleteAttribute(_refCharacter, "BakSkill");
    DeleteAttribute(_refCharacter, "BakSkillCount");
}
// сброс всех порогов (буфер расчета, пересчитывается от вещей +1)
void ClearCharacterExpRate(ref _chref)
{
    int    i;
    string name;

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        DeleteAttribute(_chref, "skill." + name + "_rate");
    }
}
// когда меняется порог кача, нужно сбросить очки, иначе будет по 120%
void RefreshCharacterSkillExpRate(ref _chref)
{
    int    i;
    string name;

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        AddCharacterExpToSkill(_chref, name, 0.0);
        ApplayNewSkill(_chref, name, 0); // иначе перки  будут 23/22
    }
}

float GetSummonSkillFromNameToOld(ref _refCharacter, string skillName)
{
    return (GetSummonSkillFromName(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetSummonSkillFromName(ref _refCharacter, string skillName)
{
    int sumSkill;

    // boal 051104 метод тормозит страшно - проверка +1 вещей, будет опрос раз в 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 25 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

    sumSkill = GetSummonSkillFromNameSimple(_refCharacter, skillName);

    // boal 27.01.2004 пенальти за крутой корабль -->
 	sumSkill = ApplayNavyPenaltyToSkill(_refCharacter, skillName, sumSkill);
    // boal 27.01.2004 <--

    _refCharacter.BakSkill.(skillName)      =  sumSkill; // значение
    _refCharacter.BakSkillCount.(skillName) = rand(5); // счетчик немного размажем пересчет

    return sumSkill;
}

int GetSummonSkillFromNameSimple(ref _refCharacter, string skillName)
{
    int sumSkill = GetCharacterSkillSimple(_refCharacter,skillName);

	if (sti(_refCharacter.index) == sti(pchar.index))
	{
	    int iOfficer = -1;
		int iOffSkill = -1;
		switch (skillName)
		{
			case SKILL_SAILING:
				iOfficer = sti(pchar.Fellows.Passengers.navigator);
			break;

			case SKILL_CANNONS:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;

			case SKILL_ACCURACY:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;

			case SKILL_GRAPPLING:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;

			case SKILL_DEFENCE:
				iOfficer = sti(pchar.Fellows.Passengers.doctor);
			break;

			case SKILL_REPAIR:
				iOfficer = sti(pchar.Fellows.Passengers.carpenter);
			break;

			case SKILL_COMMERCE:
				iOfficer = sti(pchar.Fellows.Passengers.treasurer);
			break;
		}

		if(iOfficer != -1)
		{
			iOffSkill = GetCharacterSkillSimple(&characters[iOfficer], skillName);
			if (iOffSkill > sumSkill)
			{
				sumSkill = iOffSkill;
			}
		}
	}
	return sumSkill;
}
// boal -->


void AddCharacterExpToSkillSquadron(ref _refCharacter, string _skill, float _addValue)
{
    int cn,i;
	ref chref;

	for(i=0; i<4; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{    // и квестовым тоже
			AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue);
		}
	}
}
void AddCharacterExpToSkill(ref _chref, string _skill, float _addValue)
// _chref - character _skill - name ex -"Fencing"  _skill_exp = "Fencing_exp"   _addValue = 100
{
    string  _skill_exp = _skill + "_exp";
    if (!CheckAttribute(_chref, "skill." + _skill_exp))
    {
        _chref.skill.(_skill_exp) = 0;
    }
	
    if (bExpLogShow && _addValue > 0)
    {
	   if (IsOfficer(_chref))  Log_Info(_chref.id + " take " + FloatToString(_addValue, 2) + " exp to " + _skill);
    }
    // boal 300804 падение экспы -->
    if (_addValue < 0)
    {
        if(CheckAttribute(_chref, "skill." + _skill_exp))
        {
            _chref.skill.(_skill_exp) = sti(_chref.skill.(_skill_exp)) + _addValue;
            if (sti(_chref.skill.(_skill_exp)) < 0)
            {
                _chref.skill.(_skill_exp) = 0;
            }
        }
        return;
    }
    // boal 300804 падение экспы <--
    if (CheckAttribute(_chref, "skill." + _skill) && sti(_chref.skill.(_skill)) < SKILL_MAX)// && sti(_chref.skill.(_skill)) > 0)
    { // if skill = 0 then it is great loser
        _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) + _addValue;

        while ( makeint(sti(_chref.skill.(_skill)) * GetCharacterExpRate(_chref, _skill)) <= stf(_chref.skill.(_skill_exp))
                && sti(_chref.skill.(_skill)) < SKILL_MAX )
        {
            _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) - makeint(sti(_chref.skill.(_skill)) * GetCharacterExpRate(_chref, _skill));
            AddCharacterSkillDontClearExp(_chref, _skill, 1);
            // оптимизация скилов
            DeleteAttribute(_chref, "BakSkill." + _skill);
            DeleteAttribute(_chref, "BakSkillCount." + _skill);
        }
    }
    /// officers
    if (_addValue > 0 && sti(_chref.index) == GetMainCharacterIndex()) // только для ГГ
    {
		int cn, i, iPas;
		iPas = GetPassengersQuantity(_chref); // оптимиация
		
		for(i=0; i<iPas; i++)
		{
			cn = GetPassenger(_chref,i);
			if(cn!=-1)
			{
			    if (isOfficerInShip(GetCharacter(cn), true))
	  		    {
			        AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 4.0);
			    }
			    else
			    {
			        AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 20.0);
			    }
			}
		}
	    for(i=1; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(_chref,i);
			if(cn!=-1)
			{
				AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue / 6.0);
			}
		}
    }
}

string GetPerkListText(ref _chref, string _type)
{
    int    perksQ,i;
    int    lngFilePerkID = -1;
	string perkName;
	string ret;
	aref   arPerksRoot;

    lngFilePerkID = LanguageOpenFile("AbilityDescribe.txt");
	// Варианты перков, которые можно добавить
	makearef(arPerksRoot, _chref.perks.list);
	perksQ = GetAttributesNum(arPerksRoot);
	ret = "";
	for(i=0; i<perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));

        if (CheckAttribute(&ChrPerksList, "list." + perkName) && CheckAttribute(&ChrPerksList, "list." + perkName + ".BaseType"))
        {
            if (ChrPerksList.list.(perkName).BaseType == _type)
            {
                ret += "* " + LanguageConvertString(lngFilePerkID, perkName) + " ";
            }
        }
	}
	LanguageCloseFile(lngFilePerkID);
	return ret;
}
// boal Вес предметов 19.01.2004 -->
float GetItemsWeight(ref _chref)
{
    float   Amount = 0;
    int     j;
    string  itemID;
    ref     itm;

    if (bCabinStarted || bAbordageStarted || !bSeaActive || !CheckAttribute(_chref, "ItemsWeight"))
    {
        for (j=0; j<TOTAL_ITEMS; j++)
    	{
    		makeref(itm,Items[j]);
			
			if(CheckAttribute(itm, "ID"))
			{
				itemID = itm.id;
				if (CheckAttribute(_chref, "items."+itemID) && itemID != "MapsAtlas")      // ugeen - атлас карт не учитываем !!
				{
					Amount += sti(_chref.items.(itemID))*stf(itm.Weight);
				}
			}
        }
        _chref.ItemsWeight = Amount; // оптимицация тормозов в бою на море
    }
    else
    {
        Amount = stf(_chref.ItemsWeight);
    }
    return Amount;
}

int GetMaxItemsWeight(ref _chref)
{
	if (CheckAttribute(_chref, "Skill.Fencing"))
    {
        int iBonus = 0;
        if (IsCharacterPerkOn(_chref, "Knight")) iBonus = iBonus + 10;
        if (IsCharacterPerkOn(_chref, "Viking")) iBonus = iBonus + 20;
        iBonus = iBonus + CHAR_ITEMS_WEIGHT + GetCharacterSPECIALSimple(_chref, SPECIAL_S)*(GetCharacterSPECIALSimple(_chref, SPECIAL_E) + 12 - MOD_SKILL_ENEMY_RATE);
		if(CheckAttribute(_chref, "SpeciaPotionEffect.eekatl")) iBonus = iBonus * 1.15;
		if(IsCharacterEquippedTalisman(_chref, "totem_01")) iBonus = iBonus + 20;
        return  iBonus;
    }
    else
    {
        return 10000; // сундук или труп не имееют скила и ограничения
    }
}
// boal 19.01.2004 <--

// boal -->
int Statistic_AddValue(ref _chref, string _attrName, int _add) // set and get(_add==0) value
{
    // KillShip_ 1 ..7
    // AbordShip_ 1..7
    // KillAbordShip_ 1..7
    // soldier_s  soldier_g ( s=sword g=gun)
    // Citizen_s  Citizen_g
    // Monster_s Monster_g
    // Warrior_s  Warrior_g
    // Fort
	if(!CheckAttribute(_chref, "index")) return 0;
	
    if (sti(_chref.index) != GetMainCharacterIndex()) return 0; // оптимизация
    
    if( !CheckAttribute(_chref,"Statistic." + _attrName) )
    {
        _chref.Statistic.(_attrName) = 0;
    }
    _chref.Statistic.(_attrName) = sti(_chref.Statistic.(_attrName)) + _add;

    if (sti(_chref.Statistic.(_attrName)) < 0)
    {
        _chref.Statistic.(_attrName) = 0;
    }
    return sti(_chref.Statistic.(_attrName));
}

void Statistic_KillChar(aref _attack, aref _enemy, string _attrName)
{
	if (sti(_attack.index) != GetMainCharacterIndex()) return; // оптимизация
	string  name = GetCharType(_enemy);

	name = name + _attrName;

	Statistic_AddValue(_attack, name, 1);
}

string GetCharType(aref _enemy)  //TO_DO переделать на тип в НПС
{
    string  name  = "Warrior"; // define
    string  model = _enemy.model;
    switch (_enemy.chr_ai.type)
	{
		case LAI_TYPE_PATROL :
		    name = "soldier";
		break
		case LAI_TYPE_GUARDIAN :
		    name = "soldier";
		break
		case LAI_TYPE_OFFICER :
		    name = "soldier";
		break;
        // Citizen
		case LAI_TYPE_ACTOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_BARMAN :
		    name = "Citizen";
		break;
		case LAI_TYPE_CITIZEN :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBER :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBERSTAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_MERCHANT :
		    name = "Citizen";
		break;
		case LAI_TYPE_POOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_PRIEST :
		    name = "Citizen";
		break;
		case LAI_TYPE_SIT :
		    name = "Citizen";
		break;
		case LAI_TYPE_STAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_WAITRESS :
		    name = "Citizen";
		break;
		case LAI_TYPE_OWNER :
		    name = "Citizen";
		break;

		case LAI_TYPE_WARRIOR : // to_do преверить тип
		    if (HasSubstr(model, "Skel"))
		    {
		        name = "Monster";
		    }
		    else
		    {
                if (HasSubstr(model, "off_"))
                {
                    name = "soldier";
                }
                else
                {
                    if (HasSubstr(model, "sold_"))
	                {
	                    name = "soldier";
	                }
                }
		    }
		break;
	}

	return  name;
}
// boal statistic info 17.12.2003 <--

string GetCharFraction(aref _enemy)
{
    if(CheckAttribute(_enemy, "fraction")) return _enemy.fraction;
	
	return F_CITY;
}

// boal Блок здоровье ГГ -->
int GetHealthNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.HP) + 9) / 10.0); // до целого

    return i;
}

int GetHealthMaxNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.maxHP) + 9) / 10.0); // до целого

    return i;
}
string GetHealthName(ref ch)
{
    string name = "";

    switch (GetHealthNum(ch))
    {
        case 1:
            name = "УЖАСНОЕ";
        break;
        case 2:
            name = "ПЛОХОЕ";
        break;
        case 3:
            name = "НЕВАЖНОЕ";
        break;
        case 4:
            name = "СРЕДНЕЕ";
        break;
        case 5:
            name = "ХОРОШЕЕ";
        break;
        case 6:
            name = "ОТЛИЧНОЕ";
        break;
    }
    return name;
}

string GetHealthNameMaxSmall(ref ch)
{
    string name = "";

    switch (GetHealthMaxNum(ch))
    {
        case 1:
            name = "ужасное";
        break;
        case 2:
            name = "плохое";
        break;
        case 3:
            name = "неважное";
        break;
        case 4:
            name = "среднее";
        break;
        case 5:
            name = "хорошее";
        break;
        case 6:
            name = "отличное";
        break;
    }
    return name;
}

void SetNewDayHealth()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.Damg);
    int   add   = 0;

    mainChr.Health.Damg = 0.0;

    if (CheckCharacterPerk(mainChr, "RoyalHealth"))
    {
        add = 1;
    }
	
	if(CheckAttribute(pchar, "SpeciaPotionEffect.quetzalcoatl"))
	{
		add += 1;
	}
	
    if (damg >= (maxhp / 1.5) )
    {
        if ((damg / maxhp) > add)
        {
            if(CheckCharacterPerk(mainChr, "RoyalHealth")) AddCharacterHealth(mainChr, -(damg / maxhp + add)*0.5);
            else AddCharacterHealth(mainChr, -damg / maxhp + add);
        }
    }
    else
    {
        if (!IsEntity(worldMap)) // не на карте
        {
            AddCharacterHealth(mainChr, 1 + add);
        }
        else
        {
            AddCharacterHealth(mainChr, 0.5 + add / 2.0);
        }
    }
}

void SetNewDayHealthMax()
{
    ref mainChr = GetMainCharacter();

    float maxhp = stf(mainChr.chr_ai.hp_max);
    float damg  = stf(mainChr.Health.weekDamg);
	int maxhpmlt = 3.5;

    mainChr.Health.weekDamg = 0.0;
    
	if(CheckAttribute(mainChr, "SpeciaPotionEffect.quetzalcoatl")) maxhpmlt = 3.5 * 1.75;
	
    if (damg > (maxhp * maxhpmlt))
    {
        AddCharacterMaxHealth(mainChr, -1);
    }
}

void AddCharacterHealth(ref mainChr, float add)
{
    float maxhp = stf(mainChr.chr_ai.hp_max);
    int   remHP = GetHealthNum(mainChr);

    mainChr.Health.HP = makefloat(stf(mainChr.Health.HP) + add);

    if (stf(mainChr.Health.HP) < 1)
    {
        mainChr.Health.HP = 1.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }

    if (GetHealthNum(mainChr) > remHP)
    {
        Log_Info("Здоровье стало лучше");
    }

    if (GetHealthNum(mainChr) < remHP)
    {
        Log_Info("Здоровье стало хуже");
    }
}

void AddCharacterMaxHealth(ref mainChr, float add)
{
    mainChr.Health.maxHP = makefloat(stf(mainChr.Health.maxHP) + add);

    if (stf(mainChr.Health.maxHP) < 1)
    {
        mainChr.Health.maxHP = 1.0;
    }

    if (stf(mainChr.Health.maxHP) > 60)
    {
        mainChr.Health.maxHP = 60.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }
}
// boal Блок здоровье ГГ <--

// увеличение счетчика награды за голову -->
int ChangeCharacterHunterScore(ref chref, string _huntName, int incr)
{
	int prevVal = -5; // мин набор

	if (_huntName == "pirhunter") return 0;

	if (CheckAttribute(chref, "reputation." + _huntName) )	prevVal = sti(chref.reputation.(_huntName));

	int newVal = prevVal + incr;
	if (newVal < -100)  newVal = -100;
	if (newVal > 100)   newVal = 100;

	chref.reputation.(_huntName) = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return newVal;

	if (newVal >= 10)
	{
	 	if (prevVal < newVal)
		{
			Log_SetStringToLog(XI_ConvertString(_huntName) + " увеличила награду за Вашу голову");
		}

	    if (prevVal > newVal)
		{
	        Log_SetStringToLog(XI_ConvertString(_huntName) + " снизила награду за Вашу голову");
		}
	}
	else
	{
		int iNation = 0;
		switch (_huntName) // код для совместимости со старым
		{
		    case "enghunter":  iNation = ENGLAND; break;
		    case "frahunter":  iNation = FRANCE; break;
		    case "spahunter":  iNation = SPAIN; break;
		    case "duthunter":  iNation = HOLLAND; break;
		}
		string prevName = GetNationReputationName(iNation, -prevVal);
		string newName  = GetNationReputationName(iNation, -newVal);
		if (prevName!=newName)
		{
			string outString = XI_ConvertString("Your reputation with country")+ XI_ConvertString(Nations[iNation].Name + "Gen") +" ";
			if (incr<0)	{outString+=XI_ConvertString("increase");}
			else	{outString+=XI_ConvertString("decrease");}
			outString += " "+XI_ConvertString("to")+" "+newName;
			Log_SetStringToLog(outString);
		}
	}
	return newVal;
}

int ChangeCharacterNationReputation(ref chref, int _Nation, int incr)
{
	return -ChangeCharacterHunterScore(chref, NationShortName(_Nation) + "hunter", -incr); // все наоборот, - это хорошо, + есть НЗГ
}

string GetNationReputation(ref chref, int _Nation)
{
    return GetNationReputationName(_Nation, ChangeCharacterNationReputation(chref, _Nation, 0));
}

string GetNationReputationName(int _Nation, int i)
{
	if (i <= -10)  return "Награда за голову " + (-i*1000);
    if (i < 0 )    return "Враждебная";
    if (i <= 20 )  return "Нейтральная";
    if (i <= 50 )  return "Хорошая";
    if (i <= 80 )  return "Отличная";
    if (i <= 100 ) return "Восхищение";

    return "Отличная";
}
// boal 04.04.04
string NationShortName(int iNation)
{
    switch(iNation)
	{
		case ENGLAND:
            return "eng";
		break;
		case FRANCE:
            return "fra";
		break;
		case SPAIN:
            return "spa";
		break;
		case HOLLAND:
			return "dut";
		break;
		case PIRATE:
			return "pir";
		break;
	}
	return "eng";
}
// увеличение счетчика награды за голову <--


void setWDMPointXZ(string _location)
{
    // координаты на гловал карте -->
    int n;
	string sTemp;

    n = FindIslandBySeaLocation(_location);
	if(n!=-1)
	{
		worldMap.island = Islands[n].id;
		Pchar.curIslandId = worldMap.island; // fix
		sTemp = worldMap.island;
		if (CheckAttribute(&worldMap, "islands." + sTemp))
		{
		    worldMap.zeroX = worldMap.islands.(sTemp).position.x;
			worldMap.zeroZ = worldMap.islands.(sTemp).position.z;
			if (CheckAttribute(&worldMap, "islands." + sTemp + "." + _location))
			{
			    worldMap.playerShipX = worldMap.islands.(sTemp).(_location).position.x;
				worldMap.playerShipZ = worldMap.islands.(sTemp).(_location).position.z;
				//trace(sTemp + "." + _location);
			}
			else
			{// для бухт с незаданными координатами
			    worldMap.playerShipX = worldMap.zeroX;
				worldMap.playerShipZ = worldMap.zeroZ;
			}
		}
	}
	// координаты на гловал карте <--
}

// нужно не перекрывать еще и признаки фантома
void ChangeAttributesFromCharacter(ref CopyChref, ref PastChref, bool _dialogCopy)
{
    aref arToChar;
    aref arFromChar;

    CopyChref.model            = PastChref.model;
    CopyChref.model.animation  = PastChref.model.animation;
    CopyChref.sex              = CopyChref.sex;
    CopyChref.FaceId           = PastChref.FaceId;
    CopyChref.nation           = PastChref.nation;

	CopyChref.name             = PastChref.name;
    CopyChref.lastname         = PastChref.lastname;

    CopyChref.rank             = PastChref.rank;
    CopyChref.reputation       = makeint(PastChref.reputation);
	
	CopyChref.baseCapIdx       = PastChref.index; //Id оригинального в структуру клона

    if (CheckAttribute(PastChref, "loyality"))
    {
    	CopyChref.loyality         = PastChref.loyality;
	}
	else DeleteAttribute(CopyChref, "loyality");
	if (CheckAttribute(PastChref, "alignment"))
	{
    	CopyChref.alignment        = PastChref.alignment;
    }
    else DeleteAttribute(CopyChref, "alignment");

    CopyChref.Money            = PastChref.Money;

    CopyChref.chr_ai.hp         = makeint(PastChref.chr_ai.hp);
    CopyChref.chr.chr_ai.hp_max = makeint(PastChref.chr_ai.hp_max);

    LAi_SetHP(CopyChref, makeint(PastChref.chr_ai.hp_max), makeint(PastChref.chr_ai.hp_max));
	LAi_SetCurHPMax(CopyChref);
	
	//копируем структуру quest от оригинального кэпа, очень нужно по квестам :)
	if (CheckAttribute(PastChref, "quest"))
    {
	    aref arToCharQuest, arFromCharQuest;
		makearef(arFromCharQuest, PastChref.quest);
		makearef(arToCharQuest, CopyChref.quest);
		DeleteAttribute(arToCharQuest, "");
		CopyAttributes(arToCharQuest, arFromCharQuest);
	}
	
	if (CheckAttribute(PastChref, "quest.officertype"))
    {
        CopyChref.quest.officertype     =   PastChref.quest.officertype;
    }
    else
    {
        DeleteAttribute(CopyChref, "quest.officertype");
    }

    if (CheckAttribute(PastChref, "Payment"))
    {
        CopyChref.Payment     =   PastChref.Payment; // платить ЗП
    }
    else
    {
        DeleteAttribute(CopyChref, "Payment");
    }
    if (CheckAttribute(PastChref, "HoldEquip"))
    {
        CopyChref.HoldEquip   =   PastChref.HoldEquip; // не отдавать саблю и пистоль
    }
	else
    {
        DeleteAttribute(CopyChref, "HoldEquip");
    }
    if (CheckAttribute(PastChref, "SaveItemsForDead"))
    {
        CopyChref.SaveItemsForDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "SaveItemsForDead");
    }
    if (CheckAttribute(PastChref, "DontClearDead"))
    {
        CopyChref.DontClearDead   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "DontClearDead");
    }
    if (CheckAttribute(PastChref, "OfficerWantToGo.DontGo"))
    {
        CopyChref.OfficerWantToGo.DontGo   =   true;
    }
	else
    {
        DeleteAttribute(CopyChref, "OfficerWantToGo.DontGo");
    }
    // skill
    DeleteAttribute(CopyChref, "skill");
    CopyChref.skill = "";

    makearef(arToChar, CopyChref.skill);
    makearef(arFromChar, PastChref.skill);

    CopyAttributes(arToChar,arFromChar);

    // SPECIAL
    DeleteAttribute(CopyChref, "SPECIAL");
    CopyChref.SPECIAL = "";

    makearef(arToChar, CopyChref.SPECIAL);
    makearef(arFromChar, PastChref.SPECIAL);

    CopyAttributes(arToChar,arFromChar);

    // Statistic
    DeleteAttribute(CopyChref, "Statistic");
    CopyChref.Statistic = "";

    makearef(arToChar, CopyChref.Statistic);
    makearef(arFromChar, PastChref.Statistic);

    CopyAttributes(arToChar,arFromChar);

    // perks
    DeleteAttribute(CopyChref, "perks");
    CopyChref.perks = "";

    makearef(arToChar, CopyChref.perks);
    makearef(arFromChar, PastChref.perks);

    CopyAttributes(arToChar,arFromChar);
    // items
    DeleteAttribute(CopyChref, "Items");
    CopyChref.Items = "";

    makearef(arToChar, CopyChref.Items);
    makearef(arFromChar, PastChref.Items);

    CopyAttributes(arToChar,arFromChar);

    if (CheckAttribute(PastChref, "equip.blade"))
    {
		CopyChref.equip.blade =   PastChref.equip.blade;
	}
	if (CheckAttribute(PastChref, "equip.gun"))
    {
		CopyChref.equip.gun   =   PastChref.equip.gun;
	}
	// health
	if (CheckAttribute(PastChref, "Health.TotalDamg"))
    {
		CopyChref.Health.TotalDamg =   PastChref.Health.TotalDamg;
	}
	else
	{
        CopyChref.Health.TotalDamg = 0;
	}
		
	if (CheckAttribute(PastChref,"EncType"))
	{
		CopyChref.EncType = PastChref.EncType;
	}
	
	if (CheckAttribute(PastChref,"RealEncounterType"))
	{
		CopyChref.RealEncounterType = PastChref.RealEncounterType;
	}
	if (CheckAttribute(PastChref,"Ship"))
	{
		makearef(arToChar, CopyChref.Back.Ship);
		makearef(arFromChar, PastChref.Ship);
		CopyAttributes(arToChar, arFromChar);		
	}	
	// <-- ugeen
	
	if (_dialogCopy && CheckAttribute(PastChref, "Dialog.Filename"))
	{
	    CopyChref.Dialog.Filename    = PastChref.Dialog.Filename;
	    CopyChref.Dialog.CurrentNode = PastChref.Dialog.CurrentNode;
	    if (CheckAttribute(PastChref, "greeting")) CopyChref.greeting = PastChref.greeting; //eddy.нет логам!
		else
		{
			DeleteAttribute(CopyChref, "greeting");
		}
	}
	SetEnergyToCharacter(CopyChref);
}

int GetCharacterLoyality(ref chr)
{
    if (CheckAttribute(chr, "loyality"))
    {
        if (sti(chr.loyality) > MAX_LOYALITY)
        {
            chr.loyality = MAX_LOYALITY;
        }
        if (sti(chr.loyality) < 0)
        {
            chr.loyality = 0;
        }
        return sti(chr.loyality);
    }
    else
    {
        return  0; // для пленных и гг
    }
}

// boal 091004 много героев  -->
// boal 23.01.2004 выбор персонажа-->
void setNewMainCharacter(ref ch, int num)
{
	string heroModel, heroFaceId;
	int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    totalInfo = LanguageConvertString(idLngFile, "heroFace_" + num);
    heroFaceId  = sti(totalInfo);
    ch.FaceId   = heroFaceId;

    totalInfo = LanguageConvertString(idLngFile, "heroModel_" + num);
    ch.HeroModel = totalInfo;
    ch.model	= GetSubStringByNum(ch.HeroModel, 0);

    totalInfo = LanguageConvertString(idLngFile, "heroName_" + num);
    ch.name 	=  totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "heroLastname_" + num);
    ch.lastname = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "sex_" + num);
    ch.sex = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "animation_" + num);
    ch.model.animation = totalInfo;

    if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}

    LanguageCloseFile(idLngFile);
    // для НПС
    ch.HeroParam.HeroType = GetNewMainCharacterType(num);
    ch.nation             = GetNewMainCharacterNation(num);

}

void initNewMainCharacter()
{
	ref ch = GetMainCharacter();
	string sTemp;
	int    iTmp, i;

    setNewMainCharacter(ch, startHeroType);
	
	switch(startHeroType)
	{
		case 1:
    		SetCharacterTalent(ch, "Agility");
    		SetCharacterTalent(ch, "Seducer");
		break;
		case 2:
		    SetCharacterTalent(ch, "KeenEye");
			SetCharacterTalent(ch, "ShadowMaster");
			SetCharacterPerk(ch, "spy");
		break;
		case 3:
		    SetCharacterTalent(ch, "BigBoy");
			SetCharacterTalent(ch, "Thug");
		break;
		case 4:
		    SetCharacterTalent(ch, "NaturalLeader");
			SetCharacterTalent(ch, "DiligentStudent");
		break;
	}
	
    // контроль версий -->
    ch.VersionNumber              = GetVerNum();
    ch.VersionNumberCompatibility = VERSION_NUM;
    // контроль версий <--
    ch.nation     = NullCharacter.HeroParam.nation;
    ch.BaseNation = NullCharacter.HeroParam.nation;
    
    MOD_EXP_RATE =  makeint(MOD_EXP_RATE + MOD_SKILL_ENEMY_RATE * MOD_EXP_RATE / 1.666666666); // разные уровни для всех
    if (MOD_EXP_RATE < 10) MOD_EXP_RATE = 10; // иначе будет развал целостности данных, порог релиховой версии бля всех сложностей.
    
	ch.HeroParam.ToCityId     = FindAlliedColonyForNation(sti(ch.nation), true);

	// откуда плывем
    ch.HeroParam.FromCityId  = Colonies[FindNonEnemyColonyForAdventure(sti(ch.nation), ch.HeroParam.ToCityId, true)].id;

	// где появимся
	if (sti(ch.nation) != PIRATE)
	{
	    ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
	    ch.HeroParam.Group    = "reload";
	    ch.HeroParam.Locator  = "reload1";
	}
	else
	{
		ch.HeroParam.Location = ch.HeroParam.ToCityId + "_port";
		ch.HeroParam.Group    = "reload";
		ch.HeroParam.Locator  = "sea";
	}

	setCharacterShipLocation(ch, ch.HeroParam.Location);
    setWDMPointXZ(ch.HeroParam.Location);  // коорд на карте
    
	SetTimerCondition("Move_Govenour", 0, 0, 25 + rand(10), true); // to_do перенести в один метод инициации
	//Запускаем проверку на падение здоровья раз в 5 дней
    SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
    
    SetTimerCondition("Nation_Legend", 0, 0, 25 + rand(10), true);

    // to_do PrepareVisitCity(); // задать квест на посежение города для нанесения его на карту

	ReloadProgressUpdate();

 	SetNationRelations();
 	// от кого драпаем
	ch.HeroParam.EnemyNation  = FindEnemyNation2Nation(sti(ch.nation));
	
    // boal вешаем прерывание на охотников навечно (для моря и земли) -->
    SetTimerCondition("SeaHunterCheck", 0, 0, 6, true);
    SaveCurrentQuestDateParam("Land_HunterTimerEng");
    SaveCurrentQuestDateParam("Land_HunterTimerFra");
    SaveCurrentQuestDateParam("Land_HunterTimerSpa");
    SaveCurrentQuestDateParam("Land_HunterTimerHol");
    // boal вешаем прерывание на охотников навечно (для моря и земли) <--
    LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP);

    ch.HeroParam.HeroType = NullCharacter.HeroParam.HeroType;

	SetSPECIAL(ch, 4,4,4,4,4,4,4); //фикс для любителей стирать тип ГГ в файле - была дыра
	switch (ch.HeroParam.HeroType)
	{
		// Rebbebion, новые классы, переименовал
		// следопыт
        case "Pathfinder":
		SetPIRATES(ch, 4, 9, 9, 2, 5, 8, 5);
		break;

        // негоциант
	    case "Negotiant":
		SetPIRATES(ch, 3, 3, 7, 9, 9, 3, 8);
	    break;

        // рейтар
	    case "Reiter":
		SetPIRATES(ch, 5, 7, 9, 4, 5, 5, 7);
	    break;
		
		// кирасир
		case "Cuirassier":
		SetPIRATES(ch, 9, 3, 7, 4, 4, 9, 6);
		break;
		
		// вор
		case "Thief":
		SetPIRATES(ch, 4, 8, 5, 4, 8, 4, 8);
		break;
	}
	ch.skill.freeskill   = 0;
	ch.Skill.FreeSPECIAL = 0;
	SetCharacterPerk(pchar, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
	// начальные скилы задать
    SetEnergyToCharacter(pchar);
    initMainCharacterItem();
    DeleteAttribute(pchar, "Ship");
	
	if (startHeroType <= 1)
	{
		switch (startHeroType)
		{
			case 1:
				Catherine_Start();
			break;
		}
	}
	
	// Начальный дневной рандом (dRand и dRandEx)
	PChar.DayRandom = Random();
	PChar.Random = (rand(9)+1); string yy;
	for(int y = 0; y < sti(PChar.Random); y++)
	{
		yy = y; //конвертация для помещения в атрибут; its() или ""+ здесь не помогут
		PChar.Random.nums.(yy) = Random();
	}
}

void initMainCharacterItem()
{
    ref ch = GetMainCharacter();
	String itemID;
		
	switch (ch.HeroParam.HeroType)
	{
		// стартовая экипировка следопыта
        case "Pathfinder":
			ch.money = 500;
			itemID = GetGeneratedItem("blade_03");	// итальянская рапира
        	GiveItem2Character(ch, itemID);
        	EquipCharacterbyItem(ch, itemID);
        	TakeNItems(ch, "potion1", 3);
	    break;

        // стартовая экипировка негоцианта
	    case "Negotiant":
	        ch.money = 2000;
			itemID = GetGeneratedItem("blade_18");	// дюссак
    	    GiveItem2Character(ch, itemID);
        	EquipCharacterbyItem(ch, itemID);
	    break;

        // стартовая экипировка рейтара
	    case "Reiter":
			ch.money = 300;
			itemID = GetGeneratedItem("blade_02");	// стилет
        	GiveItem2Character(ch, itemID);
        	EquipCharacterbyItem(ch, itemID);
	    	GiveItem2Character(ch, "pistol1"); // пистоль
        	EquipCharacterbyItem(ch, "pistol1");
        	TakeNItems(ch, "bullet", 20);
        	TakeNItems(ch, "gunpowder", 20);
	    	LAi_SetCharacterUseBullet(ch, "bullet");	
	    break;
		
		// стартовая экипировка кирасира
		case "Cuirassier":
			ch.money = 1000;
			itemID = GetGeneratedItem("blade_37");	// гросс-мессер
        	GiveItem2Character(ch, itemID);
        	EquipCharacterbyItem(ch, itemID);
		break;
		
		// стартовая экипировка вора
		case "Thief":
			ch.money = 1000;
			itemID = GetGeneratedItem("blade_02");	// стилет
        	GiveItem2Character(ch, itemID);
        	EquipCharacterbyItem(ch, itemID);
        	TakeNItems(ch, "gold_dublon", 50);
        	GiveItem2Character(ch, "mineral10"); // игральные карты
		break;
	}
}


int GetNewMainCharacterFace()
{
    return sti(GetNewMainCharacterParam("heroFace_" + startHeroType));
}

string GetNewMainCharacterName()
{
    return GetHeroName(startHeroType);
}

string GetMainCharacterNameGen()  // ==> eddy. родительный падеж полного имени ГГ
{
    return GetHeroNameGen(startHeroType);
}
string GetMainCharacterNameDat()  // ==> eddy. дательный падеж полного имени ГГ
{
    return GetHeroNameDat(startHeroType);
}

string GetHeroName(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroName_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastname_" + _n);

    return totalInfo;
}

string GetHeroNameGen(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameGen_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameGen_" + _n);

    return totalInfo;
}
string GetHeroNameDat(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameDat_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameDat_" + _n);

    return totalInfo;
}
int GetNewMainCharacterNation(int _startHeroType)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, "heroNation_" + _startHeroType);
    LanguageCloseFile(idLngFile);

    switch(totalInfo)
	{
		case "Англия":
            return ENGLAND;
		break;
		case "Франция":
            return FRANCE;
		break;
		case "Испания":
            return SPAIN;
		break;
		case "Голландия":
			return HOLLAND;
		break;
		case "Береговое Братство":
			return PIRATE;
		break;

		case "ENGLAND":
            return ENGLAND;
		break;
		case "FRANCE":
            return FRANCE;
		break;
		case "SPAIN":
            return SPAIN;
		break;
		case "HOLLAND":
			return HOLLAND;
		break;
		case "PIRATE":
			return PIRATE;
		break;
	}
	return PIRATE;
}

string GetNewMainCharacterType(int _startHeroType)
{
    string ret = GetNewMainCharacterParam("heroType_" + _startHeroType);

    switch (ret) // нужно по английски для квестбука
	{
        case "Следопыт":
    	    ret = "Pathfinder";
	    break;

	    case "Негоциант":
            ret = "Negotiant";
	    break;

	    case "Рейтар":
            ret = "Reiter";
	    break;
		
		case "Кирасир":
            ret = "Cuirassier";
	    break;
		
		case "Вор":
            ret = "Thief";
	    break;
	}

	return ret;
}

string GetNewMainCharacterParam(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// вернуть базовую нацию ГГ или патент
int GetBaseHeroNation()
{
	if (isMainCharacterPatented())
	{
	    return sti(Items[sti(pchar.EquipedPatentId)].Nation);
	}
	return sti(pchar.BaseNation);
}
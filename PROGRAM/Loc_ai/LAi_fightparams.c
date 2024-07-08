/*

	Возможные типы атаки attackType:
	"fast" быстрая атака
	"force" обычная
	"round" круговая
	"break" пробивающая блок
	"feint" атака после финта


*/

//--------------------------------------------------------------------------------
//Blade parameters
//--------------------------------------------------------------------------------

//Расчитать повреждение для персонажа
float LAi_CalcDamageForBlade(aref attack, aref enemy, string attackType, bool isBlocked)
{
	//Расчитываем повреждение от сабли
	float min = 10.0;
	float max = 10.0;
	
	ref rItm = ItemsFromID(GetCharacterEquipByGroup(attack, BLADE_ITEM_TYPE));
	
	if(CheckAttribute(attack, "chr_ai.dmgbldmin"))
	{
		min = stf(attack.chr_ai.dmgbldmin);
	}
	
	if(CheckAttribute(attack, "chr_ai.dmgbldmax"))
	{
		max = stf(attack.chr_ai.dmgbldmax);
	}
	
	float bladeDmg = min + (max - min)*frandSmall(LAi_GetCharacterFightLevel(attack));
	//Коэфициент в зависимости от скилов
	float aSkill = LAi_GetCharacterFightLevel(attack);
	float eSkill = LAi_GetCharacterFightLevel(enemy);
	
    if(aSkill < eSkill)
	{
		bladeDmg = bladeDmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	
	// Warship 27.08.09 Для сильных противников
	// Если долбить совсем сильных (хардкорные абордажи), то шансов взять шип будет меньше
	if(sti(enemy.Rank) > 50)
	{
		bladeDmg = bladeDmg * 45 / sti(enemy.Rank);
	}
	
	if(CheckAttribute(loadedLocation, "CabinType") && sti(enemy.index) == GetMainCharacterIndex())
	{
		bladeDmg = bladeDmg * (1.0 + stf(attack.rank)/100);
	}
	
	//Коэфициент в зависимости от удара
	float kAttackDmg = LAi_GetDamageAttackType(attack, enemy, attackType, rItm, isBlocked);
	
	if(CheckCharacterTalent(pchar, "Agility"))
	{
	    if(rItm.FencingType == "FencingLight") kAttackDmg = kAttackDmg * 1.25;
	    else kAttackDmg = kAttackDmg * 0.75;
	}
	
	if(kAttackDmg > 0)  // оптимизация boal
	{
		//Результирующий демедж
		float dmg = bladeDmg * kAttackDmg;
		
		if(IsCharacterEquippedTalisman(attack, "totem_22"))  
		{
			if(CheckAttribute(enemy, "chr_ai.energy"))
			{
				enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.9); //fix
			}
		}
		
		if(MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())	
		{
			dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
		}
		
		if (attack.model.animation == "mushketer" && IsMainCharacter(attack))
		{
			dmg = dmg / 3.0;
		}
		
		return dmg;
	}
	
	return 0.0;
}

// Ugeen --> расчет множителя повреждения при разных типах атаки
float LAi_GetDamageAttackType(aref attack, aref enemy, string attackType, ref aBlade, bool isBlocked)
{
	float kAttackDmg = 1.0;
	string sType  = aBlade.SubType;  // подтип
	
	switch(attackType)
	{
		//ЛКМ - Обычный
		case "fast":
			if(isBlocked)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				if(sType == "Spear" || sType == "Rapier" || sType == "SmallSword" || sType == "LightAxe" || sType == "Bastard" || sType == "HeavyAxe" || sType == "HeavySmallSword" || sType == "Katana" || sType == "Tomahawk" || sType == "LightFalchion" || sType == "Falchion" || sType == "Ngala")
				{
					kAttackDmg = 0.7;
					if(CheckCharacterPerk(attack, "Crusader")) kAttackDmg = kAttackDmg * 2;
					if(attack.id == pchar.id) Log_TestInfo("Профильный удар");
			    }
				else
				{
					kAttackDmg = 0.35;
					if(attack.id == pchar.id) Log_TestInfo("НЕ профильный удар");
				}
			}
		break;
		
		//ПКМ - Колющий
		case "force":
			if(isBlocked)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				if(sType == "Spear" || sType == "Dagger" || sType == "LightSword" || sType == "Cleaver" || sType == "Bastard" || sType == "Broadsword")
				{
					kAttackDmg = 1.0;
					if(CheckCharacterPerk(attack, "Crusader")) kAttackDmg = kAttackDmg * 2;
					if(attack.id == pchar.id) Log_TestInfo("Профильный удар");
			    }
				else
				{
					kAttackDmg = 0.5;
					if(attack.id == pchar.id) Log_TestInfo("НЕ профильный удар");
				}
			}
		break;
		
		//SHift + ЛКМ - круговой
		case "round":
			if(isBlocked)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				if(sType == "Spear" || sType == "Rapier" || sType == "Saber" || sType == "Sword" || sType == "HeavySmallSword" || sType == "Klewang" || sType == "Katana" || sType == "Ngala")
				{
					kAttackDmg = 0.6;
					if(CheckCharacterPerk(attack, "Crusader")) kAttackDmg = kAttackDmg * 2;
					if(attack.id == pchar.id) Log_TestInfo("Профильный удар");
			    }
				else
				{
					kAttackDmg = 0.3;
					if(attack.id == pchar.id) Log_TestInfo("НЕ профильный удар");
				}
			}
			if(CheckCharacterPerk(attack, "BladeDancer")) kAttackDmg = kAttackDmg * 1.3;
		break;
		
		//СКМ - пробивающий
		case "break":
			if(isBlocked)
			{
				if(sType == "SmallSword" || sType == "LightSword" || sType == "Saber" || sType == "Cleaver" || sType == "LightAxe" || sType == "HeavyAxe" || sType == "Sword" || sType == "Broadsword" || sType == "Klewang" || sType == "Pickaxe" || sType == "Tomahawk" || sType == "LightFalchion" || sType == "Falchion" || sType == "Macuahuitl" || sType == "Godendag")
				{
					kAttackDmg = 1.0;
					if(CheckCharacterPerk(attack, "Crusader")) kAttackDmg = kAttackDmg * 2;
					if(attack.id == pchar.id) Log_TestInfo("Профильный удар");
			    }
			    else
				{
					kAttackDmg = 0.5;
			    	if(attack.id == pchar.id) Log_TestInfo("НЕ профильный удар");
				}
			}
			else
			{
				if(sType == "SmallSword" || sType == "LightSword" || sType == "Saber" || sType == "Cleaver" || sType == "LightAxe" || sType == "HeavyAxe" || sType == "Sword" || sType == "Broadsword" || sType == "Klewang" || sType == "Pickaxe" || sType == "Tomahawk" || sType == "LightFalchion" || sType == "Falchion" || sType == "Macuahuitl" || sType == "Godendag")
				{
					kAttackDmg = 3.0;
					if(CheckCharacterPerk(attack, "Crusader")) kAttackDmg = kAttackDmg * 2;
					if(attack.id == pchar.id) Log_TestInfo("Профильный удар");
			    }
				else
				{
					kAttackDmg = 1.5;
					if(attack.id == pchar.id) Log_TestInfo("НЕ профильный удар");
				}
			}
			
			if(CheckCharacterPerk(attack, "HandOfGod")) kAttackDmg = kAttackDmg * 1.3;
			
			if(CheckAttribute(attack, "SpeciaPotionEffect.huitzilopochtli")) kAttackDmg = kAttackDmg * 1.25;
			
			if(IsCharacterEquippedTalisman(enemy, "totem_07")) kAttackDmg = kAttackDmg * 0.9;
		break;
		
		//SHift + ПКМ - парирование
		case "feintc":  // фикс после изучения ядра //Атакующие продолжение финта
			if(isBlocked)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				kAttackDmg = 0.5;
			}
		break;
		
		//SHift + СКМ - Финт с контратакой
		case "feint":
			if(isBlocked)
			{
				kAttackDmg = 0.0;
			}
			else
			{
				kAttackDmg = 0.5;
			}
		break;
	}
	
	return kAttackDmg;
}
// Ugeen <-- расчет множителя повреждения при разных типах атаки

//Расчитать полученный опыт при ударе саблей
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, bool isBlocked, float dmg)
{
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));

	switch(attackType)
	{
		case "break":
			if(isBlocked)
			{
				dmg = dmg * 1.1;
			}
			else
			{
				dmg = dmg * 1.2;
			}
		break;
		case "feint":
			dmg = dmg*1.5;
		break;
		case "feintc":
			dmg = dmg*1.5;
		break;
	}
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
	return dmg;
}

//Энергия, необходимая для запуска действия
float LAi_CalcUseEnergyForBlade(aref character, string actionType)
{
	float energy = 0.0;
	
	switch(actionType)
	{
		case "fast":
			energy = 10.0;
		break;
		case "force":
			energy = 7.0;
		break;
		case "round":
			energy = 14.0;
		break;
		case "break":
			energy = 25.0;
		break;
		case "hit_parry":  // boal fix эту энергию тратит не атакующий, а атакуемый в анимации fgt_hit_parry
			energy = 20.0;
		break;
		case "feintc":
			energy = 7.0; // расход при успехе финта
		break;
	}
	
	if(energy > 0)  // оптимизация
	{
		float fSkill = LAi_GetCharacterFightLevel(character);  // stf(character.skill.fencing) - не так это далеют!!
		fSkill = (1.0 - (0.3 * fSkill));
		energy = energy * fSkill * LAi_GetBladeEnergyType(character);  // энергоемкость от веса
	}
	
	return energy;
}

float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime)
{
	float fMultiplier = 1.6666667;

	if(CheckCharacterPerk(chr, "Energaiser")) // скрытый перк боссов и ГГ
	{
		fMultiplier = fMultiplier * 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless")) 
	{
		fMultiplier = fMultiplier * 1.05;
	}
	if(CheckCharacterPerk(chr, "Crusader")) 
	{
		fMultiplier = fMultiplier * 1.10;
	}
	if(CheckAttribute(chr, "SpeciaPotionEffect.tlaloc")) 
	{
		fMultiplier = fMultiplier * 1.15;
	}
	float fEnergy;
	fEnergy = curEnergy + dltTime * fMultiplier; 

	return fEnergy;
}


//--------------------------------------------------------------------------------
//Gun parameters
//--------------------------------------------------------------------------------

//Расчитаем вероятность попадания
float LAi_GunCalcProbability(aref attack, float kDist)
{
	//Если близко, то попадём точно
	if(kDist >= 0.9) return 1.0;
	//Расчитаем вероятность на конце отрезка
	float pmin = 0.3;
 	if(CheckAttribute(attack, "chr_ai.accuracy")) // boal это меткость самого пистолета, а не скил!
	{
		pmin = stf(attack.chr_ai.accuracy);
	}
 	//Применим разброс от скила
	// boal -->
	float aSkill = LAi_GetCharacterGunLevel(attack);
	// boal <--

	pmin = pmin + 0.3*aSkill;

	//Вероятность попадания в текущей позиции
	float p = pmin + (1.0 - pmin)*(kDist/0.9);
	
	if(CheckAttribute(attack, "SpeciaPotionEffect.Jaguar")) p = p * 1.15;
	
	if(IsCharacterEquippedTalisman(attack, "totem_20"))  p = p * 1.1;
	
	// путь будет больше 1 - тогда 100% попал
	return p;
}

//Получить повреждение от пистолета
float LAi_GunCalcDamage(aref attack, aref enemy)
{
	//Расчитываем повреждение
	float min = 10.0;
	float max = 10.0;
	
	string sBullet = LAi_GetCharacterBulletType(attack);
	
	if(CheckAttribute(attack, "chr_ai.dmggunmin"))
	{
		min = stf(attack.chr_ai.dmggunmin);
	}
	
	if(CheckAttribute(attack, "chr_ai.dmggunmax"))
	{
		max = stf(attack.chr_ai.dmggunmax);
	}
	//Учитываем скилы
	float aSkill = LAi_GetCharacterGunLevel(attack);
	float eSkill = LAi_GetCharacterLuckLevel(enemy); // good luck
	
	float dmg = min + (max - min)*frandSmall(aSkill);
	//Модифицировать повреждение от pistol с учетом скилов
    if(aSkill < eSkill)
	{
		dmg = dmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())	
	{
		dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
	}
	
	if(sBullet == "petard") dmg = dmg * 0.33; //Петарды не наносят урона (почти)
	
	if(CheckCharacterPerk(attack, "Grenadier"))
	{
		if(sBullet == "petard" || sBullet == "grenade" || sBullet == "poison_bomb") dmg = dmg * 2;
	}
	
	if(CharIsUndead(enemy))
	{
		if(sBullet == "silver_bullet" || sBullet == "Silver_cartridge") dmg = dmg * 2;
	}
	
	return dmg;
}

//Расчитать полученный опыт при попадании из пистолета
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
    //Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
    return dmg;
}

//Расчитаем текущую скорость перезарядки пистолета
float LAi_GunReloadSpeed(aref chr)
{
	//Получим текущее состояние скорости зарядки
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if(CheckAttribute(chr, "chr_ai.charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.charge_dlt);
	}
	//Модифицируем скилом
	// boal -->
	//float skill = LAi_GetCharacterFightLevel(chr);
	float skill = LAi_GetCharacterGunLevel(chr);
	// boal <--

	charge_dlt = charge_dlt*(1.0 + 0.3*skill);//boal
	//УчтЈм абилити
	if(IsCharacterPerkOn(chr, "Shooter"))
	{
		charge_dlt = charge_dlt*1.25;
	}
	else
	{
		if(IsCharacterPerkOn(chr, "Breter"))
		{
			charge_dlt = charge_dlt*1.15;
		}
		else
		{
			if(IsCharacterPerkOn(chr, "Musketeer"))
		    {
	    		charge_dlt = charge_dlt*1.05;
    		}
		}
	}
	return charge_dlt;
}

//--------------------------------------------------------------------------------
//Calculate total
//--------------------------------------------------------------------------------

//Начисление повреждений при атаке мечём
void LAi_ApplyCharacterAttackDamage(aref attack, aref enemy, string attackType, bool isBlocked)
{
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//Вычисляем повреждение
	float dmg = LAi_CalcDamageForBlade(attack, enemy, attackType, isBlocked);
	float critical = 0.0;
	int iCrtChance = 0;
	int Ddgchance = 0;
	float iCirassLevel = 0;
	
	string weaponID = GetCharacterEquipByGroup(attack, BLADE_ITEM_TYPE);
    aref weapon;
    Items_FindItem(weaponID, &weapon);
	
	if(CheckAttribute(attack, "SpeciaPotionEffect.huitzilopochtli")) iCrtChance = iCrtChance + 25;
	
	if(IsCharacterPerkOn(attack, "CriticalHit")) iCrtChance = iCrtChance + 5;
	
	CheckCharacterPerk(attack, "HardHitter") iCrtChance = iCrtChance + 15;
	
	IsCharacterEquippedTalisman(enemy, "totem_04") iCrtChance = iCrtChance - 5;
	
	if(rand(100) <= iCrtChance)
	{
		critical = 1.0;
	}

	float kDmg = 1.0;
	if(CheckAttribute(attack, "SpeciaPotionEffect.berserker_potion"))
	{
		kDmg = 3.0;
	}
	
	float kDmgRush = 1.0;
	if(CheckAttribute(enemy, "SpeciaPotionEffect.berserker_potion"))
	{
		kDmgRush = 0.5;
	}
	
	dmg = dmg*kDmg*kDmgRush;
	//Аттака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group") && CheckAttribute(enemy, "chr_ai.group"))
	{
		if(attack.chr_ai.group == enemy.chr_ai.group)
		{
			dmg = 0.0;
			critical = 0.0;
			noExp = true;
		}
	}
	
	if(isBlocked)// если кираса или блок, то критикал невозможен
	{
		critical = 0;
	}
	
	if(CheckAttribute(enemy, "cirassId") && critical > 0.0 && CheckAttribute(&Items[sti(enemy.cirassId)],"critical"))
	{
		iCrtChance = makeint(stf(Items[sti(enemy.cirassId)].critical) * 1000)
		
		if(CheckCharacterTalent(pchar, "Agility"))
		{
			if(Items[sti(enemy.cirassId)].id == "Cirass1" || Items[sti(enemy.cirassId)].id == "Cirass2" || Items[sti(enemy.cirassId)].id == "Cirass3" || Items[sti(enemy.cirassId)].id == "Cirass6" || Items[sti(enemy.cirassId)].id == "Cirass7") iCrtChance = iCrtChance * 1.25;
			else iCrtChance = iCrtChance * 0.75;
		}
		
		if(iCrtChance < rand(1000)) critical = 0.0;
	}
	
	if(critical > 0.0)
	{
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
		if(sti(attack.index) == GetMainCharacterIndex())
		{
			Log_SetStringToLog(XI_ConvertString("Critical Hit"));
		}
	}
	kDmg = 1.0;
	if(IsCharacterPerkOn(enemy, "BasicDefense")) kDmg = 0.9;
	
	if(IsCharacterPerkOn(enemy, "StrengthOfSpirit")) kDmg = 0.85;
	
	if(IsCharacterPerkOn(enemy, "Knight")) kDmg = 0.8;
	
	if(IsCharacterPerkOn(enemy, "Paladin")) kDmg = 0.7;

	// ГПК 1.2.3
	dmg = dmg*kDmg;
	dmg = dmg *(1 + critical);//dmg + critical;
	if(CheckAttribute(enemy, "cirassId"))
	{
		iCirassLevel = 1.0 - stf(Items[sti(enemy.cirassId)].B_CirassLevel);
		if(CheckCharacterTalent(pchar, "Agility"))
		{
			if(Items[sti(enemy.cirassId)].id == "Cirass1" || Items[sti(enemy.cirassId)].id == "Cirass2" || Items[sti(enemy.cirassId)].id == "Cirass3" || Items[sti(enemy.cirassId)].id == "Cirass6" || Items[sti(enemy.cirassId)].id == "Cirass7") iCirassLevel = iCirassLevel * 0.75;
			else iCirassLevel = iCirassLevel * 1.25;
		}
		dmg = dmg * iCirassLevel;
	}
	
	if(CheckCharacterPerk(enemy, "BladeDancer")) Ddgchance = Ddgchance + 5;
	
	if(CheckCharacterPerk(enemy, "Crusader")) Ddgchance = Ddgchance + 5;
	
	if((rand(99) + 1) <= Ddgchance)
	{
		if(enemy.id == pchar.id) Log_TestInfo("Уворот, ёпта!");
		else Log_TestInfo("У перса "+enemy.id+" уворот, ёпта!");
		dmg = 0;
    }
	
	if(dmg > 0.0)
	{
        //проверим на отравление
		if (CheckAttribute(weapon, "isPoisoned"))
		{
			if (CheckAttribute(weapon, "isPoisoned.poisonQunatity"))
			{
				if(attack.id == pchar.id) Log_TestInfo("Это яд, расчитанный на попадания");
				if(weapon.isPoisoned.poisonQunatity > 0)
				{
			    	weapon.isPoisoned.poisonQunatity = sti(weapon.isPoisoned.poisonQunatity) - 1;
					
					if(CheckCharacterPerk(enemy, "SnakeSkin") || IsCharacterEquippedTalisman(enemy, "totem_27") || CheckAttribute(enemy, "PoisonResist"))
					{
						Log_TestInfo("У персонажа " +enemy.id+ " иммунитет/Черная роза/Змеиная кожа!");
					}
					else
					{
    					dmg = dmg * sti(weapon.isPoisoned.dmgBonus);
    					
						if(rand(100) <= sti(weapon.isPoisoned.InstantKill) && !CheckAttribute(enemy, "IsBoss"))
						{
							dmg = LAi_GetCharacterMaxHP(enemy) + 1;
							Log_TestInfo("Инстант Килл!");
						}
					}
					
					if(attack.id == pchar.id) Log_TestInfo("Осталось "+ weapon.isPoisoned.poisonQunatity +" отравленных ударов");
					
					if(weapon.isPoisoned.poisonQunatity < 1)
					{
						DeleteAttribute(weapon, "isPoisoned");
		    	    	DeleteAttribute(weapon, "isPoisoned.poisonQunatity");
		    	   	 	DeleteAttribute(weapon, "isPoisoned.poison");
	    		    	if(attack.id == pchar.id) Log_TestInfo("Действие яда закончилось");
					}
    			}
		    	else
	    		{
    				DeleteAttribute(weapon, "isPoisoned");
		    		DeleteAttribute(weapon, "isPoisoned.poisonQunatity");
		    		DeleteAttribute(weapon, "isPoisoned.poison");
	    			if(attack.id == pchar.id) Log_TestInfo("Действие яда закончилось");
    			}
		    }
			else
			{
				if(attack.id == pchar.id) Log_TestInfo("Это яд, расчитанный на время");
				MakePoisonAttack(attack, enemy, sti(weapon.isPoisoned.poisonduration), sti(weapon.isPoisoned.poisonchance), sti(weapon.isPoisoned.poisondamage), weapon.isPoisoned.poison);
			}
		}
		//Наносим повреждение
		LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5));
		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
	}
	//Есть ли оружие у цели
	bool isSetBlade = (CheckAttribute(enemy, "equip.blade") == true);
	//Начисляем опыта
	float exp = LAi_CalcExperienceForBlade(attack, enemy, attackType, isBlocked, dmg);
	if(LAi_IsDead(enemy))
	{
		// boal  check skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
        AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), makefloat(10.0 + ((1 + re) / (1+ra))*6.5));
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 1);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_s");
        // boal statistic info 17.12.2003 <--
        LAi_SetResultOfDeath(attack, enemy, isSetBlade);
	}
	if(!isSetBlade)
	{
		exp = 0.0;
	}
	
	if (!noExp)
    {
        AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), Makefloat(exp*0.2));
    }
	
}
//boal 19.09.05 -->
void LAi_SetResultOfDeath(ref attack, ref enemy, bool isSetBlade)
{
    if (sti(attack.index) == GetMainCharacterIndex())
    {
		if (GetRelation2BaseNation(sti(enemy.nation)) == RELATION_ENEMY)
		{
			if (!isSetBlade)
			{
				LAi_ChangeReputation(attack, -1);   // to_do
				if (rand(1) && CheckAttribute(enemy, "City"))
				{
					ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 1);
				}
			}
		}
		else
		{
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 2);
			}
		}
		// обида нации на разборки в городе boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// нужна проверка на дуэли и квесты
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // скрытность
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
	}
}
// boal <--

//Начисление повреждений при попадании
void LAi_ApplyCharacterFireDamage(aref attack, aref enemy, float kDist)
{
	ref rItm = ItemsFromID(GetCharacterEquipByGroup(attack, GUN_ITEM_TYPE));
	int iCirassLevel;
	Lai_CharacterChangeEnergy(attack, -4); // жрем энергию за выстрел boal 20/06/06
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//Вероятность поподания
	float p = LAi_GunCalcProbability(attack, kDist);
	
	if(IsCharacterEquippedTalisman(enemy, "totem_04"))  p = p * 0.95;
	
	//Если промахнулись, то выйдем
	if(rand(10000) > p*10000) return;	  
	// boal брон работает всегда, а не токо в блоке 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId"))
	{
		iCirassLevel = (1.0 - stf(Items[sti(enemy.cirassId)].G_CirassLevel));
		if(CheckCharacterTalent(pchar, "Agility"))
		{
			if(Items[sti(enemy.cirassId)].id == "Cirass1" || Items[sti(enemy.cirassId)].id == "Cirass2" || Items[sti(enemy.cirassId)].id == "Cirass3" || Items[sti(enemy.cirassId)].id == "Cirass6" || Items[sti(enemy.cirassId)].id == "Cirass7") iCirassLevel = iCirassLevel * 0.75;
			else iCirassLevel = iCirassLevel * 1.25;
		}
		damage = damage * iCirassLevel;
	}
	// boal 23.05.2004 <--
	//Начисляем повреждение
	float damage = LAi_GunCalcDamage(attack, enemy);
	
	if(CheckCharacterTalent(pchar, "Agility"))
	{
	    if(HasSubStr(rItm.id, "pistol")) damage = damage * 1.25;
	    else damage = damage * 0.75;
	}
	
	damage = damage + makeint(isEquippedTalismanUse(attack, "totem_20", 0.0, 10.0));

	//Аттака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group"))
	{
		if(CheckAttribute(enemy, "chr_ai.group"))
		{
			if(attack.chr_ai.group == enemy.chr_ai.group)
			{
				damage = 0.0;
				noExp = true;
			}
		}
	}
	
	if(damage > 0.0)
	{
		LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5));	
		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
	}
	
	//Есть ли оружие у цели
	bool isSetBlade = (CheckAttribute(enemy, "equip.blade") == true);
	//Начисляем опыт
	float exp = LAi_GunCalcExperience(attack, enemy, damage);
	if(LAi_IsDead(enemy))
	{
		// boal skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
        AddCharacterExpToSkill(attack, SKILL_PISTOL, makefloat(15.0 + ((1 + re) / (1+ra))*12.0));
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
		// boal skill <--
		// boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_g");
        // boal statistic info 17.12.2003 <--
        
  		LAi_SetResultOfDeath(attack, enemy, isSetBlade);
	}
	
	if(!isSetBlade)
	{
		//LAi_ChangeReputation(attack, -1);
		exp = 0.0;
	}
	
	if(!noExp)
    {
        AddCharacterExpToSkill(attack, SKILL_PISTOL, Makefloat(exp*0.85));
    }
}

bool IsAttackerHitByProfile(aref attack, string attackType)
{
	string sEBG = GetCharacterEquipByGroup(attack, BLADE_ITEM_TYPE);
	string sType;
	
	if(sEBG == "" || sEBG == "unarmed") return false;
    ref rIFID = ItemsFromID(sEBG);
	
	if(CheckAttribute(rIFID, "SubType")) sType = rIFID.SubType;  // подтип
	
	switch(attackType)
	{
		//ЛКМ - Обычный
		case "fast":
			if(sType == "Spear" || sType == "Rapier" || sType == "SmallSword" || sType == "LightAxe" || sType == "Bastard" || sType == "HeavyAxe" || sType == "HeavySmallSword" || sType == "Katana" || sType == "Tomahawk" || sType == "LightFalchion" || sType == "Falchion" || sType == "Ngala")
			{
				return true;
			}
		break;
		
		//ПКМ - Колющий
		case "force":
			if(sType == "Spear" || sType == "Dagger" || sType == "LightSword" || sType == "Cleaver" || sType == "Bastard" || sType == "Broadsword")
			{
				return true;
			}
		break;
		
		//SHift + ЛКМ - круговой
		case "round":
			if(sType == "Spear" || sType == "Rapier" || sType == "Saber" || sType == "Sword" || sType == "HeavySmallSword" || sType == "Klewang" || sType == "Katana" || sType == "Ngala")
			{
				return true;
			}
		break;
		
		//СКМ - пробивающий
		case "break":
			if(sType == "SmallSword" || sType == "LightSword" || sType == "Saber" || sType == "Cleaver" || sType == "LightAxe" || sType == "HeavyAxe" || sType == "Sword" || sType == "Broadsword" || sType == "Klewang" || sType == "Pickaxe" || sType == "Tomahawk" || sType == "LightFalchion" || sType == "Falchion" || sType == "Macuahuitl" || sType == "Godendag")
			{
				return true;
			}
		break;
	}
	
	return false;
}

//--------------------------------------------------------------------------------
//Параметры NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//Атаки
//Скорость нарастания вероятности атаки в секунду  p > 0
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.7;
	npc_return_tmp = npc_return_tmp + 0.1;
	return npc_return_tmp;
}

//Вес выбора удара "fast", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFast","LAi_NPC_GetAttackWeightFast");
float LAi_NPC_GetAttackWeightFast()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	if(IsAttackerHitByProfile(chr, "fast")) npc_return_tmp = npc_return_tmp * 1.5;	
	return npc_return_tmp;
}

//Вес выбора удара "force", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightForce","LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 50.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	if(IsAttackerHitByProfile(chr, "Force"))  npc_return_tmp = npc_return_tmp * 1.5;
	return npc_return_tmp;
}

//Вес выбора удара "round", 0 - никогда не выбирать, если врагов <3 то удар не выбирается
#event_handler("NPC_Event_GetAttackWeightRound","LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	if(IsAttackerHitByProfile(chr, "Round"))  npc_return_tmp = npc_return_tmp * 1.5;
	return npc_return_tmp;
}

//Вес выбора удара "break", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightBreak","LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	if(IsAttackerHitByProfile(chr, "Break"))  npc_return_tmp = npc_return_tmp * 1.5;
	return npc_return_tmp;
}

//Вес выбора удара "feint", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFeint","LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Прараметры защиты
//Вероятность желания защитится - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceActive","LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.35;
	return npc_return_tmp;
}

// boal 20.01.08 коммент - забавно, что спустя два года, понал как и что с вероятностями. Они все приводятся к 0-1 от веса общей суммы, то есть фактически умножение на сложность или цифры распределяют сумму по другим акшенам, а не усиливают этот
// Экшены идут парами - все атаки и защита (блок + пари)
//Вес выбора блока, 0 - никогда не выбирать
#event_handler("NPC_Event_GetDefenceWeightBlock","LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));   // boal
	return npc_return_tmp;
}

//Вес выбора  паррирования, 0 - никогда не выбирать
//кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0; // 40 boal
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Разрешён ли отскок
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}


//Параметры стрельбы
//Вероятность желания выстрелить - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.001 + level*0.06;
	// boal наши офицеры пулят из всех стволов -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
        npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal наши офицеры пулят из всех стволов <--
		if (CheckAttribute(chr, "SuperShooter"))
		{
			npc_return_tmp = npc_return_tmp + 0.4 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
		else
		{
			npc_return_tmp = npc_return_tmp + 0.1 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
	}
	if(chr.model.animation == "mushketer") npc_return_tmp = 0.99;
	
	return npc_return_tmp;
}

//Разрешён ли выстрел
#event_handler("NPC_Event_EnableFire","LAi_NPC_EnableFire");
bool LAi_NPC_EnableFire()
{
	aref chr = GetEventData();
	return   true;
}

//Разрещён ли временный перевыбор цели среди ближних - опрашивается постоянно
#event_handler("NPC_Event_AdaptiveTargetSelect","LAi_NPC_AdaptiveTargetSelect");
bool LAi_NPC_AdaptiveTargetSelect()
{
	aref chr = GetEventData();
	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
	{
		npc_return_tmpb = false;
	}else{
		npc_return_tmpb = true;
	}
	return npc_return_tmpb;
}


//--------------------------------------------------------------------------------
//Work
//--------------------------------------------------------------------------------

#event_handler("Location_CharacterSGFire","LAi_Location_CharacterSGFire");
void LAi_Location_CharacterSGFire()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDmg = GetEventData();
	if(LAi_IsDead(enemy)) return;
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//Наносим повреждение
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg));
	//Проверим на смерть
	LAi_CheckKillCharacter(enemy);
}

#event_handler("ChrAttackAction", "LAi_ChrAttackAction");
bool LAi_ChrAttackAction()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float curEnergy = Lai_CharacterGetEnergy(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	if(curEnergy >= needEnergy)
	{
		npc_return_tmpb = true;
	}
	else
	{
		npc_return_tmpb = false;
	}
	return npc_return_tmpb;
}

#event_handler("ChrFgtActApply", "LAi_ChrFightActionApply");
void LAi_ChrFightActionApply()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	Lai_CharacterChangeEnergy(attack, -needEnergy);
}

//Получить относительную затрачиваемую энергию
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение жизни
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}


//Необходимо вернуть максимально быстро нормализованое значение энергии
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}
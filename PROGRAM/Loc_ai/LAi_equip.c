#define PERK_TEMPLATE_SHIPDEFENCE	0	// 3 perks
#define PERK_TEMPLATE_REPAIR		1	// 2 perks
#define PERK_TEMPLATE_CANNONS		2	// 8 perks
#define PERK_TEMPLATE_SPEECHCRAFT	3	// 5 perks
#define PERK_TEMPLATE_SAILING		4	// 5 perks
#define PERK_TEMPLATE_GRAPPLING		5	// 3 perks
#define PERK_TEMPLATE_MELEE		    6	// 9 perks
#define PERK_TEMPLATE_PERSONAL		7	// 6 perks
#define PERK_TEMPLATE_LAST          8

//Экипировать NPC оружием и перками (переделал полностью 11/11/04 boal)
void LAi_NPC_Equip(ref chr, int rank, bool isWeapons, bool isGun)
{
	// boal не нужно - ранг и так точно расчитан r = rank + rand(3) - 1;
	string sBullet = "bullet";
	string blade, gun, sGunPowder;
	
	DeleteAttribute(chr, "equip");
	DeleteAttribute(chr, "perks.list"); // FIX 101104 убрать накопивщиеся умения
	DelBakSkillAttr(chr); // fix
	
    if (chr.model.animation == "mushketer") return;
	if (chr.sex == "woman") return;
	
	if (CheckAttribute(chr, "quest.officertype"))
	{
		// наши офицеры
		LAi_NPC_EquipPerk(chr, chr.quest.officertype);
	}
	else
	{
		LAi_NPC_EquipPerk(chr, "fantom");
	}
	
	//Подберём саблю
	if(isWeapons)
	{
		
		if (CheckAttribute(chr, "CityType") && chr.CityType == "soldier")
		{   // у солдат в городе свои сабли
			blade = LAi_Soldier_EquipBlade();
		}
		else
		{
            blade = LAi_NPC_EquipBladeSelection(chr);
		}
		
		DeleteAttribute(chr, "items");
		
		blade = GetGeneratedItem(blade); // Генерим оружие
		
		GiveItem2Character(chr, blade);
		EquipCharacterByItem(chr, blade);
		// boal -->
		if(rand(1500) < MOD_SKILL_ENEMY_RATE*100)
        {
		   TakeNItems(chr, "potion1", rand(makeint(rank/(11-MOD_SKILL_ENEMY_RATE) +0.5))); // даю меньше
		}
		// boal <--
	}
    else
    {
		isGun = false;
	}
	// boal выдаем пистоль -->
	if(isGun)
	{
		if(rand(1000) < MOD_SKILL_ENEMY_RATE * sti(chr.rank) * 8)
		{
			gun = LAi_NPC_EquipGunSelection(chr);
			
			GiveItem2Character(chr, gun);
	    	EquipCharacterByItem(chr, gun);

			LAi_SetCharacterDefaultBulletType(chr, "pistol");
		}
	}
	// boal выдаем пистоль <--
}

void LAi_NPC_MushketerEquip(ref chr)
{
	string sMush 	= "mushket_matchlock";
	string sBullet 	= "bullet";

	while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
    }	
	GiveItem2Character(chr, "unarmed");
	EquipCharacterbyItem(chr, "unarmed");
	
	if(CheckAttribute(chr, "MushketBulletType"))	sBullet = chr.MushketBulletType;
	if(CheckAttribute(chr, "MushketType")) 			sMush 	= chr.MushketType;
	else
	{
		if(CheckAttribute(chr, "model"))
		{
			if(HasSubStr(chr.model, "mush_eng_") || HasSubStr(chr.model, "mush_hol_"))
			{
				if(rand(1) == 0) sMush = "mushket_Bayonet";
				else			 sMush = "mushket_matchlock";
			}
			if(HasSubStr(chr.model, "mush_fra_") || HasSubStr(chr.model, "mush_spa_"))
			{
				if(rand(1) == 0) sMush = "mushket_matchlock";
				else			 sMush = "mushket_Arquebus";
			}
		}
	}
	
	GiveItem2Character(chr, sMush);
	EquipCharacterbyItem(chr, sMush);
	
	switch (sMush)
	{
		case "mushket_matchlock":
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, "musket", sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr, "musket");
		break;
		
		case "mushket_Bayonet":
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, "musket", sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr, "musket");
		break;
		
		case "mushket_Arquebus":
			AddItems(chr, "grapeshot", 	50);
			AddItems(chr, "gunpowder", 	50);
			LAi_SetCharacterUseBullet(chr, "musket", "grapeshot");
		break;
		
		case "mushket_Portuguese":
			AddItems(chr, "grapeshot", 	50);
			AddItems(chr, "gunpowder", 	50);
			LAi_SetCharacterUseBullet(chr, "musket", "grapeshot");
		break;
		
		case "mushket_sklopetta":
			AddItems(chr, "grenade", 	50);
			AddItems(chr, "petard", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, "musket", sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr, "musket");
		break;
		
		case "mushket_Shtuzer":
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, "musket", sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr, "musket");
		break;
		
		case "mushket_2x2":
			AddItems(chr, "cartridge", 	50);
			AddItems(chr, "bullet", 	50);
			AddItems(chr, "gunpowder", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, "musket", sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr, "musket");
		break;
		
		case "mushket_Bombard":
			AddItems(chr, "grenade", 	50);
			AddItems(chr, "petard", 	50);
			if(CheckAttribute(chr, "MushketType") && 
			   CheckAttribute(chr, "MushketBulletType")) 	LAi_SetCharacterUseBullet(chr, "musket", sBullet);
			else											LAi_SetCharacterDefaultBulletType(chr, "musket");
		break;
	}
	
	chr.isMusketer = true;
	chr.isMusketer.weapon = true; // Jason: а пули с порохом кто удалять будет? И вообще, что за муть - менять мушкет при каждой установке типа?
	if (!CheckAttribute(chr, "MusketerDistance")) chr.MusketerDistance = 10.0 + frand(10.0);
}

string LAi_NPC_EquipBladeSelection(ref chr)
{
    string sType;
	string blade;
	
	if(CheckAttribute(chr, "PhantomType"))
	{
		sType = chr.PhantomType;
		switch(sType)
		{
			case "pofficer":	blade = SelectGeneratedItem(TGT_SOLDIER, "", "", "");	break;
			case "pirate":		blade = SelectGeneratedItem(TGT_PIRATE, "", "", "");	break;
			case "citizen":		blade = SelectGeneratedItem(TGT_CITIZEN, "", "", "");	break;		
			case "soldier":		blade = SelectGeneratedItem(TGT_SOLDIER, "", "", "");	break;
			case "noble":		blade = SelectGeneratedItem(TGT_OFFICER, "", "", "");	break;
			case "sailor":		blade = SelectGeneratedItem(TGT_SOLDIER, "", "", "");	break;
		}
	}
	else blade = SelectGeneratedItem(TGT_SOLDIER, "", "", "");	
	return blade;
}

string LAi_NPC_EquipGunSelection(ref chr)
{
    string sType;
	string gun;
	
	if(CheckAttribute(chr, "PhantomType"))
	{
		sType = chr.PhantomType;
		switch(sType)
		{
			case "pofficer":	gun = SelectGun(TGT_SOLDIER, "");	break;
			case "pirate":		gun = SelectGun(TGT_SOLDIER, "");	break;
			case "citizen":		gun = SelectGun(TGT_SOLDIER, "");	break;	
			case "soldier":		gun = SelectGun(TGT_SOLDIER, "");	break;
			case "noble":		gun = SelectGun(TGT_SOLDIER, "");	break;
			case "sailor":		gun = SelectGun(TGT_SOLDIER, "");	break;
		}
	}
	else gun = SelectGun(TGT_SOLDIER, "");	
	return gun;
}

// казенная сабля солдат в городе
string LAi_Soldier_EquipBlade()
{
	return SelectGeneratedItem(TGT_SOLDIER, "", "", "");
}

// new perks generator, more specialized (Gray 12.11.2004)
void LAi_NPC_EquipPerk(ref chr, string kind)
{
	int  i;
    int  rest;
    int  PerkTemplates[PERK_TEMPLATE_LAST];
    int  NumPerks[PERK_TEMPLATE_LAST];
    int  rank = sti(chr.rank);
    bool ok;

	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		PerkTemplates[i] = 0;
	}

	switch (kind)        // to_do
	{
		 case "boatswain" :
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0 + 1);
			PerkTemplates[PERK_TEMPLATE_GRAPPLING]   = makeint((rank + rand(3)) / 6.0);
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(3)) / 5.0);
		break;

		case "cannoner" :
			PerkTemplates[PERK_TEMPLATE_CANNONS] = makeint((rank + rand(2)) / 3.0 + 1);
			PerkTemplates[PERK_TEMPLATE_MELEE]   = makeint((rank + rand(3)) / 6.0);
		break;

		case "treasurer" :
			PerkTemplates[PERK_TEMPLATE_SPEECHCRAFT] = makeint((rank + rand(1)) / 5.0 + 1);
			PerkTemplates[PERK_TEMPLATE_REPAIR]      = makeint((rank + rand(3)) / 5.0);
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(3)) / 6.0);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0 + 1);
		break;

		case "navigator" :
			PerkTemplates[PERK_TEMPLATE_SAILING]     = makeint((rank + rand(2)) / 4.0 + 1);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(3)) / 6.0);
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(3)) / 6.0);
		break;

		case "fighter" :
			PerkTemplates[PERK_TEMPLATE_MELEE] = makeint((rank + rand(1)) / 2.0 + 1);
		break;

		case "fantom" : 
			PerkTemplates[PERK_TEMPLATE_MELEE]       = makeint((rank + rand(4)) / 4.0);
			PerkTemplates[PERK_TEMPLATE_SAILING]     = makeint((rank + rand(5)) / 8.0);
			PerkTemplates[PERK_TEMPLATE_GRAPPLING]   = makeint((rank + rand(7)) / 9.0);
			PerkTemplates[PERK_TEMPLATE_REPAIR]      = makeint((rank + rand(10)) / 15.0);
			PerkTemplates[PERK_TEMPLATE_CANNONS]     = makeint((rank + rand(2)) / 5.0);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0);
		break;
    } 

	NumPerks[PERK_TEMPLATE_SHIPDEFENCE] = 3;
	NumPerks[PERK_TEMPLATE_REPAIR]      = 4;
	NumPerks[PERK_TEMPLATE_CANNONS]     = 8;
	NumPerks[PERK_TEMPLATE_SPEECHCRAFT] = 2;
	NumPerks[PERK_TEMPLATE_SAILING]     = 8;
	NumPerks[PERK_TEMPLATE_GRAPPLING]   = 5;
	NumPerks[PERK_TEMPLATE_MELEE]       = 12;
	NumPerks[PERK_TEMPLATE_PERSONAL]    = 4;

	rest = 0;
	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		if (PerkTemplates[i] > NumPerks[i])
		{
			PerkTemplates[i] = NumPerks[i];
		}
		rest += NumPerks[i];
	}

	if (rest > rank)
	{
		rest = rank;
	}
	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		rest = rest - PerkTemplates[i];
	}

	// the rest perks (like half usually) distributed randomly among templates
	while (rest > 0)
	{
		i = rand(PERK_TEMPLATE_LAST - 1);
		if (PerkTemplates[i] < NumPerks[i])
		{
			PerkTemplates[i] = PerkTemplates[i] + 1;
			rest--;
		}
	}
}

bool isMushket(string name)
{
	if(HasSubStr(name, "mushket")) return true;
	return false;
}

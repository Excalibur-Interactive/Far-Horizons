void extrnInitPerks()
{
    DeleteAttribute(&ChrPerksList, "list");
    // NPCOnly - только НПС  PlayerOnly - только ГГ, Hiden - скрыт для всех, кодерские трюки Боссов-НПС
    // navigator  boatswain  cannoner doctor carpenter treasurer fighter  - офицеры  для  .OfficerType
    
    // Rebbebion, обновлённая система способностей персонажа
	// №1. Ветка фехтования
	ChrPerksList.list.CriticalHit.descr = "perkCriticalHit";
    ChrPerksList.list.CriticalHit.BaseType = "self";
	
	ChrPerksList.list.Sliding.descr = "perkSliding";
	ChrPerksList.list.Sliding.condition.CriticalHit = true;
	ChrPerksList.list.Sliding.BaseType = "self";
	
	ChrPerksList.list.HardHitter.descr = "perkHardHitter";
	ChrPerksList.list.HardHitter.condition.Sliding = true;
	ChrPerksList.list.HardHitter.BaseType = "self";
	
	ChrPerksList.list.Tireless.descr = "perkTireless";
	ChrPerksList.list.Tireless.condition.Sliding = true;
	ChrPerksList.list.Tireless.BaseType = "self";
	
	ChrPerksList.list.BladeDancer.descr = "perkBladeDancer";
	ChrPerksList.list.BladeDancer.condition.Sliding = true;
	ChrPerksList.list.BladeDancer.BaseType = "self";
	
	ChrPerksList.list.HandOfGod.descr = "perkHandOfGod";
	ChrPerksList.list.HandOfGod.condition.HardHitter = true;
	ChrPerksList.list.HandOfGod.BaseType = "self";
	
	ChrPerksList.list.Crusader.descr = "perkCrusader";
	ChrPerksList.list.Crusader.condition.HardHitter = true;
	ChrPerksList.list.Crusader.condition.Tireless = true;
	ChrPerksList.list.Crusader.condition.BladeDancer = true;
	ChrPerksList.list.Crusader.condition.HandOfGod = true;
	ChrPerksList.list.Crusader.BaseType = "self";
	
	// №2. Ветка защиты
	ChrPerksList.list.BasicDefense.descr = "perkBasicDefense";
    ChrPerksList.list.BasicDefense.BaseType = "self";
	
	ChrPerksList.list.StrengthOfSpirit.descr = "perkStrengthOfSpirit";
	ChrPerksList.list.StrengthOfSpirit.condition.BasicDefense = true;
    ChrPerksList.list.StrengthOfSpirit.BaseType = "self";
	
	ChrPerksList.list.Shipwrecker.descr = "perkShipwrecker";
	ChrPerksList.list.Shipwrecker.condition.StrengthOfSpirit = true;
    ChrPerksList.list.Shipwrecker.BaseType = "self";
	
	ChrPerksList.list.Knight.descr = "perkKnight";
	ChrPerksList.list.Knight.condition.StrengthOfSpirit = true;
    ChrPerksList.list.Knight.BaseType = "self";
	
	ChrPerksList.list.RoyalHealth.descr = "perkRoyalHealth";
	ChrPerksList.list.RoyalHealth.condition.Knight = true;
    ChrPerksList.list.RoyalHealth.BaseType = "self";
	
	ChrPerksList.list.Viking.descr = "perkViking";
	ChrPerksList.list.Viking.condition.StrengthOfSpirit = true;
    ChrPerksList.list.Viking.BaseType = "self";
	
	ChrPerksList.list.Paladin.descr = "perkPaladin";
	ChrPerksList.list.Paladin.condition.Knight = true;
	ChrPerksList.list.Paladin.condition.RoyalHealth = true;
	ChrPerksList.list.Paladin.condition.Viking = true;
    ChrPerksList.list.Paladin.BaseType = "self";
	
	// №3. Ветка стрельбы
	ChrPerksList.list.Musketeer.descr = "perkMusketeer";
    ChrPerksList.list.Musketeer.BaseType = "self";
	
	ChrPerksList.list.Perfectionist.descr = "perkPerfectionist";
	ChrPerksList.list.Perfectionist.condition.Musketeer = true;
    ChrPerksList.list.Perfectionist.BaseType = "self";
	
	ChrPerksList.list.Breter.descr = "perkBreter";
	ChrPerksList.list.Breter.condition.Musketeer = true;
    ChrPerksList.list.Breter.BaseType = "self";
	
	ChrPerksList.list.ThriftyJaeger.descr = "perkThriftyJaeger";
	ChrPerksList.list.ThriftyJaeger.condition.Breter = true;
    ChrPerksList.list.ThriftyJaeger.BaseType = "self";
	
	ChrPerksList.list.Shooter.descr = "perkShooter";
	ChrPerksList.list.Shooter.condition.Breter = true;
    ChrPerksList.list.Shooter.BaseType = "self";
	
	// №4. Ветка скрытности
	ChrPerksList.list.Spy.descr = "perkSpy";
    ChrPerksList.list.Spy.BaseType = "self";
	
	ChrPerksList.list.Shadow.descr = "perkShadow";
	ChrPerksList.list.Shadow.condition.Spy = true;
    ChrPerksList.list.Shadow.BaseType = "self";
	
	ChrPerksList.list.Cardsharper.descr = "perkCardsharper";
    ChrPerksList.list.Cardsharper.BaseType = "self";
	
	ChrPerksList.list.Bribe.descr = "perkBribe";
	ChrPerksList.list.Bribe.condition.Shadow = true;
    ChrPerksList.list.Bribe.BaseType = "self";
	
	// (OOAS это one's own among strangers, т.е свой среди чужих)
	ChrPerksList.list.OOAS.descr = "perkOOAS";
	ChrPerksList.list.OOAS.condition.Shadow = true;
    ChrPerksList.list.OOAS.BaseType = "self";
	
	ChrPerksList.list.FearsomeLook.descr = "perkFearsomeLook";
	ChrPerksList.list.FearsomeLook.condition.OOAS = true;
    ChrPerksList.list.FearsomeLook.BaseType = "self";
	
	// (AGOS это a game of shadows, т.е игра теней)
	ChrPerksList.list.AGOS.descr = "perkAGOS";
	ChrPerksList.list.AGOS.condition.Cardsharper = true;
	ChrPerksList.list.AGOS.condition.Bribe = true;
	ChrPerksList.list.AGOS.condition.FearsomeLook = true;
    ChrPerksList.list.AGOS.BaseType = "self";
	
	// №5. Ветка взлома
	ChrPerksList.list.Safecracker.descr = "perkSafecracker";
    ChrPerksList.list.Safecracker.BaseType = "self";
	
	ChrPerksList.list.SkilledThief.descr = "perkSkilledThief";
	ChrPerksList.list.SkilledThief.condition.Safecracker = true;
    ChrPerksList.list.SkilledThief.BaseType = "self";
	
	ChrPerksList.list.TreasureHunter.descr = "perkTreasureHunter";
	ChrPerksList.list.TreasureHunter.condition.SkilledThief = true;
    ChrPerksList.list.TreasureHunter.BaseType = "self";
	
	ChrPerksList.list.BreakAndSilence.descr = "perkBreakAndSilence";
	ChrPerksList.list.BreakAndSilence.condition.SkilledThief = true;
    ChrPerksList.list.BreakAndSilence.BaseType = "self";
	
	ChrPerksList.list.Lockpicking.descr = "perkLockpicking";
	ChrPerksList.list.Lockpicking.condition.SkilledThief = true;
	ChrPerksList.list.Lockpicking.condition.TreasureHunter = true;
	ChrPerksList.list.Lockpicking.condition.BreakAndSilence = true;
    ChrPerksList.list.Lockpicking.BaseType = "self";
	
	// №6. Ветка алхимии
	ChrPerksList.list.BeginnerAlchemist.descr = "perkBeginnerAlchemist";
    ChrPerksList.list.BeginnerAlchemist.BaseType = "self";
	
	ChrPerksList.list.SkilledAlchemist.descr = "perkSkilledAlchemist";
	ChrPerksList.list.SkilledAlchemist.condition.BeginnerAlchemist = true;
    ChrPerksList.list.SkilledAlchemist.BaseType = "self";
	
	ChrPerksList.list.Poisoner.descr = "perkPoisoner";
	ChrPerksList.list.Poisoner.condition.BeginnerAlchemist = true;
	ChrPerksList.list.Poisoner.condition.SkilledAlchemist = true;
    ChrPerksList.list.Poisoner.BaseType = "self";
	
	ChrPerksList.list.Pyrotechnician.descr = "perkPyrotechnician";
	ChrPerksList.list.Pyrotechnician.condition.BeginnerAlchemist = true;
    ChrPerksList.list.Pyrotechnician.BaseType = "self";
	
	ChrPerksList.list.MasterOfAlchemy.descr = "perkMasterOfAlchemy";
	ChrPerksList.list.MasterOfAlchemy.condition.BeginnerAlchemist = true;
    ChrPerksList.list.MasterOfAlchemy.BaseType = "self";
	
	ChrPerksList.list.WastefulCreator.descr = "perkWastefulCreator";
	ChrPerksList.list.WastefulCreator.condition.MasterOfAlchemy = true;
    ChrPerksList.list.WastefulCreator.BaseType = "self";
	
	ChrPerksList.list.SnakeSkin.descr = "perkSnakeSkin";
	ChrPerksList.list.SnakeSkin.condition.Poisoner = true;
	ChrPerksList.list.SnakeSkin.condition.MasterOfAlchemy = true;
    ChrPerksList.list.SnakeSkin.BaseType = "self";
	
	ChrPerksList.list.Grenadier.descr = "perkGrenadier";
	ChrPerksList.list.Grenadier.condition.Pyrotechnician = true;
	ChrPerksList.list.Grenadier.condition.MasterOfAlchemy = true;
    ChrPerksList.list.Grenadier.BaseType = "self";
	
	/////////////////////////  КОРАБЕЛЬНЫЕ /////////////////////////////////////
    /////////////////////////////////////////////////////////////
	/// Перки для ГГ
	/////////////////////////////////////////////////////////////
    
	//новый перк гроза морей ! //zagolski
 	ChrPerksList.list.SeaDogProfessional.descr = "perkSeaDogProfessional";
	ChrPerksList.list.SeaDogProfessional.condition.SailingProfessional = true;
	ChrPerksList.list.SeaDogProfessional.BaseType = "ship";
	ChrPerksList.list.SeaDogProfessional.PlayerOnly = true;
    
	/////////////////////////////////////////////////////////////
	/// Перки для квартирмейстер
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.Brander.descr = "perkBrander";  // квартирмейстер
	ChrPerksList.list.Brander.BaseType = "ship";
	ChrPerksList.list.Brander.OfficerType = "boatswain";

	ChrPerksList.list.Troopers.descr = "perkTroopers";  // квартирмейстер
	ChrPerksList.list.Troopers.BaseType = "ship";
	ChrPerksList.list.Troopers.OfficerType = "boatswain";
	
	ChrPerksList.list.LongRangeGrappling.descr = "perkLongRangeGrappling";  // квартирмейстер
	ChrPerksList.list.LongRangeGrappling.BaseType = "ship";
    ChrPerksList.list.LongRangeGrappling.OfficerType = "boatswain";
    
	ChrPerksList.list.GrapplingProfessional.descr = "perkGrapplingProfessional";   // квартирмейстер
	ChrPerksList.list.GrapplingProfessional.condition.LongRangeGrappling = true;
	ChrPerksList.list.GrapplingProfessional.condition.MusketsShoot = true;
	ChrPerksList.list.GrapplingProfessional.BaseType = "ship";
	ChrPerksList.list.GrapplingProfessional.OfficerType = "boatswain";
	
	ChrPerksList.list.MusketsShoot.descr = "perkMusketsShoot";     // квартирмейстер
	ChrPerksList.list.MusketsShoot.condition.CrewDamageUp = true;
	ChrPerksList.list.MusketsShoot.BaseType = "ship";
	ChrPerksList.list.MusketsShoot.OfficerType = "boatswain";

    /////////////////////////////////////////////////////////////
	/// Перки для казначе
	/////////////////////////////////////////////////////////////
	
	ChrPerksList.list.BasicCommerce.descr = "perkBasicCommerce";  // казначей
	ChrPerksList.list.BasicCommerce.BaseType = "ship";
	ChrPerksList.list.BasicCommerce.OfficerType = "treasurer";

	ChrPerksList.list.AdvancedCommerce.descr = "perkAdvancedCommerce";  // казначей
	ChrPerksList.list.AdvancedCommerce.condition.BasicCommerce = true;
	ChrPerksList.list.AdvancedCommerce.BaseType = "ship";
	ChrPerksList.list.AdvancedCommerce.OfficerType = "treasurer";

	/////////////////////////////////////////////////////////////
	/// Перки для канонир
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.FastReload.descr = "perkFastReload";  // канонир
	ChrPerksList.list.FastReload.BaseType = "ship";
	ChrPerksList.list.FastReload.OfficerType = "cannoner";

	ChrPerksList.list.ImmediateReload.descr = "perkImmediateReload";  // канонир
	ChrPerksList.list.ImmediateReload.condition.FastReload = true;
	ChrPerksList.list.ImmediateReload.TimeDelay = 300;
	ChrPerksList.list.ImmediateReload.TimeDuration = 60;
	ChrPerksList.list.ImmediateReload.BaseType = "ship";
	ChrPerksList.list.ImmediateReload.OfficerType = "cannoner";

	ChrPerksList.list.HullDamageUp.descr = "perkHullDamageUp";   // канонир
	ChrPerksList.list.HullDamageUp.BaseType = "ship";
	ChrPerksList.list.HullDamageUp.OfficerType = "cannoner";

	ChrPerksList.list.SailsDamageUp.descr = "perkSailsDamageUp";  // канонир
	ChrPerksList.list.SailsDamageUp.BaseType = "ship";
	ChrPerksList.list.SailsDamageUp.OfficerType = "cannoner";

	ChrPerksList.list.CrewDamageUp.descr = "perkCrewDamageUp";   // канонир
	ChrPerksList.list.CrewDamageUp.BaseType = "ship";
	ChrPerksList.list.CrewDamageUp.OfficerType = "cannoner";

	ChrPerksList.list.CriticalShoot.descr = "perkCriticalShoot";  // канонир
	ChrPerksList.list.CriticalShoot.condition.HullDamageUp = true;
	ChrPerksList.list.CriticalShoot.condition.SailsDamageUp = true;
	ChrPerksList.list.CriticalShoot.condition.CrewDamageUp = true;
	ChrPerksList.list.CriticalShoot.BaseType = "ship";
	ChrPerksList.list.CriticalShoot.OfficerType = "cannoner";

	ChrPerksList.list.LongRangeShoot.descr = "perkLongRangeShoot";   // канонир
	ChrPerksList.list.LongRangeShoot.BaseType = "ship";
	ChrPerksList.list.LongRangeShoot.OfficerType = "cannoner";

	ChrPerksList.list.CannonProfessional.descr = "perkCannonProfessional";  // канонир
	ChrPerksList.list.CannonProfessional.condition.CriticalShoot = true;
	ChrPerksList.list.CannonProfessional.condition.LongRangeShoot = true;
	ChrPerksList.list.CannonProfessional.condition.FastReload = true;
	ChrPerksList.list.CannonProfessional.BaseType = "ship";
	ChrPerksList.list.CannonProfessional.OfficerType = "cannoner";



	// Ship Control Skills Group
	//================================================================
	/////////////////////////////////////////////////////////////
	/// Перки для плотника
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.Carpenter.descr = "perkCarpenter";
    ChrPerksList.list.Carpenter.OfficerType = "carpenter";
    ChrPerksList.list.Carpenter.BaseType = "ship";
    
	ChrPerksList.list.Builder.descr = "perkBuilder";
	ChrPerksList.list.Builder.condition.Carpenter = true;
    ChrPerksList.list.Builder.OfficerType = "carpenter";
    ChrPerksList.list.Builder.BaseType = "ship";
    
	ChrPerksList.list.LightRepair.descr = "perkLightRepair";   // плотник
	ChrPerksList.list.LightRepair.TimeDelay = 240;
	ChrPerksList.list.LightRepair.TimeDuration = 60;
	ChrPerksList.list.LightRepair.BaseType = "ship";
	ChrPerksList.list.LightRepair.OfficerType = "carpenter";

    if (MOD_SKILL_ENEMY_RATE < 10)
    {
    	ChrPerksList.list.InstantRepair.descr = "perkInstantRepair";    // плотник
    	ChrPerksList.list.InstantRepair.condition.LightRepair = true;
    	ChrPerksList.list.InstantRepair.condition.Carpenter = true;
    	ChrPerksList.list.InstantRepair.TimeDelay = 240;// boal 13.02.2004
    	ChrPerksList.list.InstantRepair.TimeDuration = 30;
    	ChrPerksList.list.InstantRepair.BaseType = "ship";
    	ChrPerksList.list.InstantRepair.OfficerType = "carpenter";
    }
    
    ChrPerksList.list.BasicBattleState.descr = "perkBasicBattleState";   // плотник разделить с доктором корпус и команду
    ChrPerksList.list.BasicBattleState.OfficerType = "carpenter";
	ChrPerksList.list.BasicBattleState.BaseType = "ship";

	ChrPerksList.list.AdvancedBattleState.descr = "perkAdvancedBattleState";
	ChrPerksList.list.AdvancedBattleState.condition.BasicBattleState = true;
	ChrPerksList.list.AdvancedBattleState.OfficerType = "carpenter";
	ChrPerksList.list.AdvancedBattleState.BaseType = "ship";

	ChrPerksList.list.ShipDefenseProfessional.descr = "perkShipDefenseProfessional";
	ChrPerksList.list.ShipDefenseProfessional.condition.AdvancedBattleState = true;
	ChrPerksList.list.ShipDefenseProfessional.BaseType = "ship";
	ChrPerksList.list.ShipDefenseProfessional.OfficerType = "carpenter";
    /////////////////////////////////////////////////////////////
	/// Перки для штурман
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.ShipSpeedUp.descr = "perkShipSpeedUp";  // штурман
	ChrPerksList.list.ShipSpeedUp.BaseType = "ship";
	ChrPerksList.list.ShipSpeedUp.OfficerType = "navigator";

	ChrPerksList.list.ShipTurnRateUp.descr = "perkShipTurnRateUp";    // штурман
	ChrPerksList.list.ShipTurnRateUp.BaseType = "ship";
	ChrPerksList.list.ShipTurnRateUp.OfficerType = "navigator";

	ChrPerksList.list.StormProfessional.descr = "perkStormProfessional";   // штурман
	ChrPerksList.list.StormProfessional.BaseType = "ship";
	ChrPerksList.list.StormProfessional.OfficerType = "navigator";

	ChrPerksList.list.WindCatcher.descr = "perkWindCatcher";
	ChrPerksList.list.WindCatcher.BaseType = "ship";
	ChrPerksList.list.WindCatcher.OfficerType = "navigator";

	ChrPerksList.list.SailsMan.descr = "perkSailsMan";
	ChrPerksList.list.SailsMan.BaseType = "ship";
	ChrPerksList.list.SailsMan.OfficerType = "navigator";
	
	ChrPerksList.list.Turn180.descr = "perkTurn180";           // штурман
	ChrPerksList.list.Turn180.condition.ShipSpeedUp = true;
	ChrPerksList.list.Turn180.condition.ShipTurnRateUp = true;
	ChrPerksList.list.Turn180.condition.WindCatcher = true;
	ChrPerksList.list.Turn180.TimeDelay = 240;
	ChrPerksList.list.Turn180.TimeDuration = 60;
	ChrPerksList.list.Turn180.BaseType = "ship";
	ChrPerksList.list.Turn180.OfficerType = "navigator";

	ChrPerksList.list.SailingProfessional.descr = "perkSailingProfessional";   // штурман
	ChrPerksList.list.SailingProfessional.condition.SailsMan = true;
	ChrPerksList.list.SailingProfessional.condition.StormProfessional = true;
	ChrPerksList.list.SailingProfessional.condition.Turn180 = true;
	ChrPerksList.list.SailingProfessional.BaseType = "ship";
	ChrPerksList.list.SailingProfessional.OfficerType = "navigator";

    // список из ВМЛ <--

	/////////////////////////////////////////////////////////////
	/// Перки для доктора
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.Doctor1.descr = "perkDoctor1";
    ChrPerksList.list.Doctor1.BaseType = "ship";
	ChrPerksList.list.Doctor1.OfficerType = "doctor";
	
	ChrPerksList.list.Doctor2.descr = "perkDoctor2";
	ChrPerksList.list.Doctor2.condition.Doctor1 = true;
    ChrPerksList.list.Doctor2.BaseType = "ship";
	ChrPerksList.list.Doctor2.OfficerType = "doctor";

	/////////////////////////////////////////////////////////////
	/// Скрытые перки
	/////////////////////////////////////////////////////////////
	
	// скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
	ChrPerksList.list.Energaiser.descr = "perkEnergaiser";
	ChrPerksList.list.Energaiser.Hiden = true;
	
	// скрытый перк дает бонус в 5% к базовой скорости корабля при наличии всех карт
	ChrPerksList.list.MapMaker.descr = "perkMapMaker";
	ChrPerksList.list.MapMaker.PlayerOnly = true;
	ChrPerksList.list.MapMaker.Hiden = true;
}
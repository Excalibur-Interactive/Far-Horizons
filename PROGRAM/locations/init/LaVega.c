
int LocationInitLaVega(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Порт Ла Веги
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_port";
	locations[n].id.label = "LaVega Port";
	locations[n].image = "loading\outside\harbor3.tga";
	locations[n].worldmap = "LaVega_port";
	locations[n].citizens = true;
	locations[n].MaxCitizensQuantity = 3;
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\LaVega\Port";
	Locations[n].models.always.port = "LaVega_Port";
	Locations[n].models.always.portseabed = "LaVega_Port_sb";
	Locations[n].models.always.locators = "LaVega_Port_Locators";

	Locations[n].models.always.grassPatch = "LaVega_Port_Grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "LaVega_Port_tortuga_back";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "LaVega_Port_patch";
	//Night
	locations[n].models.night.charactersPatch = "LaVega_Port_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Hispaniola1";
	locations[n].reload.l2.emerge = "reload_4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 5.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города Ла-Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	Locations[n].filespath.models = "locations\LaVega\Exit";
	Locations[n].models.always.Exit = "LaVega_ExitTown";	
	Locations[n].models.always.locators = "LaVega_ExitTown_locators";		
	Locations[n].models.always.grassPatch = "LaVega_ExitTown_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "LaVega_ExitTown_patch";
	locations[n].models.day.fonars = "LaVega_ExitTown_fd";
	//Night
	locations[n].models.night.charactersPatch = "LaVega_ExitTown_patch";
	locations[n].models.night.fonars = "LaVega_ExitTown_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_port";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "LaVega Port";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LaVega_town";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	locations[n].locators_radius.reload.reload1_back = 2.0;

    Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Hispaniola_Jungle_03";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3 = 1.8;
	
	Locations[n].reload.l4.name = "reload4";
	Locations[n].reload.l4.go = "LaVega_JungleHouse";
	Locations[n].reload.l4.emerge = "reload2";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "House";
	locations[n].reload.l4.disable = 1;//закрыто
	
	/* Locations[n].reload.l5.name = "Tower_up";
	Locations[n].reload.l5.go = "LaVega_ExitTown";
	Locations[n].reload.l5.emerge = "Tower_down";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "ToTower";
	
	Locations[n].reload.l51.name = "Tower_down";
	Locations[n].reload.l51.go = "LaVega_ExitTown";
	Locations[n].reload.l51.emerge = "Tower_up";
	Locations[n].reload.l51.autoreload = "0";
	Locations[n].reload.l51.label = "FromTower"; */
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ла-Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_town";
	locations[n].id.label = "Street";
	locations[n].image = "loading\towns\pearl1.tga";
	locations[n].worldmap = "LaVega_town";
	locations[n].citizens = true;
	locations[n].soldiers = true;	
	//locations[n].carrier = true;	
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	Locations[n].filespath.models = "locations\LaVega\Town";
	Locations[n].models.always.Town = "LaVega_Town";	
	Locations[n].models.always.locators = "LaVega_Town_locators";		
	Locations[n].models.always.grassPatch = "LaVega_Town_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	
	Locations[n].models.always.lians = "LaVega_Town_lians";
	
	Locations[n].models.always.Waterfall1 = "LaVega_Town_waterfall";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	
	Locations[n].models.always.Water = "LaVega_Town_Water";
	Locations[n].models.always.Water.uvslide.v0 = 0.00;
    Locations[n].models.always.Water.uvslide.v1 = 0.0;
    Locations[n].models.always.Water.uvslide.u0 = -0.005;
    Locations[n].models.always.Water.uvslide.u1 = 0.0;
	Locations[n].models.always.Water.tech = "LocationWaterFall";
	
	//Day
	locations[n].models.day.charactersPatch = "LaVega_Town_patch";
	locations[n].models.day.fonars = "LaVega_Town_fd";
	//Night
	locations[n].models.night.charactersPatch = "LaVega_Town_patch";
	locations[n].models.night.fonars = "LaVega_Town_fn";	

	//RTX On	
	Locations[n].models.night.vlight = "LaVega_Town_RTX";
	Locations[n].models.night.vlight.uvslide.u0 = 0.0;
	Locations[n].models.night.vlight.uvslide.u1 = -0.05;
	Locations[n].models.night.vlight.uvslide.v0 = 0.0;
    Locations[n].models.night.vlight.uvslide.v1 = 0.0;
	Locations[n].models.night.vlight.tech = "LocationWaterFall";
	Locations[n].models.night.vlight.level = 99950;
	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map

	Locations[n].reload.l1.name = "reload1"; 
	Locations[n].reload.l1.go = "LaVega_ExitTown";
	Locations[n].reload.l1.emerge = "reload2";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1 = 1.8;

	locations[n].reload.l2.name = "reload_hut2";
	locations[n].reload.l2.go = "CommonHut";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";
	
	locations[n].reload.l3.name = "reload_hut3";
	locations[n].reload.l3.go = "CommonRoom_MH3";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "House";

	locations[n].reload.l4.name = "reload_barn2";
	locations[n].reload.l4.go = "Common_barn2";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "shack";

	Locations[n].reload.l5.name = "reload5";
	Locations[n].reload.l5.go = "LaVega_tavern";
	Locations[n].reload.l5.emerge = "reload1_back";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "Tavern";
	
	Locations[n].reload.l51.name = "reload5_1";
	Locations[n].reload.l51.go = "LaVega_tavern";
	Locations[n].reload.l51.emerge = "reload4";
	Locations[n].reload.l51.autoreload = "0";
	Locations[n].reload.l51.label = "Tavern";

	Locations[n].reload.l6.name = "reload6";
	Locations[n].reload.l6.go = "LaVega_townhall";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Townhall";
	Locations[n].reload.l6.disable = 1;//закрыто
	//Locations[n].reload.l6.close_for_night = 1;

	Locations[n].reload.l8.name = "reload8";
	Locations[n].reload.l8.go = "LaVega_store";
	Locations[n].reload.l8.emerge = "reload1";
	Locations[n].reload.l8.autoreload = "0";
	Locations[n].reload.l8.label = "Store";
	Locations[n].reload.l8.close_for_night = 1;
	
	Locations[n].reload.l9.name = "Reload_FlHut1";
	Locations[n].reload.l9.go = "LaVega_FlamanHut";
	Locations[n].reload.l9.emerge = "reload1";
	Locations[n].reload.l9.autoreload = "0";
	Locations[n].reload.l9.label = "house";
	Locations[n].reload.l9.close_for_night = 1;
	
	locations[n].reload.l10.name = "reload_barn1";
	locations[n].reload.l10.go = "LaVega_barn1";
	locations[n].reload.l10.emerge = "reload2";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "shack";
	
    n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Ла-Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "LaVega_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern02\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "LaVega";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.tavern = "tavern02";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "tavern02_locators";
	locations[n].models.always.window = "tavern02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern02_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
    //Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LaVega_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но свљзку сделаем длљ квестовых нужд.

    ////////////////////////==> подсобка таверны
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "CommonRoom_MH3";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "LaVega_town";
	locations[n].reload.l4.emerge = "reload5_1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Ла-Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_tavern";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Ла-Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop.tga";
	locations[n].filespath.models = "locations\inside\Store04\";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.store = "Store04";
	locations[n].models.always.locators = "Store04_locators";
	locations[n].models.always.window = "Store04_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Store04_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store04_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload8"; 
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
/* 
    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room"; */
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция Ла-Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\pirateresidence";
	locations[n].models.always.house = "ResP";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "ResP_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.locators = "ResP_l";
	locations[n].models.day.charactersPatch = "ResP_p";
	//Night
	locations[n].models.night.locators = "ResP_l_n";
	locations[n].models.night.charactersPatch = "ResP_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].box1.QuestClosed = true;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////
	/////Дом за воротами
	//////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_JungleHouse";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\hut.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Hut_locators";
	locations[n].models.always.tavern = "Hut";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map.
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "LaVega_ExitTown";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Jungle";
	
	locations[n].box1.QuestClosed = true;
	n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_FlamanHut";
	locations[n].id.label = "Shack";
	locations[n].image = "loading\inside\mediumhouse10.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].islandId = "Hispaniola1";
	locations[n].fastreload = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	locations[n].filespath.models = "Locations\Inside\FlamanHut_Inside";
	locations[n].models.always.room = "FlamanHut_Inside";
	locations[n].models.always.room.level = 65538;
	locations[n].models.always.locators = "FlamanHut_Inside_locators";

	locations[n].models.always.windows = "FlamanHut_Inside_windows";
	locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	//Day
	locations[n].models.day.charactersPatch = "FlamanHut_Inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "FlamanHut_Inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_Town";
	locations[n].reload.l1.emerge = "Reload_FlHut1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_barn1";
	locations[n].filespath.models = "locations\inside\barn1";
	locations[n].id.label = "Shack";
	locations[n].image = "loading\inside\hut.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].islandId = "Hispaniola1";
	locations[n].fastreload = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].models.always.locators = "barn1_locators";
	locations[n].models.always.tavern = "barn1";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "barn1_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "barn1_patch";
	//Night
	locations[n].models.night.charactersPatch = "barn1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "LaVega_Town";
	locations[n].reload.l1.emerge = "reload_barn1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	return n;
}
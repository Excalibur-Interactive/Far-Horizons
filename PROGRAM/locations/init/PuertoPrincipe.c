int LocationInitPuertoPrincipe(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Баракоа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "PuertoPrincipe_town";
    locations[n].id.label = "Street";
    locations[n].image = "loading\towns\pearl1.tga";
    locations[n].worldmap = "PuertoPrincipe_town";
    locations[n].citizens = true;
    locations[n].soldiers = true;
    //Town sack
    locations[n].townsack = "PuertoPrincipe";
    //Sound
    locations[n].type = "town";
    locations[n].fastreload = "PuertoPrincipe";
    locations[n].islandId = "Cuba";
    //Models
    //Always
    locations[n].filespath.models = "Locations\Town_PuertoPrincipe";
    locations[n].models.always.Town_PuertoPrincipe = "Town_PuertoPrincipe";
    locations[n].models.always.locators = "Town_PuertoPrincipe_locators";
    Locations[n].models.always.seabed = "Town_PuertoPrincipe_seabed";
	
	Locations[n].models.always.grassPatch = "Town_PuertoPrincipe_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

    //Day
    locations[n].models.day.charactersPatch = "Town_PuertoPrincipe_pd";
    locations[n].models.day.Rinok = "Town_PuertoPrincipe_rinok";
    locations[n].models.day.fd = "Town_PuertoPrincipe_fd";
    //Night
    locations[n].models.night.charactersPatch = "Town_PuertoPrincipe_pn";
    locations[n].models.night.fn = "Town_PuertoPrincipe_fn";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
	//Reload map
	Locations[n].reload.l1.name = "reload1"; 
	Locations[n].reload.l1.go = "Cuba1";
	Locations[n].reload.l1.emerge = "reload_4";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "sea";
	locations[n].locators_radius.reload.reload1 = 1.8;

	locations[n].reload.l2.name = "Hut3";
	locations[n].reload.l2.go = "CommonHut";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "House";

	locations[n].reload.l4.name = "Hut2";
	locations[n].reload.l4.go = "CommonRoom_MH";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "House";

	Locations[n].reload.l5.name = "reload4_back";
	Locations[n].reload.l5.go = "PuertoPrincipe_tavern";
	Locations[n].reload.l5.emerge = "reload1";
	Locations[n].reload.l5.autoreload = "0";
	Locations[n].reload.l5.label = "Tavern";

	Locations[n].reload.l6.name = "reload3_back";
	Locations[n].reload.l6.go = "PuertoPrincipe_townhall";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Townhall";
	Locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "Barn2";
	locations[n].reload.l7.go = "CommonRoom_MH2";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "House";

	Locations[n].reload.l8.name = "reload6_back";
	Locations[n].reload.l8.go = "PuertoPrincipe_store";
	Locations[n].reload.l8.emerge = "reload1";
	Locations[n].reload.l8.autoreload = "0";
	Locations[n].reload.l8.label = "Store";
	Locations[n].reload.l8.close_for_night = 1;
	
	Locations[n].reload.l9.name = "gate_back"; 
	Locations[n].reload.l9.go = "PuertoPrincipe_ExitTown";
	Locations[n].reload.l9.emerge = "reload3";
	Locations[n].reload.l9.autoreload = "0";
	Locations[n].reload.l9.label = "ExitTown";
	locations[n].locators_radius.reload.reload1 = 1.8;
	
    n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города Баракоа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PuertoPrincipe_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate" + rand(1) + ".tga";
	//Town sack
	locations[n].townsack = "PuertoPrincipe";
	//Sound
	locations[n].type = "jungle";
	locations[n].fastreload = "PuertoPrincipe";
	locations[n].islandId = "Cuba";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitY";
	Locations[n].models.always.townExit = "townExitY";
	Locations[n].models.always.townWalls = "townExitY_stucco";
	
	Locations[n].models.always.locators = "townExitY_locators";
		
	Locations[n].models.always.grassPatch = "townExitY_grass";
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
	locations[n].models.day.charactersPatch = "townExitY_patch";
	locations[n].models.day.fonars = "townExitY_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitY_patch";
	locations[n].models.night.fonars = "townExitY_fn";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Cuba_Jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	/* locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "";
	locations[n].reload.l2.emerge = "";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "?????";
	locations[n].locators_radius.reload.reload1_back = 2.0; */

    Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "PuertoPrincipe_town";
	Locations[n].reload.l3.emerge = "gate_back";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Street";
	locations[n].locators_radius.reload.reload3 = 1.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Баракоа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "PuertoPrincipe_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern04\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "PuertoPrincipe";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "PuertoPrincipe";
	locations[n].islandId = "Cuba";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern04";
	locations[n].models.always.locators = "Tavern04_locators";
	locations[n].models.always.window = "tavern04_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Tavern04_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern04_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "PuertoPrincipe_town";
	locations[n].reload.l1.emerge = "reload4"; 
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "PuertoPrincipe_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Баракоа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PuertoPrincipe_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "PuertoPrincipe";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PuertoPrincipe";
	locations[n].islandId = "Cuba";
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
	locations[n].reload.l1.go = "PuertoPrincipe_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Баракоа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PuertoPrincipe_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store01\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "PuertoPrincipe";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "PuertoPrincipe";
	locations[n].islandId = "Cuba";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\StoreSmall\";
	locations[n].models.always.locators = "StoreSmall_locators";
	locations[n].models.always.store = "StoreSmall";
	locations[n].models.always.window = "StoreSmall_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "StoreSmall_patch";
	//Night
	locations[n].models.night.charactersPatch = "StoreSmall_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PuertoPrincipe_town";
	locations[n].reload.l1.emerge = "reload6"; 
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция Баракоа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PuertoPrincipe_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "PuertoPrincipe";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "PuertoPrincipe";
 	locations[n].islandId = "Cuba";
 	// стража
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallResidence";
	locations[n].models.always.locators = "SmallResidence_locators";
	locations[n].models.always.house = "SmallResidence";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "SmallResidence_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SmallResidence_patch";
	//Night
	locations[n].models.night.charactersPatch = "SmallResidence_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PuertoPrincipe_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.item.item1 = 0.8;
	n = n + 1;

	return n;
}

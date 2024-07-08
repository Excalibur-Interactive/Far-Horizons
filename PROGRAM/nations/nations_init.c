void InitNations()
{
	ref rNation;
	//England
	makeref(rNation,Nations[ENGLAND]);
	rNation.Name = "England";
	rNation.ShortName = "Eng";
	rNation.worldMapShip = "british";
	rNation.fort = 0;  // колво фортов у нации, заполняется само в начале, методом CreateColonyCommanders
	//Location fantom models
	rNation.fantomModel.m0 = "sold_eng_1";
	rNation.fantomModel.m1 = "sold_eng_1";
	rNation.fantomModel.m2 = "sold_eng_1";
	rNation.fantomModel.m3 = "sold_eng_1";
	rNation.fantomModel.m4 = "sold_eng_1";
	rNation.fantomModel.m5 = "sold_eng_1";
	rNation.fantomModel.m6 = "sold_eng_1";
	rNation.fantomModel.m7 = "sold_eng_1";
	rNation.fantomModel.m8 = "sold_eng_1";
	rNation.fantomModel.m9 = "sold_eng_1";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_eng_1";// "off_eng_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_eng_1";// "off_eng_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_eng_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_eng_1";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_eng_1";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_eng_1";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_eng_1";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_eng_1";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_eng_1";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_eng_1";
	rNation.boardingModel.enemy.m10.ani = "man";



	//France
	makeref(rNation,Nations[FRANCE]);
	rNation.Name = "France";
	rNation.ShortName = "Fra";
	rNation.worldMapShip = "french";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "sold_fra_1";
	rNation.fantomModel.m1 = "sold_fra_1";
	rNation.fantomModel.m2 = "sold_fra_1";
	rNation.fantomModel.m3 = "sold_fra_1";
	rNation.fantomModel.m4 = "sold_fra_1";
	rNation.fantomModel.m5 = "sold_fra_1";
	rNation.fantomModel.m6 = "sold_fra_1";
	rNation.fantomModel.m7 = "sold_fra_1";
	rNation.fantomModel.m8 = "sold_fra_1";
	rNation.fantomModel.m9 = "sold_fra_1";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_fra_1"; // "off_fra_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_fra_1"; // "off_fra_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_fra_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_fra_1";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_fra_1";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_fra_1";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_fra_1";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_fra_1";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_fra_1";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_fra_1";
	rNation.boardingModel.enemy.m10.ani = "man";


	//Spain
	makeref(rNation,Nations[SPAIN]);
	rNation.Name = "Spain";
	rNation.ShortName = "Spa";
	rNation.worldMapShip = "spanish";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m1 = "sold_spa_1";
	rNation.fantomModel.m2 = "sold_spa_2";
	rNation.fantomModel.m3 = "sold_spa_3";
	rNation.fantomModel.m4 = "sold_spa_4";
	rNation.fantomModel.m5 = "sold_spa_5";
	rNation.fantomModel.m6 = "sold_spa_6";
	rNation.fantomModel.m7 = "sold_spa_7";
	rNation.fantomModel.m8 = "sold_spa_8";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_spa_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_spa_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_spa_3";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_spa_4";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_spa_5";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_spa_6";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_spa_7";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_spa_8";
	rNation.boardingModel.enemy.m8.ani = "man";

	//Pirate
	makeref(rNation,Nations[PIRATE]);
	rNation.Name = "Pirate";
	rNation.ShortName = "Pir";
	rNation.worldMapShip = "pirates";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "pirate_1";
	//Boarding models
	rNation.boardingModel.enemy.m0 = "pirate_1";
	rNation.boardingModel.enemy.m0.ani = "man";
	rNation.boardingModel.enemy.m1 = "pirate_2";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "pirate_3";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "pirate_4";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "pirate_5";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "pirate_6";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "pirate_7";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "pirate_8";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "pirate_9";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "pirate_10";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "pirate_11";
	rNation.boardingModel.enemy.m10.ani = "man";
	rNation.boardingModel.enemy.m11 = "pirate_12";
	rNation.boardingModel.enemy.m11.ani = "man";
	rNation.boardingModel.enemy.m12 = "pirate_13";
	rNation.boardingModel.enemy.m12.ani = "man";
	rNation.boardingModel.enemy.m13 = "pirate_14";
	rNation.boardingModel.enemy.m14.ani = "man";
	rNation.boardingModel.enemy.m15 = "pirate_15";
	rNation.boardingModel.enemy.m15.ani = "man";
	rNation.boardingModel.enemy.m16 = "pirate_16";
	rNation.boardingModel.enemy.m16.ani = "man";

	//Holland
	makeref(rNation,Nations[HOLLAND]);
	rNation.Name = "Holland";
	rNation.ShortName = "Dut";
	rNation.worldMapShip = "dutch";
	rNation.fort = 0;
	//Location fantom models
	rNation.fantomModel.m0 = "sold_dut_1";
	rNation.fantomModel.m1 = "sold_dut_1";
	rNation.fantomModel.m2 = "sold_dut_1";
	rNation.fantomModel.m3 = "sold_dut_1";
	rNation.fantomModel.m4 = "sold_dut_1";
	rNation.fantomModel.m5 = "sold_dut_1";
	rNation.fantomModel.m6 = "sold_dut_1";
	rNation.fantomModel.m7 = "sold_dut_1";
	rNation.fantomModel.m8 = "sold_dut_1";
	rNation.fantomModel.m9 = "sold_dut_1";
	//Boarding models
	rNation.boardingModel.enemy.m1 = "sold_dut_1"; // "Off_hol_1";
	rNation.boardingModel.enemy.m1.ani = "man";
	rNation.boardingModel.enemy.m2 = "sold_dut_1"; // "Off_hol_2";
	rNation.boardingModel.enemy.m2.ani = "man";
	rNation.boardingModel.enemy.m3 = "sold_dut_1";
	rNation.boardingModel.enemy.m3.ani = "man";
	rNation.boardingModel.enemy.m4 = "sold_dut_1";
	rNation.boardingModel.enemy.m4.ani = "man";
	rNation.boardingModel.enemy.m5 = "sold_dut_1";
	rNation.boardingModel.enemy.m5.ani = "man";
	rNation.boardingModel.enemy.m6 = "sold_dut_1";
	rNation.boardingModel.enemy.m6.ani = "man";
	rNation.boardingModel.enemy.m7 = "sold_dut_1";
	rNation.boardingModel.enemy.m7.ani = "man";
	rNation.boardingModel.enemy.m8 = "sold_dut_1";
	rNation.boardingModel.enemy.m8.ani = "man";
	rNation.boardingModel.enemy.m9 = "sold_dut_1";
	rNation.boardingModel.enemy.m9.ani = "man";
	rNation.boardingModel.enemy.m10 = "sold_dut_1";
	rNation.boardingModel.enemy.m10.ani = "man";


	//Player boarding command
	for(int i = 0; i < MAX_NATIONS; i++)
	{
		makeref(rNation,Nations[i]);
		rNation.boardingModel.player.m0 = "shipbuilder_1";
		rNation.boardingModel.player.m0.ani = "man";
		rNation.boardingModel.player.m1 = "shipbuilder_1";
		rNation.boardingModel.player.m1.ani = "man";
		rNation.boardingModel.player.m2 = "shipbuilder_1";
		rNation.boardingModel.player.m2.ani = "man";
		rNation.boardingModel.player.m3 = "shipbuilder_1";
		rNation.boardingModel.player.m3.ani = "man";
		rNation.boardingModel.player.m4 = "shipbuilder_1";
		rNation.boardingModel.player.m4.ani = "man";
		rNation.boardingModel.player.m5 = "shipbuilder_1";
		rNation.boardingModel.player.m5.ani = "man";
		rNation.boardingModel.player.m6 = "shipbuilder_1";
		rNation.boardingModel.player.m6.ani = "man";
		rNation.boardingModel.player.m7 = "shipbuilder_1";
		rNation.boardingModel.player.m7.ani = "man";
		rNation.boardingModel.player.m8 = "shipbuilder_1";
		rNation.boardingModel.player.m8.ani = "man";
		rNation.boardingModel.player.m9 = "shipbuilder_1";
		rNation.boardingModel.player.m9.ani = "man";
		//boal 06/05/05 -->
		rNation.boardingModel.merchant.m0 = "burgher_1";
		rNation.boardingModel.merchant.m0.ani = "man";
		rNation.boardingModel.merchant.m1 = "burgher_2";
		rNation.boardingModel.merchant.m1.ani = "man";
		rNation.boardingModel.merchant.m2 = "burgher_3";
		rNation.boardingModel.merchant.m2.ani = "man";
		rNation.boardingModel.merchant.m3 = "burgher_4";
		rNation.boardingModel.merchant.m3.ani = "man";
		rNation.boardingModel.merchant.m4 = "burgher_5";
		rNation.boardingModel.merchant.m4.ani = "man";
		rNation.boardingModel.merchant.m4 = "burgher_6";
		rNation.boardingModel.merchant.m4.ani = "man";
		rNation.boardingModel.merchant.m4 = "burgher_7";
		rNation.boardingModel.merchant.m4.ani = "man";
		rNation.boardingModel.merchant.m4 = "burgher_8";
		rNation.boardingModel.merchant.m4.ani = "man";
		//boal <--
	}
}


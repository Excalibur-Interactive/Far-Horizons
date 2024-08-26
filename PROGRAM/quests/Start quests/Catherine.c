void Catherine_Start()
{
	SetWDMPointXZ("LaVega_port");
	SetCharacterShipLocation(pchar, "LaVega_port"); // чтобы появлялась возле Ла Веги на глобалке
	
	pchar.Ship.Type = GenerateShipExt(SHIP_FRIGATE, true, pchar);
	pchar.Ship.name = "Бретань";
	SetBaseShipData(pchar);
	pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
	NullCharacterGoods(pchar);
	SetCharacterGoods(pchar, GOOD_BALLS, 500);
	SetCharacterGoods(pchar, GOOD_GRAPES, 500);
	SetCharacterGoods(pchar, GOOD_KNIPPELS, 500);
	SetCharacterGoods(pchar, GOOD_POWDER, 1000);
	SetCharacterGoods(pchar, GOOD_FOOD, 700);
	SetCharacterGoods(pchar, GOOD_WEAPON, 250);
	SetCharacterGoods(pchar, GOOD_MEDICAMENT, 600);
	SetCharacterGoods(pchar, GOOD_RUM, 300);
	SetCrewQuantity(pchar, 150)
	AddCrewMorale(pchar, 100);
	ChangeCrewExp(pchar, "Sailors", 100);
	ChangeCrewExp(pchar, "Cannoners", 100);
	ChangeCrewExp(pchar, "Soldiers", 100);
	
	LoadMainCharacterInFirstLocationGroup("FortFrance_ExitTown", "reload", "reload1");
}
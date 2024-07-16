
//---------------------------------------------------------------------------------------------------
// scrollimage
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithCompanionShips(string sNodeName, int iNotUsed)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "BLANK_SHIP2";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "Not Used2";

	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 0; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			isPossibleToFill = 1;
			
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;		
					}
				}
			}
		} 
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithFaces(string sNodeName, int iNotUsed, bool bCompanions, bool bPassengers)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "emptyface";

	ref refCharacter = pchar;

	int iListSize = 0;
	int cn;
	string attributeName;
	aref pRef,pRef2;
	string PsgAttrName;


	if (bCompanions){

		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 1); // companions

		for(int n= 0; n< COMPANION_MAX; n++)
		{
			attributeName = "pic" + (iListSize+1);
			cn = GetCompanionIndex(refCharacter, n);

			if(cn!= -1)
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}

	if (bPassengers){


		makearef(pRef,refCharacter.Fellows.Passengers);
		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 2); // passengers

		for(int i= 0; i< GetPassengersQuantity(refCharacter); i++)
		{
			attributeName = "pic" + (iListSize+1);
			PsgAttrName = "id"+(i+1);
			cn = sti(pRef.(PsgAttrName));

			if(cn!=-1 && !CheckAttribute(&characters[cn], "isfree"))
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}
	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.(sNodeName).NotUsed = iNotUsed;	

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
/// boal -->
void StartAboveForm(bool _pauseTime)
{
    ChangeShowIntarface();
    
	EngineLayersOffOn(true);
    if (_pauseTime)
		SetTimeScale(0.0);
	else
		SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
	
	locCameraSleep(true);
	LAi_CharacterDisableDialog(pchar);
}

void EndAboveForm(bool _pauseTime)
{
    if (_pauseTime)
    {
		SetTimeScale(1.0);
		TimeScaleCounter = 0;
	 	DelPerkFromActiveList("TimeSpeed");
	 	DeleteAttribute(pchar, "pause");
	}
	locCameraSleep(false);
	LAi_CharacterEnableDialog(pchar);
	ChangeShowIntarface();
}

void ChangeShowIntarface()
{
    if (bSeaActive && !bAbordageStarted)
    {
        if (!IsEntity(BattleInterface))
        {
            InitBattleInterface();
            StartBattleInterface();
            RefreshBattleInterface();
        }
        else DeleteBattleInterface();
    }
    else
    {
		if (!IsEntity(worldMap))
		{
			if (!bLandInterfaceStart)
	        {
	            StartBattleLandInterface();
	        }
	        else EndBattleLandInterface();
        }
    }
}
// вернуть тип по номеру скрола в ф2 персонаж
string GetOfficerTypeByNum(int nCurScrollNum)
{
    string ret = "";
    
	switch (nCurScrollNum)
	{
		case 1:
   			ret = "navigator";
		break;

		case 2:
   			ret = "boatswain";
		break;

		case 3:
   			ret = "cannoner";
		break;

		case 4:
   			ret = "doctor";
		break;

		case 5:
   			ret = "treasurer";
		break;

		case 6:
   			ret = "carpenter";
		break;

		case 7:
  			ret = "fighter";
		break;

		case 8:
   			ret = "fighter";
		break;

		case 9:
			ret = "fighter";
		break;
	}
	return ret;
}

////////////////////////////// общие методы для форм
void SetOTHERMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=5; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.85;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Rank";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Rank";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.rank);

	GameInterface.(_tabName).tr2.UserData.ID = "Life";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Life";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Life");
	GameInterface.(_tabName).tr2.td3.str = MakeInt(LAi_GetCharacterHP(_chr)) + " / " + MakeInt(LAi_GetCharacterMaxHP(_chr));

    GameInterface.(_tabName).tr3.UserData.ID = "Reputation";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Reputation";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Reputation");
	GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetReputationName(sti(_chr.reputation)));
	GameInterface.(_tabName).tr3.td3.scale = 0.78;

    GameInterface.(_tabName).tr4.UserData.ID = "Loyality";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Loyality";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Loyality");
	if (_chr.id == pchar.id)
	{
		GameInterface.(_tabName).tr4.td3.str = "-";
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.str = XI_ConvertString(GetLoyalityName(makeint(GetCharacterLoyality(_chr) * 100 / MAX_LOYALITY)));
	}
	GameInterface.(_tabName).tr4.td3.scale = 0.78;
	
	GameInterface.(_tabName).tr5.UserData.ID = "weight";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "weight";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("weight");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(GetItemsWeight(_chr), 1) + " / "+GetMaxItemsWeight(_chr);
	
	// прорисовка
	Table_UpdateWindow(_tabName);
}
void SetSPECIALMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     diff, skillVal;
    
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	row = "tr1";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

		GameInterface.(_tabName).(row).(col).fontidx = 0;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-6";
		GameInterface.(_tabName).(row).(col).str = XI_ConvertString(skillName + "T");
	}
	row = "tr2";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
        skillVal = GetCharacterSPECIAL(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.95;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-2";
		diff = skillVal - GetSkillValue(_chr, SPECIAL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	row = "tr3";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
	}
	row = "tr4";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName); 
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-9,-4";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	
	row = "tr5";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
	}
	row = "tr6";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-9,-4";
		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

// опыт команды нпс _chr
void SetCrewExpTable(ref _chr, string _tabName, string _bar1, string _bar2, string _bar3)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=3; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.8;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Sailors";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Class";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Sailors");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr1.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Sailors)));
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.str = "";
	}
	
	GameInterface.(_tabName).tr2.UserData.ID = "Cannoners";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr2.td1.icon.image = "Cannons skill icon";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Cannoners");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr2.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Cannoners)));
	}
		else
	{
		GameInterface.(_tabName).tr2.td3.str = "";
	}
	
    GameInterface.(_tabName).tr3.UserData.ID = "Soldiers";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr3.td1.icon.image = "grappling skill icon";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Soldiers");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Soldiers)));
	}
		else
	{
		GameInterface.(_tabName).tr3.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
	
	///  прогресбары
	GameInterface.StatusLine.(_bar1).Max   = 100;
    GameInterface.StatusLine.(_bar1).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar1).Value = sti(_chr.Ship.Crew.Exp.Sailors);
    }
    else
    {
    	GameInterface.StatusLine.(_bar1).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);
    
    GameInterface.StatusLine.(_bar2).Max   = 100;
    GameInterface.StatusLine.(_bar2).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar2).Value = sti(_chr.Ship.Crew.Exp.Cannoners);
    }
    else
    {
    	GameInterface.StatusLine.(_bar2).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);
    
    GameInterface.StatusLine.(_bar3).Max   = 100;
    GameInterface.StatusLine.(_bar3).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar3).Value = sti(_chr.Ship.Crew.Exp.Soldiers);
    }
    else
    {
    	GameInterface.StatusLine.(_bar3).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);
}

void SetShipOTHERTable(string _tabName, ref _chr)
{
    int     i;
	string  row;
	float   fTmp;

    int iShip = sti(_chr.ship.type);
	ref refBaseShip = GetRealShip(iShip);
		
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=9; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.85;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.85;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Hull";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Hull";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Hull");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.ship.hp) + " / " + sti(refBaseShip.hp);

	GameInterface.(_tabName).tr2.UserData.ID = "Sails";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Sails";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Sails");
	GameInterface.(_tabName).tr2.td3.str = sti(_chr.ship.sp) + " / " + sti(refBaseShip.sp);

    GameInterface.(_tabName).tr3.UserData.ID = "Speed";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Speed";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Speed");
	if (IsCompanion(_chr))
	{
		GameInterface.(_tabName).tr3.td3.str = FloatToString(FindShipSpeed(_chr),2) + " / " + FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr3.td3.str = FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	

    GameInterface.(_tabName).tr4.UserData.ID = "Maneuver";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Maneuver";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Maneuver");
	if (IsCompanion(_chr))
	{
  		GameInterface.(_tabName).tr4.td3.str = FloatToString((stf(refBaseShip.turnrate) * FindShipTurnRate(_chr)), 2) + " / " + FloatToString(stf(refBaseShip.TurnRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr4.td3.str = FloatToString(stf(refBaseShip.TurnRate),2);
	}

	GameInterface.(_tabName).tr5.UserData.ID = "AgainstWind";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "AgainstWind";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("AgainstWind");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(stf(refBaseShip.WindAgainstSpeed), 2);
	
	
	RecalculateCargoLoad(_chr);
	GameInterface.(_tabName).tr6.UserData.ID = "Capacity";
	GameInterface.(_tabName).tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr6.td1.icon.image = "Capacity";
	GameInterface.(_tabName).tr6.td2.str = XI_ConvertString("Capacity");
	GameInterface.(_tabName).tr6.td3.str = GetCargoLoad(_chr) + " / " + GetCargoMaxSpace(_chr);
	
	GameInterface.(_tabName).tr7.UserData.ID = "Crew";
	GameInterface.(_tabName).tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr7.td1.icon.image = "Crew";
	GameInterface.(_tabName).tr7.td2.str = XI_ConvertString("Crew");
	GameInterface.(_tabName).tr7.td3.str = GetCrewQuantity(_chr) + " : "+ sti(refBaseShip.MinCrew) +" / " + sti(refBaseShip.OptCrew);	
	
	GameInterface.(_tabName).tr8.UserData.ID = "sCannons";
	GameInterface.(_tabName).tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr8.td1.icon.image = "Caliber";
	GameInterface.(_tabName).tr8.td2.str = XI_ConvertString("sCannons"); //XI_ConvertString("Caliber");
	GameInterface.(_tabName).tr8.td3.str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + " / " + sti(refBaseShip.CannonsQuantity);
		
	GameInterface.(_tabName).tr9.UserData.ID = "CannonType";
	GameInterface.(_tabName).tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr9.td1.icon.image = "Cannons";
	GameInterface.(_tabName).tr9.td2.str = XI_ConvertString(GetCannonType(sti(_chr.Ship.Cannons.Type)) + "s2");
	
	if (sti(_chr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		if(GetCannonsNum(_chr) > 0)
		{
		GameInterface.(_tabName).tr9.td3.str = XI_ConvertString("caliber" + GetCannonCaliber(sti(_chr.Ship.Cannons.Type))) + " / " + GetCannonsNum(_chr);
	}
	else
	{
			GameInterface.(_tabName).tr9.td3.str = GetCannonsNum(_chr);
		}	
	}
	else
	{
	    GameInterface.(_tabName).tr9.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

void SetFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;
	
	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = "Провианта на корабле на ";
		iFood = CalculateShipFood(chr);
		sText = sText + FindRussianDaysString(iFood);
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);	
	}
}

// Warship 11.07.09 Вывести в текстовое поле инфу о количестве дней, на сколько хватит рому на судне
void SetRumShipInfo(ref _character, String _node)
{
	int color, rum;
	String text;
	
	SetFormatedText(_node, "");
	
	if(sti(_character.ship.type) != SHIP_NOTUSED)
	{
		text = "Рома на корабле на ";
		rum = CalculateShipRum(_character);
		text = text + FindRussianDaysString(rum);
		SetFormatedText(_node, text);
		
		if(rum < 3)
		{
			color = argb(255, 255, 192, 192);
		}
		
		if(rum >= 3)
		{
			color = argb(255, 255, 255, 192);
		}
		
		if(rum >= 10)
		{
			color = argb(255, 192, 255, 192);
		}
		
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _node, 8, -1, color);	
	}
}

// Myth Корректное отображение пушек у компаньонов -->
bool CannonShipCheck(ref sld)
{
	if(!CheckAttribute(sld,"Ship.Cannons.Charge.Type"))
	{
		return false;
	}
	if(GetCannonsNum(sld) == 0)
	{
		return false;
	}
	return true;
}
// Myth Корректное отображение пушек у компаньонов <--

void GetXYWindowOffset(ref offsetX, ref offsetY)
{
	float dwScreenHeight 			= 600.0;
	float dwScreenWidth 			= sti(showWindow.width) * dwScreenHeight/ sti(showWindow.height);
	if(dwScreenWidth < 800.0)  dwScreenWidth = 800.0;
	
	float offX = (dwScreenWidth - 800.0)/2.0;
	float offY = 0.0;
	
	offsetX = offX;
	offsetY = offY;
}

// evganat - плавные переходы групп нод -->
object MoveList[10];

void AddNodeToMoveList(int mIdx, string nodeName, int left, int top, int right, int bottom)
{
	float offsetX, offsetY;
	GetXYWindowOffset(&offsetX, &offsetY);
	MoveList[mIdx].(nodeName).left = makeint(offsetX+left);
	MoveList[mIdx].(nodeName).top = makeint(offsetY+top);
	MoveList[mIdx].(nodeName).right = makeint(offsetX+right);
	MoveList[mIdx].(nodeName).bottom = makeint(offsetY+bottom);
}

void DeleteNodeFromMoveList(int mIdx, string nodeName)
{
	if(CheckAttribute(MoveList[mIdx], nodeName))
		DeleteAttribute(&MoveList[mIdx], nodeName);
}

void ClearMoveList(int mIdx)
{
	int n = GetAttributesNum(&MoveList[mIdx]);
	aref arNode;
	string nodeName;
	for (int i=n-1; i>=0; i--)
	{
		arNode = GetAttributeN(&MoveList[mIdx], 0);
		nodeName = GetAttributeName(arNode);
		DeleteAttribute(&MoveList[mIdx], nodeName);
	}
}

void MoveNodeToPosition(int mIdx, string nodeName, int left, int top, int right, int bottom)
{
	if(CheckAttribute(MoveList[mIdx], nodeName))
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,nodeName, -1, 4, left, top, right, bottom);
}


#event_handler("MoveNodeSteady", "MoveNodeToDirSteady");
void MoveNodeToDirSteady()
{
	int mIdx = GetEventData();
	string nodeName = GetEventData();
	string dir = GetEventData();
	int dist = GetEventData();
	int remain = GetEventData();
	string tag = GetEventData();
	if(remain <= 0)
	{
//		DeleteNodeFromMoveList(mIdx, nodeName);
		PostEvent("MoveFinished", 100, "ls", mIdx, tag);
		return;
	}
	if(!CheckAttribute(MoveList[mIdx], nodeName))
		return;
	int oldleft = sti(MoveList[mIdx].(nodeName).left);
	int oldtop = sti(MoveList[mIdx].(nodeName).top);
	int oldright = sti(MoveList[mIdx].(nodeName).right);
	int oldbottom = sti(MoveList[mIdx].(nodeName).bottom);
	int newleft, newright, newtop, newbottom;
	int kleft = 0;
	int kright = 0;
	int ktop = 0;
	int kbottom = 0;
	switch(dir)
	{
		case "up":			ktop = -1;		kbottom = -1;	break;
		case "down":		ktop = 1;		kbottom = 1;	break;
		case "left":		kleft = -1;		kright = -1;	break;
		case "right":		kleft = 1;		kright = 1;		break;
		case "up-left":		ktop = -1;		kbottom = -1;	kleft = -1;		kright = -1;		break;
		case "up-right":	ktop = -1;		kbottom = -1;	kleft = 1;		kright = 1;			break;
		case "down-left":	ktop = 1;		kbottom = 1;	kleft = -1;		kright = -1;		break;
		case "down-right":	ktop = 1;		kbottom = 1;	kleft = 1;		kright = 1;			break;
	}
	if(remain < dist)
		dist = remain;
	newleft = oldleft + kleft*dist;
	newright = oldright + kright*dist;
	newtop = oldtop + ktop*dist;
	newbottom = oldbottom + kbottom*dist;
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, nodeName, -1, 4, newleft, newtop, newright, newbottom);
	MoveList[mIdx].(nodeName).left = newleft;
	MoveList[mIdx].(nodeName).top = newtop;
	MoveList[mIdx].(nodeName).right = newright;
	MoveList[mIdx].(nodeName).bottom = newbottom;

	
	PostEvent("MoveNodeSteady", 20, "lsslls", mIdx, nodeName, dir, dist, remain-dist, tag);

}	

#event_handler("MoveNodeSoftly", "MoveNodeToDirSoftly");
void MoveNodeToDirSoftly()
{
	int mIdx = GetEventData();
	string nodeName = GetEventData();
	string dir = GetEventData();
	int startdist = GetEventData();
	int remain = GetEventData();
	int total = GetEventData();
	string tag = GetEventData();
	if(remain <= 0)
	{
//		DeleteNodeFromMoveList(mIdx, nodeName);
		PostEvent("MoveFinished", 100, "ls", mIdx, tag);
		return;
	}
	if(!CheckAttribute(MoveList[mIdx], nodeName))
		return;
	
	int oldleft = sti(MoveList[mIdx].(nodeName).left);
	int oldtop = sti(MoveList[mIdx].(nodeName).top);
	int oldright = sti(MoveList[mIdx].(nodeName).right);
	int oldbottom = sti(MoveList[mIdx].(nodeName).bottom);
	int newleft, newright, newtop, newbottom;
	int kleft = 0;
	int kright = 0;
	int ktop = 0;
	int kbottom = 0;
	switch(dir)
	{
		case "up":			ktop = -1;		kbottom = -1;	break;
		case "down":		ktop = 1;		kbottom = 1;	break;
		case "left":		kleft = -1;		kright = -1;	break;
		case "right":		kleft = 1;		kright = 1;		break;
		case "up-left":		ktop = -1;		kbottom = -1;	kleft = -1;		kright = -1;		break;
		case "up-right":	ktop = -1;		kbottom = -1;	kleft = 1;		kright = 1;			break;
		case "down-left":	ktop = 1;		kbottom = 1;	kleft = -1;		kright = -1;		break;
		case "down-right":	ktop = 1;		kbottom = 1;	kleft = 1;		kright = 1;			break;
	}
	
	int dist = startdist;
	if(remain >= total*0.8)
	{
		dist = round_near((4.2 - (makefloat(remain)/makefloat(total))*4)*startdist);
	}
	else
	{
		if(remain <= total*0.2)
		{
			dist = round_near(startdist*(0.2 + 4*(makefloat(remain)/makefloat(total))));
		}
	}
	
	if(remain < dist)
		dist = remain;	
	
//	Trace("total = "+total+" remain = "+remain+" startdist = "+startdist+ " remain/total = "+remain/total+" dist = "+dist);
	
	newleft = oldleft + kleft*dist;
	newright = oldright + kright*dist;
	newtop = oldtop + ktop*dist;
	newbottom = oldbottom + kbottom*dist;
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, nodeName, -1, 4, newleft, newtop, newright, newbottom);
	MoveList[mIdx].(nodeName).left = newleft;
	MoveList[mIdx].(nodeName).top = newtop;
	MoveList[mIdx].(nodeName).right = newright;
	MoveList[mIdx].(nodeName).bottom = newbottom;
	
	PostEvent("MoveNodeSoftly", 20, "lssllls", mIdx, nodeName, dir, startdist, remain-dist, total, tag);
}	

void MoveAllNodesToDirSteady(int mIdx, string dir, int speed, int dist, string tag)
{
	int n = GetAttributesNum(MoveList[mIdx]);
	string nodeName;
	aref arNode;
	for (int i=0; i<n; i++)
	{
		arNode = GetAttributeN(&MoveList[mIdx], i);
		nodeName = GetAttributeName(arNode);
		Event("MoveNodeSteady", "lsslls", mIdx, nodeName, dir, speed, dist, tag);
	}
}

void MoveAllNodesToDirSoftly(int mIdx, string dir, int speed, int dist, string tag)
{
	int n = GetAttributesNum(MoveList[mIdx]);
	string nodeName;
	aref arNode;
	for (int i=0; i<n; i++)
	{
		arNode = GetAttributeN(&MoveList[mIdx], i);
		nodeName = GetAttributeName(arNode);
		Event("MoveNodeSoftly", "lssllls", mIdx, nodeName, dir, speed, dist, dist, tag);
	}
}
// evganat - плавные переходы групп нод <--


// evganat - вызов подсказки рядом с указателем мыши -->
void ShowTextFrame(float fX, float fY, string sTitle, string sText)
{
	// вычисляем размеры ноды от текста
	int iWidth, iHeight, iLeft, iTop, iRight, iBottom;
	
	if(sTitle != "")
		sText = sTitle + newStr() + sText;
	
	if(strlen(sText) < 20)
	{
		iHeight = 18;
		iWidth = strlen(sText)*12;
	}
	else
	{
		iWidth = 200;
		iHeight = 10*(1 + strlen(sText)/20);
	}
	
	if(iWidth < 5*strlen(sTitle))
		iWidth = 5*strlen(sTitle);
		
	// вычисляем позицию ноды от размера и курсора
	if(makeint(fX) + iWidth > 1050)
		iLeft = 1050-iWidth;
	else
	{
		if(fX < 0)
			iLeft = 0;
		else
			iLeft = makeint(fX);
	}
	iRight = iLeft + iWidth;
	
	if(fY - iHeight < 0)
	{
		iTop = 0;
		iBottom = iTop + iHeight;
	}
	else
	{
		iBottom = makeint(fY);
		iTop = iBottom - iHeight;
	}
	
	// выставляем на координаты
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "NEW_INFO_FRAME", -1, 4, iLeft-5, iTop, iRight+5, iBottom);	// телепортируем рамку
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "NEW_INFO_TEXT", -1, 4, iLeft, iTop, iRight, iBottom);	// телепортируем текст
	
	// подгоняем размеры под реальные строки
	int iRows = SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"NEW_INFO_TEXT", 9, sText);
	if(iHeight < iRows * 16)
	{
		iHeight = iRows*16;
		iTop = iBottom - iHeight;
		SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "NEW_INFO_FRAME", -1, 4, iLeft-5, iTop, iRight+5, iBottom);	// телепортируем рамку
		SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "NEW_INFO_TEXT", -1, 4, iLeft, iTop, iRight, iBottom);	// телепортируем текст
	}
	
	// выставляем текст
	SetFormatedText("NEW_INFO_TEXT", sText);
	
	// отображаем ноды
	SetNodeUsing("NEW_INFO_FRAME", true);
	SetNodeUsing("NEW_INFO_TEXT", true);
}

void HideTextFrame()
{
	SetFormatedText("NEW_INFO_TEXT", "");
	SetNodeUsing("NEW_INFO_FRAME", false);
	SetNodeUsing("NEW_INFO_TEXT", false);
}
// evganat - вызов подсказки рядом с указателем мыши <--

// evganat - окрашивание текста -->
string ColorText(string sText, string color)
{
	string sPrefix = GetColorChar(color);
	if(sPrefix != "")
		return sPrefix + sText + "†";
	
	return sText;
}

string ColorTextLine(string sText, string color)
{
	string sPrefix = GetColorChar(color);
	if(sPrefix != "")
		return sPrefix + sText;
	
	return sText;
}

string GetColorChar(string color)
{
	string sPrefix = "";
	switch(color)
	{
		case "red":			sPrefix = "¡";		break;	// красный
		case "green":		sPrefix = "¢";		break;	// зелёный
		case "blue":		sPrefix = "£";		break;	// голубой
		case "yellow":		sPrefix = "¤";		break;	// синий
		case "purple":		sPrefix = "¥";		break;	// пурпурный
		case "aqua":		sPrefix = "¦";		break;	// цвет морской волны
		case "black":		sPrefix = "§";		break;	// чёрный
		case "gray":		sPrefix = "¨";		break;	// серый
		case "white":		sPrefix = "©";		break;	// белый
		case "darkgreen":	sPrefix = "ª";		break;	// тёмно-зелёный
		case "brown":		sPrefix = "®";		break;	// коричневый
		case "yellowgreen":	sPrefix = "¯";		break;	// жёлто-зелёный
		case "pink":		sPrefix = "°";		break;	// розовый
		case "gold":		sPrefix = "±";		break;	// золотой
		case "khaki":		sPrefix = "²";		break;	// хаки
		case "violet":		sPrefix = "³";		break;	// фиолетовый
		case "darkred":		sPrefix = "´";		break;	// тёмно-красный
		case "darkgray":	sPrefix = "µ";		break;	// тёмно-серый
		case "orange":		sPrefix = "¶";		break;	// оранжевый
		case "navy":		sPrefix = "·";		break;	// тёмно-синий
	}
	return sPrefix;
}
// evganat - окрашивание текста <--
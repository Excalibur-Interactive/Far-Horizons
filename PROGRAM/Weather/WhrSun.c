object SunGlow;

void WhrDeleteSunGlowEnvironment()
{
	if (isEntity(&SunGlow))
	{
		DeleteClass(&SunGlow);
	}
	DeleteAttribute(&SunGlow,"");
}

void WhrCreateSunGlowEnvironment()
{
	// create sunglow
	if (!isEntity(&SunGlow))
	{
		CreateEntity(&SunGlow,"SunGlow");
		LayerAddObject(SEA_SUNROAD,&SunGlow,-1);
	}
	WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
	SunGlow.isDone = true;
}

void WhrFillSunGlowData(int nw1, int nw2)
{
	if( nw1<0 || nw1>=MAX_WEATHERS ) {return;}

	SunGlow.Clear = "";
	DeleteAttribute(&SunGlow,"");

	aref aSun1;			makearef(aSun1, Weathers[nw1].Sun);
	aref aMoon1;		makearef(aMoon1, Weathers[nw1].Sun);
	aref aGlow1;		makearef(aGlow1, aSun1.Glow);
	aref aFlare1;		makearef(aFlare1, aSun1.Flare);
	aref aOverflow1;	makearef(aOverflow1, aSun1.Overflow);
	aref aReflection1;	makearef(aReflection1, aSun1.Reflection);
	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;
	aref aFlares,aFlareN;
	int iNumFlares, i;
	string sTemp;

	Whr_DebugLog("WhrFillSunGlowData  nw1:" + nw1 + " nw2:" + nw2 + " time:" + GetTime());
    Whr_DebugLog("Glow.Enable :" + sti(aSun1.Glow.Enable));
    Whr_DebugLog("Flare.Enable :" + sti(aSun1.Flare.Enable));
    Whr_DebugLog("Overflow.Enable :" + sti(aSun1.Overflow.Enable));
    Whr_DebugLog("Reflection.Enable :" + sti(aSun1.Reflection.Enable));

	if( nw2<0 )
	{
		if (sunIsShine)
		{
			if (sti(aSun1.Glow.Enable) != false)
			{
				SunGlow.Glow.Dist = Whr_GetFloat(aGlow1,"Dist");
				SunGlow.Glow.Size = Whr_GetFloat(aGlow1,"Size");
				SunGlow.Glow.Texture = Whr_GetString(aGlow1,"Texture");
				SunGlow.Glow.DecayTime = Whr_GetColor(aGlow1,"DecayTime");
				SunGlow.Glow.TechniqueNoZ = Whr_GetString(aGlow1,"TechniqueNoZ");
				SunGlow.Glow.TechniqueZ = Whr_GetString(aGlow1,"TechniqueZ");
				SunGlow.Glow.Color = Whr_GetColor(aGlow1,"Color");
			}

			if (sti(aMoon1.Glow.Enable) != false)
			{
				SunGlow.Glow.Dist = Whr_GetFloat(aGlow1,"Dist");
				SunGlow.Glow.Size = Whr_GetFloat(aGlow1,"Size");
				SunGlow.Glow.Texture = Whr_GetString(aGlow1,"Texture");
				SunGlow.Glow.DecayTime = Whr_GetColor(aGlow1,"DecayTime");
				SunGlow.Glow.TechniqueNoZ = Whr_GetString(aGlow1,"TechniqueNoZ");
				SunGlow.Glow.TechniqueZ = Whr_GetString(aGlow1,"TechniqueNoZ");
				SunGlow.Glow.Color = Whr_GetColor(aGlow1,"Color");
			}

			if (sti(aSun1.Flare.Enable) != false)
			{
				SunGlow.Flare.Texture = Whr_GetString(aFlare1,"Texture");
				SunGlow.Flare.TexSizeX = Whr_GetString(aFlare1,"TexSizeX");
				SunGlow.Flare.TexSizeY = Whr_GetString(aFlare1,"TexSizeY");
				SunGlow.Flare.Technique = Whr_GetString(aFlare1,"Technique");
				SunGlow.Flare.Scale = Whr_GetFloat(aFlare1,"Scale");
				SunGlow.Flare.Dist = Whr_GetFloat(aFlare1,"Dist");

				makearef(aFlares,aSun1.Flares);
				iNumFlares = GetAttributesNum(aFlares);
				for (i=0;i<iNumFlares;i++)
				{
					aFlareN = GetAttributeN(aFlares,i);
					sTemp = "f" + i;
					SunGlow.Flares.(sTemp) = GetAttributeValue(aFlareN);
				}
			}

			if (sti(aSun1.Overflow.Enable) != false)
			{
				SunGlow.Overflow.Texture = Whr_GetString(aOverflow1,"Texture");
				SunGlow.Overflow.Color = Whr_GetColor(aOverflow1,"Color");
				SunGlow.Overflow.Size = Whr_GetFloat(aOverflow1,"Size");
				SunGlow.Overflow.Technique = Whr_GetString(aOverflow1,"Technique");
				SunGlow.Overflow.Start = Whr_GetFloat(aOverflow1,"Start");
			}

			if (sti(aSun1.Reflection.Enable) != false)
			{
				SunGlow.Reflection.Texture = Whr_GetString(aReflection1, "Texture");
				SunGlow.Reflection.Technique = Whr_GetString(aReflection1, "Technique");
				SunGlow.Reflection.Dist = Whr_GetFloat(aReflection1, "Dist");
				SunGlow.Reflection.Size = Whr_GetFloat(aReflection1, "Size");
				SunGlow.Reflection.Color = Whr_GetColor(aReflection1, "Color");
			}
			SunGlow.Moon = aMoon1.Moon;
		}
	}
	else
	{	
		if (sti(aSun1.Glow.Enable) != false)
		{
			SunGlow.Glow.Dist = Whr_GetFloat(aGlow1,"Dist");
			SunGlow.Glow.Size = Whr_GetFloat(aGlow1,"Size");
			SunGlow.Glow.Texture = Whr_GetString(aGlow1,"Texture");
			SunGlow.Glow.Color = Whr_GetColor(aGlow1,"Color");
			SunGlow.Glow.DecayTime = Whr_GetColor(aGlow1,"DecayTime");
			SunGlow.Glow.TechniqueZ = Whr_GetString(aGlow1,"TechniqueZ");
			SunGlow.Glow.TechniqueNoZ = Whr_GetString(aGlow1,"TechniqueNoZ");
		}

		if (sti(aMoon1.Glow.Enable) != false)
		{
			SunGlow.Glow.Dist = Whr_GetFloat(aGlow1,"Dist");
			SunGlow.Glow.Size = Whr_GetFloat(aGlow1,"Size");
			SunGlow.Glow.Texture = Whr_GetString(aGlow1,"Texture");
			SunGlow.Glow.DecayTime = Whr_GetColor(aGlow1,"DecayTime");
			SunGlow.Glow.TechniqueNoZ = Whr_GetString(aGlow1,"TechniqueNoZ");
			SunGlow.Glow.TechniqueZ = Whr_GetString(aGlow1,"TechniqueNoZ");
			SunGlow.Glow.Color = Whr_GetColor(aGlow1,"Color");
		}

		if (sti(aSun1.Flare.Enable) != false)
		{
			SunGlow.Flare.Texture = Whr_GetString(aFlare1,"Texture");
			SunGlow.Flare.TexSizeX = Whr_GetString(aFlare1,"TexSizeX");
			SunGlow.Flare.TexSizeY = Whr_GetString(aFlare1,"TexSizeY");
			SunGlow.Flare.Technique = Whr_GetString(aFlare1,"Technique");
			SunGlow.Flare.Dist = Whr_GetFloat(aFlare1,"Dist");
			SunGlow.Flare.Scale = Whr_GetFloat(aFlare1,"Scale");

			makearef(aFlares,aSun1.Flares);
			iNumFlares = GetAttributesNum(aFlares);
			for (i=0;i<iNumFlares;i++)
			{
				aFlareN = GetAttributeN(aFlares,i);
				sTemp = "f" + i;
				SunGlow.Flares.(sTemp) = GetAttributeValue(aFlareN);
			}
		}

		if (sti(aSun1.Overflow.Enable) != false)
		{
			SunGlow.Overflow.Texture = Whr_GetString(aOverflow1,"Texture");
			SunGlow.Overflow.Color = Whr_GetColor(aOverflow1,"Color");
			SunGlow.Overflow.Size = Whr_GetFloat(aOverflow1,"Size");
			SunGlow.Overflow.Technique = Whr_GetString(aOverflow1,"Technique");
			SunGlow.Overflow.Start = Whr_GetFloat(aOverflow1,"Start");
		}

		if (sti(aSun1.Reflection.Enable) != false)
		{
			SunGlow.Reflection.Texture = Whr_GetString(aReflection1, "Texture");
			SunGlow.Reflection.Technique = Whr_GetString(aReflection1, "Technique");
			SunGlow.Reflection.Size = Whr_GetFloat(aReflection1, "Size");
			SunGlow.Reflection.Dist = Whr_GetFloat(aReflection1, "Dist");
			SunGlow.Reflection.Color = Whr_GetColor(aReflection1, "Color");
		}
		SunGlow.Moon = aMoon1.Moon;
	}

	if( stf(Environment.Time) < 5.5 || stf(Environment.Time) > 20.5 ) {
		SunGlow.Moon = true;
		SunGlow.Reflection.Color = argb(0,255,255,255);	
		SunGlow.Reflection.Texture = "weather\sun\reflection\refl_night.tga";
	} else {
		SunGlow.Moon = false;
	}
//Sith: ниже идут настройки солнца и луны с привязкой ко времени и датам
	if( nw2 >= 0)
	{
		SunGlow.Glow.SunTexture = "weather\sun\glow\sun.tga";
		SunGlow.Glow.MoonTexture = "weather\sun\glow\moon.tga";
		SunGlow.Glow.GlowTexture = "weather\sun\glow\sunglow.tga";
		if (GetTime() >= 5.0 && GetTime() < 6.0) {
			SunGlow.Flare.Scale 	= 0;
			SunGlow.Glow.SunSize 	= 0;
			SunGlow.Glow.Size 		= 0;
			SunGlow.Reflection.Size = 0;
		} else {
		if (GetTime() >= 6.0 && GetTime() < 6.4){
			SunGlow.Flare.Scale 	= 0;
			SunGlow.Glow.SunSize 	= 0;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			SunGlow.Glow.Color = argb(0,205,205,205);
			SunGlow.Reflection.Size = 650;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_evening.tga";
		} else {
		if (GetTime() >= 6.4 && GetTime() < 7.0){
			SunGlow.Glow.SunSize 	= 0;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			if (!bMainMenu) 
			{
				SunGlow.Overflow.Color = argb(0,50,50,50);
				SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_morning.tga";
			}
			SunGlow.Reflection.Size = 750;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_morning.tga";
		} else {
		if (GetTime() >= 7.0 && GetTime() < 8.0){
			SunGlow.Glow.SunSize 	= 250;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			SunGlow.Reflection.Size = 850;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
		} else {
		if( GetTime() >= 8.0 && GetTime() < 9.0 ) {
			SunGlow.Glow.SunSize 	= 500;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			SunGlow.Reflection.Size = 850;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
		} else {
		if( GetTime() >= 9.0 && GetTime() < 17.0 ) {
			SunGlow.Glow.SunSize 	= 2000;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			SunGlow.Reflection.Size = 850;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
		} else {
		if( GetTime() >= 17.0 && GetTime() < 18.8 ) {
			SunGlow.Glow.SunSize 	= 750;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			SunGlow.Reflection.Size = 850;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
		} else {
		if( GetTime() >= 18.8 && GetTime() < 19.0 ) {
			SunGlow.Glow.SunSize 	= 0;
			SunGlow.Glow.Size 		= 500;
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun.tga";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun_dg.tga";
			SunGlow.Reflection.Size = 850;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
		} else {
		if( GetTime() >= 19.0 && GetTime() < 19.7 ) {
			SunGlow.Glow.SunSize 	= 0;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			if (!bMainMenu) SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_evening.tga";
			SunGlow.Reflection.Size = 750;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_evening.tga";
		} else {
		if( GetTime() >= 19.7 && GetTime() < 20.0 ) {
			SunGlow.Flare.Scale = 0;
			SunGlow.Glow.SunSize 	= 0;
			SunGlow.Glow.Size 		= 175;
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
			if (!bMainMenu) SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_evening.tga";
			// SunGlow.Glow.Color = argb(0,205,205,205);
			SunGlow.Reflection.Size = 550;
			SunGlow.Reflection.Texture = "weather\sun\reflection\refl_evening.tga";
		} else {
		if (GetTime() >= 20.0 && GetTime() < 20.5) {
			SunGlow.Glow.Size = 0;
			SunGlow.Reflection.Size = 0;
		} else {
		if (GetTime() >= 20.5 || GetTime() < 5.5) 
		{
			if (stf(Environment.date.day) < 3 || stf(Environment.date.day) > 29) {
				SunGlow.Reflection.Size = 0;
				SunGlow.Overflow.Color = argb(0,10,10,10);
			} else {
				SunGlow.Reflection.Size = 550;
			}
		}}}}}}}}}}}}
		if (CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) SunGlow.Glow.Size = 0;
		if (CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) SunGlow.Reflection.Size = 0;
		if (stf(Environment.date.day) == 1) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon01.tga";
		if (stf(Environment.date.day) == 2) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon02.tga";
		if (stf(Environment.date.day) == 3) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon03.tga";		
		if (stf(Environment.date.day) == 4) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon04.tga";		
		if (stf(Environment.date.day) == 5) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon05.tga";
		if (stf(Environment.date.day) == 6) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon06.tga";
		if (stf(Environment.date.day) == 7) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon07.tga";
		if (stf(Environment.date.day) == 8) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon08.tga";
		if (stf(Environment.date.day) == 9) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon09.tga";
		if (stf(Environment.date.day) == 10) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon10.tga";
		if (stf(Environment.date.day) == 11) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon11.tga";
		if (stf(Environment.date.day) == 12) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon12.tga";
		if (stf(Environment.date.day) == 13) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon13.tga";
		if (stf(Environment.date.day) == 14) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon14.tga";
		if (stf(Environment.date.day) == 15) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon15.tga";
		if (stf(Environment.date.day) == 16) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon16.tga";
		if (stf(Environment.date.day) == 17) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon17.tga";
		if (stf(Environment.date.day) == 18) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon18.tga";
		if (stf(Environment.date.day) == 19) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon19.tga";
		if (stf(Environment.date.day) == 20) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon20.tga";
		if (stf(Environment.date.day) == 21) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon21.tga";
		if (stf(Environment.date.day) == 22) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon22.tga";
		if (stf(Environment.date.day) == 23) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon23.tga";
		if (stf(Environment.date.day) == 24) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon24.tga";
		if (stf(Environment.date.day) == 25) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon25.tga";
		if (stf(Environment.date.day) == 26) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon26.tga";
		if (stf(Environment.date.day) == 27) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon27.tga";
		if (stf(Environment.date.day) == 28) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon28.tga";
		if (stf(Environment.date.day) == 29) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon29.tga";
		if (stf(Environment.date.day) == 30) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon30.tga";
		if (stf(Environment.date.day) == 31) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon31.tga";
		SunGlow.Glow.MoonSize = 250;
		SunGlow.Glow.Color = argb(0,255,255,255);
		SunGlow.Reflection.Color = argb(0,255,255,255);
	}
	else
	{
		if (sunIsShine)
		{
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun.tga";
			SunGlow.Glow.MoonTexture = "weather\sun\glow\moon.tga";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sunglow.tga";
			if (GetTime() >= 5.0 && GetTime() < 6.0) {
				SunGlow.Flare.Scale 	= 0;
				SunGlow.Glow.SunSize 	= 0;
				SunGlow.Glow.Size 		= 0;
				SunGlow.Reflection.Size = 0;
			} else {
			if (GetTime() >= 6.0 && GetTime() < 6.4){
				SunGlow.Flare.Scale 	= 0;
				SunGlow.Glow.SunSize 	= 0;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				if (!bMainMenu) 
				{
					SunGlow.Overflow.Color = argb(0,50,50,50);
					SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_morning.tga";
				}
				SunGlow.Reflection.Size = 650;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_evening.tga";
			} else {
			if (GetTime() >= 6.4 && GetTime() < 7.0){
				SunGlow.Glow.SunSize 	= 0;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				if (!bMainMenu) 
				{
					SunGlow.Overflow.Color = argb(0,50,50,50);
					SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_morning.tga";
				}
				SunGlow.Reflection.Size = 750;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_morning.tga";
			} else {
			if (GetTime() >= 7.0 && GetTime() < 8.0){
				SunGlow.Glow.SunSize 	= 250;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				SunGlow.Reflection.Size = 850;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
			} else {
			if( GetTime() >= 8.0 && GetTime() < 9.0 ) {
				SunGlow.Glow.SunSize 	= 500;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				SunGlow.Reflection.Size = 850;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
			} else {
			if( GetTime() >= 9.0 && GetTime() < 17.0 ) {
				SunGlow.Glow.SunSize 	= 2000;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				SunGlow.Reflection.Size = 850;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
			} else {
			if( GetTime() >= 17.0 && GetTime() < 18.8 ) {
				SunGlow.Glow.SunSize 	= 750;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.SunTexture = "weather\sun\glow\sun_dg.tga";
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				SunGlow.Reflection.Size = 850;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
			} else {
			if( GetTime() >= 18.8 && GetTime() < 19.0 ) {
				SunGlow.Glow.SunSize 	= 0;
				SunGlow.Glow.Size 		= 500;
				SunGlow.Glow.SunTexture = "weather\sun\glow\sun.tga";
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun_dg.tga";
				SunGlow.Reflection.Size = 850;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_day.tga";
			} else {
			if( GetTime() >= 19.0 && GetTime() < 19.7 ) {
				SunGlow.Glow.SunSize 	= 0;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				if (!bMainMenu) SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_evening.tga";
				SunGlow.Reflection.Size = 750;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_evening.tga";
			} else {
			if( GetTime() >= 19.7 && GetTime() < 20.0 ) {
				SunGlow.Flare.Scale = 0;
				SunGlow.Glow.SunSize 	= 0;
				SunGlow.Glow.Size 		= 175;
				SunGlow.Glow.GlowTexture = "weather\sun\glow\sun.tga";
				if (!bMainMenu) SunGlow.Overflow.Texture = "weather\sun\overflow\overflow_evening.tga";
				// SunGlow.Glow.Color = argb(0,205,205,205);
				SunGlow.Reflection.Size = 550;
				SunGlow.Reflection.Texture = "weather\sun\reflection\refl_evening.tga";
			} else {
			if (GetTime() >= 20.0 && GetTime() < 20.5) {
				SunGlow.Glow.Size = 0;
				SunGlow.Reflection.Size = 0;
			} else {
			if (GetTime() >= 20.5 || GetTime() < 5.5) 
			{
				if (stf(Environment.date.day) < 3 || stf(Environment.date.day) > 29) {
					SunGlow.Reflection.Size = 0;
					SunGlow.Overflow.Color = argb(0,10,10,10);
				} else {
					SunGlow.Reflection.Size = 550;
				}
			}}}}}}}}}}}}
			if (CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) SunGlow.Glow.Size = 0;
			if (CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) SunGlow.Reflection.Size = 0;
			if (stf(Environment.date.day) == 1) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon01.tga";
			if (stf(Environment.date.day) == 2) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon02.tga";
			if (stf(Environment.date.day) == 3) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon03.tga";		
			if (stf(Environment.date.day) == 4) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon04.tga";		
			if (stf(Environment.date.day) == 5) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon05.tga";
			if (stf(Environment.date.day) == 6) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon06.tga";
			if (stf(Environment.date.day) == 7) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon07.tga";
			if (stf(Environment.date.day) == 8) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon08.tga";
			if (stf(Environment.date.day) == 9) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon09.tga";
			if (stf(Environment.date.day) == 10) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon10.tga";
			if (stf(Environment.date.day) == 11) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon11.tga";
			if (stf(Environment.date.day) == 12) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon12.tga";
			if (stf(Environment.date.day) == 13) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon13.tga";
			if (stf(Environment.date.day) == 14) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon14.tga";
			if (stf(Environment.date.day) == 15) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon15.tga";
			if (stf(Environment.date.day) == 16) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon16.tga";
			if (stf(Environment.date.day) == 17) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon17.tga";
			if (stf(Environment.date.day) == 18) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon18.tga";
			if (stf(Environment.date.day) == 19) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon19.tga";
			if (stf(Environment.date.day) == 20) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon20.tga";
			if (stf(Environment.date.day) == 21) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon21.tga";
			if (stf(Environment.date.day) == 22) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon22.tga";
			if (stf(Environment.date.day) == 23) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon23.tga";
			if (stf(Environment.date.day) == 24) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon24.tga";
			if (stf(Environment.date.day) == 25) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon25.tga";
			if (stf(Environment.date.day) == 26) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon26.tga";
			if (stf(Environment.date.day) == 27) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon27.tga";
			if (stf(Environment.date.day) == 28) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon28.tga";
			if (stf(Environment.date.day) == 29) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon29.tga";
			if (stf(Environment.date.day) == 30) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon30.tga";
			if (stf(Environment.date.day) == 31) 	SunGlow.Glow.MoonTexture = "weather\sun\glow\moon\moon31.tga";
			SunGlow.Glow.MoonSize = 250;
			SunGlow.Glow.Color = argb(0,255,255,255);
			SunGlow.Reflection.Color = argb(0,255,255,255);
		}
	}
}

void MoveSunGlowToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&SunGlow);
	LayerDelObject(REALIZE,&SunGlow);
	LayerDelObject(SEA_EXECUTE,&SunGlow);
	LayerDelObject(SEA_REALIZE,&SunGlow);

	LayerAddObject(sExecuteLayer, &SunGlow, -2);
	LayerAddObject(sRealizeLayer, &SunGlow, -2);
}
int Whr_GetColor(aref arRef, string sAttribute)
{
	return sti(arRef.(sAttribute));
}

float Whr_GetFloat(aref arRef, string sAttribute)
{
	string sTmpAttr = sAttribute + ".max";
	if (CheckAttribute(arRef,sTmpAttr))
	{
		float fMin = stf(arRef.(sAttribute).min);
		float fMax = stf(arRef.(sAttribute).max);
		return fMin + frnd() * (fMax - fMin);
	}
	if (!CheckAttribute(&arRef, sAttribute)) return 0.0; //задолбало
	
	return stf(arRef.(sAttribute));
}

int Whr_GetLong(aref arRef, string sAttribute)
{
	string sTmpAttr = sAttribute + ".max";
	if (CheckAttribute(arRef,sTmpAttr))
	{
		int iMin = sti(arRef.(sAttribute).min);
		int iMax = sti(arRef.(sAttribute).max);
		return iMin + rand(iMax - iMin - 1);
	}
	if (CheckAttribute(arRef, sAttribute))		// LDH added check  30 Mar09
	{
		return sti(arRef.(sAttribute));
	}
	return 0;
}

string Whr_GetString(aref arRef, string sAttribute)
{
	return arRef.(sAttribute);
}

void eChangeDayNight()
{
}

// утилиты блендинга
float Whr_BlendFloat(float fBlend, float f1, float f2)
{
	float f = f1 + fBlend * (f2-f1);
	return f;
}

int Whr_BlendLong(float fBlend, int i1, int i2)
{
	int i = makeint(i1 + fBlend * (i2-i1));
	return i;
}

int Whr_BlendColor(float fBlend, int col1, int col2)
{
	int a1 = shr(and(col1,4278190080), 24); 	// get alpha 1
	int a2 = shr(and(col2,4278190080), 24); 	// get alpha 2
	
	int r1 = shr(and(col1,16711680), 16); 		// get red color 1
	int r2 = shr(and(col2,16711680), 16); 		// get red color 2

	int g1 = shr(and(col1,65280), 8); 			// get green color 1
	int g2 = shr(and(col2,65280), 8); 			// get green color 2

	int b1 = and(col1,255); 					// get blue color 1
	int b2 = and(col2,255); 					// get blue color 2

	int r = r1 + MakeInt(fBlend * (r2-r1));
	int g = g1 + MakeInt(fBlend * (g2-g1));
	int b = b1 + MakeInt(fBlend * (b2-b1));
	int a = a1 + MakeInt(fBlend * (a2-a1));

	return argb(a,r,g,b);
}
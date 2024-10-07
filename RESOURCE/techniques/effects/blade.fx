technique Blade
{
    pass p0
    {
		ZWriteEnable = false;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;
		SrcBlend = zero;
		DestBlend = one;
		ColorOp[0] = modulate;
		AlphaOp[0] = disable;
		
		CullMode = none;
    }
}
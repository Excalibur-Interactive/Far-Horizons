technique texturedialogfon
{
    pass p0
    {
        ZEnable = false;
        Lighting = false;
        CullMode = none;
        SpecularEnable = false;
        AlphaTestEnable = false;
        AlphaBlendEnable = true;
        SrcBlend = srcalpha;
        DestBlend = invsrcalpha;

        ColorOp[0] = selectarg1;
        ColorArg1[0] = texture;

        AlphaOp[0] = modulate;
        AlphaArg1[0] = texture;
        AlphaArg2[0] = current;

        ColorOp[1] = disable;
    }
}
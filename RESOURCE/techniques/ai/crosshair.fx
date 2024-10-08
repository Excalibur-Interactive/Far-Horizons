technique Crosshair
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

        ColorOp[0] = modulate;
        ColorArg1[0] = texture;
        ColorArg2[0] = diffuse;

        AlphaOp[0] = selectarg1;
        AlphaArg1[0] = texture;

        ColorOp[1] = disable;
    }
}
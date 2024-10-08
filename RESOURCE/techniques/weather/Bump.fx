technique bump_interpolate
{
    pass p0
    {
        ZEnable = false;
        FogEnable = false;
        SpecularEnable = false;
        Lighting = false;
        CullMode = none;
        AlphaTestEnable = false;
        AlphaBlendEnable = false;

        MinFilter[0] = point;
        MinFilter[1] = point;

        TexCoordIndex[0] = 0;
        TexCoordIndex[1] = 0;

        ColorOp[0] = SelectArg1;
        ColorArg1[0] = texture;

        ColorOp[1] = blendfactoralpha;
        ColorArg1[1] = texture;
        ColorArg2[1] = current;

        ColorOp[2] = disable;
    }
}

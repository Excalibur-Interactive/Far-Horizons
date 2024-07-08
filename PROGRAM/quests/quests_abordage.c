// запускается сразу после начала абордажа
void QuestAbordageStartEvent()
{
	int iCharacter1 = GetEventData();
	int iCharacter2 = GetEventData();

	int iTestCharacter = -2;

	if (iCharacter1 == iTestCharacter || iCharacter2 == iTestCharacter)
	{
		AddCharacterGoods(GetMainCharacter(), GOOD_BALLS, 50);
	}
}

// boal установки игры BETATEST 20.08.04 -->

void InitInterface(string iniName)
{

    GameInterface.title = "BetaTeleport";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
 
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
}

void ProcessCancelExit()
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
    DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");

    interfaceResultCommand = RC_INTERFACE_QUICK_SAVE;
    
    EndCancelInterface(true);
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

	switch(nodName)
	{
 	    case "island_1":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_1();
		  }
	    break;

 	    case "island_2":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_2();
		  }
	    break;
 	    case "island_3":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_3();
		  }
	    break;
 	    case "island_4":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_4();
		  }
	    break;
 	    case "island_5":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_5();
		  }
	    break;
 	    case "island_6":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_6();
		  }
	    break;
	 	case "island_7":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_7();
		  }
	    break;	
 	    case "island_8":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_8();
		  }
	    break;		
 	    case "island_9":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_9();
		  }
	    break;		
 	    case "island_10":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_10();
		  }
	    break;		
 	    case "island_11":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_11();
		  }
	    break;		
 	    case "island_12":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_12();
		  }
	    break;		
 	    case "island_13":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_13();
		  }
	    break;		
 	    case "island_14":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_14();
		  }
	    break;		
 	    case "island_15":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_15();
		  }
	    break;		
 	    case "island_16":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_16();
		  }
	    break;		
 	    case "island_17":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_17();
		  }
	    break;		
 	    case "island_18":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_18();
		  }
	    break;
 	    case "island_19":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_19();
		  }
	    break;
 	    case "island_20":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_20();
		  }
	    break;		
	    case "island_21":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_21();
		  }
	    break;				
	    case "island_22":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_22();
		  }
	    break;				
	    case "island_23":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_23();
		  }
	    break;		
	    case "island_24":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_24();
		  }
	    break;		
	    case "island_25":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_25();
		  }
	    break;		
	    case "island_26":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_26();
		  }
	    break;		
	    case "island_27":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_27();
		  }
	    break;		
	    case "island_28":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_28();
		  }
	    break;		
	    case "island_29":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_29();
		  }
	    break;		
	    case "island_30":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_30();
		  }
	    break;		
	    case "island_31":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_31();
		  }
	    break;			
		case "island_32":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_32();
		  }
	    break;		
	    case "island_33":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_33();
		  }
	    break;			
		case "island_34":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_34();
		  }
	    break;
		case "island_35":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_35();
		  }
	    break;
		case "island_36":
		  if(comName=="activate" || comName=="click")
		  {
		      nodName_island_36();
		  }
	    break;			
	}
}


void nodName_island_1()
{
	ref mc, ch;
	mc = GetMainCharacter();
	DoReloadCharacterToLocation("Charles_town","reload","reload1");
	SetCharacterShipLocation(mc, "Charles_town");
	setWDMPointXZ("Charles_town");	
}

void nodName_island_2()
{
	ref mc, ch;
	mc = GetMainCharacter();
			    	DoReloadCharacterToLocation("SentJons_town","reload","reload1");
					SetCharacterShipLocation(mc, "SentJons_town");
					setWDMPointXZ("SentJons_town");	
}

void nodName_island_3()
{
	ref mc, ch;
	mc = GetMainCharacter();
			    	DoReloadCharacterToLocation("Bridgetown_town","reload","reload1");
					SetCharacterShipLocation(mc, "Bridgetown_town");
					setWDMPointXZ("Bridgetown_town");	
}

void nodName_island_4()
{
	ref mc, ch;
	mc = GetMainCharacter();
			    	DoReloadCharacterToLocation("Villemstad_town","reload","reload1");
					SetCharacterShipLocation(mc, "Villemstad_town");
					setWDMPointXZ("Villemstad_town");	
}

void nodName_island_5()
{
	ref mc, ch;
	mc = GetMainCharacter();
					DoReloadCharacterToLocation("Tortuga_town","reload","reload1");
					SetCharacterShipLocation(mc, "Tortuga_town");
					setWDMPointXZ("Tortuga_town");	
}	
		    	
void nodName_island_6()
{
	ref mc, ch;
	mc = GetMainCharacter();
			    	DoReloadCharacterToLocation("PuertoPrincipe_town","reload","reload1");
					SetCharacterShipLocation(mc, "PuertoPrincipe_town");
					setWDMPointXZ("PuertoPrincipe_town");
}						

void nodName_island_7()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("FortFrance_town","reload","reload1");
					SetCharacterShipLocation(mc, "FortFrance_town");
					setWDMPointXZ("FortFrance_town");			
	
}		

void nodName_island_8()
{
	ref mc, ch;
	mc = GetMainCharacter();

					DoReloadCharacterToLocation("PortPax_town","reload","reload1");
					SetCharacterShipLocation(mc, "PortPax_town");
					setWDMPointXZ("PortPax_town");			
	
}	

void nodName_island_9()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("LeFransua_port","reload","reload1");
					SetCharacterShipLocation(mc, "LeFransua_port");
					setWDMPointXZ("LeFransua_port");	
	
}	
								
void nodName_island_10()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("Marigo_town","reload","reload1");
					SetCharacterShipLocation(mc, "Marigo_town");
					setWDMPointXZ("Marigo_town");	
					
}						

void nodName_island_11()
{
	ref mc, ch;
	mc = GetMainCharacter();

					DoReloadCharacterToLocation("Beliz_town","reload","reload1");
					SetCharacterShipLocation(mc, "Beliz_town");
					setWDMPointXZ("Beliz_town");	
	
}						

void nodName_island_12()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("BasTer_town","reload","reload1");
					SetCharacterShipLocation(mc, "BasTer_town");
					setWDMPointXZ("BasTer_town");		
	
}						

void nodName_island_13()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("SantaCatalina_town","reload","reload1");
					SetCharacterShipLocation(mc, "SantaCatalina_town");
					setWDMPointXZ("SantaCatalina_town");			
	
}						

void nodName_island_14()
{
	ref mc, ch;
	mc = GetMainCharacter();

	
			    	DoReloadCharacterToLocation("Shore26","reload","sea");
					SetCharacterShipLocation(mc, "Shore26");
					setWDMPointXZ("Shore26");		
}						


void nodName_island_15()
{
	ref mc, ch;
	mc = GetMainCharacter();
	
					DoReloadCharacterToLocation("Shore57","reload","reload1");
					SetCharacterShipLocation(mc, "Shore57");
					setWDMPointXZ("Shore57");	
	
	
}						

void nodName_island_16()
{
	ref mc, ch;
	mc = GetMainCharacter();

					DoReloadCharacterToLocation("Shore17","reload","reload1");
					SetCharacterShipLocation(mc, "Shore17");
					setWDMPointXZ("Shore17");
	
}						

void nodName_island_17()
{
	ref mc, ch;
	mc = GetMainCharacter();

	
			    	DoReloadCharacterToLocation("Caracas_town","reload","reload1");
					SetCharacterShipLocation(mc, "Caracas_town");
					setWDMPointXZ("Caracas_town");			
}						


void nodName_island_18()
{
	ref mc, ch;
	mc = GetMainCharacter();

	
					DoReloadCharacterToLocation("Cartahena_town","reload","reload1");
					SetCharacterShipLocation(mc, "Cartahena_town");
					setWDMPointXZ("Cartahena_town");		
}						

void nodName_island_19()
{
	ref mc, ch;
	mc = GetMainCharacter();
	
                    DoReloadCharacterToLocation("Cumana_town","reload","reload1");
					SetCharacterShipLocation(mc, "Cumana_town");
					setWDMPointXZ("Cumana_town");
	
	
}						

void nodName_island_20()
{
	ref mc, ch;
	mc = GetMainCharacter();

					DoReloadCharacterToLocation("PortRoyal_town","reload","reload1_back");
					SetCharacterShipLocation(mc, "PortRoyal_town");
					setWDMPointXZ("PortRoyal_town");
					
}						

void nodName_island_21()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("Havana_town","reload","reload1");
					SetCharacterShipLocation(mc, "Havana_town");
					setWDMPointXZ("Havana_town");		
	
}		


void nodName_island_22()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("LaVega_port","reload","reload1");
					SetCharacterShipLocation(mc, "LaVega_port");
					setWDMPointXZ("LaVega_port");		
	
}		


void nodName_island_23()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("Maracaibo_town","reload","reload1");
					SetCharacterShipLocation(mc, "Maracaibo_town");
					setWDMPointXZ("Maracaibo_town");		
	
}		


void nodName_island_24()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("Panama_town","reload","reload1");
					SetCharacterShipLocation(mc, "Panama_town");
					setWDMPointXZ("Panama_town");		
	
}		


void nodName_island_25()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("PortoBello_town","reload","reload1");
					SetCharacterShipLocation(mc, "PortoBello_town");
					setWDMPointXZ("PortoBello_town");	
	
}		


void nodName_island_26()
{
	ref mc, ch;
	mc = GetMainCharacter();

			    	DoReloadCharacterToLocation("SanJuan_town","reload","reload1");
					SetCharacterShipLocation(mc, "SanJuan_town");
					setWDMPointXZ("SanJuan_town");		
	
}		


void nodName_island_27()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("Santiago_town","reload","reload1");
					SetCharacterShipLocation(mc, "Santiago_town");
					setWDMPointXZ("Santiago_town");	
	
}		


void nodName_island_28()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("SantoDomingo_town","reload","reload1");
					SetCharacterShipLocation(mc, "SantoDomingo_town");
					setWDMPointXZ("SantoDomingo_town");	
	
}		


void nodName_island_29()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("PortSpein_town","reload","reload1");
					SetCharacterShipLocation(mc, "PortSpein_town");
					setWDMPointXZ("PortSpein_town");
	
}		


void nodName_island_30()
{
	ref mc, ch;
	mc = GetMainCharacter();

				    DoReloadCharacterToLocation("Shore35","reload","reload1");
					SetCharacterShipLocation(mc, "Shore35");
					setWDMPointXZ("Shore35");
}		

void nodName_island_31()
{
	ref mc, ch;
	mc = GetMainCharacter();
	
}		

void nodName_island_32()
{
	ref mc, ch;
	mc = GetMainCharacter();					
	
}		


void nodName_island_33()
{
	ref mc, ch;
	mc = GetMainCharacter();					
	
}		

void nodName_island_34()
{
	ref mc, ch;
	mc = GetMainCharacter();
	
}
	
void nodName_island_35()
{
	ref mc, ch;
	mc = GetMainCharacter();
	
}	

void nodName_island_36()
{
	ref mc, ch;
	mc = GetMainCharacter();
	
}		
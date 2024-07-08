void InitGoods()
{
	int i;
	
	Goods[GOOD_PLANKS].Name		    = "Planks";
	Goods[GOOD_PLANKS].Weight	    = 3;
	Goods[GOOD_PLANKS].Cost		    = 8;
	Goods[GOOD_PLANKS].Units	    = 1;
	Goods[GOOD_PLANKS].Swim.Model	= "roll_of_planks";
	Goods[GOOD_PLANKS].Swim.Time	= 45; // boal 15
	Goods[GOOD_PLANKS].AfraidWater = 0;
	Goods[GOOD_PLANKS].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_PLANKS].canbecontraband	= 0;  
	Goods[GOOD_PLANKS].Norm          = 5000;
	
    Goods[GOOD_BRICKS].Name	        = "Bricks";
	Goods[GOOD_BRICKS].Weight        = 6;
	Goods[GOOD_BRICKS].Cost	        = 16;
	Goods[GOOD_BRICKS].Units	        = 10;
	Goods[GOOD_BRICKS].AfraidWater = 0;
	Goods[GOOD_BRICKS].canbecontraband	= 1;	
	
	Goods[GOOD_FABRICS].Name		= "Fabrics";
	Goods[GOOD_FABRICS].Weight	= 2;
	Goods[GOOD_FABRICS].Cost		= 5;
	Goods[GOOD_FABRICS].Units		= 1;
	Goods[GOOD_FABRICS].Swim.Model= "roll_of_materials";
	Goods[GOOD_FABRICS].Swim.Time	= 45; // boal 10
	Goods[GOOD_FABRICS].AfraidWater = 0;
	Goods[GOOD_FABRICS].canbecontraband	= 0;
	
	Goods[GOOD_SAILCLOTH].Name		= "Sailcloth";
	Goods[GOOD_SAILCLOTH].Weight	= 2;
	Goods[GOOD_SAILCLOTH].Cost		= 5;
	Goods[GOOD_SAILCLOTH].Units		= 1;
	Goods[GOOD_SAILCLOTH].Swim.Model= "roll_of_materials";
	Goods[GOOD_SAILCLOTH].Swim.Time	= 45; // boal 10
	Goods[GOOD_SAILCLOTH].AfraidWater = 0;
	Goods[GOOD_SAILCLOTH].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_SAILCLOTH].canbecontraband	= 0;
	
	Goods[GOOD_BALLS].Name			= "Balls";
	Goods[GOOD_BALLS].Cost			= 4;
	Goods[GOOD_BALLS].Weight		= 2;
	Goods[GOOD_BALLS].Units			= 20;
	Goods[GOOD_BALLS].SpeedV0		= 1.0;
	Goods[GOOD_BALLS].DamageHull	= 8.0;
	Goods[GOOD_BALLS].DamageRig		= 0.5;
	Goods[GOOD_BALLS].DamageCrew	= 0.2;
	Goods[GOOD_BALLS].AfraidWater = 0;    // рудимент от к3
	Goods[GOOD_BALLS].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_BALLS].canbecontraband	= 0;  // рудимент от к3
	
	Goods[GOOD_GRAPES].Name			= "Grapes";
	Goods[GOOD_GRAPES].Cost			= 12;
	Goods[GOOD_GRAPES].Weight		= 1;
	Goods[GOOD_GRAPES].Units		= 20;
	Goods[GOOD_GRAPES].SpeedV0		= 0.6; // boal
	Goods[GOOD_GRAPES].DamageHull	= 1.0;
	Goods[GOOD_GRAPES].DamageRig	= 2.0;
	Goods[GOOD_GRAPES].DamageCrew	= 1.5;
	Goods[GOOD_GRAPES].AfraidWater	= 0;
	Goods[GOOD_GRAPES].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_GRAPES].canbecontraband	= 0;
	
	Goods[GOOD_KNIPPELS].Name		= "Knippels";
	Goods[GOOD_KNIPPELS].Cost		= 26;
	Goods[GOOD_KNIPPELS].Weight		= 2;
	Goods[GOOD_KNIPPELS].Units		= 20;
	Goods[GOOD_KNIPPELS].SpeedV0	= 0.9;
	Goods[GOOD_KNIPPELS].DamageHull = 1.5;
	Goods[GOOD_KNIPPELS].DamageRig	= 9.0;
	Goods[GOOD_KNIPPELS].DamageCrew = 0.3;
	Goods[GOOD_KNIPPELS].AfraidWater = 0;
	Goods[GOOD_KNIPPELS].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_KNIPPELS].canbecontraband	= 0;
	
	Goods[GOOD_LEATHER].Name	    = "Leather";
	Goods[GOOD_LEATHER].Weight	    = 1;
	Goods[GOOD_LEATHER].Cost	    = 14;
	Goods[GOOD_LEATHER].Units	    = 1;
	Goods[GOOD_LEATHER].Swim.Model	= "bale";
	Goods[GOOD_LEATHER].Swim.Time	= 30;
	Goods[GOOD_LEATHER].AfraidWater = 1;
	Goods[GOOD_LEATHER].canbecontraband	= 0;
	
	Goods[GOOD_RUM].Name		    = "Rum";
	Goods[GOOD_RUM].Weight		    = 1;
	Goods[GOOD_RUM].Cost		    = 13;
	Goods[GOOD_RUM].Units		    = 1;
	Goods[GOOD_RUM].Swim.Model	    = "barrel";
	Goods[GOOD_RUM].Swim.Time	    = 30;
	Goods[GOOD_RUM].AfraidWater = 1;
	Goods[GOOD_RUM].canbecontraband	= 0;
	
	Goods[GOOD_ALE].Name	        = "Ale";
	Goods[GOOD_ALE].Weight	        = 1;
	Goods[GOOD_ALE].Cost	        = 7;
	Goods[GOOD_ALE].Units	        = 1;
	Goods[GOOD_ALE].Swim.Model	    = "barrel";
	Goods[GOOD_ALE].Swim.Time	    = 30;
	Goods[GOOD_ALE].AfraidWater = 1;
	Goods[GOOD_ALE].canbecontraband	= 0;
	
	Goods[GOOD_OIL].Name	        = "Oil";
	Goods[GOOD_OIL].Weight	        = 1;
	Goods[GOOD_OIL].Cost	        = 10;
	Goods[GOOD_OIL].Units	        = 1;
	Goods[GOOD_OIL].Swim.Model	    = "barrel";
	Goods[GOOD_OIL].Swim.Time	    = 20;
	Goods[GOOD_OIL].AfraidWater = 0;
	Goods[GOOD_OIL].canbecontraband	= 1;
	Goods[GOOD_OIL].Norm          = 2000;

	Goods[GOOD_POWDER].Name		    = "Powder";
	Goods[GOOD_POWDER].Weight	    = 1;
	Goods[GOOD_POWDER].Cost	        = 40;
	Goods[GOOD_POWDER].Units	    = 20;
	Goods[GOOD_POWDER].AfraidWater = 1;
	Goods[GOOD_POWDER].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_POWDER].canbecontraband	= 0;
	Goods[GOOD_FOOD].Norm          = 12000;
		
	Goods[GOOD_WEAPON].Name	  	    = "Weapon";
	Goods[GOOD_WEAPON].Weight	    = 1;
	Goods[GOOD_WEAPON].Cost	        = 120;
	Goods[GOOD_WEAPON].Units	    = 10;
	Goods[GOOD_WEAPON].AfraidWater = 0;
	Goods[GOOD_WEAPON].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_WEAPON].canbecontraband	= 0;
	Goods[GOOD_WEAPON].Norm          = 6000; 

	Goods[GOOD_SILK].Name	        = "Silk";
	Goods[GOOD_SILK].Weight	        = 1;
	Goods[GOOD_SILK].Cost	        = 62;
	Goods[GOOD_SILK].Units	        = 1;
	Goods[GOOD_SILK].Swim.Model	    = "roll_of_rolls";
	Goods[GOOD_SILK].Swim.Time	    = 30;
	Goods[GOOD_SILK].AfraidWater = 3;
	Goods[GOOD_SILK].canbecontraband	= 1;	
	
	Goods[GOOD_MEDICAMENT].Name		    = "Medicament";
	Goods[GOOD_MEDICAMENT].Weight	    = 1;
	Goods[GOOD_MEDICAMENT].Cost		    = 95;
	Goods[GOOD_MEDICAMENT].Units	    = 30;
	Goods[GOOD_MEDICAMENT].Swim.Model	= "box";
	Goods[GOOD_MEDICAMENT].Swim.Time	= 45;
	Goods[GOOD_MEDICAMENT].AfraidWater = 0;
	Goods[GOOD_MEDICAMENT].canbecontraband	= 0;
	Goods[GOOD_MEDICAMENT].Norm          = 6000; 
	
	Goods[GOOD_MAHOGANY].Name	    = "Mahogany";
	Goods[GOOD_MAHOGANY].Weight	    = 4;
	Goods[GOOD_MAHOGANY].Cost	    = 250;
	Goods[GOOD_MAHOGANY].Units	    = 1;
	Goods[GOOD_MAHOGANY].Swim.Model	= "roll_of_planks";
	Goods[GOOD_MAHOGANY].Swim.Time	= 45;
	Goods[GOOD_MAHOGANY].AfraidWater = 1;
	Goods[GOOD_MAHOGANY].canbecontraband	= 1;
	Goods[GOOD_MAHOGANY].Norm          = 3000;

    Goods[GOOD_EBONY].Name		    = "Ebony";
	Goods[GOOD_EBONY].Weight	    = 5;
	Goods[GOOD_EBONY].Cost		    = 190;
	Goods[GOOD_EBONY].Units		    = 1;
	Goods[GOOD_EBONY].canbecontraband	= 1;
	Goods[GOOD_EBONY].Swim.Model	= "roll_of_planks";
	Goods[GOOD_EBONY].Swim.Time	= 20; 
	Goods[GOOD_EBONY].AfraidWater = 0;    
	Goods[GOOD_EBONY].Norm          = 2500;  

	Goods[GOOD_FOOD].Name		    = "Food";
	Goods[GOOD_FOOD].Weight	        = 1;
	Goods[GOOD_FOOD].Cost	        = 90;
	Goods[GOOD_FOOD].Units	        = 10;
	Goods[GOOD_FOOD].Swim.Model	    = "barrel";
	Goods[GOOD_FOOD].Swim.Time	    = 45;
	Goods[GOOD_FOOD].AfraidWater = 1;
	Goods[GOOD_FOOD].type				= TRADE_TYPE_AMMUNITION;
	Goods[GOOD_FOOD].canbecontraband	= 0;	
	Goods[GOOD_FOOD].Norm          = 8000;
	
	Goods[GOOD_CITRUSES].Name		    = "Citruses";
	Goods[GOOD_CITRUSES].Weight	    = 1;
	Goods[GOOD_CITRUSES].Cost		    = 16;
	Goods[GOOD_CITRUSES].Units	    = 1;
	Goods[GOOD_CITRUSES].Swim.Model	= "box";
	Goods[GOOD_CITRUSES].Swim.Time	= 25;
	Goods[GOOD_CITRUSES].AfraidWater = 3;
	Goods[GOOD_CITRUSES].canbecontraband	= 0;
	
	Goods[GOOD_COPRA].Name		    = "Copra";
	Goods[GOOD_COPRA].Weight	    = 2;
	Goods[GOOD_COPRA].Cost		    = 18;
	Goods[GOOD_COPRA].Units		    = 1;
	Goods[GOOD_COPRA].Swim.Model	= "basket";
	Goods[GOOD_COPRA].Swim.Time		= 30;
	Goods[GOOD_COPRA].AfraidWater = 3;
	Goods[GOOD_COPRA].canbecontraband	= 0;
	Goods[GOOD_COPRA].Norm          = 5000;  
	
	Goods[GOOD_WHEAT].Name		    = "Wheat";
	Goods[GOOD_WHEAT].Weight	    = 1;
	Goods[GOOD_WHEAT].Cost		    = 10;
	Goods[GOOD_WHEAT].Units		    = 1;
	Goods[GOOD_WHEAT].Swim.Model	= "sack";
	Goods[GOOD_WHEAT].Swim.Time		= 30;
	Goods[GOOD_WHEAT].AfraidWater = 3;
	Goods[GOOD_WHEAT].canbecontraband	= 0;  
	
	Goods[GOOD_SUGAR].Name		    = "Sugar";
	Goods[GOOD_SUGAR].Weight	    = 2;
	Goods[GOOD_SUGAR].Cost		    = 18;
	Goods[GOOD_SUGAR].Units		    = 1;
	Goods[GOOD_SUGAR].AfraidWater = 3;
	Goods[GOOD_SUGAR].canbecontraband	= 0;
	Goods[GOOD_SUGAR].Norm          = 5000;  
	
	Goods[GOOD_WINE].Name		    = "Wine";
	Goods[GOOD_WINE].Weight	        = 2;
	Goods[GOOD_WINE].Cost		    = 45;
	Goods[GOOD_WINE].Units		    = 1;
	Goods[GOOD_WINE].Swim.Model	    = "barrel";
	Goods[GOOD_WINE].Swim.Time	    = 30;
	Goods[GOOD_WINE].AfraidWater = 1;
	Goods[GOOD_WINE].canbecontraband	= 0;
	Goods[GOOD_WINE].Norm          = 5000;

    Goods[GOOD_COTTON].Name		    = "Cotton";
	Goods[GOOD_COTTON].Weight	    = 1;
	Goods[GOOD_COTTON].Cost		    = 13;
	Goods[GOOD_COTTON].Units	    = 1;
	Goods[GOOD_COTTON].Swim.Model	= "bale";
	Goods[GOOD_COTTON].Swim.Time	= 25; 
	Goods[GOOD_COTTON].AfraidWater = 3;
	Goods[GOOD_COTTON].canbecontraband	= 0;

	Goods[GOOD_CINNAMON].Name	    = "Cinnamon";
	Goods[GOOD_CINNAMON].Weight	    = 2;
	Goods[GOOD_CINNAMON].Cost	    = 37;
	Goods[GOOD_CINNAMON].Units	    = 1;
	Goods[GOOD_CINNAMON].Swim.Model	= "bale";
	Goods[GOOD_CINNAMON].Swim.Time	= 25;
	Goods[GOOD_CINNAMON].AfraidWater = 3;
	Goods[GOOD_CINNAMON].canbecontraband	= 1;
	Goods[GOOD_CINNAMON].Norm          = 5000; 

	Goods[GOOD_PAPRIKA].Name	    = "Paprika";
	Goods[GOOD_PAPRIKA].Weight	    = 2;
	Goods[GOOD_PAPRIKA].Cost	    = 25;
	Goods[GOOD_PAPRIKA].Units	    = 1;
	Goods[GOOD_PAPRIKA].Swim.Model	= "box";
	Goods[GOOD_PAPRIKA].Swim.Time	= 25;
	Goods[GOOD_PAPRIKA].AfraidWater = 3;
	Goods[GOOD_PAPRIKA].canbecontraband	= 1;
	Goods[GOOD_PAPRIKA].Norm          = 5000;

	Goods[GOOD_DYES].Name	    = "Dyes";
	Goods[GOOD_DYES].Weight	    = 2;
	Goods[GOOD_DYES].Cost	    = 25;
	Goods[GOOD_DYES].Units	    = 1;
	Goods[GOOD_DYES].Swim.Model	= "box";
	Goods[GOOD_DYES].Swim.Time	= 25;
	Goods[GOOD_DYES].AfraidWater = 3;
	Goods[GOOD_DYES].canbecontraband	= 1;
	Goods[GOOD_DYES].Norm          = 5000; 	 	

	Goods[GOOD_CACAO].Name		= "Cacao";
	Goods[GOOD_CACAO].Weight	= 2;
	Goods[GOOD_CACAO].Cost		= 50;
	Goods[GOOD_CACAO].Units		= 1;
	Goods[GOOD_CACAO].Swim.Model= "bale";
	Goods[GOOD_CACAO].Swim.Time	= 25;
	Goods[GOOD_CACAO].AfraidWater = 3;
	Goods[GOOD_CACAO].canbecontraband	= 1;  
	Goods[GOOD_CACAO].Norm          = 5000;  

	Goods[GOOD_TOBACCO].Name	    = "Tobacco";
	Goods[GOOD_TOBACCO].Weight	    = 2;
	Goods[GOOD_TOBACCO].Cost	    = 65;
	Goods[GOOD_TOBACCO].Units	    = 1;
	Goods[GOOD_TOBACCO].Swim.Model	= "bale";
	Goods[GOOD_TOBACCO].Swim.Time	= 25;
	Goods[GOOD_TOBACCO].AfraidWater = 3;
	Goods[GOOD_TOBACCO].canbecontraband	= 1;
	Goods[GOOD_TOBACCO].Norm          = 5000;  

	Goods[GOOD_COFFEE].Name		    = "Coffee";
	Goods[GOOD_COFFEE].Weight	    = 2;
	Goods[GOOD_COFFEE].Cost		    = 93;
	Goods[GOOD_COFFEE].Units	    = 1;
	Goods[GOOD_COFFEE].Swim.Model	= "sack";
	Goods[GOOD_COFFEE].Swim.Time	= 25;
	Goods[GOOD_COFFEE].AfraidWater = 3;
	Goods[GOOD_COFFEE].canbecontraband	= 1;
	Goods[GOOD_COFFEE].Norm          = 5000;

	Goods[GOOD_TEA].Name		= "Tea";
	Goods[GOOD_TEA].Weight	    = 2;
	Goods[GOOD_TEA].Cost		= 93;
	Goods[GOOD_TEA].Units	    = 1;
	Goods[GOOD_TEA].Swim.Model	= "sack";
	Goods[GOOD_TEA].Swim.Time	= 25;
	Goods[GOOD_TEA].AfraidWater = 3;
	Goods[GOOD_TEA].canbecontraband	= 1;
	Goods[GOOD_TEA].Norm          = 5000;
	
	Goods[GOOD_IRON].Name		    = "Iron";
	Goods[GOOD_IRON].Weight	        = 1;
	Goods[GOOD_IRON].Cost	        = 230;
	Goods[GOOD_IRON].Units	        = 1;
	Goods[GOOD_IRON].AfraidWater    = 0;
	Goods[GOOD_IRON].canbecontraband	= 0;
	Goods[GOOD_IRON].Norm          = 2500;

	Goods[GOOD_COPPER].Name		    = "Copper";
	Goods[GOOD_COPPER].Weight	    = 1;
	Goods[GOOD_COPPER].Cost	        = 230;
	Goods[GOOD_COPPER].Units	    = 1;
	Goods[GOOD_COPPER].AfraidWater = 0;
	Goods[GOOD_COPPER].canbecontraband	= 0;
	Goods[GOOD_COPPER].Norm          = 2500;

	Goods[GOOD_SALTPETER].Name		    = "Saltpeter";
	Goods[GOOD_SALTPETER].Weight	    = 1;
	Goods[GOOD_SALTPETER].Cost	        = 230;
	Goods[GOOD_SALTPETER].Units	        = 1;
	Goods[GOOD_SALTPETER].AfraidWater   = 0;
	Goods[GOOD_SALTPETER].canbecontraband	= 0;
	Goods[GOOD_SALTPETER].Norm          = 2500;      	

	Goods[GOOD_SILVER].Name		    = "Silver";
	Goods[GOOD_SILVER].Weight	    = 1;
	Goods[GOOD_SILVER].Cost	        = 230;
	Goods[GOOD_SILVER].Units	    = 1;
	Goods[GOOD_SILVER].AfraidWater = 0;
	Goods[GOOD_SILVER].canbecontraband	= 0;
	Goods[GOOD_SILVER].Norm          = 2500; 
	
	Goods[GOOD_GOLD].Name		    = "Gold";
	Goods[GOOD_GOLD].Weight	        = 2;
	Goods[GOOD_GOLD].Cost	        = 510;
	Goods[GOOD_GOLD].Units	        = 1;
	Goods[GOOD_GOLD].AfraidWater = 0;
	Goods[GOOD_GOLD].canbecontraband	= 0;
	Goods[GOOD_GOLD].Norm          = 1500; 
	
	Goods[GOOD_SLAVES].Name		    = "Slaves";
	Goods[GOOD_SLAVES].Weight	    = 1;
	Goods[GOOD_SLAVES].Cost		    = 110;
	Goods[GOOD_SLAVES].Units	    = 1;
	Goods[GOOD_SLAVES].Swim.Model	= "lo_man";
	Goods[GOOD_SLAVES].Swim.Time	= 20;
	Goods[GOOD_SLAVES].AfraidWater = 0;
	Goods[GOOD_SLAVES].canbecontraband	= 1;
	Goods[GOOD_SLAVES].Norm          = 1000; 
		
	////////////////////////////////////////////////////// пушки это товар - boal 27/07/06	
	Goods[GOOD_CANNON_8].Name			= "Cannon_8";
	Goods[GOOD_CANNON_8].CannonIdx		= CANNON_TYPE_CANNON_LBS8;
	Goods[GOOD_CANNON_8].Cost			= Cannon[CANNON_TYPE_CANNON_LBS8].Cost;
	Goods[GOOD_CANNON_8].Weight		    = Cannon[CANNON_TYPE_CANNON_LBS8].Weight;
	Goods[GOOD_CANNON_8].FireRange	    = Cannon[CANNON_TYPE_CANNON_LBS8].FireRange;
	Goods[GOOD_CANNON_8].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS8].DamageMultiply;
	Goods[GOOD_CANNON_8].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS8]));
	Goods[GOOD_CANNON_8].Units			= 1;
	Goods[GOOD_CANNON_8].AfraidWater	= 0;
	Goods[GOOD_CANNON_8].type			= TRADE_TYPE_CANNONS;
	Goods[GOOD_CANNON_8].canbecontraband	= 0;
	Goods[GOOD_CANNON_8].NotSale		= 0;
	Goods[GOOD_CANNON_8].Norm           = 30; 
	
	Goods[GOOD_CANNON_12].Name			= "Cannon_12";
	Goods[GOOD_CANNON_12].CannonIdx		= CANNON_TYPE_CANNON_LBS12;
	Goods[GOOD_CANNON_12].Cost			= Cannon[CANNON_TYPE_CANNON_LBS12].Cost;
	Goods[GOOD_CANNON_12].Weight		= Cannon[CANNON_TYPE_CANNON_LBS12].Weight;
	Goods[GOOD_CANNON_12].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS12].FireRange;
	Goods[GOOD_CANNON_12].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS12].DamageMultiply;
	Goods[GOOD_CANNON_12].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS12]));
	Goods[GOOD_CANNON_12].Units			= 1;
	Goods[GOOD_CANNON_12].AfraidWater	= 0;
	Goods[GOOD_CANNON_12].type				= TRADE_TYPE_CANNONS;
	Goods[GOOD_CANNON_12].canbecontraband	= 0;
	Goods[GOOD_CANNON_12].NotSale		= 0;
	Goods[GOOD_CANNON_12].Norm          = 25; 
	
	Goods[GOOD_CANNON_16].Name			= "Cannon_16";
	Goods[GOOD_CANNON_16].CannonIdx		= CANNON_TYPE_CANNON_LBS16;
	Goods[GOOD_CANNON_16].Cost			= Cannon[CANNON_TYPE_CANNON_LBS16].Cost;
	Goods[GOOD_CANNON_16].Weight		= Cannon[CANNON_TYPE_CANNON_LBS16].Weight;
	Goods[GOOD_CANNON_16].Units			= 1;
	Goods[GOOD_CANNON_16].AfraidWater	= 0;
	Goods[GOOD_CANNON_16].type				= TRADE_TYPE_CANNONS;
	Goods[GOOD_CANNON_16].canbecontraband	= 0;
	Goods[GOOD_CANNON_16].NotSale		= 0;
	Goods[GOOD_CANNON_16].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS16].FireRange;
	Goods[GOOD_CANNON_16].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS16].DamageMultiply;
	Goods[GOOD_CANNON_16].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS16]));
	Goods[GOOD_CANNON_16].Norm          = 20; 
	
	Goods[GOOD_CANNON_24].Name			= "Cannon_24";
	Goods[GOOD_CANNON_24].CannonIdx		= CANNON_TYPE_CANNON_LBS24;
	Goods[GOOD_CANNON_24].Cost			= Cannon[CANNON_TYPE_CANNON_LBS24].Cost;
	Goods[GOOD_CANNON_24].Weight		= Cannon[CANNON_TYPE_CANNON_LBS24].Weight;
	Goods[GOOD_CANNON_24].Units			= 1;
	Goods[GOOD_CANNON_24].AfraidWater	= 0;
	Goods[GOOD_CANNON_24].type				= TRADE_TYPE_CANNONS;
	Goods[GOOD_CANNON_24].canbecontraband	= 0;
	Goods[GOOD_CANNON_24].NotSale   	= 0;
	Goods[GOOD_CANNON_24].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS24].FireRange;
	Goods[GOOD_CANNON_24].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS24].DamageMultiply;
	Goods[GOOD_CANNON_24].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS24]));
	Goods[GOOD_CANNON_24].Norm          = 15; 
	
	Goods[GOOD_CANNON_32].Name			= "Cannon_32";
	Goods[GOOD_CANNON_32].CannonIdx		= CANNON_TYPE_CANNON_LBS32;
	Goods[GOOD_CANNON_32].Cost			= Cannon[CANNON_TYPE_CANNON_LBS32].Cost;
	Goods[GOOD_CANNON_32].Weight		= Cannon[CANNON_TYPE_CANNON_LBS32].Weight;
	Goods[GOOD_CANNON_32].Units			= 1;
	Goods[GOOD_CANNON_32].AfraidWater	= 0;
	Goods[GOOD_CANNON_32].type				= TRADE_TYPE_CANNONS;
	Goods[GOOD_CANNON_32].canbecontraband	= 0;
	Goods[GOOD_CANNON_32].NotSale		= 0;
	Goods[GOOD_CANNON_32].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS32].FireRange;
	Goods[GOOD_CANNON_32].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS32].DamageMultiply;
	Goods[GOOD_CANNON_32].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS32]));
	Goods[GOOD_CANNON_32].Norm          = 10; 
	
	Goods[GOOD_CANNON_42].Name			= "Cannon_42";
	Goods[GOOD_CANNON_42].CannonIdx		= CANNON_TYPE_CANNON_LBS42;
	Goods[GOOD_CANNON_42].Cost			= Cannon[CANNON_TYPE_CANNON_LBS42].Cost;
	Goods[GOOD_CANNON_42].Weight		= Cannon[CANNON_TYPE_CANNON_LBS42].Weight;
	Goods[GOOD_CANNON_42].Units			= 1;
	Goods[GOOD_CANNON_42].AfraidWater	= 0;
	Goods[GOOD_CANNON_42].type				= TRADE_TYPE_CANNONS;
	Goods[GOOD_CANNON_42].canbecontraband	= 0;
	Goods[GOOD_CANNON_42].NotSale		= 1;
	Goods[GOOD_CANNON_42].FireRange		    = Cannon[CANNON_TYPE_CANNON_LBS42].FireRange;
	Goods[GOOD_CANNON_42].DamageMultiply	= Cannon[CANNON_TYPE_CANNON_LBS42].DamageMultiply;
	Goods[GOOD_CANNON_42].ReloadTime		= sti(GetCannonReloadTime(&Cannon[CANNON_TYPE_CANNON_LBS42]));
	Goods[GOOD_CANNON_42].Norm          = 10; 

	// boal 24/01/08 Норма товара в магазине (режим Экспорта), то есть максимум, ниже установлены исключения
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		if (!CheckAttribute(&Goods[i], "Norm"))
		{
			Goods[i].Norm          = 10000; 
		}
	}
}
#define CANNON_TYPES_QUANTITY		7

#define CANNON_TYPE_CANNON_LBS8	    0
#define CANNON_TYPE_CANNON_LBS12    1
#define CANNON_TYPE_CANNON_LBS16    2
#define CANNON_TYPE_CANNON_LBS24    3
#define CANNON_TYPE_CANNON_LBS32    4
#define CANNON_TYPE_CANNON_LBS42    5
#define CANNON_TYPE_CANNON_LBS48    6

#define CANNON_TYPE_NONECANNON		1000

#define CANNON_NAME_CANNON              1

object  Cannon[CANNON_TYPES_QUANTITY];

ref GetCannonByType(int iCannonType) 
{ 
	if (iCannonType == CANNON_TYPE_NONECANNON) return &NullCharacter; // fix для тартант boal
	return &Cannon[iCannonType]; 
}

int GetCannonCaliber(int nCannon)
{
    switch(nCannon)
    {
		case CANNON_TYPE_NONECANNON:
            return 0;
        break;
	
        case CANNON_TYPE_CANNON_LBS8:
            return 8;
        break;
    
        case CANNON_TYPE_CANNON_LBS12:
            return 12;
        break;
    
        case CANNON_TYPE_CANNON_LBS16:
            return 16;
        break;
    
        case CANNON_TYPE_CANNON_LBS24:
            return 24;
        break;
    
        case CANNON_TYPE_CANNON_LBS32:
            return 32;
        break;
		
        case CANNON_TYPE_CANNON_LBS42:
            return 42;
        break;
		
        case CANNON_TYPE_CANNON_LBS48:
            return 48;
        break;
    }
}
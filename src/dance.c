#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../common/HPMi.h"
#include "../map/clif.h"
#include "../map/atcommand.h"
#include "../map/script.h"
#include "../map/pc.h"

#include "../common/HPMDataCheck.h"

HPExport struct hplugin_info pinfo =
{
    "@dance",		// Plugin name
    SERVER_TYPE_MAP,// Which server types this plugin works with?
    "0.1b",			// Plugin version
    HPM_VERSION,	// HPM Version (don't change, macro is automatically updated)
};


ACMD(dance){
int msg;

msg = rand()%9;
switch(msg){
	case 0:
	case 1:
	case 3:
	case 5:
	case 7:
	case 9:
		clif->specialeffect(&sd->bl, 400, ALL_CLIENT);
		if (msg==0 || msg==1) {clif->specialeffect(&sd->bl, 413, ALL_CLIENT);}
		else if(msg==3){clif->specialeffect(&sd->bl, 415, ALL_CLIENT);}
		else if(msg==5){clif->specialeffect(&sd->bl, 458, ALL_CLIENT);}
		else if(msg==7){clif->specialeffect(&sd->bl, 501, ALL_CLIENT);}
		else{clif->specialeffect(&sd->bl, 550, ALL_CLIENT);}
		break;
	case 2:
	case 4:
	case 6:
	case 8:
		clif->specialeffect(&sd->bl, 300, ALL_CLIENT);
		if (msg==2){clif->specialeffect(&sd->bl, 414, ALL_CLIENT);}
		else if (msg==4){ clif->specialeffect(&sd->bl, 426, ALL_CLIENT); }
		else if (msg==6){ clif->specialeffect(&sd->bl, 466, ALL_CLIENT); }
		else { clif->specialeffect(&sd->bl, 540, ALL_CLIENT); }
	
}
return true;
}



/* Server Startup */
HPExport void plugin_init (void)
{
	addAtcommand("dance",dance);
}
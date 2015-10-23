/*
=============================================
@arealoot
Converted by: Dastgir
Original Made by: Streusel
================================================
v1.0 Initial Release
Autoloots item in x by x Range
*/
#include "common/hercules.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common/HPMi.h"
#include "common/mmo.h"
#include "common/socket.h"
#include "common/memmgr.h"
#include "common/nullpo.h"
#include "common/mapindex.h"
#include "common/strlib.h"
#include "common/utils.h"
#include "common/cbasetypes.h"
#include "common/timer.h"
#include "common/showmsg.h"
#include "common/conf.h"
#include "common/db.h"
#include "common/sql.h"

#include "map/atcommand.h"
#include "map/battle.h"
#include "map/clif.h"
#include "map/map.h"
#include "map/pc.h"
#include "map/skill.h"
#include "map/itemdb.h"

#include "common/HPMDataCheck.h"

HPExport struct hplugin_info pinfo = {
	"@arealoot",			// Plugin name
	SERVER_TYPE_MAP,	// Which server types this plugin works with?
	"1.0",				// Plugin version
	HPM_VERSION,		// HPM Version (don't change, macro is automatically updated)
};

int arealoot_range = 3;		//x BY x Range

struct area_p_data {
	bool arealoot;
	bool in_process;
};

struct area_p_data* adb_search(struct map_session_data* sd){
	struct area_p_data *data;
	if( !(data = getFromMSD(sd,0)) ) {
		CREATE(data,struct area_p_data,1);
		addToMSD(sd,data,0,true);
	}
	return data;
}

/*==========================================
 * @arealoot
 *------------------------------------------*/
ACMD(arealoot) {
	struct area_p_data *data;
	data = adb_search(sd);
	if (data->arealoot) {
		data->arealoot = false;
		clif->message(fd, "Arealoot is now off.");
		return true;
	}
	data->arealoot = true;
	clif->message(fd, "Arealoot is now on.");
	
	return true;
}


int arealoot_item(struct map_session_data *sd,struct flooritem_data *fitem){
	struct area_p_data *data;
	data = adb_search(sd);
	if (data->arealoot && data->in_process==false){
		data->in_process = true;
		map->foreachinrange(skill->greed, &fitem->bl, arealoot_range, BL_ITEM, &sd->bl);
		hookStop();
		data->in_process = false;
		return 1;
	}
	return 1;
}

void arealoot_range_setting(const char *val) {
	int value = atoi(val);
	if (value < 1 || value > 10){ ShowError("'arealoot_range' is set to %d,(Min:1,Max:10)", value); return; }	//1 to 9 Range.
	arealoot_range = value;
	ShowDebug("Arealoot_Range set to %d",arealoot_range);
}

/* run when server starts */
HPExport void plugin_init (void) {
    addAtcommand("arealoot",arealoot);
	addHookPre("pc->takeitem",arealoot_item);
}

HPExport void server_online (void) {
	ShowInfo ("'%s' Plugin by Dastgir/Hercules. Version '%s'\n",pinfo.name,pinfo.version);
}

HPExport void server_preinit (void) {
	addBattleConf("arealoot_range",arealoot_range_setting);
}

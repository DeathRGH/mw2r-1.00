#include "debug.h"

#include "utility.h"

void PrintLoadedZones() {
	uartprintf("[MW2R 1.00] ========== Loaded Zones ==========\n");
	uint64_t ptr = 0x0000000002F08140;
	int count = 0;

	while (*(char *)(ptr + 0x110) != 0) {
		uartprintf("[MW2R 1.00] %s\n", (char *)(ptr + 0x110));
		ptr += 0xF8;
		count++;
	}

	uartprintf("[MW2R 1.00] -> A total of %i zones are loaded.\n", count);
	uartprintf("[MW2R 1.00] ==================================\n");
}

//build string stuff
//0000000000527877 loc_527877

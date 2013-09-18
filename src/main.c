#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <penetra/error.h>


#include "dissect.h"
#include "util.h"

#define DISSECT "dissect"

static void _penetra_help()
{
    HELP("\n");
    HELP("Tool to analyse PE binary.\n");
    HELP("Usage: penetra <command> [-h] <options> \n");
    HELP("Commands:\n");
    HELP("         dissect \tShow PE binary info. \n");
    HELP("\n");
    exit(PENETRA_SUCCESS);
}



int main(int argc, char **argv)
{
	Dissect dissect;
	_u32 error;
	(void)error;

    if (argc == 1) {
        _penetra_help();
        return -1;
    }

    if (strncmp(argv[1], DISSECT, sizeof(DISSECT)) == 0) {
        error = dissect_init(&dissect, argc, argv);
        dissect_finish(&dissect);
    } else {
		_penetra_help();
    }

	return 0;
}


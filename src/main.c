#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <penetra/error.h>

#include <unstable/unstable.h>

#include "dissect.h"
#include "util.h"

#define DISSECT "dissect"

static void _penalise_help()
{
    HELP("\n");
    HELP("Tool to analise PE binary.\n");
    HELP("Usage: penalise <command> [-h] <options> \n");
    HELP("Commands:\n");
    HELP("         dissect \tShow PE binary info. \n");
    HELP("\n");
    exit(PENETRA_SUCCESS);
}



int main(int argc, char **argv)
{

    if (argc == 1) {
        _penalise_help();
        return -1;
    }

    if (strncmp(argv[1], DISSECT, sizeof(DISSECT)) == 0) {
        //error = malelf_dissect_init(&dissect, argc, argv);
        //malelf_dissect_finish(&dissect);
         printf("Dissecando! =)\n");
    } else {
         printf("Error Bitch! =)\n");
    }

	return 0;
}


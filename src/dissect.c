#include <stdio.h>
#include <stdlib.h>

#include <penetra/penetra.h>

#include "util.h"

void dissect_help(void)
{
    HELP("\n");
    HELP("This command display information about the PE binary.\n");
    HELP("Usage: penalise dissect <options>\n");
    HELP("         -h, --help     \tDissect Help\n");
    HELP("         -i, --input    \tBinary File\n");
    HELP("         -e, --coff     \tDisplay COFF Header\n");
    HELP("         -s, --dos      \tDisplay DOS Header \n");
    HELP("         -p, --optional \tDisplay Optional Header \n");
    HELP("         -S, --stable   \tDisplay Symbol Table\n");
    HELP("         -f, --format   \tOutput Format (XML or Stdout). Default is Stdout.\n");
    HELP("         -o, --output   \tOutput File.\n");
    HELP("Example: penalise dissect -i /tmp/putty.exe -f xml -o /tmp/putty.xml\n");
    HELP("\n");
    exit(PENETRA_SUCCESS);
}



#ifndef __DISSECT_H__
#define __DISSECT_H__

#include <penetra/types.h>

/*
 * Dissect Options
 */
#define DISSECT_FORMAT   'f'
#define DISSECT_COFF     'c'
#define DISSECT_OPTIONAL 'p'
#define DISSECT_BINARY   'i'
#define DISSECT_FILE     'o'
#define DISSECT_UNKNOWN  '?'

/* Store info about dissect */
typedef struct  {
        char *fname;                       /* Output File */
} Dissect;


_u32 dissect_init(Dissect *obj, int argc, char **argv);

_u32 dissect_finish(Dissect *obj);

void dissect_help();


#endif /* __DISSECT_H__ */


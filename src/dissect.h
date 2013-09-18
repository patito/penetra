#ifndef __DISSECT_H__
#define __DISSECT_H__

#include <penetra/types.h>
#include <penetra/penetra.h>

/*
 * Dissect Options
 */
#define DISSECT_ALL      'a'
#define DISSECT_DOS      'd'
#define DISSECT_COFF     'c'
#define DISSECT_HELP     'h'
#define DISSECT_OPTIONAL 't'
#define DISSECT_BINARY   'i'
#define DISSECT_UNKNOWN  '?'

/* Store info about dissect */
typedef struct  {
	Penetra pen;
	char *fname;
	_u8 flag_dos;
	_u8 flag_coff;
	_u8 flag_optional;
	_u8 flag_all;
} Dissect;


_u32 dissect_init(Dissect *obj, int argc, char **argv);

_u32 dissect_finish(Dissect *obj);

void dissect_help();


#endif /* __DISSECT_H__ */


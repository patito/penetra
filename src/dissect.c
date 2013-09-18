#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <penetra/penetra.h>

#include <unstable/unstable.h>

#include "util.h"
#include "dissect.h"

void dissect_help(void)
{
    HELP("\n");
    HELP("This command display information about the PE binary.\n");
    HELP("Usage: penetra dissect <options>\n");
    HELP("         -h, --help     \tDissect Help\n");
    HELP("         -a, --all      \tShow all Headers. Default option.\n");
    HELP("         -i, --input    \tInput Binary File\n");
    HELP("         -c, --coff     \tDisplay COFF Header\n");
    HELP("         -d, --dos      \tDisplay DOS Header \n");
    HELP("         -t, --optional \tDisplay Optional Header \n");
    HELP("Example: penetra dissect -i /tmp/putty.exe -a\n");
    HELP("\n");
    exit(PENETRA_SUCCESS);
}

static _u32 _dissect_coff_txt(Dissect *obj)
{
	_u32 status;
	PenetraNT nt;
	PenetraCoff coff;
	UnsTable table;

	if (NULL == obj) {
		return PENETRA_EINVAL;
	}
	
	status = penetra_get_nt(&obj->pen, &nt);
	if (PENETRA_SUCCESS != status) {
		return status;
	}

	status = penetra_nt_get_coff(&nt, &coff);
	if (PENETRA_SUCCESS != status) {
		return status;
	}

	char *headers[] = {"Structure Member", "Value", NULL};

	if (UNSTABLE_SUCCESS != unstable_init(&table, 80, 7, 2)) {
		return PENETRA_ERROR;
	}

	unstable_set_title(&table, "COFF Header");

	unstable_set_headers(&table, headers);

	unstable_add_str_value(&table, "Machine");
	unstable_add_hex_value(&table, coff.machine);
	
	unstable_add_str_value(&table, "Number of Sections");
	unstable_add_int_value(&table, coff.nsections);

	unstable_add_str_value(&table, "Time Date Stamp");
	unstable_add_int_value(&table, coff.tstamp);

	unstable_add_str_value(&table, "Pointer To Symbol Table");
	unstable_add_hex_value(&table, coff.symbol_table);

	unstable_add_str_value(&table, "Number of Symbols");
	unstable_add_int_value(&table, coff.nsymbols);

	unstable_add_str_value(&table, "Size of Optional Header");
	unstable_add_hex_value(&table, coff.size_opt_header);

	unstable_add_str_value(&table, "Characteristics");
	unstable_add_hex_value(&table, coff.characteristics);

	unstable_print(&table);

	unstable_finish(&table);

	return PENETRA_SUCCESS;
}

static _u32 _dissect(Dissect *obj)
{
	_u32 status;

	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	status = penetra_init(&obj->pen);
	if (PENETRA_SUCCESS != status) {
		return status;
	}

	status = penetra_open(&obj->pen, obj->fname);
	if (PENETRA_SUCCESS != status) {
		return status;
	}

	_dissect_coff_txt(obj);

	return PENETRA_SUCCESS;
}


static _u32 _dissect_set_flag_dos(Dissect *obj)
{
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	obj->flag_dos = 1;

	return PENETRA_SUCCESS;
}

static _u32 _dissect_set_flag_coff(Dissect *obj)
{
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	obj->flag_coff = 1;

	return PENETRA_SUCCESS;
}

static _u32 _dissect_set_flag_optional(Dissect *obj)
{
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	obj->flag_optional = 1;

	return PENETRA_SUCCESS;
}

static _u32 _dissect_set_flag_all(Dissect *obj)
{
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	obj->flag_all = 1;

	return PENETRA_SUCCESS;
}

static _u32 _dissect_set_binary_file(Dissect *obj, const char *fname)
{
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	if (NULL == fname) {
		return PENETRA_EINVAL;
	}

	obj->fname = strdup(fname);
	if (NULL == obj->fname) {
		return PENETRA_ENOMEM;
	}

	return PENETRA_SUCCESS;
}

static _u32 _dissect_handle_options(Dissect *obj, int option)
{
	static _u8 error = PENETRA_SUCCESS;

	switch (option) {
	case DISSECT_HELP:
		dissect_help();
		break;
	case DISSECT_COFF:
		error |= _dissect_set_flag_coff(obj);
		break;
	case DISSECT_DOS:
		error |= _dissect_set_flag_dos(obj);
		break;
	case DISSECT_OPTIONAL:
		error |= _dissect_set_flag_optional(obj);
		break;
	case DISSECT_BINARY:
		error |= _dissect_set_binary_file(obj, optarg);
		break;
	case DISSECT_ALL:
		error |= _dissect_set_flag_all(obj);
		break;
	case ':':
		printf("Unknown option character '%s'.\n", optarg);
		break;
	case DISSECT_UNKNOWN:
		dissect_help();
		error |= 1;
		break;
	}

	return error;
}

static _u32 _dissect_options(Dissect *obj, int argc, char **argv)
{
	_i32 option = 0;
	_u32 error = PENETRA_ERROR;
	int option_index = 0;
	static struct option long_options[] = {
		{"help", 0, 0, DISSECT_HELP},
		{"input", 1, 0, DISSECT_BINARY},
		{"coff", 0, 0, DISSECT_COFF},
		{"dos", 0, 0, DISSECT_DOS},
		{"optional", 0, 0, DISSECT_OPTIONAL},
		{"all", 0, 0, DISSECT_ALL},
		{0, 0, 0, 0}
	};

	if (2 == argc) {
		dissect_help();
		return PENETRA_EINVAL;
	}

	while ((option = getopt_long (argc, argv, "hi:cdta",
            long_options, &option_index)) != -1) {
		error = _dissect_handle_options(obj, option);
	}

	if (PENETRA_SUCCESS == error ) {
		error = _dissect(obj);
	} else {
		printf("Invalid arguments...\n");
		dissect_help();
	}

	return error;
}

_u32 dissect_init(Dissect *obj, int argc, char **argv)
{
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	obj->flag_dos = 0;
	obj->flag_coff = 0;
	obj->flag_optional = 0;
	obj->flag_all = 0;

	return _dissect_options(obj, argc, argv);
}

_u32 dissect_finish(Dissect *obj)
{
	_u32 status = PENETRA_SUCCESS;
	
	if (NULL == obj) {
		return PENETRA_EINVAL;
	}

	if (NULL != obj->fname) {
		free(obj->fname);
	}

	status = penetra_finish(&obj->pen);
	if (PENETRA_SUCCESS != status) {
		return status;
	}

	return status;
}



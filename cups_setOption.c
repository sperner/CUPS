#include <cups/cups.h>

int main(int argc, char* argv[])
{
	if( argc < 4 )
	{
		printf("Usage: %s <PrinterName> <OptionName> <OptionValue>\n", argv[0]);
		return -1;
	}

        int num_dests, num_options=0;
        cups_dest_t *dests, *dest;
        int job_id;

        num_dests = cupsGetDests(&dests);

	int i,j;
	cups_option_t* option;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(strcmp(dest->name, argv[1]) == 0)
			for(j = dest->num_options, option=dest->options; j > 0; j--, option++)
				if(strcmp(option->name, argv[2]) == 0)
				{
					num_options = cupsAddOption(argv[2], argv[3], dest->num_options, &option);
					printf("%s: Set '%s' to '%s'\n", dest->name, option->name, option->value);
					return 0;
				}
//				else
//					printf("Option %s not found for Printer %s\n", dest->name, option->name);

}

//compilieren mit: -lcups








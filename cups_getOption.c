#include <cups/cups.h>

int main(int argc, char* argv[])
{
	if( argc < 3 )
	{
		printf("Usage: %s <PrinterName> <OptionName>\n", argv[0]);
		return -1;
	}

        int num_dests;
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
					printf("Printer: %s \n\t Option: %s \n\t Value: %s\n", dest->name, option->name, option->value);
					return 0;
				}
//				else
//					printf("Option %s not found for Printer %s\n", dest->name, option->name);

}

//compilieren mit: -lcups








#include <cups/cups.h>

int main(int argc, char* argv[])
{
	int i;
	int num_dests;
	cups_dest_t *dests, *dest;
	int job_id;
	char *value;

	num_dests = cupsGetDests(&dests);

	for (i = num_dests, dest = dests; i > 0; i --, dest ++)
	{
		if(dest->instance == NULL)
                {
                        value = cupsGetOption("printer-info", dest->num_options, dest->options);
			//printf("%s/%s\n", dest->name, dest->instance);
			printf("%s : %s\n", dest->name, value ? value : "no description");
		}
		else
			puts(dest->name);
	}
}

//compilieren mit: -lcups








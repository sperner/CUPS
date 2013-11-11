#include <cups/cups.h>

int main(int argc, char* argv[])
{
	if( argc < 2 )
	{
		printf("Usage: %s <File2Print>\n", argv[0]);
		return -1;
	}

	int num_dests;
	cups_dest_t *dests, *default_dest;
	int job_id;
//	const char *ppd_filename;
//	ppd_file_t *ppd;

	num_dests = cupsGetDests(&dests);
	default_dest = cupsGetDest(NULL, NULL, num_dests, dests);
/*
	ppd_filename = cupsGetPPD(default_dest->name);
	ppd = ppdOpenFile(ppd_filename);
	ppdLocalize(ppd);
*/
	job_id = cupsPrintFile(default_dest->name, argv[1],"bild",default_dest->num_options,default_dest->options);
}

//compilieren mit: -lcups








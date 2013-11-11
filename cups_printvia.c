#include <stdio.h>
#include <stdlib.h>
#include <cups/cups.h>


int main(int argc, char* argv[])
{
  int num_dests,i;
  cups_dest_t *dests, *dest;// *default_dest;
  int job_id;

    if( argc < 3 )
    {
	printf("Usage: %s <PrinterName> <File2Print>\n", argv[0]);
	return -1;
    }
  
    num_dests = cupsGetDests(&dests);
/*
    for (i = num_dests, dest = dests; i > 0; i --, dest ++)
    {
	if (dest->instance)
	  printf("%s/%s\n", dest->name, dest->instance);
	else
	  puts(dest->name);
    }
*/
    dest = cupsGetDest(argv[1], NULL, num_dests, dests);
    if( dest != NULL )
    {
	printf("%s\n",dest->name);
	job_id=cupsPrintFile(dest->name,argv[2],"temporary",dest->num_options,dest->options);
    }
    else
    {
	printf("got default\n");
    }

  return 0;
}

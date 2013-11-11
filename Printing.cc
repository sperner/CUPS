/*
 *   surf - visualizing algebraic curves and algebraic surfaces
 *   Copyright (C) 1996-1997 Friedrich-Alexander-Universitaet
 *                           Erlangen-Nuernberg
 *                 1997-2000 Johannes Gutenberg-Universitaet Mainz
 *   Authors: Stephan Endrass, Hans Huelf, Ruediger Oertel,
 *            Kai Schneider, Ralf Schmitt, Johannes Beigel
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

// ----------------------------------------------------------------------------
//  printing.CC
//  enables CUPS-Printing
//  by Sven
//  date 28.11.2009
//  last modified 09.01.2009
// ----------------------------------------------------------------------------

#include "Printing.h"



Printing::Printing()
{
	num_dests = cupsGetDests(&dests);
}
 

void Printing::print(char* pname, char* inputFilePath)
{
    	char filename[25];

    	time_t now = time ( NULL );
    	struct tm *date = localtime ( &now );
 
	sprintf(filename, "surf_%d%d%d-%d%d%d", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900, date->tm_hour, date->tm_min, date->tm_sec ); 
	dest = cupsGetDest(pname, NULL, num_dests, dests);
	job_id = cupsPrintFile(dest->name, inputFilePath, filename, dest->num_options, dest->options);
}

void Printing::printWithOpt(char* pname, char* inputFilePath, cups_option_t* options, int num_options)
{
    	char filename[25];

    	time_t now = time ( NULL );
    	struct tm *date = localtime ( &now );
 
	sprintf(filename, "surf_%d%d%d-%d%d%d", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900, date->tm_hour, date->tm_min, date->tm_sec ); 
	dest = cupsGetDest(pname, NULL, num_dests, dests);
	job_id = cupsPrintFile(dest->name, inputFilePath, filename, num_options, options);
}

void Printing::setUsedPrinter(char* pname)
{
	usedPrinter = new char[strlen(pname)];
	sprintf(usedPrinter, "%s\0", pname);
}

char* Printing::getUsedPrinterName()
{
	if(num_dests > 0)
		return usedPrinter;
	else
		return "none";
}

int Printing::getNumPrinters()
{
	return num_dests;
}

char* Printing::getDefPrinterName()
{
	int i;
	if(num_dests > 0)
	{
		for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		{
			if( dest->is_default)
				return (char*)dests->name;
		}
	}
	else
		return "none";
}

char* Printing::getPrinterName(int destnum)
{
	if(num_dests >= destnum)
	{
		dest = dests;
		dest += destnum;
		return (char*)dest->name;
	}
	else
		return "none";
}

int Printing::isPrinterDefault(int destnum)
{
	if(num_dests >= destnum)
	{
		dest = dests;
		dest += destnum;
		return dest->is_default;
	}
	else
		return false;
}

int Printing::isPrinterDefault(char* pname)
{
	int i;
	if(num_dests > 0)
		for(i = num_dests, dest = dests; i > 0; i --, dest ++)
			if(strcmp(dest->name, pname) == 0)
				return dest->is_default;
	else
		return false;
}

cups_option_t* Printing::getOptions(char* pname)
{
	int i,j;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(strcmp(dest->name, pname) == 0)
			return dest->options;
	return NULL;
}

int Printing::getNumOptions(char* pname)
{
	int i,j;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(strcmp(dest->name, pname) == 0)
			return dest->num_options;
	return NULL;
}

char* Printing::getOptionByName(char* pname, char* oname)
{
	int i,j;
	cups_option_t* option;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(strcmp(dest->name, pname) == 0)
			for(j = dest->num_options, option=dest->options; j > 0; j--, option++)
				if(strcmp(option->name, oname) == 0)
					return option->value;
				else
					return "";
	return "";
}

cups_option_t* Printing::setOptionByName(cups_option_t* options, int num_opts, char* oname, char* value)
{
	int j,ret;
	cups_option_t* option;
	for(j = num_opts, option=options; j > 0; j--, option++)
		if(strcmp(option->name, oname) == 0)
			ret = cupsAddOption(oname, value, num_opts, &option);
	return options;
}

int Printing::addOption(cups_option_t* options, int num_opts, char* oname, char* ovalue)
{
	int j,ret;
	cups_option_t* option;
	for(j = num_opts, option=options; j > 0; j--, option++)
	{
		printf("%i: %s %s\n",j,option->name,option->value);
		if(strcmp(option->name, oname) == 0)
			return num_opts;
	}
	printf("adding Option: %s %s\n",oname,ovalue);
	return cupsAddOption(oname, ovalue, num_opts, &options);
}

bool Printing::isOptionAvailable(char* pname, char* oname)
{
	int i,j;
	cups_option_t* option;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(strcmp(dest->name, pname) == 0)
			for(j = dest->num_options, option=dest->options; j > 0; j--, option++)
				if(strcmp(option->name, oname) == 0)
					return true;
	return false;
}

bool Printing::isOptionAvailable(cups_option_t* options, int num_options, char* oname)
{
	int j;
	for(j = num_options, options; j > 0; j--, options++)
		if(strcmp(options->name, oname) == 0)
			return true;
	return false;
}

void Printing::showDests()
{
	int i;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(dest->instance)
			printf("%s/%s\n", dest->name, dest->instance);
		else
			puts(dest->name);
}

void Printing::showOptions(char* pname)
{
	int i,j;
	cups_option_t* option;
	for(i = num_dests, dest = dests; i > 0; i --, dest ++)
		if(strcmp(dest->name, pname) == 0)
			for(j = dest->num_options, option=dest->options; j > 0; j--, option++)
				printf("Name: %s - Value: %s\n",option->name, option->value);
}

void Printing::showOptions(cups_option_t* options, int num_options)
{
	int i,j;
	cups_option_t* option;
	for(j = num_options, option=options; j > 0; j--, option++)
		printf("Name: %s - Value: %s\n",option->name, option->value);
}


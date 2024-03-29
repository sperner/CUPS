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
//  printing.H
//  enables CUPS-Printing
//  by Sven
//  date 28.11.2009
//  last modified 09.01.2009
// ----------------------------------------------------------------------------

#ifndef PRINTING_H
#define PRINTING_H

#include <cups/cups.h>
#include <stdio.h>


class Printing
{
private:
	int num_dests;
	cups_dest_t *dests, *dest;
	int job_id;

public:
        Printing();

	int getNumPrinters();

	char* getDefPrinterName();
	char* getPrinterName(int destnum);

	int isPrinterDefault(int destnum);
	int isPrinterDefault(char* pname);

	void setUsedPrinter(char* pname);
	char* getUsedPrinterName();

	cups_option_t* getOptions(char* pname);
	int getNumOptions(char* pname);
	char* getOptionByName(char* pname, char* option);
	cups_option_t* setOptionByName(cups_option_t* options, int num_opts, char* oname, char* value);
	int addOption(cups_option_t* options, int num_opts, char* oname, char* ovalue);
	bool isOptionAvailable(char* pname, char* oname);
	bool isOptionAvailable(cups_option_t* options, int num_options, char* oname);

	void print(char* pname, char* inputFilePath);
	void printWithOpt(char* pname, char* inputFilePath, cups_option_t* options, int num_options);

        void showDests();
	void showOptions(char* pname);
	void showOptions(cups_option_t* options, int num_options);

protected:
	char* usedPrinter;
};

#endif // PRINTING_H
 

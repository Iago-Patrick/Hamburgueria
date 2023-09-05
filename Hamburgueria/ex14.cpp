/***************************************************************************
 *   exN.cpp                                  Version 20230620.225755      *
 *                                                                         *
 *   Programa Principal                                                    *
 *   Copyright (C) 2023         by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/*
 * Instrucoes para compilar:
 *   $ make ex14.out
 * Leia mais detalhes no arquivo INSTALL
 */

/* ---------------------------------------------------------------------- */
/* includes */

#include "ui_mainmenu.h"
#include "help.hpp" /* To be created for this template if needed */
#include "mainwin.hpp"

/* ---------------------------------------------------------------------- */
/* definitions */

/* limits */
#define SBUFF 256 /* string buffer */

/* ---------------------------------------------------------------------- */
/* This function does ...
 * It receives as input ...
 * It returns ...
 */
int main(int argc, char *argv[])
{
    /* local declarations */
    document doc; /* create an object of a class */

    /* Q_INIT_RESOURCE(x); */

    if(argc > 1)
    {
        doc.help();
        doc.copyr();
        return EXIT_SUCCESS;
    }

    QApplication app(argc, argv);

    MainWindow win;

    win.show();

    /* ...and we are done */
    return app.exec();
}

/* add more functions here */

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : CPP config - Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20220718.172615      */

#***************************************************************************
#*   Autoversion makefile                   v.20230620.220121 (qmake-qt5)  *
#*   Copyright (C) 2014-2023 by Ruben Carlo Benante <rcb@beco.cc>          *
#*                                                                         *
#*   This makefile sets BUILD and allows to set MAJOR.MINOR version,       *
#*   DEBUG and OBJ to compile a range of different targets                 *
#***************************************************************************
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU General Public License as published by  *
#*   the Free Software Foundation; version 2 of the License.               *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU General Public License for more details.                          *
#*                                                                         *
#*   You should have received a copy of the GNU General Public License     *
#*   along with this program; if not, write to the                         *
#*   Free Software Foundation, Inc.,                                       *
#*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#***************************************************************************
#*   To contact the author, please write to:                               *
#*   Ruben Carlo Benante                                                   *
#*   Email: rcb@beco.cc                                                    *
#*   Webpage: http://beco.cc/                                              *
#***************************************************************************
#
# Usage:
#    make clean : remove arquivos automaticos
#    make ex14.out :
#         - compila e cria ex14.out, e para isso
#         - antes cria Makefile, e para isso
#         - antes cria pf3-tico-teco.pro, sem dependencias, fazendo:
#             + varredura na pasta
#             + adicionando linha QT += requisitos...
#             + trocando target

# Regra para limpar a pasta de trabalho (working dir)
clean:
	rm Makefile exN.o ex14.out pf3-tico-teco.pro ui_exN.h

# Regra para criar ex14.out, dependendo de Makefile no modo debug
debug: Makefile
	qmake-qt5 pf3-tico-teco.pro CONFIG+=debug
	make -f Makefile
	mv ex14.out ex14-debug.out

# Regra para criar ex14.out, dependendo de Makefile no modo debug
release: Makefile
	qmake-qt5 pf3-tico-teco.pro CONFIG+=release
	make -f Makefile

# Regra para criar Makefile, dependendo de pf3-tico-teco.pro
Makefile: pf3-tico-teco.pro
	qmake-qt5 pf3-tico-teco.pro

# Regra para criar pf3-tico-teco.pro, nao depende de nada
pf3-tico-teco.pro:
	qmake-qt5 -project
	echo "QT += gui widgets sql" >> pf3-tico-teco.pro
	sed -i 's/TARGET = .*/TARGET = ex14.out/' pf3-tico-teco.pro

#* ------------------------------------------------------------------- *
#* makefile config for Vim modeline                                    *
#* vi: set ai noet ts=4 sw=4 tw=0 wm=0 fo=croqlt list :                *
#* Template by Dr. Beco <rcb at beco dot cc> Version 20220521.001405   *

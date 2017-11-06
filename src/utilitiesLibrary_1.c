/*
 * utilitiesLibrary.c
 *
 *  Created on: Mar 24, 2017
 *      Author: Everton Lincoln Uehara
 *
 *******************************************************************************
 *
 * 		"... the authors of this package cannot predict all possible uses/needs
 * of every user in the world - so sometimes you need to manage the path and
 * the content of your project(s). On the other side, you made your project
 * where on disk? if you made it outside of StellarisWare/boards/your_board
 * then you must expect other changes, like possible new include paths. Take
 * two projects from StelarisWare and check their settings - paths, defines,
 * options. Look to a project which uses lwip and you will understand."
 *
 * Petrei - TI Community member - Mar 7, 2013 1:05 PM
 *
 *******************************************************************************
 *
 * 		"You should never #include a *.c file.  A *.c file should be compiled b
 * itself, then linked into the project.  When you #include a *.c file, you are
 * basically inserting that file into another source file as far as the compiler
 * is concerned.  While that may work, it's not a particularly good way to
 * program, and is prone to causing very hard to sort out problems later in life
 * when you are likely to get namespace collisions.  For instance, if you have
 * two source files that refer to functions in xyz.c, and they both attempt to
 * #include xyz.c, the functions will be created twice, and will cause linker
 * errors.
 *
 * 		*.h files are header files, and provide the defines and interfaces so
 * that you can refer to functions and variables that are contained elsewhere.
 *
 * 		If you need to access the functions in uartstdio.c, there are two things
 * you need to do.  You need to have uartstdio.c compiled and linked as part of
 * your project, and you need to #include the header file uartstdio.h in every
 * source file that refers to a function or variable from uartstdio.c.  How you
 * get the file added to your project varies from IDE to IDE.
 *
 * 		What you don't realize about the driverlib source files is that they are
 * all compiled and then linked into the driverlib library, and that whole
 * library is then being linked into your project.  That's why you don't have to
 * add the specific source files to your project, you just need to have files
 * #include the header files for the functions they need access to.  The
 * advantage of a library is that functions that you don't call in the library
 * don't get added to your code, only the functions that you actually make
 * reference to get linked in.  Other source files in your project that are built
 * and linked in will generate code for every function in your application whether
 * or not you call the functions."
 *
 * slandrum - TI Community member - Mar 7, 2013 9:16 PM
 *
 ******************************************************************************
 *
 *   Link of the discussion:
 * https://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/t/249645#pi239031350=1
 *
 ******************************************************************************
 *
 * Ps.: Each one of library from "Utilities" need to be indexed one by
 * one.
 *
 */

#include <utils/uartstdio.c>


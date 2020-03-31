/*
 *
 *
 * Filename:		scan.l
 * Date:		02/28/2019
 * Author:		Stephen Perkins
 * Email:		stephen.perkins@utdallas.edu
 * Version:		1.0
 * Copyright:		2019, All Rights Reserved
 *
 * Description:
 *
 *	A quick Lex Example Program. 
 */

%option noyywrap
%option nounput
%option noinput

%{
  #include <stdlib.h>
  #include "myproject.h"
%}

%%


[ \t\r]+			{ /* eat up whitespace */ }
[A-Za-z][A-Za-z]+               { return NAMETOKEN; }
[A-Za-z0-9]+                    { return IDENTIFIERTOKEN; }
[A-Za-z]\.?                     { return NAME_INITIAL_TOKEN; }
[IVXLCDM]+                      { return ROMANTOKEN; }
"Sr."                           { return SRTOKEN; }
"Jr."                           { return JRTOKEN; }
"\n"                            { return EOLTOKEN; }
[0-9]+                          { return INTTOKEN; }
","                             { return COMMATOKEN; }
"-"                             { return DASHTOKEN; }
"#"				{ return HASHTOKEN; }

%%

/* 
 * This section is empty on purpose.
 *    DO NOT PUT YOUR main() routine here.
 *    
 * Put your main routine in a separate file.
 */

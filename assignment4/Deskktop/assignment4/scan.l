/*
 *
 *
 * Filename:		scan.l
 * Date:		04/05/2020
 * Author:		Harsha Srikara
 * Email:		hxc170009s@utdallas.edu
 * Version:		1.0
 * Copyright:		2020, All Rights Reserved
 *
 * Description: Contains regex rules for assignment 4. 
 */

%option noyywrap
%option nounput
%option noinput

%{
  #include <stdlib.h>
  #include "y.tab.h"
%}

%%




[ \t\r]+			{ /* eat up whitespace */ }
"Sr."                           { return SRTOKEN; }
"Jr."                           { return JRTOKEN; }
"\n"                            { return EOLTOKEN; }
[0-9]+                          { yylval.value=atoi(yytext); return INTTOKEN; }
","                             { return COMMATOKEN; }
"-"                             { return DASHTOKEN; }
"#"			        { return HASHTOKEN; }
[IVXLCDM]+                      { yylval.str=yytext; return ROMANTOKEN; }
[A-Za-z]\.?                     { yylval.str=yytext; return NAME_INITIAL_TOKEN; }
[A-Za-z][A-Za-z]+               { yylval.str=yytext; return NAMETOKEN; }
[A-Za-z0-9]+			{ yylval.str=yytext; return IDENTIFIERTOKEN; }


%%

/* 
 * This section is empty on purpose.
 *    DO NOT PUT YOUR main() routine here.
 *    
 * Put your main routine in a separate file.
 */

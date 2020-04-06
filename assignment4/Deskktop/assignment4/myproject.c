/*
 *
 *
 * Filename:		myproject.c
 * Date:		04/05/2020
 * Author:		Harsha Srikara
 * Email:		hxc170009@utdallas.edu
 * Version:		1.0
 * Copyright:		2020, All Rights Reserved
 *
 * Description:
 *   Run in scanner or parser mode depending on how the program still gets called
 */

#include <stdio.h>	   /* needed for printf() */
//#include "myproject.h"     /* needed for ENUM */
#include "y.tab.h"

/* 
 * Manually insert prototype and extern declarations for the
 * stuff in the flex output file.
 */
int yylex(void);
extern char *yytext;

/* Just call the lexical scanner until we reach EOF */

int main(int argc, char* argv[])
{
	if(strcmp(argv[0],"./scanner") == 0) {
//	enum {HASHTOKEN=1, DASHTOKEN, COMMATOKEN, INTTOKEN, JRTOKEN, SRTOKEN, ROMANTOKEN, NAME_INITIAL_TOKEN, IDENTIFIERTOKEN, NAMETOKEN, EOLTOKEN};
	int token;

	token = yylex();
	printf("Operating in scan mode\n");
	while (token != 0)
	{
	printf("yylex returned ");
		switch (token)
		{
		case HASHTOKEN:
			printf("HASHTOKEN token (%d)\n",token);
			break;
		case COMMATOKEN:
			printf("COMMATOKEN token (%d)\n",token);
			break;
		case DASHTOKEN:
			printf("DASHTOKEN token (%d)\n",token);
			break;
		case SRTOKEN:
			printf("SRTOKEN token (%d)\n",token);
			break;
		case JRTOKEN:
			printf("JRTOKEN token (%d)\n",token);
			break;
		case INTTOKEN:
			printf("INTTOKEN token (%s)\n",yytext);
			break;
		case EOLTOKEN:
			printf("EOLTOKEN token (%d)\n",token);
			break;
		case ROMANTOKEN:
			printf("ROMAN NUMERAL token (%s)\n",yytext);
			break;
		case NAME_INITIAL_TOKEN:
			printf("NAME INITIAL TOKEN token (%s)\n",yytext);
			break;
		case NAMETOKEN:
			printf("NAMETOKEN token (%s)\n",yytext);
			break;
		case IDENTIFIERTOKEN:
			printf("IDENTIFIER TOKEN token (%s)\n",yytext);
			break;
		default:
			printf("UNKNOWN\n");
			break;
		}

		token = yylex();
	}
	}
	else if(strcmp(argv[0],"./parser")==0) {
		printf("Operating in parse mode\n");
		//do stuff heree
		switch(yyparse()) {
			case 0:
				printf("parsing was successful");
				break;
			case 1:
				printf("parsing was not successful");
				break;
			default:
				printf("unknown result");

		}
	}
	else {

	}
	
	return 0;
}

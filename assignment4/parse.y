
%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char *);;

    extern int line;
%}

%union
{
    int value;
    char *str;
}

%type   <value> INTTOKEN
%type   <str>   NAMETOKEN
%type   <str>   NAME_INITIAL_TOKEN
%type   <str>   IDENTIFIERTOKEN
%type   <str>   ROMANTOKEN
%type   <str>   street_name

%token  NAMETOKEN
%token  NAME_INITIAL_TOKEN
%token  JRTOKEN
%token  SRTOKEN
%token  ROMANTOKEN
%token  IDENTIFIERTOKEN
%token  INTTOKEN
%token  HASHTOKEN
%token  COMMATOKEN
%token  EOLTOKEN
%token  DASHTOKEN

%start postal_addresses

%%

postal_addresses:       address_block   EOLTOKEN    {fprintf(stderr, "\n");} postal_addresses
                    |   address_block
                    ;
address_block:          name_part   street_address  location_part
                    ;
name_part:              personal_part   last_name   suffix_part EOLTOKEN
                    |   personal_part   last_name   EOLTOKEN
                    |   error EOLTOKEN  {fprintf(stdout, "Bad name-part...skipping to newline\n"); }
                    ;
personal_part:          NAMETOKEN   {fprintf(stderr,"<FirstName>%s</FirstName>\n",$1); }
                    |   NAME_INITIAL_TOKEN  {fprintf(stderr,"<FirstName>%s</FirstName>\n",$1); }
                    ;
last_name:              NAMETOKEN   {fprintf(stderr,"<LastName>%s</LastName>\n",$1); }
                    ;
suffix_part:            SRTOKEN     {fprintf(stderr,"<Suffix>Sr.</Suffix>\n"); }
                    |   JRTOKEN     {fprintf(stderr,"<Suffix>Jr.</Suffix>\n"); }
                    |   ROMANTOKEN  {fprintf(stderr,"<Suffix>%s</Suffix>\n",$1); }
                    ;
street_address:         street_number   street_name INTTOKEN    EOLTOKEN    {fprintf(stderr,"<AptNum>%d</AptNum>\n",$3); }
                    |   street_number   street_name HASHTOKEN   INTTOKEN    EOLTOKEN    {fprintf(stderr,"<AptNum>%d</AptNum>\n",$4); }
                    |   street_number   street_name EOLTOKEN
                    |   error   EOLTOKEN    {fprintf(stdout, "Bad name-part...skipping to newline\n"); }
                    ;
street_number:          INTTOKEN    {fprintf(stderr,"<HouseNumber>%d</HouseNumber>\n",$1); }
                    |   IDENTIFIERTOKEN {fprintf(stderr,"<HouseNumber>%d</HouseNumber>\n",$1); }
                    ;
street_name:            NAMETOKEN   {fprintf(stderr,"<StreetName>%s</StreetName>\n",$1); }
                    ;
location_part:          town_name   COMMATOKEN  state_code  zip_code    EOLTOKEN
                    |   error      {fprintf(stdout, "Bad name-part...skipping to newline\n"); }
                    ;
town_name:              NAMETOKEN   {fprintf(stderr,"<City>%s</City>\n",$1); }
                    ;
state_code:             NAMETOKEN   {fprintf(stderr,"<State>%s</State>\n",$1); } 
                    ;
zip_code:               INTTOKEN    DASHTOKEN   INTTOKEN    {fprintf(stderr,"<Zip5>%d</Zip5>\n<Zip4>%d</Zip4>\n",$1,$3); }
                    |   INTTOKEN    {fprintf(stderr,"<Zip5>%d</Zip5>\n",$1); }
                    ;

%%

void yyerror(char *s)
{
    //blank
}

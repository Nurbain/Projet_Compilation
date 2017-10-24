%option nounput
%option noyywrap

%{
/* Declaration C */

/* fichier dans lequel est defini les macros constantes */
#include "sprint1.tab.h"
#include <stdio.h>

%}

/* Declaration Lex */

/* ###### SPRINT 1 ###### */

MAIN "int main"
NOMBRE [0-9]*
COMMENT \/\*.*\*\/
ENDLIGNE [\n]
STRING   \"([^\"\\]|\\.)*\"
RETURN return

/* ##################### */




/* Regle syntaxique */
%%
{COMMENT}* ;
{ENDLIGNE}* {printf("fin de ligne\n");};
\t ;

{MAIN} {printf("main reconnu\n");return MAIN;}
{RETURN} {printf("return reconnu\n");return RETURN;}
{NOMBRE} {printf("entier lu\n");yylval.nombre=atoi(yytext); return NOMBRE;}
{STRING} {yylval.string=strdup(yytext); return STRING;}


printf {return PRINTF;}
printi {return PRINTI;}

. {printf("caractere : %s\n",yytext);return yytext[0];}

%%


/* Code C additionnel */
int main(int argc, char **argv )
{
	yyin = fopen(argv[1],"r");
	yyparse();
	fclose(yyin);
	return 0;
}

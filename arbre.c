#include "arbre.h"
#include <stdlib.h>
#include <stdio.h>


Arbre new_var(char* var){
	Arbre new = malloc(sizeof(std_arbre));	
		printf("var : %s",var);
  new->type = ast_var;
  new->val.str = var;
  // On return une feuille de type ast_var
  return new;
}

Arbre new_op(arbre_type type, char op){
	Arbre new = malloc(sizeof(std_arbre));		
  new->type = type;
  new->val.op = op;
  // On return une feuille de type ast_op_OP
  return new;
}

Arbre ast_new_affectation(Arbre id, Arbre expr){
  Arbre newaffec = malloc(sizeof(std_arbre));
  newaffec->type = ast_affectation;
  newaffec->fils = concat(id,expr);
  return newaffec;
}

Arbre ast_new_declaration(Arbre feuille){
  Arbre newdeclare = malloc(sizeof(std_arbre));
  newdeclare->type = ast_declaration;
  newdeclare->fils = feuille;
  return newdeclare;
}

Arbre ast_new_expression(Arbre arg1, char op, Arbre arg2){
  Arbre newexpr = malloc(sizeof(std_arbre));
  newexpr->type = ast_expression;
  newexpr->fils = concat(arg1,arg2);
  newexpr->val.op = op;
  return newexpr;
}

//creation d'un arbre vide
Arbre newArbre(){
  return NULL;
}

//creation d'une feuille const
Arbre new_const(int val){
  Arbre new = malloc(sizeof(std_arbre));
  new->type = ast_constant;
  new->val.constante = val;
  // On return une feuille de type ast_constant
  return new;
}

//creation d'une feuille string
Arbre new_string(char* val){
  Arbre new = malloc(sizeof(std_arbre));
  new->type = ast_str;
  new->val.str = val;
  // On return une feuille de type ast_str
  return new;
}

//ajout de a2 dans les frere de a1
Arbre concat(Arbre a1,Arbre a2){
  Arbre tmp=a1;
  while(a1->freres != NULL){
    a1=a1->freres;
  }
  a1->freres=a2;
  return tmp;
}

//Ajout d'un noeud printi ou printf suivant le type
Arbre ast_new_print(arbre_type type,Arbre feuille){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint->type = type;
  newprint->fils = feuille;
  return newprint;
}

//Ajout d'un noeud return
Arbre ast_new_return(Arbre feuille){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint->type = ast_return;
  newprint->fils = feuille;
  return newprint;
}

//Ajout un noeud main, noeud le plus haut en profondeurs
Arbre ast_new_main(Arbre statement){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint->type = ast_main;
  newprint->fils = statement;
  return newprint;
}

//Affiche dans le terminal l'AST avec ses profondeurs
void ast_print_aux(Arbre a,int profondeur){
  if(a==NULL)
    return;
  int i;
  for(i=0;i<profondeur;i++){
    printf("-");
  }
  switch(a->type){
    case ast_constant:
      printf("ast_constant\n");
      break;
    case ast_str:
      printf("ast_str\n");
      break;
    case ast_printf:
      printf("ast_printf\n");
      break;
    case ast_printi:
      printf("ast_printi\n");
      break;
    case ast_return:
      printf("ast_return\n");
      break;
    case ast_main:
      printf("ast_main\n");
      break;
    case ast_affectation:
      printf("ast_affectation\n");
      break;
	case ast_var:
		printf("ast_var %s\n",a->val.str);
		break;
	case ast_expression:
	printf("ast_expression : %c \n",a->val.op);
	break;
	case ast_declaration:
	printf("ast_declaration \n");
	break;
	break;
  }

  //Affiche de manière recursive et ajoute une profondeur si possède des fils
  ast_print_aux(a->fils,profondeur+1);
  ast_print_aux(a->freres,profondeur);

}

void ast_print(Arbre a){
  ast_print_aux(a,0);
}




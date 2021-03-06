#include "table_symbole.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// determine le hach du symbole avec son id
int sym_hach(char* name){
  unsigned int i;
  int hach=0;

  // Fonction de hachage
  int sizeName = strlen(name);
  for(i=0;i<sizeName;i++){
    hach+=name[i]<<i;
  }

  return hach%TAILLE_TABLE;
}

// Verifie qu'un symbole existe et le renvoie
Symbole sym_existe(Symbole s,char* name){
  if(s==NULL){
    return NULL;
  }
  if(strcmp(s->name,name)==0){
    return s;
  }
  // Parcours tout les symboles en recursifs
  return sym_existe(s->next,name);
}

// Ajoute un symbole au hach donné
Symbole sym_add_aux(Symbole s,char* name,int h){
  // id pour l'index des symboles
  static int id=0;
  Symbole e=sym_existe(s,name);

  // Si le symbole existe on ne l'ajoute pas
  if(e!=NULL){
    return s;
  }

  // Sinon on ajoute ce nouveau temporaire
  Symbole new=malloc(sizeof(std_symbole));
  new->name=strdup(name);
  new->index=id++;
  new->next = s; // table des symbole
  new->type=sym_var; //type temporaire
  return new;
}

// Ajoute un symbole dans la table
void sym_add(char* name,Symbole sym_Table[TAILLE_TABLE]){
  int h = sym_hach(name);
  Symbole e = sym_Table[h];
  sym_Table[h]=sym_add_aux(sym_Table[h],name,h);
}

// Cherche l'index d'un symbole dans la table avec son id
int sym_find_index(char* name,Symbole sym_Table[TAILLE_TABLE]){
  int h = sym_hach(name);
  Symbole e = sym_existe(sym_Table[h],name);
  if(e==NULL)
    return -1;
  return e->index;
}

// Cherche un symbole dans la table avec son id
Symbole sym_find(char* name,Symbole sym_Table[TAILLE_TABLE]){
  int h = sym_hach(name);
  Symbole e = sym_existe(sym_Table[h],name);
  return e;
}

void free_Dim(Dim d){
  if(d== NULL){
    return;
  }
  free_Dim(d->next);
  free(d);
}

void free_Arg(Arg a){
  if(a== NULL){
    return;
  }
  free_Arg(a->next);
  free(a->name);
  free(a);
}

// Free un symbole
void sym_delete(Symbole s){
  if(s==NULL){
    return;
  }
  if(s->type == sym_string){
	  free(s->val.str);
  }
  if(s->type == sym_tab){
    free_Dim(s->val.dimension);
  }
  if(s->type == sym_fonction){
    free_Arg(s->val.arg_list);
  }
  Symbole tmp = s->next;
  free(s->name);
  free(s);
  sym_delete(tmp);
}

// Free la table de symbole
void sym_delete_table(Symbole sym_Table[TAILLE_TABLE]){
  int i=0;
  for(;i<TAILLE_TABLE;i++){
    sym_delete(sym_Table[i]);
  }
}


// Ajoute un nouveau symbole temporaire dans la table
Symbole sym_new_tmp(Symbole sym_Table[TAILLE_TABLE]){
  // static pour le nombre de temporaire
  static int nb_tmp=0;

  char name[1024];
  snprintf(name,1024,"$tmp%d",nb_tmp);
  //printf("%s size : %d\n",name,strlen(name));

  //printf("%s size : %d\n\n",name_tmp,strlen(name_tmp));

  nb_tmp++;

  int h=sym_hach(name);

  Symbole new_tmp;

  // si le symbole existe on le free pour l'ajouter
  if(sym_existe(sym_Table[h],name)!=NULL){
    new_tmp=sym_new_tmp(sym_Table);
    return new_tmp;
  }

  // on ajoute le symbol
  sym_add(name,sym_Table);

  // on verifie que le symbole existe bien en le retournant
  new_tmp=sym_existe(sym_Table[h],name);

  return new_tmp;

}

// Ajoute un nouveau symbole temporaire dans la table
Symbole sym_new_lbl(Symbole sym_Table[TAILLE_TABLE]){
  // static pour le nombre de temporaire
  static int nb_lbl=0;

  char name[1024];
  snprintf(name,1024,"$lbl%d",nb_lbl);
  //printf("%s size : %d\n",name,strlen(name));

  //printf("%s size : %d\n\n",name_tmp,strlen(name_tmp));

  nb_lbl++;

  int h=sym_hach(name);

  Symbole new_lbl;

  // si le symbole existe on le free pour l'ajouter
  if(sym_existe(sym_Table[h],name)!=NULL){
    new_lbl=sym_new_lbl(sym_Table);
    return new_lbl;
  }

  // on ajoute le symbol
  sym_add(name,sym_Table);

  // on verifie que le symbole existe bien en le retournant
  new_lbl=sym_existe(sym_Table[h],name);

  new_lbl->type = sym_label;

  return new_lbl;

}

int sym_existe_table(Symbole table[],char* name){
	Symbole e = sym_existe(table[sym_hach(name)],name);
	return e != NULL;
}

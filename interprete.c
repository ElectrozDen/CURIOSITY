#include "listes.h"
#include "curiosity.h"
#include <stdio.h>
#include <stdlib.h>

List commands;
List pile;


void printGroup(Element *e){
	
	
	while(e != NULL){
		if(e->val == '{'){
			printf("{");
			printGroup(e->group);
			printf("}");
			e = e->next;
		}else{
			printf("%c", e->val);
			e = e->next;
		}
	}
	
}

void printList(List l){
	printf("Liste: ");
	printGroup(l.first);
	printf("\n");
}


void read_group(Element *e, FILE *f){
	char c;

	fscanf(f,"%c",&c);
	e->group = createElement(c);
	if(c=='{'){
		read_group(e->group,f);
	}
	e = e->group;
	fscanf(f,"%c", &c);
	while(c != '}'){
		e->next = createElement(c);
		if(c == '{'){
			read_group(e->next, f);	
		}
		e = e->next;
		fscanf(f, "%c", &c);
	}

}

void read_commands(char file_name[]){
	FILE *f = NULL;
	char c;
	f = fopen(file_name, "r");

	fscanf(f, "%c", &c);
	if(feof(f)){ printf("Aucune Commande\n"); exit(6);}
	Element *e = createElement(c);
	if(c == '{'){
		read_group(e,f);
	}
	commands.first = e;
	while(!feof(f)){
		fscanf(f, "%c", &c);
		if(c != '\n'){
			e->next = createElement(c);
			if(c == '{'){
				read_group(e->next, f);
			}
			e=e->next;
		}
	}

	fclose(f);

	printList(commands);

}

Element *setOperation(Element *e, int i, int j, char operation){
	int result;
	int tmp;
	if(operation == '*')
		result = i*j;
	else
		result = i+j;

	if(result < 10){
		e = addElement(&pile, e, result + '0');
		return e;
	}

	while(result >= 10){
		tmp = result/10;
		tmp = result - tmp*10;
		e = addElement(&pile, e, tmp + '0');
		result /= 10;
	}

	e = addElement(&pile, e, result + '0');

	return e;
}


Element *setCmd(Element *e, Element *e_group){
	
	while(e_group != NULL){
		e = addNext(e, e_group->val);
		e_group = e_group->next;
	
	}
	return e;
}





void interprete_group(Element *e_command, Element *e_pile){
	Element *e1; int val1;
	Element *e2; int val2;
	while( e_command != NULL){
		afficherCarte();
      	printf("Commande : %c\n", e_command->val);
      	switch(e_command->val){
      		case 'A' : case 'a' : avance(); break;
      		case 'G' : case 'g' : gauche(); break;
      		case 'D' : case 'd' : droite(); break;
      		case 'M' : case 'm' : e_pile->val = mesure(e_pile->val); break ;
      		case 'P' : case 'p' : poser_enlever(e_pile->val);
      							  e_pile = remove_last(&pile); break;
      		case '{' : e_pile = addElement(&pile,e_pile,e_command->val);
      							e_pile->group = e_command->group; break;

      		case '?': e1 = e_pile->group; e_pile = remove_last(&pile);
      				  e2 = e_pile->group; e_pile = remove_last(&pile);
      				  char val = e_pile->val;
      				  remove_last(&pile);
      				  if(val == '0')
      				  	interprete_group(e1, e_pile);
      				  else
      				  	interprete_group(e2, e_pile);
      				  e_pile = getLast(pile);
					  break;
			case '*': val1 = e_pile->val - '0'; e_pile = remove_last(&pile);
					  val2 = e_pile->val - '0'; e_pile = remove_last(&pile);
					  e_pile = setOperation(e_pile, val1, val2, '*');
					  break;
			case '+': val1 = e_pile->val - '0'; e_pile = remove_last(&pile);
					  val2 = e_pile->val - '0'; e_pile = remove_last(&pile);
					  e_pile = setOperation(e_pile, val1, val2, '+');
					  break;
			case  '!': e_command = setCmd(e_command, e_pile->group);
					   e_pile = remove_last(&pile);
					   break;
			case 'X' : e1 = e_pile; e_pile = remove_last(&pile);
      				   e2 = e_pile; e_pile = remove_last(&pile);
      				   e_pile = addElement(&pile, e_pile, e2->val);
      				   if(e2->val = '{') e_pile->group = e2->group;
      				   e_pile = addElement(&pile, e_pile, e1->val);
      				   if(e1->val = '{') e_pile->group = e1->group;
      				   break;
      		case 'C' : e1 = e_pile;
      				   e_pile=addElement(&pile, e_pile, e1->val);
      				   e_pile->group = e1->group;
      				   break;
        	default: if(e_command-> val >= '0' && e_command->val <'9'){
            	              e_pile = addElement(&pile,e_pile,e_command->val);
            	      }else { printf("erreur commande inconnue"); exit(7); }
     	}
     	e_command = e_command->next;
     	printList(pile);
	}
}


void interprete(){
  Element *e = commands.first;
  Element *e_pile = pile.first;
  interprete_group(e, e_pile);
}




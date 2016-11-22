#include "listes.h"
#include <stdlib.h>

List createListe(){
	List l;
	l.first = NULL;
	return l;
}

Element *createElement(char val){
	Element *e = malloc(sizeof(Element));
	e->next = NULL;
	e->group = NULL;
	e->val = val;
	return e;
}

void removeElement(Element *e){
	free(e);
}

Element *addElement(List *l,Element *e,char c){
	if(e == NULL){
		e = createElement(c);
		l->first = e;
		return e;
	}else{
		e->next = createElement(c);
		return e->next;
	}
}


Element *remove_last(List *l){
	if (l->first == NULL) return NULL;
	Element *e = l->first;

	if(e->next == NULL){
		l->first = NULL;
		//removeElement(e);
		return NULL;
	}

	while(e->next->next != NULL) e = e->next;

	e->next = NULL;
	removeElement(e->next);
	return e;
}

Element *getLast(List l){
	if(l.first == NULL)
		return NULL;
	else{
		Element *e = l.first;
		while(e->next != NULL)
			e = e->next;
		return e;
	}
}

Element *addNext(Element *e, char val){
	Element *etmp = createElement(val);

	if(e == NULL){
		e = etmp;
		return e;
	}

	etmp->next = e->next;
	e->next = etmp;
	return e;
}
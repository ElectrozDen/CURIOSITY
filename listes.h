typedef struct Element Element;

struct Element{
	char val;
	Element *group;
	Element *next;
} ;

typedef struct  List
{
  Element *first;	
} List;

List createListe();
Element *createElement(char val);
void removeElement(Element *e);
Element *addElement(List *l,Element *e,char c);
Element *remove_last(List *l);
Element *getLast(List l);
Element *addNext(Element *e, char val);
#define tailleCarte 100

extern char mars[tailleCarte][tailleCarte];
extern int cX,cY,dX,dY; //position et direction de curiosity


void lireCarte();
void afficherCarte();
void avance();
void droite();
void gauche();
char mesure(char c);
void poser_enlever(char c);

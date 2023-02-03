#include"struct.h"
#include<stdio.h>
#include<stdlib.h>


float max(float a,float b);


float min(float a,float b);


Arbre* creationArbre(int station,float temperature,float temperaturemax, float temperaturemin);

Arbre* insertABR(Arbre* a,int station,float t,float tmin, float tmax);
Arbre* insertAVL(Arbre* a,int station,float t,float tmin, float tmax,int* h);

void ParcoursInfixe(Arbre* a,int* i);

int lancementt1();

int lancementt1AVL();
Arbre* equilibrerAVL(Arbre* a);
Arbre* DoubleRotationDroit(Arbre* a);
Arbre* DoubleRotationGauche(Arbre* a);
Arbre* rotationDroit(Arbre* a);
Arbre* rotationGauche(Arbre* a);
int min2(int a, int b,int c);
int max2(int a, int b, int c);
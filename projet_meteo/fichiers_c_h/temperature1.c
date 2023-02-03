#include<stdio.h>
#include<stdlib.h>
#include"temperature1.h"


float max(float a,float b){ // retourne le max 
if(a>=b){
	return a;
}
else{
	return b;
}
}




float min(float a,float b){ //retourne le min 
if(a<=b){
	return a;
}
else{
	return b;
}
}



int max2(int a, int b, int c){ // retourne le max
	if(a>b && a>c){
		return a;
	}
	if(b>a && b>c){
		return b;
	}
	if(c>a && c>b){
		return c;
	}
	if(a==b && a==c){
		return a;
	}
}

int min2(int a, int b,int c){ //retourne le min
	if(a<b && a<c){
		return a;
	}
	if(b<a && b<c){
		return b;
	}
	if(c<a && c<b){
		return c;
	}
	if(a==b && a==c){
		return a;
	}
}


Arbre* rotationGauche(Arbre* a){  // cree une rotation vers la gauche de l'arbre
    Arbre* pivot;
    int eq_a;
    int eq_p;
    pivot =a->fd;
    a->fd=pivot->fg;
    pivot->fg=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-max2(eq_p, 0,0)-1;
    pivot->equilibre=min2(eq_a-2, eq_a+eq_p-2, eq_p-1);
    a=pivot;
    return a;
}


Arbre* rotationDroit(Arbre* a){  // cree une rotation vers la droite de l'arbre 
    Arbre* pivot;
    int eq_a;
    int eq_p;
    pivot=a->fg;
    a->fg=pivot->fd;
    pivot->fd=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-min2(eq_p, 0,0)+1;
    pivot->equilibre=max2(eq_a+2, eq_a+eq_p+2, eq_p+1);
    a=pivot;
    return a;
}

Arbre* DoubleRotationGauche(Arbre* a){ // cree une double rotation gauche de l'arbre
	a->fd=rotationDroit(a->fd);
	a=rotationGauche(a);
	return a;

}

Arbre* DoubleRotationDroit(Arbre* a){ // cree une double rotation droite de l'arbre 
	a->fg=rotationGauche(a->fg);
	a=rotationDroit(a);
	return a;

}


Arbre* equilibrerAVL(Arbre* a){  // permets d'equilibrer l'AVL
	if(a->equilibre >=2){
		if(a->fd->equilibre>=0){
			return rotationGauche(a);
		}
		return DoubleRotationGauche(a);
	}
	else if(a->equilibre <=-2){
		if(a->fg->equilibre<=0){
			return rotationDroit(a);
		}
		return DoubleRotationDroit(a);
	}
	return a;
}



Arbre* creationArbre(int station,float temperature,float temperaturemax, float temperaturemin){//permets d'initialiser l'arbre
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->station = station;
	nouveau->temperature=temperature;
	nouveau->temperaturemin=temperaturemin;
	nouveau->temperaturemax=temperaturemax;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	return nouveau;
}

Arbre* insertABR(Arbre* a,int station,float t,float tmin, float tmax){ // permets d'inserer dans l'ABR
	if(a==NULL){
		return creationArbre(station,t,tmin,tmax);
	}

		if(station==a->station){

			if(tmin==0 && tmax==0){
				a->temperaturemin=min(t,a->temperaturemin);
				a->temperaturemax=max(t,a->temperaturemax);
				a->temperature=(a->temperaturemin+a->temperaturemax)/2;
			}
			else{
				a->temperaturemin=min(tmin,a->temperaturemin);
				a->temperaturemax=max(tmax,a->temperaturemax);
				a->temperature=(a->temperaturemin+a->temperaturemax)/2;
			}
		}
		if(station<a->station){
			a->fg=insertABR(a->fg,station,t,tmin,tmax);
		}

		if(station>a->station){
			a->fd=insertABR(a->fd,station,t,tmin,tmax);
		}

		return a;
}


Arbre* insertAVL(Arbre* a,int station,float t,float tmin, float tmax,int* h){ //permets d'inserer dans l'AVL
	if(a==NULL){
		*h=1;
		return creationArbre(station,t,tmin,tmax);
	}

		if(station==a->station){

			if(tmin==0 && tmax==0){
				a->temperaturemin=min(t,a->temperaturemin);
				a->temperaturemax=max(t,a->temperaturemax);
				a->temperature=(a->temperaturemin+a->temperaturemax)/2;
			}
			else{
				a->temperaturemin=min(tmin,a->temperaturemin);
				a->temperaturemax=max(tmax,a->temperaturemax);
				a->temperature=(a->temperaturemin+a->temperaturemax)/2;
			}
			*h=0;
			return a;
		}
		if(station<a->station){
			a->fg=insertAVL(a->fg,station,t,tmin,tmax,h);
			*h= -(*h);
		}

		if(station>a->station){
			a->fd=insertAVL(a->fd,station,t,tmin,tmax,h);
		}
		if(*h != 0 ){
			a->equilibre+=*h;
			a=equilibrerAVL(a);
			if(a->equilibre==0){
				*h=0;
			}
			else{
				*h=1;
			}
		}
		return a;
}

void ParcoursInfixe(Arbre* a, int* i){ //permets d'enregistrer le resultat 
	if(a!=NULL){
		ParcoursInfixe(a->fg,i);
		FILE* fichier=fopen("bin/t1_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d;%f;%f;%f\n",*i,a->temperature,a->temperaturemin,a->temperaturemax);
		*i=*i+1;
		fclose(fichier);
		ParcoursInfixe(a->fd,i);
	}
}


int lancementt1(){			//permets de lancer le tri T1 par ABR
	remove("bin/t1_filtre.csv");
	Arbre* tree;
	int a;
	float t,tmin,tmax;
	FILE* file= fopen("bin/t1.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%f;%f;%f",&a,&t,&tmin,&tmax);
	tree=creationArbre(a,t,tmin,tmax);
	while(fscanf(file,"%d;%f;%f;%f",&a,&t,&tmin,&tmax)!=EOF){
		//printf("%d;%f;%f;%f\n",a,t,tmin,tmax);
		tree=insertABR(tree,a,t,tmin,tmax);
	}
	fclose(file);
	int i=1;
	ParcoursInfixe(tree, &i);
}



int lancementt1AVL(){                  //permets de lancer le tri T1 par AVL
	remove("bin/t1_filtre.csv");
	Arbre* tree;
	int a;
	int h=0;
	float t,tmin,tmax;
	FILE* file= fopen("bin/t1.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%f;%f;%f",&a,&t,&tmin,&tmax);
	tree=creationArbre(a,t,tmin,tmax);
	while(fscanf(file,"%d;%f;%f;%f",&a,&t,&tmin,&tmax)!=EOF){
		tree=insertAVL(tree,a,t,tmin,tmax,&h);
	}
	fclose(file);
	int i=1;
	ParcoursInfixe(tree, &i);
}




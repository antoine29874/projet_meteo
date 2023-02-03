#include<stdio.h>
#include<stdlib.h>
#include"temperature1.h"



Arbre* creationArbreP1(int station,float pression){ // permet d'initialiser l'arbre
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->station = station;
	nouveau->pression=pression;
	nouveau->pressionmax=0;
	nouveau->pressionmin=0;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	return nouveau;
}

Arbre* insertABRP1(Arbre* a,int station,float p){ // permet d'inserer das un ABR
	if(a==NULL){
		return creationArbreP1(station,p);
	}

		if(station==a->station){
				a->pressionmin=min(p,a->pressionmin);
				a->pressionmax=max(p,a->pressionmax);
				a->pression=(a->pressionmin+a->pressionmax)/2;
			}
			
		if(station<a->station){
			a->fg=insertABRP1(a->fg,station,p);
		}

		if(station>a->station){
			a->fd=insertABRP1(a->fd,station,p);
		}

		return a;
}


Arbre* insertAVLP1(Arbre* a,int station,float p,int* h){ //permets d'inserer dans un AVL
	if(a==NULL){
		*h=1;
		return creationArbreP1(station,p);
	}

		if(station==a->station){
				a->pressionmin=min(p,a->pressionmin);
				a->pressionmax=max(p,a->pressionmax);
				a->pression=(a->pressionmin+a->pressionmax)/2;
				*h=0;
			return a;
			}
			
		if(station<a->station){
			a->fg=insertAVLP1(a->fg,station,p,h);
			*h= -(*h);
		}

		if(station>a->station){
			a->fd=insertAVLP1(a->fd,station,p,h);
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



void ParcoursInfixeP1(Arbre* a,int* i){ // permets d'enregistrer le resultat dans un fichier
	if(a!=NULL){
		ParcoursInfixeP1(a->fg, i);
		FILE* fichier=fopen("bin/p1_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d;%f;%f;%f\n",*i,a->pression,a->pressionmin,a->pressionmax);
		*i=*i+1;
		fclose(fichier);
		ParcoursInfixeP1(a->fd,i);
		
	}
}


int lancementP1(){                  //permets de lancer le tri P1 par ABR
	remove("bin/p1_filtre.csv");
	Arbre* tree;
	int a;
	float p;
	FILE* file= fopen("bin/p1.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%f",&a,&p);
	tree=creationArbreP1(a,p);
	while(fscanf(file,"%d;%f",&a,&p)!=EOF){
		if(p!=0){
			tree=insertABRP1(tree,a,p);
		}
	}
	fclose(file);
	int i=1;
	ParcoursInfixeP1(tree,&i);
}



int lancementP1AVL(){                  //permets de lancer le tri P1 par AVL
	remove("bin/p1_filtre.csv");
	Arbre* tree;
	int a;
	float p;
	int h=0;
	FILE* file= fopen("bin/p1.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%f",&a,&p);
	tree=creationArbreP1(a,p);
	while(fscanf(file,"%d;%f",&a,&p)!=EOF){
		if(p!=0){
			tree=insertAVLP1(tree,a,p,&h);
		}
	}
	fclose(file);
	int i=1;
	ParcoursInfixeP1(tree,&i);
}

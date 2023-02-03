#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"temperature1.h"

Arbre* creationArbrew(int station,float d,float v, float lat,float longi){ //permets d'initialiser l'arbre
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->station=station;
	nouveau->direction=d;
	nouveau ->vitesse=v;
	nouveau->temperature=lat;
	nouveau->pression=longi;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	return nouveau;
}



Arbre* insertABRw(Arbre* a,int station,float direction,float vitesse,float lat,float longi){ //permets d'inserer dans l'abr
	if(a==NULL){
		return creationArbrew(station,direction,vitesse,lat,longi);
	}
	if(station<a->station){
		a->fg=insertABRw(a->fg,station,direction,vitesse,lat,longi);
	}
	else if(station>a->station){
		a->fd=insertABRw(a->fd,station,direction,vitesse,lat,longi);
	}
	else if (station==a->station){
		a->coef++;
		a->direction=((a->direction*(a->coef-1))+direction)/a->coef;
		a->vitesse=((a->vitesse*(a->coef-1))+vitesse)/a->coef;
	}
	return a;
}


Arbre* insertAVLw(Arbre* a,int station,float direction,float vitesse,int* h,float lat,float longi){ // permets d'inserer dans l'AVL
	if(a==NULL){
		*h=1;
		return creationArbrew(station,direction,vitesse,lat,longi);
	}
	if(station<a->station){
		a->fg=insertAVLw(a->fg,station,direction,vitesse,h,lat,longi);
		*h= -(*h);
	}
	else if(station>a->station){
		a->fd=insertAVLw(a->fd,station,direction,vitesse,h,lat,longi);
	}
	else if (station==a->station){
		a->coef++;
		a->direction=((a->direction*(a->coef-1))+direction)/a->coef;
		a->vitesse=((a->vitesse*(a->coef-1))+vitesse)/a->coef;
		*h=0;
		return a;
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


void ParcoursInfixew(Arbre* a){ // permets d'enregistrer le tri dans un fichier 
	if(a!=NULL){
		ParcoursInfixew(a->fg);
		float ventX,ventY;
		FILE* fichier=fopen("bin/w_filtre.csv","a");
		rewind(fichier);
		ventX=cosf(a->direction*3.1415/180)*a->vitesse;
		ventY=sinf(a->direction*3.1415/180)*a->vitesse;
		fprintf(fichier,"%d;%f;%f;%f;%f\n",a->station,ventX,ventY,a->temperature,a->pression);
		fclose(fichier);
		ParcoursInfixew(a->fd);
	}
}


int lancementw(){			//permets de lancer le tri w par ABR
	remove("bin/w_filtre.csv");
	Arbre* tree;
	int a;
	float d,v,lat,longi;
	FILE* file= fopen("bin/w.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%f;%f;%f,%f",&a,&d,&v,&lat,&longi);
	tree=creationArbrew(a,d,v,lat,longi);
	while(fscanf(file,"%d;%f;%f;%f,%f",&a,&d,&v,&lat,&longi)!=EOF){
		if(d!=0 && v!=0){
			tree=insertABRw(tree,a,d,v,lat,longi);
		}
	}
	fclose(file);
	ParcoursInfixew(tree);
}



int lancementwAVL(){			//permets de lancer le tri w par AVL
	remove("bin/w_filtre.csv");
	Arbre* tree;
	int a;
	float d,v,lat,longi;
	int h=0;
	FILE* file= fopen("bin/w.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%f;%f;%f,%f",&a,&d,&v,&lat,&longi);
	tree=creationArbrew(a,d,v,lat,longi);
	while(fscanf(file,"%d;%f;%f;%f,%f",&a,&d,&v,&lat,&longi)!=EOF){
		if(d!=0 && v!=0){
			tree=insertAVLw(tree,a,d,v,&h,lat,longi);
		}
	}
	fclose(file);
	ParcoursInfixew(tree);
}

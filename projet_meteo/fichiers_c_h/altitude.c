#include<stdio.h>
#include<stdlib.h>
#include"temperature1.h"





Arbre* creationArbreH(int alt,float lat, float longi){ // on initialise l'arbre
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->station=alt;
	nouveau->temperature=lat;
	nouveau->pression=longi;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	return nouveau;
}

Arbre* insertABRH(Arbre* a,int alt,float lat,float longi){ //on insert dans l'ABR
	if(a==NULL){
		return creationArbreH(alt,lat,longi);
	}
	if(a->station<=alt){
		if(lat != a->temperature && longi!=a->pression){
			a->fg=insertABRH(a->fg,alt,lat,longi);
		}
	}
	else if(a->station >alt){
		a->fd=insertABRH(a->fd,alt,lat,longi);
	}

	return a;
}



Arbre* insertAVLH(Arbre* a,int alt,float lat,float longi,int* h){ //on insert dans l'AVL
	if(a==NULL){
		*h=1;
		return creationArbreH(alt,lat,longi);
	}
	if(a->station<=alt){
		if(lat != a->temperature && longi!=a->pression){
			a->fg=insertAVLH(a->fg,alt,lat,longi,h);
		}
		if(a->station==alt){
			*h=0;
		}
		else{
			*h= -(*h);
		}
	}
	else if(a->station >alt){
		a->fd=insertAVLH(a->fd,alt,lat,longi,h);
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


void ParcoursInfixeH(Arbre* a){		// on enregistre le resultat dans un fichier
	if(a!=NULL){
		ParcoursInfixeH(a->fg);
		FILE* fichier=fopen("bin/h_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d;%f;%f\n",a->station,a->temperature,a->pression);
		fclose(fichier);
		ParcoursInfixeH(a->fd);
	}
}

int lancementh(){			//permets de lancer le tri h par ABR
	remove("bin/h_filtre.csv");
	Arbre* tree;
	int a;
	float b,c;
	FILE* file= fopen("bin/altitude.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%f,%f;%d",&b,&c,&a);
	tree=creationArbreH(a,b,c);
	while(fscanf(file,"%f,%f;%d",&b,&c,&a)!=EOF){
		//printf("%d;%f;%f;%f\n",a,t,tmin,tmax);
		tree=insertABRH(tree,a,b,c);
	}
	fclose(file);
	ParcoursInfixeH(tree);
}


int lancementhAVL(){			//permets de lancer le tri h par AVL
	remove("bin/h_filtre.csv");
	Arbre* tree;
	int a;
	float b,c;
	int h=0;
	FILE* file= fopen("bin/altitude.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%f,%f;%d",&b,&c,&a);
	tree=creationArbreH(a,b,c);
	while(fscanf(file,"%f,%f;%d",&b,&c,&a)!=EOF){
		tree=insertAVLH(tree,a,b,c,&h);
	}
	fclose(file);
	ParcoursInfixeH(tree);
}

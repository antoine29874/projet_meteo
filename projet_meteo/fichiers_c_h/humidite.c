#include<stdio.h>
#include<stdlib.h>
#include"temperature1.h"





Arbre* creationArbreM(int alt,float lat, float longi,int station){ //  permet d'initialiser l'ABR
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->station=station;
	nouveau->an=alt;
	nouveau->temperature=lat;
	nouveau->pression=longi;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	return nouveau;
}

Arbre* insertABRM(Arbre* a,int alt,float lat,float longi,int station){ // permets d'inserer dans l'arbre
	if(a==NULL){
		return creationArbreM(alt,lat,longi,station);
	}
		if(station==a->station){
				if(alt>a->an){
					a->an=alt;
				}

		}
		if(station<a->station){
			a->fg=insertABRM(a->fg,alt,lat,longi,station);
		}

		if(station>a->station){
			a->fd=insertABRM(a->fd,alt,lat,longi,station);
		}

	return a;
}




Arbre* insertAVLM(Arbre* a,int alt,float lat,float longi,int station,int* h){ //permet d'inserer dans l'AVL
	if(a==NULL){
		*h=1;
		return creationArbreM(alt,lat,longi,station);
	}
		if(station==a->station){
				if(alt>a->an){
					a->an=alt;
				}
				*h=0;
			return a;

		}
		if(station<a->station){
			a->fg=insertAVLM(a->fg,alt,lat,longi,station,h);
			*h= -(*h);
		}

		if(station>a->station){
			a->fd=insertAVLM(a->fd,alt,lat,longi,station,h);
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






void ParcoursInfixeM(Arbre* a){ // enregistre le resultat dans un fichier
	if(a!=NULL){
		ParcoursInfixeM(a->fg);
		FILE* fichier=fopen("bin/m_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d;%d;%f;%f\n",a->station,a->an,a->temperature,a->pression);
		fclose(fichier);
		ParcoursInfixeM(a->fd);
	}
}

int lancementM(){			//permets de lancer le tri M par ABR
	remove("bin/m_filtre.csv");
	Arbre* tree;
	int a,d;
	float b,c;
	FILE* file= fopen("bin/humidite.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%d;%f,%f",&d,&a,&b,&c);
	tree=creationArbreM(a,b,c,d);
	while(fscanf(file,"%d;%d;%f,%f",&d,&a,&b,&c)!=EOF){
		//printf("%d;%f;%f;%f\n",a,t,tmin,tmax);
		tree=insertABRM(tree,a,b,c,d);
	}
	fclose(file);
	ParcoursInfixeM(tree);
}


int lancementMAVL(){			//permets de lancer le tri M par AVL
	remove("bin/m_filtre.csv");
	Arbre* tree;
	int a,d;
	float b,c;
	int h=0;
	FILE* file= fopen("bin/humidite.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%d;%f,%f",&d,&a,&b,&c);
	tree=creationArbreM(a,b,c,d);
	while(fscanf(file,"%d;%d;%f,%f",&d,&a,&b,&c)!=EOF){
		tree=insertAVLM(tree,a,b,c,d,&h);
	}
	fclose(file);
	ParcoursInfixeM(tree);
}

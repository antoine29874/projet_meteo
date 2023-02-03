#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"temperature1.h"

Arbre* creationArbreP2(float p,int an,int mois,int jour,int heure){ //permets d'initialiser l'arbre
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->pression=p;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	nouveau->an = an;
	nouveau->mois = mois;
	nouveau->jour = jour;
	nouveau->heure=heure;
	nouveau->coef=1;
	return nouveau;
}


Arbre* insertABRP2(Arbre* a,float t,int an,int mois,int jour,int heure){ //permets d'inserer dans l'ABR
	if(a==NULL){
		return creationArbreP2(t,an,mois,jour,heure);
	}

		if(a->an==an){
			if(a->mois==mois){
				if (a->jour==jour){
					if(a->heure==heure){
						a->coef++;
							a->temperature=((a->temperature*(a->coef-1))+t)/a->coef;
					}
					else if(a->heure>heure){
						a->fg=insertABRP2(a->fg,t,an,mois,jour,heure);
					}
					else{
						a->fd=insertABRP2(a->fd,t,an,mois,jour,heure);
					}
				}
				else if(a->jour>jour){
					a->fg=insertABRP2(a->fg,t,an,mois,jour,heure);
				}
				else{
				a->fd=insertABRP2(a->fd,t,an,mois,jour,heure);
				}
			}
			else if(a->mois>mois){
				a->fg=insertABRP2(a->fg,t,an,mois,jour,heure);
			}
			else{
				a->fd=insertABRP2(a->fd,t,an,mois,jour,heure);
			}
		}
		else if(a->an>an){
			a->fg=insertABRP2(a->fg,t,an,mois,jour,heure);
		}
		else{
			a->fd=insertABRP2(a->fd,t,an,mois,jour,heure);
		}
		return a;
}
	



Arbre* insertAVLP2(Arbre* a,float t,int an,int mois,int jour,int heure,int* h){ //permets d'inserer dans l'avl
	if(a==NULL){
		*h=1;
		return creationArbreP2(t,an,mois,jour,heure);
	}

		if(a->an==an){
			if(a->mois==mois){
				if (a->jour==jour){
					if(a->heure==heure){
						a->coef++;
						*h=0;
							a->temperature=((a->temperature*(a->coef-1))+t)/a->coef;
							return a;
					}
					else if(a->heure>heure){
						a->fg=insertAVLP2(a->fg,t,an,mois,jour,heure,h);
						*h= -(*h);
					}
					else{
						a->fd=insertAVLP2(a->fd,t,an,mois,jour,heure,h);
					}
				}
				else if(a->jour>jour){
					a->fg=insertAVLP2(a->fg,t,an,mois,jour,heure,h);
					*h= -(*h);
				}
				else{
				a->fd=insertAVLP2(a->fd,t,an,mois,jour,heure,h);
				}
			}
			else if(a->mois>mois){
				a->fg=insertAVLP2(a->fg,t,an,mois,jour,heure,h);
				*h= -(*h);
			}
			else{
				a->fd=insertAVLP2(a->fd,t,an,mois,jour,heure,h);
			}
		}
		else if(a->an>an){
			a->fg=insertAVLP2(a->fg,t,an,mois,jour,heure,h);
			*h= -(*h);
		}
		else{
			a->fd=insertAVLP2(a->fd,t,an,mois,jour,heure,h);
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
	




void ParcoursInfixeP2(Arbre* a){ //permets d'afficher le resultat dans un nouveau fichier 
	if(a!=NULL){
		ParcoursInfixeP2(a->fg);
		FILE* fichier=fopen("bin/p2_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d-%d-%dT%d:00:00UTC;%f\n",a->an,a->mois,a->jour,a->heure,a->temperature);
		fclose(fichier);
		ParcoursInfixeP2(a->fd);
	}
}



int pression2AVL(){			//permets de lancer le tri P2 par AVL
	remove("bin/p2_filtre.csv");
	Arbre* tree;
	float t;
	int h=0;
	int an,mois,jour,heure,dec;
	FILE* file= fopen("bin/p2.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t);
	tree=creationArbreP2(t,an,mois,jour,heure);
	while(fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t)!=EOF){
		tree=insertAVLP2(tree,t,an,mois,jour,heure,&h);

	}
	fclose(file);
	ParcoursInfixeP2(tree);
	}

	int pression2(){			//permets de lancer le tri P2 par ABR
	remove("bin/p2_filtre.csv");
	Arbre* tree;
	float t;
	int an,mois,jour,heure,dec;
	FILE* file= fopen("bin/p2.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t);
	tree=creationArbreP2(t,an,mois,jour,heure);
	while(fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t)!=EOF){
		
		tree=insertABRP2(tree,t,an,mois,jour,heure);

	}
	fclose(file);
	ParcoursInfixeP2(tree);
	}

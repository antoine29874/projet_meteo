#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"temperature1.h"

Arbre* creationArbreT2(float t,int an,int mois,int jour,int heure){ //permets de cree un arbre
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->temperature=t;
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


Arbre* insertABRT2(Arbre* a,float t,int an,int mois,int jour,int heure){ //permets d'inserer dans un ABR
	if(a==NULL){
		return creationArbreT2(t,an,mois,jour,heure);
	}

		if(a->an==an){
			if(a->mois==mois){
				if (a->jour==jour){
					if(a->heure==heure){
						a->coef++;
							a->temperature=((a->temperature*(a->coef-1))+t)/a->coef;
					}
					else if(a->heure>heure){
						a->fg=insertABRT2(a->fg,t,an,mois,jour,heure);
					}
					else{
						a->fd=insertABRT2(a->fd,t,an,mois,jour,heure);
					}
				}
				else if(a->jour>jour){
					a->fg=insertABRT2(a->fg,t,an,mois,jour,heure);
				}
				else{
				a->fd=insertABRT2(a->fd,t,an,mois,jour,heure);
				}
			}
			else if(a->mois>mois){
				a->fg=insertABRT2(a->fg,t,an,mois,jour,heure);
			}
			else{
				a->fd=insertABRT2(a->fd,t,an,mois,jour,heure);
			}
		}
		else if(a->an>an){
			a->fg=insertABRT2(a->fg,t,an,mois,jour,heure);
		}
		else{
			a->fd=insertABRT2(a->fd,t,an,mois,jour,heure);
		}
		return a;
}
			

Arbre* insertAVLT2(Arbre* a,float t,int an,int mois,int jour,int heure,int* h){ //permets d'inserer dans un AVL
	if(a==NULL){
		*h=1;
		return creationArbreT2(t,an,mois,jour,heure);
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
						a->fg=insertAVLT2(a->fg,t,an,mois,jour,heure,h);
						*h= -(*h);
					}
					else{
						a->fd=insertAVLT2(a->fd,t,an,mois,jour,heure,h);
					}
				}
				else if(a->jour>jour){
					a->fg=insertAVLT2(a->fg,t,an,mois,jour,heure,h);
					*h= -(*h);
				}
				else{
				a->fd=insertAVLT2(a->fd,t,an,mois,jour,heure,h);
				}
			}
			else if(a->mois>mois){
				a->fg=insertAVLT2(a->fg,t,an,mois,jour,heure,h);
				*h= -(*h);
			}
			else{
				a->fd=insertAVLT2(a->fd,t,an,mois,jour,heure,h);
			}
		}
		else if(a->an>an){
			a->fg=insertAVLT2(a->fg,t,an,mois,jour,heure,h);
			*h= -(*h);
		}
		else{
			a->fd=insertAVLT2(a->fd,t,an,mois,jour,heure,h);
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



void ParcoursInfixeT2(Arbre* a){ //permet d'enregistrer le resultat 
	if(a!=NULL){
		ParcoursInfixeT2(a->fg);
		FILE* fichier=fopen("bin/t2_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d-%d-%dT%d:00:00UTC;%f\n",a->an,a->mois,a->jour,a->heure,a->temperature);
		fclose(fichier);
		ParcoursInfixeT2(a->fd);
	}
}


int temperature2(){			//permets de lancer le tri T2 par ABR
	remove("bin/t2_filtre.csv");
	Arbre* tree;
	float t;
	int an,mois,jour,heure,dec;
	FILE* file= fopen("bin/t2.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t);
	heure+=dec;
	tree=creationArbreT2(t,an,mois,jour,heure);
	while(fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t)!=EOF){
		tree=insertABRT2(tree,t,an,mois,jour,heure);
	}
	fclose(file);
	ParcoursInfixeT2(tree);
	free(tree);
}

int temperature2AVL(){			//permets de lancer le tri T2 par AVL
	remove("bin/t2_filtre.csv");
	Arbre* tree;
	float t;
	int h=0;
	int an,mois,jour,heure,dec;
	FILE* file= fopen("bin/t2.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t);
	heure+=dec;
	tree=creationArbreT2(t,an,mois,jour,heure);
	while(fscanf(file,"%d-%d-%dT%d:00:00+%d:00;%f",&an,&mois,&jour,&heure,&dec,&t)!=EOF){
		tree=insertAVLT2(tree,t,an,mois,jour,heure,&h);

	}
	fclose(file);
	ParcoursInfixeT2(tree);
	free(tree);
	}

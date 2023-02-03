#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Arbre{
	int station;
	float temperature;
	float temperaturemin;
	float temperaturemax;
	float pression;
	float pressionmin;
	float pressionmax;
	int equilibre;
	int jour;
	int mois;
	int an;
	int heure;
	int coef;
	float direction;
	float vitesse;
	struct Arbre*  fg;
	struct Arbre* fd;
}Arbre;


Arbre* creationArbreT3(int station,float t,int an,int mois,int jour,int heure){
	Arbre* nouveau = malloc(sizeof(Arbre));
	if(nouveau==NULL){
		exit(1);
	}
	nouveau->station=station;
	nouveau->temperature=t;
	nouveau->equilibre=0;
	nouveau->fg=NULL;
	nouveau->fd=NULL;
	nouveau->an = an;
	nouveau->mois = mois;
	nouveau->jour = jour;
	nouveau->heure=heure;
	return nouveau;
}


/*Arbre* insertABRT3(Arbre* a,int station,float t,int an,int mois,int jour,int heure){
	if(a==NULL){
		return creationArbreT3(station,t,an,mois,jour,heure);
	}

		if(a->an==an){
			if(a->mois==mois){
				if (a->jour==jour){
					if(a->heure==heure){
							if(station<a->station){
								a->fg=insertABRT3(a->fg,station,t,an,mois,jour,heure);
							}

							if(station>a->station){
								a->fd=insertABRT3(a->fd,station,t,an,mois,jour,heure);
							}
							return a;
					}
					else if(a->heure>heure){
						a->fg=insertABRT3(a->fg,station,t,an,mois,jour,heure);
					}
					else{
						a->fd=insertABRT3(a->fd,station,t,an,mois,jour,heure);
					}
				}
				else if(a->jour>jour){
					a->fg=insertABRT3(a->fg,station,t,an,mois,jour,heure);
				}
				else{
				a->fd=insertABRT3(a->fd,station,t,an,mois,jour,heure);
				}
			}
			else if(a->mois>mois){
				a->fg=insertABRT3(a->fg,station,t,an,mois,jour,heure);
			}
			else{
				a->fd=insertABRT3(a->fd,station,t,an,mois,jour,heure);
			}
		}
		else if(a->an>an){
			a->fg=insertABRT3(a->fg,station,t,an,mois,jour,heure);
		}
		else{
			a->fd=insertABRT3(a->fd,station,t,an,mois,jour,heure);
		}
		return a;
}
*/
void ParcoursInfixeT3(Arbre* a, int* i){
	if(a!=NULL){
		ParcoursInfixeT3(a->fg,i);
		FILE* fichier=fopen("bin/t3_filtre.csv","a");
		rewind(fichier);
		fprintf(fichier, "%d;%d-%d-%dT%d:00:00UTC;%f\n",a->station,a->an,a->mois,a->jour,a->heure,a->temperature);
		*i=*i+1;
		fclose(fichier);
		ParcoursInfixeT3(a->fd,i);
	}
}



int temperature3(){			//permets de lancer le tri T2 par ABR
	remove("bin/t3_filtre.csv");
	Arbre* tree;
	float t;
	int i=0;
	int an,mois,jour,heure,dec;
	int station;
	FILE* file= fopen("bin/temperature3.csv","r");
	if(file==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(file);
	fscanf(file,"%d;%d-%d-%dT%d:00:00+%d:00;%f",&station,&an,&mois,&jour,&heure,&dec,&t);
	heure+=dec;
	tree=creationArbreT3(station,t,an,mois,jour,heure);
	fclose(file);
	ParcoursInfixeT3(tree,&i);
}

int main(){
	//temperature3();
}
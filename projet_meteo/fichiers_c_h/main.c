#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAILLE 500
#include"temperature1.h"
#include"temperature2.h"
#include"pression1.h"
#include"pression2.h"
#include"vent.h"
#include"altitude.h"
#include"humidite.h"

int main(int argc, const char *argv[]){
int a;

char line[TAILLE];
char cpyline[TAILLE];
char* X;
char* Y;
char* Z;
float X2,Y2;



if (*argv[1]=='r'){	// permets de trier par zones geographiques
	float lat_min,lat_max,long_min,long_max;
	FILE* fichier;
	FILE* nouveau_fichier;
	lat_min=atoi(argv[2]);
	lat_max=atoi(argv[3]);
	long_min=atoi(argv[4]);
	long_max=atoi(argv[5]);
	fichier=fopen("bin/fichiermeteo.csv","r");
	nouveau_fichier=fopen("bin/fichiertransit.csv","w");
	if(fichier==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(fichier);
	memset(cpyline,0,TAILLE);
	memcpy(cpyline,line,TAILLE);
	while(fgets(line,TAILLE,fichier)!=NULL){
		if(line !=NULL){
			memset(cpyline,0,TAILLE);
			memcpy(cpyline,line,TAILLE);
			X=strtok(line,";");
			for(int i=1;i<10;i++){
				X=strtok(NULL,";,");
			}
			Y=strtok(NULL,";,");
		}
		X2=strtof(X,NULL);
		Y2=strtof(Y,NULL);
		if(lat_min<X2 && lat_max>X2 && long_min<Y2 && long_max>Y2){

			fputs(cpyline,nouveau_fichier);
		}
	}
	fclose(fichier);
	fclose(nouveau_fichier);

}


if(*argv[1]=='d'){						// tri par date
	int an_d,mois_d,jour_d,an_f,mois_f,jour_f;
	int an,mois,jour;
	FILE* fichier;
	FILE* nouveau_fichier;
	char* t;
	//char* t=*argv[2];
	an_d=strtof(strtok(t,"-"),NULL);
	mois_d=strtof(strtok(NULL,"--"),NULL);
	jour_d=strtof(strtok(NULL,"--_"),NULL);
	an_f=strtof(strtok(NULL,"--_-"),NULL);
	mois_f=strtof(strtok(NULL,"--_--"),NULL);
	jour_f=strtof(strtok(NULL,"--_---"),NULL);
	fichier=fopen("bin/fichiermeteo.csv","r");
	nouveau_fichier=fopen("bin/fichiertransit.csv","w");
	if(fichier==NULL){
		printf("erreur d'ouverture fichier");
		exit(1);
	}
	rewind(fichier);
	memset(cpyline,0,TAILLE);
	memcpy(cpyline,line,TAILLE);
	while(fgets(line,TAILLE,fichier)!=NULL){
		if(line !=NULL){
			memset(cpyline,0,TAILLE);
			memcpy(cpyline,line,TAILLE);
			X=strtok(line,";");
			an=strtof(strtok(NULL,";-"),NULL);
			mois=strtof(strtok(NULL,"-"),NULL);
			jour=strtof(strtok(NULL,"T"),NULL);
		}
		if(an>an_d && an<an_f){
			if(mois>mois_d && mois<mois_f){
				if(jour>jour_d && jour<jour_f){
					fputs(cpyline,nouveau_fichier);
				}
			}

		}
	}
	fclose(fichier);
	fclose(nouveau_fichier);



}




if(*argv[1]=='a'){	// lance tous les tris par AVL

	if(*argv[2]=='t'){	//lance T1
		lancementt1AVL();
		printf("tri avl t1 \n");
	}

	else if (*argv[2]=='y'){ //lance T2
		temperature2AVL();
		printf("tri avl t2");

	}

	else if (*argv[2]=='u'){ //lance T3
		printf("tri avl t3");

	}

	else if (*argv[2]=='x'){ //lance P1
		lancementP1AVL();
		printf("tri avl p1");

	}

	else if (*argv[2]=='z'){	//lance P2
		pression2AVL();
		printf("tri avl p2");

	}

	else if (*argv[2]=='n'){	//lance P3
		printf("tri avl p3");

	}
	else if (*argv[2]=='w'){	//lance W
		lancementwAVL();
		printf("tri avl w ");

	}
	else if (*argv[2]=='h'){	//lance H
		lancementhAVL();
		printf("tri avl h");

	}

	else if (*argv[2]=='m'){	//lance M
		lancementMAVL();
		printf("tri avl m");

	}




}


else if (*argv[1]=='b'){	//Lance le tri par ABR


	if(*argv[2]=='t'){ //lance T1
		lancementt1();
		printf("tri abr t1\n");
		

	}

	else if (*argv[2]=='y'){ //lance T2
		temperature2();
		printf("tri abr t2\n");

	}

	else if (*argv[2]=='u'){ //lance T3
		printf("tri abr t3");

	}

	else if (*argv[2]=='x'){ //lance p1
		lancementP1();
		printf("tri abr p1\n");

	}

	else if (*argv[2]=='z'){ //lance p2
		pression2();
		printf("tri abr p2");

	}

	else if (*argv[2]=='n'){ //lance p3
		printf("tri abr p3");

	}
	else if (*argv[2]=='w'){ //lance W
		lancementw();
		printf("tri abr w");

	}

	else if (*argv[2]=='h'){ //lance H
		lancementh();
		printf("tri abr h");

	}

	else if (*argv[2]=='m'){ //lance M
		lancementM();
		printf("tri abr m");

	}
}



else if(*argv[1]=='c'){ // lance tous les tri par Tab

	if(*argv[2]=='t'){ //lance T1
		lancementt1();
		printf("tri tab t1");
	}

	else if (*argv[2]=='y'){ //lance T2
		temperature2();
		printf("tri tab t2");

	}

	else if (*argv[2]=='u'){ //lance T3
		printf("tri tab t3");

	}

	else if (*argv[2]=='x'){ //lance P1
		lancementP1();
		printf("tri tab p1");

	}

	else if (*argv[2]=='z'){ //lance P2
		pression2();
		printf("tri tab p2");

	}
	else if (*argv[2]=='n'){ //lance P3
		printf("tri tab p3");

	}

	else if (*argv[2]=='w'){ //lance W
		lancementw();
		printf("tri tab w");
	}

	else if (*argv[2]=='h'){ //lance H
		lancementh();
		printf("tri tab h");
	}

	else if (*argv[2]=='m'){ //lance M
		lancementM();
		printf("tri tab m");
	}

	
}

 
}

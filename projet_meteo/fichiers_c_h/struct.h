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
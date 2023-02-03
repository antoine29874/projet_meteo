all: exec

main.o : fichiers_c_h/main.c fichiers_c_h/temperature1.h fichiers_c_h/struct.h fichiers_c_h/pression1.h fichiers_c_h/temperature2.h
		gcc -o main.o -c fichiers_c_h/main.c

temperature1.o : fichiers_c_h/temperature1.c fichiers_c_h/temperature1.h fichiers_c_h/struct.h
		gcc -o temperature1.o -c fichiers_c_h/temperature1.c

temperature2.o : fichiers_c_h/temperature2.c fichiers_c_h/temperature2.h fichiers_c_h/temperature1.h
		gcc -o temperature2.o -c fichiers_c_h/temperature2.c


pression1.o : fichiers_c_h/pression1.c fichiers_c_h/temperature1.h fichiers_c_h/pression1.h
		gcc -o pression1.o -c fichiers_c_h/pression1.c


pression2.o : fichiers_c_h/pression2.c fichiers_c_h/pression2.h fichiers_c_h/temperature1.h
		gcc -o pression2.o -c fichiers_c_h/pression2.c

vent.o : fichiers_c_h/vent.c fichiers_c_h/vent.h fichiers_c_h/temperature1.h
		gcc -o vent.o -c fichiers_c_h/vent.c -lm

altitude.o : fichiers_c_h/altitude.c fichiers_c_h/altitude.h fichiers_c_h/temperature1.h
		gcc -o altitude.o -c fichiers_c_h/altitude.c

humidite.o : fichiers_c_h/humidite.c fichiers_c_h/humidite.h fichiers_c_h/temperature1.h
		gcc -o humidite.o -c fichiers_c_h/humidite.c


exec : main.o temperature1.o pression1.o temperature2.o pression2.o vent.o altitude.o humidite.o
		gcc main.o temperature1.o pression1.o temperature2.o pression2.o  vent.o altitude.o humidite.o -o exec -lm
		

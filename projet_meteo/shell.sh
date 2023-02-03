#!/bin/bash

if [ $# -le 0 ]
then

	echo "pas le bon nombre d'arguments : merci de rentrer le fichier data ainsi qu'au moins une option de tri"
fi

region=0
d=0
t1=0
t2=0
t3=0
p1=0
p2=0
p3=0
w=0
h=0				#on initialise les variables
m=0
abr=0
avl=0
tab=0
help=0
set_coordonees_lat_min=0
set_coordonees_lat_max=0
set_coordonees_long_min=0
set_coordonees_long_max=0
fichier_out1=0

while getopts "d:o:f:t:p:whmFGSAOQ-:" opt 
do
if [[ $opt = "-" ]]
then
	opt=$OPTARG
fi
case $opt in 

	abr)
		abr=1
	;;
					#on recupere tous les arguments utilisés
	avl)
		avl=1
	;;

	tab)
		tab=1
	;;

	help)
		echo "BIENVENUE"
		echo "Plusieurs options existent afin de réaliser un tri :"
		echo " 3 options de tri : "
		echo "--avl(mode par defaut)pour trier par AVL"
		echo "--abr pour trier par ABR"
		echo "--tab pour trier par tableau"
		echo "6 restrictions de tri par regions (seulement 1 autorisé):"
		echo "-F pour la france metropolitaine"
		echo "-G pour la guyane"
		echo "-S pour saint pierre et miquelon"
		echo "-A pour les antilles "
		echo "-O pour l'ocean indien "
		echo "-Q pour l'antartique"
		echo "pour indiquer le fichier à trier (obligatoire) : -f <NOM_FICHIER>"
		echo "pour indiquer le fichier de reception du tri : -o <NOM_FICHIER>"
		echo "Pour choisir le type de données à traiter :"
		echo "-t1 pour trier par température mini maxi moyennes par stations croissantes "
		echo "-t2 pour trier les températures moyennes de toutes les stations par ordre chronologique"
		echo "-t3 non fonctionnel"
		echo "-p1 pour trier par pressions mini maxi moyennes par stations croissantes "
		echo "-p2 pour trier les pressions moyennes de toutes les stations par ordre chronologique"
		echo "-p3 non fonctionnel"
		echo "-w pour avoir l'orientation et la vitesse des vents "
		echo " -h pour avoir l'altitude de chaques stations "
		echo "-m pour avoir l'humidité maximale par stations "
		echo "tri par date (non fonctionnel):"
		echo "-o <AAAA-MM-JJ_AAAA_MM_JJ> avec 1ere date le debut et ensuite de fin "

		exit
	;;
	o) fichier_out=$OPTARG
		fichier_out1=1
		
	;;
	d)
	d=1
	dates=$OPTARG
		
	;;

	F) region_france=1
		region=$(($region+1))
		set_coordonees_lat_min="40.401627"
		set_coordonees_lat_max="51.771788"
		set_coordonees_long_min="-11.021999"
		set_coordonees_long_max="13.629127"




	;;

	G) region_guyane=1
		region=$(($region+1))
		set_coordonees_lat_max="7.822141"
		set_coordonees_lat_min="0.782326"
		set_coordonees_long_min="-54.837650"
		set_coordonees_long_max="-50.873780"
	;;

	S) region_saint_pierre=1
		region=$(($region+1))
		set_coordonees_lat_max="53.720340"
		set_coordonees_lat_min="42.969559"
		set_coordonees_long_max="-47.989764"
		set_coordonees_long_min="-66.185317"

	;;

	A) region_antille=1
		region=$(($region+1))
		set_coordonees_lat_max="19.220346"
		set_coordonees_lat_min="10.285147"
		set_coordonees_long_min="-67.055384"
		set_coordonees_long_max="-56.450836"


	;;

	O) region_indien=1
		region=$(($region+1))
		set_coordonees_lat_min="-34.320624"
		set_coordonees_lat_max="21.742165"
		set_coordonees_long_max="125.453777"
		set_coordonees_long_min="31.004554"

	;;

	Q) region_antartique=1
		region=$(($region+1))
		set_coordonees_lat_max="-43.406507"
		set_coordonees_lat_min="-79.617053"
		set_coordonees_long_min="-177.139103"
		set_coordonees_long_max="177.172076"

	;;


	f) arg=$OPTARG
		fichier=$OPTARG	
	;;




	t) arg=$OPTARG
		if [ $arg -eq 1 ]
		then
			t1=1
			echo "température mini maxi moyennes par stations croissantes"
		fi

		if [ $arg -eq 2 ]
		then
			t2=1
			echo "température moyennes par heure/date, orgre chronologique "
		fi

		if [ $arg -eq 3 ]
		then
			t3=1
			echo "température par date/heure par stations ordre chrono et ordre croissant "
		fi

		if [ $arg -ne 1 ] && [ $arg -ne 2 ] && [ $arg -ne 3 ]
		then 
			echo "merci d'entrer un mode existant "
		fi
	;;
	p) arg=$OPTARG
		if [ $arg -eq 1 ]
		then
			p1=1
			echo "pression mini maxi moyennes par stations croissantes"
		fi

		if [ $arg -eq 2 ]
		then
			p2=1
			echo "pression moyennes par heure/date, orgre chronologique"
		fi

		if [ $arg -eq 3 ]
		then
			p3=1
			echo "pression par date/heure par stations ordre chrono et ordre croissant "
		fi
		if [ $arg -ne 1 ] && [ $arg -ne 2 ] && [ $arg -ne 3 ]
		then 
			echo "merci d'entrer un mode existant "
		fi
	;;
	w) 
		w=1
	;;

	h) 
		h=1
		

		
	;;

	m)
		m=1
	;;

esac
done
cp $fichier bin/fichiermeteo.csv 
sed 1d bin/fichiermeteo.csv -i			#on fait une copie du fichier a trier
sed 's/;;/;0;/g' bin/fichiermeteo.csv >bin/fichiertransit.csv
sed 's/;;/;0;/g' bin/fichiertransit.csv>bin/fichiermeteo.csv




if [ $region -gt 1 ]
	then 
		echo "Please enter just one argument for localisation"
		exit 1

fi


if [ $region -eq 1 ]		#on trie les zones geographiques
then
	make
	./exec r $set_coordonees_lat_min $set_coordonees_lat_max $set_coordonees_long_min $set_coordonees_long_max
	mv bin/fichiertransit.csv bin/fichiermeteo.csv
fi

if [ $d -eq 1 ]
then

	make 
	./exec d $dates
	mv bin/fichiertransit.csv bin/fichiermeteo.csv
fi


if [ $abr -eq 0 ] && [ $tab -eq 0 ]
then
	avl=1		#on initialise le tri par avl par defaut
fi

if [ $t1 -eq 1 ]	#on appelle le prgramme c avec tri T1 en fonction du mode de tri
then
	cut -d';' -f1,11,12,13 bin/fichiermeteo.csv>bin/t1.csv
	if [ $abr -eq 1 ]
	then
		make
		./exec b t  

	fi
	if [ $avl -eq 1 ]
	then
		make
		./exec a t

	fi
	if [ $tab -eq 1 ]
	then
		make
		./exec c t

	fi
	gnuplot --persist gnu/gnuplot_scriptT1.gnu 	#on lance le graphique
	if [ $fichier_out1 -eq 1 ]
	then
		cp bin/t1_filtre.csv $fichier_out
		open $fichier_out
	fi

fi

if [ $t2 -eq 1 ]	#on appelle le prgramme c avec tri T2 en fonction du mode de tri
then
	cut -d';' -f2,11 bin/fichiermeteo.csv>bin/t2.csv
	if [ $abr -eq 1 ]
	then
		make
		./exec b y

	fi
	if [ $avl -eq 1 ]
	then
		make
		./exec a y

	fi
	if [ $tab -eq 1 ]
	then
		make
		./exec c y

	fi
	gnuplot --persist gnu/gnuplot_scriptT2.gnu		#on lance le graphique
	if [ $fichier_out1 -eq 1 ]
	then
		cp bin/t2_filtre.csv $fichier_out
		open $fichier_out
	fi
fi

	if [ $t3 -eq 1 ]	#on appelle le prgramme c avec tri T3 en fonction du mode de tri
	then
		cut -d';' -f1,2,11 bin/fichiermeteo.csv>bin/temperature3.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b u 

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a u

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c u

		fi


	fi


	if [ $p1 -eq 1 ]	#on appelle le prgramme c avec tri p1 en fonction du mode de tri
	then
		cut -d';' -f1,7 bin/fichiermeteo.csv>bin/p1.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b x 

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a x

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c x

		fi
		gnuplot --persist gnu/gnuplot_scriptP1.gnu	#on lance le graphique
		if [ $fichier_out1 -eq 1 ]
		then
			cp bin/p1_filtre.csv $fichier_out
			open $fichier_out
		fi

	fi

	if [ $p2 -eq 1 ]	#on appelle le prgramme c avec tri p2 en fonction du mode de tri
	then
		cut -d';' -f2,7 bin/fichiermeteo.csv>bin/p2.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b z

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a z

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c z

		fi
		gnuplot --persist gnu/gnuplot_scriptP2.gnu	#on lance le graphique
		if [ $fichier_out1 -eq 1 ]
		then
			cp bin/p2_filtre.csv $fichier_out
			open $fichier_out
		fi

	fi

	if [ $p3 -eq 1 ]	#on appelle le prgramme c avec tri P3 en fonction du mode de tri
	then
		cut -d';' -f1,2,7 bin/fichiermeteo.csv>bin/pression3.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b n

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a n

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c n

		fi


	fi

	if [ $w -eq 1 ]	#on appelle le prgramme c avec tri W en fonction du mode de tri
	then
		cut -d';' -f1,4,5,10 bin/fichiermeteo.csv>bin/w.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b w  

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a w

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c w

		fi

		gnuplot --persist gnu/gnuplot_scriptW.gnu	#on lance le graphe
		if [ $fichier_out1 -eq 1 ]
		then
			cp bin/w_filtre.csv $fichier_out
			open $fichier_out
		fi
	fi

	if [ $h -eq 1 ] #on appelle le prgramme c avec tri H en fonction du mode de tri
	then
		cut -d';' -f10,14 bin/fichiermeteo.csv>bin/altitude.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b h  

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a h

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c h

		fi
			gnuplot --persist gnu/gnuplot_scriptH.gnu	#on lance le graphe
		if [ $fichier_out1 -eq 1 ]
		then
			cp bin/h_filtre.csv $fichier_out
			open $fichier_out
		fi

	fi

	if [ $m -eq 1 ]	#on appelle le prgramme c avec tri M en fonction du mode de tri
	then
		cut -d';' -f1,10,6 bin/fichiermeteo.csv>bin/humidite.csv
		if [ $abr -eq 1 ]
		then
			make
			./exec b m 

		fi
		if [ $avl -eq 1 ]
		then
			make
			./exec a m

		fi
		if [ $tab -eq 1 ]
		then
			make
			./exec c m

		fi
			gnuplot --persist gnu/gnuplot_scriptM.gnu #on lance le graphe
		if [ $fichier_out1 -eq 1 ]
		then
			cp bin/h_filtre.csv $fichier_out
			open $fichier_out
		fi


fi




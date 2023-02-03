set datafile separator ";"
set title "carte des vents"
set xlabel "longitude"
set ylabel "latitude"
set xtic auto
set ytic auto
Shadecolor="#80E0A080"
set xrange [-180.00 : 180.00 ]
set yrange [-90.00 : 90.00 ]
plot "bin/w_filtre.csv"  using 5:4:3:2 with vectors linecolor 2 title "vecteur de vitesse/direction des vents"


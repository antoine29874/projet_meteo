set datafile separator ";"
#set terminal png
set grid xtics mxtics ytics nomztics nortics nox2tics 
#set autoscale noextend
set multiplot
set autoscale noextend
set xtic auto
set ytic auto
set title "Temperatures par stations"
set xlabel "Id station"
set ylabel "temperatures"
Shadecolor="#80E0A080"
plot 'bin/t1_filtre.csv' using 1:2  with linespoints  linecolor 2 title "temp moyenne"
plot 'bin/t1_filtre.csv' using 1:3:4  with filledcurves fc rgb Shadecolor title "temp min et max"

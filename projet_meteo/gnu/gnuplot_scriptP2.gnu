set datafile separator ";"
#set terminal png
set grid xtics mxtics ytics nomztics nortics nox2tics 
#set autoscale noextend
set multiplot
set autoscale noextend
set xtic auto
set ytic auto
set title "pression par date"
set xlabel "date"
set ylabel "pression"
Shadecolor="#80E0A080"
plot 'bin/p2_filtre.csv' using 1:2  with linespoints  linecolor 2 title "pression"

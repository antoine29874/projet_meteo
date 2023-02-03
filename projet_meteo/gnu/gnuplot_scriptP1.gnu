set datafile separator ";"
#set terminal png
#set output "test.png"
set grid xtics mxtics ytics nomztics nortics nox2tics 
#set autoscale noextend
set multiplot
set autoscale noextend
set xtic auto
set ytic auto
set title "pressions par stations"
set xlabel "Id station"
set ylabel "pressions"
Shadecolor="#80E0A080"
plot 'bin/p1_filtre.csv' using 1:2  with linespoints  linecolor 2 title "pression moyenne"
plot 'bin/p1_filtre.csv' using 1:3:4  with filledcurves fc rgb Shadecolor title "pression min et max"

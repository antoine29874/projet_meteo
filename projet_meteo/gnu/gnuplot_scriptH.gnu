set datafile separator ";"
#set terminal png
set grid xtics mxtics ytics nomztics nortics nox2tics 
#set multiplot
set pm3d implicit at b
set autoscale noextend
set xtic auto
set ytic auto
set view map
set pm3d interpolate 0,0
set hidden3d
set dgrid3d 200,200
set title "carte des altitudes"
set xlabel "longitude"
set ylabel "latitude"
stats "bin/h_filtre.csv" using 3:2
splot [STATS_min_x:STATS_max_x] [STATS_min_y:STATS_max_y] "bin/h_filtre.csv"  using 3:2:1 with lines


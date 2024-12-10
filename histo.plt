set terminal dumb size 100,30
set output "output.txt" 
set datafile separator ","
set xrange [-1:4]
set yrange [0:*]
set xtics ("[1-10)" 0, "[10-100)" 1, "[100-1000)" 2, "[1000-inf]" 3)
unset key
unset border
unset mxtics
unset mytics
unset ytics

plot '/home/ma843/histo.csv' using ($0):($1):($1) with labels notitle
unset output
# Manually setting labels
do for [i=0:3] {
    stats '/home/ma843/histo.csv' using ($0==i? $1 : 1/0) nooutput
    value = int(STATS_sum)
    do for [j=0:value-1] {
       set label at i, j "*" offset char 0, 0 font ",8"
    }
}
replot

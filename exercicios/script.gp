set terminal pngcairo
set xlabel 'x'
set ylabel 'y'
set autoscale

set view map
set output 'graf1.png'
splot 'dados_12.1ex1.txt' matrix with image

set output 'graf2.png'
splot 'dados_12.1ex2.txt' matrix with image

unset output
unset terminal
reset




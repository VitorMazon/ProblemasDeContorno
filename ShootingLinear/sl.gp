set terminal pdf enhanced font 'Times New Roman'
set output "ShootingLinear.pdf"
set key left
set xrange [0:(pi)/2]
f(x)=(-0.1)*(sin(x)+3*cos(x))
plot 'sol100.dat' w lp pt 7 ps 0.3 t "Solução Numérica N=100", 'sol10.dat' w lp pt 7 ps 0.3 t "Solução Numérica N=10", f(x) t "Solução Analítica"
set output

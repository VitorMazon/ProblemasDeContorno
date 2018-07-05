set terminal pdf enhanced font 'Times New Roman'
set output "ShootingLinear.pdf"
set key left
set xrange [0:(pi)/2]
f(x)=(-0.1)*(sin(x)+3*cos(x))
plot 'res.dat' w lp pt 7 ps 0.3 t "Solução Numérica", f(x) t "Solução Analítica"
set output

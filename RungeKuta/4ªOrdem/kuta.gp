set terminal pdf enhanced font 'Times New Roman'
set output "RungeKuta.pdf"
set key left
f(x)=x+1/(1-x)
plot 'sol.dat' pt 7 ps 0.5 t "Solução Numérica", f(x) t "Solução Analítica"
set output

set term pngcairo size 800,600

#set term x11
set title "On the razor's edge of cancerous and healthy tissues"

set xrange[0.000001:0.1]
set yrange[0.000001:1]

set xlabel"Mutation rate (mu)"
set ylabel"P(mu,m)"


do for[i=5:5]{

N = 1e5
NpN0=1e5
n=10.
#g = N**(1/n) #gamma 
g = 10.0
s1 = 1/(g-1)
d0 = (1/g)**(n) #delta_0
N0=1
dnm1 = 1*(1/g) #delta_{n-1}
set logscale
unset key
  


# mutation range:
rm = 2

# number of top layers, where the mutations have no effect:
nt = 1

# number of extra terms in Poisson sums:
mp = 5

plus(x) = (x>0?x:0)

# rscd'/rscdd = 1 + q(g)*(m*s*(g-1)-1)

# if p=1 is given:
#p(g) = 1.

# if q=1 is given:
p(g) = 1

q(g) = 2/(g*p(g))
ddpd(m,g) = 1 / ( 1 + q(g)*(m*s*(g-1)-1) )

mc(g) = ceil( 1/(s*(g-1)) )

Dtr(g,k) = k*(g-1)
Dli(g,k) = Dtr(g,k) + NpN0/g**(n-1)

lambda(g,k) = 1.0/g**(n - k - 1) + (1.0/g ** (n-k-1) - 1.0/g**(n-k) )*m*s


Dli_mut (g, k, m,s) = (Dtr (g, k) + NpN0/g**(n-1) + (g-1)*(k-1)*m*s)/(1-(g-1)*m*s) + exp(-lambda(g,k)*NpN0)/(1.0/g**(n-1)*lambda(g,k)**2)

Pmul(g,k) = ( k==n ? 2/g : 1 )
Dadd(g,k) = ( k==n ? 0 : (1-p(g))/2 )
#Dadd(g,k) = 0

P(mu,m,k) = mu**m/gamma(m+1) * ( k-1 >= 0 ? ((Dli(g,k)+Dadd(g,k)-1.5)**m-(Dtr(g,k)+Dadd(g,k)-1.5)**m)*g**k*Pmul(g,k) : Dli(g,0)**m)


set output 'P_mu_m_mu_N_1e4_fit_nc_pkqk_1.'.i.'.png'

plot P(x,1,n) with lines lw 3 lc rgb'green' , P(x,2,n) with lines lw 3 lc rgb'green', P(x,3,n) with lines lw 3 lc rgb'green', P(x,4,n) with lines lw 3 lc rgb'green', P(x,5,n) with lines lw 3 lc rgb'green', P(x,6,n) with lines lw 3 lc rgb'green', P(x,7,n) with lines lw 3 lc rgb'green','mutmeres.txt' every 15 u 1:2 w p pt 7 lc rgb'black', 'mutmeres.txt' u 1:2 every 15 ::1  w p pt 7 lc rgb'black', 'mutmeres.txt' u 1:2 every 15 ::2 w p pt 7 lc rgb'black', 'mutmeres.txt' u 1:2 every 15 ::3 w p pt 7 lc rgb'black', 'mutmeres.txt' u 1:2 every 15 ::4 w p pt 7 lc rgb'black', 'mutmeres.txt' u 1:2 every 15 ::5 w p pt 7 lc rgb'black','mutmeres.txt' u 1:2 every 15 ::6 w p pt 7 lc rgb'black'
unset output
}


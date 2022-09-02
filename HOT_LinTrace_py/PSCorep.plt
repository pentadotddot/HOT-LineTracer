
# NpN0 = 3e8 ; N0 = 1 ; n = 10 ; s = 0.023*3 ; mu = 1e-5
# NpN0 = 1e5 ; N0 = 1 ; n = 5 ; s = 0.023*3 ; mu = .7e-3
NpN0 = 10**5 ; N0 = 1 ; n = 3 ; s = 0.1 ; mu = 1e-5

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

# Time factor for truncated lineage ends:
# n  : delta_{n-1}
# n-1: delta_{n-1}*p/2 = delta_{n-1}/(gamma*q) = delta_{n-2}/q

# Corrected truncation:
# branch length: Lb = (1-p+p/2)/(p/2) = (1-p/2)/(p/2) = 2/p-1
# number of acd: Lb-1 = 2*(1/p-1) ; number of scdd: 1
# number of leafs of a binary tree of the same size: Nl = (Lb-1)/2 + 1 = 1/p
# This is equivalent to turning every other acd ((Lb-1)/2) to scdd, i.e.,
# the time factor for level k becomes: delta_k/2
# Or, alternatively in P_mu_m.pdf: ...*(1+(Lb-1)/2) = ...*(Lb+1)/2 = ...*1/p
# and D -> D+Dadd
# n  : delta_{n-1} = delta_{n-1}*g/2 * (2/g)
# n-1: delta_{n-1}/2 = delta_{n-2}*g/2

Pmul(g,k) = ( k==n ? 2/g : 1 )
Dadd(g,k) = ( k==n ? 0 : (1-p(g))/2 )
#Dadd(g,k) = 0

P(m,g,k) = mu**m/gamma(m+1) * ( k-1 >= 0 ? ((Dli(g,k)+Dadd(g,k)-1.5)**m-(Dtr(g,k)+Dadd(g,k)-1.5)**m)*g**k*Pmul(g,k) : Dli(g,0)**m)
Pold(m,g,k) = mu**m/gamma(m+1) * ( k-1 >= 0 ? 2*((Dli(g,k)-1.5)**m-(Dtr(g,k)-1.5)**m)*g**(k-1)/(k<n?q(g):1) : Dli(g,0)**m)
Poldadd(m,g,k) = mu**m/gamma(m+1) * ( k-1 >= 0 ? 2*((Dli(g,k)+Dadd(g,k)-1.5)**m-(Dtr(g,k)+Dadd(g,k)-1.5)**m)*g**(k-1)/(k<n?q(g):1) : Dli(g,0)**m)
#p [2:12][1e-6:1] P(mc(x),x,n), P(mc(x),x,n-nt), Pold(mc(x),x,n-nt), Poldadd(mc(x),x,n-nt)

#DkP(m,g,k) = P(m,g,k) - P(m,g,k-1)
DkP(m,g,k) = P(m,g,k) - ( k-1 >= 0 ? P(m,g,k-1) : 0 )
##DmDkP(m,g,k) = DkP(m,g,k) - DkP(m+1,g,k)
#DmDkP(m,g,k) = DkP(m,g,k) - ( m+1 <= mc(g)+rm-1 ? DkP(m+1,g,k) : 0 )

Su(m,g,k) = 1
S(m,g,k)  = 1 - ddpd(m,g)**(2**(n-nt+1-k)-1)
Sl(m,g,k) = 1 - ddpd(m,g)

PSu(g) = sum[m=mc(g):mc(g)+rm-1] sum[k=0:n-nt] DkP(m,g,k)*Su(m,g,k)
PS(g)  = sum[m=mc(g):mc(g)+rm-1] sum[k=0:n-nt] DkP(m,g,k)*S(m,g,k)
PSl(g) = sum[m=mc(g):mc(g)+rm-1] sum[k=0:n-nt] DkP(m,g,k)*Sl(m,g,k)

set log y
set format y "10^{%T}"
set sam 1000
set arrow 1 from NpN0**(1./n), graph 0 to NpN0**(1./n), graph 1 nohead lw 5 lc rgb "green"

#rep 10**(-mc(x)) ls 4

## rep DkP(mc(x)-2,x,0)*N0
## rep 1-exp(-PS(x)*N0 * 2**( Dli(x,0) * (s*(mc(x))) / (1+s*(mc(x))) ) )

### expansion of the stem cell level:
A = log(2)*mu/s ; phi = 0.55
PS0(g) = plus(Dli(g,0)*mu - A*log((mc(g)+phi)/phi)*log((mc(g)+phi)*phi/A**2)/2) 

## rep 1-exp(-PS(x)*N0-PS0(x)*N0)

### re-normalization:
Norm(g,k) = ( k-1 >= 0 ? 1 + 2*(exp((Dli(g,k)-1.5)*mu)-exp((Dtr(g,k)-1.5)*mu))*g**(k-1)/(k<n?q(g):1) : exp(Dli(g,0)*mu) )
PN(m,g,k) = P(m,g,k)/Norm(g,k)

DkPN(m,g,k) = PN(m,g,k) - ( k-1 >= 0 ? PN(m,g,k-1) : 0 )
#DmDkPN(m,g,k) = DkPN(m,g,k) - ( m+1 <= mc(g)+rm-1 ? DkPN(m+1,g,k) : 0 )

PNSu(g) = sum[m=mc(g):mc(g)+rm-1] sum[k=0:n-nt] DkPN(m,g,k)*Su(m,g,k)
PNS(g)  = sum[m=mc(g):mc(g)+rm-1] sum[k=0:n-nt] DkPN(m,g,k)*S(m,g,k)
PNSl(g) = sum[m=mc(g):mc(g)+rm-1] sum[k=0:n-nt] DkPN(m,g,k)*Sl(m,g,k)

#rep 1-exp(-PNSu(x)*N0) ls 3, 1-exp(-PNS(x)*N0) ls 3, 1-exp(-PNSl(x)*N0) ls 3

## rep sum[i=int(mc(x)-0*mc(2)):mc(x)+mp] exp(-Dli(x,0)*mu)*(Dli(x,0)*mu)**i/i!

## rep 1/Norm(x,n-nt)

### separation of the stem cell level for g=2:
## rep exp(-Dli(2,0)*mu)*(Dli(2,0)*mu)**(mc(2))/gamma(mc(2)+1)
#Ng2 = NpN0/2./Dli(2,0)
Ng2 = 2**(n-nt-1)
#Dg2 = log(Ng2)/log(2)
Dg2 = n-nt-1
Pg2(m) = mu**m/gamma(m) * 2*(Dg2+1-1.5)**(m-1) * Ng2
Dlig2(m) = Dli(2,0)-1/Pg2(m)
mg2 = 1

## rep exp(-Dlig2(mg2)*mu)*(Dlig2(mg2)*mu)**(mc(2)-mg2)/gamma(mc(2)-mg2+1)
P0brSg2   = sum[m=mc(2)-mg2:mc(2)-mg2+mp] exp(-Dlig2(mg2)*mu)*(Dlig2(mg2)*mu)**m/gamma(m+1)
#rep 1-(1-P0brSg2)**N0 ls 7

P0brSg(g) = sum[m=mc(g)-mg2:mc(g)-mg2+mp] exp(-Dli(g,0)  *mu)*(Dli(g,0)  *mu)**m/gamma(m+1)
#rep 1-(1-P0brSg(x))**N0 ls 7

### separation of the stem cell level:
Pbr(m,g,k) = mu**m/gamma(m) * ( k-1 >= 0 ? ((Dtr(g,k)+Dadd(g,k)+1-1.5)**(m-1))*g**k*Pmul(g,k) : 0)
Pbrold(m,g,k) = mu**m/gamma(m) * ( k-1 >= 0 ? 2*((Dtr(g,k)+1-1.5)**(m-1))*g**(k-1)/(k<n?q(g):1) : 0)

DkPbr(m,g,k) = Pbr(m,g,k) - ( k-1 >= 0 ? Pbr(m,g,k-1) : 0 )

PbrSu(m0,m1,g) = sum[k=1:n-nt] DkPbr(m1,g,k)*Su(m0+m1,g,k)
PbrS(m0,m1,g)  = sum[k=1:n-nt] DkPbr(m1,g,k)*S(m0+m1,g,k)
PbrSl(m0,m1,g) = sum[k=1:n-nt] DkPbr(m1,g,k)*Sl(m0+m1,g,k)

poi(a,x) = exp(-x) * x**a/gamma(a+1)
P0(m0,g) = poi(m0,Dli(g,0)*mu)

P0brSu(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrSu(m0,m1,g)) )
P0brS(m1,g)  = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrS(m0,m1,g) ) )
P0brSl(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrSl(m0,m1,g)) )

inf = 25
threshold = 1e-10
# 1e-14 <= threshold <= 1e-1
reg_gamma_largex(a,x) = 1 - exp(-x) * sum[i=0:a-1] x**i/gamma(i+1)
reg_gamma_smallx(a,x) = exp(-x) * sum[i=a:a+inf] x**i/gamma(i+1)
reg_gamma(a,x) = ( x>=0 ? igamma(a,x) : ( igamma(a,-x)>threshold ? reg_gamma_largex(a,x) : reg_gamma_smallx(a,x) ) )

Pc(m0,D0,Pbr) = reg_gamma(m0+1,(mu-Pbr)*D0) / poi(m0+1,(mu-Pbr)*D0) * D0*Pbr / (1-poi(0,D0*Pbr)) / (m0+1)

P0brcSu(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrSu(m0,m1,g)) ) * Pc(m0,Dli(g,0),PbrSu(m0,m1,g))
P0brcS(m1,g)  = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrS(m0,m1,g) ) ) * Pc(m0,Dli(g,0),PbrS(m0,m1,g) )
P0brcSl(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrSl(m0,m1,g)) ) * Pc(m0,Dli(g,0),PbrSl(m0,m1,g))

#Pcorr_1(m0,D0,Pbr) = reg_gamma(m0+1,(mu-Pbr)*D0) / (m0+1) / poi(m0+1,(mu-Pbr)*D0)
#P0brSu_1(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * Dli(g,0)*PbrSu(m0,m1,g) * Pcorr_1(m0,Dli(g,0),PbrSu(m0,m1,g))
#P0brS_1(m1,g)  = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * Dli(g,0)*PbrS(m0,m1,g)  * Pcorr_1(m0,Dli(g,0),PbrS(m0,m1,g) )
#P0brSl_1(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * Dli(g,0)*PbrSl(m0,m1,g) * Pcorr_1(m0,Dli(g,0),PbrSl(m0,m1,g))
#rep 1-(1-P0brS_1(1,x)-P0brS_1(2,x))**N0 ls 7, 1-(1-P0brS_1(1,x)-P0brS_1(2,x)-P0brS_1(3,x))**N0 ls 4

#P0brSu_3(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrSu(m0,m1,g)) ) / (m0+1)
#P0brS_3(m1,g)  = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrS(m0,m1,g) ) ) / (m0+1)
#P0brSl_3(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] P0(m0,g) * ( 1-exp(-Dli(g,0)*PbrSl(m0,m1,g)) ) / (m0+1)

#rep 1-(1-P0brS_3(1,x)-P0brS_3(2,x))**N0 ls 7, 1-(1-P0brS_3(1,x)-P0brS_3(2,x)-P0brS_3(3,x))**N0 ls 4

#rep 1-(1-P0brSu(1,x))**N0 ls 8, 1-(1-P0brS(1,x))**N0 ls 8, 1-(1-P0brSl(1,x))**N0 ls 8
#rep 1-(1-P0brSu(2,x))**N0 ls 2, 1-(1-P0brS(2,x))**N0 ls 2, 1-(1-P0brSl(2,x))**N0 ls 2

#rep 1-(1-P0brS(1,x)-P0brS(2,x))**N0 ls 7, 1-(1-P0brS(1,x)-P0brS(2,x)-P0brS(3,x))**N0 ls 4 title ""

#rep  1-exp(-PSu(x)*N0) ls 1, 1-exp(-PS(x)*N0) ls 1, 1-exp(-PSl(x)*N0) ls 1

CalcCheck(m1,g) = sum[m0=plus(mc(g)-m1):plus(mc(g)-m1+mp)] Dli(g,0)*exp(PbrS(m0,m1,g) - Dli(g,0)* PbrS(m0,m1,g)) *(Dli(g,0) *mu)**m0 * (Dli(g,0)* (mu - PbrS(m0,m1,g)))**(-1-m0)*PbrS(m0,m1,g)*(gamma(1+m0)-(1-reg_gamma(1 + m0, Dli(g,0)*(mu - PbrS(m0,m1,g))))*m0!) /m0!
                      



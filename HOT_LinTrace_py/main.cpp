#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  /* time */
#include <math.h> //log iylesmi
#include <random>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <sys/time.h>

using namespace std;

struct szint //Ebben tárolom az egy szinthez tartozó rátákat és a szint várt méretét
{
    double rscdplusd,rscd,racd,delta,pk,qk;
    int Nk;
};

struct lista
{
    double ertek;
    int szintszam, sejtszam, tipus;
};

struct sejt
{
    int oszt_szam,mut_szam,n_acd,n_scd,n_scdplusd,id;
    double rscdplusd,rscd,racd;

};

double idoskala;//egy idõlépés hossza
double ido; //amennyi ideig fut a szim.
double legyartando;
vector<szint> szintek; //vektor amiben minden szinthez minden ráta meg van adva
double mutrata;
double szamlalo; // ebbe fogom összeadni a rátákat
int szintszam;
int instanciak;
int instancia;
int gen;
int maxMut;//maximálisan begyűjthető mutációk száma
double randdriver;// mutrata*drivergének száma/összes   ~ 0.84*70/20000
double s_acd;
double s_scd;
double s_scdd; //fittnessz erősség
int sumnacd;  // összesített driver mutációk az adott szinten acd,scd,scdplusdből
int sumnscd;
int sumnscdplusd;
double utolsodelta;
double idosum;
double Nsuminstanc=0;
double Nnegyzetatlag_Ref=0;
double Nnegyzetatlag_Varied=0;
double supernegyzetart_Varied;
double Natlag_Ref=0;
double Natlag_Varied;
int vartosszes;
int Nrak = 0;
double B;
int rakosodas;
double STOP;
double Dszum=0;
double Dszumnegyzet;
double Dnegyzetszum=0;
double Dnegyzetatlag=0;
double Dn_atlagsum=0;
double D_natlag=0;
int legyartottatlag=0;
int rendszermeret=0;
int boolkapcs = 0;
double differencialt_sum =0;
double mert_tranziensido;
double N_idoatlagsum=0;
int N_idokanter = 0;
double gamma_manual = 0;

double superatl_Ref=0;
double superatl_Varied=0;
double summ;
double summNegyzet;
double sosszeg;
int insrendszmeret;
int systemmutnumber=0;
double atlsystemmutnumber=0;
double atlmut_scdd = 0;
double atlmut_scd = 0;
int mutsum_scdd=0;
int mutsum_scd=0;
double stemMutTime = 0;
int mutansKimos = 0;


int Nmutmax=0;
char flag_optimal; //opt gamma?
char flag_stemMut; //őssejt mut?
char flag_gnuplot;
char flag_idKiir;
char flag_kimenoKiir;
char flag_pkqk;
char flag_idoplotok;
int flag_tranziens=0;
char flag_legyartando_ido_Futas;
char flag_neutr_s;

string outputDir;
int mutCounterStrike;
int mutCounterStrikeszum = 0;
int D_n=0;
int D_max_lineage = 0;
int D_max_lineage_sum = 0;
double D_n_negyzet=0;
int D_n_kilepes = 0;
int D_n_sum=0;
int D_n_max=0;
int differencialt_sejtek=0;
double ettol=0;
double eddig=0;
int Renmut=0;
int maxMutszubpop=0;
int maxMutKimosszubpop=0;
int maxMutelement=0;
int maxMutelementKimos=0;
double S = 0;
int S_rak = 0;
int ossejt_kritmut = 0;
int ossejt_kritmut_szam=0;
int idCounter = 0;
int Nsum = 0;

int scd_counter = 0;
int scdd_counter = 0;
int acd_counter = 0;

int stem_scd_counter = 0;
int stem_scdd_counter = 0;
int stem_acd_counter = 0;
int elseCounter = 0;
double tranziens_ido=0;
int kihalas = 0;
int legyartott_sejtek=0;


void txtsorcsere(string ezt, string erre, ifstream& in,const char *inStreamFileName)
{
    ofstream out("tmp.txt");
    string tmp;
    while(true){
        getline(in,tmp);
        if(tmp==ezt){
            out<<erre<<endl;
        }else{
            out<<tmp<<endl;
        }
        if(in.eof()) break;
    }
    rename("tmp.txt",inStreamFileName);
    out.close();


}
void fancyRead(ifstream & ifs, string & tmp){

    while(true){
        getline(ifs,tmp);
        if(ifs.eof()){
            break;
        }else if(tmp.length()!=0){
            if(tmp.at(0)!='#') break;
        }
    }
}


ifstream f;
void txtsorcsere(string ezt, string erre, ifstream& in, const char *inStreamFileName);
void fancyRead(ifstream & ifs, string & tmp);


map<int,vector<sejt> > x;//ebbe tároljuk a sejteket


int main()
{
	
	unsigned Seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine Generator (Seed);
	struct timeval time;
    gettimeofday(&time,NULL);
    double seed =(time.tv_sec * 100) + (time.tv_usec / 100);
    srand(seed);
  	mt19937 generator (seed);
  	uniform_real_distribution<double> dis(0.0, 1.0); //random generálás


    f.open("adatok.txt");

    string tempRead;


    while(!f.eof()){

        f>>tempRead;
        if(tempRead=="instanciak="){
            f>>instanciak;
        }else if(tempRead=="legyartando="){
            f>>legyartando;
        }else if(tempRead=="ido="){
            f>>ido;
        }else if(tempRead=="rakosodas="){
            f>>rakosodas;
        }else if(tempRead=="STOP="){
            f>>STOP;
        }else if(tempRead=="szintszam="){
            f>>szintszam;
        }else if(tempRead=="mutrata="){
            f>>mutrata;
        }else if(tempRead=="s_acd="){
            f>>s_acd;
        }else if(tempRead=="s_scd="){
            f>>s_scd;
        }else if(tempRead=="s_scdd="){
            f>>s_scdd;
        }else if(tempRead=="B="){
            f>>B;
        }else if(tempRead=="maxMut="){
            f>>maxMut;
        }else if(tempRead=="flag_optimal="){
            f>>flag_optimal;
        }else if(tempRead=="gamma_manual="){
            f>>gamma_manual;
        }else if(tempRead=="flag_stemMut="){
            f>>flag_stemMut;
        }else if(tempRead=="outputDir="){
            f>>outputDir;
        }else if(tempRead=="flag_gnuplot="){
            f>>flag_gnuplot;
        }else if(tempRead=="flag_idKiir="){
            f>>flag_idKiir;
        }else if(tempRead=="flag_pkqk="){
            f>>flag_pkqk;
        }else if(tempRead=="flag_legyartando_ido_futas="){
            f>>flag_legyartando_ido_Futas;
        }else if(tempRead=="flag_neutr_s="){
            f>>flag_neutr_s;
        }else if(tempRead=="flag_idoplotok="){
            f>>flag_idoplotok;
        }else if(tempRead=="matrix="){
            szintszam++;
            for(int i=0; i<szintszam;i++)
            {
                szint ujszint;
                f>>ujszint.delta;
                f>>ujszint.Nk;

			    if(i==0){
                    f>>ujszint.pk;
                    ujszint.qk = 0;
                }
                if(flag_pkqk=='p'&& i>0) {
                    f>>ujszint.pk;
                    ujszint.qk = 0;
                }

                if(flag_pkqk=='q' && i>0){
                    f>>ujszint.qk;
                    ujszint.pk = 0;
                }




                ujszint.racd=0;
                ujszint.rscd=0;
                ujszint.rscdplusd=0;
                szintek.push_back(ujszint);
            }
        }else{
            getline(f,tempRead);
        }
    }
    if(outputDir=="default"){
        outputDir="";
    }
    f.close();


	 if(flag_optimal=='y' || flag_optimal== 'Y') //Optimalis ratak
	{
		 double gamma_optimalis;
		 gamma_optimalis=pow(legyartando,1.0/(double) (szintszam-1) );
		 utolsodelta=1;


		 if(pow(legyartando,1.0/(double) (szintszam-1) )<2.0)
		 {
		    cout<<"Nem fog elmenni a megadott szintszamig ekkora N-el, mert az optimális gamma tul nagy lesz. Ha ez zavar, noveld meg N-t"<<endl;
		 }

		 szintek[szintszam-1].delta=2.0;
		 szintek[szintszam-2].delta=1.0;
		 for(int i=szintszam-2;i>=0;i--)
		 {
		    szintek[i-1].delta=szintek[i].delta/gamma_optimalis;
		 }


		 for(int i=0;i<szintszam;i++)
		 {

		    if(flag_pkqk=='p'){
		        szintek[i].qk=2*(szintek[i-1].delta/szintek[i].delta)/szintek[i].pk;
		    }

		    else if(flag_pkqk=='q'){
		        szintek[i].pk=2*(szintek[i-1].delta/szintek[i].delta)/szintek[i].qk;
		    }

		    else{
		        cout<<"Nem sikerult valasztani, irj pk, vagy qk-t"<<endl;
		        return 1;
		    }

		    if(i==0){
		        szintek[i].qk=0;
		    }

		    szintek[i].racd=szintek[i].delta*(1-szintek[i].pk);
		    szintek[i].rscd=0.5*szintek[i].delta*(1-szintek[i].qk)*szintek[i].pk;
		    szintek[i].rscdplusd=0.5*szintek[i].delta*szintek[i].pk;



			//szintek[i].racd=(1.0/szintek[i].Nk)*2*szintek[i].delta*(1-szintek[i].pk)/(szintek[i].pk*szintek[i].qk);

			    if(szintek[i].pk>1 || szintek[i].qk>1)
			    {
			        cout<<"baj van, a pk vagy qk nagyobb lett 1-nel, valassz jobb pk-t ezen a szinten:"<<i<<endl;
			        cout<<szintek[i].pk<<endl;
			        cout<<szintek[i].qk<<endl;

			        if(gamma_optimalis<2.0)
			        {
			            cout<<"Az opt. gamma it túl kicsi (<2.0). Próbáld meg nagyobb N-re ha több szintet akarsz (az optimális görbe csak idáig tart)";
			        }

			        return 1;
			    }
			        if((szintek[i+1].delta/szintek[i].delta)<2.0 && i!=szintszam-1)
			        {
			            cout<<"baj van, a delta(k+1)/delta(k) kisebb lett 2.0-nel ezen a szinten:"<<i<<endl;
			            return 3;
			        }

			 }
	}


	else if(flag_optimal=='n' || flag_optimal== 'N') // manualis ratak
	{
	 double gamma_optimalis;
	 gamma_optimalis=gamma_manual;
	 utolsodelta=1;


		 if(gamma_manual<2.0)
		 {
		    cout<<"Nem fog elmenni a megadott szintszamig ekkora N-el, mert az optimális gamma tul nagy lesz. Ha ez zavar, noveld meg N-t"<<endl;
		 }

		 szintek[szintszam-1].delta=2.0;
		 szintek[szintszam-2].delta=1.0;
		 for(int i=szintszam-2;i>=0;i--)
		 {
		    szintek[i-1].delta=szintek[i].delta/gamma_optimalis;
		 }

		 for(int i=0;i<szintszam;i++)
		 {
		    if (i>0){
		        if(flag_pkqk=='p'){
		        szintek[i].qk=2*(szintek[i-1].delta/szintek[i].delta)/szintek[i].pk;
		    }

		    else if(flag_pkqk=='q'){
		        szintek[i].pk=2*(szintek[i-1].delta/szintek[i].delta)/szintek[i].qk;
		    }

		    else{
		        cout<<"Nem sikerult valasztani, irj pk, vagy qk-t"<<endl;
		        return 1;
		    }
		    }


		    szintek[i].racd=szintek[i].delta*(1-szintek[i].pk);
		    szintek[i].rscd=0.5*szintek[i].delta*(1-szintek[i].qk)*szintek[i].pk;
		    szintek[i].rscdplusd=0.5*szintek[i].delta*szintek[i].pk;



		//szintek[i].racd=(1.0/szintek[i].Nk)*2*szintek[i].delta*(1-szintek[i].pk)/(szintek[i].pk*szintek[i].qk);

		    if(szintek[i].pk>1 || szintek[i].qk>1)
		    {
		        cout<<"baj van, a pk vagy qk nagyobb lett 1-nel, valassz jobb pk-t ezen a szinten:"<<i<<endl;
		        cout<<szintek[i].pk<<endl;
		        cout<<szintek[i].qk<<endl;

		        if(gamma_optimalis<2.0)
		        {
		            cout<<"Az opt. gamma it túl kicsi (<2.0). Próbáld meg nagyobb N-re ha több szintet akarsz (az optimális görbe csak idáig tart)";
		        }

		        return 1;
		    }
		        if((szintek[i+1].delta/szintek[i].delta)<2.0 && i!=szintszam-1)
		        {
		            cout<<"baj van, a delta(k+1)/delta(k) kisebb lett 2.0-nel ezen a szinten:"<<i<<endl;
		            return 3;
		        }

		 }

		}

		else
		{
		    cout<<"Nem sikerult valasztani..."<<endl;
		    return 1;
	}



vartosszes = 0;

for(int k=0; k<szintszam;++k){
	vartosszes+=szintek[k].Nk;
}

tranziens_ido=0;
double ratasumma = 0;
for(int i=1; i<szintszam-1;++i){

    if(i>=1){
        tranziens_ido += szintek[i].Nk/szintek[i-1].delta;
        int b = i-1;
        ratasumma += szintek[b].delta-szintek[b-1].delta;
    }

}

ofstream g; //kimenodadatok
ofstream p(outputDir+"vegallapotok.txt");

char num = 'l';

if(gamma_manual>2.5){
    num = 'S';
}
else{
    num = 'L';
}

ofstream linTree(outputDir+"Tree"+num+".txt");



vector<int> talaltam_Mutanst;
for(int j=0; j<maxMut+1;++j){
    int zero =0;
    talaltam_Mutanst.push_back(zero);
}

vector<int> mutans_Kapcsolo;
for(int j=0; j<maxMut+1;++j){
    int zero =0;
    mutans_Kapcsolo.push_back(zero);
}

vector<double> D_n_vec;
for(int j=0; j<maxMut+1;++j){
    int zero =0;
    D_n_vec.push_back(zero);
}

vector<int> talaltam_Mutanst2;
for(int j=0; j<maxMut+1;++j){
    int zero =0;
    talaltam_Mutanst2.push_back(zero);
}

vector<int> mutans_Kapcsolo2;
for(int j=0; j<maxMut+1;++j){
    int zero =0;
    mutans_Kapcsolo2.push_back(zero);
}

vector<double> P_muem;
for(int j=0; j<maxMut+1;++j){
    int zero =0;
    P_muem.push_back(zero);
}

for(instancia=0;instancia<instanciak;instancia++){ //instanciak for


	string filenameRoot2("kimenoadatok_");
    stringstream sss;
    sss << filenameRoot2 <<instancia<< ".txt";
    g.open(outputDir+sss.str() );

	for(int i=0;i<szintszam;i++)
    {
        x[i].clear();

    }//inicializalja az adatszerkezetet



	cout<<endl<<"Instancia: "<<instancia<<endl;


	poisson_distribution<int> distribution (mutrata);

	sejt ossejt;
    
    idCounter=0;
    //ossejt properties beallitasa

    ossejt.oszt_szam=0;
    ossejt.mut_szam=0;
    ossejt.racd=szintek[0].racd;
    ossejt.rscd=szintek[0].rscd;
    ossejt.rscdplusd=szintek[0].rscdplusd;
    ossejt.n_acd=0;
    ossejt.n_scd=0;
    ossejt.n_scdplusd=0;
    ossejt.id=idCounter;

    for(int i=0; i<szintek[0].Nk; ++i){
        x[0].push_back(ossejt);
    }
/*
	 sejt kezdosejt;
     for(int k=1; k<szintszam; ++k){
        for(int l=0; l<szintek[k].Nk; ++l){
            sejt kezdosejt;
            kezdosejt.oszt_szam=k;
            kezdosejt.mut_szam=0;
            kezdosejt.racd=szintek[k].racd;
            kezdosejt.rscd=szintek[k].rscd;
            kezdosejt.rscdplusd=szintek[k].rscdplusd;
            kezdosejt.n_acd=0;
            kezdosejt.n_scd=0;
            kezdosejt.n_scdplusd=0;
            idCounter++;
            kezdosejt.id=idCounter;
            x[k].push_back(kezdosejt);
        }
    }
*/
    double eltelt_ido=0;
    differencialt_sejtek=0;


    vector<double> szintRataSum;
    for(int i=0; i<szintszam;i++){
        szintRataSum.push_back(szintek[i].racd+szintek[i].rscd+szintek[i].rscdplusd);
    }

    gen=0;

    Nsum = 0;

    int tranz_kapcs=0;

	if(flag_legyartando_ido_Futas=='i' || flag_legyartando_ido_Futas=='k'){
		ettol = eltelt_ido;
		if(ido!=0){
			eddig = ido;
		}
		else{eddig = (legyartando/szintek[szintszam-2].delta);}
	} 
	legyartott_sejtek = 0;

	if(flag_legyartando_ido_Futas=='l'){
	    ettol = legyartott_sejtek;
	    if(ido!=0){
	        eddig = ido;
	    }
	    else{eddig = legyartando/szintek[szintszam-2].delta;}
	}

	 while((ettol<=eddig-1 && Nsum<STOP*vartosszes)){

		if(flag_legyartando_ido_Futas=='i' || flag_legyartando_ido_Futas=='k'){
	        ettol = eltelt_ido;
	        if(ido!=0){
	            eddig = ido;
	        }
	        else{eddig = legyartando/szintek[szintszam-2].delta;}
	    }

	    if(flag_legyartando_ido_Futas=='l'){
	        ettol = legyartott_sejtek;
	        if(ido!=0){
	            eddig = ido;
	        }
	        else{eddig = legyartando/szintek[szintszam-2].delta;}
	    }

	 	Nsum = 0;

    	for(int k=0; k<szintszam; k++){

    		Nsum+= x[k].size();

    	}


		if(flag_neutr_s =='s'){

		for(int i=0; i<szintszam;i++){

			for(unsigned int j=0;j<x[i].size();j++){

			if(i==szintszam-1){

				x[i][j].racd=0;
				x[i][j].rscd=0;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			else if(i==0){
				x[i][j].racd=szintek[i].racd+x[i][j].n_acd*s_acd*szintRataSum[i];
				x[i][j].rscd=szintek[i].rscd+x[i][j].n_scd*s_scd*szintRataSum[i];
				x[i][j].rscdplusd=szintek[i].rscdplusd+x[i][j].n_scdplusd*s_scdd*szintRataSum[i];
			}

			//if(gen<100) cout<<x[i][j].rscdplusd<<" "<<eltelt_ido<<endl;


			else{
				x[i][j].racd=szintek[i].racd;
				x[i][j].rscd=szintek[i].rscd;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

				if(x[i][j].rscdplusd<0) x[i][j].rscdplusd=0;
				if(x[i][j].rscd<0) x[i][j].rscd=0;
				if(x[i][j].racd<0) x[i][j].racd=0;
			}
			}
		}
		double kritmut = 0;
	    
	    if(s_scd > 0){
	        kritmut = ceil((1.0/(gamma_manual-1))/s_scd) ;
	    }

	    if(s_scdd < 0){
	        kritmut = -ceil((1.0/(gamma_manual-1))/s_scdd) ;;

	    }

		else  if(flag_neutr_s =='h'){

			for(int i=0; i<szintszam;i++){

			for(unsigned int j=0;j<x[i].size();j++){

			if(i==szintszam-1){

				x[i][j].racd=0;
				x[i][j].rscd=0;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			else if(i==0){
				x[i][j].racd=szintek[i].racd;
				x[i][j].rscd=szintek[i].rscd;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			//if(gen<100) cout<<x[i][j].rscdplusd<<" "<<eltelt_ido<<endl;


			else{
				if(x[i][j].n_scd >= kritmut){
					x[i][j].racd=szintek[i].racd+x[i][j].n_acd*s_acd*szintRataSum[i];
					x[i][j].rscd=(szintek[i].rscd+x[i][j].n_scd*s_scd*szintRataSum[i]);
					x[i][j].rscdplusd=(szintek[i].rscdplusd+x[i][j].n_scdplusd*s_scdd*szintRataSum[i]);
				}

				else{
					 x[i][j].racd=szintek[i].racd;
					x[i][j].rscd=szintek[i].rscd;
					x[i][j].rscdplusd=szintek[i].rscdplusd;

				}

			}

			if(x[i][j].rscdplusd<0) x[i][j].rscdplusd=0;
			if(x[i][j].rscd<0) x[i][j].rscd=0;
			if(x[i][j].racd<0) x[i][j].racd=0;
			}
			}
		}

		if(x[szintszam-1].size()>0 && tranz_kapcs==0){
			mert_tranziensido=eltelt_ido;
			tranz_kapcs=1;


		}

		else  if(flag_neutr_s =='p'){

			for(int i=0; i<szintszam;i++){

			for(unsigned int j=0;j<x[i].size();j++){

			if(i==szintszam-1){

				x[i][j].racd=0;
				x[i][j].rscd=0;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			else if(i==0){
				x[i][j].racd=szintek[i].racd;
				x[i][j].rscd=szintek[i].rscd;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			//if(gen<100) cout<<x[i][j].rscdplusd<<" "<<eltelt_ido<<endl;


			else{
				x[i][j].racd=(szintek[i].racd+x[i][j].n_acd*s_acd*szintRataSum[i]);
				x[i][j].rscd=(szintek[i].rscd+x[i][j].n_scd*s_scd*szintRataSum[i]);
				x[i][j].rscdplusd=(szintek[i].rscdplusd+x[i][j].n_scdplusd*s_scdd*szintRataSum[i]);
			}

			if(x[i][j].rscdplusd<0) x[i][j].rscdplusd=0;
			if(x[i][j].rscd<0) x[i][j].rscd=0;
			if(x[i][j].racd<0) x[i][j].racd=0;
			}
			}
		}

		else if(flag_neutr_s =='t'){

			for(int i=0; i<szintszam;i++){

			for(unsigned int j=0;j<x[i].size();j++){

			if(i==szintszam-1){

				x[i][j].racd=0;
				x[i][j].rscd=0;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			else if(i==0){
					x[i][j].racd=szintek[i].racd+(x[i][j].n_acd*s_acd*szintRataSum[i]);
					x[i][j].rscd=szintek[i].rscd+x[i][j].n_scd*s_scd*szintRataSum[i];
					x[i][j].rscdplusd=szintek[i].rscdplusd+x[i][j].n_scdplusd*s_scdd*szintRataSum[i];
				}

			//if(gen<100) cout<<x[i][j].rscdplusd<<" "<<eltelt_ido<<endl;


			else{
			   x[i][j].racd=(szintek[i].racd+x[i][j].n_acd*s_acd*szintRataSum[i]);
			x[i][j].rscd=(szintek[i].rscd+x[i][j].n_scd*s_scd*szintRataSum[i]);
			x[i][j].rscdplusd=(szintek[i].rscdplusd+x[i][j].n_scdplusd*s_scdd*szintRataSum[i]);
			}

			if(x[i][j].rscdplusd<0) x[i][j].rscdplusd=0;
			if(x[i][j].rscd<0) x[i][j].rscd=0;
			if(x[i][j].racd<0) x[i][j].racd=0;
			}
			}
		}



		else if(flag_neutr_s=='n'){
			for(int i=0; i<szintszam;i++){

			for(unsigned int j=0;j<x[i].size();j++){

			if(i==szintszam-1){

			x[i][j].racd=0;
			x[i][j].rscd=0;
			x[i][j].rscdplusd=szintek[i].rscdplusd;
			}

			else if(i==0){

			x[i][j].racd=szintek[i].racd;
			x[i][j].rscd=szintek[i].rscd;;
			x[i][j].rscdplusd=szintek[i].rscdplusd;
			}


			else{
				x[i][j].racd=szintek[i].racd;
				x[i][j].rscd=szintek[i].rscd;
				x[i][j].rscdplusd=szintek[i].rscdplusd;
			}
			}
			}
		}

		else{cout<<"Válassz n = neutrális mutációk , s= szelekció..."<<endl; return 0;}


		sumnacd=0;
		sumnscd=0;
		sumnscdplusd=0;
		vector<lista> StateVec;
		StateVec.clear();
		if(Nsum ==0){
			kihalas ++;
			break;

		}

		szamlalo=0;


		for(int i=0; i<szintszam; i++){

			for(int j=0; j<x[i].size(); j++){

				lista ujlistaelem;

				ujlistaelem.sejtszam=j;
                ujlistaelem.szintszam=i;

                if(x[i][j].rscd>0){

                	szamlalo+=x[i][j].rscd;
		            ujlistaelem.ertek=szamlalo;
		            ujlistaelem.tipus=0;
		            StateVec.push_back(ujlistaelem);
	
                }

                if(x[i][j].rscdplusd>0){

                	szamlalo+=x[i][j].rscdplusd;
		            ujlistaelem.tipus=1;
		            ujlistaelem.ertek=szamlalo;
		           	StateVec.push_back(ujlistaelem);


                }

				if(x[i][j].racd>0){

					szamlalo+=x[i][j].racd;
	                ujlistaelem.tipus=2;
	                ujlistaelem.ertek=szamlalo;
	                StateVec.push_back(ujlistaelem);	
				}                                
                        
			} // kumulativ lista

		}

		double T = szamlalo*dis(generator);
		int esemeny_szintje;
        int esemeny_sejtszama;
        int esemeny_tipus; // 0-rscd, 1 rscdplusd, 2 acd


		int L = 0;
		int R = StateVec.size()-1;
		int mid = floor((StateVec.size())/2.0);


		while(L<=R){
			mid = floor((L+R)/2.0);
			if(StateVec[mid].ertek<T){
				if(L==R){
					mid = mid+1;
					break;	
				}
				L = mid+1;
			}

			else if(StateVec[mid].ertek>T){
				R = mid-1;

			}
			else{
				break;
			} // felezos modszer
		}

		esemeny_tipus = StateVec[mid].tipus;
		esemeny_szintje = StateVec[mid].szintszam;
		esemeny_sejtszama = StateVec[mid].sejtszam;

		 if(esemeny_szintje==0){
        	if(esemeny_tipus==0){

        		stem_scd_counter++;
        	}
      
        	if(esemeny_tipus==1){
        		stem_scdd_counter++;
        	}
        	
        	if(esemeny_tipus==2){
        		stem_acd_counter++;
        	}

        }

		x[esemeny_szintje][esemeny_sejtszama].oszt_szam++;

		linTree<<esemeny_szintje<<'\t'<<esemeny_sejtszama<<'\t'<<esemeny_tipus<<'\t'<<eltelt_ido<<'\t'<<eltelt_ido<<'\t'<<x[esemeny_szintje][esemeny_sejtszama].id<<'\t'<<x[szintszam-1].size()<<'\t'<<x[0].size()<<'\t';
		linTree<<endl;

		if(esemeny_tipus==0){ //scd event occurs

			sejt ujsejt;
			idCounter++;
            ujsejt.n_acd=x[esemeny_szintje][esemeny_sejtszama].n_acd;
            ujsejt.n_scd=x[esemeny_szintje][esemeny_sejtszama].n_scd;
            ujsejt.n_scdplusd=x[esemeny_szintje][esemeny_sejtszama].n_scdplusd;
            ujsejt.oszt_szam=x[esemeny_szintje][esemeny_sejtszama].oszt_szam;
            ujsejt.mut_szam=x[esemeny_szintje][esemeny_sejtszama].mut_szam;
            ujsejt.id=idCounter;

             if(flag_stemMut=='y' || flag_stemMut=='Y'){

             	if(ujsejt.mut_szam<maxMut && esemeny_szintje<szintszam-1){
            		ujsejt.mut_szam+= distribution(generator);
            		ujsejt.n_scd = ujsejt.mut_szam;
	            }

	            if(x[esemeny_szintje][esemeny_sejtszama].mut_szam < maxMut && esemeny_szintje<szintszam-1){
	          	    x[esemeny_szintje][esemeny_sejtszama].mut_szam += distribution(generator);
	            	x[esemeny_szintje][esemeny_sejtszama].n_scd = x[esemeny_szintje][esemeny_sejtszama].mut_szam;
	            }

	            for(int i=1; i<maxMut+1; ++i){
		            if((ujsejt.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
		                talaltam_Mutanst[i]++;
		                mutans_Kapcsolo[i] += 1;
		                break;
		            }

	            }

	            for(int i=1; i<maxMut+1; ++i){
		            if((x[esemeny_szintje][esemeny_sejtszama].mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
		                talaltam_Mutanst[i]++;
		                mutans_Kapcsolo[i] += 1;
		                break;
		            }

	            }


             }

             else{
             	if(esemeny_szintje>0){

             		if(ujsejt.mut_szam<maxMut && esemeny_szintje<szintszam-1){
		            	ujsejt.mut_szam+= distribution(generator);
		            	ujsejt.n_scd = ujsejt.mut_szam;
		            }

		            if(x[esemeny_szintje][esemeny_sejtszama].mut_szam <  maxMut && esemeny_szintje<szintszam-1){
		            x[esemeny_szintje][esemeny_sejtszama].mut_szam += distribution(generator);
		            	x[esemeny_szintje][esemeny_sejtszama].n_scd = x[esemeny_szintje][esemeny_sejtszama].mut_szam;
		            }

		            for(int i=1; i<maxMut+1; ++i){
			            if((ujsejt.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
			                talaltam_Mutanst[i]++;
			                mutans_Kapcsolo[i] += 1;
			                break;
			            }

		            }

		            for(int i=1; i<maxMut+1; ++i){
			            if((x[esemeny_szintje][esemeny_sejtszama].mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
			                talaltam_Mutanst[i]++;
			                mutans_Kapcsolo[i] += 1;
			                break;
			            }

		            }

             	}

             }

             x[esemeny_szintje].push_back(ujsejt);

		}

		if(esemeny_tipus==1){ //scdd event occurs


            if(esemeny_szintje<szintszam-1){
	            sejt ujsejt;
	            ujsejt.n_acd=x[esemeny_szintje][esemeny_sejtszama].n_acd;
	            ujsejt.n_scd=x[esemeny_szintje][esemeny_sejtszama].n_scd;
	            ujsejt.n_scdplusd=x[esemeny_szintje][esemeny_sejtszama].n_scdplusd;
	            ujsejt.oszt_szam=x[esemeny_szintje][esemeny_sejtszama].oszt_szam;
	            ujsejt.mut_szam=x[esemeny_szintje][esemeny_sejtszama].mut_szam;
	            ujsejt.id=x[esemeny_szintje][esemeny_sejtszama].id;

	            sejt ujsejt2;
	            idCounter++;
	            ujsejt2.n_acd=x[esemeny_szintje][esemeny_sejtszama].n_acd;
	            ujsejt2.n_scd=x[esemeny_szintje][esemeny_sejtszama].n_scd;
	            ujsejt2.n_scdplusd=x[esemeny_szintje][esemeny_sejtszama].n_scdplusd;
	            ujsejt2.oszt_szam=x[esemeny_szintje][esemeny_sejtszama].oszt_szam;
	            ujsejt2.mut_szam=x[esemeny_szintje][esemeny_sejtszama].mut_szam;
	            ujsejt2.id=idCounter;

	             if(flag_stemMut=='y' || flag_stemMut=='Y'){

		            if(ujsejt.mut_szam<maxMut && esemeny_szintje<szintszam-1){
		            	ujsejt.mut_szam+= distribution(generator);
		            	ujsejt.n_scd = ujsejt.mut_szam;
		            }

		            if(ujsejt2.mut_szam < maxMut && esemeny_szintje<szintszam-1){
		            	ujsejt2.mut_szam += distribution(generator);
		            	ujsejt2.n_scd = ujsejt2.mut_szam;
		            }

		            for(int i=1; i<maxMut+1; ++i){
			            if((ujsejt.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
			                talaltam_Mutanst[i]++;
			                mutans_Kapcsolo[i] += 1;
			                break;
			            }

		            }

		            for(int i=1; i<maxMut+1; ++i){
			            if((ujsejt2.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
			                talaltam_Mutanst[i]++;
			                mutans_Kapcsolo[i] += 1;
			                break;
			            }

		            }
	        	}

	        	else{
	        		if(esemeny_szintje>0){


			            if(ujsejt.mut_szam<maxMut && esemeny_szintje<szintszam-1){
			            	ujsejt.mut_szam+= distribution(generator);
			            	ujsejt.n_scd = ujsejt.mut_szam;
			            }

			            if(ujsejt2.mut_szam < maxMut && esemeny_szintje<szintszam-1){
			            	ujsejt2.mut_szam += distribution(generator);
			            	ujsejt2.n_scd = ujsejt2.mut_szam;
			            }

			            for(int i=1; i<maxMut+1; ++i){
				            if((ujsejt.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
				                talaltam_Mutanst[i]++;
				                mutans_Kapcsolo[i] += 1;
				                break;
				            }

			            }

			            for(int i=1; i<maxMut+1; ++i){
				            if((ujsejt2.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
				                talaltam_Mutanst[i]++;
				                mutans_Kapcsolo[i] += 1;
				                break;
				            }

			            }


	        		}


	        	}

            	x[esemeny_szintje+1].push_back(ujsejt);
            	x[esemeny_szintje+1].push_back(ujsejt2);
	
            }

			


            if(esemeny_szintje==szintszam-1){

            	D_n=x[esemeny_szintje][esemeny_sejtszama].oszt_szam;

            	for(int k = 0; k<maxMut; ++k){

            		D_n_vec[k+1]+=pow((double) x[esemeny_szintje][esemeny_sejtszama].oszt_szam-1.5,k);

            	}

            	legyartott_sejtek++;
            	
            }

            std::vector<sejt>::iterator it=x[esemeny_szintje].begin();
            for(int i=0;i<esemeny_sejtszama;i++)it++;
            x[esemeny_szintje].erase(it);


		}


		if(esemeny_tipus==2){ //acd event occurs

			sejt ujsejt;
			idCounter++;
            ujsejt.n_acd=x[esemeny_szintje][esemeny_sejtszama].n_acd;
            ujsejt.n_scd=x[esemeny_szintje][esemeny_sejtszama].n_scd;
            ujsejt.n_scdplusd=x[esemeny_szintje][esemeny_sejtszama].n_scdplusd;
            ujsejt.oszt_szam=x[esemeny_szintje][esemeny_sejtszama].oszt_szam;
            ujsejt.mut_szam=x[esemeny_szintje][esemeny_sejtszama].mut_szam;
            ujsejt.id=idCounter;


            
            if(flag_stemMut=='y' || flag_stemMut=='Y'){


	            if(ujsejt.mut_szam<maxMut && esemeny_szintje<szintszam-1){
	            	ujsejt.mut_szam+= distribution(generator);

	            	ujsejt.n_scd = ujsejt.mut_szam;
	            }


	            if(x[esemeny_szintje][esemeny_sejtszama].mut_szam < maxMut && esemeny_szintje<szintszam-1){
	            	x[esemeny_szintje][esemeny_sejtszama].mut_szam += distribution(generator);
	            	if(esemeny_szintje==0 && x[esemeny_szintje][esemeny_sejtszama].mut_szam >0 && ossejt_kritmut ==0){

	            		ossejt_kritmut_szam++;
	            		ossejt_kritmut = 1;

	            	}
	            	x[esemeny_szintje][esemeny_sejtszama].n_scd = x[esemeny_szintje][esemeny_sejtszama].mut_szam;
	            }

	            for(int i=1; i<maxMut+1; ++i){
		            if((ujsejt.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
		                talaltam_Mutanst[i]++;
		                mutans_Kapcsolo[i] += 1;
		                break;
		            }

	            }

	            for(int i=1; i<maxMut+1; ++i){
		            if((x[esemeny_szintje][esemeny_sejtszama].mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
		                talaltam_Mutanst[i]++;
		                mutans_Kapcsolo[i] += 1;
		                break;
		            }

	            }

            }

            else{

            	if(esemeny_szintje>0){

            		if(ujsejt.mut_szam<maxMut && esemeny_szintje<szintszam-1){
		            	ujsejt.mut_szam+= distribution(generator);
		            	ujsejt.n_scd = ujsejt.mut_szam;
		           	}

		            if(x[esemeny_szintje][esemeny_sejtszama].mut_szam < maxMut && esemeny_szintje<szintszam-1){
		      	        x[esemeny_szintje][esemeny_sejtszama].mut_szam += distribution(generator);
		            	x[esemeny_szintje][esemeny_sejtszama].n_scd = x[esemeny_szintje][esemeny_sejtszama].mut_szam;
		            }

		            for(int i=1; i<maxMut+1; ++i){
			            if((ujsejt.mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
			                talaltam_Mutanst[i]++;
			                mutans_Kapcsolo[i] += 1;
			                break;
			            }

		            }

		            for(int i=1; i<maxMut+1; ++i){
			            if((x[esemeny_szintje][esemeny_sejtszama].mut_szam == i && mutans_Kapcsolo[i] == 0) && esemeny_szintje<szintszam-1) {
			                talaltam_Mutanst[i]++;
			                mutans_Kapcsolo[i] += 1;
			                break;
			            }

		            }

            	}



            }


            if(esemeny_szintje<szintszam-1){
            	x[esemeny_szintje+1].push_back(ujsejt);
            }
            

		}
	

		eltelt_ido+=1.0/szamlalo;
		double elteltido_prev = 0;

	 	int kritmutBent1=0;
        int kritmutBent2=0;
        int kritmutBent3=0;
        int kritmutBent4=0;
        for(int i=1;i<szintszam-1;i++){
            for(int j=0;j<x[i].size();j++){
                if (x[i][j].mut_szam >= kritmut){
                    mutansKimos++;
                    kritmutBent1++;
                }

                if (x[i][j].mut_szam >= kritmut+1){
                    mutansKimos++;
                    kritmutBent2++;
                }

                if (x[i][j].mut_szam >= kritmut+2){
                    mutansKimos++;
                    kritmutBent3++;
                }

                if (x[i][j].mut_szam >= kritmut+3){
                    mutansKimos++;
                    kritmutBent4++;
                }
            }
        }

        int kritStemMut = 0;


        for(int j=0;j<x[0].size();j++){

            if (x[0][j].mut_szam >= 1){
                kritStemMut++;
            }

        }


        double S = 0;

        S = 1.0 - (1.0 / ( 1.0 + 2*s_scd/szintek[0].pk));


        if(flag_legyartando_ido_Futas=='k' && kritStemMut > min(10.0/S,1000.0) ){
            Nrak++;

            break;

        }

        S = 1.0 - (1.0 / ( 1.0 + szintek[szintszam-2].qk*(kritmut*s_scd*(gamma_manual-1.0)-1.0) ) );

        if(flag_legyartando_ido_Futas=='k' && kritmutBent1 > min(10.0/S,1000.0) ){
            Nrak++;
            break;
        }

        S = 1.0 - (1.0 / ( 1.0 + szintek[szintszam-2].qk*( (kritmut+1)*s_scd*(gamma_manual-1.0)-1.0) ) );

        if(flag_legyartando_ido_Futas=='k' && kritmutBent2 > min(10.0/S,1000.0) ){
            Nrak++;
            break;
        }

        S = 1.0 - (1.0 / ( 1.0 + szintek[szintszam-2].qk*((kritmut+2)*s_scd*(gamma_manual-1.0)-1.0) ) );

        if(flag_legyartando_ido_Futas=='k' && kritmutBent3 > min(10.0/S,1000.0) ){
            Nrak++;
            break;
        }

        S = 1.0 - (1.0 / ( 1.0 + szintek[szintszam-2].qk*((kritmut+3)*s_scd*(gamma_manual-1.0)-1.0) ) );

        if(flag_legyartando_ido_Futas=='k' && kritmutBent4 > min(10.0/S,1000.0) ){
            Nrak++;
            break;
        }
        

        


		if(x[0].size()==0){

			kihalas++;
			break;

		}

	 } // while where all cell divisions take place

	 D_n_sum+=D_n;
	 D_n_negyzet+= pow(D_n,2);
	

	 for(int k = 1; k<maxMut; ++k){
		P_muem[k] += 2.0*pow(mutrata,k)*(double)D_n_vec[k]/(double)tgamma((double)k);
 	 }


 	 for(int k = 1; k<maxMut+1; ++k){
		D_n_vec[k-1] = 0;
 	 }




	//g.open("kimenoadatok.txt");
    //szint adatok kiiratas
  	int w=17;
    g<<"Az egyes szintek adatai:"<<endl<<endl;
    g<<setw(5)<<"szint";
    g<<setw(8)<<"Nk";
    g<<setw(w)<<"racd";
    g<<setw(w)<<"rscd";
    g<<setw(w)<<"rscdplusd";
    g<<setw(w)<<"pk";
    g<<setw(w)<<"qk";
    g<<setw(w)<<"delta";
    g<<setw(w)<<"s_osszeg"<<endl;
    rendszermeret=0;

    for(int i=0;i<szintszam;i++)
    {
        if(i == szintszam-1){
            g<<setw(5)<<"TERM";
        }
        else{
            g<<setw(5)<<i;
        }

        g<<setw(8)<<szintek[i].Nk;
        g<<setw(w)<<szintek[i].racd;
        g<<setw(w)<<szintek[i].rscd;
        g<<setw(w)<<szintek[i].rscdplusd;
        g<<setw(w)<<szintek[i].pk;
        g<<setw(w)<<szintek[i].qk;
        g<<setw(w)<<szintek[i].delta;
        g<<setw(w)<<sosszeg<<endl;
        rendszermeret+=x[i-1].size();
        insrendszmeret+=x[i-1].size();

    }
    g<<endl;
    g<<setw(w)<<"s_scd, s_acd, s_scdd: "<<s_scd<<","<<s_acd<<","<<s_scdd<<endl;
    g<<setw(w)<<"Beta: "<<B<<endl;
    g<<setw(w)<<"Tranziens idő (elméleti): "<<tranziens_ido<<endl;
    g<<setw(w)<<"Tranziens idő (mért): "<<mert_tranziensido<<endl;
    g<<setw(w)<<"Rátasumma: "<<ratasumma<<endl;
    g<<setw(w)<<"Rendszerméret: "<<rendszermeret<<endl;
    g.precision(17);
    g<<"Random_seed: "<<seed<<endl;
    g.precision(6);
    g<<endl<<"A szimuláció alatt legyártott sejtek száma: "<<legyartott_sejtek<<endl;
    g<<endl<<"A szimuláció alatt differencialodott sejtek száma: "<<differencialt_sejtek<<endl;
    g<<endl<<"A szimulacio alatt eltelt ido: "<<eltelt_ido<<endl;
    g<<endl<<"D_n: "<<D_n<<endl;
    g<<endl<<"D_max_lin: "<<D_max_lineage<<endl;
    g<<endl<<"D_n_max: "<<D_n_max<<endl;
    g<<endl<<"esemenyek szama: "<<gen<<endl;

    for(int i=0; i<szintszam;i++)
    {
        g<<endl<<i<<". szint"<<endl;
        int sum=0;
        g<<"sejtek osztódási számai:"<<endl;
        for(unsigned int j=0; j<x[i].size();j++)
        {
                g<<x[i][j].oszt_szam<<" ";
                sum+=x[i][j].oszt_szam;
        }
        double atl=(double)sum/(double)(x[i].size());
        g<<endl<<"az átlagos osztódási szám: "<<atl<<endl;
        g<<"sejtek száma a szinten: ";
        g<<x[i].size()<<endl;
        g<<"ez "<<100*((double)x[i].size()/(double)szintek[i].Nk)<<"%-a a vártnak (Nk)"<<endl;

        sum=0;
        g<<"sejtek mutációs számai:"<<endl;
        for(unsigned int j=0; j<x[i].size();j++)
        {
                g<<x[i][j].mut_szam<<" ";
                sum+=x[i][j].mut_szam;


        }

        atl=(double)sum/(double)(x[i].size());
        g<<endl<<"az átlagos mutációs szám: "<<atl<<endl;

        sumnacd=0;
        g<<" acd driverek száma:"<<endl;
        for(unsigned int j=0; j<x[i].size();j++)
        {
                g<<x[i][j].n_acd<<" ";
                sumnacd+=x[i][j].n_acd;

        }

        double atlnacd=(double)sumnacd/(double)(x[i].size());
        g<<endl<<"az átlagos n_acd szám: "<<atlnacd<<endl;

        sumnscd=0;
        g<<" scd driverek száma:"<<endl;
        for(unsigned int j=0; j<x[i].size();j++)
        {
                g<<x[i][j].n_scd<<" ";
                sumnscd+=x[i][j].n_scd;

        }

        double atlnscd=(double)sumnscd/(double)(x[i].size());
        g<<endl<<"az átlagos n_scd szám: "<<atlnscd<<endl;

        sumnscdplusd=0;

        g<<" scdplusd driverek száma:"<<endl;
        for(unsigned int j=0; j<x[i].size();j++)
        {
                g<<x[i][j].n_scdplusd<<" ";
                sumnscdplusd+=x[i][j].n_scdplusd;

        }

        double atlnscdplusd=(double)sumnscdplusd/(double)(x[i].size());
        g<<endl<<"az átlagos n_scdplusd szám: "<<atlnscdplusd<<endl;
    }



vector<int> szintcounter;

for(int j=0; j<maxMut+1;++j){
	mutans_Kapcsolo[j] = 0;
}

for(int j=0; j<maxMut+1;++j){
	mutans_Kapcsolo2[j] = 0;
}


sss.str().clear();
//atlOszt.close();
//sssss.str().clear();
//incidencia.close();
linTree.close();
//g.close();
//sz.close();
//id.close();
//z.close();

} //instances


p<<"D_n: "<<D_n_sum/(double)instanciak<<endl;
p<<"D_n_szoras: "<<sqrt((D_n_negyzet/(double)instanciak)-pow(D_n_sum/(double)instanciak,2))<<endl;
p<<"Kihalas: "<<kihalas/(double)instanciak<<endl;
p<<"ossejt acd esemenyek: "<<stem_acd_counter/(double)instanciak<<endl;
p<<"ossejt scd esemenyek: "<<stem_scd_counter/(double)instanciak<<endl;
p<<"ossejt scdd esemenyek: "<<stem_scdd_counter/(double)instanciak<<endl;
p<<"legyartando adtlag: "<<legyartott_sejtek/(double)instanciak<<endl;
p<<"ossejt mutszam: "<<ossejt_kritmut_szam/(double)instanciak<<endl;
p<<"Nrak: "<<Nrak/(double)instanciak<<endl;
p<<endl;
p<<setw(8)<<"Az adott számú mutációval rendelkező mutánsok előfordulási valószínűsége (Instanciakken max 1...): "<<endl;

for(int i=1; i<maxMut; ++i){
    if(talaltam_Mutanst[i]>0){
        p<<setw(8)<<i<<"mut_instanc: "<<(talaltam_Mutanst[i]/(double)instanciak)<<endl;
        p<<setw(8)<<i<<"mutans: "<<talaltam_Mutanst[i]<<endl;
    }

}
cout<<endl<<endl;
for(int i=1; i<maxMut; ++i){
    if(talaltam_Mutanst2[i]>0){
        p<<setw(8)<<i<<"mut_instanc2: "<<(talaltam_Mutanst2[i]/(double)instanciak)<<endl;
        p<<setw(8)<<i<<"mutans2: "<<talaltam_Mutanst2[i]<<endl;
    }

}
cout<<endl<<endl;

p<<setw(8)<<"Az adott számú mutációval rendelkező mutánsok előfordulási valószínűsége (Instanciakken max 1...): "<<endl;

for(int i=1; i<maxMut; ++i){
    p<<setw(8)<<"P_(mu,"<<i<<"): "<<(P_muem[i]/(double)instanciak)<<endl;
}
p.close();





return 0;
}




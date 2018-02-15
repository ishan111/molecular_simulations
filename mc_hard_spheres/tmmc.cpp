/* tmmc.cpp
*  Created on: 19-Nov-2017
*  Author: ishan
*/
#include "tmmc.h"


using std::vector;
using namespace std;


ofstream tmmcHist_data;
ofstream tmmcHist_dataC;
ofstream tmmcHist_dataN;

void tmmc_update(double accProb,bool inc,bool UpdateNorm){
	double accProbExp=accProb;
	if (inc){
		if( Nmax<N+1){
			Nmax=N+1;
			tmmcC.push_back({(double) Nmax,0,0,0});
			tmmcN.push_back({(double) Nmax,0,0,0});
		}
		if (sampleNo> tmmcCupstart){
			accProbExp = exp(accProb);
			accProbExp = accProbExp<1?accProbExp:1;
			tmmcC[N][1] = tmmcC[N][1] + accProbExp ;
			tmmcC[N][2] = tmmcC[N][2] + 1  ;
		}
	}
	else {//removal
		if (sampleNo>tmmcCupstart){
			accProbExp = exp(accProb);
			accProbExp = accProbExp<1?accProbExp:1;
			tmmcC[N][3] = tmmcC[N][3] + accProbExp ;
			tmmcC[N][2] = tmmcC[N][2] + 1  ;
		}
	}
	if (sampleNo>tmmcNupstart){
		for (int i=0;i<=Nmax;i+=1){
			//tmmcRsum = tmmcC[i][0]+tmmcC[i][1]+tmmcC[i][2];
			if (tmmcC[i][2]!=0){
				tmmcN[i][1]=tmmcC[i][1]/tmmcC[i][2];
//				tmmcN[i][2]=tmmcC[i][2]/tmmcC[i][2];
				tmmcN[i][3]=tmmcC[i][3]/tmmcC[i][2];
			}
		}


	}
}

double tmmc_bias(bool inc){
	double bias = 0;
	if(inc){

		if (N+1 <= Nmax && tmmcN[N][1] > 0 && tmmcN[N+1][3] > 0 ) {
			bias = log(tmmcN[N+1][3])-log(tmmcN[N][1]);
		}
	}
	else{
		if (N!=0 && tmmcN[N][3]>0  && tmmcN[N-1][1]>0 ){
			bias = log(tmmcN[N-1][1])-log(tmmcN[N][3]);
		}

	}
	return bias ;
}

void tmmc_hist(){
	tmmcHist_data.open("tmmc.dat");
	tmmcHist_dataC.open("tmmcC.dat");
	tmmcHist_dataN.open("tmmcN.dat");
	tmmcHist_dataC<<Nmax<<endl;
	//tmmcHist.push_back({tmmcC[0][0],0});
	for(int i=0;i<=Nmax;i+=1){

		tmmcHist_dataC<<tmmcC[i][0]<<" "<<tmmcC[i][1]<<" "<<tmmcC[i][2]<<" "<<tmmcC[i][3]<<endl;
		tmmcHist_dataN<<tmmcN[i][0]<<" "<<tmmcN[i][1]<<" "<<tmmcN[i][2]<<" "<<tmmcN[i][3]<<endl;

		if (i>0) {
			if (tmmcN[i-1][1]>0 && tmmcN[i][3]>0 ) {

				tmmcHist.push_back({tmmcN[i][0],log(tmmcN[i-1][1]/tmmcN[i][3])});
			}
			else{
				tmmcHist.push_back({tmmcN[i][0],0});


			}
			tmmcHist[i][1]=tmmcHist[i][1]+tmmcHist[i-1][1];

		}


		tmmcHist_data<<tmmcHist[i][0]<<" "<<tmmcHist[i][1]<<endl;





	}
	tmmcHist_data.close();
	tmmcHist_dataN.close();
	tmmcHist_dataC.close();
}

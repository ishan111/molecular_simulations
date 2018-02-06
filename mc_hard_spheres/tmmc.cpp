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
			tmmcC.push_back({0,0,0});
			tmmcN.push_back({0,0,0});
		}
		if (sampleNo> tmmcCupstart){
			accProbExp = exp(accProb);
			accProbExp = accProbExp<1?accProbExp:1;
			tmmcC[N][0] = tmmcC[N][0] + accProbExp ;
			tmmcC[N][1] = tmmcC[N][1] + 1 - accProbExp ;
		}
	}
	else {//removal
		if (sampleNo>tmmcCupstart){
			accProbExp = exp(accProb);
			accProbExp = accProbExp<1?accProbExp:1;
			tmmcC[N][2] = tmmcC[N][2] + accProbExp ;
			tmmcC[N][1] = tmmcC[N][1] + 1 - accProbExp ;
		}
	}
	if (sampleNo>tmmcNupstart){
		for (int i=0;i<=Nmax;i+=1){
			tmmcRsum = tmmcC[i][0]+tmmcC[i][1]+tmmcC[i][2];
			if (tmmcRsum!=0){
				tmmcN[i][0]=tmmcC[i][0]/tmmcRsum;
				tmmcN[i][1]=tmmcC[i][1]/tmmcRsum;
				tmmcN[i][2]=tmmcC[i][2]/tmmcRsum;
			}
		}


	}
}

double tmmc_bias(bool inc){
	double bias = 0;
	if(inc){

		if (N+1 <= Nmax ) {
			bias = (tmmcN[N][0] > 0 && log(tmmcN[N+1][2] > 0 )? (log(tmmcN[N+1][2])-log(tmmcN[N][0])):0);
		}
}
	else{
		if (N!=0){
			bias = (tmmcN[N][2]>0  && log(tmmcN[N-1][0]>0 )? (log(tmmcN[N-1][0])-log(tmmcN[N][2])):0);
}
	}
	return bias ;
}

void tmmc_hist(){
	tmmcHist_data.open("tmmc.dat");
	tmmcHist_dataC.open("tmmcC.dat");
	tmmcHist_dataN.open("tmmcN.dat");

	for(int i=1;i<=Nmax;i+=1){
		if (tmmcN[i][0]>0 && tmmcN[i+1][2]>0){
			tmmcHist.push_back({log(tmmcN[i-1][0])-log(tmmcN[i][2])});
		}
		else{
			tmmcHist.push_back({0});
		}
		tmmcHist[i]=tmmcHist[i]+tmmcHist[i-1];
		tmmcHist_data<<tmmcHist[i]<<endl;
		tmmcHist_dataN<<tmmcN[i][0]<<" "<<tmmcN[i][1]<<" "<<tmmcN[i][2]<<endl;
		tmmcHist_dataC<<tmmcC[i][0]<<" "<<tmmcC[i][1]<<" "<<tmmcC[i][2]<<endl;

	}
	tmmcHist_data.close();
	tmmcHist_dataN.close();
	tmmcHist_dataC.close();
}

/*
 * tmmc.cpp
 *
 *  Created on: 19-Nov-2017
 *      Author: ishan
 */
#include "tmmc.h"
#include "common_params.h"
#include <iostream>
#include <vector>

using std::vector;
using namespace std;


ofstream tmmcHist_data;

void tmmc_update(double accProb,bool inc,bool UpdateNorm){
	if (inc){
		if( Nmax<N+1){
			Nmax=N;
			tmmcC.push_back({0,0,0});
			tmmcN.push_back({0,0,0});
		}
		tmmcC[N][0] = tmmcC[N][0] + accProb ;
		tmmcC[N][1] = tmmcC[N][1] + 1 - accProb ;
	}
	else {
		tmmcC[N][2] = tmmcC[N][2] + accProb ;
		tmmcC[N][1] = tmmcC[N][1] + 1 - accProb ;
	}
	if (UpdateNorm){
         for (int i=0;i<=Nmax;i+=1){
        	 tmmcRsum = tmmcC[i][0]+tmmcC[i][1]+tmmcC[i][2];
             tmmcN[i][0]=tmmcC[i][0]/tmmcRsum;
             tmmcN[i][1]=tmmcC[i][1]/tmmcRsum;
             tmmcN[i][2]=tmmcC[i][2]/tmmcRsum;
         	 }


	}
}
double tmmc_bias(bool inc){
	double bias;
	if(inc){
		bias = tmmcN[N][0]==0? tmmcN[N+1][2]/tmmcN[N][0]:1;

	}
	else{
		bias = tmmcN[N][2]? tmmcN[N-1][0]/tmmcN[N][2]:1;
	}
	return bias ;
}

void tmmc_hist(){
  tmmcHist_data.open("tmmc.dat");
	for(int i=0;i<tmmcN.size()-1;i+=1){
		tmmcHist.push_back(tmmcN[i+1][0]?tmmcN[i+1][2]/tmmcN[i][0]:1);
		if(i>0){
			tmmcHist[i]=tmmcHist[i]*tmmcHist[i-1];
		}
		tmmcHist_data<<tmmcHist[i]<<endl;

	}
	tmmcHist_data.close();
}

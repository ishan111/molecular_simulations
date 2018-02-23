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

void tmmc_update(double accProb){
	if (sampleNo> tmmcCupstart && transition != 0){
		double accProbExp=accProb;

		/*if( Nmax<N+1){
		Nmax=N+1;
		tmmcC.push_back({(double) Nmax,0,0,0});
		tmmcN.push_back({(double) Nmax,0,0,0});
	}*/

	accProbExp = exp(accProb);
	accProbExp = accProbExp<1?accProbExp:1;
	tmmcC[Ninit[1]][Ninit[2]][transition] = tmmcC[Ninit[1]][Ninit[2]][transition] + accProbExp ;
	tmmcC[Ninit[1]][Ninit[2]][8] = tmmcC[Ninit[1]][Ninit[2]][8] + 1  ;




	if (sampleNo>tmmcNupstart && sampleNo % samp_ival == 0){
		for (int i=0;i<=Nmax[0];i+=1){
			for (int j=0;j<=Nmax[1];j+=1){
				//tmmcRsum = tmmcC[i][0]+tmmcC[i][1]+tmmcC[i][2];
				if (tmmcC[i][j][8]!=0){
					for(int k=2;k<=7;k+=1){
						tmmcN[i][k]=tmmcC[i][k]/tmmcC[i][8];
						//			tmmcN[i][2]=tmmcC[i][2]/tmmcC[i][2];
						//tmmcN[i][3]=tmmcC[i][3]/tmmcC[i][2];
					}
				}
			}
		}
	}


}
}

double tmmc_bias(){
	double bias = 0;



	if(tmmcN[Nfin[1]][Nfin[2]][revTransition] > 0 && tmmcN[Ninit[1]][Ninit[2]][transition] > 0 ) {
		bias = log(tmmcN[Nfin[1]][Nfin[2]][revTransition])-log(tmmcN[Ninit[1]][Ninit[2]][transition]);
		//bias = -bias ;
	}



	return bias ;
}

void tmmc_hist(){
	tmmcHist_data.open("tmmc.dat");
	tmmcHist_dataC.open("tmmcC.dat");
	tmmcHist_dataN.open("tmmcN.dat");
	tmmcHist_dataC<<Nmax<<endl;
	//tmmcHist.push_back({tmmcC[0][0],0});
	for(int i=0;i<=Nmax[0];i+=1){
		for(int j=0;j<=Nmax[0];j+=1){
			for (k=0;k<=8;k+=1){
				tmmcHist_dataC<<tmmcC[i][j][k]<<" " ;
				tmmcHist_dataN<<tmmcN[i][j][k]<<" " ;
				if (k==8){
					tmmcHist_dataC << endl ;
					tmmcHist_dataN << endl ;
				}
			}
		}
	}

	for(int j=0;j<=Nmax[1];j+=1){
		for(int i=0;i<=Nmax[0];i+=1){

			if (j>0) {
				if (tmmcN[i][j-1][4]>0 && tmmcN[i][j][5]>0 ) {

					tmmcHist.push_back({tmmcN[i][j][0],tmmcN[i][j][1],log(tmmcN[i][j-1][4]/tmmcN[i][j][5])});
				}
				else{
					tmmcHist.push_back({tmmcN[i][j][0],tmmcN[i][j][1],0});


				}
				tmmcHist[i][j][2]=tmmcHist[i][j][2]+tmmcHist[i][j-1][2];

			}
			else {
				if (i>0) {
					if (tmmcN[i-1][j][2]>0 && tmmcN[i][j][3]>0 ) {

						tmmcHist.push_back({tmmcN[i][j][0],tmmcN[i][j][1],log(tmmcN[i-1][j][2]/tmmcN[i][j][3])});
					}
					else{
						tmmcHist.push_back({tmmcN[i][j][0],tmmcN[i][j][1],0});


					}
					tmmcHist[i][j][2]=tmmcHist[i][j][2]+tmmcHist[i-1][j][2];

				}

			}


			tmmcHist_data<<tmmcHist[i][j][0]<<" "<<tmmcHist[i][j][1]<<" "<<tmmcHist[i][j][2]<<endl;



		}

	}
	tmmcHist_data.close();
	tmmcHist_dataN.close();
	tmmcHist_dataC.close();
}

bool is_in_bin(int binNo, vector<double> particle){
	bool is_in_bin = 0;
	if	(particle[0]>bin_dimes[binNo][0][0] && particle[1]>bin_dimes[binNo][0][1] && particle[2]>bin_dimes[binNo][0][2] && particle[0]<bin_dimes[binNo][1][0] &&...
		particle[1]<bin_dimes[binNo][1][1] && particle[2]<bin_dimes[binNo][1][2] ){
			is_in_bin = 1 ;
		}
		return is_in_bin ;
	}

	bool updateNbin( vector<double> particle_old_pos,vector<double> particle_new_pos, bool inc){




		if (is_in_bin(0,particle_old_pos) == 1){
			if (is_in_bin(0,particle_new_pos) == 0){
				Nfin[0] = Ninit[0] - 1;

			}
			else {
				Nfin[0] = Ninit[0] ;
			}
		}
		else {
			if (is_in_bin(0,particle_new_pos) == 0){
				Nfin[0] = Ninit[0];

			}
			else {
				Nfin[0] = Ninit[0] + 1 ;
			}

		}

		if (is_in_bin(1,particle_old_pos) == 1){
			if (is_in_bin(1,particle_new_pos) == 0){
				Nfin[1] = Ninit[1] - 1;

			}
			else {
				Nfin[1] = Ninit[1] ;
			}
		}
		else {
			if (is_in_bin(1,particle_new_pos) == 0){
				Nfin[1] = Ninit[1];

			}
			else {
				Nfin[1] = Ninit[1] + 1 ;
			}

		}
		trans_sel();
	}

	void trans_sel(){
		//int transition ;
		if (Nfin[0]-Ninit[0] == 0 && Nfin[1]-Ninit[1] == 0){
			transition = 0 ;
			revTransition = 0;
		}
		else if (Nfin[0]-Ninit[0] == 1 && Nfin[1]-Ninit[1] == 0){
			transition = 2; revTransition = 3 ;
		}
		else if (Nfin[0]-Ninit[0] == -1 && Nfin[1]-Ninit[1] == 0){
			transition = 3; revTransition = 2 ;
		}
		else if (Nfin[0]-Ninit[0] == 0 && Nfin[1]-Ninit[1] == 1){
			transition = 4; revTransition = 5 ;
		}
		else if (Nfin[0]-Ninit[0] == 0 && Nfin[1]-Ninit[1] == -1){
			transition = 5; revTransition = 4 ;
		}
		else if (Nfin[0]-Ninit[0] == 1 && Nfin[1]-Ninit[1] == -1){
			transition = 6; revTransition = 7 ;
		}
		else if (Nfin[0]-Ninit[1] == -1 && Nfin[1]-Ninit[2] == 1){
			transition = 7; revTransition = 6 ;
		}
	}

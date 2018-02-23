#include "state.h"

void save(){
    ofstream state_file;
    state_file.open("particles.state");
    state_file << N << endl;
    for(vector<vector<double> >::iterator it = particles.begin(); it < particles.end(); it++){
        state_file << (*it)[0] << " " << (*it)[1] << " " << (*it)[2] << endl;
    }
    state_file.close();
}

void collect(){
    ifstream state_file;
    //if tmmc read in ON
    ifstream tmmcC_file;
    state_file.open("particles.state");

    if (read_tm_from_file == true){
      tmmcC_file.open("tmmcC.dat");
    }

    state_file >> N;
    cout << "Reading in " << N << " particles from state file." << endl;
    for(int i = 0; i < N; i++){
      vector<double> newp(3);
      state_file >> newp[0] >> newp[1] >> newp[2];
      particles.push_back(newp);

// N bin Initialize
      if(newp[0]>bin_dimes[0][0][0] && newp[0]<bin_dimes[0][1][0] &&
        newp[1]>bin_dimes[0][0][1] && newp[1]<bin_dimes[0][1][1] &&
        newp[2]>bin_dimes[0][0][2] && newp[0]<bin_dimes[0][1][2]){

          Ninit[0]=Ninit[0]+1;


        }else if (newp[0]>bin_dimes[1][0][0] && newp[0]<bin_dimes[1][1][0] &&
          newp[1]>bin_dimes[1][0][1] && newp[1]<bin_dimes[1][1][1] &&
          newp[2]>bin_dimes[1][0][2] && newp[0]<bin_dimes[1][1][2]){

            Ninit[1]=Ninit[1]+1;

          }

        }

    cout << "Finished reading. Updated particle list with " << particles.size() << " particles." << endl;


  //tm initialize maybe

  /*tmmcN.reserve(Nmax[0]+1);
  tmmcC.reserve(Nmax[0]+1);
  tmmcHist.reserve(Nmax[0]+1);
  for (int i=0;i<=Nmax[0];i+=1){
    tmmcN[i].reserve(Nmax[1]+1);
    tmmcC[i].reserve(Nmax[1]+1);
    tmmcHist[i].reserve(Nmax[1]+1);
    for (int j=0;j<=Nmax[1];j+=1){
      tmmcN[i][j].reserve(9);
      tmmcC[i][j].reserve(9);
      tmmcHist[i][j].reserve(3);
    }
  }*/




    state_file.close();

    if (read_tm_from_file == true){
      tmmcC_file.close();
    }
}

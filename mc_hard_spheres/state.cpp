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
    }
    cout << "Finished reading. Updated particle list with " << particles.size() << " particles." << endl;
    Nmax = N ;
    if(read_tm_from_file == true){

    }
    if (read_tm_from_file == false){
    for(int i=1;i<=Nmax;i++){
      tmmcN.push_back({(double) i,0,0,0});
      tmmcC.push_back({(double) i,0,0,0});
    }
  }
  else{
    tmmcC_file >> Nmax ;

    for(int i = 0; i<=Nmax; i++){
      vector<double> tmRow(4);
    /*  if (i==0) {
        tmmcC_file >> tmRow[0] >> tmRow[1] >> tmRow[2] >> tmRow[3];
        tmmcC[0][0]=tmRow[0];
        tmmcC[0][1]=tmRow[1];
        tmmcC[0][0]=tmRow[0];
        tmmcC[0][0]=tmRow[0];
      //  tmmcN.push_back({(double) i,0,0,0});
      }
      else*/
        tmmcC_file >> tmRow[0] >> tmRow[1] >> tmRow[2] >> tmRow[3];
      if (i>0) {

        tmmcC.push_back(tmRow);
        tmmcN.push_back({(double) i,0,0,0});
      }


    //  tmmcC.push_back({(double) i,0,0,0});

    }
  }
    state_file.close();

    if (read_tm_from_file == true){
      tmmcC_file.close();
    }
}

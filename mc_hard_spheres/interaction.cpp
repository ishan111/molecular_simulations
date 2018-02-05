#include "interaction.h"
#include<iostream>
using namespace std;


//distance and overlap checking
vector<double> dist(vector<double> newp, vector<double> p){
  vector<double> dist ;
  if (truncDist<bfactor/2){
    double deltax = abs(newp[0] - p[0]);
    double deltay = abs(newp[1] - p[1]);
    double deltaz = abs(newp[2] - p[2]);
    dist.push_back(pow(pow(min(deltax, L-deltax),2) + pow(min(deltay, L-deltay),2) + pow(min(deltaz, L-deltaz),2),0.5));
  }
  else {

    int noCopies = floor(truncDist/bfactor);
    for(int i=-noCopies;i<=noCopies;i++){
      for (int j=-noCopies;j<=noCopies;j++){
        for (int k=-noCopies;k<=noCopies;k++){

          double deltax = abs(i*bfactor+newp[0] - p[0]);
          double deltay = abs(j*bfactor+newp[1] - p[1]);
          double deltaz = abs(k*bfactor+newp[2] - p[2]);
          dist.push_back(pow(pow(deltax,2) + pow(deltay,2) + pow(deltaz,2),0.5));


        }
      }
    }
  }

  return dist;

}

double partE(vector<double> newp, vector<double> p){
  vector<double>  pDist = dist(newp, p) ;
  double pEnergy = 0;
  for(vector<double>::iterator itp = pDist.begin(); itp != pDist.end(); itp++){
    if (*itp<truncDist) {
      pEnergy =  pEnergy + 4*(epsilon)*(pow((sigma/(*itp)),12) - pow((sigma/(*itp)),6)) ;
    }

  }
  return pEnergy;
}

//hard sphere model - returns 0 if no overlaps, 1 if there is an overlap
//uses cell list for efficient calculations
double energy_hard_displace(vector<double> newp, int p){
  vector<double> part = particles[p];


  double pEnergy = 0;


  for(vector<vector<double>>::iterator itp = particles.begin(); itp != particles.end(); itp++){
    if(*itp != part ){

      pEnergy = pEnergy + partE(newp, *itp);

    }
  }

  for(vector<vector<double>> ::iterator itp = particles.begin(); itp != particles.end(); itp++){
    if(*itp != part){

      pEnergy = pEnergy -  partE(part, *itp);
    }
  }
  return pEnergy;
}

double energy_hard_insert(vector<double> newp){

  double pEnergy = 0;

  for(vector<vector<double>> ::iterator itp = particles.begin(); itp != particles.end(); itp++){

    pEnergy = pEnergy + partE(newp, *itp);

  }


  return pEnergy;
}


double energy_hard_remove(int p){
  vector<double> part = particles[p];



  double pEnergy = 0;

  for(vector<vector<double>> ::iterator itp = particles.begin(); itp != particles.end(); itp++){
    if(*itp != part){

      pEnergy = pEnergy -  partE(part, *itp);

    }
  }


  return pEnergy;

}

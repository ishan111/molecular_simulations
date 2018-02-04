#include "interaction.h"
#include<iostream>
using namespace std;


//distance and overlap checking
double dist(vector<double> newp, vector<double> p){
  double deltax = abs(newp[0] - p[0]);
  double deltay = abs(newp[1] - p[1]);
  double deltaz = abs(newp[2] - p[2]);
  return pow(pow(min(deltax, L-deltax),2) + pow(min(deltay, L-deltay),2) + pow(min(deltaz, L-deltaz),2),0.5);
}

double partE(vector<double> newp, vector<double> p){
  double  pDist = dist(newp, p) ;
  double pEnergy =  4*(epsilon)*(pow((sigma/pDist),12) - pow((sigma/pDist),6)) ;
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

#include "interaction.h"
#include<iostream>
using namespace std;

//cell list - bookkeeping
void make_cell_list(){
  cell_list_div = L/ncells;
  cell_list.assign(ncells*ncells*ncells + 1, list<vector<double> >());

  //neccessary when resuming a simulation from a previous output
  for(vector<vector<double> >::iterator ipart = particles.begin(); ipart < particles.end(); ipart++){
    vector<double> part = *ipart;
    vector<int> bc = {(int) (part[0]/cell_list_div), (int) (part[1]/cell_list_div), (int) (part[2]/cell_list_div)};
    int bx = map_box(bc);
    cell_list[bx].push_back(part);
  }
}

int map_box(vector<int> bc){ //bc = box coordinates
  return bc[0]*ncells*ncells + bc[1]*ncells + bc[2];
}

void cell_list_insert(vector<double> part){
  vector<int> bc = {(int) (part[0]/cell_list_div), (int) (part[1]/cell_list_div), (int) (part[2]/cell_list_div)};
  int bx = map_box(bc);
  cell_list[bx].push_back(part);
}

void cell_list_remove(vector<double> part){
  vector<int> bc = {(int) (part[0]/cell_list_div), (int) (part[1]/cell_list_div), (int) (part[2]/cell_list_div)};
  int bx = map_box(bc);
  cell_list[bx].remove(part);
}

//distance and overlap checking
double dist(vector<double> newp, vector<double> p){
  double deltax = abs(newp[0] - p[0]);
  double deltay = abs(newp[1] - p[1]);
  double deltaz = abs(newp[2] - p[2]);
  return pow(pow(min(deltax, L-deltax),2) + pow(min(deltay, L-deltay),2) + pow(min(deltaz, L-deltaz),2),0.5);
}

double partE(vector<double> newp, vector<double> p){
  double  pDist = dist(newp, p) ;
  double pEnergy =  4*(epsilon)*(((sigma/pDist)^12) - ((sigma/pDist)^12))
  return pEnergy;
}

//hard sphere model - returns 0 if no overlaps, 1 if there is an overlap
//uses cell list for efficient calculations
double energy_hard_displace(vector<double> newp, int p){
  vector<double> part = particles[p];
  vector<int> bc = {(int) (newp[0]/cell_list_div), (int) (newp[1]/cell_list_div), (int) (newp[2]/cell_list_div)};
  int bx = map_box(bc);

  //which boxes to check in
  vector<int> boxes = {};
  vector<int> delta_neigh = {-1,0,1};

  for(vector<int>::iterator a = delta_neigh.begin(); a < delta_neigh.end(); a++){
    for(vector<int>::iterator b = delta_neigh.begin(); b < delta_neigh.end(); b++){
      for(vector<int>::iterator c = delta_neigh.begin(); c < delta_neigh.end(); c++){
        vector<int> neigh = {((bc[0] + *a) % ncells + ncells) % ncells,
          ((bc[1] + *b) % ncells + ncells) % ncells,
          ((bc[2] + *c) % ncells + ncells) % ncells};
          boxes.push_back(map_box(neigh));
        }
      }
    }

    double pEnergy = 0;

    for(vector<int>::iterator it = boxes.begin(); it < boxes.end(); it++){
      for(list<vector<double> >::iterator itp = cell_list[*it].begin(); itp != cell_list[*it].end(); itp++){
        if(*itp != part){

          pEnergy = pEnergy + partE(newp, *itp);

        }
      }
    }

    bc = {(int) (part[0]/cell_list_div), (int) (part[1]/cell_list_div), (int) (part[2]/cell_list_div)};
    bx = map_box(bc);



    for(vector<int>::iterator a = delta_neigh.begin(); a < delta_neigh.end(); a++){
      for(vector<int>::iterator b = delta_neigh.begin(); b < delta_neigh.end(); b++){
        for(vector<int>::iterator c = delta_neigh.begin(); c < delta_neigh.end(); c++){
          vector<int> neigh = {((bc[0] + *a) % ncells + ncells) % ncells,
            ((bc[1] + *b) % ncells + ncells) % ncells,
            ((bc[2] + *c) % ncells + ncells) % ncells};
            boxes.push_back(map_box(neigh));
          }
        }
      }
      for(vector<int>::iterator it = boxes.begin(); it < boxes.end(); it++){
        for(list<vector<double> >::iterator itp = cell_list[*it].begin(); itp != cell_list[*it].end(); itp++){
          if(*itp != part){

            pEnergy = pEnergy -  partE(part, *itp);

          }
        }
      }

      return pEnergy;
    }


    double energy_hard_insert(vector<double> newp){
      vector<int> bc = {(int) (newp[0]/cell_list_div), (int) (newp[1]/cell_list_div), (int) (newp[2]/cell_list_div)};
      int bx = map_box(bc);

      //which boxes to check in
      vector<int> boxes;
      vector<int> delta_neigh = {-1,0,1};

      for(vector<int>::iterator a = delta_neigh.begin(); a < delta_neigh.end(); a++){
        for(vector<int>::iterator b = delta_neigh.begin(); b < delta_neigh.end(); b++){
          for(vector<int>::iterator c = delta_neigh.begin(); c < delta_neigh.end(); c++){
            vector<int> neigh = {((bc[0] + *a) % ncells + ncells) % ncells,
              ((bc[0] + *b) % ncells + ncells) % ncells,
              ((bc[0] + *c) % ncells + ncells) % ncells};
              boxes.push_back(map_box(neigh));
            }
          }
        }

        double pEnergy = 0;

        for(vector<int>::iterator it = boxes.begin(); it < boxes.end(); it++){
          for(list<vector<double> >::iterator itp = cell_list[*it].begin(); itp != cell_list[*it].end(); itp++){

            pEnergy = pEnergy + partE(newp, *itp);

          }
        }

        return pEnergy;
      }


      int energy_hard_remove(int p){
        vector<double> part = particles[p];

        vector<int> bc = {(int) (part[0]/cell_list_div), (int) (part[1]/cell_list_div), (int) (part[2]/cell_list_div)};
        int bx = map_box(bc);

        //which boxes to check in
        vector<int> boxes = {};
        vector<int> delta_neigh = {-1,0,1};

        for(vector<int>::iterator a = delta_neigh.begin(); a < delta_neigh.end(); a++){
          for(vector<int>::iterator b = delta_neigh.begin(); b < delta_neigh.end(); b++){
            for(vector<int>::iterator c = delta_neigh.begin(); c < delta_neigh.end(); c++){
              vector<int> neigh = {((bc[0] + *a) % ncells + ncells) % ncells,
                ((bc[1] + *b) % ncells + ncells) % ncells,
                ((bc[2] + *c) % ncells + ncells) % ncells};
                boxes.push_back(map_box(neigh));
              }
            }
          }

          double pEnergy = 0;



          for(vector<int>::iterator it = boxes.begin(); it < boxes.end(); it++){
            for(list<vector<double> >::iterator itp = cell_list[*it].begin(); itp != cell_list[*it].end(); itp++){
              if(*itp != part){

                pEnergy = pEnergy -  partE(part, *itp);

              }
            }
          }

          return pEnergy;

        }

#ifndef INTERACTION
#define INTERACTION

#include "common_params.h"
#include <cmath>
#include <vector>
#include <list>

using namespace std;
//optimization: cell list

vector<double> dist(vector<double>,vector<double>);
double partE(vector<double>,vector<double>);
double energy_hard_displace(vector<double>,int);
double energy_hard_insert(vector<double>);
double energy_hard_remove(int);

#endif

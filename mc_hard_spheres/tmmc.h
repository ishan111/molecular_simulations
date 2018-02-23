/*
* tmmc.h
*
*  Created on: 19-Nov-2017
*      Author: ishan
*/

#ifndef TMMC_H_
#define TMMC_H_

#include <fstream>
#include "common_params.h"
#include <iostream>
#include <vector>
//#include <math>
void tmmc_update(double);

double tmmc_bias();

bool is_in_bin(int,vector<double>);
bool updateNbin( vector<double>,vector<double>);
void trans_sel();
void tmmc_hist();

#endif /* TMMC_H_ */

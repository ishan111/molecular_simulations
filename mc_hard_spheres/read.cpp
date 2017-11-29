#include "read.h"

void read(){
    int nparams = 19;
    string comment[nparams];
    string input[nparams];

    for(int i = 0; i < nparams; i++){
        getline(cin, comment[i]);
        getline(cin, input[i]);
    }

    potential_type = stoi(input[0]);
    sigma = stod(input[1]);
    bfactor = stod(input[2]);
    ncells = stoi(input[3]);
    periodic = (bool) stod(input[4]);
    ncycles = stoi(input[5]);
    samp_ival = stoi(input[6]);
    zz = stod(input[7]);
    exc_disp_ratio = stod(input[8]);
    delta = stod(input[9]);
    rmax_factor = stoi(input[10]);
    dr_factor = stoi(input[11]);
    logging = stoi(input[12]);
    read_from_file = (bool) stoi(input[13]);
    tmmcSamp = (bool) stoi(input[14]);
    tmmcBias = (bool) stoi(input[15]);
    tmmcCupstart = stoi(input[16]);
    tmmcNupstart = stoi(input[17]);
    tmmcBiasStart = stoi(input[18]);

    L = bfactor * sigma;
}

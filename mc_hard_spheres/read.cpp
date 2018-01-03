#include "read.h"

void read(){
    int nparams = 21;
    string comment[nparams];
    string input[nparams];

    for(int i = 0; i < nparams; i++){
        getline(cin, comment[i]);
        getline(cin, input[i]);
    }

    potential_type = stoi(input[0]);
    sigma = stod(input[1]);
    epsilon = stod(input[2])
    bfactor = stod(input[3]);
    ncells = stoi(input[4]);
    periodic = (bool) stod(input[5]);
    ncycles = stoi(input[6]);
    samp_ival = stoi(input[7]);
    zz = stod(input[8]);
    exc_disp_ratio = stod(input[9]);
    delta = stod(input[10]);
    rmax_factor = stoi(input[11]);
    dr_factor = stoi(input[12]);
    logging = stoi(input[13]);
    read_from_file = (bool) stoi(input[14]);
    tmmcSamp = (bool) stoi(input[15]);
    tmmcBias = (bool) stoi(input[16]);
    tmmcCupstart = stoi(input[17]);
    tmmcNupstart = stoi(input[18]);
    tmmcBiasStart = stoi(input[19]);
    T = stoi(input[20])

    L = bfactor * sigma;
}

#include "read.h"

void read(){
    int nparams = 39;
    string comment[nparams];
    string input[nparams];

    for(int i = 0; i < nparams; i++){
        getline(cin, comment[i]);
        getline(cin, input[i]);
    }

    potential_type = stoi(input[0]);
    sigma = stod(input[1]);
    epsilon = stod(input[2]);
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
    logging = (bool) stoi(input[13]);
    read_from_file = (bool) stoi(input[14]);
    tmmcSamp = (bool) stoi(input[15]);
    tmmcBias = (bool) stoi(input[16]);
    tmmcCupstart = stoi(input[17]);
    tmmcNupstart = stoi(input[18]);
    tmmcBiasStart = stoi(input[19]);
    T = stod(input[20]);
    truncDist = stod(input[21]);
    Nllim = stoi(input[22]);
    Nulim = stoi(input[23]);
    read_tm_from_file = (bool) stoi(input[24]);
    bin_dimes[0][0][0]=stod(input[25]);
    bin_dimes[0][0][1]=stod(input[26]);
    bin_dimes[0][0][2]=stod(input[27]);
    bin_dimes[0][1][0]=stod(input[28]);
    bin_dimes[0][1][1]=stod(input[29]);
    bin_dimes[0][1][2]=stod(input[30]);
    bin_dimes[1][0][0]=stod(input[31]);
    bin_dimes[1][0][1]=stod(input[32]);
    bin_dimes[1][0][2]=stod(input[33]);
    bin_dimes[1][1][0]=stod(input[34]);
    bin_dimes[1][1][1]=stod(input[35]);
    bin_dimes[1][1][2]=stod(input[36]);
    Nmax[0]=stoi(input[37]);
    Nmax[1]=stoi(input[38]);

    

    L = bfactor * sigma;
}

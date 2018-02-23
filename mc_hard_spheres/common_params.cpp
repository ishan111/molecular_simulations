#include "common_params.h"

//potential type
int potential_type = 0;

//For random number generation
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> zero_one(0,nextafter(1, std::numeric_limits<double>::max()));

double ranf(){
    return zero_one(gen);
}

//Common simulation parameters
double sigma = 0;
double epsilon = 0;
double truncDist = 4 ;
double bfactor = 0;
double L = 0;
int N = 0;
int Nulim=0;
int Nllim=400;
bool periodic = true;
int ncycles = 0;
int samp_ival = 0;
double delta = 0;
double zz = 0.0115;
double T = 1.2;

//Optimization: Cell list
int ncells;
double cell_list_div;

double sampEnergy = 0 ;

//GCMC parameters
double exc_disp_ratio = 0.6; //ratio of exchanges to displacements

//Particles
vector<vector<double> > particles;

//Time
double start;

//Statistics
int att_disp;
int att_ins;
int att_del;
int succ_disp;
int succ_ins;
int succ_del;

//RDF computation
int rmax_factor;
int dr_factor;

//Logging
bool logging = 0;

//Resume from state
bool read_from_file = false;

//TMMC parameters
vector<vector<vector<double>>> tmmcC;//={{0,0,0,0,0,0,0,0,0}};
vector<vector<vector<double>>> tmmcN;//={{0,0,0,0,0,0,0,0,0}};
vector<int> Nmax={0 0};
double tmmcRsum = 0 ;
double bias = 0;
bool inc = false ;
vector<vector<double>> tmmcHist;// = {{0,0,0}};

int tmmcCupstart = 15000;
int tmmcNupstart=29000;
int tmmcBiasStart=30000;
bool tmmcBias = true;
bool tmmcSamp = true;
bool read_tm_from_file = false;

//tmmc 2D stuff
vector<int> Ninit ={0,0} ;
vector<int> Nfin ={0,0} ;
//int N2 = 0;
//int Nmax=0;
//int N2max=0;
double[2][2][3] bin_dimes;
int transition = 0;
int revTransition = 0;



int biasStart;
//Loop counter
int sampleNo=0;

#ifndef COMMON_PARAMS
#define COMMON_PARAMS

#include<random>
#include<list>
using namespace std;

//potential
extern int potential_type;

//For random number generation
extern random_device rd;  //used to obtain seed
extern mt19937 gen; //mersenne_twister_engine
extern uniform_real_distribution<> zero_one; //uniform real distribution from [0,1]
double ranf();

//Common simulation parameters
extern double sigma; //particle diameter
extern double epsilon;
extern double truncDist;
extern double bfactor; //box scaling factor
extern double L; //box dimension
extern int N; //no of particles
extern int Nulim;//N upper limit
extern int Nllim;//N lower limit
extern bool periodic; //periodic boundary conditions, enabled by default
extern int ncycles;
extern int samp_ival; //interval for sampling averages
extern double delta;
extern double zz; //activity, exp(beta*mu)/lambda^3
extern double T ; // temperature


//Optimization: Cell list
extern int ncells; //number of cells per dimension (user-specified)
extern double cell_list_div; //size of a single cell list division along a dimension (calculated)


extern double sampEnergy ;

//GCMC parameters
extern double exc_disp_ratio;

//Particles
extern vector<vector<double> > particles;

//Time
extern double start;

//Statistics
extern int att_disp; //displacements attempted
extern int att_ins; //insertions attempted
extern int att_del; //deletions attempted
extern int succ_disp; //successful displacements
extern int succ_ins; //successful insertions
extern int succ_del; //successful deletions

//RDF plot parameters
extern int rmax_factor;
extern int dr_factor;

//Logging
extern bool logging; //off by default

//Resume from state
extern bool read_from_file;

//TMMC parameters
extern vector<vector<vector<double>>> tmmcC;
extern vector<vector<vector<double>>> tmmcN;
extern vector<vector<vector<double>>> tmmcHist;
extern vector<int> Nmax;
extern double tmmcRsum ;
extern bool inc ;

extern int tmmcCupstart;
extern int tmmcNupstart;
extern int tmmcBiasStart;
extern bool tmmcBias;
extern bool tmmcSamp;
extern bool read_tm_from_file;

//tmmc 2D stuff
extern vector<int> Ninit  ;
extern vector<int> Nfin  ;
//int N2 = 0;
//int Nmax=0;
//int N2max=0;
extern double bin_dimes[2][2][3];
extern int transition ;
extern int revTransition ;

extern int sampleNo;

#endif

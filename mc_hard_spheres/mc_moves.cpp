#include "mc_moves.h"


void hard_displace(){
    att_disp+=1;
    if(N == 0) return;

    int p = int(ranf() * N); //0 to N-1

    vector<double> newp = {particles[p][0] + (ranf()-0.5)*2*delta, particles[p][1] + (ranf()-0.5)*2*delta, particles[p][2] + (ranf()-0.5)*2*delta};
    newp = {fmod(newp[0] + L, L), fmod(newp[1] + L, L), fmod(newp[2] + L, L)}; //prevent overflow

    double e_new = energy_hard_displace(newp,p); //energy on displacing p to newp
    double arg = -e_new/T;
    if(log(rand())<=e_new){
        cell_list_remove(particles[p]);
        particles[p] = newp;
        cell_list_insert(particles[p]);

        succ_disp += 1;
        log_current_config(1);
    }
}

void hard_exchange(){
    bool bias ;
    if(ranf() > 0.5){ //insert
    	inc = true ;
      att_ins += 1;

      vector<double> newp = {ranf()*L, ranf()*L, ranf()*L};

      double e_new = energy_hard_insert(newp); //energy on inserting newp


      double arg = log(pow(L,3)) + log(zz) - log(N+1) - e_new/T ;
      double biasedArg ;
      double bias = 1 ;
      if (tmmcBias == true & sampleNo>tmmcBiasStart){
        bias = tmmc_bias(inc);
      }
      else{
        bias = 1;
      }
      if(tmmcSamp==true){
        tmmc_update(arg,inc,true);
      }

            biasedArg = log(bias) + arg ;
          /*  if(ranf() >= biasedArg){
                cout << "Rejected by rule: " << ranf() << " " << arg << endl;
            }*/
            if(log(ranf()) < biasedArg) { //acceptance condition
                particles.push_back(newp); N+=1;
                cell_list_insert(newp);

                succ_ins += 1;
                log_current_config(2);
            }

        inc = false ;

    }
    else{ //remove
        double biasedArg;
        double bias = 1;
        att_del += 1;
        if(N==0) return;
        int p = ceil(ranf() * N);
        double e_new = energy_hard_remove(p); //energy on inserting newp
        if (tmmcSamp==true & tmmcBias == true & sampleNo>tmmcBiasStart){
          bias = tmmc_bias(inc);
        }
        else{
          bias = 1;
        }
        double arg = log(N)-log(pow(L,3)) -log(zz)-e_new/T ;
        biasedArg = log(bias) + arg ;
        if (tmmcSamp==true){
          tmmc_update(arg,inc,true);
        }


        if(ranf() < biasedArg){ //acceptance condition

            cell_list_remove(particles[p]);
            particles.erase(particles.begin() + p); N-=1;

            succ_del += 1;
            log_current_config(3);
        }
    }
}

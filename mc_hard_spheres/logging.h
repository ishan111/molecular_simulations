#ifndef LOGGING
#define LOGGING

#define _USE_MATH_DEFINES

#include "common_params.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <time.h>
#include <cmath>
#include <map>


using namespace std;

void log_init();
void log_current_config(int);
void log_finalize();

#endif

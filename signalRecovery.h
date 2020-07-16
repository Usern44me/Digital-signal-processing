#ifndef RECOVERY
#define RECOVERY

#define _USE_MATH_DEFINES
 
#include <cmath>
#include <math.h>
#include <utility>
#include <vector>


double getFunctionValue(double Td, std::vector<double> discreteSignal, double t);

std::vector<std::pair<double,double>> signalRecovery(double Td, double T, std::vector<double> discreteSignal);

#endif
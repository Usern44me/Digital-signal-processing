#include "signalRecovery.h"

double getFunctionValue(double Td, std::vector<double> discreteSignal, double t) {
	double result = 0;
	for (int k = 0; k < discreteSignal.size(); k++)
	{
		result += discreteSignal[k] * sin(M_PI/Td * (t - (k + 1)*Td)) / (M_PI/Td * (t - (k + 1)*Td));
	}
	return result;
}

std::vector<std::pair<double,double>> signalRecovery(double Td, double T, std::vector<double> discreteSignal) {
	std::vector<std::pair<double,double>> result;
	for (double t = 0; t <= T; t += Td / 100)
	{
		result.push_back(std::make_pair(t, getFunctionValue(Td, discreteSignal, t)));
	}
	return result;
}
#include "sampling.h"

std::vector<double> sampling(double F, double coef) {
	std::vector<double> result;
	for (double t = 0; t <= 10 / F; t += 1/(coef * F))
	{
		result.push_back(sin(F*t + M_PI/6));
	}
	return result;
}
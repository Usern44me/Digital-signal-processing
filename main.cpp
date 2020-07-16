#include <iostream>
#include <conio.h>

#include "sampling.h"
#include "signalRecovery.h"

int main(int argc, char const *argv[])
{

	//sin(x + pi/6);
	double F = 0;
	std::cout << std::endl << "Input F: ";
	std::cin >> F;
	//3.1

	//3.1.1
	std::vector<double> sample1 = sampling(F, 1.5);
	std::cout << std::endl << std::endl << "RESULT OF SAMPLING (fd = 1,5F):" << std::endl << std::endl;
	int i = 0;
	for (std::vector<double>::iterator it = sample1.begin(); it != sample1.end(); ++it)
	{
		std::cout << "n = " << i << ":u[n] = " << *it << std::endl;
		i++;
	}

/*	std::vector<std::pair<double, double>> recovery1 = signalRecovery(1/(1.5*F), 10/F, sample1);
	std::cout << std::endl << std::endl << "RECOVERY:" << std::endl << std::endl;
	for (int i = 0; i < recovery1.size(); i++)
	{
		std::cout << "t=" << recovery1[i].first << "; u(t)=" << recovery1[i].second << "  ";
	}

	std::cout << std::endl << std::endl << "Press Enter to resume..." << std::endl << std::endl;*/
	getch();

	//3.1.2
	std::vector<double> sample2 = sampling(F, 1.75);
	std::cout << std::endl << std::endl << "RESULT OF SAMPLING (fd = 1,75F):" << std::endl << std::endl;
	i = 0;
	for (std::vector<double>::iterator it = sample2.begin(); it != sample2.end(); ++it)
	{
		std::cout << "n = " << i << ":u[n] = " << *it << std::endl;
		i++;
	}

	std::cout << std::endl << std::endl << "Press Enter to resume..." << std::endl << std::endl;
	getch();

	//3.1.3
	std::vector<double> sample3 = sampling(F, 2);
	std::cout << std::endl << std::endl << "RESULT OF SAMPLING (fd = 2F):" << std::endl << std::endl;
	i = 0;
	for (std::vector<double>::iterator it = sample3.begin(); it != sample3.end(); ++it)
	{
		std::cout << "n = " << i << ":u[n] = " << *it << std::endl;
		i++;
	}

	std::cout << std::endl << std::endl << "Press Enter to resume..." << std::endl << std::endl;
	getch();

	//3.1.4
	std::vector<double> sample4 = sampling(F, 3);
	std::cout << std::endl << std::endl << "RESULT OF SAMPLING (fd = 3F):" << std::endl << std::endl;
	i = 0;
	for (std::vector<double>::iterator it = sample4.begin(); it != sample4.end(); ++it)
	{
		std::cout << "n = " << i << ":u[n] = " << *it << std::endl;
		i++;
	}

	std::vector<std::pair<double, double>> recovery4 = signalRecovery(1/(3*F), 10/F, sample4);
	std::cout << std::endl << std::endl << "RECOVERY:" << std::endl << std::endl;
	for (int i = 0; i < recovery4.size(); i++)
	{
		std::cout << "t=" << recovery4[i].first << "; u(t)=" << recovery4[i].second << "  ";
	}

	std::cout << std::endl << std::endl << "Press Enter to resume..." << std::endl << std::endl;
	getch();

	//3.1.5
	std::vector<double> sample5 = sampling(F, 1000);
	std::cout << std::endl << std::endl << "RESULT OF SAMPLING (fd = 1000F):" << std::endl << std::endl;
	i = 0;
	for (std::vector<double>::iterator it = sample5.begin(); it != sample5.end(); ++it)
	{
		std::cout << "n = " << i << ":u[n] = " << *it << std::endl;
		i++;
	}
}
#define _USE_MATH_DEFINES
 
#include <cmath>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <complex.h>
#include <conio.h>

int main(int argc, char const *argv[])
{
	//2.1
	const std::complex<double> j(0, 1);
	double f = 20, Td = 0.001, T = 1/f;

	std::vector<double> u;
	for (double i = 0; i < T*3 + Td; i+= Td)
		u.push_back(sin(2*M_PI*f*i));

	double k = u.size();
	
	std::vector<std::vector<std::complex<double>>> F(k, std::vector<std::complex<double>>(k, std::complex<double>(0, 0)));
	for (int i = 0; i < k; i++)
		for (int n = 0; n < k; n++)
			F[i][n] = std::exp(j*2.0*M_PI*(double)n*(double)i/k);

	std::vector<std::vector<std::complex<double>>> Fh(k, std::vector<std::complex<double>>(k, std::complex<double>(0, 0)));
	for (int i = 0; i < k; i++)
		for (int n = 0; n < k; n++)
			Fh[i][n] = (F[n][i]).real() - (F[n][i]).imag()*j; 

	std::vector<std::complex<double>> U(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
	{
		std::complex<double> elem(0, 0);
		for (int n = 0; n < k; n++)
			elem += u[n] * Fh[n][i];
		U[i] = elem;
	}

	std::vector<std::complex<double>> u_recovered(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
	{
		std::complex<double> elem(0, 0);
		for (int n = 0; n < k; n++)
			elem += U[n] * F[n][i];
		u_recovered[i] = elem/k;
	}

	std::cout << std::endl << "u:" << std::endl;
	for (std::vector<double>::iterator i = u.begin(); i != u.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl << std::endl << "U:" << std::endl;
	for (std::vector<std::complex<double>>::iterator i = U.begin(); i != U.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl << std::endl << "u recovered:" << std::endl;
	for (std::vector<std::complex<double>>::iterator i = u_recovered.begin(); i != u_recovered.end(); ++i)
		std::cout << (*i).real() << " ";

	std::cout << std::endl  << std::endl << "Press any key to resume.." << std::endl;
	getch();


	//2.2 : Р»РёРЅРµР№РЅРѕСЃС‚СЊ
	double a1 = 5, a2 = 7, f2 = 70;
	std::vector<double> u2;
	for (double i = 0, t = 0; i < k; i++, t += Td)
		u2.push_back(sin(2*M_PI*f2*t));

	std::vector<double> u_sum;
	for (int i = 0; i < k; i++)
		u_sum.push_back(a1*u[i] + a2*u2[i]);
	std::cout << std::endl << std::endl << "sum of signals u + u2:" << std::endl;
	for (std::vector<double>::iterator i = u_sum.begin(); i != u_sum.end(); ++i)
		std::cout << *i << " ";

	std::vector<std::complex<double>> U_sum(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
	{
		std::complex<double> elem(0, 0);
		for (int n = 0; n < k; n++)
			elem += u_sum[n] * Fh[n][i];
		U_sum[i] = elem;
	}
	std::cout << std::endl << std::endl << "spectrum of (u + u2):" << std::endl;
	for (std::vector<std::complex<double>>::iterator i = U_sum.begin(); i != U_sum.end(); ++i)
		std::cout << *i << " ";

	std::vector<std::complex<double>> U2(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
	{
		std::complex<double> elem(0, 0);
		for (int n = 0; n < k; n++)
			elem += u2[n] * Fh[n][i];
		U2[i] = elem;
	}

	std::vector<std::complex<double>> U_sum2;//(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
		U_sum2.push_back(a1*U[i] + a2*U2[i]);
	std::cout << std::endl << std::endl << "sum of spectrums U + U2:" << std::endl;
	for (std::vector<std::complex<double>>::iterator i = U_sum2.begin(); i != U_sum2.end(); ++i)
		std::cout << *i << " ";

	std::vector<std::complex<double>> u_sum2(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
	{
		std::complex<double> elem(0, 0);
		for (int n = 0; n < k; n++)
			elem += U_sum2[n] * F[n][i];
		u_sum2[i] = elem/k;
	}
	std::cout << std::endl << std::endl << "recover of (U + U2):" << std::endl;
	for (std::vector<std::complex<double>>::iterator i = u_sum2.begin(); i != u_sum2.end(); ++i)
		std::cout << (*i).real() << " ";

	std::cout << std::endl << std::endl << "Press any key to resume.." << std::endl;
	getch();

	//2.2 : СЃРґРІРёРі РІРѕ РІСЂРµРјРµРЅРё
	int tau = 5;

	std::vector<double> u_shift;
	for (int i = tau - 1; i < u.size(); i++)
		u_shift.push_back(u[i]);
	for (int i = 0; i < tau - 1; i++)
		u_shift.push_back(u[i]);

	std::cout << std::endl << "u shifted:" << std::endl;
	for (std::vector<double>::iterator i = u_shift.begin(); i != u_shift.end(); ++i)
		std::cout << *i << " ";

	std::vector<std::complex<double>> U_shift(k, std::complex<double>(0, 0));
	for (int i = 0; i < k; i++)
	{
		std::complex<double> elem(0, 0);
		for (int n = 0; n < k; n++)
			elem += u_shift[n] * Fh[n][i];
		U_shift[i] = elem;
	}

	std::cout << std::endl << std::endl << "U shifted:" << std::endl;
	for (std::vector<std::complex<double>>::iterator i = U_shift.begin(); i != U_shift.end(); ++i)
		std::cout << *i << " ";

	std::ofstream file;
	file.open ("values.csv");
	for (int i = 0; i < k; i++)
		file << i << "," << std::abs(U[i]) << "," << std::abs(U_shift[i]) <<"\n";
	file.close();

	std::cout << std::endl << std::endl << "Press any key to resume.." << std::endl;
	getch();
	
	//2.2 : СЂР°РІРµРЅСЃС‚РІРѕ РџР°СЂСЃРµРІР°Р»СЏ
	double u_sum_sq = 0;
	for (int i = 1; i < k; i++)
		u_sum_sq += u[i] * u[i];

	double U_sum_sq = 0;
	for (int i = 1; i < k; i++)
		U_sum_sq += std::abs(U[i]) * std::abs(U[i]);
	U_sum_sq /= k;

	std::cout << std::endl << std::endl << "u square sum: " << u_sum_sq <<
	std::endl << "U square sum: " << U_sum_sq << 
	std::endl << "Parseval's identity: " << ((float)u_sum_sq == (float)U_sum_sq ? "true" : "false") << std::endl;

	return 0;
}
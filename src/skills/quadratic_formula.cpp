#include <iostream>
#include <random>
#include <complex>
#include <math.h>

std::string* generate_quadratic_formula_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int a = distrib(gen);
        int b = distrib(gen);
        int c = distrib(gen);
        std::complex<double> xone = (std::complex<double>(-b, 0) + std::sqrt(std::complex<double>(pow(b, 2) - (4*a*c), 0)))/std::complex<double>((2*a),0); 
        std::complex<double> xtwo = (std::complex<double>(-b, 0) - std::sqrt(std::complex<double>(pow(b, 2) - (4*a*c), 0)))/std::complex<double>((2*a),0); 

        std::string problem = std::to_string(a) + "x^2 + " + std::to_string(b) + "x + " + std::to_string(c) + " = 0";
        std::string solution = std::to_string(xone.real()) + " + " + std::to_string(xone.imag()) + "i, " + std::to_string(xtwo.real()) + " + " + std::to_string(xtwo.imag()) + "i, ";
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}

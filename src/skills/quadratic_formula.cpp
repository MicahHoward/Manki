#include <iostream>
#include <random>
#include <complex>
#include <math.h>
#include "../utils.h"

/**
 * Generates a string array that represents a quadratic formula problem 
 *
 * @return Returns a string representing a quadratic formula problem, a string representing the solution, and an empty notes string 
 */
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
        std::string solution = "";
        if(xone.imag() == 0.0){
                solution = solution + return_rounded_number_string(std::to_string(xone.real())) + ", ";
        } else{

                solution = solution + return_rounded_number_string(std::to_string(xone.real()))  + " + " + return_rounded_number_string(std::to_string(xone.imag()))+ "i, ";
        }
        if(xtwo.imag() == 0.0){
                solution = solution + return_rounded_number_string(std::to_string(xtwo.real()));
        } else{

                solution = solution + return_rounded_number_string(std::to_string(xtwo.real()))  + " + " + return_rounded_number_string(std::to_string(xtwo.imag()))+ "i";
        }
        std::cout << solution + "\n";

        std::string notes = "";
        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes;

        return problem_array;
}

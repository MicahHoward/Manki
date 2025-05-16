#include <iostream>
#include <random>

/**
 * Generates a string array that represents a trigonometric functions derivatives problem 
 *
 * @return Returns a string representing a trigonometric functions derivatives problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_trig_deriv_problem() 
{
        int min = 1;
        int max = 6;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int index = distrib(gen);

        std::string trig_functions[6] = {"\\sin(x)", "\\cos(x)", "\\tan(x)", "\\sec(x)", "\\csc(x)", "\\cot(x)"}; 
        std::string trig_functions_derivatives[6] = {"\\cos(x)", "-\\sin(x)", "\\sec^2(x)", "\\frac{\\tan(x)}{\\cos(x)}", "\\frac{-\\cot(x)}{\\sin(x)}", "-\\frac{1}{sin^2(x)}"}; 

        std::string problem = trig_functions[index-1];
        std::string solution = trig_functions_derivatives[index-1];
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes; 

        return problem_array;
}

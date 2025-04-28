#include <iostream>
#include <random>

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
        std::string* returnValue = new std::string[3];
        returnValue[0] = problem;
        returnValue[1] = solution;
        returnValue[2] = "";

        return returnValue;
}

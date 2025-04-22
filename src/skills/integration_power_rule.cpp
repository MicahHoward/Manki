#include <iostream>
#include <random>

std::string* generate_integration_power_rule_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int coefficient = distrib(gen);
        int exponent = distrib(gen);

        std::string problem = std::to_string(coefficient) + "x^{" + std::to_string(exponent) + "} = ?";
        std::string solution;
        if(coefficient % (exponent+1) == 0){
                solution = std::to_string(coefficient/(exponent+1)) + "x^{" + std::to_string(exponent+1) + "} + C ";
        } else{

                solution = "\\frac{" + std::to_string(coefficient) + "}{" + std::to_string(exponent+1) + "}x^{" + std::to_string(exponent+1) + "} + C";
        }
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}

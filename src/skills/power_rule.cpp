#include <iostream>
#include <random>

/**
 * Generates a string array that represents a derivation power rule problem
 *
 * @return Returns a string representing a derivation power rule problem, a string representing the solution, and a notes string specifiying answer formatting 
 */
std::string* generate_power_rule_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int coefficient = distrib(gen);
        int exponent = distrib(gen);
        int product = coefficient * exponent;

        std::string problem = "";
        std::string solution = "";
        if(exponent != 1){
                problem = "f = " + std::to_string(coefficient) + "x^{" + std::to_string(exponent) + "}, \\frac{df}{dx} = ?";
                solution = std::to_string(product) + "x^" + std::to_string(exponent-1);
        } else{
                problem = "f = " + std::to_string(coefficient) + "x, \\frac{df}{dx}= ?";
                solution = std::to_string(product);
        }
        std::string notes = "Note:\nExponents should be entered with \"^\".\nExample: \"4x^7\".";

        std::string* returnValue = new std::string[3];
        returnValue[0] = problem;
        returnValue[1] = solution;
        returnValue[2] = notes;  
        return returnValue;
}

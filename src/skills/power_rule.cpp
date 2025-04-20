#include <iostream>
#include <random>

std::string* generate_power_rule_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int first_number = distrib(gen);
        int second_number = distrib(gen);
        int product = first_number * second_number;

        std::string problem = std::to_string(first_number) + "x^{" + std::to_string(second_number) + "} = ?";
        std::string solution = std::to_string(product) + "x^" + std::to_string(second_number-1);
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}

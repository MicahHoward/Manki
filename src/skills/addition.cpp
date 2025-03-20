#include <iostream>
#include <random>

std::string* generate_addition_problem() 
{
        int min = 1;
        int max = 100;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int first_number = distrib(gen);
        int second_number = distrib(gen);
        int sum = first_number + second_number;

        std::string problem = std::to_string(first_number) + " + " + std::to_string(second_number) + " = ?";
        std::string solution = std::to_string(sum);
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = sum;

        return returnValue;
}

#include <iostream>
#include <random>

/**
 * Generates a string array that represents an addition problem
 *
 * @return Returns a string representing an addition problem, a string representing the solution, and an empty notes string
 */
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
        std::string* return_value = new std::string[3];
        return_value[0] = problem;
        return_value[1] = solution;
        return_value[2] = "";

        return return_value;
}

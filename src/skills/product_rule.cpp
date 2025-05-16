#include <iostream>
#include <random>

/**
 * Generates a string array that represents a derivation product rule problem
 *
 * @return Returns a string representing a derivation power rule problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_product_rule_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int first_power = distrib(gen);
        int first_coefficient = distrib(gen);
        int second_power = distrib(gen);
        int second_coefficient = distrib(gen);

        int first_derivative_coefficient = first_power * first_coefficient;
        int first_derivative_power = first_power - 1;
        int second_derivative_coefficient = second_power * second_coefficient;
        int second_derivative_power = second_power - 1;

        int first_half_of_product_coefficient = first_derivative_coefficient * second_coefficient; 
        int first_half_of_product_power = first_derivative_power + second_power; 
        int second_half_of_product_coefficient = second_derivative_coefficient * first_coefficient; 
        int second_half_of_product_power = second_derivative_power + first_power;
        std::string solution = "";

        if(first_half_of_product_power == second_half_of_product_power){
                solution = std::to_string(first_half_of_product_coefficient + second_half_of_product_coefficient) + "x^" + std::to_string(first_half_of_product_power);
        } else{
                solution = std::to_string(first_half_of_product_coefficient) + "x^" + std::to_string(first_half_of_product_power) + " + " + 
                        std::to_string(second_half_of_product_coefficient) + "x^" + std::to_string(second_half_of_product_power);
        }
        std::string problem = std::to_string(first_coefficient) + "x^{" + std::to_string(first_power) + "}\\times" + std::to_string(second_coefficient) + "x^{" + std::to_string(second_power) + "}";
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes;

        return problem_array;
}

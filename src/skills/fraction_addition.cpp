#include <iostream>
#include <random>
#include <numeric>

/**
 * Generates a string array that represents a fraction addition problem
 *
 * @return Returns a string representing a fraction addition problem, a string representing the solution, and a notes string that specifies answer formatting
 */
std::string* generate_fraction_addition_problem() 
{
        int min = 1;
        int max = 10;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int first_numerator = distrib(gen);
        int second_numerator = distrib(gen);
        int first_denominator = distrib(gen);
        int second_denominator = distrib(gen);
        int lcm = std::lcm(first_denominator, second_denominator);
        std::cout << "made it to sum\n";
        std::cout << "lcm is " + std::to_string(lcm) + "\n";
        std::cout << "first_denom is " + std::to_string(first_denominator) + "\n";
        std::cout << "second_denom is " + std::to_string(second_denominator) + "\n";
        int sum = first_numerator * (lcm/first_denominator) + second_numerator * (lcm/second_denominator);

        int simplify = 0;

        std::cout << "1simplify is " + std::to_string(simplify) + "\n";
        for(int i = 1; i < sum; i++){
                std::cout << "i is " + std::to_string(i) + "\n";
                if(sum % i == 0 && lcm % i == 0){
                        simplify = i;
                }
        }

        std::cout << "simplify is " + std::to_string(simplify) + "\n";
        if(simplify != 0){
                sum = sum / simplify;
                lcm = lcm / simplify;
        }
        std::string problem = "";
        if(first_denominator == 1){
                problem = std::to_string(first_numerator) + " + ";
        } else{
                problem = "\\frac{" + std::to_string(first_numerator) + "}{" + std::to_string(first_denominator) + "} + "; 
        }
        if(second_denominator == 1){
                problem = problem + std::to_string(second_numerator) + " = ?";
        } else{
                problem = problem + "\\frac{" + std::to_string(second_numerator) + "}{" + std::to_string(second_denominator) + "} = ?"; 
        }
        std::string solution;
        if(lcm == 1){
                solution = std::to_string(sum); 
        } else{
                solution = std::to_string(sum) + "/" + std::to_string(lcm);
        }

        std::string notes = "Note:\nEnter fractions with a \"/\" between the numerator and the denominator.";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes; 
        return problem_array;
}

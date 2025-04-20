#include <iostream>
#include <random>
#include <numeric>

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

        std::string problem = "\\frac{" + std::to_string(first_numerator) + "}{" + std::to_string(first_denominator) + "} + \\frac{" + std::to_string(second_numerator) + "}{" + std::to_string(second_denominator) +"} = ?"; 
        std::string solution = std::to_string(sum) + "/" + std::to_string(lcm);
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}

#include <iostream>
#include <random>

std::string* generate_partial_derivatives_problem() 
{
        int min = 1;
        int max = 10;
        std::cout << "Made first int distri \n";

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> one_through_three(min, 3);

        int partial_term = one_through_three(gen);

        std::cout << "Made second int distri \n";
        std::uniform_int_distribution<> distrib(min, max);
        std::string function[3] = {"", "", ""};
        std::string partial_derivative[3] = {"", "", ""};
        std::string terms[3][3] = {{"", "", ""},{"", "", ""},{"", "", ""}};
        std::string variables[3] = {"x", "y", "z"};
        int coefficient;
        bool term_present;

        std::cout << "Made it to for loop \n";
        for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                        coefficient = distrib(gen);
                        if(j == 0){
                                function[i] = std::to_string(coefficient) + variables[i];
                                terms[i][j] = std::to_string(coefficient) + variables[i];
                                if(i == partial_term){
                                        partial_derivative[0] = std::to_string(coefficient); 
                                }
                        } else{
                                term_present = ((distrib(gen) % 2) == 0);
                                if(term_present){
                                        function[i] = std::to_string(coefficient) + variables[i] + "^" + std::to_string(j+1) + " + " + function[i];
                                        terms[i][j] = std::to_string(coefficient) + variables[i] + "^" + std::to_string(j+1);
                                        std::cout << terms[i][j] + "\n";

                                        if(i == partial_term){
                                                partial_derivative[j] = std::to_string(coefficient*(j+1)) + variables[i] + "^" + std::to_string(j); 
                                        }
                                }
                        }
                }
        }

        std::string problem = "\f = " + function[2] + " + " + function[1] + " + " + function[0] + ", \\frac{\\partial f}{\\partial " + variables[partial_term-1] + "} = ?"; 
        std::string solution = partial_derivative[2] + " + " + partial_derivative[1] + " + " + partial_derivative[0];
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}

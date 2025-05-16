#include <iostream>
#include <random>

/**
 * Generates a string array that represents a partial derivatives problem
 *
 * @return Returns a string representing a partial derivatives problem, a string representing the solution, and an empty notes string 
 */
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
        std::string string_coefficient;
        int coefficient;
        bool term_present;

        std::cout << "Made it to for loop \n";
        for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                        coefficient = distrib(gen);
                        string_coefficient = std::to_string(coefficient);
                        if(string_coefficient == "1"){
                                string_coefficient = "";
                        }
                        if(j == 0){
                                function[i] = string_coefficient + variables[i];
                                terms[i][j] = string_coefficient + variables[i];
                                if(i == partial_term-1){
                                        partial_derivative[0] = string_coefficient; 
                                }
                        } else{
                                term_present = ((distrib(gen) % 2) == 0);
                                if(term_present){
                                        function[i] = string_coefficient + variables[i] + "^" + std::to_string(j+1) + " + " + function[i];
                                        terms[i][j] = string_coefficient + variables[i] + "^" + std::to_string(j+1);
                                        std::cout << terms[i][j] + "\n";

                                        if(i == partial_term-1){
                                                if(j == 1){
                                                partial_derivative[j] = std::to_string(coefficient*(j+1)) + variables[i]; 
                                                } else{
                                                        partial_derivative[j] = std::to_string(coefficient*(j+1)) + variables[i] + "^" + std::to_string(j); 
                                                }
                                        }
                                }
                        }
                }
        }

        std::string problem = "f = " + function[0] + " + " + function[1] + " + " + function[2] + ", \\frac{\\partial f}{\\partial " + variables[partial_term-1] + "} = ?"; 
        std::string solution = "";
        for(int i = 0; i < 3; i++){
                if(i == 0){
                        solution = partial_derivative[i];
                } else if(partial_derivative[i] != ""){
                        solution = partial_derivative[i] + " + " + solution;
                }
        }
        std::string notes = "";

        std::string* problem_array = new std::string[3];
        problem_array[0] = problem;
        problem_array[1] = solution;
        problem_array[2] = notes;

        return problem_array;
}

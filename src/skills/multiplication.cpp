#include <iostream>
#include <random>
using namespace std;

string* generate_multiplication_problem() 
{
        int min = 1;
        int max = 100;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int first_number = distrib(gen);
        int second_number = distrib(gen);
        int product = first_number * second_number;

        string* problem_and_solution = new string[3];
        problem_and_solution[0] = to_string(first_number) + " \\times " + to_string(second_number) + " = ?";
        problem_and_solution[1] = to_string(product);
        problem_and_solution[2] = "";

        return problem_and_solution;
}

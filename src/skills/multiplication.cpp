#include <iostream>
#include <random>
using namespace std;

/**
 * Generates a string array that represents an multiplication problem
 *
 * @return Returns a string representing an multiplication problem, a string representing the solution, and an empty notes string
 */
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

        string* problem_array = new string[3];
        problem_array[0] = to_string(first_number) + " \\times " + to_string(second_number) + " = ?";
        problem_array[1] = to_string(product);
        problem_array[2] = "";

        return problem_array;
}

#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>
using namespace std;

/**
 * Generates a string array that represents a pythagorean theorem problem 
 *
 * @return Returns a string representing a pythagorean theorem problem, a string representing the solution, and an empty notes string 
 */
std::string* generate_pythagorean_theorem_problem() 
{
        int min = 1;
        int max = 20;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int first_side = distrib(gen);
        int second_side = distrib(gen);
        double hypotenuse = ceil((std::sqrt(std::pow(first_side, 2) + std::pow(second_side, 2)))*100)/100.0;

        std::string notes = "";

        string* problem_array = new string[3];
        problem_array[0] = "a = " + to_string(first_side) + ", b =" + to_string(second_side) + ", c = ?";
        problem_array[1] = to_string(hypotenuse);
        problem_array[2] = notes; 
        return problem_array;
}

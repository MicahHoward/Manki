#include <iostream>
#include <random>
#include <cmath>
#include "../utils.h"
using namespace std;

/**
 * Generates a string array that represents a circle area problem
 *
 * @return Returns a string representing a circle area problem, a string representing the solution, and anotes string that specifies answer formatting
 */
string* generate_circle_area_problem() 
{
        int min = 1;
        int max = 16;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int radius = distrib(gen);
        double area = radius * radius * M_PI;

        string* problem_and_solution = new string[3];
        problem_and_solution[0] = "r = " + to_string(radius) + ", A = ?";
        problem_and_solution[1] = return_rounded_number_string(to_string(area));
        problem_and_solution[2] = "Note:\nEnter answer as a decimal rounded to two places.";

        return problem_and_solution;
}

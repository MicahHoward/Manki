#include <iostream>
#include <random>
#include <cmath>
#include "../utils.h"
using namespace std;

/**
 * Generates a string array that represents a cylinder volume problem
 *
 * @return Returns a string representing a cylinder volume problem, a string representing the solution, and anotes string that specifies answer formatting
 */
string* generate_cylinder_volume_problem() 
{
        int min = 1;
        int max = 16;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int radius = distrib(gen);
        int height = distrib(gen);
        double area = radius * radius * M_PI;
        double volume = area * height;

        string* problem_array = new string[3];
        problem_array[0] = "r = " + to_string(radius) + "h = " + to_string(height) + ", V = ?";
        problem_array[1] = return_rounded_number_string(to_string(volume));
        problem_array[2] = "Note:\nEnter answer as a decimal rounded to two places.";

        return problem_array;
}

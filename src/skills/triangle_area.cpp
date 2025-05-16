#include <iostream>
#include <random>
using namespace std;

/**
 * Generates a string array that represents a triangle area problem 
 *
 * @return Returns a string representing a triangle area problem, a string representing the solution, and an empty notes string 
 */
string* generate_triangle_area_problem() 
{
        int min = 1;
        int max = 100;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int base = distrib(gen);
        int height = distrib(gen);
        double area = base * height/2.0;

        std::string notes = "";

        string* problem_array = new string[3];
        problem_array[0] = "b = " + to_string(base) + ", h =" + to_string(height) + ", A = ?";
        problem_array[1] = to_string(area);
        problem_array[2] = notes;

        return problem_array;
}

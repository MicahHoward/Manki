#include <iostream>
#include <random>
#include <cmath>
using namespace std;

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
        problem_and_solution[0] = "r = " + to_string(radius) + "\\newline A = ?";
        problem_and_solution[1] = to_string(area);

        return problem_and_solution;
}

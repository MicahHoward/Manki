#include <iostream>
#include <random>
using namespace std;

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

        string* problem_and_solution = new string[3];
        problem_and_solution[0] = "b = " + to_string(base) + ", h =" + to_string(height) + ", A = ?";
        problem_and_solution[1] = to_string(area);

        return problem_and_solution;
}

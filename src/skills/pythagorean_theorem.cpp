#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>
using namespace std;

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


        string* problem_and_solution = new string[3];
        problem_and_solution[0] = "a = " + to_string(first_side) + ", b =" + to_string(second_side) + ", c = ?";
        problem_and_solution[1] = to_string(hypotenuse);

        return problem_and_solution;
}

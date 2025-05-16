#include <iostream>
#include <random>
using namespace std;

/**
 * Generates a string array that represents a cuboid volume problem 
 *
 * @return Returns a string representing a cuboid volume problem, a string representing the solution, and an empty notes string 
 */
string* generate_cuboid_volume_problem() 
{
        int min = 1;
        int max = 20;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int length = distrib(gen);
        int width = distrib(gen);
        int height = distrib(gen);
        int volume = length * width * height;

        std::string notes = "";

        string* problem_array = new string[3];
        problem_array[0] = "l = " + to_string(length) + ", w =" + to_string(width) + ", h =" + to_string(height) +", V = ?";
        problem_array[1] = to_string(volume);
        problem_array[2] = notes;

        return problem_array;
}

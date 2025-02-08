#include <iostream>
#include <random>
using namespace std;

int* generate_subtraction_problem() 
{
        int min = 1;
        int max = 100;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);

        int first_number = distrib(gen);
        int second_number = distrib(gen);
        int difference = first_number - second_number;

        int* returnValues = new int[3];
        returnValues[0] = first_number;
        returnValues[1] = second_number;
        returnValues[2] = difference;

        return returnValues;
}

#include <iostream>
#include <random>

std::string* generate_cos_values_problem() 
{
        int min = 1;
        int max = 16;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        int angle_index = distrib(gen);
        std::string angle;

        std::string degree_angles[16]={"0^\\circ", "30^\\circ", "45^\\circ", "60^\\circ", "90^\\circ", "120^\\circ", "135^\\circ", "150^\\circ", "180^\\circ", "210^\\circ", "225^\\circ", "240^\\circ", "270^\\circ", "300^\\circ", "315^\\circ", "330^\\circ"};
        std::string radian_angles[16] = {"0",  "\\frac{\\pi}{6}",  "\\frac{\\pi}{4}",   "\\frac{\\pi}{3}",  "\\frac{\\pi}{2}",  
                "\\frac{2\\pi}{3}", "\\frac{3\\pi}{4}", "\\frac{5\\pi}{6}", "\\pi", "\\frac{7\\pi}{6}", "\\frac{5\\pi}{4}", 
                "\\frac{4\\pi}{3}", "\\frac{3\\pi}{2}", "\\frac{5\\pi}{3}", "\\frac{7\\pi}{4}", "\\frac{11\\pi}{6}"};
        std::string cos_values[16] = {"1","\\frac{\\sqr{3}}{2}","\\frac{\\sqr{2}}{2}","\\frac{1}{2}","0","-\\frac{1}{2}","-\\frac{\\sqr{2}}{2}","-\\frac{\\sqr{3}}{2}","-1","-\\frac{\\sqr{3}}{2}","-\\frac{\\sqr{2}}{2}","-\\frac{1}{2}", "0","\\frac{1}{2}","\\frac{\\sqr{2}}{2}","\\frac{\\sqr{3}}{2}"};
        
        if(angle_index % 2 == 0){
                angle = radian_angles[angle_index]; 
                std::cout << angle + "\n";
        } else{
                angle = degree_angles[angle_index];
                std::cout << angle + "\n";
        }


        std::string problem = "cos(" + angle + ")";
        std::string solution = cos_values[angle_index];
        std::string* returnValue = new std::string[2];
        returnValue[0] = problem;
        returnValue[1] = solution;

        return returnValue;
}

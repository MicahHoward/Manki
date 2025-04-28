#include<chrono>
#include<cmath>
#include<string>
using namespace std;
time_t get_current_time()
{
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        return currentTime;
}
 
std::string return_rounded_number_string(std::string input){
        double input_double = std::stod(input);
        input_double = input_double * 100;
        input_double = std::round(input_double);
        input_double = input_double/100.0;

        std::string output = std::to_string(input_double);

        std::string stupid_string = ".";
        if(output.contains(stupid_string)){
                for(int i = 0; i < output.size(); i++){
                        if(output.at(i) == '.'){
                                output = output.substr(0, i+3);
                                break;
                        }
                }

        }
        return output;
}

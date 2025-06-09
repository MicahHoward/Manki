#include<chrono>
#include<cmath>
#include<string>
using namespace std;


/**
 * Gets the current time from the system clock
 * @return The current time
 */
time_t get_current_time()
{
        auto now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        return current_time;
}
 
/**
 * Takes a string representation of a float with too many digits past the decimal place and rounds it to two digits past the decimal
 *
 * @param input The string representation of the number to be rounded
 * @return The string representation of the rounded number
 */
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

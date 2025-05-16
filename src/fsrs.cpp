#include <iostream>
#include <cmath>
#include "db.h"
#include "utils.h"
using namespace std;

// This functions were made following this explanation: https://expertium.github.io/Algorithm.html
// and this https://github.com/open-spaced-repetition/fsrs4anki/wiki/The-Algorithm

// Default parameters for FSRS
float weights[19] = {0.40255, 1.18385, 3.173, 15.69105, 7.1949, 0.5345, 1.4604, 0.0046, 1.54575, 0.1192, 1.01925, 1.9395, 0.11, 0.29605, 2.2698, 0.2315, 2.9898, 0.51655, 0.6621};

int update_stablity_after_same_day_review(int skill_id, int grade)
{
        float old_stability = get_skill_value(skill_id, "STABILITY");
        float update_factor = exp(weights[17] * (grade - 3 + weights[18]));
        float new_stability = old_stability * update_factor;
        update_skill_value(skill_id, "STABILITY", new_stability);
        return 0;
}

int update_stability_after_recall(int skill_id, int grade, float difficulty, float stability, float retrievability)
{
        float grade_factor;
        if(grade == 2){
                grade_factor = weights[15];
        } else if (grade == 4 ){
                grade_factor = weights[16];
        } else{
                grade_factor = 1;
        }
        float new_stability = stability * (exp(weights[8]) * (11 - difficulty) * (pow(stability,(-weights[9]))) * (exp(weights[10]*(1-retrievability))-1) * grade_factor + 1);
        update_skill_value(skill_id, "STABILITY", new_stability);
        return 0; 
}

int update_stability_after_lapse(int skill_id, float difficulty, float stability, float retrievability)
{
        float new_stability = weights[11] * pow(difficulty, -weights[12]) * (pow(stability + 1, weights[13]) - 1) * (exp(weights[14] * (1 - retrievability))); 
        update_skill_value(skill_id, "STABILITY", new_stability);
        return 0;
}

int update_difficulty(int skill_id, float difficulty, int grade)
{
        float new_difficulty = difficulty + (-weights[6] * (grade-3)) * ((10-difficulty)/9);
        update_skill_value(skill_id, "DIFFICULTY", new_difficulty);
        return 0;
}

int update_last_review_time(int skill_id, string review_time)
{
        update_skill_value(skill_id, "LAST_REVIEW_TIME", review_time);
        return 0;
}

// time is the number of days since last review
int update_retrievability()
{
        int number_of_skills = get_number_of_skills();
        std::cout << "I think there are " << number_of_skills << " skills \n"; 
        for(int skill_id = 1; skill_id < number_of_skills + 1; skill_id++){
                if(get_skill_value(skill_id, "RETRIEVABILITY") != -1){
                        float time = (get_current_time() - get_skill_value(skill_id, "LAST_REVIEW_TIME"))/86400.0;
                        float stability = get_skill_value(skill_id, "STABILITY");
                        float new_retrievability =  pow((1 + (19.0/81.0)*(time/stability)),-0.5);
                        update_skill_value(skill_id, "RETRIEVABILITY", new_retrievability);
                }
        }
        return 0;
}

int update_retrievability_on_review(int skill_id)
{
        float time = 0;  
        float stability = get_skill_value(skill_id, "STABILITY");
        float new_retrievability =  pow((1 + (19.0/81.0)*(time/stability)),-0.5);
        update_skill_value(skill_id, "RETRIEVABILITY", new_retrievability);
        return 0;
}

int initialize_difficulty(int skill_id, int grade)
{
        float initial_difficulty = weights[4] - exp(weights[5] * (grade - 1)) + 1;
        update_skill_value(skill_id, "DIFFICULTY", initial_difficulty);
        return 0;
}

int initialize_stability(int skill_id, int grade)
{
        float initial_stability = weights[grade];
        update_skill_value(skill_id, "STABILITY", initial_stability);
        return 0;
}

float get_next_interval(float desired_retrievability, float stability)
{
        return (stability/(19.0/81.0))*(pow(desired_retrievability,((1/-0.5)-1)));
}


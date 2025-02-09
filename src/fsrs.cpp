#include <iostream>
#include <cmath>
#include "db.h"
#include "utils.h"
using namespace std;

// This functions were made following this explanation: https://expertium.github.io/Algorithm.html
// and this https://github.com/open-spaced-repetition/fsrs4anki/wiki/The-Algorithm

// Default parameters for FSRS
float weights[19] = {0.40255, 1.18385, 3.173, 15.69105, 7.1949, 0.5345, 1.4604, 0.0046, 1.54575, 0.1192, 1.01925, 1.9395, 0.11, 0.29605, 2.2698, 0.2315, 2.9898, 0.51655, 0.6621};

int update_stablity_after_same_day_review(int skillID, int grade)
{
        float oldStability = get_skill_value(skillID, "STABILITY");
        float updateFactor = exp(weights[17] * (grade - 3 + weights[18]));
        float newStability = oldStability * updateFactor;
        update_skill_value(skillID, "STABILITY", newStability);
        return 0;
}

int update_stability_after_recall(int skillID, int grade, float difficulty, float stability, float retrievability)
{
        float gradeFactor;
        if(grade == 2){
                gradeFactor = weights[15];
        } else if (grade == 4 ){
                gradeFactor = weights[16];
        } else{
                gradeFactor = 1;
        }
        float newStability = stability * (exp(weights[8]) * (11 - difficulty) * (pow(stability,(-weights[9]))) * (exp(weights[10]*(1-retrievability))-1) * gradeFactor + 1);
        update_skill_value(skillID, "STABILITY", newStability);
        return 0; 
}

int update_stability_after_lapse(int skillID, float difficulty, float stability, float retrievability)
{
        float newStability = weights[11] * pow(difficulty, -weights[12]) * (pow(stability + 1, weights[13]) - 1) * (exp(weights[14] * (1 - retrievability))); 
        update_skill_value(skillID, "STABILITY", newStability);
        return 0;
}

int update_difficulty(int skillID, float difficulty, int grade)
{
        float newDifficulty = difficulty + (-weights[6] * (grade-3)) * ((10-difficulty)/9);
        update_skill_value(skillID, "DIFFICULTY", newDifficulty);
        return 0;
}

int update_last_review_time(int skillID, string reviewTime)
{
        update_skill_value(skillID, "LAST_REVIEW_TIME", reviewTime);
        return 0;
}

// time is the number of days since last review
int update_retrievability()
{
        int numberOfSkills = get_number_of_skills();
        for(int skillID = 0; skillID < numberOfSkills; skillID++){
                float time = (get_current_time() - get_skill_value(skillID, "LAST_REVIEW_TIME"))/86400.0;
                float stability = get_skill_value(skillID, "STABILITY");
                float newRetrievability =  pow((1 + (19.0/81.0)*(time/stability)),-0.5);
                update_skill_value(skillID, "RETRIEVABILITY", newRetrievability);
        }
        return 0;
}

int update_retrievability_on_review(int skillID)
{
        float time = 0;  
        float stability = get_skill_value(skillID, "STABILITY");
        float newRetrievability =  pow((1 + (19.0/81.0)*(time/stability)),-0.5);
        update_skill_value(skillID, "RETRIEVABILITY", newRetrievability);
        return 0;
}

int initialize_difficulty(int skillID, int grade)
{
        float initialDifficulty = weights[4] - exp(weights[5] * (grade - 1)) + 1;
        update_skill_value(skillID, "DIFFICULTY", initialDifficulty);
        return 0;
}

int initialize_stability(int skillID, int grade)
{
        float initialStability = weights[grade];
        update_skill_value(skillID, "STABILITY", initialStability);
        return 0;
}

float get_next_interval(float desiredRetrievability, float stability)
{
        return (stability/(19.0/81.0))*(pow(desiredRetrievability,((1/-0.5)-1)));
}



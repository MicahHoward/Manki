#include <iostream>
#include <chrono>
#include "skills/addition.h"
#include "skills/subtraction.h"
#include "skills/multiplication.h"
#include "db.h"
#include "fsrs.h"
using namespace std;

int update_fsrs_on_answer(int skillID, int grade)
{
        auto now = chrono::system_clock::now();
        time_t reviewTime = chrono::system_clock::to_time_t(now);

        float currentStability = get_skill_value(skillID, "STABILITY");
        float currentDifficulty = get_skill_value(skillID, "DIFFICULTY");
        float currentRetrievability = get_skill_value(skillID, "RETRIEVABILITY");
        
        if(currentStability == -1){
                initialize_stability(skillID, grade);
                currentStability = get_skill_value(skillID, "STABILITY");
        } else if(grade == 3){
                update_stability_after_recall(skillID, grade, currentDifficulty, currentStability, currentRetrievability);
        } else if(grade == 1){
                update_stability_after_lapse(skillID, currentDifficulty, currentStability, currentRetrievability);
        } else{
                cout << "Invalid grade inputted to update_fsrs_on_answer" << endl;
        }

        if(currentDifficulty == -1){
                initialize_difficulty(skillID, grade);
                currentDifficulty = get_skill_value(skillID, "DIFFICULTY");
        } else{
                update_difficulty(skillID, currentDifficulty, grade);
        }

        update_last_review_time(skillID, to_string(reviewTime));

        // time = 0, since update_fsrs is only called on review
        update_retrievability(skillID, 0, currentStability);
        return 0;
}

int update_fsrs_on_time()
{
        return 0;
}

int print_skill_info(int skillID){
        cout << endl << "print_skill_info section" << endl;
        float currentStability = get_skill_value(skillID, "STABILITY");
        float currentDifficulty = get_skill_value(skillID, "DIFFICULTY");
        float currentRetrievability = get_skill_value(skillID, "RETRIEVABILITY");
        float currentLastReviewTime = get_skill_value(skillID, "LAST_REVIEW_TIME");
        cout << "For skillID " << to_string(skillID) << ":" << endl; 
        cout << "Current stability = " << to_string(currentStability) << endl;
        cout << "Current difficulty = " << to_string(currentDifficulty) << endl;
        cout << "Current retrievability = " << to_string(currentRetrievability) << endl;
        cout << "Current last review time = " << to_string(currentLastReviewTime) << endl;
        return 0;
}

int main()
{
        initialize_database();
        insert_default_values();
        read_database();
        int skillID;
        int* problem;
        string operand;
        cout << "What type of problem would you like?" << endl;
        cout << "Please enter 1 for addition, 2 for subtraction, or 3 for multiplication." << endl;
        cin >> skillID;

        if(skillID == 1){
                problem = generate_addition_problem();
                operand = "+";
        } else if(skillID == 2){
                problem = generate_subtraction_problem();
                operand = "-";
        } else if(skillID == 3){
                problem = generate_multiplication_problem();
                operand = "x";
        } else{
                cout << "Please enter 1, 2, or 3." << endl;
        }

        int firstNumber = problem[0];
        int secondNumber = problem[1];
        int solution = problem[2];
        
        int userGuess;

        cout << firstNumber << " " << operand << " " << secondNumber << " = ?" << endl;
        cin >> userGuess;

        if(userGuess == solution){
                cout << "Correct!" << endl;
                update_fsrs_on_answer(skillID, 3);
        } else{
                cout << "Incorrect!" << endl;
                update_fsrs_on_answer(skillID, 1);
        }

        cout << "You guessed " << userGuess << " and the answer was " << solution << "." << endl;

        print_skill_info(skillID);



        return 0;
}


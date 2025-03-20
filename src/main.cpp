#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include <cmath>
#include "skills/addition.h"
#include "skills/subtraction.h"
#include "skills/multiplication.h"
#include "db.h"
#include "fsrs.h"
#include "latexpp/latex.hpp"

std::string user_response;

int latexpp_example()
{
	// Single class
	Latex latex;

	const std::string equation = "\\sum_{i=1}^{n} i = \\frac{n(n + 1)}{2}";
	// Convert to PNG, store in 'equation.png'
	latex.to_png(equation, "equation.png");


	// Convert to HTML, returns a HTML snippet
	std::string html = latex.to_html(equation);
    return 0;
}

int update_fsrs_on_answer(int skillID, int grade)
{
        auto now = std::chrono::system_clock::now();
        time_t reviewTime = std::chrono::system_clock::to_time_t(now);

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
                std::cout << "Invalid grade inputted to update_fsrs_on_answer" << std::endl;
        }

        if(currentDifficulty == -1){
                initialize_difficulty(skillID, grade);
                currentDifficulty = get_skill_value(skillID, "DIFFICULTY");
        } else{
                update_difficulty(skillID, currentDifficulty, grade);
        }

        update_last_review_time(skillID, std::to_string(reviewTime));

        update_retrievability_on_review(skillID);
        return 0;
}

int print_skill_info(int skillID){
        std::cout << std::endl << "print_skill_info section" << std::endl;
        float currentStability = get_skill_value(skillID, "STABILITY");
        float currentDifficulty = get_skill_value(skillID, "DIFFICULTY");
        float currentRetrievability = get_skill_value(skillID, "RETRIEVABILITY");
        float currentLastReviewTime = get_skill_value(skillID, "LAST_REVIEW_TIME");
        std::cout << "For skillID " << std::to_string(skillID) << ":" << std::endl; 
        std::cout << "Current stability = " << std::to_string(currentStability) << std::endl;
        std::cout << "Current difficulty = " << std::to_string(currentDifficulty) << std::endl;
        std::cout << "Current retrievability = " << std::to_string(currentRetrievability) << std::endl;
        std::cout << "Current last review time = " << std::to_string(currentLastReviewTime) << std::endl;
        return 0;
}

void user_guess(std::stop_token stoken){
        std::stop_callback callBack (stoken, [] {
                user_response = "Ran out of time!";                    
        });
        std::cin >> user_response;
}

void problem_timer(std::stop_token stoken, std::stop_source threadToBeStopped, float problemTime){
        std::stop_callback callBack (stoken, [] {
                std::cout << "Don't just stand there!" << std::endl;
        });
        float elapsedSeconds = 0;
        while(!stoken.stop_requested() && problemTime > elapsedSeconds){
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                elapsedSeconds += 0.01;
        }
        if(problemTime < elapsedSeconds){
                threadToBeStopped.request_stop();
                std::cout << "Reached end of problem timer" << std::endl;
        }
}

std::string timed_input(int timeout_seconds) {
        std::string input_string;
        auto future = async(std::launch::async, [&]() {
                getline(std::cin, input_string);
                return input_string;
        });

        auto result = future.wait_for(std::chrono::seconds(10));
        if (result == std::future_status::timeout){
                return "";
        } else {
                return future.get();
        }
}



int practice_skills()
{
        int skillID;
        int* problem;
        std::string operand;
        std::cout << "What type of problem would you like?" << std::endl;
        std::cout << "Please enter 1 for addition, 2 for subtraction, or 3 for multiplication." << std::endl;
        std::cin >> skillID;

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
                std::cout << "Please enter 1, 2, or 3." << std::endl;
        }

        float problemTime = get_skill_value(skillID, "PROBLEM_TIME");

        int firstNumber = problem[0];
        int secondNumber = problem[1];
        int solution = problem[2];

        std::cout << firstNumber << " " << operand << " " << secondNumber << " = ?" << std::endl;
        std::cin >> user_response;

//        std::stop_source stopSourceProblemTimer;
//        std::stop_source stopSourceInput;
//        std::stop_token stopTokenProblemTimer = std::stop_token(stopSourceProblemTimer.get_token());
//        std::stop_token stopTokenInputTimer = std::stop_token(stopSourceProblemTimer.get_token());
//        jthread inputThread(user_guess, stopTokenInputTimer);
//        jthread timerThread(problem_timer, stopTokenProblemTimer, stopSourceInput, problemTime);
//
//        inputThread.join();
//        stopSourceProblemTimer.request_stop();



//        auto future = async(std::launch::async, []() {
//                std::string user_guessing;
//                std::cin >> user_guessing;
//                return user_guessing;
//        });
//        std::chrono::seconds timeout(static_cast<int>(round(problemTime)));
//        if(future.wait_for(timeout) == future_status::timeout) {
//                std::cout << "Ran out of time. You shall be executed" << std::endl;
//        } else {
//               user_response = future.get(); 
//        }
//                        
//        user_response = timed_input(10);
        std::cout << user_response << std::endl;

        int userGuess = -1;
        try
        {
        userGuess = stoi(user_response);
        }
        catch(...){
                std::cout << "Invalid response. Please give an actual number next time." << std::endl;
                return 0;
        }

        if(userGuess == solution){
                std::cout << "Correct!" << std::endl;
                update_fsrs_on_answer(skillID, 3);
        } else{
                std::cout << "Incorrect!" << std::endl;
                update_fsrs_on_answer(skillID, 1);
        }

        std::cout << "You guessed " << userGuess << " and the answer was " << solution << "." << std::endl;

        print_skill_info(skillID);

        return 0;

}

int main()
{
        bool willContinue = true;
        initialize_database();
        insert_default_values();
        read_database();
        update_retrievability();
        read_database();
        latexpp_example();

        while(willContinue){
                int option;
                std::cout << "What would you like to do?" << std::endl << "Please enter:" << std::endl;
                std::cout << "1 to practice a skill" << std::endl << "2 to read the database" << std::endl << "3 to read a specific skill" << std::endl << "4 to set a skill's timer" << std::endl << "5 to exit program" << std::endl;   
                std::cin >> option;

                if(option == 1){
                        practice_skills();
                } else if(option == 2){
                        read_database();
                } else if(option == 3){
                        int skillID;
                        std::cout << "What skill would you like to print?" << std::endl << "Please enter:" << std::endl << "1 for addition" << std::endl << "2 for subtraction" << std::endl << "3 for multiplication" << std::endl;
                        std::cin >> skillID;
                        print_skill_info(skillID);
                } else if(option == 4){
                        int skillID;
                        int newProblemTime;
                        std::cout << "What skill would you like to adjust the timer for?" << std::endl << "Please enter:" << std::endl << "1 for addition" << std::endl << "2 for subtraction" << std::endl << "3 for multiplication" << std::endl;
                        std::cin >> skillID;
                        std::cout << "What would you like to adjust the timer to?" << std::endl; 
                        std::cin >> newProblemTime;
                        update_skill_value(skillID, "PROBLEM_TIME", newProblemTime);

                }else if(option == 5){
                        willContinue = false;
                }else{
                        std::cout << "Please enter 1, 2, 3, 4, or 5." << std::endl;
                } 
        }
        return 0;
}


#pragma once
#include <stop_token>

std::string return_spaceless_string(std::string input);
int generate_latex_image(std::string expression);
int update_fsrs_on_answer(int skillID, int grade);
int print_skill_info(int skillID);
std::string get_skill_info(int skillID);
int get_skill_status(int skillID);
void user_guess(std::stop_token stoken);
std::string* generate_problem(int skillID);
std::string timed_input(int timeout_seconds); 
int practice_skills();
int old_main();

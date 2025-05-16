#pragma once

std::string return_spaceless_string(std::string input);
int update_fsrs_on_answer(int skillID, int grade);
int print_skill_info(int skillID);
std::string get_skill_info(int skillID);
int get_skill_status(int skillID);
void user_guess(std::stop_token stoken);
std::string* generate_problem(int skillID);

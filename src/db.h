#pragma once
static int callback();
int initialize_database();
int insert_default_values();
int read_database();
float get_skill_value(int skillID, std::string attribute);
int get_number_of_skills();
std::string get_skill_name(int skillID);
std::string get_skill_retaining(int skillID);
std::string* get_skill_names();
int update_skill_value(int skillID, std::string attribute, float newValue);
int update_skill_value(int skillID, std::string attribute, std::string newValue);
int insert_timed_skill(int base_skill_id, int time_in_milliseconds);

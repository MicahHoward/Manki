#pragma once
static int callback();
int initialize_database();
int insert_default_values();
int read_database();
float get_skill_value(int skillID, std::string attribute);
int get_number_of_skills();
int update_skill_value(int skillID, std::string attribute, float newValue);
int update_skill_value(int skillID, std::string attribute, std::string newValue);

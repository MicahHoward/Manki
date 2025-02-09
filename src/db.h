#pragma once
using namespace std;
static int callback();
int initialize_database();
int insert_default_values();
int read_database();
float get_skill_value(int skillID, string attribute);
int get_number_of_skills();
int update_skill_value(int skillID, string attribute, float newValue);
int update_skill_value(int skillID, string attribute, string newValue);

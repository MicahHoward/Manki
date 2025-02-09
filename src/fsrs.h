#pragma once

int update_stablity_after_same_day_review(int skillID, int grade);
int update_stability_after_recall(int skillID, int grade, float difficulty, float retrievability, float stability);
int update_stability_after_lapse(int skillID, float difficulty, float stability, float retrievability);
int update_difficulty(int skillID, float difficulty, int grade);
int update_retrievability();
int update_retrievability_on_review(int skillID);
int update_last_review_time(int skillID, string reviewTime);
int initialize_difficulty(int skillID, int grade);
int initialize_stability(int skillID, int grade);
float get_next_interval(float desiredRetrievability, float stability);

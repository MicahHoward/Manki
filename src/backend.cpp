#include <iostream>
#include <cmath>
#include <chrono>
#include "skills/addition.h"
#include "skills/subtraction.h"
#include "skills/multiplication.h"
#include "skills/power_rule.h"
#include "skills/fraction_addition.h"
#include "skills/two_by_two_det.h"
#include "skills/three_by_three_det.h"
#include "skills/quadratic_formula.h"
#include "skills/product_rule.h"
#include "skills/sin_values.h"
#include "skills/cos_values.h"
#include "skills/tan_values.h"
#include "skills/two_by_two_matrix_multiplication.h"
#include "skills/matrix_vector_multiplication.h"
#include "skills/triangle_area.h"
#include "skills/circle_area.h"
#include "skills/integration_power_rule.h"
#include "skills/trig_deriv.h"
#include "skills/pythagorean_theorem.h"
#include "skills/partial_derivatives.h"
#include "skills/cuboid_volume.h"
#include "skills/triangular_prism_volume.h"
#include "skills/cylinder_volume.h"
#include "skills/sphere_volume.h"
#include "skills/cone_volume.h"
#include "db.h"
#include "fsrs.h"

/**
 * Returns a version of the input string with all spaces removed. Used in comparing user guesses with correct answers
 *
 * @param input The string from which to remove spaces
 * @return The input string with spaces removed
 */
std::string return_spaceless_string(std::string input){
        std::string output = "";
        for(int i = 0; i < input.size(); i++){
                if(input[i] != ' '){
                       output = output + input[i]; 
                }
        }
        return output;
}


/**
 * Updates stability, difficulty, and retrievability for a skill based off of whether or not the user guessed correctly
 *
 * @param skill_id The id number for the skill to be updated
 * @param grade An integer representing whether or not the user got the solution correctly
 * @return 0
 */
int update_fsrs_on_answer(int skill_id, int grade)
{
        auto now = std::chrono::system_clock::now();
        time_t review_time = std::chrono::system_clock::to_time_t(now);

        float current_stability = get_skill_value(skill_id, "STABILITY");
        float current_difficulty = get_skill_value(skill_id, "DIFFICULTY");
        float current_retrievability = get_skill_value(skill_id, "RETRIEVABILITY");
        
        if(current_stability == -1){
                initialize_stability(skill_id, grade);
                current_stability = get_skill_value(skill_id, "STABILITY");
        } else if(grade == 3){
                update_stability_after_recall(skill_id, grade, current_difficulty, current_stability, current_retrievability);
        } else if(grade == 1){
                update_stability_after_lapse(skill_id, current_difficulty, current_stability, current_retrievability);
        } else{
                std::cout << "Invalid grade inputted to update_fsrs_on_answer" << std::endl;
        }

        if(current_difficulty == -1){
                initialize_difficulty(skill_id, grade);
                current_difficulty = get_skill_value(skill_id, "DIFFICULTY");
        } else{
                update_difficulty(skill_id, current_difficulty, grade);
        }

        update_last_review_time(skill_id, std::to_string(review_time));
        if(grade == 3){
                update_retrievability_on_review(skill_id);
        }
        return 0;
}

/**
 * Determines whether or not the skill is due or not
 *
 * @param skill_id The id number for the skill to be updated
 * @return 0 for due, 1 for learnt, 2 for not learnt
 */
int get_skill_status(int skill_id){
        float current_retrievability = get_skill_value(skill_id, "RETRIEVABILITY");
        if(current_retrievability >= 0.90){
                // The int get_skill_status returns indicates which collapsible pane the skill should be in.
                // 0 for due, 1 for not due, 2 for not learnt
                return 1;
        } else if(current_retrievability == -1){
                return 2;
        } else{
                return 0;
        }
}

/**
 * Prints to console attributes of specified skill
 *
 * @param skill_id The id number for the skill to be updated
 * @return 0
 */
int print_skill_info(int skill_id){
        std::cout << std::endl << "print_skill_info section" << std::endl;
        float current_stability = get_skill_value(skill_id, "STABILITY");
        float current_difficulty = get_skill_value(skill_id, "DIFFICULTY");
        float current_retrievability = get_skill_value(skill_id, "RETRIEVABILITY");
        float current_last_review_time = get_skill_value(skill_id, "LAST_REVIEW_TIME");
        std::cout << "For skill_id " << std::to_string(skill_id) << ":" << std::endl; 
        std::cout << "Current stability = " << std::to_string(current_stability) << std::endl;
        std::cout << "Current difficulty = " << std::to_string(current_difficulty) << std::endl;
        std::cout << "Current retrievability = " << std::to_string(current_retrievability) << std::endl;
        std::cout << "Current last review time = " << std::to_string(current_last_review_time) << std::endl;
        return 0;
}

/**
 * Gets attributes of specified skill
 *
 * @param skill_id The id number for the skill to be updated
 * @return A string with the attributes of the specified skill
 */
std::string get_skill_info(int skill_id){
        float current_stability = get_skill_value(skill_id, "STABILITY");
        float current_difficulty = get_skill_value(skill_id, "DIFFICULTY");
        float current_retrievability = get_skill_value(skill_id, "RETRIEVABILITY");
        float current_last_review_time = get_skill_value(skill_id, "LAST_REVIEW_TIME");
        std::string skill_info = "For skill_id " + std::to_string(skill_id) + ":\n"; 
        skill_info = skill_info + "Current stability = " + std::to_string(current_stability) + "\n";
        skill_info = skill_info + "Current difficulty = " + std::to_string(current_difficulty) + "\n";
        skill_info = skill_info + "Current retrievability = " + std::to_string(current_retrievability) + "\n";
        skill_info = skill_info + "Current last review time = " + std::to_string(current_last_review_time) + "\n";
        return skill_info;
}

/**
 * Maps from skill id to appropriate problem generation function
 *
 * @param skill_id The id number for the skill to be updated
 * @return A pointer to an array with three strings: the problem, the solution, and notes for entry
 */
std::string* generate_problem(int skill_id)
{
        std::string* problem_array = new std::string[3]; 
        switch (skill_id){
                case 1:
                        problem_array = generate_addition_problem();
                        break;
                case 2:
                        problem_array = generate_subtraction_problem();
                        break;
                case 3:
                        problem_array = generate_multiplication_problem();
                        break;
                case 4:
                        problem_array = generate_power_rule_problem();
                        break;
                case 5:
                        problem_array = generate_fraction_addition_problem();
                        break;
                case 6:
                        problem_array = generate_two_by_two_det_problem();
                        break;
                case 7:
                        problem_array = generate_three_by_three_det_problem();
                        break;
                case 8:
                        problem_array = generate_quadratic_formula_problem();
                        break;
                case 9:
                        problem_array = generate_product_rule_problem();
                        break;
                case 10:
                        problem_array = generate_sin_values_problem();
                        break;
                case 11:
                        problem_array = generate_cos_values_problem();
                        break;
                case 12:
                        problem_array = generate_tan_values_problem();
                        break;
                case 13:
                        problem_array = generate_two_by_two_matrix_multiplication_problem();
                        break;
                case 14:
                        problem_array = generate_matrix_vector_multiplication_problem();
                        break;
                case 15:
                        problem_array = generate_triangle_area_problem();
                        break;
                case 16:
                        problem_array = generate_circle_area_problem();
                        break;
                case 17:
                        problem_array = generate_integration_power_rule_problem();
                        break;
                case 18:
                        problem_array = generate_trig_deriv_problem();
                        break;
                case 19:
                        problem_array = generate_pythagorean_theorem_problem();
                        break;
                case 20:
                        problem_array = generate_partial_derivatives_problem();
                        break;
                case 21:
                        problem_array = generate_cuboid_volume_problem();
                        break;
                case 22:
                        problem_array = generate_triangular_prism_volume_problem();
                        break;
                case 23:
                        problem_array = generate_cylinder_volume_problem();
                        break;
                case 24:
                        problem_array = generate_sphere_volume_problem();
                        break;
                case 25:
                        problem_array = generate_cone_volume_problem();
                        break;


                default:
                        int base_skill_id = get_skill_value(skill_id, "BASE_SKILL_ID");
                        switch (base_skill_id){
                                case 1:
                                        problem_array = generate_addition_problem();
                                        break;
                                case 2:
                                        problem_array = generate_subtraction_problem();
                                        break;
                                case 3:
                                        problem_array = generate_multiplication_problem();
                                        break;
                                case 4:
                                        problem_array = generate_power_rule_problem();
                                        break;
                                case 5:
                                        problem_array = generate_fraction_addition_problem();
                                        break;
                                case 6:
                                        problem_array = generate_two_by_two_det_problem();
                                        break;
                                case 7:
                                        problem_array = generate_three_by_three_det_problem();
                                        break;
                                case 8:
                                        problem_array = generate_quadratic_formula_problem();
                                        break;
                                case 9:
                                        problem_array = generate_product_rule_problem();
                                        break;
                                case 10:
                                        problem_array = generate_sin_values_problem();
                                        break;
                                case 11:
                                        problem_array = generate_cos_values_problem();
                                        break;
                                case 12:
                                        problem_array = generate_tan_values_problem();
                                        break;
                                case 13:
                                        problem_array = generate_two_by_two_matrix_multiplication_problem();
                                        break;
                                case 14:
                                        problem_array = generate_matrix_vector_multiplication_problem();
                                        break;
                                case 15:
                                        problem_array = generate_triangle_area_problem();
                                        break;
                                case 16:
                                        problem_array = generate_circle_area_problem();
                                        break;
                                case 17:
                                        problem_array = generate_integration_power_rule_problem();
                                        break;
                                case 18:
                                        problem_array = generate_trig_deriv_problem();
                                        break;
                                case 19:
                                        problem_array = generate_pythagorean_theorem_problem();
                                        break;
                                case 20:
                                        problem_array = generate_partial_derivatives_problem();
                                        break;
                                case 21:
                                        problem_array = generate_cuboid_volume_problem();
                                        break;
                                case 22:
                                        problem_array = generate_triangular_prism_volume_problem();
                                        break;
                                case 23:
                                        problem_array = generate_cylinder_volume_problem();
                                        break;
                                case 24:
                                        problem_array = generate_sphere_volume_problem();
                                        break;
                                case 25:
                                        problem_array = generate_cone_volume_problem();
                                        break;

                                default:
                                        throw std::invalid_argument("generate problem received invalid skill_id");
                                        break;
                        }
        }
        return problem_array;
}

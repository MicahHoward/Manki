#include <iostream>
#include <cmath>
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
#include "db.h"
#include "fsrs.h"
#include "latexpp/latex.hpp"

std::string return_spaceless_string(std::string input){
        std::string output = "";
        for(int i = 0; i < input.size(); i++){
                if(input[i] != ' '){
                       output = output + input[i]; 
                }
        }
        return output;
}

int generate_latex_image(std::string expression)
{
	// Single class
	Latex latex;

	// Convert to PNG, store in 'problem.png'
    std::cout << "made it to to_png\n";
	latex.to_png(expression, "problem.png");

    std::cout << "made it past to_png\n";

	// Convert to HTML, returns a HTML snippet
	std::string html = latex.to_html(expression);
    return 0;
}

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

std::string* generate_problem(int skill_id)
{
        std::string* problem_and_solution = new std::string[2]; 
        switch (skill_id){
                case 1:
                        problem_and_solution = generate_addition_problem();
                        break;
                case 2:
                        problem_and_solution = generate_subtraction_problem();
                        break;
                case 3:
                        problem_and_solution = generate_multiplication_problem();
                        break;
                case 4:
                        problem_and_solution = generate_power_rule_problem();
                        break;
                case 5:
                        problem_and_solution = generate_fraction_addition_problem();
                        break;
                case 6:
                        problem_and_solution = generate_two_by_two_det_problem();
                        break;
                case 7:
                        problem_and_solution = generate_three_by_three_det_problem();
                        break;
                case 8:
                        problem_and_solution = generate_quadratic_formula_problem();
                        break;
                case 9:
                        problem_and_solution = generate_product_rule_problem();
                        break;
                case 10:
                        problem_and_solution = generate_sin_values_problem();
                        break;
                case 11:
                        problem_and_solution = generate_cos_values_problem();
                        break;
                case 12:
                        problem_and_solution = generate_tan_values_problem();
                        break;
                case 13:
                        problem_and_solution = generate_two_by_two_matrix_multiplication_problem();
                        break;
                case 14:
                        problem_and_solution = generate_matrix_vector_multiplication_problem();
                        break;
                case 15:
                        problem_and_solution = generate_triangle_area_problem();
                        break;
                case 16:
                        problem_and_solution = generate_circle_area_problem();
                        break;
                case 17:
                        problem_and_solution = generate_integration_power_rule_problem();
                        break;
                case 18:
                        problem_and_solution = generate_trig_deriv_problem();
                        break;
                case 19:
                        problem_and_solution = generate_pythagorean_theorem_problem();
                        break;
                case 20:
                        problem_and_solution = generate_partial_derivatives_problem();
                        break;

                default:
                        int base_skill_id = get_skill_value(skill_id, "BASE_SKILL_ID");
                        switch (base_skill_id){
                                case 1:
                                        problem_and_solution = generate_addition_problem();
                                        break;
                                case 2:
                                        problem_and_solution = generate_subtraction_problem();
                                        break;
                                case 3:
                                        problem_and_solution = generate_multiplication_problem();
                                        break;
                                case 4:
                                        problem_and_solution = generate_power_rule_problem();
                                        break;
                                case 5:
                                        problem_and_solution = generate_fraction_addition_problem();
                                        break;
                                case 6:
                                        problem_and_solution = generate_two_by_two_det_problem();
                                        break;
                                case 7:
                                        problem_and_solution = generate_three_by_three_det_problem();
                                        break;
                                case 8:
                                        problem_and_solution = generate_quadratic_formula_problem();
                                        break;
                                case 9:
                                        problem_and_solution = generate_product_rule_problem();
                                        break;
                                case 10:
                                        problem_and_solution = generate_sin_values_problem();
                                        break;
                                case 11:
                                        problem_and_solution = generate_cos_values_problem();
                                        break;
                                case 12:
                                        problem_and_solution = generate_tan_values_problem();
                                        break;
                                case 13:
                                        problem_and_solution = generate_two_by_two_matrix_multiplication_problem();
                                        break;
                                case 14:
                                        problem_and_solution = generate_matrix_vector_multiplication_problem();
                                        break;
                                case 15:
                                        problem_and_solution = generate_triangle_area_problem();
                                        break;
                                case 16:
                                        problem_and_solution = generate_circle_area_problem();
                                        break;
                                case 17:
                                        problem_and_solution = generate_integration_power_rule_problem();
                                        break;
                                case 18:
                                        problem_and_solution = generate_trig_deriv_problem();
                                        break;
                                case 19:
                                        problem_and_solution = generate_pythagorean_theorem_problem();
                                        break;
                                case 20:
                                        problem_and_solution = generate_partial_derivatives_problem();
                                        break;

                                default:
                                        throw std::invalid_argument("generate problem received invalid skill_id");
                                        break;
                        }
        }
        return problem_and_solution;
}

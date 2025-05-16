#include <sqlite3.h>
#include <iostream>

/**
 * Attempts to open "../data/manki.db" and create a table for skills in it.
 * @return 0 on success, -1 on failure
 */
int initialize_database()
{
        sqlite3* DB;
        std::string sql("CREATE TABLE SKILL("
                     "ID INT PRIMARY KEY    NOT NULL, "
                     "NAME TEXT             NOT NULL, " 
                     "RETRIEVABILITY FLOAT NOT NULL,"
                     "STABILITY FLOAT NOT NULL,"
                     "DIFFICULTY FLOAT NOT NULL,"
                     "LAST_REVIEW_TIME INT NOT NULL,"
                     "PROBLEM_TIME FLOAT NOT NULL,"
                     "RETAINING TEXT NOT NULL,"
                     "TIME FLOAT NOT NULL,"
                     "BASE_SKILL_ID INT NOT NULL,"
                     "CATEGORY TEXT NOT NULL);");
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 
        
        char* message_error;
        sqlite3_exec(DB, sql.c_str(), NULL, 0, &message_error);  
        
        if(exit != SQLITE_OK){
                std::cerr << "Error creating table!" << std::endl;
                sqlite3_free(message_error);
        } 

        sqlite3_close(DB);
        return 0;
}

/**
 * Inserts default values into SKILL table in "../data/manki.db"
 * @return 0 on success, -1 on failure
 */
int insert_default_values()
{
        sqlite3* DB;
        char* message_error;
        std::string sql("INSERT INTO SKILL VALUES(1, 'Addition', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Arthimetic');"
                   "INSERT INTO SKILL VALUES(2, 'Subtraction', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Arthimetic');"
                   "INSERT INTO SKILL VALUES(3, 'Multiplication', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Arthimetic');"
                   "INSERT INTO SKILL VALUES(4, 'Power Rule', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Calculus');"
                   "INSERT INTO SKILL VALUES(5, 'Fraction Addition', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Arthimetic');"
                   "INSERT INTO SKILL VALUES(6, '2x2 Matrix Determinants', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Linear Algebra');"
                   "INSERT INTO SKILL VALUES(7, '3x3 Matrix Determinants', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Linear Algebra');"
                   "INSERT INTO SKILL VALUES(8, 'Quadratic Formula', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Algebra');"
                   "INSERT INTO SKILL VALUES(9, 'Product Rule', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Calculus');"
                   "INSERT INTO SKILL VALUES(10, 'Sin Values', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Trigonometry');"
                   "INSERT INTO SKILL VALUES(11, 'Cos Values', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Trigonometry');"
                   "INSERT INTO SKILL VALUES(12, 'Tan Values', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Trigonometry');"
                   "INSERT INTO SKILL VALUES(13, '2x2 Matrix Multiplication', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Linear Algebra');"
                   "INSERT INTO SKILL VALUES(14, 'Matrix Vector Multiplication', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Linear Algebra');"
                   "INSERT INTO SKILL VALUES(15, 'Triangle Area', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Geometry');"
                   "INSERT INTO SKILL VALUES(16, 'Circle Area', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Geometry');"
                   "INSERT INTO SKILL VALUES(17, 'Integration Power Rule', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Calculus');"
                   "INSERT INTO SKILL VALUES(18, 'Derivatives of Trigonometric Functions', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Calculus');"
                   "INSERT INTO SKILL VALUES(19, 'Pythagorean Theorem', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Geometry');"
                   "INSERT INTO SKILL VALUES(20, 'Partial Derivatives', 0, 0, 0, 0, 10, 'FALSE', 0.0, 0, 'Calculus');");

        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &message_error);
        if(exit != SQLITE_OK){
                std::cerr << "Error inserting to table!" << std::endl;
                sqlite3_free(message_error);
                return 1;
        } else{
                std::cout << "Insertion has done completed!" << std::endl;
        }
        sqlite3_close(DB);
        return 0;
}

/**
 * Callback function for read_database
 *
 * @return 0
 */
static int read_database_callback(void* data, int argc, char** argv, char** az_col_name)
{
        int i;
        fprintf(stderr, "%s: ", (const char*)data);

        for(i = 0; i < argc; i++){
                printf("%s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");
        }

        printf("\n");
        return 0;
}

/**
 * Prints out all data in SKILL table in "../data/manki.db" 
 *
 * @return 0 on success, -1 on failure
 */
int read_database()
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT * FROM SKILL;");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } else{
                std::cout << "DB opened successfully!" << std::endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), read_database_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error selecting!" << std::endl;
                return -1;
        } else{
                std::cout << "Selection completed!" << std::endl;
        }

        sqlite3_close(DB);
        return 0;
}
// Global variable so that it can be shared between get_number_of_skills_callback and get_number_of_skills
int number_of_skills = 0;
/**
 * Callback function for get_number_of_skills
 */
static int get_number_of_skills_callback(void* data, int argc, char** argv, char** az_col_name)
{
        number_of_skills++;
        return 0;
}

/**
 * Counts the number of skills in the SKILL table in "../data/manki.db"
 *
 * @return the number of skills found in the SKILL table
 */
int get_number_of_skills()
{
        if(number_of_skills != 0){
                return number_of_skills;
        }
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT * FROM SKILL;");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_number_of_skills_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error selecting!" << std::endl;
                return -1;
        } 
        sqlite3_close(DB);
        return number_of_skills;
}

// Global variable so that it can be shared between get_skill_value_callback and get_skill_value
float current_skill_value;

/**
 * Callback function for get_skill_value
 *
 * @return 0 
 */
static int get_skill_value_callback(void* data, int argc, char** argv, char** az_col_name)
{
        current_skill_value = atof(argv[0]) ? atof(argv[0]) : -1;
        return 0;
}

/**
 * Gets a decimal value from a specifed skill
 *
 * @param skill_id The id number for the skill to be accessed 
 * @param attribute The attribute of the skill to be accessed
 * @return The float for the specified value from the specified skill 
 */
float get_skill_value(int skill_id, std::string attribute)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT " + attribute + " FROM SKILL WHERE ID = " + std::to_string(skill_id) + ";");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_value_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error retrieving skill value!" << std::endl;
                return -1;
        } 
  
        float intermediate_variable = current_skill_value;

        sqlite3_close(DB);
        return intermediate_variable;
}

// TODO: get_skill_name, get_skill_category, and get_skill_retaining should be placed with a text version of get_skill_value
// Global variable to be shared between get_skill_name_callback and get_skill_name
std::string current_skill_name;
// Callback function for get_skill_name
static int get_skill_name_callback(void* data, int argc, char** argv, char** az_col_name)
{
        current_skill_name= argv[0];
        return 0;
}

/**
 * Gets the text from the NAME attribute for a specified skill
 *
 * @param skill_id The id number for the skill to be accessed
 * @return The string representing the NAME attribute
 */
std::string get_skill_name(int skill_id)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT NAME FROM SKILL WHERE ID = " + std::to_string(skill_id) + ";");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return "";
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_name_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error retrieving skill name!" << std::endl;
                return "";
        } 
  
        std::string intermediate_variable = current_skill_name;

        sqlite3_close(DB);
        return intermediate_variable;
}

// Global variable to be shared between get_skill_category_callback and get_skill_category
std::string current_skill_category;

// Callback function for get_skill_category
static int get_skill_category_callback(void* data, int argc, char** argv, char** az_col_name)
{
        current_skill_category = argv[0];
        return 0;
}

/**
 * Gets the CATEGORY attribute for a specified skill
 *
 * @param skill_id The id number for the skill to be accessed
 * @return A string representing the CATEGORY attribute of the accessed skill
 */
std::string get_skill_category(int skill_id)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT CATEGORY FROM SKILL WHERE ID = " + std::to_string(skill_id) + ";");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return "";
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_category_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error retrieving skill category!" << std::endl;
                return "";
        } 
  
        std::string intermediate_variable = current_skill_category;

        sqlite3_close(DB);
        return intermediate_variable;
}

// Global variable to be shared between get_skill_retaining_callback and get_skill_retaining
std::string current_skill_retaining;

// Callback function for get_skill_retaining
static int get_skill_retaining_callback(void* data, int argc, char** argv, char** az_col_retaining)
{
        current_skill_retaining = argv[0];
        return 0;
}

/**
 * Gets the RETAINING attribute for a specified skill
 *
 * @param skill_id The id number for the skill to be accessed
 * @return A string representing the RETAINING attribute of the accessed skill
 */
std::string get_skill_retaining(int skill_id)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT RETAINING FROM SKILL WHERE ID = " + std::to_string(skill_id) + ";");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return "";
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_retaining_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error retrieving skill retaining!" << std::endl;
                return "";
        } 
  
        std::string intermediate_variable = current_skill_retaining;

        sqlite3_close(DB);
        return intermediate_variable;
}

/**
 * Gets a list of skill names by calling get_number_of_skills on all utilized ids
 *
 * @return A pointer to an array of skill names
 */
std::string* get_skill_names(){
            int number_of_skills = get_number_of_skills();
            std::string* skill_names = new std::string[number_of_skills];
            for(int i = 0; i < number_of_skills; i++){
                    skill_names[i] = get_skill_name(i+1);
            }
            return skill_names;
}

/**
 * Updates a specified numerical attribute for a specified skill to a new value
 *
 * @param skill_id The id number specifying which skill to update
 * @param attribute A string specifiying which attribute of the skill to update
 * @param new_value A float for the updated value of that skill
 * @return 0 on success, -1 on failure
 */
int update_skill_value(int skill_id, std::string attribute, float new_value)
{
        sqlite3* DB;
        char* message_error;
        std::string sql("UPDATE SKILL SET " + attribute + " = '" + std::to_string(new_value) + "' WHERE ID = " + std::to_string(skill_id) + ";");

        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &message_error);
        if(exit != SQLITE_OK){
                std::cerr << "Error updating skill value!" << std::endl;
                sqlite3_free(message_error);
        } 

        sqlite3_close(DB);
        return 0;
}

/**
 * Updates a specified text attribute for a specified skill to a new value
 *
 * @param skill_id The id number specifying which skill to update
 * @param attribute A string specifiying which attribute of the skill to update
 * @param new_value A string for the updated value of that skill
 * @return 0 on success, -1 on failure
 */
int update_skill_value(int skill_id, std::string attribute, std::string new_value)
{
        sqlite3* DB;
        char* message_error;
        std::string sql("UPDATE SKILL SET " + attribute + " = '" + new_value + "' WHERE ID = " + std::to_string(skill_id) + ";");

        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } else{
                std::cout << "DB opened successfully!" << std::endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &message_error);
        if(exit != SQLITE_OK){
                std::cerr << "Error updating skill value!" << std::endl;
                sqlite3_free(message_error);
        } else{
                std::cout << "Skill value update completed!" << std::endl;
        }

        sqlite3_close(DB);
        return 0;
}

/**
 * Inserts a new timed version of skill into the database
 *
 * @param base_skill_id The id number for the non-timed version of the skill
 * @param time_in_milliseconds The time limit for the timed skill in milliseconds
 * @return On success, the id number for the new skill; on failure, -1
 */
int insert_timed_skill(int base_skill_id, int time_in_milliseconds)
{
        sqlite3* DB;
        char* message_error;
        std::string new_skill_name = "Timed " + get_skill_name(base_skill_id);
        int new_skill_id = get_number_of_skills() + 1;
        std::cout << std::to_string(new_skill_id) + "\n";
        std::string sql("INSERT INTO SKILL VALUES(" + std::to_string(new_skill_id) + ", '" + new_skill_name + "', -1, -1, -1, -1, 10, 'FALSE', " + std::to_string(time_in_milliseconds) + ", " + std::to_string(base_skill_id) + ");");

        std::cout << sql.c_str() + '\n';
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &message_error);
        if(exit != SQLITE_OK){
                std::cerr << "Error inserting to table!" << sqlite3_errmsg(DB) << std::endl;
                sqlite3_free(message_error);
                return -1;
        } else{
                std::cout << "Insertion has done completed!" << std::endl;
        }
        sqlite3_close(DB);
        return new_skill_id;
}



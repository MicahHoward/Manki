#include <sqlite3.h>
#include <iostream>

static int callback(void* data, int argc, char** argv, char** azColName)
{
        int i;
        fprintf(stderr, "%s: ", (const char*)data);

        for(i = 0; i < argc; i++){
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }

        printf("\n");
        return 0;
}

int numberOfSkills = 0;
static int get_number_of_skills_callback(void* data, int argc, char** argv, char** azColName)
{
        numberOfSkills++;
        return 0;
}

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
                     "PROBLEM_TIME FLOAT NOT NULL);");
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 
        //else{
        //       std::cout << "DB opened successfully!" << std::endl;
        //}
        
        char* messageError;
        sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);  
        
        if(exit != SQLITE_OK){
                std::cerr << "Error creating table!" << std::endl;
                sqlite3_free(messageError);
        } 
        //else{
        //        std::cout << "Table created succesfully!" << std::endl;
        //}

        sqlite3_close(DB);
        return 0;
}

int insert_default_values()
{
        sqlite3* DB;
        char* messageError;
        std::string sql("INSERT INTO SKILL VALUES(1, 'Addition', -1, -1, -1, -1, 10);"
                   "INSERT INTO SKILL VALUES(2, 'Subtraction', -1, -1, -1, -1, 10);"
                   "INSERT INTO SKILL VALUES(3, 'Multiplication', -1, -1, -1, -1, 10);"
                   "INSERT INTO SKILL VALUES(4, 'Power Rule', -1, -1, -1, -1, 10);"
                   "INSERT INTO SKILL VALUES(5, 'Fraction Addition', -1, -1, -1, -1, 10);"
                   "INSERT INTO SKILL VALUES(6, '2x2 Matrix Determinants', -1, -1, -1, -1, 10);"
                   "INSERT INTO SKILL VALUES(7, '3x3 Matrix Determinants', -1, -1, -1, -1, 10);");

        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 
        //else{
        //        std::cout << "DB opened successfully!" << std::endl;
        //}

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(exit != SQLITE_OK){
                std::cerr << "Error inserting to table!" << std::endl;
                sqlite3_free(messageError);
        } else{
                std::cout << "Insertion has done completed!" << std::endl;
        }
        return 0;
}

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

        exit = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error selecting!" << std::endl;
                return -1;
        } else{
                std::cout << "Selection completed!" << std::endl;
        }
        return 0;
}

int get_number_of_skills()
{
        if(numberOfSkills != 0){
                return numberOfSkills;
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
        //else{
         //       std::cout << "DB opened successfully!" << std::endl;
        //}

        exit = sqlite3_exec(DB, sql.c_str(), get_number_of_skills_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error selecting!" << std::endl;
                return -1;
        } 
        //else{
         //       std::cout << "Selection completed!" << std::endl;
        //}
        return numberOfSkills;
}

float currentSkillValue;
static int get_skill_value_callback(void* data, int argc, char** argv, char** azColName)
{
        currentSkillValue = atof(argv[0]) ? atof(argv[0]) : -1;
        return 0;
}

float get_skill_value(int skillID, std::string attribute)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT " + attribute + " FROM SKILL WHERE ID = " + std::to_string(skillID) + ";");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_value_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error retrieving skill value!" << std::endl;
                return -1;
        } 
  
        float intermediateVariable = currentSkillValue;
        return intermediateVariable;
}

std::string currentSkillName;
static int get_skill_name_callback(void* data, int argc, char** argv, char** azColName)
{
        currentSkillName= argv[0];
        return 0;
}

std::string get_skill_name(int skillID)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        std::string data("CALLBACK FUNCTION");

        std::string sql("SELECT NAME FROM SKILL WHERE ID = " + std::to_string(skillID) + ";");

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return "";
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_name_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                std::cerr << "Error retrieving skill name!" << std::endl;
                return "";
        } 
  
        std::string intermediateVariable = currentSkillName;
        return intermediateVariable;
}

std::string* get_skill_names(){
            int number_of_skills = get_number_of_skills();
            std::string* skill_names = new std::string[number_of_skills];
            for(int i = 0; i < number_of_skills; i++){
                    skill_names[i] = get_skill_name(i+1);
            }
            return skill_names;
}

int update_skill_value(int skillID, std::string attribute, float newValue)
{
        sqlite3* DB;
        char* messageError;
        std::string sql("UPDATE SKILL SET " + attribute + " = '" + std::to_string(newValue) + "' WHERE ID = " + std::to_string(skillID) + ";");


        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } 
        //else{
        //       std::cout << "DB opened successfully!" << std::endl;
        //}

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(exit != SQLITE_OK){
                std::cerr << "Error updating skill value!" << std::endl;
                sqlite3_free(messageError);
        } else{
                std::cout << "Skill value update completed!" << std::endl;
        }
        return 0;
}
int update_skill_value(int skillID, std::string attribute, std::string newValue)
{
        sqlite3* DB;
        char* messageError;
        std::string sql("UPDATE SKILL SET " + attribute + " = '" + newValue + "' WHERE ID = " + std::to_string(skillID) + ";");


        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
                return -1;
        } else{
                std::cout << "DB opened successfully!" << std::endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(exit != SQLITE_OK){
                std::cerr << "Error updating skill value!" << std::endl;
                sqlite3_free(messageError);
        } else{
                std::cout << "Skill value update completed!" << std::endl;
        }
        return 0;
}

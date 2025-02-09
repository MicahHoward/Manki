#include <sqlite3.h>
#include <iostream>
using namespace std;

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

int numberOfSkills;
static int get_number_of_skills_callback(void* data, int argc, char** argv, char** azColName)
{
        numberOfSkills++;
        return 0;
}

int initialize_database()
{
        sqlite3* DB;
        string sql("CREATE TABLE SKILL("
                     "ID INT PRIMARY KEY    NOT NULL, "
                     "NAME TEXT             NOT NULL, " 
                     "RETRIEVABILITY FLOAT NOT NULL,"
                     "STABILITY FLOAT NOT NULL,"
                     "DIFFICULTY FLOAT NOT NULL,"
                     "LAST_REVIEW_TIME INT NOT NULL);");
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } else{
                cout << "DB opened successfully!" << endl;
        }
        
        char* messageError;
        sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);  
        
        if(exit != SQLITE_OK){
                cerr << "Error creating table!" << endl;
                sqlite3_free(messageError);
        } else{
                cout << "Table created succesfully!" << endl;
        }

        sqlite3_close(DB);
        return 0;
}

int insert_default_values()
{
        sqlite3* DB;
        char* messageError;
        string sql("INSERT INTO SKILL VALUES(1, 'Addition', -1, -1, -1, -1);"
                   "INSERT INTO SKILL VALUES(2, 'Subtraction', -1, -1, -1, -1);"
                   "INSERT INTO SKILL VALUES(3, 'Multiplication', -1, -1, -1, -1);");


        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } else{
                cout << "DB opened successfully!" << endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(exit != SQLITE_OK){
                cerr << "Error inserting to table!" << endl;
                sqlite3_free(messageError);
        } else{
                cout << "Insertion completed!" << endl;
        }
        return 0;
}

int read_database()
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        string data("CALLBACK FUNCTION");

        string sql("SELECT * FROM SKILL;");

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } else{
                cout << "DB opened successfully!" << endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                cerr << "Error selecting!" << endl;
                return -1;
        } else{
                cout << "Selection completed!" << endl;
        }
        return 0;
}

int get_number_of_skills()
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        string data("CALLBACK FUNCTION");

        string sql("SELECT * FROM SKILL;");

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } else{
                cout << "DB opened successfully!" << endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), get_number_of_skills_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                cerr << "Error selecting!" << endl;
                return -1;
        } else{
                cout << "Selection completed!" << endl;
        }
        return numberOfSkills;
}

float currentSkillValue;
static int get_skill_value_callback(void* data, int argc, char** argv, char** azColName)
{
        currentSkillValue = atof(argv[0]) ? atof(argv[0]) : -1;
        return 0;
}

float get_skill_value(int skillID, string attribute)
{
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);
        string data("CALLBACK FUNCTION");

        string sql("SELECT " + attribute + " FROM SKILL WHERE ID = " + to_string(skillID) + ";");

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } 

        exit = sqlite3_exec(DB, sql.c_str(), get_skill_value_callback, (void*)data.c_str(), NULL);
        if(exit != SQLITE_OK){
                cerr << "Error retrieving skill value!" << endl;
                return -1;
        } 
  
        float intermediateVariable = currentSkillValue;
        return intermediateVariable;
}

int update_skill_value(int skillID, string attribute, float newValue)
{
        sqlite3* DB;
        char* messageError;
        string sql("UPDATE SKILL SET " + attribute + " = '" + to_string(newValue) + "' WHERE ID = " + to_string(skillID) + ";");


        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } else{
                cout << "DB opened successfully!" << endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(exit != SQLITE_OK){
                cerr << "Error updating skill value!" << endl;
                sqlite3_free(messageError);
        } else{
                cout << "Skill value update completed!" << endl;
        }
        return 0;
}
int update_skill_value(int skillID, string attribute, string newValue)
{
        sqlite3* DB;
        char* messageError;
        string sql("UPDATE SKILL SET " + attribute + " = '" + newValue + "' WHERE ID = " + to_string(skillID) + ";");


        int exit = 0;
        exit = sqlite3_open("../data/manki.db", &DB);

        if(exit){
                cerr << "Error opening DB " << sqlite3_errmsg(DB) << endl; 
                return -1;
        } else{
                cout << "DB opened successfully!" << endl;
        }

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(exit != SQLITE_OK){
                cerr << "Error updating skill value!" << endl;
                sqlite3_free(messageError);
        } else{
                cout << "Skill value update completed!" << endl;
        }
        return 0;
}

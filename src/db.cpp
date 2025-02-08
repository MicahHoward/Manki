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

int initialize_database()
{
        sqlite3* DB;
        string sql = "CREATE TABLE SKILL("
                     "ID INT PRIMARY KEY    NOT NULL, "
                     "NAME TEXT             NOT NULL);"; 
        int exit = 0;
        exit = sqlite3_open("example.db", &DB);

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
        string sql("INSERT INTO SKILL VALUES(1, 'Addition');"
                   "INSERT INTO SKILL VALUES(2, 'Subtraction');"
                   "INSERT INTO SKILL VALUES(3, 'Multiplication');");


        int exit = 0;
        exit = sqlite3_open("example.db", &DB);

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
        exit = sqlite3_open("example.db", &DB);
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


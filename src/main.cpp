#include <iostream>
#include "skills/addition.h"
#include "skills/subtraction.h"
#include "skills/multiplication.h"
#include "db.h"
using namespace std;

int main()
{
        initialize_database();
        insert_default_values();
        read_database();
        int problemType;
        int* problem;
        string operand;
        cout << "What type of problem would you like?" << endl;
        cout << "Please enter 1 for addition, 2 for subtraction, or three for multiplication." << endl;
        cin >> problemType;

        if(problemType == 1){
                problem = generate_addition_problem();
                operand = "+";
        } else if(problemType == 2){
                problem = generate_subtraction_problem();
                operand = "-";
        } else if(problemType == 3){
                problem = generate_multiplication_problem();
                operand = "x";
        } else{
                cout << "Please enter 1, 2, or 3." << endl;
        }

        int firstNumber = problem[0];
        int secondNumber = problem[1];
        int sum = problem[2];
        
        int userGuess;

        cout << firstNumber << " " << operand << " " << secondNumber << " = ?" << endl;
        cin >> userGuess;

        if(userGuess == sum){
                cout << "Correct!" << endl;
        } else{
                cout << "Incorrect!" << endl;
        }

        cout << "You guessed " << userGuess << " and the answer was " << sum << "." << endl;

       return 0;
}



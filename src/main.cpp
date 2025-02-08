#include <iostream>
#include "skills/addition.h"
using namespace std;

int main()
{
        int* additionProblem = generate_problem();

        int firstNumber = additionProblem[0];
        int secondNumber = additionProblem[1];
        int sum = additionProblem[2];
        
        int userGuess;

        cout << firstNumber << " + " << secondNumber << " = ?" << endl;
        cin >> userGuess;

        if(userGuess == sum){
                cout << "Correct!" << endl;
        } else{
                cout << "Incorrect!" << endl;
        }

        cout << "You guessed " << userGuess << " and the answer was " << sum << "." << endl;

       return 0;
}

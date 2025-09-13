#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class Calculator {
public: 
    void startCalculation() {
        double currentNum;
        char operation;

       runningTotal = 0.0;

        cout << "Enter a number to begin: ";

        if (! (cin >> runningTotal)) {
            handleInvalidInput();
            return;
        }

        while (true) {
            cout << "Enter an operator (+, -, *, /) or '=' to finish, or 'Q' to quit: ";
            cin  >> operation;

            if (operation == '='){
                cout << "Final Result: " << runningTotal << endl;
                history.push_back(runningTotal);
                break;
            }
            else if (operation == 'Q'){
                cout << "Exiting Calculator. Goodbye!";
                runningTotal = 0.0;
                return;
            }

            cout << "Enter a number: ";
            if (!(cin >> currentNum)) {
                handleInvalidInput();
            }

            switch (operation) {
                case '+': 
                    runningTotal += currentNum;
                    break;
                case '-':
                    runningTotal -= currentNum;
                    break;
                case '*':
                    runningTotal *= currentNum;
                    break;
                case '/':
                    if (currentNum != 0){
                        runningTotal /= currentNum;
                    }
                    else {
                        cerr << "Error: Division by zero is not allowed";
                    }
                    break;
                default:
                    cout << "Invalid operator. Try again";
                    break;
                
                cout << "Current Total: " << runningTotal;

            }
        }
    }

    void displayHistory() const {
        if (history.empty()) {
            cout << "History is empty";
        }

        cout << "Calculation History: ";
        for (double result : history) {
            cout << result << endl;
        }
    }

    void saveHistoryToFile (const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& result : history) {
                file << result << endl;
            }
            file.close();
            cout << "Calculation history saved to " << filename << endl;
        } else {
            cerr << "Error: Could not open file for writing.\n";
        }
    }

    void loadHistoryFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            history.clear();
            double result;
            while (file >> result) {
                history.push_back(result);
            }
            file.close();
            cout << "Calculation history loaded from " << filename << endl;
        } else {
            cerr << "Note: No existing history file found. Starting with an empty history.\n";
        }
    }



private:
    vector<double> history;
    double runningTotal;

    void handleInvalidInput(){
        cin.clear();
        cin.ignore(numeric_limits <std:: streamsize>::max(), '\n');
        cerr << "Invalid input. Try again and enter a number: ";
    }
};

int main() {
    Calculator myCalculator;
    const string historyFilename = "calculator_history.txt";

    myCalculator.loadHistoryFromFile(historyFilename);

    char choice;
    do {
        cout << "Menu" << endl;
        cout << "S - Start a new calculation" << endl;
        cout << "H - Display History" << endl;
        cout << "Q - Quit" << endl;
        cout << "Enter your choice: ";
        cin >>  choice ;

        switch (choice) {
            case 'S':
            case 's': 
                myCalculator.startCalculation();
                break;
            case 'H':
            case 'h':
                myCalculator.displayHistory();
                break;
            case 'Q':
            case 'q':
                cout << "Saving History";
                myCalculator.saveHistoryToFile(historyFilename);
                return 0;
            default:
                cout << "Invalid Choice. Try again";
                break;
        }

    } while (true);

    return 0;
}

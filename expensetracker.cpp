#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Expense {

    string description;
    double amount;
};

class ExpenseTracker {

private:

    vector<Expense> expenses;

public:

    void addExpense(const Expense& expense) {
        expenses.push_back(expense);
        cout << "Expense added successfully."<<endl;
    }

    void viewTotalExpenses() const {
        double total = 0.0;
        for (const auto& expense : expenses) {
            total += expense.amount;
        }

        cout << "Total Expenses: $" << fixed << setprecision(2) << total << endl;
    }

    void viewAllExpenses() const {
        if (expenses.empty()) {
            cout << "No expenses recorded."<<endl;
            return;
        }

        cout << "List of Expenses:"<<endl;
        cout << setw(20) << left << "Description" << setw(10) << "Amount"<<endl;
        cout << setfill('-') << setw(1) << "\n" << setfill(' ');

        for (const auto& expense : expenses) {
            cout << setw(20) << left << expense.description << "$" << fixed << setprecision(2) << expense.amount << "\n";
        }
    }
};

int main() {
    ExpenseTracker expenseTracker;

    while (true) {
        cout << "\nExpense Tracker Menu:"<<endl;
        cout << "1. Add Expense"<<endl;
        cout << "2. View Total Expenses"<<endl;
        cout << "3. View All Expenses"<<endl;;
        cout << "4. Exit"<<endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                Expense newExpense;
                cout << "Enter expense description: ";
                cin.ignore();  
                getline(cin, newExpense.description);
                cout << "Enter expense amount: $";
                cin >> newExpense.amount;
                expenseTracker.addExpense(newExpense);
                break;
            }
            case 2:
                expenseTracker.viewTotalExpenses();
                break;
            case 3:
                expenseTracker.viewAllExpenses();
                break;
            case 4:
                cout << "Exiting Expense Tracker. Goodbye!"<<endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again."<<endl;
        }
    }

    return 0;
}


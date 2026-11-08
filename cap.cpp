
//XYZ bank atm interface
/*Author:   David Russell
            Shadrick Jones
*/
/*
==================================
==================================
Menu Options:
    checking the account balance,
    debiting the account
    crediting the account
    calculating savings interest
    exit program.
==================================
==================================
*/

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::fixed;
using std::setprecision;

// Function to pause the program
void pauseScreen() {
    cout << "\nPress enter to continue" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Function to clear the console screen
void clearScreen() {
    system("cls");
}

class BankAccount {
    private:
        double accountBalance = 0; 

    protected:
        // Function to deduct transaction fees from the account balance
        void deductFee(double fee) {
            accountBalance -= fee;
        }

    public:
        string accountHolderName; // Public member variable to store the account holder's name
        string accountNumber; // Public member variable to store the account number

        // Function to set the account balance
        void setBalance() {

            cout << "Enter initial account balance: ";

            if (!(cin >> accountBalance)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                accountBalance = 0;

                cout << "Invalid balance entered." << endl;
                pauseScreen();
                clearScreen();
                return;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // Set balance to 0 if it's less than 1000
            if (accountBalance < 1000) {
                accountBalance = 0; 

                cout << "The initial balance was invalid." << endl;
                pauseScreen();
                clearScreen();
            }
            //Displaying the Iniitial balance
            cout << "Initial balance is: $" << accountBalance << endl;
            pauseScreen();
            clearScreen();
        }

        //// Function to get and return account balance
        double getBalance() const {
            return accountBalance; 
        }

        // withdraw from the account
        virtual bool withdraw(double amount) {

            if (amount <= 0) {
                cout << "Invalid amount. Transaction declined." << endl;
                return false;
            }

            if (amount > accountBalance) {
                cout << "Debit amount exceeded account balance." << endl;
                return false;
            }

            accountBalance -= amount; // Deduct withdrawal amount from the account balance

            cout << "Withdrew $" << amount
                 << ". New balance: $" << accountBalance << endl;

            return true;// Successful withdrawal 
        }

        // deposit into the account
        double deposit(double amount) {

            if (amount <= 0) {
                cout << "Invalid amount. Transaction declined." << endl;
                return -1; // failed deposit
            }

            accountBalance += amount; // Add the amount to the account balance

            cout << "Deposited $" << amount
                 << ". New balance: $" << accountBalance << endl;

            return accountBalance; // successful deposit
        }

        // Virtual function for calculating interest
        virtual double calculateInterest() const {
            return 0.0;
        }

        // Virtual function to identify savings accounts
        virtual bool supportsInterest() const {
            return false;
        }

        void displayMenu() {
            // Function to display the menu options

            cout << "===============================" << endl;
            cout << "Welcome to XYZ Bank ATM " << accountHolderName << endl;
            cout << "Please select an option:" << endl;
            cout << "1. Account Balance" << endl;
            cout << "2. Withdraw " << endl;
            cout << "3. Deposit" << endl;
            cout << "4. Calculate Interest" << endl;
            cout << "5. Exit" << endl;
            cout << "===============================" << endl;
        }

        // Virtual destructor for the BankAccount base class
        virtual ~BankAccount() = default;

};

// Creating Savings Account Class that inherits from the BankAccount class and adds an interest rate.

class SavingsAccount : public BankAccount {

    private:
        double interestRate;

    public:

        // Constructor to initialize the savings account with an interest rate
        SavingsAccount(double rate) {
            interestRate = rate;
        }

        // Function to calculate the interest earned
        double calculateInterest() const override {
            return getBalance() * interestRate;
        }

        // Function to identify savings accounts
        bool supportsInterest() const override {
            return true;
        }
};

// Creating Checking Account Class that inherits from the BankAccount class and adds a transaction fee.

class CheckingAccount : public BankAccount {

    private:
        double transactionFee;

    public:

        // Constructor to initialize the checking account with a transaction fee
        CheckingAccount(double fee) {
            transactionFee = fee;
        }

        // Function to withdraw money and deduct a transaction fee
        bool withdraw(double amount) override {

            if (amount <= 0) {
                cout << "Invalid amount. Transaction declined." << endl;
                return false;
            }

            if (amount + transactionFee > getBalance()) {
                cout << "Insufficient funds to cover withdrawal and transaction fee." << endl;
                return false;
            }

            // Call the parent class withdrawal function
            if (BankAccount::withdraw(amount)) {

                // Deduct the transaction fee after a successful withdrawal
                deductFee(transactionFee);

                cout << "Transaction fee: $" << transactionFee << endl;
                cout << "Final account balance: $" << getBalance() << endl;

                return true;
            }

            return false;
        }
};

int main() {

    clearScreen();

    // Create the different account types
    SavingsAccount savingsAccount(0.02); // Savings interest rate of 2%
    CheckingAccount checkingAccount(25.00); // Checking transaction fee of $25

    BankAccount* account = nullptr; // Basse class 

    // Variable to store account type selection
    int accountType = 0; 

    // Variable to store the user's menu choice
    int choice = 0; 

    double creditAmount = 0; // Variable to store the amount to credit
    double debitAmount = 0; // Variable to store the amount to debit
    double balance = 0; // Variable to store the account balance

    while (accountType != 1 && accountType != 2) {

    cout << "===============================" << endl;
    cout << "Welcome to XYZ Bank ATM" << endl;
    cout << "Select Account Type:" << endl;
    cout << "1. Savings Account" << endl;
    cout << "2. Checking Account" << endl;
    cout << "===============================" << endl;

    cout << "Enter account type: ";

    if (!(cin >> accountType)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid input. Please enter 1 or 2." << endl;
        continue;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (accountType != 1 && accountType != 2) {
        cout << "\nInvalid account type. Please select 1 or 2." << endl;
        pauseScreen();
        clearScreen();}
    }   

    if (accountType == 1) {
        account = &savingsAccount;
    }
    else if (accountType == 2) {
        account = &checkingAccount;
    }

    account->accountHolderName = "David Russell";
    // account->accountNumber = "123";

    account->setBalance(); // Set initial balance

    while (choice != 5) { // Loop until the user chooses to exit

        clearScreen();

        account->displayMenu(); // Display the menu options

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number." << endl;
            pauseScreen();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        clearScreen();

        switch (choice) { // Handle the user's choice

            case 1:
                balance = account->getBalance(); // Display the account balance

                cout << "Your account balance is: $" << balance << endl;

                pauseScreen();
                break;

            case 2:
                cout << "Enter amount to withdraw: ";

                if (!(cin >> debitAmount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid withdrawal amount." << endl;
                    pauseScreen();
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Attempt to withdraw from the account
                account->withdraw(debitAmount);

                pauseScreen();
                break;

            case 3:
                cout << "Enter amount to deposit: ";

                if (!(cin >> creditAmount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid deposit amount." << endl;
                    pauseScreen();
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                // Attempt to deposit into the account
                account->deposit(creditAmount);

                pauseScreen();
                break;

            case 4:

                if (account->supportsInterest()) {

                    cout << "Your current balance is: $"
                         << account->getBalance() << endl;

                    cout << "Interest rate: 2%" << endl;

                    cout << "Interest earned: $"
                         << account->calculateInterest() << endl;
                }
                else {
                    cout << "Interest calculation is only available for Savings Accounts." << endl;
                }

                pauseScreen();
                break;

            case 5:
                cout << "Thank you for using XYZ Bank ATM. Goodbye!" << endl;
                pauseScreen();
                clearScreen();
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
                pauseScreen();
        }
    }

    return 0;
}

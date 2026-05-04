#include <iostream>
#include <fstream>
using namespace std;

class Account {
public:
    int accNo;
    char name[50];
    float balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() {
        cout << "Account No: " << accNo
             << " | Name: " << name
             << " | Balance: " << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    void deposit(float amt) {
        balance += amt;
    }

    void withdraw(float amt) {
        if (amt > balance)
            cout << " Insufficient Balance!\n";
        else {
            balance -= amt;
            cout << " Withdrawal Successful!\n";
        }
    }
};
void addAccount() {
    Account a;
    ofstream file("bank.dat", ios::binary | ios::app);

    a.createAccount();
    file.write((char*)&a, sizeof(a));

    file.close();
    cout << " Account Created!\n";
}
void displayAccounts() {
    Account a;
    ifstream file("bank.dat", ios::binary);

    cout << "\n--- Account Details ---\n";

    while (file.read((char*)&a, sizeof(a))) {
        a.display();
    }

    file.close();
}
void depositMoney(int accNo) {
    Account a;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == accNo) {
            float amt;
            cout << "Enter amount to deposit: ";
            cin >> amt;

            a.deposit(amt);

            file.seekp(-sizeof(a), ios::cur);
            file.write((char*)&a, sizeof(a));

            cout << " Deposit Successful!\n";
            file.close();
            return;
        }
    }

    cout << " Account not found!\n";
    file.close();
}
void withdrawMoney(int accNo) {
    Account a;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == accNo) {
            float amt;
            cout << "Enter amount to withdraw: ";
            cin >> amt;

            a.withdraw(amt);

            file.seekp(-sizeof(a), ios::cur);
            file.write((char*)&a, sizeof(a));

            file.close();
            return;
        }
    }

    cout << " Account not found!\n";
    file.close();
}
void checkBalance(int accNo) {
    Account a;
    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == accNo) {
            a.display();
            file.close();
            return;
        }
    }

    cout << " Account not found!\n";
    file.close();
}
int main() {
    int choice, accNo;

    do {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            cout << "Enter Account No: ";
            cin >> accNo;
            depositMoney(accNo);
            break;

        case 4:
            cout << "Enter Account No: ";
            cin >> accNo;
            withdrawMoney(accNo);
            break;

        case 5:
            cout << "Enter Account No: ";
            cin >> accNo;
            checkBalance(accNo);
            break;

        case 6:
            cout << " Exiting...\n";
            break;

        default:
            cout << " Invalid choice!\n";
        }


    } while (choice != 6);

    return 0;
}

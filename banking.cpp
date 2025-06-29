#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

class Bank
{
public:
  string accountNo;
  string name;
  float balance;
  string pin;

  void createAccount()
  {
    cout << "Enter account number: ";
    cin >> accountNo;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter initial balance (minimum 1000): ";
    cin >> balance;

    if (balance < 1000)
    {
      cout << "Initial deposit must be at least 1000!\n";
      return;
    }

    cout << "Set 4-digit PIN: ";
    cin >> pin;

    if (pin.length() != 4)
    {
      cout << "PIN must be exactly 4 digits!\n";
      return;
    }

    ofstream file(accountNo + ".txt");
    if (file.is_open())
    {
      file << accountNo << endl;
      file << name << endl;
      file << balance << endl;
      file << pin << endl;
      file.close();
      cout << "Account created successfully!\n";
      logTransactionCSV("Account created", balance);
    }
    else
    {
      cout << "Error creating account file.\n";
    }
  }

  bool loadAccount(string accNo)
  {
    ifstream file(accNo + ".txt");
    if (file.is_open())
    {
      string balStr;
      getline(file, accountNo);
      getline(file, name);
      getline(file, balStr);
      getline(file, pin);
      balance = stof(balStr);
      file.close();
      return true;
    }
    return false;
  }

  bool verifyPin()
  {
    string inputPin;
    cout << "Enter 4-digit PIN: ";
    cin >> inputPin;
    return inputPin == pin;
  }

  void deposit()
  {
    if (!verifyPin())
    {
      cout << "Invalid PIN. Transaction cancelled.\n";
      return;
    }

    float amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    balance += amount;
    updateAccount();
    logTransactionCSV("Deposit", amount);
    cout << "Deposit successful! New balance: ₹" << fixed << setprecision(2) << balance << endl;
  }

  void withdraw()
  {
    if (!verifyPin())
    {
      cout << "Invalid PIN. Transaction cancelled.\n";
      return;
    }

    float amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount > balance)
    {
      cout << "Insufficient balance!\n";
      return;
    }

    balance -= amount;
    updateAccount();
    logTransactionCSV("Withdraw", amount);
    cout << "Withdrawal successful! New balance: ₹" << fixed << setprecision(2) << balance << endl;
  }

  void checkBalance()
  {
    cout << "\n=== Account Details ===\n";
    cout << "Account Number: " << accountNo << endl;
    cout << "Name          : " << name << endl;
    cout << "Balance       : ₹" << fixed << setprecision(2) << balance << endl;
  }

  void updateAccount()
  {
    ofstream file(accountNo + ".txt");
    if (file.is_open())
    {
      file << accountNo << endl;
      file << name << endl;
      file << balance << endl;
      file << pin << endl;
      file.close();
    }
  }

  void logTransactionCSV(const string &action, float amount)
  {
    string logFilename = accountNo + "_log.csv";
    bool fileExists = ifstream(logFilename).good();

    ofstream logFile(logFilename, ios::app);
    if (logFile.is_open())
    {

      if (!fileExists)
      {
        logFile << left << setw(20) << "DateTime"
                << setw(15) << "Action"
                << setw(15) << "Amount"
                << setw(15) << "New Balance" << endl;
      }

      time_t now = time(0);
      tm *localTime = localtime(&now);
      char buffer[80];
      strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

      logFile << left << setw(20) << buffer
              << setw(15) << action
              << setw(15) << fixed << setprecision(2) << amount
              << setw(15) << fixed << setprecision(2) << balance << endl;

      logFile.close();
    }
  }
};

int main()
{
  int choice;
  string accNo;

  while (true)
  {
    cout << "\n===== BANK MENU =====\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    Bank acc;

    switch (choice)
    {
    case 1:
      acc.createAccount();
      break;

    case 2:
      cout << "Enter account number: ";
      cin >> accNo;
      if (acc.loadAccount(accNo))
      {
        acc.deposit();
      }
      else
      {
        cout << "Account not found!\n";
      }
      break;

    case 3:
      cout << "Enter account number: ";
      cin >> accNo;
      if (acc.loadAccount(accNo))
      {
        acc.withdraw();
      }
      else
      {
        cout << "Account not found!\n";
      }
      break;

    case 4:
      cout << "Enter account number: ";
      cin >> accNo;
      if (acc.loadAccount(accNo))
      {
        acc.checkBalance();
      }
      else
      {
        cout << "Account not found!\n";
      }
      break;

    case 5:
      cout << "Thank you for using the Bank System!\n";
      return 0;

    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }
}

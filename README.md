# 💳 MiniBank – A Simple C++ Console Banking System

MiniBank is a command-line based banking system written in C++ that allows users to create secure accounts, manage deposits and withdrawals, and track transaction history in a neat CSV table format.

---

## 🚀 Features

- 🆕 Account Creation with:
  - Account number
  - Full name
  - Minimum balance of ₹1000
  - 4-digit secure PIN

- 💰 Deposit & 🧾 Withdraw money (PIN protected)

- 📊 View account balance

- 🧾 CSV-formatted transaction logs with:
  - Timestamp
  - Action (Deposit, Withdraw, etc.)
  - Amount
  - Updated balance

---

## 📦 File Structure

- Each account is saved as a `accountNo.txt` file.
- Transactions are saved as `accountNo_log.csv`.

Example:
```
2241011116.txt
2241011116_log.csv
```

---

## 📌 How to Use

1. **Compile the program:**
   ```bash
     g++ bank.cpp -o bank
   ```

2. **Run the program:**
   ```bash
   ./bank   # or bank.exe on Windows
   ```

3. **Menu Options:**
   - `1`: Create a new account
   - `2`: Deposit money
   - `3`: Withdraw money
   - `4`: Check balance
   - `5`: Exit

---

## 📋 Sample Transaction Log (CSV Table)

```
DateTime            Action         Amount         New Balance    
2025-06-29 10:00:01 Account created 1500.00        1500.00        
2025-06-29 10:10:22 Deposit         500.00         2000.00        
2025-06-29 10:15:33 Withdraw        300.00         1700.00        
```

---



---

## 🛠 Technologies Used

- C++ (`iostream`, `fstream`, `iomanip`, `ctime`)
- File I/O for persistent data storage
- CSV for transaction logs

---



---

## 🙌 Acknowledgements

- Inspired by real-life money management needs.
- Built with  C++.

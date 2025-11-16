#include <iostream>
#include <string>

class Bank {
private:
    int accNum;
    double bal;
    std::string accType;

public:
    // Constructors
    Bank() : accNum(0), bal(0.0), accType("saving") {}
    Bank(int ac, double ba, std::string ty) : accNum(ac), bal(ba), accType(ty) {}
    Bank(const Bank& other) : accNum(other.accNum), bal(other.bal), accType(other.accType) {}

    // Getters
    int getAccNum() const { return accNum; }
    double getBal() const { return bal; }
    std::string getAccType() const { return accType; }

    // Core banking operations
    bool deposit(double amtDeposit) {
        if (amtDeposit > 0) {
            bal += amtDeposit;
            return true;
        }
        return false;
    }

    bool withdraw(double amtWithdraw) {
        if (amtWithdraw > 0 && bal >= amtWithdraw) {
            bal -= amtWithdraw;
            return true;
        }
        return false;
    }

    bool transfer(Bank& targetAccount, double transAmt) {
        if (this->withdraw(transAmt)) {
            if (targetAccount.deposit(transAmt)) {
                return true;
            } else {
                // Rollback if deposit fails
                this->deposit(transAmt);
                return false;
            }
        }
        return false;
    }

    // Display method
    void display() const {
        std::cout << "AccountNumber: " << accNum << std::endl;
        std::cout << "Balance: " << bal << std::endl;
        std::cout << "AccountType: " << accType << std::endl;
    }

    // Operator overloads
    Bank& operator+=(double addAmt) {
        this->deposit(addAmt);
        return *this;
    }

    Bank& operator-=(double subAmt) {
        this->withdraw(subAmt);
        return *this;
    }

    bool operator>(const Bank& otherAcc) const {
        return this->bal > otherAcc.bal;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Bank accountA(7500, 1500, "current");
    Bank accountB(5000, 1200, "current");
    Bank accountC(accountB);

    if (accountA.deposit(300)) {
        std::cout << "Deposit to Account A successful." << std::endl;
    } else {
        std::cout << "Deposit to Account A failed." << std::endl;
    }

    if (accountB.deposit(400)) {
        std::cout << "Deposit to Account B successful." << std::endl;
    } else {
        std::cout << "Deposit to Account B failed." << std::endl;
    }

    if (accountC.withdraw(100)) {
        std::cout << "Withdrawal from Account C successful." << std::endl;
    } else {
        std::cout << "Withdrawal from Account C failed." << std::endl;
    }

    accountA += 800;
    accountB += 900;

    if (accountA.transfer(accountB, 500)) {
        std::cout << "Transfer from Account A to Account B successful." << std::endl;
    } else {
        std::cout << "Transfer from Account A to Account B failed." << std::endl;
    }

    std::cout << "\n--- Account Details ---" << std::endl;
    accountA.display();
    std::cout << "---------------------" << std::endl;
    accountB.display();
    std::cout << "---------------------" << std::endl;
    accountC.display();
    std::cout << "---------------------\n" << std::endl;

    if (accountA > accountB) {
        std::cout << "Account A has a higher balance than Account B." << std::endl;
    } else if (accountB > accountA) {
        std::cout << "Account B has a higher balance than Account A." << std::endl;
    } else {
        std::cout << "Account A and Account B have the same balance." << std::endl;
    }

    return 0;
}
#include <iostream>
#include <mutex>
#include <thread>
#include <iomanip>
#include <string>
#include <vector>

class BankAccount {
public:
  BankAccount(const std::string& name, double balance)
    : m_name(name), m_balance(balance) {}

  void transfer(BankAccount& toAccount, double amount) {
    // Lock both accounts
    std::lock_guard<std::mutex> lock1(m_mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate processing delay
    std::lock_guard<std::mutex> lock2(toAccount.m_mutex);

    if (m_balance >= amount) {
      m_balance -= amount;
      toAccount.m_balance += amount;
      std::cout << "Transferred " << amount << " from " << m_name
                << " to " << toAccount.m_name << ".\n";
    } else {
      std::cout << "Insufficient funds in " << m_name << " to transfer " << amount << ".\n";
    }
  }


  void printBalance() const {
    std::cout << m_name << " balance: " << m_balance << "\n";
  }

private:
  std::string m_name;
  double m_balance;
  mutable std::mutex m_mutex;
};


void performTransfers(BankAccount& account1, BankAccount& account2) {
  std::vector<std::thread> threads;
  for (int i = 0; i < 1; ++i) {
    threads.emplace_back([&]() { account1.transfer(account2, 100.0); });
    threads.emplace_back([&]() { account2.transfer(account1, 200.0); });
  }
  for (auto& t : threads) {
    t.join();
  }
}

int main() {
  BankAccount account1("Account1", 1000.0);
  BankAccount account2("Account2", 1000.0);

  performTransfers(account1, account2);

  account1.printBalance();
  account2.printBalance();

  return 0;
}

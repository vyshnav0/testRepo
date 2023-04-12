class Account:
    count = 0
    def _init_(self):
        self.balance=0
        Account.count += 1
    def displayBalance(self):
        print("Your balance is: ", self.balance)
    def deposit(self):
        amount = int(input("Enter money to deposit."))
        self.balance += amount
        self.displayBalance()
    def withdraw(self):
        amount = int(input("Enter the amount to withdraw."))
        if(amount <= self.balance):
            self.balance -= amount
        else:
            print("Insufficient balanace.")
        self.displayBalance()
        
ac1 = Account ()
ac2 = Account ()
ac1.deposit()
ac2.deposit()
ac1.withdraw()
ac2.withdraw()
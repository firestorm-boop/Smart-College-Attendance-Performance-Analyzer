import java.util.Scanner;
import java.util.ArrayList;

class Account {
    protected String accNo;
    protected String holder;
    protected double balance;
    
    public Account(String accNo, String holder, double balance) {
        this.accNo = accNo;
        this.holder = holder;
        this.balance = balance;
    }
    
    public void deposit(double amt) {
        if(amt > 0) {
            balance += amt;
            System.out.println("Deposited: ₹" + amt);
        }
    }
    
    public void withdraw(double amt) {
        if(amt > 0 && amt <= balance) {
            balance -= amt;
            System.out.println("Withdrew: ₹" + amt);
        } else {
            System.out.println("Insufficient balance!");
        }
    }
    
    public void display() {
        System.out.println("Acc: " + accNo + ", Holder: " + holder + ", Balance: ₹" + balance);
    }
}

class SavingsAccount extends Account {
    private double interestRate = 0.04;
    
    public SavingsAccount(String accNo, String holder, double balance) {
        super(accNo, holder, balance);
    }
    
    public void addInterest() {
        balance += balance * interestRate;
        System.out.println("Interest added!");
    }
}

public class BankSystem {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Account> accounts = new ArrayList<>();
        
        // Sample accounts
        accounts.add(new SavingsAccount("SAV001", "Aasrith Sri", 5000));
        accounts.add(new Account("CUR002", "Test User", 10000));
        
        int choice;
        do {
            System.out.println("\n1. Display Accounts 2. Deposit 3. Withdraw 4. Add Interest 0. Exit");
            choice = sc.nextInt();
            
            if(choice == 1) {
                for(Account acc : accounts) acc.display();
            } else if(choice == 2) {
                System.out.print("Acc Index: "); int idx = sc.nextInt();
                System.out.print("Amount: "); double amt = sc.nextDouble();
                accounts.get(idx).deposit(amt);
            } else if(choice == 3) {
                // Similar for withdraw
                System.out.print("Acc Index: "); int idx = sc.nextInt();
                System.out.print("Amount: "); double amt = sc.nextDouble();
                accounts.get(idx).withdraw(amt);
            } else if(choice == 4) {
                ((SavingsAccount)accounts.get(0)).addInterest();
            }
        } while(choice != 0);
        sc.close();
    }
}

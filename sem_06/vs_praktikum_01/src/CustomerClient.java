import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class CustomerClient {
    public static void main (String args[]) {
        String format = "Name: %8s, Number: %8d, Balance: %8.0f, Password: %8s\n";
        try {
            Registry reg = LocateRegistry.getRegistry(1099);
            CustomerInterface c = (CustomerInterface)reg.lookup("rmi://localhost:1099/Customer");
            try {
                System.out.print("Creating Accounts.\n");
                int id1 = c.createCustomer("Peter", "1234");
                int id2 = c.createCustomer("Steve", "1234");
                int id3 = c.createCustomer("Chris", "1234");

                Account a1 = c.getAccount(id1, "Peter", "1234");
                Account a2 = c.getAccount(id2, "Steve", "1234");
                Account a3 = c.getAccount(id3, "Chris", "1234");

                System.out.printf(format, a1.getName(), a1.getNumber(), a1.getBalance(), a1.getPassword());
                System.out.printf(format, a2.getName(), a2.getNumber(), a2.getBalance(), a2.getPassword());
                System.out.printf(format, a3.getName(), a3.getNumber(), a3.getBalance(), a3.getPassword());

                System.out.print("Depositing Money.\n");
                c.deposit(id1, "Peter",   1.0);
                c.deposit(id2, "Steve",  10.0);
                c.deposit(id3, "Chris", 100.0);

                a1 = c.getAccount(id1, "Peter", "1234");
                a2 = c.getAccount(id2, "Steve", "1234");
                a3 = c.getAccount(id3, "Chris", "1234");

                System.out.printf(format, a1.getName(), a1.getNumber(), a1.getBalance(), a1.getPassword());
                System.out.printf(format, a2.getName(), a2.getNumber(), a2.getBalance(), a2.getPassword());
                System.out.printf(format, a3.getName(), a3.getNumber(), a3.getBalance(), a3.getPassword());

                System.out.print("Depositing Money.\n");
                c.deposit(id1, "Peter",   100.0);
                c.deposit(id2, "Steve",  1000.0);
                c.deposit(id3, "Chris", 10000.0);

                a1 = c.getAccount(id1, "Peter", "1234");
                a2 = c.getAccount(id2, "Steve", "1234");
                a3 = c.getAccount(id3, "Chris", "1234");

                System.out.printf(format, a1.getName(), a1.getNumber(), a1.getBalance(), a1.getPassword());
                System.out.printf(format, a2.getName(), a2.getNumber(), a2.getBalance(), a2.getPassword());
                System.out.printf(format, a3.getName(), a3.getNumber(), a3.getBalance(), a3.getPassword());

                System.out.print("Withdrawing Money.\n");
                c.withdraw(id1, "Peter", "1234",   1.0);
                c.withdraw(id2, "Steve", "1234",  10.0);
                c.withdraw(id3, "Chris", "1234", 100.0);

                a1 = c.getAccount(id1, "Peter", "1234");
                a2 = c.getAccount(id2, "Steve", "1234");
                a3 = c.getAccount(id3, "Chris", "1234");

                System.out.printf(format, a1.getName(), a1.getNumber(), a1.getBalance(), a1.getPassword());
                System.out.printf(format, a2.getName(), a2.getNumber(), a2.getBalance(), a2.getPassword());
                System.out.printf(format, a3.getName(), a3.getNumber(), a3.getBalance(), a3.getPassword());

                try {
                    System.out.print("Hans (has no id) tries to withdraw money\n");
                    c.withdraw(55113, "Hans", "1234", 1000000.0);
                } catch(BankException e) {
                    System.out.print("Exception! ");
                    System.out.print(e);
                }
                try {
                    System.out.print("Peter is now trying to take way to much money\n");
                    c.withdraw(id1, "Peter", "1234", 1000000.0);
                } catch(BankException e) {
                    System.out.print("Exception! ");
                    System.out.print(e);
                }
                try {
                    System.out.print("Steve is now trying to withdraw with the wrong password\n");
                    c.withdraw(id2, "Steve", "4321", 1.0);
                } catch(BankException e) {
                    System.out.print("Exception! ");
                    System.out.print(e);
                }
                try {
                    System.out.print("Chris is now trying deposit with wrong password id combination\n");
                    c.deposit(id3, "Peter", 1.0);
                } catch(BankException e) {
                    System.out.print("Exception! ");
                    System.out.print(e);
                }

                System.out.print("Peter now creates 4 more accounts and adds 10$ to each\n");
                int tmp;
                tmp = c.createCustomer("Peter", "1234");
                c.deposit(tmp, "Peter", 10.0);
                tmp = c.createCustomer("Peter", "1234");
                c.deposit(tmp, "Peter", 10.0);
                tmp = c.createCustomer("Peter", "1234");
                c.deposit(tmp, "Peter", 10.0);
                tmp = c.createCustomer("Peter", "1234");
                c.deposit(tmp, "Peter", 10.0);
                System.out.print("Steve now creates 2 more accounts and adds 1111$ each\n");
                tmp = c.createCustomer("Steve", "1234");
                c.deposit(tmp, "Steve", 1111.0);
                tmp = c.createCustomer("Steve", "1234");
                c.deposit(tmp, "Steve", 1111.0);
            } catch(BankException e) {
                System.out.print("Exception\n");
                System.out.print(e);
            } catch(Exception e) {
                System.out.print("Exception\n");
                System.out.print(e);
                e.printStackTrace();
            }

        } catch (Exception e) {
            System.out.print("Exception\n");
            System.out.print(e);
            e.printStackTrace();
        }
    }
}

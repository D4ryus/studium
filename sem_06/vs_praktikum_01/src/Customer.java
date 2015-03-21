import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

class Customer extends UnicastRemoteObject implements CustomerInterface {
    private static final long serialVersionUID = 1L;
    private Bank bank;

    public Customer(Registry reg, String name, Bank bank) throws RemoteException {
        this.bank = bank;
        try {
            reg.rebind(name, this);
            System.out.println ("Customer Interface ready.");
        }
        catch (Exception e) {
            System.out.println("Exception on creating Customer Interface:\n" + e.getMessage());
        }
    }

    @Override
    public synchronized int createCustomer(String customerName, String customerPassword)
            throws RemoteException {
        bank.setAccountCounts(bank.getAccountCounts() + 1);
        bank.getAccounts().put(bank.getAccountCounts(), new Account(customerName, customerPassword, bank.getAccountCounts()));
        return bank.getAccountCounts();
    }

    @Override
    public synchronized void deposit(int accountNumber, String customerName, double depositAmount)
            throws BankException, RemoteException {
        Account tmp = bank.getAccounts().get(accountNumber);
        if (tmp == null) {
            throw new BankException("Account Number does not Exist!\n");
        }
        if (!tmp.getName().equals(customerName)) {
            throw new BankException("Account Number does not match given Account Name!\n");
        }
        tmp.setBalance(tmp.getBalance() + depositAmount);
    }

    @Override
    public synchronized double withdraw(int accountNumber, String customerName, String customerPassword, double withdrawAmount)
            throws BankException, RemoteException {
        Account tmp = bank.getAccounts().get(accountNumber);
        if (tmp == null) {
            throw new BankException("Account Number does not Exist!\n");
        }
        if (!tmp.getName().equals(customerName)) {
            throw new BankException("Account Number does not match given Account Name!\n");
        }
        if (!tmp.getPassword().equals(customerPassword)) {
            throw new BankException("Account Password does not match!\n");
        }
        if (tmp.getBalance() < withdrawAmount) {
            throw new BankException("Balance to low, withdraw aborted.\n");
        }
        tmp.setBalance(tmp.getBalance() - withdrawAmount);
        return withdrawAmount;
    }

    @Override
    public synchronized Account getAccount(int accountNumber, String customerName, String customerPassword)
            throws BankException, RemoteException {
        Account tmp = bank.getAccounts().get(accountNumber);
        if (tmp == null) {
            throw new BankException("Account Number does not Exist!\n");
        }
        if (!tmp.getName().equals(customerName)) {
            throw new BankException("Account Number does not match given Account Name!\n");
        }
        if (!tmp.getPassword().equals(customerPassword)) {
            throw new BankException("Account Password does not match!\n");
        }
        return tmp;
    }
}

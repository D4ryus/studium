import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Hashtable;

class Bank {
    private int accountCounts = 1000;
    private Hashtable<Integer, Account> accounts = new Hashtable<Integer, Account>();

    public static void main(String... args) {
        Bank b = new Bank();
    }

    public Bank() {
        try {
            Registry reg = LocateRegistry.createRegistry(1099);
            Customer c1 = new Customer(reg, "rmi://localhost:1099/Customer", this);
            TaxOffice t1 = new TaxOffice(reg, "rmi://localhost:1099/TaxOffice", this);
        } catch (Exception e) {
            System.out.println ("ServerException: " + e.getMessage());
        }
    }

    /**
     * @return the accountCounts
     */
    public int getAccountCounts() {
        return accountCounts;
    }

    /**
     * @param accountCounts the accountCounts to set
     */
    public void setAccountCounts(int accountCounts) {
        this.accountCounts = accountCounts;
    }

    /**
     * @return the accounts
     */
    public Hashtable<Integer, Account> getAccounts() {
        return accounts;
    }
}

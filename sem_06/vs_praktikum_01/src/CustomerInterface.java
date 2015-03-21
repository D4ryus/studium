import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CustomerInterface extends Remote {
    int createCustomer(String customerName, String customerPassword) throws RemoteException;

    void deposit(int accountNumber, String customerName, double depositAmount)
        throws BankException, RemoteException;

    double withdraw(int accountNumber, String customerName, String customerPassword, double withdrawAmount)
        throws BankException, RemoteException;

    Account getAccount(int accountNumberString, String customerName, String customerPassword)
        throws BankException, RemoteException;
}

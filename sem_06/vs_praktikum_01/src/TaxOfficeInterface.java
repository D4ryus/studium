import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.LinkedList;

public interface TaxOfficeInterface extends Remote {
    double balanceOfCustomer(String customer) throws BankException, RemoteException;
    LinkedList<Integer> numbersOfCustomer(String customer)throws BankException, RemoteException;
}

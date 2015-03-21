import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;

class TaxOffice extends UnicastRemoteObject implements TaxOfficeInterface {
    private static final long serialVersionUID = 2L;
    private Bank bank;

    public TaxOffice(Registry reg, String name, Bank bank) throws RemoteException {
        this.bank = bank;
        try {
            reg.rebind(name, this);
            System.out.println ("TaxOffice Interface ready.");
        } catch (Exception e) {
            System.out.println("Exception on creating TaxOffice Interface:\n" + e.getMessage());
        }
    }

    @Override
    public double balanceOfCustomer(String customer) throws BankException, RemoteException {
        double totalBalance = 0.0;
        boolean does_exist = false;
        for (Account tmp : bank.getAccounts().values()) {
            if (tmp.getName().equals(customer)) {
                totalBalance += tmp.getBalance();
                if (!does_exist) {
                    does_exist = true;
                }
            }
        }
        if (!does_exist) {
            throw new BankException("requested customer (" + customer + ") does not Exists!\n");
        }
        return totalBalance;
    }

    @Override
    public LinkedList<Integer> numbersOfCustomer(String customer)
            throws BankException, RemoteException {
        LinkedList<Integer> numbers = new LinkedList<Integer>();
        boolean does_exist = false;
        for (Account tmp : bank.getAccounts().values()) {
            if (tmp.getName().equals(customer)) {
                numbers.push(new Integer(tmp.getNumber()));
                if (!does_exist) {
                    does_exist = true;
                }
            }
        }
        if (!does_exist) {
            throw new BankException("requested customer (" + customer + ") does not Exists!\n");
        }
        return numbers;
    }
}

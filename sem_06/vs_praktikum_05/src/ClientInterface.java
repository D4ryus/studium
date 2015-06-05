import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ClientInterface extends Remote {

    String getName() throws RemoteException;

    void notifyClientChange() throws RemoteException;

    void newMessage(Message message) throws RemoteException;
}

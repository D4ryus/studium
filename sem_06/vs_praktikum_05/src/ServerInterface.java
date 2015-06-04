import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.LinkedList;

public interface ServerInterface extends Remote {
    void registerClient(String address, int port, String clientName) throws RemoteException;

    void deregisterClient(String clientName) throws RemoteException;

    void sendMessage(Message message) throws RemoteException;

    LinkedList<String> getOtherClients() throws RemoteException;
}

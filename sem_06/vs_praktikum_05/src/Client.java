import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

class Client extends UnicastRemoteObject implements ClientInterface {

    private static final long serialVersionUID = 1L;
    private String name;

    protected Client(String name) throws RemoteException {
        super();
        // TODO Auto-generated constructor stub
    }

    @Override
    public void notifyClientChange() throws RemoteException {
        // TODO Auto-generated method stub

    }

    @Override
    public void newMessage(Message message) throws RemoteException {
        // TODO Auto-generated method stub

    }

    @Override
    public String getName() throws RemoteException {
        return name;
    }
}

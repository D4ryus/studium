import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;

class Server extends UnicastRemoteObject implements ServerInterface {

    private static final long serialVersionUID = -8888164889924917331L;
    private int port;
    private String address;
    private String name;
    private Registry reg = null;
    private LinkedList<ClientInterface> clients =
                new LinkedList<ClientInterface>();

    public static void main(String... args) {
        if (args.length < 3) {
            System.out.printf("usage: java %s Address Port Name\n",
                Server.class.getSimpleName());
            System.exit(1);
        }
        try {
            Server s = new Server(args[0], Integer.parseInt(args[1]),
                               args[2]);
        } catch (Exception e) {
            System.out.println("Exception on registering Registry:\n"
                           + e.getMessage());
            System.exit(1);
        }
    }

    public Server(String address, int port, String name)
               throws RemoteException {
        this.address = address;
        this.port = port;
        this.name = name;
        try {
            reg = LocateRegistry.createRegistry(port);
            reg.rebind("rmi://" + this.address + ":" + this.port + "/"
                    + this.name, this);
            System.out.println ("Server Interface ready.");
        } catch (Exception e) {
            System.out.println("Exception on creating Server Interface:\n"
                    + e.getMessage());
            System.exit(1);
        }
    }

    @Override
    public void registerClient(String address, int port, String clientName)
                    throws RemoteException {
        ClientInterface client = null;
        Registry tmp = null;
        try {
            tmp = LocateRegistry.getRegistry(address, port);
            client = (ClientInterface)tmp.lookup("rmi://" + address + ":"
                                              + port + "/" + clientName);
        } catch (Exception e) {
            System.out.printf("could not lookup %s\n", clientName);
            return;
        }
        for (ClientInterface c : clients) {
            c.notifyClientChange();
        }
        clients.add(client);
        System.out.println("new Client registered: " + clientName);
    }

    @Override
    public void deregisterClient(String clientName) throws RemoteException {
        int i = 0;
        for (ClientInterface c : clients) {
            if (c.getName().equals(clientName)) {
                clients.remove(i);
                System.out.println("Client deregistered: " + clientName);
                for (ClientInterface cc : clients) {
                    cc.notifyClientChange();
                }
                return;
            }
            i++;
        }
    }

    @Override
    public void sendMessage(Message message) throws RemoteException {
        for (ClientInterface c : clients) {
            c.newMessage(message);
        }
    }

    @Override
    public LinkedList<ClientInterface> getOtherClients()
               throws RemoteException {
        return clients;
    }
}

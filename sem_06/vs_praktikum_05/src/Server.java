import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.LinkedList;

class Server extends UnicastRemoteObject implements ServerInterface {

    private static final long serialVersionUID = -8888164889924917331L;
    private int port;
    private String address;
    private String name;
    private Registry reg = null;
    private HashMap<String, ClientInterface> clients = new HashMap<String, ClientInterface>();

    public static void main(String... args) {
        if (args.length < 3) {
            System.out.printf("usage: java %s Adress Port ServerName\n", Server.class.getSimpleName());
        }
        try {
            Server s = new Server(args[0], Integer.parseInt(args[1]), args[2]);
        } catch (Exception e) {
            System.out.println("Exception on registering Registry:\n" + e.getMessage());
            System.exit(1);
        }
    }

    public Server(String address, int port, String name) throws RemoteException {
        this.address = address;
        this.port = port;
        this.name = name;
        try {
            reg = LocateRegistry.createRegistry(1099);
            reg.rebind("rmi://" + this.address + ":" + this.port + "/" + this.name, this);
            System.out.println ("Server Interface ready.");
        } catch (Exception e) {
            System.out.println("Exception on creating Server Interface:\n" + e.getMessage());
            System.exit(1);
        }
    }

    @Override
    public void registerClient(String address, int port, String clientName) throws RemoteException {
        ClientInterface client = null;
        try {
            client = (ClientInterface)reg.lookup("rmi://" + address + ":" + port + "/" + clientName);
        } catch (Exception e) {
            System.out.printf("could not lookup %s\n", clientName);
            return;
        }
        for (ClientInterface c : clients.values()) {
            c.notifyClientChange();
        }
        clients.put(clientName, client);
    }

    @Override
    public void deregisterClient(String clientName) throws RemoteException {
        for (ClientInterface c : clients.values()) {
            if (c.getName().equals(clientName)) {
                clients.remove(clientName, c);
                return;
            }
        }
    }

    @Override
    public void sendMessage(Message message) throws RemoteException {
        for (ClientInterface c : clients.values()) {
            c.newMessage(message);
        }
    }

    @Override
    public LinkedList<String> getOtherClients() throws RemoteException {
        LinkedList<String> otherClients = new LinkedList<String>();
        for (ClientInterface c : clients.values()) {
            otherClients.push(c.getName());
        }
        return otherClients;
    }
}

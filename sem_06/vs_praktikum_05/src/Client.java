import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;
import java.util.LinkedList;

class Client extends UnicastRemoteObject implements ClientInterface {
    private int port;
    private String address;
    private String name;
    private Registry lokalReg = null;
    private Registry serverReg = null;
    private ServerInterface server;
    private static final long serialVersionUID = 1L;
    private LinkedList<ClientInterface> clients =
                new LinkedList<ClientInterface>();

    public static void main(String... args) {
        Client c = null;
        if (args.length != 3) {
            System.out.printf("usage: java %s Address Port Name\n",
                Client.class.getSimpleName());
            System.exit(1);
        }
        try {
            c = new Client(args[0], Integer.parseInt(args[1]), args[2]);
            c.readUserInput();
        } catch (RemoteException e) {
            System.out.println("RemoteException:\n" + e.getMessage());
            System.exit(1);
        }
    }

    protected Client(String address, int port, String name)
                  throws RemoteException {
        this.address = address;
        this.port = port;
        this.name = name;
        try {
            lokalReg = LocateRegistry.createRegistry(port);
            lokalReg.rebind("rmi://" + this.address + ":" + this.port + "/"
                + this.name, this);
            System.out.println ("Client Interface ready.");
        } catch (Exception e) {
            System.out.println("Exception on creating Client Interface:\n"
                + e.getMessage());
            System.exit(1);
        }
    }

    public void readUserInput() throws RemoteException {
        String lines[];
        BufferedReader br = new BufferedReader(
                                    new InputStreamReader(System.in));
        while (true) {
            lines = null;
            try {
                lines = br.readLine().split(" ");
            } catch (IOException e) {
                System.out.print("IO Exception:\n" + e);
                System.exit(1);
            }
            if (lines == null) {
                System.out.print("please enter something!\n");
                continue;
            }
            switch (lines[0]) {
                case "msg":
                    if (server == null) {
                        System.out.print("not connected to Server\n");
                    }
                    if (lines.length < 3) {
                        System.out.print("please enter a recipient and "
                            + "message\n");
                        continue;
                    }
                    for (ClientInterface c : clients) {
                        if (lines[1].equals(c.getName())) {
                            String msg = "";
                            for (int i = 2; i < lines.length; i++) {
                                msg += lines[i] + " ";
                            }
                            c.newMessage(new Message(name, new Date(), msg));
                            continue;
                        }
                    }
                    break;
                case "broadcast":
                    if (server == null) {
                        System.out.print("not connected to Server\n");
                    }
                    if (lines.length < 2) {
                        System.out.print("please enter a message\n");
                        continue;
                    }
                    String msg = "";
                    for (int i = 1; i < lines.length; i++) {
                        msg += lines[i] + " ";
                    }
                    server.sendMessage(new Message(name, new Date(), msg));
                    break;
                case "register":
                    if (server != null) {
                        System.out.print("already registered on a server\n" );
                        continue;
                    }
                    if (lines.length != 4) {
                        System.out.print("please use: register [adress] [port] "
                                 + "[name]\n" );
                        continue;
                    }
                    try {
                        serverReg = LocateRegistry.getRegistry(lines[1],
                                        Integer.parseInt(lines[2]));
                        server = (ServerInterface)serverReg.lookup(
                                                "rmi://" + lines[1] + ":"
                                                + Integer.parseInt(lines[2])
                                                + "/" + lines[3]);
                        System.out.println ("Connected to Server " + lines[3]);
                    } catch (Exception e) {
                        System.out.printf("could not lookup %s\n", lines[3]);
                        continue;
                    }
                    server.registerClient(address, port, name);
                    System.out.println ("Registert on Server" + lines[3]);
                case "update":
                    if (server == null) {
                        System.out.print("not registered on any server\n" );
                        continue;
                    }
                    clients = server.getOtherClients();
                case "list":
                    for (ClientInterface c : clients) {
                        System.out.print(" * " + c.getName() + "\n");
                    }
                    break;
                case "deregister":
                    if (server == null) {
                        System.out.print("not registered on any server\n" );
                        continue;
                    }
                    server.deregisterClient(name);
                    server = null;
                    System.out.print("Connection to Server closed\n");
                    break;
                case "quit":
                    if (server == null) {
                        System.out.print("not registered on any server\n" );
                        continue;
                    }
                    server.deregisterClient(name);
                    server = null;
                    System.out.print("Connection to Server closed\n");
                    System.exit(1);
                default:
                    System.out.print("command not found, write one of the "
                            + "following: register, deregister, msg, update, "
                            + "list, broadcast\n");
                    continue;
            }
        }
    }

    @Override
    public void notifyClientChange() throws RemoteException {
        System.out.print("Server notifies a list update!\n");
    }

    @Override
    public void newMessage(Message message) throws RemoteException {
        System.out.print(message.getDate() + " " + message.getName() + ": "
                + message.getMessage() + "\n");
    }

    @Override
    public String getName() throws RemoteException {
        return name;
    }
}

import java.net.*;
import java.io.*;

class DtgClient
{
    private static DtgHeader header;

    private static String read() throws Exception
    {
        BufferedReader userin = new BufferedReader(new InputStreamReader(System.in));
        return userin.readLine();
    }

    public static void main(String args[]) throws Exception
    {
        if(args.length < 2)
        {
            System.out.println("usage: java DtgClient <server_adress> <port>");
            System.exit(0);
        }

        header = new DtgHeader();

        header.rec_port       = 12345;
        header.dtgSocket      = new DatagramSocket(header.rec_port);
        header.send_port      = Integer.parseInt(args[1]);
        header.send_address   = InetAddress.getByName(args[0]);

        String message = read();

        System.out.println("sending message: " + message);
        header.send_message(message);

        message = header.get_message();
        System.out.println("got message:     " + message);

        header.dtgSocket.close();
    }
}

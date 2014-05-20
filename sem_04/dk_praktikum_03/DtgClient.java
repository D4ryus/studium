/* author: d4ryus - https://github.com/d4ryus/
 * vim:ft=java:foldmethod=syntax:foldcolumn=4:
 */
import java.net.*;
import java.io.*;

class DtgClient
{
    private static DtgHeader header;

    private static String read() throws Exception
    {
        BufferedReader userin = new BufferedReader(
                                            new InputStreamReader(System.in));
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

        String message;

        while(true)
        {
            message = read();
            if (message == null)
                break;

            System.out.println("sending message: \"" + message
                                 + "\" to:   \""    + header.send_address.toString()
                                 + ":"              + header.send_port + "\"");
            header.send_message(message);

            message = header.get_message();
            System.out.println("got message:     \"" + message
                                 + "\" from: \""    + header.dtgRecPacket.getPort()
                                 + ":"              + header.dtgRecPacket.getAddress() + "\"");

        }
        header.dtgSocket.close();
    }
}

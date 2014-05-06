import java.net.*;

class DtgServer
{
    private static DtgHeader header;

    public static void main(String args[]) throws Exception
    {
        if(args.length < 1)
        {
            System.out.println("usage: java DtgServer <port>");
            System.exit(0);
        }

        header = new DtgHeader();

        header.rec_port = Integer.parseInt(args[0]);
        header.dtgSocket = new DatagramSocket(header.rec_port);

        while(true)
        {
            String message = header.get_message();
            System.out.println("got message:     " + message);

            header.send_port    = header.dtgRecPacket.getPort();
            header.send_address = header.dtgRecPacket.getAddress();

            message = message.toUpperCase();
            System.out.println("sending message: " + message);
            header.send_message(message);
        }
        //header.dtgSocket.close();
    }
}

/* author: d4ryus - https://github.com/d4ryus/
 * vim:noexpandtab:ft=java:foldmethod=syntax:
 */
import java.net.*;

class DtgHeader
{
    public DatagramSocket dtgSocket;

    public DatagramPacket dtgRecPacket;
    public DatagramPacket dtgSendPacket;

    public int rec_port;
    public int send_port;

    public InetAddress send_address;

    public String get_message() throws Exception
    {
        byte[] buffer = new byte[100];
        dtgRecPacket  = new DatagramPacket(buffer, 100);
        dtgSocket.receive(dtgRecPacket);

        buffer = dtgRecPacket.getData();

        return (new String(buffer));
    }

    public void send_message(String message) throws Exception
    {
        byte[] buffer = message.getBytes();
        dtgSendPacket = new DatagramPacket(buffer, buffer.length, send_address, send_port);
        dtgSocket.send(dtgSendPacket);
    }
}

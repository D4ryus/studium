/* author: d4ryus - https://github.com/d4ryus/
 * vim:ft=java:foldmethod=syntax:foldcolumn=4:
 */
import java.net.*;
import java.io.*;

class Client
{

    private static String read()
    {
        String message = new String();
        try
        {
            BufferedReader bufferedReader =
                new BufferedReader(
                    new InputStreamReader(
                        System.in));
            message = bufferedReader.readLine();
        }
        catch(IOException e)
        {
            System.out.println("IOException by read occured!! " + e);
            System.exit(1);
        }
        return message;
    }

    private static void send_message(Socket socket, String message)
    {
        try
        {
            PrintWriter printWriter =
                new PrintWriter(
                        new OutputStreamWriter(
                            socket.getOutputStream()));
            printWriter.print(message + "\n");
            printWriter.flush();
        }
        catch(IOException e)
        {
            System.out.println("IOException by send_message occured!! " + e);
            System.exit(1);
        }
    }

    private static String get_message(Socket socket)
    {
        String message = new String();
        try
        {
            BufferedReader bufferedReader =
                new BufferedReader(
                        new InputStreamReader(
                            socket.getInputStream()));
            message = bufferedReader.readLine();
        }
        catch(IOException e)
        {
            System.out.println("IOException by get_message occured!! " + e);
            System.exit(1);
        }
        return message;
    }

    public static void main(String args[]) throws Exception
    {
        if(args.length < 2)
        {
            System.out.println("usage: java Client <server_adress> <port>");
            System.exit(0);
        }

        String address = args[0];
        int port       = Integer.parseInt(args[1]);
        Socket socket  = new Socket(address, port);

        while(true)
        {
            String message = read();

            send_message(socket, message);
            System.out.println("sending message: " + message);

            if(message.equals("exit"))
                System.exit(1);

            message = get_message(socket);
            System.out.println("got message:     " + message);
        }
    }
}

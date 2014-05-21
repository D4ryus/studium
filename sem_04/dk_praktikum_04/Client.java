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


    public static void main(String args[]) throws Exception
    {
        if(args.length < 2)
        {
            System.out.println("usage: java Client <server_adress> <port>");
            System.exit(0);
        }

        Header header  = new Header();
        String address = args[0];
        header.port    = Integer.parseInt(args[1]);
        header.socket  = new Socket(address, header.port);

        while(true)
        {
            String message = read();

            header.send_message(message);
            System.out.println("sending message: " + message);

            if(message.equals("exit"))
                System.exit(1);

            message = header.get_message();
            System.out.println("got message:     " + message);
        }
    }
}

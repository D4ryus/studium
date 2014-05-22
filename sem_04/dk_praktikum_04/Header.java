/* author: d4ryus - https://github.com/d4ryus/
 * vim:ft=java:foldmethod=syntax:foldcolumn=5:
 */

import java.net.*;
import java.io.IOException;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import java.io.PrintWriter;
import java.io.OutputStreamWriter;


class Header
{
    public Socket socket;

    public String get_message()
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

    public void send_message(String message)
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
}

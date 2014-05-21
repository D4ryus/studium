/* author: d4ryus - https://github.com/d4ryus/
 * vim:ft=java:foldmethod=syntax:foldcolumn=5:
 */

import java.net.*;
import java.io.IOException;

class Server
{
    static String state = "Init";

    private static String state_automaton(String command)
    {
        String message;
        switch(command)
        {
            case "Go":
                if(state.equals("Init"))
                    message = "Gone";
                else
                    message = "didNothing";
                break;
            case "Left":
                if(state.equals("SNext"))
                    message = "WentLeft";
                else
                    message = "didNothing";
                break;
            case "Right":
                if(state.equals("SNext"))
                    message = "WentRight";
                else
                    message = "didNothing";
                break;
            case "OnceMore":
                if(state.equals("SRight"))
                    message = "DidOnceMore";
                else
                    message = "didNothing";
                break;
            case "Back":
                if(state.equals("SLeft"))
                    message = "WentBack";
                else
                    message = "didNothing";
                break;
            case "exit":
                System.exit(1);
            default:
                message = "didNothing";
                break;
        }
        switch(message)
        {
            case "didNothing":
                return message;
            case "WentLeft":
                state = "SLeft";
                return message;
            case "WentRight":
                state = "SRight";
                return message;
            case "DidOnceMore":
                state = "SNext";
                return message;
            case "WentBack":
                state = "Init";
                return message;
            case "Gone":
                state = "SNext";
                return message;
            default:
                return message;
        }
    }

    public static void main(String args[]) throws Exception
    {
        if(args.length < 1)
        {
            System.out.println("usage: java Server <port>");
            System.exit(0);
        }

        Header header  = new Header();
        header.port    = Integer.parseInt(args[0]);
        ServerSocket socket = new ServerSocket(header.port);

        header.socket = socket.accept();
        System.out.println("got client!");

        while(true)
        {
            String command = header.get_message();
            System.out.println("got command: " + command);

            String message = state_automaton(command);
            System.out.println("in state " + state + " now");
            System.out.println("sending message: " + message);

            header.send_message(message);
        }
        //client_socket.close();
        //s_socket.close();
    }
}

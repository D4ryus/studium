package it_05;

import java.net.URL;

public class Client {
    public static String urls[] = {
        "http://localhost:8080/party1?wsdl",
        "http://localhost:8080/party2?wsdl",
        "http://localhost:8080/party3?wsdl"
    };

    public static void main (String... args) throws Exception {
        for (String u : urls) {
            Party p = new PartyService(new URL(u)).getPartyPort();
            p.invite("steve");
            p.invite("bob");
            p.getDatum();
            p.getDj();
        }
        new PartyService(new URL(urls[0])).getPartyPort().invite("me");
    }
}

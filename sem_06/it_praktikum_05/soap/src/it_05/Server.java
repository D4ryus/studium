package it_05;

import javax.jws.*;
import javax.xml.ws.Endpoint;

@WebService
public class Server {
	Party party1 = new Party("Monday", 2, "DJMongo");
	Party party2 = new Party("Tuesday", 3, "DJJava");
	Party party3 = new Party("Friday", 4, "DJCoffee");
	Weather weather = new Weather();
	Party[] allpartys = {party1, party2, party3};

	public static void main(String[] args) {
		Server serv = new Server();
		Endpoint.publish("http://localhost:8080/party1", serv.party1);
		Endpoint.publish("http://localhost:8080/party2", serv.party2);
		Endpoint.publish("http://localhost:8080/party3", serv.party3);
		Endpoint.publish("http://localhost:8080/weather", serv.weather);
	}
}

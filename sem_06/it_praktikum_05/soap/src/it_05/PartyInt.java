package it_05;

import javax.jws.*;
import java.util.LinkedList;

@WebService
public interface PartyInt {
	@WebMethod public String getDatum();
	@WebMethod public String getDj();
	@WebMethod public int amountOfGuest();
	@WebMethod public LinkedList<String> getGuestList();
	@WebMethod public boolean invite(String guest);
}

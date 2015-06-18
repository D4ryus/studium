package it_05;

import java.util.LinkedList;

import javax.jws.*;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

@WebService
@SOAPBinding(style = Style.RPC)
public class Party implements PartyInt {

	LinkedList<String> guestlist = new LinkedList<>();
	int max;
	String datum;
	String dj;

	public Party(String datum, int max, String dj){
		this.datum = datum;
		this.max = max;
		this.dj = dj;
	}

	@Override
	public String getDatum() {
		return datum;
	}

	@Override
	public String getDj() {
		return dj;
	}

	@Override
	public int amountOfGuest() {
		return guestlist.size();
	}

	@Override
	public LinkedList<String> getGuestList() {
		return guestlist;
	}

	@Override
	public boolean invite(String guest) {
		if (guestlist.size() < max) {
			guestlist.add(guest);
			System.out.printf("Guest %s added\n", guest);
			return true;
		} else {
			System.out.println("Guestlist full\n");
			return false;
		}
	}
}

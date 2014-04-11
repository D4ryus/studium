//package dbj.jdbc;

// usage:   java Buchhandel
// momentan notwendiger Treiber: postgresql-8.3-603.jdbc4.jar
// Buchhaendler- und Verlagssystem

import java.sql.*;
import java.io.*;
import java.util.*;

public class Buchhdl {
	static public void main (String args[]) {
		if (args.length != 0) {
			System.out.println ("usage: java Buchhandel");
			System.exit (1);
		}
		Buchhandel bhl = new Buchhandel ();
		try {
			bhl.work();
		} catch (IOException ioe) {
			System.out.println ("Eingabefehler");
			System.exit(0);
		}
	}
}

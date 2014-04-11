import java.sql.*;
import java.io.*;
import java.util.*;
class Buchhandel {

   // Ausgabe aller Buecher, einfaches Statement
   public void alleBuecher () throws SQLException {
	   Statement stmt = con.createStatement ();
	   String query = "select titel, preis, vname from verlag join buch on verlag.verlag_id = buch.verl_id;";
	   ResultSet rs = stmt.executeQuery (query);
	   while (rs.next ()) {
			String s0 = rs.getString(1);
			double d = rs.getDouble(2);
			String s1 = rs.getString(3);
			System.out.println (s0 + " " + d + " " + s1);
	   }
	   rs.close(); 
	   stmt.close();
   }

   // Ausgabe aller Buecher eines Autors, mehrere Autoren nacheinander,
   // prepared Statement
   public void alleBuecherAutor () {
		BufferedReader inputreader = new BufferedReader (new InputStreamReader (System.in));
		System.out.print("\nAutor Nachname? ");
		try{
			String input = inputreader.readLine();
			
			System.out.println();
			
			String[] autor = input.split(" ");

			for(int i = 0; i < autor.length; i++){
				System.out.println(autor[i] + ": ");
				PreparedStatement stmt = con.prepareStatement ( "select titel, preis, vname  "
																+ "from autor join schreibt on autor.autor_id = schreibt.aut_id "
																+ "join buch on schreibt.isbn = buch.isbn "
																+ "join verlag on buch.verl_id = verlag.verlag_id where autor.nachname = ?" );
				stmt.setString (1, autor[i]);
				ResultSet rs = stmt.executeQuery();
				while (rs.next ()) {
					String s0 = rs.getString(1);
					double d = rs.getDouble(2);
					String s1 = rs.getString(3);
					System.out.println (s0 + " " + d + " " + s1);
				}
				rs.close(); 
				stmt.close();
				System.out.println();
			}
			
		}catch(Exception q){
			System.out.println("exception: " + q);
		}
		
   }

   // Anlegen einer Bestellung durch Angabe von Kundennummer, Buchtitel
   // und Anzahl der zu bestellenden Exemplare
   // Datum ist CURRENT_DATE, Status wird auf 0 gesetzt)
   public void bestellen () throws SQLException {
	    BufferedReader inputreader = new BufferedReader (new InputStreamReader (System.in));
		System.out.print("\nKundenname Buchtitel Anzahl? ");
		try{
			String input = inputreader.readLine();
			System.out.println();
			
			String[] bestellung = input.split(" ");
			String book_name = "empty";
			for(int i = 1; i < bestellung.length - 1; i++){
				if(book_name.equals("empty")){
					book_name = bestellung[i];
				}else{
					book_name = book_name + " " + bestellung[i];
				}
			}
			int anzahl = Integer.parseInt(bestellung[bestellung.length -1]);
			int kund_id;
			String isbn;
			
			PreparedStatement stmt0 = con.prepareStatement ( "select isbn from buch where buch.titel = ?" );
			stmt0.setString(1, book_name);
			ResultSet rs0 = stmt0.executeQuery();
			rs0.next();
			isbn = rs0.getString(1);
			rs0.close(); 
			stmt0.close();
			
			PreparedStatement stmt1 = con.prepareStatement ( "select kunde_id from kunde where kunde.kname = ?" );
			stmt1.setString(1, bestellung[0]);
			ResultSet rs1 = stmt1.executeQuery();
			rs1.next();
			kund_id = rs1.getInt(1);
			rs1.close(); 
			stmt1.close();
			
			PreparedStatement stmt2 = con.prepareStatement ( "insert into bestellung values ( (nextval('bestellid')), ?, (CURRENT_DATE), 0 )" );
			stmt2.setInt(1, kund_id);
			stmt2.executeUpdate();
			stmt2.close();
			
			
			PreparedStatement stmt3 = con.prepareStatement ( "insert into enthaelt values ( (currval('bestellid')), ?, ? )" );
			stmt3.setString(1, isbn);
			stmt3.setInt(2, anzahl);
			stmt3.executeUpdate();
			stmt3.close();			
		}catch(Exception e){
			System.out.println("Exception: " + e);
		}
   }



   // Ausfuehren der anliegenden Bestellungen, soweit nach den Bestaenden moeglich
   public void ausliefern () throws SQLException {
	   
	    int best_id;
		List isbns = new ArrayList();
		
	    PreparedStatement stmt = con.prepareStatement ( "select best_id from bestellung where bestellung.status = 0" );
		ResultSet rs = stmt.executeQuery();
		while(rs.next()){
			
			best_id = rs.getInt(1);
			
			PreparedStatement stmt0 = con.prepareStatement ( "select isbn from enthaelt where enthaelt.bst_id = ?" );
			stmt0.setInt(1, best_id);
			ResultSet rs0 = stmt0.executeQuery();
			rs0.next();
			isbns.add(rs0.getString(1));			
			rs0.close(); 
			stmt0.close();
			
		}
		rs.close(); 
		stmt.close();
		
		int vorrat;
		int bestellung;
		
		for(int i = 0; i < isbns.size(); i++){
			PreparedStatement stmt1 = con.prepareStatement ( "select vorrat from buch where buch.isbn = ?" );
			stmt1.setString(1, (String) isbns.get(i));
			ResultSet rs1 = stmt1.executeQuery();
			rs1.next();
			vorrat = rs1.getInt(1);
			rs1.close(); 
			stmt1.close();
			
			PreparedStatement stmt2 = con.prepareStatement ( "select anzahl from enthaelt where enthaelt.isbn = ?" );
			stmt2.setString(1, (String) isbns.get(i));
			ResultSet rs2 = stmt2.executeQuery();
			rs2.next();
			bestellung = rs2.getInt(1);
			rs2.close(); 
			stmt2.close();
			
			if(bestellung <= vorrat){	
				
				PreparedStatement stmt3 = con.prepareStatement ( "select bst_id from enthaelt where enthaelt.isbn = ?" );
				stmt3.setString(1, (String) isbns.get(i));
				ResultSet rs3 = stmt3.executeQuery();
				rs3.next();
				best_id = rs3.getInt(1);
				rs3.close();
				stmt3.close();
				
				PreparedStatement stmt4 = con.prepareStatement ( "UPDATE bestellung SET status = 1 WHERE best_id = ?" );
				stmt4.setInt(1, best_id);
				stmt4.executeUpdate();
				stmt4.close();
				
				PreparedStatement stmt5 = con.prepareStatement ( "UPDATE buch SET vorrat = ? WHERE isbn = ?" );
				stmt5.setInt(1, (vorrat-bestellung));
				stmt5.setString(2, (String) isbns.get(i));
				stmt5.executeUpdate();
				stmt5.close();
			}
		}
	   
	   
   }

   // Hilfsfunktion fuer ausliefern():
   // Bestand ueberpruefen, ob eine Bestellung ausfuehrbar ist
   // zaehlt Anzahl der Bestellpositionen einer Bestellung mit
   // "geforderte Anzahl > aktueller Bestand"
   // Ist diese Anzahl > 0 kann die Bestellung nicht ausgefuehrt werden.

   private boolean durchfuehrbar (int bnr) {
      return true;  
   }

  // Main: Verbindungsaufbau, Auswahl der gewuenschten Funktion
  public  void work () throws IOException {
    String driverClass = "org.postgresql.Driver";
    try {
	Class.forName (driverClass);
    } catch (ClassNotFoundException exc) {
      System.out.println ("ClassNotFoundException: " + exc.getMessage() );
   }
   try {
        String url = "jdbc:postgresql://localhost/buch";

	con = DriverManager.getConnection (url, "d4ryus", "");
	System.out.println ("Connection gemacht");
	Buchhandel bhl = new Buchhandel ();
	String aufgabe = null;
	userin = new BufferedReader (new InputStreamReader (System.in));
	System.out.println
           ("\nGeben Sie ein: Buecher oder BuecherAutor " +
                               "oder Bestellen oder Ausliefern oder #!");
        while ( ! (aufgabe = userin.readLine()).startsWith("#")) {
		if (aufgabe.equals ("Buecher"))
	    		bhl.alleBuecher();
		else if (aufgabe.equals ("BuecherAutor"))
	    		bhl.alleBuecherAutor();
	        else if (aufgabe.equals ("Bestellen"))
	                bhl.bestellen();
                else if (aufgabe.equals ("Ausliefern"))
                        bhl.ausliefern();
		System.out.println
                   ("Geben Sie ein: Buecher oder BuecherAutor " +
                             "oder Bestellen oder Ausliefern oder #!");
	}
    }
    catch (SQLException exc) {
      exc.printStackTrace ();
    }
  }
  private static Connection con;
  private BufferedReader userin;
}

import org.omg.CORBA.ORB;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;

public class VereinsMitgliedServer {
	public static void main(String args[]) {
		try {
			ORB orb = ORB.init(args, null);
			
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			NamingContext ncRoot = NamingContextHelper.narrow(objRef);
			
			NameComponent nmCities[][] = {
				{ new NameComponent("muenchen", "")   },
				{ new NameComponent("landshut", "")   },
				{ new NameComponent("vilsbiburg", "") },
				{ new NameComponent("berlin", "")     }
			};

			NameComponent nmClubs[][] = {
				{ new NameComponent("fussball", "")   },
				{ new NameComponent("volleyball", "") },
				{ new NameComponent("tennis", "")     },
				{ new NameComponent("schwimmen", "")  }
			};
			
			NameComponent nmServants[][] = {
				{ new NameComponent("sepp", "")     },
				{ new NameComponent("hans", "")     },
				{ new NameComponent("peter", "")    },
				{ new NameComponent("georg", "")    },
				{ new NameComponent("wolfgang", "") },
				{ new NameComponent("franz", "")    }
			};
			
			NamingContext ncCity;
			NamingContext ncClub;
			Servant servant;
			for (NameComponent[] nmCity : nmCities) {
				ncCity = ncRoot.new_context();
				ncRoot.rebind_context(nmCity, ncCity);
				for (NameComponent[] nmClub : nmClubs) {
					ncClub = ncCity.new_context();
					ncCity.rebind_context(nmClub, ncClub);
					for (NameComponent[] nmServant : nmServants) {
						servant = new Servant();
						orb.connect(servant);
						ncClub.rebind(nmServant, servant);
					}
				}
			}
			
			//NameComponent nmMuenchen[] = { new NameComponent("muenchen", "") };
			//NamingContext ncMuenchen = ncRoot.new_context();
			//ncRoot.rebind_context(nmMuenchen, ncMuenchen);
			
			//NameComponent nmBayern[] = { new NameComponent("fcBayern", "") };
			//NamingContext ncBayern = ncMuenchen.new_context();
			//ncMuenchen.rebind_context(nmBayern, ncBayern);
			
			//servRef = new Servant();
			//orb.connect(servRef);
			//NameComponent nmHans[] = { new NameComponent("hans", "") };
			//ncBayern.rebind(nmHans, servRef);
			
			java.lang.Object sync = new java.lang.Object();
			synchronized (sync) {
				sync.wait();
			}
		} catch (Exception e) {
			System.out.println("Error: " + e);
			e.printStackTrace(System.out);
		}
	}
}

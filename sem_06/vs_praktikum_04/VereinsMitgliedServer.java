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

			String names[] = {
				"sepp",
				"hans",
				"peter",
				"georg",
				"wolfgang",
				"franz"
			};

			NameComponent nmServants[][] = {
				{ new NameComponent(names[0], "") },
				{ new NameComponent(names[1], "") },
				{ new NameComponent(names[2], "") },
				{ new NameComponent(names[3], "") },
				{ new NameComponent(names[4], "") },
				{ new NameComponent(names[5], "") }
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
					for (int i = 0; i < names.length; i++) {
						servant = new Servant(names[i]);
						servant.addVerein("tennis");
						orb.connect(servant);
						ncClub.rebind(nmServants[i], servant);
					}
				}
			}

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

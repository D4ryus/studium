import org.omg.CORBA.ORB;
import org.omg.CosNaming.Binding;
import org.omg.CosNaming.BindingIteratorHolder;
import org.omg.CosNaming.BindingListHolder;
import org.omg.CosNaming.BindingType;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;

import Verein.VereinsMitglied;
import Verein.VereinsMitgliedHelper;

public class VereinsMitgliedClient {
	public static void main(String args[]) {
		try {
			ORB orb = ORB.init(args, null);
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			NamingContext ncRef = NamingContextHelper.narrow(objRef);

			NameComponent city[] = { new NameComponent("muenchen", "") };
			ncRef = NamingContextHelper.narrow(ncRef.resolve(city));

			NameComponent club[] = { new NameComponent("fussball", "") };
			ncRef = NamingContextHelper.narrow(ncRef.resolve(club));

			NameComponent serv[] = { new NameComponent("franz", "") };

			BindingListHolder bl = new BindingListHolder();
			BindingIteratorHolder blIt= new BindingIteratorHolder();

			ncRef.list(1000, bl, blIt);
			Binding bindings[] = bl.value;

			if (bindings.length == 0) {
				return;
			}

			for (int i = 0; i < bindings.length; i++) {
				org.omg.CORBA.Object obj = ncRef.resolve(bindings[i].binding_name);
				String objStr = orb.object_to_string(obj);
				int lastIx = bindings[i].binding_name.length - 1;

				if (bindings[i].binding_type == BindingType.ncontext) {
					System.out.println("Context: " + bindings[i].binding_name[lastIx].id);
				} else {
					System.out.println("Object: " + bindings[i].binding_name[lastIx].id);
				}
			}
		} catch (Exception e) {
			System.out.println("Error: " + e);
			e.printStackTrace(System.out);
		}
	}
}

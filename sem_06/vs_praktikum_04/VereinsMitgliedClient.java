import java.util.LinkedList;

import org.omg.CORBA.ORB;
import org.omg.CosNaming.Binding;
import org.omg.CosNaming.BindingIteratorHolder;
import org.omg.CosNaming.BindingListHolder;
import org.omg.CosNaming.BindingType;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;

import Verein.*;
import Verein.VereinsMitgliedPackage.*;

public class VereinsMitgliedClient {

	public static void main(String args[]) {
		try {
			ORB orb = ORB.init(args, null);
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			NamingContext ncRef = NamingContextHelper.narrow(objRef);
			print_context(orb, ncRef, "muenchen");
			print_context(orb, ncRef, "muenchen/tennis");
			print_user_info(get_user(orb, ncRef, "muenchen/tennis/hans"));
			print_user_info(get_user(orb, ncRef, "muenchen/tennis/sepp"));
			print_user_info(get_user(orb, ncRef, "muenchen/tennis/franz"));
		} catch (Exception e) {
			System.out.println("Error: " + e);
			e.printStackTrace(System.out);
		}
	}

	public static NamingContext print_context(ORB orb, NamingContext root, String name)
			throws Exception {
		NamingContext nc = get_context(orb, root, name);
		System.out.printf("Context %s:\n", name);
		BindingListHolder bl = new BindingListHolder();
		BindingIteratorHolder blIt= new BindingIteratorHolder();

		nc.list(1000, bl, blIt);
		Binding bindings[] = bl.value;
		if (bindings.length == 0) {
			return null;
		}

		for (int i = 0; i < bindings.length; i++) {
			int lastIx = bindings[i].binding_name.length-1;

			if (bindings[i].binding_type == BindingType.ncontext) {
				System.out.println("    Context: " +
					bindings[i].binding_name[lastIx].id);
			} else {
				System.out.println("    Object: " +
					bindings[i].binding_name[lastIx].id);
			}
		}
		if (bindings.length != 0) {
			return nc;
		}

		return null;
	}

	public static VereinsMitglied get_user(ORB orb, NamingContext root, String path)
			throws Exception {
		NamingContext nc = get_context(orb, root, path.substring(0, path.lastIndexOf("/")));
		String name = path.substring(path.lastIndexOf("/") + 1, path.length());

		BindingListHolder bl = new BindingListHolder();
		BindingIteratorHolder blIt= new BindingIteratorHolder();

		nc.list(1000, bl, blIt);
		Binding bindings[] = bl.value;
		if (bindings.length == 0) {
			return null;
		}

		for (int i = 0; i < bindings.length; i++) {
			org.omg.CORBA.Object obj = nc.resolve(bindings[i].binding_name);
			int lastIx = bindings[i].binding_name.length-1;

			if (bindings[i].binding_name[lastIx].id.equals(name)) {
				return VereinsMitgliedHelper.narrow(obj);
			}
		}
		return null;
	}

	public static void print_user_info(VereinsMitglied user) {
		System.out.printf("Name: %s, Vereine:\n", user.mname());
		for (verein v : user.mvereine()) {
			System.out.printf("    %s, Beitrag: %d\n", v.vname, v.vbeitrag);
		}
		return;
	}

	public static NamingContext get_context(ORB orb, NamingContext root, String name)
			throws Exception {
		String names[] = name.split("/");
		NameComponent tmp[] = new NameComponent[names.length];

		for (int i = 0; i < names.length; i++) {
			tmp[i] = new NameComponent(names[i], "");
		}

		return NamingContextHelper.narrow(root.resolve(tmp));
	}
}

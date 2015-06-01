import java.util.LinkedList;

import Verein._VereinsMitgliedImplBase;
import Verein.VereinsMitgliedPackage.*;

public class Servant extends _VereinsMitgliedImplBase {
	private static final long serialVersionUID = -2832463024059762637L;
	private String mname;
	LinkedList<verein>mvereine = new LinkedList<verein>();

	public Servant(String mname) {
		this.mname = mname;
	}

	@Override
	public String mname() {
		return mname;
	}

	@Override
	public verein[] mvereine() {
		return mvereine.toArray(new verein[mvereine.size()]);
	}

	@Override
	public short erhoeheBeitrag(String verein, short erhoehung) {
		for (verein v : mvereine) {
			if (v.vname.equals(verein)) {
				v.vbeitrag += erhoehung;
				return v.vbeitrag;
			}
		}
		return 0;
	}

	public void addVerein(String verein) {
		mvereine.push(new verein(verein, (short)0));
	}
}

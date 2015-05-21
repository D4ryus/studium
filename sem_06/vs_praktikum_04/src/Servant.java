import Verein._VereinsMitgliedImplBase;
import Verein.VereinsMitgliedPackage.verein;

public class Servant extends _VereinsMitgliedImplBase {
	private static final long serialVersionUID = -2832463024059762637L;
	private String mname;
	private verein[] mvereine;

	@Override
	public String mname() {
		return mname;
	}

	@Override
	public verein[] mvereine() {
		return mvereine;
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
}

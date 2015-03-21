public class BankException extends Exception {

    private static final long serialVersionUID = -1998388662089722336L;

    public BankException(String message) {
        super(message);
    }
    public BankException(String message, Throwable cause) {
        super(message, cause);
    }
    public BankException(Throwable cause) {
        super(cause);
    }
}

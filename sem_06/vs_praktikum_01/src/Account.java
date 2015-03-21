import java.io.Serializable;

public class Account implements java.io.Serializable
{
    private static final long serialVersionUID = -6517669675215068870L;

    private String name;
    private String password;
    private int number;
    private double balance;

    /**
     * @param name
     * @param password
     */
    public Account(String name, String password, int number) {
        this.name = name;
        this.password = password;
        this.number = number;
        this.balance = 0.0;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @return the number
     */
    public int getNumber() {
        return number;
    }

    /**
     * @return the password
     */
    public String getPassword() {
        return password;
    }

    /**
     * @param password the password to set
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * @return the balance
     */
    public double getBalance() {
        return balance;
    }

    /**
     * @param balance the balance to set
     */
    public void setBalance(double balance) {
        this.balance = balance;
    }
}

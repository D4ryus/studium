import java.util.Date;

public class Message implements java.io.Serializable
{
    private static final long serialVersionUID = -6517669675215068870L;

    private String name;
    private Date date;
    private String message;

    /**
     * @param name
     * @param password
     */
    public Message(String name, Date date, String message) {
        this.name = name;
        this.date = date;
        this.message = message;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @return the date
     */
    public Date getDate() {
        return date;
    }

    /**
     * @return the message
     */
    public String getMessage() {
        return message;
    }
}

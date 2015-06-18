package it_05;

import javax.jws.*;

@WebService
public interface WeatherInt {
	@WebMethod public int getTemp(String date);
	@WebMethod public String getRain(String date);
}

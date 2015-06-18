package it_05;

import javax.jws.*;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

import java.util.Random;

@WebService
@SOAPBinding(style = Style.RPC)
public class Weather implements WeatherInt {

	@Override
	public int getTemp(String datum) {
		return new Random().nextInt(31);
	}

	@Override
	public String getRain(String datum) {
		if(new Random().nextBoolean()){
			return "Rain";
		} else {
			return "Sunshine";
		}
	}
}

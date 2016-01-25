package ru.spb.trak.homesteads;

/**
 * Created by uv.ivanov@jet.msk.su on 25.01.2016.
 */
public class NoControlSocketException extends Exception {
    public NoControlSocketException() {};
    public NoControlSocketException(String message) {
        super(message);
    }
}

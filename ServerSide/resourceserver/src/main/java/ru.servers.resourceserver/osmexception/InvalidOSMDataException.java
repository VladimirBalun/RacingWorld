package ru.servers.osmexception;

public class InvalidOSMDataException extends Exception {

    public InvalidOSMDataException () {
        super();
    }

    public InvalidOSMDataException (String message) {
        super(message);
    }

}
package ru.servers.resourceserver.osmexception;

import org.xml.sax.SAXException;

public class InvalidOSMDataException extends SAXException {

    public InvalidOSMDataException(String message, Exception e) {
        super(message, e);
    }

}
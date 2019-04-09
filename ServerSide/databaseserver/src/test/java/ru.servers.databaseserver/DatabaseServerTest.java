package ru.servers.databaseserver;

import org.junit.Test;
import ru.servers.databaseserver.network.DatabaseServer;

import java.rmi.RemoteException;

public class DatabaseServerTest {

    @Test
    public void checkingInitializationDatabaseServer() throws RemoteException {
        new DatabaseServer();
    }

}

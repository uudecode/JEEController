package ru.spb.trak.homesteads;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.annotation.PreDestroy;
import javax.ejb.Remove;
import javax.ejb.Singleton;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;

/**
 * Created by trak on 1/14/2016.
 */
@Singleton(name = "ControllerEJB")
public class ControllerBean {
    private static final Logger logger = LoggerFactory.getLogger(ControllerBean.class);
    private static final int PORT_NUMBER = 37001;
    private static final int SOCKET_TIMEOUT = 1000;
    private static ServerSocket controlServerSocket = null;
    private static Socket controlSocket = null;

    public ControllerBean() throws Exception {
        if (null == controlServerSocket)
            try {
                controlServerSocket = new ServerSocket(PORT_NUMBER);
                controlServerSocket.setSoTimeout(SOCKET_TIMEOUT);
                logger.info("Listening port: " + PORT_NUMBER);
            } catch (Exception e) {
                String message = "Can't listen port: " + PORT_NUMBER + " error is: " + e.getMessage();
                logger.error(message);
                throw new Exception(message);
            }

        logger.info("Bean started");
    }

    public String doBarrel() {
        String result = "nothing :(";
        if (null != controlServerSocket) {
            if (null == controlSocket) {
                try {
                    controlSocket = controlServerSocket.accept();
                } catch (SocketTimeoutException timeoutException) {
                    System.out.println("Nobody wait control");
                    result += "Nobody wait control";
                } catch (Exception e) {
                    System.out.println("Got other exception: " + e.getMessage());
                }
            } else {
                System.out.println("Socket already exists ?");
            }
        }

        if (null != controlSocket && controlSocket.isConnected()) {
            try {

                DataOutputStream outToClient = new DataOutputStream(controlSocket.getOutputStream());
                String leCommando = "STATUS\n";
                outToClient.writeBytes(leCommando);

                String arduinoAnswer;
                BufferedReader inFromClient = new BufferedReader(new InputStreamReader(controlSocket.getInputStream()));
                arduinoAnswer = inFromClient.readLine();
                System.out.println("Received: " + arduinoAnswer);
                result = arduinoAnswer;
            } catch (Exception e) {
                System.out.println("got error, while comminicate with client: " + e.getMessage());
            }
        }
        return result;
    }

    @Remove
    @PreDestroy
    public void closeAll() {
        logger.info("Close all!");
        try {
            controlSocket.close();
            logger.debug("controlSocket closed!");
        } catch (Exception e) {
            logger.error("Can't close controlSocket, got error: ", e.getMessage());
        }
        try {
            controlServerSocket.close();
            logger.debug("controlServerSocket closed!");
        } catch (Exception e) {
            logger.error("Can't close controlServerSocket, got error:", e.getMessage());
        }
    }
}

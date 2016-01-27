package ru.spb.trak.homesteads;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.annotation.PreDestroy;
import javax.ejb.LocalBean;
import javax.ejb.Remove;
import javax.ejb.Singleton;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.charset.Charset;

/**
 * Created by trak on 1/14/2016.
 */


@Singleton(name = "ControllerEJB")
@LocalBean
public class ControllerBean {
    private static final Logger logger = LoggerFactory.getLogger(ControllerBean.class);
    private static final int PORT_NUMBER = 37001;
    private static final int SERVER_SOCKET_TIMEOUT = 5000;
    private static final int SOCKET_TIMEOUT = 2000;
    private static ServerSocket controlServerSocket = null;
    private static Socket controlSocket = null;
    private static DataOutputStream outToClient = null;
    private static BufferedReader inFromClient = null;

    public ControllerBean() throws Exception {
        logger.debug("Starting bean");
        if (null == controlServerSocket )
            try {
                controlServerSocket = new ServerSocket(PORT_NUMBER);
                logger.info("Listening port: " + PORT_NUMBER);
                logger.info("some about controlServerSocket: {}",controlServerSocket.toString());
            } catch (Exception e) {
                String message = "Can't listen port: " + PORT_NUMBER + " error is: " + e.getMessage();
                logger.error(message);
                throw new Exception(message);
            }

        try {
            controlServerSocket.setSoTimeout(SERVER_SOCKET_TIMEOUT);
            logger.info("some about controlSocket.isConnected: {}",controlSocket.isConnected());
            logger.info("some about controlSocket.isBound: {}",controlSocket.isBound());
            logger.info("some about controlSocket.getInetAddress: {}",controlSocket.getInetAddress());
        } catch (Exception e) {
            String message = "Can't get control socket:  error is: " + e.getMessage();
            logger.error(message);
        }
        logger.info("Bean started");
    }

    private void checkConnect() throws Exception {
        try {
            logger.debug("controlSocket.getInetAddress: {}",controlSocket.getInetAddress());
            logger.debug("controlSocket.isConnected: {}",controlSocket.isConnected());
            logger.debug("controlSocket.isBound: {}",controlSocket.isBound());
            logger.debug("controlSocket.isClosed: {}",controlSocket.isClosed());
        }catch (Exception e) {
            logger.error("Can't check controlSocket, error is: {}",e.getMessage());
        }
        if (null == controlSocket || !controlSocket.isConnected()) {
            try {
                controlSocket = controlServerSocket.accept();
                controlSocket.setSoTimeout(SOCKET_TIMEOUT);
                if (null == outToClient ) {
                    outToClient = new DataOutputStream(controlSocket.getOutputStream());
                }
                if (null == inFromClient ) {
                    inFromClient = new BufferedReader(new InputStreamReader(controlSocket.getInputStream(), "UTF-8"));
                }

            } catch (SocketTimeoutException timeoutException) {
                throw new NoControlSocketException("No Arduino controller connected.");
            }
        }
    }

    private void sendCommand(String command) throws Exception {
        checkConnect();
        outToClient.write(command.getBytes(Charset.forName("UTF-8")));
        outToClient.flush();
        logger.debug("Command: {} successfully sended to Arduino.", command);
    }

    private String receiveAnswer() throws Exception {
        String result = new String();
        try {
            checkConnect();
            String partAnswer;
            while ((partAnswer = inFromClient.readLine()) != null) {
                result += partAnswer;
            }
        } catch (SocketTimeoutException ignoredException) {
        }
        return result;
    }

    public String getHomesteadStatus() {
        String command = "getConfig\n";
        String result = new String();

        try {
            sendCommand(command);
        } catch (Exception e) {
            logger.error("Can't send command: {}, got error: {}",command, e.getMessage());
        }

        try {
            result = receiveAnswer();
        } catch (Exception e) {
            logger.error("Can't receive answer, got error: {}", e.getMessage());
        }
        logger.debug(result);
        return result;

    }

    public String turnSwitch(String uuid,String state) {
        String command = "turn" + (state.equals("ON")? "On:" : "Off:") + uuid + "\n";
        String result = new String();
        try {
            sendCommand(command);
        } catch (Exception e) {
            logger.error("Can't send command: {}, got error: {}",command, e.getMessage());
        }

        try {
            result = receiveAnswer();
        } catch (Exception e) {
            logger.error("Can't receive answer, got error: {}", e.getMessage());
        }
        logger.debug(result);

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

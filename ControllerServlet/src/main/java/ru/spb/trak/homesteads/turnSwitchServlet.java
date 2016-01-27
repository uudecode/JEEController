package ru.spb.trak.homesteads;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Created by uv.ivanov@jet.msk.su on 27.01.2016.
 */
@WebServlet(name = "turnSwitch", urlPatterns = "/turnSwitch")
public class turnSwitchServlet extends HttpServlet {
    private static final Logger logger = LoggerFactory.getLogger(turnSwitchServlet.class);
    @EJB(name = "ControllerEJB")
    ControllerBean controller;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        logger.debug("turnSwitch request from: {} path: {}", request.getRemoteAddr(), request.getPathInfo());
        String uuid = request.getParameter("uuid");
        String state = request.getParameter("state");
        String answerFromHomestead = controller.turnSwitch(uuid,state);
        logger.debug("got answer: {}",answerFromHomestead);
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        out.println(answerFromHomestead);

    }
}

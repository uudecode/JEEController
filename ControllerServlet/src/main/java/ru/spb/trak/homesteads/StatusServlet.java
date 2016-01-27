package ru.spb.trak.homesteads;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.w3c.dom.Document;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.StringWriter;

/**
 * Created by trak on 1/14/2016.
 */
@WebServlet(name = "Status", urlPatterns = "/getStatus")
public class StatusServlet extends HttpServlet {
    private static final Logger logger = LoggerFactory.getLogger(StatusServlet.class);
    private static final String XSLT = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
            "<xsl:stylesheet\n" +
            "        xmlns:xsl=\n" +
            "                \"http://www.w3.org/1999/XSL/Transform\"\n" +
            "        version=\"1.0\"\n" +
            ">\n" +
            "    <xsl:output method=\"html\"/>\n" +
            "    <xsl:template match=\"/\">\n" +
            "        <xsl:apply-templates/>\n" +
            "    </xsl:template>\n" +
            "\n" +
            "    <xsl:template match=\"/Homestead/Locations/Location/Switches/Switch\">\n" +
            "        <div class=\"row\">\n" +
            "\n" +
            "            <div class=\"col s12 m6 l3 brown lighten-4\">\n" +
            "                <xsl:attribute name=\"id\">\n" +
            "                    <xsl:value-of select=\"@uuid\"/>\n" +
            "                </xsl:attribute>\n" +
            "                <span class=\"flow-text\">\n" +
            "                    <xsl:value-of select=\"@name\"/>\n" +
            "                </span>\n" +
            "            </div>\n" +
            "            <div >\n" +
            "                <xsl:attribute name=\"class\">\n" +
            "                    <xsl:if test=\"@state ='ON'\">col s12 m3 l2 green darken-4</xsl:if>\n" +
            "                    <xsl:if test=\"@state ='OFF'\">col s12 m3 l2 red lighten-2</xsl:if>\n" +
            "                </xsl:attribute>\n" +
            "                <xsl:attribute name=\"id\">lbl_<xsl:value-of select=\"@uuid\"/></xsl:attribute>\n" +
            "                <span class=\"flow-text\">\n" +
            "                    <xsl:attribute name=\"id\">lbl_spn_<xsl:value-of select=\"@uuid\"/></xsl:attribute>\n" +
            "                    <xsl:if test=\"@state ='ON'\">ВКЛЮЧЕН</xsl:if>\n" +
            "                    <xsl:if test=\"@state ='OFF'\">ВЫКЛЮЧЕН</xsl:if>\n" +
            "                </span>\n" +
            "            </div>\n" +
            "            <div>\n" +
            "                <xsl:attribute name=\"class\">\n" +
            "                    <xsl:if test=\"@state ='ON'\">col s12 m3 l1 waves-effect waves-light btn red</xsl:if>\n" +
            "                    <xsl:if test=\"@state ='OFF'\">col s12 m3 l1 waves-effect waves-light btn green</xsl:if>\n" +
            "                </xsl:attribute>\n" +
            "                <xsl:attribute name=\"id\">btn_<xsl:value-of select=\"@uuid\"/></xsl:attribute>\n" +
            "                <a class=\"flow-text\">\n" +
            "                    <xsl:attribute name=\"id\">btn_spn_<xsl:value-of select=\"@uuid\"/></xsl:attribute>\n" +
            "                    <xsl:attribute name=\"state\"><xsl:value-of select=\"@state\"/></xsl:attribute>\n" +
            "                    <xsl:attribute name=\"onclick\">turn(\"<xsl:value-of select=\"@uuid\"/>\",this.getAttribute(\"state\"));</xsl:attribute><xsl:if test=\"@state ='ON'\">ВЫКЛЮЧИТЬ</xsl:if><xsl:if test=\"@state ='OFF'\">ВКЛЮЧИТЬ</xsl:if></a>\n" +
            "            </div>\n" +
            "        </div>\n" +
            "    </xsl:template>\n" +
            "\n" +
            "\n" +
            "    <xsl:template match=\"/Homestead/Locations/Location/Sensors/Sensor\">\n" +
            "        <div class=\"row\">\n" +
            "\n" +
            "            <div class=\"col s12 m6 l3 blue-grey lighten-4\">\n" +
            "                <xsl:attribute name=\"id\">\n" +
            "                    <xsl:value-of select=\"@uuid\"/>\n" +
            "                </xsl:attribute>\n" +
            "                <span class=\"flow-text\">\n" +
            "                    <xsl:value-of select=\"@name\"/>\n" +
            "                </span>\n" +
            "            </div>\n" +
            "            <div class=\"col s12 m3 l3 deep-orange accent-1\">\n" +
            "                <xsl:attribute name=\"id\">\n" +
            "                    <xsl:value-of select=\"@uuid\"/>\n" +
            "                </xsl:attribute>\n" +
            "                <span class=\"flow-text\">\n" +
            "                    <xsl:value-of select=\"@data\"/>\n" +
            "                </span>\n" +
            "            </div>\n" +
            "\n" +
            "        </div>\n" +
            "    </xsl:template>\n" +
            "\n" +
            "    <xsl:template match=\"/Homestead/Locations/Location\">\n" +
            "        <div class=\"row\">\n" +
            "\n" +
            "            <div class=\"col s12 m6 teal lighten-2\">\n" +
            "                <xsl:attribute name=\"id\">\n" +
            "                    <xsl:value-of select=\"@uuid\"/>\n" +
            "                </xsl:attribute>\n" +
            "                <span class=\"flow-text\">\n" +
            "                    <xsl:value-of select=\"@name\"/>\n" +
            "                </span>\n" +
            "            </div>\n" +
            "        </div>\n" +
            "        <xsl:apply-templates select=\"./Sensors/Sensor\"/>\n" +
            "        <xsl:apply-templates select=\"./Switches/Switch\"/>\n" +
            "    </xsl:template>\n" +
            "\n" +
            "    <xsl:template match=\"/Homestead\">\n" +
            "        <div class=\"row\">\n" +
            "\n" +
            "            <div class=\"col s12 m6 blue lighten-2\">\n" +
            "                <span class=\"flow-text\">\n" +
            "                    <xsl:value-of select=\"@name\"/>\n" +
            "                </span>\n" +
            "            </div>\n" +
            "        </div>\n" +
            "        <xsl:apply-templates select=\"./Locations/Location\"/>\n" +
            "    </xsl:template>\n" +
            "\n" +
            "\n" +
            "\n" +
            "</xsl:stylesheet>";

    @EJB(name = "ControllerEJB")
    ControllerBean controller;

    public static Document stringToDom(String xmlSource)
            throws SAXException, ParserConfigurationException, IOException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        return builder.parse(new InputSource(new StringReader(xmlSource)));
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        logger.debug("getStatus request from: {} path: {}", request.getRemoteAddr(), request.getPathInfo());

        // Set the response message's MIME type
        response.setContentType("text/html;charset=UTF-8");
        // Allocate a output writer to write the response message into the network socket
        PrintWriter out = response.getWriter();

        String answerFromHomestead = controller.getHomesteadStatus();
        String status = new String();

        try {
            Document answerXML = stringToDom(answerFromHomestead);
            logger.debug("Answer parsed!");
            try {
                StringWriter outWriter = new StringWriter();
                StreamResult result = new StreamResult(outWriter);
                TransformerFactory transformerFactory = TransformerFactory.newInstance();
                Source stylesheetSource = new StreamSource(new StringReader(XSLT));
                Transformer transformer = transformerFactory.newTransformer(stylesheetSource);
                transformer.setOutputProperty("indent","yes");
                transformer.transform(new DOMSource(answerXML), result);
                StringBuffer sb = outWriter.getBuffer();
                status = sb.toString();
                logger.debug("HTML: {}",status);

            } catch (Exception e) {
                logger.error("Can't transform answer to HTML, got error: {}", e.getMessage());
                status = "<h1 class=\"header center orange-text\">Error transform XML</h1><p>" + e.getMessage() + "</p>" + answerFromHomestead;

            }

        } catch (Exception e) {
            logger.error("Can't parse answer as XML, got error: {}", e.getMessage());
            status = "<h1 class=\"header center orange-text\">Error parsing XML</h1>" + e.getMessage() + answerFromHomestead;
        }

        // Write the response message, in an HTML page
        try {
            out.println(status);
        } finally {
            //out.close();  // Always close the output writer
        }
    }
}
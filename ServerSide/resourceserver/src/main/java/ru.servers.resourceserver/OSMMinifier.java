package ru.servers.resourceserver;

import lombok.extern.log4j.Log4j;
import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import ru.servers.resourceserver.osmexception.InvalidOSMDataException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.IOException;
import java.io.StringReader;
import java.io.StringWriter;

@Log4j
public class OSMMinifier {

    public String minify(String osmData) throws InvalidOSMDataException {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            InputSource inputSource = new InputSource(new StringReader(osmData));
            Document document = builder.parse(inputSource);
            document.setXmlStandalone(true);

            attributesDelete("node", document);
            attributesDelete("way", document);
            attributesDelete("relation", document);

            return getStringFromDocument(document);
        } catch (SAXException | IOException | ParserConfigurationException | TransformerException e) {
            log.warn("Minification error. Cause: " + e.getMessage());
            throw new InvalidOSMDataException("Minification error. Cause: " + e.getMessage());
        }
    }

    private String getStringFromDocument(Document document) throws TransformerException {
        DOMSource domSource = new DOMSource(document);
        StringWriter writer = new StringWriter();
        StreamResult result = new StreamResult(writer);
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        transformer.transform(domSource, result);
        return writer.toString();
    }

    private void attributesDelete(String attributeName, Document document) {
        NodeList nodeList = document.getElementsByTagName(attributeName);
        for (int i = 0; i < nodeList.getLength(); ++i) {
            Node node = document.getElementsByTagName(attributeName).item(i);
            NamedNodeMap namedNodeMap = node.getAttributes();
            removeAttributeIfExists(namedNodeMap, "version");
            removeAttributeIfExists(namedNodeMap, "changeset");
            removeAttributeIfExists(namedNodeMap, "timestamp");
            removeAttributeIfExists(namedNodeMap, "user");
            removeAttributeIfExists(namedNodeMap, "uid");
            removeAttributeIfExists(namedNodeMap, "visible");
        }
    }

    private void removeAttributeIfExists(NamedNodeMap namedNodeMap, String attributeName) {
        if (namedNodeMap.getNamedItem(attributeName) != null) {
            namedNodeMap.removeNamedItem(attributeName);
        }
    }

}
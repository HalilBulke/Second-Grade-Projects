import java.io.File;
import java.util.HashMap;
import java.util.Map;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;


public class XMLParser {
    /**
     * TODO: Parse the input XML file and return a dictionary as described in the assignment insturctions
     *
     * @param filename the input XML file
     * @return a dictionary as described in the assignment insturctions
     */
    public static Map<String, Malware> parse(String filename) {
        // TODO: YOUR CODE HERE
        Map<String, Malware> malwareDB = new HashMap<>();
        File inputFile = new File(filename);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        try {
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            NodeList nodeList = doc.getElementsByTagName("row");
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node nNode = nodeList.item(i);

                if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element eElement = (Element) nNode;
                    malwareDB.put(eElement.getElementsByTagName("hash").item(0).getTextContent(),
                            new Malware(eElement.getElementsByTagName("title").item(0).getTextContent(),
                            Integer.parseInt(eElement.getElementsByTagName("level").item(0).getTextContent()),
                            eElement.getElementsByTagName("hash").item(0).getTextContent()));

                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return malwareDB;
    }
}

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class MissionExploration {

    /**
     * Given a Galaxy object, prints the solar systems within that galaxy.
     * Uses exploreSolarSystems() and printSolarSystems() methods of the Galaxy object.
     *
     * @param galaxy a Galaxy object
     */
    public void printSolarSystems(Galaxy galaxy) {
        // TODO: YOUR CODE HERE
        galaxy.printSolarSystems(galaxy.exploreSolarSystems());
    }

    /**
     * TODO: Parse the input XML file and return a list of Planet objects.
     *
     * @param filename the input XML file
     * @return a list of Planet objects
     */
    public Galaxy readXML(String filename) {
        List<Planet> planetList = new ArrayList<>();

        File inputFile = new File(filename);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        try {
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            NodeList nodeList = doc.getElementsByTagName("Galaxy");
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node nNode = nodeList.item(i);
                if (nNode.getNodeType() == Node.ELEMENT_NODE) {

                    Element eElement = (Element) nNode;
                    for(int j = 0; j < eElement.getElementsByTagName("Planet").getLength(); j++){
                        List<String> neighbors=new ArrayList<>();
                        String [] s= eElement.getElementsByTagName("Neighbors").item(j).getTextContent().replaceAll("\\s+"," ").split(" ");
                        for(int e=1;e<s.length;e++){
                            neighbors.add(s[e]);
                        }
                        planetList.add(new Planet(eElement.getElementsByTagName("ID").item(j).getTextContent(),
                                Integer.parseInt(eElement.getElementsByTagName("TechnologyLevel").item(j).getTextContent()),
                                neighbors));

                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return new Galaxy(planetList);
    }
}

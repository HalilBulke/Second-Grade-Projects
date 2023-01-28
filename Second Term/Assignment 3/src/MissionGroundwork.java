import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.util.*;

public class MissionGroundwork {

    /**
     * Given a list of Project objects, prints the schedule of each of them.
     * Uses getEarliestSchedule() and printSchedule() methods of the current project to print its schedule.
     * @param projectList a list of Project objects
     */
    public void printSchedule(List<Project> projectList) {
        // TODO: YOUR CODE HERE
        for (Project p:projectList) {
            p.printSchedule(p.getEarliestSchedule());
        }
    }

    /**
     * TODO: Parse the input XML file and return a list of Project objects
     *
     * @param filename the input XML file
     * @return a list of Project objects
     */
    public List<Project> readXML(String filename) {
        List<Project> projectList = new ArrayList<>();
        // TODO: YOUR CODE HERE
        File inputFile = new File(filename);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        try {
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            NodeList nodeList = doc.getElementsByTagName("Project");
            for (int i = 0; i < nodeList.getLength(); i++) {
                List<Task> tasks = new ArrayList<>();
                Node nNode = nodeList.item(i);
                if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element eElement = (Element) nNode;
                    for(int j = 0; j < eElement.getElementsByTagName("Task").getLength(); j++){
                        List<Integer> dependencies = new ArrayList<>();
                        if(j==0) {
                            tasks.add(new Task(Integer.parseInt(eElement.getElementsByTagName("TaskID").item(j).getTextContent()),
                                    eElement.getElementsByTagName("Description").item(j).getTextContent(),
                                    Integer.parseInt(eElement.getElementsByTagName("Duration").item(j).getTextContent()),dependencies));
                        }else{
                            String [] s= eElement.getElementsByTagName("Dependencies").item(j).getTextContent().replaceAll("\\s+"," ").split(" ");
                            for (int e=1;e<s.length;e++) {
                                dependencies.add(Integer.parseInt(s[e]));
                            }
                            tasks.add(new Task(Integer.parseInt(eElement.getElementsByTagName("TaskID").item(j).getTextContent()),
                                    eElement.getElementsByTagName("Description").item(j).getTextContent(),
                                    Integer.parseInt(eElement.getElementsByTagName("Duration").item(j).getTextContent()),dependencies));
                        }
                    }
                    projectList.add(new Project(eElement.getElementsByTagName("Name").item(0).getTextContent(),tasks));
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return projectList;
    }


}

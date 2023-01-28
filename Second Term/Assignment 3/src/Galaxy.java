import java.util.*;

public class Galaxy {

    private final List<Planet> planets;
    private List<SolarSystem> solarSystems;

    public Galaxy(List<Planet> planets) {
        this.planets = planets;
    }

    /**
     * Using the galaxy's list of Planet objects, explores all the solar systems in the galaxy.
     * Saves the result to the solarSystems instance variable and returns a shallow copy of it.
     *
     * @return List of SolarSystem objects.
     */
    public List<SolarSystem> exploreSolarSystems() {
        solarSystems = new ArrayList<>();
        // TODO: YOUR CODE HERE
        Map<String,Integer> idDic=new HashMap<>();
        Map<Integer,String> intDic=new HashMap<>();
        Collections.sort(planets);
        int index=-1;
        for(Planet p:planets){
            index+=1;
            idDic.put(p.getId(),index);
            intDic.put(index,p.getId());
        }
        Graph g=new Graph(planets.size());
        for(Planet p:planets){
            for(String id:p.getNeighbors()) {
                g.addEdge(idDic.get(p.getId()), idDic.get(id));
            }
        }
        ConnectedC cc=new ConnectedC(g);

        for(int k=0;k<cc.count();k++){
            SolarSystem solars=new SolarSystem();
            int ind=-1;
            for(int il:cc.getId()){
                ind+=1;
                if(k==il) {
                    solars.addPlanet(planets.get(ind));
                }
            }
            solarSystems.add(solars);
        }


        return new ArrayList<>(solarSystems);
    }

    public List<SolarSystem> getSolarSystems() {
        return solarSystems;
    }


    // FOR TESTING
    public List<Planet> getPlanets() {
        return planets;
    }

    // FOR TESTING
    public int getSolarSystemIndexByPlanetID(String planetId) {
        for (int i = 0; i < solarSystems.size(); i++) {
            SolarSystem solarSystem = solarSystems.get(i);
            if (solarSystem.hasPlanet(planetId)) {
                return i;
            }
        }
        return -1;
    }

    public void printSolarSystems(List<SolarSystem> solarSystems) {
        System.out.printf("%d solar systems have been discovered.%n", solarSystems.size());
        for (int i = 0; i < solarSystems.size(); i++) {
            SolarSystem solarSystem = solarSystems.get(i);
            List<Planet> planets = new ArrayList<>(solarSystem.getPlanets());
            Collections.sort(planets);
            System.out.printf("Planets in Solar System %d: %s", i + 1, planets);
            System.out.println();
        }
    }
}

import java.util.*;

public class SubspaceCommunicationNetwork {

    private List<SolarSystem> solarSystems;

    /**
     * Perform initializations regarding your implementation if necessary
     * @param solarSystems a list of SolarSystem objects
     */
    public SubspaceCommunicationNetwork(List<SolarSystem> solarSystems) {
        // TODO: YOUR CODE HERE
        this.solarSystems = solarSystems;
    }

    /**
     * Using the solar systems of the network, generates a list of HyperChannel objects that constitute the minimum cost communication network.
     * @return A list HyperChannel objects that constitute the minimum cost communication network.
     */
    public List<HyperChannel> getMinimumCostCommunicationNetwork() {
        List<HyperChannel> minimumCostCommunicationNetwork = new ArrayList<>();
        // TODO: YOUR CODE HERE
        ArrayList<Planet> maxPlanets=new ArrayList<>();
        for(SolarSystem s:solarSystems){
            Planet maxP=s.getPlanets().get(0);
            for(Planet p:s.getPlanets()){
                if(p.getTechnologyLevel()>maxP.getTechnologyLevel()){
                    maxP=p;
                }
            }
            maxPlanets.add(maxP);
        }
        Map<String,Integer> idDic=new HashMap<>();
        Map<Integer,Planet> intDic=new HashMap<>();
        int index=-1;
        for(Planet planet:maxPlanets){
            index+=1;
            idDic.put(planet.getId(),index);
            intDic.put(index, planet);
        }
        EdgeWeightedGraph weightedGraph=new EdgeWeightedGraph(maxPlanets.size());

        for (int i=0;i<maxPlanets.size()-1;i++){
            for (int j=i+1;j<maxPlanets.size();j++){
                double cost=(Constants.SUBSPACE_COMMUNICATION_CONSTANT)/((double)(maxPlanets.get(i).getTechnologyLevel()+maxPlanets.get(j).getTechnologyLevel())/2);
                weightedGraph.addEdge((new Edge(idDic.get(maxPlanets.get(i).getId()),idDic.get(maxPlanets.get(j).getId()),cost)));
            }
        }
        LazyPrimMST mst=new LazyPrimMST(weightedGraph);
        for(Edge e:mst.edges()){
            minimumCostCommunicationNetwork.add(new HyperChannel(intDic.get(e.either()),intDic.get(e.other(e.either())),e.weight()));
        }
        return minimumCostCommunicationNetwork;
    }

    public void printMinimumCostCommunicationNetwork(List<HyperChannel> network) {
        double sum = 0;
        for (HyperChannel channel : network) {
            Planet[] planets = {channel.getFrom(), channel.getTo()};
            Arrays.sort(planets);
            System.out.printf("Hyperchannel between %s - %s with cost %f", planets[0], planets[1], channel.getWeight());
            System.out.println();
            sum += channel.getWeight();
        }
        System.out.printf("The total cost of the subspace communication network is %f.", sum);
        System.out.println();
    }
}

import java.util.LinkedList;

public class EdgeWeightedGraph
{
    private final int V;
    private int E;
    private LinkedList<Edge>[] adj;
    public EdgeWeightedGraph(int V) {
        this.V = V;
        this.E = 0;
        adj = (LinkedList<Edge>[]) new LinkedList[V];
        for (int v = 0; v < V; v++)
            adj[v] = new LinkedList<Edge>();
    }


    public int V() { return V; }
    public int E() { return E; }
    public void addEdge(Edge e)
    {
        int v = e.either(), w = e.other(v);
        adj[v].add(e);
        adj[w].add(e);
        E++;
    }
    public Iterable<Edge> adj(int v)
    { return adj[v]; }

    public Iterable<Edge> edges() {
        LinkedList<Edge> b = new LinkedList<>();
        for (int v = 0; v < V; v++)
            for (Edge e : adj[v])
                if (e.other(v) > v) b.add(e);
        return b;
    }
}
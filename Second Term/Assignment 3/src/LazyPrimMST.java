import java.util.LinkedList;
import java.util.Queue;

public class LazyPrimMST
{
    private boolean[] marked;
    private Queue<Edge> mst;
    private MinPQ<Edge> pq;
    public LazyPrimMST(EdgeWeightedGraph G)
    {
        pq = new MinPQ<Edge>(G.E());
        marked = new boolean[G.V()];
        mst = new LinkedList<>();
        visit(G, 0);
        while (!pq.isEmpty())
        {
            Edge e = pq.delMin();
            int v = e.either(), w = e.other(v);
            if (marked[v] && marked[w]) continue;
            mst.add(e);
            if (!marked[v]) visit(G, v);
            if (!marked[w]) visit(G, w);
        }
    }
    private void visit(EdgeWeightedGraph G, int v)
    {
        marked[v] = true;
        for (Edge e : G.adj(v))
            if (!marked[e.other(v)]) pq.insert(e);
    }
    public Iterable<Edge> edges()
    { return mst; }

}
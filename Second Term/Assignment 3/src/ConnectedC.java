public class ConnectedC
{
    private boolean[] marked;
    private int[] id;
    private int count;
    public ConnectedC(Graph G)
    {
        marked = new boolean[G.getV()];
        id = new int[G.getV()];
        for (int s = 0; s < G.getV(); s++)
            if (!marked[s])
            {
                dfs(G, s);
                count++;
            }

    }
    private void dfs(Graph G, int v)
    {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w);
    }
    public int[] getId(){return id;}
    public boolean connected(int v, int w)
    { return id[v] == id[w]; }
    public int id(int v)
    { return id[v]; }
    public int count()
    { return count; }
}
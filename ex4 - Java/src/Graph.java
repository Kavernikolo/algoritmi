import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Graph<N, T>
{
    private Map<N, List<Edge<N, T>>> graph;
    private List<Edge<N, T>> edgeList;

    private final boolean direct;

    //Creazione di un grafo vuoto - O(1)
    public Graph(boolean direct)
    {
        this.graph = new HashMap<>();
        this.edgeList = new ArrayList<>();

        this.direct = direct;
    }

    //Aggiunta di un nodo - O(1)
    public void addNode(N node) throws GraphException
    {
        if(node == null){ throw new GraphException("Error: node cannot be NULL"); }

        graph.put(node, new ArrayList<>());
    }

    //Aggiunta di un arco - O(1)
    public void addEdge(N source, N destination, T label) throws GraphException
    {
        if(source == null || destination == null){ throw new GraphException("Error: source or destination cannot be NULL"); }

        if(!graph.containsKey(source)){ addNode(source); }
        if(!graph.containsKey(destination)){ addNode(destination); }

        //isDirect = TT
        Edge<N, T> edge = new Edge<N, T>(source, destination, label);
            graph.get(source).add(edge);
            this.edgeList.add(edge);
        
        //isDirect = FF
        if(!isDirect())
        {
            edge = new Edge<N, T>(source, destination, label);
                graph.get(destination).add(edge);
                this.edgeList.add(edge);
        }
    }

    public void addEdge(Edge<N, T> edge) throws GraphException
    {
        if(edge == null){ throw new GraphException("Error: edge cannot be NULL"); }
    
        N source = edge.getSource();
        N destination = edge.getDestination();

        if(!graph.containsKey(source)){ addNode(source); }
        if(!graph.containsKey(destination)){ addNode(destination); }
    
        graph.get(source).add(edge);
        edgeList.add(edge);
    
        if(!isDirect())
        {
            graph.get(destination).add(edge);
            edgeList.add(edge);
        }
    }

    //Verifica se un grafo è diretto - O(1)
    public boolean isDirect(){ return direct; }

    //Verifica se il grafo contiene un dato nodo – O(1)
    public boolean hasNode(N node) throws GraphException
    {
        if(node == null){ throw new GraphException("Error: node cannot be NULL"); }

        return graph.containsKey(node);
    }

    //Verifica se il grafo contiene un dato arco – O(1)
    public boolean hasEdge(N source, N destination) throws GraphException
    {
        if(source == null || destination == null){ throw new GraphException("Error: source or destination cannot be NULL"); }

        if(!graph.containsKey(source)){ return false; }

        List<Edge<N, T>> edgeList = graph.get(source);
        boolean found = false;

        for(int i = 0; i < edgeList.size() && !found; i++)
        {
            found = edgeList.get(i).getDestination().equals(destination);
        }
        return found;
    }

    //Cancellazione di un nodo – O(n)
    public void removeNode(N node) throws GraphException
    {
        if(node == null){ throw new GraphException("Error: node cannot be NULL"); }

        graph.remove(node);
    }

    //Cancellazione di un arco – O(1)
    public void removeEdge(N source, N destination) throws GraphException
    {
        if(source == null || destination == null){ throw new GraphException("Error: source or destination cannot be NULL"); }

        List<Edge<N, T>> edgeList = graph.get(source);
        boolean removed = false;

        if(!edgeList.isEmpty())
        {
            for(int i = 0; i < edgeList.size() && !removed; i++)
            {
                if(edgeList.get(i).getDestination().equals(destination)){ removed = true; }

                edgeList.remove(edgeList.get(i));
                edgeList.remove(i);
            }
        }

        //isDirect == FF
        if(removed && !isDirect())
        {
            removed = false;
            edgeList = graph.get(destination);

            if(!edgeList.isEmpty())
            {
                for(int i = 0; i < edgeList.size() && !removed; i++)
                {
                    if(edgeList.get(i).getDestination().equals(source)){ removed = true; }

                    edgeList.remove(edgeList.get(i));
                    edgeList.remove(i);
                }
            }
        }
    }

    //Determinazione del numero di nodi – O(1)
    public int countNode(){ return graph.size(); }

    //Determinazione del numero di archi – O(n)
    public int countEdge()
    {
        int count = edgeList.size();

        if(!isDirect()){ count /= 2; }

        return count;
    }

    //Recupero dei nodi del grafo – O(n)
    public Set<N> getNode(){ return graph.keySet(); }

    //Recupero degli archi del grafo – O(n)
    public List<Edge<N, T>> getEdge(){ return edgeList; }

    //Recupero nodi adiacenti di un dato nodo – O(1)
    public List<Edge<N, T>> getAdjNode(N node) throws GraphException
    {
        if(node == null){ throw new GraphException("Error: node cannot be NULL"); }

        return graph.get(node);
    }

    //Recupero etichetta associata a una coppia di nodi – O(1)
    public T getLabel(N source, N destination) throws GraphException
    {
        if(source == null || destination == null){ throw new GraphException("Error: source or destination cannot be NULL"); }

        if(!hasEdge(source, destination)){ return null; }

        List<Edge<N, T>> edgeList = graph.get(source);
        T label = null;

        for(Edge<N, T> edge : edgeList)
        {
            if(edge.getDestination().equals(destination)){ label = edge.getLabel(); }
        }
        return label;
    }
}
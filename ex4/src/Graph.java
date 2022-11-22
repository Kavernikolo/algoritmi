import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Graph<N, T>
{
    private Map<N, List<Edge<N, T>>> graph;
    private List<Edge<N, T>> edgeList;

    private final boolean isDirect;

    //Creazione di un grafo vuoto - O(1)
    public Graph(boolean isDirect)
    {
        this.graph = new HashMap<>();
        this.edgeList = new ArrayList<>();

        this.isDirect = isDirect;
    }

    //Aggiunta di un dono - O(1)
    public void addNode(N node)
    {
        if(node == null){ return; /* Creare Exception */ }

        graph.put(node, new ArrayList<>());
    }

    //Aggiunta di un arco - O(1)
    public void addEdge(N source, N destination, T label)
    {
        if(source == null || destination == null){ return; /* Creare Exception */ }

        if(!graph.containsKey(source)){ addNode(source); }
        if(!graph.containsKey(destination)){ addNode(destination); }

        Edge<N, T> edge = new Edge<N, T>(source, destination, label);
        graph.get(source).add(edge);
        this.edgeList.add(edge);

        if(!isDirect())
        {
            Edge<N, T> edge = new Edge<N, T>(source, destination, label);
            graph.get(destination).add(edge);
            this.edgeList.add(edge);
        }
    }

    public void addEdge(Edge<N, T> edge)
    {
        if(edge == null){ return; /* Creare Exception */ }

        N source = edge.getSource();
        N destination = edge.getDestination();

        if(!graph.containsKey(source)){ addNode(source); }
        if(!graph.containsKey(destination)){ addNode(destination); }

        graph.get(source).add(edge);
        this.edgeList.add(edge);

        if(!isDirect())
        {
            graph.get(destination).add(edge);
            edgeList.add(edge);
        }
    }

    //Verifica se un grafo è diretto - O(1)
    public boolean isDirect(){ return isDirect; }

    //Verifica se il grafo contiente un dato nodo - O(1)
    publci boolean hasNode(N node)
    {
        if(node == null){ return; /* Creare Exception */ }

        return graph.containsKey(node);
    }

    //Verifica se il grafo contiene un determinato arco - O(1)
    public boolean hasEdge(N source, N destination)
    {
        if(source == null || destination == null){ return; /* Creare Exception */ }

        if(!graph.containsKey(source)){ return false; }
        
        List<Edge<N, T>> edgeList = graph.get(source);

        boolean found = false;
        for(int i = 0; i < edgeList.size(); i++ )
        {
            found = edgeList.get(i).getDestination().equals(destination);
        }

        return found;
    }

    //Cancellazione di un nodo - O(1)
    public void removeNode(N node)
    {
        if(node == null){ return; /* Creare Exception */ }

        graph.remove(node);
    }

    //Cancellazione di un arco - O(1)
    public void removeEdge(N source, N destination)
    {
        if(source == null || destination == null){ return; /* Creare Exception */ }

        List<Edge<N, T>> edgelist = graph.get(source);
        
        boolean found = false;
        for(int i = 0; i < edgelist.size() && !found; i++)
        {
            if(edgelist.get(i).getDestination().equals(source)){ found = true; }

            edgeList.remove(edgelist.get(i));
            edgelist.remove(i);
        }

        if(found && !isDirect)
        {
            found = false;
            edgelist = graph.get(destination);

            if(!edgeList.isEmpty())
            {
                for(int i = 0; i < edgeList.size() && !found; i++)
                {
                    if(edgelist.get(i).getDestination().equals(destination)){ found = true; }

                    edgelist.remove(edgelist.get(i));
                    edgelist.remove(i);
                }
            }
        }
    }

    //Determinazione del numero dei nodi - O(1)
    public int countNode()
    {
        return graph.size();
    }

    //Determinazione del numero degli archi - O(1)
    public int countEdge()
    {
        int count = edgeList.size();

        if(!isDirect()){ count /= 2; }

        return count;
    }

    //Recupero dei nodi del grafo - O(n)
    public Set<N> getNode(){ return graph.keySet(); }

    //Recupero degli archi del grafo - O(n)
    public List<Edge<N, T>> getEdge(){ return edgeList; }

    //Recupero dei nodi adiacenti di un dato nodo - O(1)
    public List<Edge<N, T>> getAdiacentNodes(N node)
    {
        if(node == null){ return; /* Creare Exception */ }

        return graph.get(node);
    }

    //Recupero etichetta associata a una coppia di nodi – O(1)
    public T getLabel(N source, N destination)
    {
        if(source == null || destination == null){ return; /* Creare Exception */ }

        if(!hasEdge(source, destination)){ return null; }

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

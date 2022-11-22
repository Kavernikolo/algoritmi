public class Edge<N, T>
{
    private N source;
    private N destination;

    private final T label;

    public Edge(N source, N destination, T label)
    {
        this.source = source;
        this.destination = destination;

        this.label = label;
    }

    public N getSource(){ return this.source; }
    public N getDestination(){ return this.destination; }
    public T getLabel(){ return this.label; }

    public boolean isNULL(){ return(source == null || destination == null || label == null); }
}
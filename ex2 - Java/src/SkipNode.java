public class SkipNode<N extends Comparable<? super N>>
{
    static int LEVELS = 3;
    N data;

    SkipNode<N>[] next = new SkipNode[LEVELS];

    SkipNode(N data){ this.data = data; }

    SkipNode<N> getNext(int level){ return this.next[level]; }
    void setNext(SkipNode<N> next, int level){ this.next[level] = next; }

    void insert(SkipNode<N> node, int level)
    {
        SkipNode<N> current = this.getNext(level);

        if(current == null)
        {
            this.setNext(node, level);
            return;
        }

        if(node.data.compareTo(current.data) < 1)
        {
            this.setNext(node, level);
            node.setNext(current, level);

            return;
        }

        while(current.getNext(level) != null && current.getNext(level).data.compareTo(node.data) < 1 && current.data.compareTo(node.data) < 1)
        {
            current = current.getNext(level);
        }

        SkipNode<N> successor = current.getNext(level);
        current.setNext(node, level);
        node.setNext(successor, level);
    }

    SkipNode<N> search(N data, int level)
    {
        System.out.println("Searching for: "+data);

        SkipNode<N> result = null;

        SkipNode<N> current = this.getNext(level);
        while(current != null && current.data.compareTo(data) < 1)
        {
            if(current.data.equals(data))
            {  
                result = current;
                break;
            }
            current = current.getNext(level);
        }
        return result;
    }

    void print(int level) 
    {
        System.out.print("level " + level + ": [ ");
        
        int length = 0;
        
        SkipNode<N> current = this.getNext(level);
        while (current != null) 
        {
            length++;
            System.out.print(current.data + " ");
            current = current.getNext(level);
        }
    
        System.out.println("], length: " + length);
    }
}
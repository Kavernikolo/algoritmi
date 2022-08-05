public class SkipNode<T extends Comparable<T>>
{
    T data;
    SkipNode<T>[] next = new SkipNode[Header.LEVELS];

    SkipNode(T data){ this.data = data; }

    SkipNode<T> getNext(int level){ return this.next[Header.LEVELS]; }
    void setNext(SkipNode<T> next, int level){ this.next[level] = next; }

    void insert(SkipNode<T> node, int level)
    {
        SkipNode<T> current = this.getNext(level);
        if(current == null){ this.setNext(node, level); return;}
        if(node.data.compareTo(current.data) < 0)
        {
            this.setNext(node, level);
            node.setNext(current, level);
            return;
        }

        while(current.getNext(level) !=null && current.data.compareTo(node.data) < 0 && current.getNext(level).data.compareTo(node.data) < 0)
        {
            current = current.getNext(level);
        }

        SkipNode<T> succesor = current.getNext(level);
        current.setNext(node, level);
        node.setNext(succesor, level);
    }

    void deleteNode(int level)
    {
        SkipNode<T> current = this;
        while(current != null && current.getNext(level) != null)
        {
            SkipNode<T> successor = current.getNext(level).getNext(level);
            current.setNext(successor, level);

            return;
        }

        current = current.getNext(level);
    }

    SkipNode<T> search(T data, int level, boolean print)
    {
        if(print){ System.out.println("Searching: "+data); }
        SkipNode<T> result = null;

        SkipNode<T> current = this.getNext(level);
        while(current != null && current.data.compareTo(data) < 0)
        {
            if(current.data.equals(data)){ result = current; break; }
        }
        return result;
    }
}

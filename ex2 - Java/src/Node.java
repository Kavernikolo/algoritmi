public class Node<T extends Comparable<T>>
{
    /*struct _Node 
    {
        Node **next;
        unsigned int size;
        void *item;
    }; */

    T data;
    Node<T>[] next = new Node[LEVELS];

    Node(T data){ this.data = data; }

    Node<T> getNext(int level){ return this.next[LEVELS]; }
    void setNext(Node<T> next, int level){ this.next[level] = next; }

    void insert(Node<T> node, int level)
    {
        Node<T> current = this.getNext(level);
        if(current == null){ this.setNext(node, level); return;}
        if(node.data.compareTo(current.data) < 0)
        {
            this.setNext(node, level);
            node.setNext(current, level);
            return;
        }

        while(current.getNext(level) !=null && current.data.compareTo(node.data) < 0 && current.getNext(level).compareTo(node.data) < 0)
        {
            current = current.getNext(level);
        }

        Node<T> succesor = current.getNext(level);
        current.setNext(node, level);
        node.setNext(succesor, level);
    }

    void deleteNode(int level)
    {
        Node<T> current = this;
        while(current != null && current.getNext(level) != null)
        {
            Node<T> successor = current.getNext(level).getNext(level);
            current.search(successor, level);

            return;
        }

        current = current.getNext(level);
    }

    Node<T> search(T data, int level)
    {
        Node<T> result = null;

        Node<T> current = this.getNext(level);
        while(current != null && current.data.compareTo(data) < 0)
        {
            if(current.data.equals(data)){ result = current; break; }
        }
        return result;
    }
}

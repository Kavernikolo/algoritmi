import java.util.NoSuchElementException;

public class Node<K extends Comparable<K>, V>
{
    private Node<K, V> up;
    private Node<K, V> down;
    private Node<K, V> next;
    private Node<K, V> previous;

    private int level;
    private K key;
    private V value;

    public Node(int level, K key, V value)
    {
        this.level = level;
        this.key = key;
        this.value = value;
    }

    public int getLevel(){ return level; }
    public K getK(){ return this.key; }
    public V getValue(){ return this.value; }

    public Node<K, V> getUp(){ return this.up; }
    public Node<K, V> getDown(){ return this.down; }
    public Node<K, V> getNext(){ return this.next; }
    public Node<K, V> getPrevious(){ return this.previous; }

    public void setUp(Node up){ this.up = up; }
    public void setDown(Node down){ this.down = down; }
    public void setNext(Node next){ this.next = next;}
    public void setPrevious(Node previous){this.previous = previous; }

    public void insert(int level, K key, V value, Node<K, V> parent)
    {
        if(this.level <= level && (next == null || next.getK().compareTo(key) > 0))
        {
            Node<K, V> newNode = new Node<K, V>(this.level, key, value);

            if(next != null)
            {
                next.setPrevious(newNode);
                newNode.setNext(next);
            }

            next = newNode;
            newNode.setPrevious(this);

            if(parent != null)
            {
                newNode.setUp(parent);
                parent.setDown(newNode);
            }

            if(down != null){ down.insert(level, key, value, newNode); }
        }
        else if(next != null && next.getK().compareTo(key) < 0){ next.insert(level, key, value, parent); }
        else if(next != null && next.getK().compareTo(key) == 0){ throw new IllegalArgumentException("Duplicate key is not allowed!"); }
        else if(down != null){ down.insert(level, key, value, parent); }
    }

    public Node<K, V> find(K key)
    {
        if(next != null)
        {
            int result = next.getK().compareTo(key);

            if(result == 0){ return next; }
            else if( result < 0){ return next.find(key); }
            else if(down != null){ return down.find(key); }
            else{ throw new NoSuchElementException(); }
        }
        else if(down != null){ return down.find(key); }
        else{ throw new NoSuchElementException(); }
    }
}

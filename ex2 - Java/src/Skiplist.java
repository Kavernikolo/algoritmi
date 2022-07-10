import java.util.Random;

public class Skiplist<K extends Comparable<K>, V>
{
    final static Random random = new Random();

    private Node<K, V> head = new Node<K, V>(0, null, null);

    public void insert(K key, V value)
    {
        int level = 0;

        while(random.nextInt() < 0.5){ level += 1;}

        while(head.getLevel() < level)
        {
            Node<K, V> newHead = new Node<K, V>(head.getLevel() + 1, null, null);

            head.setUp(newHead);
            newHead.setDown(head);

            head = newHead;
        }

        head.insert(level, key, value, null);
    }

    public V find(K key){ return head.find(key).getValue(); }

    public void delete(K key)
    {
        for(Node<K, V> node = head.find(key); node != null; node = node.getDown())
        {
            node.getPrevious().setNext(node.getNext());

            if(node.getNext() != null){ node.getPrevious().setNext(node.getPrevious()); }
        }

        while(head.getNext() == null)
        {
            head = head.getDown();
            head.setUp(null);
        }
    }
}
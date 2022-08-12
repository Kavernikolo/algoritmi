package skipList;

public class SkipList<V extends Comparable<V>>
{
    private static final int MAX_HEIGHT = 1;
    private SkipNode<V> head = new SkipNode<>(null, 0);

    private int randomLevel()
    {
        int upperBound = 1;

        while(Math.random() < 0.5 && upperBound <= MAX_HEIGHT){ upperBound += 1; }

        return upperBound;

    }

    public void insert(V value)
    {
        int level = randomLevel();
        while(head.getLevel() <= level)
        {
            SkipNode<V> newHead = new SkipNode<V>(value, head.getLevel() + 1);

            head.setUp(newHead);
            newHead.setDown(head);

            head = newHead;
        }
        head.insertNode(value, level, null);
    }
    
    public V find(V value)
    {
        return head.find(value).getValue();
    }
}

package skipList;

import java.util.NoSuchElementException;

public class SkipNode<V extends Comparable<V>>
{
    private SkipNode<V> up;
    private SkipNode<V> down;
    private SkipNode<V> next;
    private SkipNode<V> previous;

    private V value;
    private int level;

    SkipNode(V value, int level)
    { 
        this.value = value; 
        this.level = level; 
    }

    public SkipNode<V> getUp(){ return up; }
    public void setUp(SkipNode<V> node){ up = node; }

    public SkipNode<V> getDown(){ return down; }
    public void setDown(SkipNode<V> node){ down = node; }

    public SkipNode<V> getNext(){ return next; }
    public void setNext(SkipNode<V> node){ next = node; }

    public SkipNode<V> getPrevious(){ return previous; }
    public void setPrevious(SkipNode<V> node){ previous = node; }

    public V getValue(){ return value; }
    public int getLevel(){ return level; }

    public void insertNode(V value, int level, SkipNode<V> parent)
    {
        if(this.level <= level && (next == null || next.getValue().compareTo(value) > 0))
        {
            SkipNode<V> newNode = new SkipNode<>(value, this.level);

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

            if(down != null){ down.insertNode(value, level, newNode); }
        }
        //else if(next != null && next.getValue().compareTo(value) == 0){ throw new IllegalArgumentException("Duplicate not allowed!"); }
        else if(next != null && next.getValue().compareTo(value) < 0){ next.insertNode(value, level, parent);}
        else if(down != null){ down.insertNode(value, level, parent); }
    }
    
    public SkipNode<V> find(V value)
    {
        if(next != null)
        {
            int compare = next.getValue().compareTo(value);

            if(compare == 0){ return next; }
            else if(compare < 0){ return next.find(value); }
            else if(down != null){ return down.find(value); }
            else{ throw new NoSuchElementException(); }
        }
        else if(down != null){ return down.find(value); }
        else{ throw new NoSuchElementException(); }
    }
}
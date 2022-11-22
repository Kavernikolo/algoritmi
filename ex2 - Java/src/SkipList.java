import java.util.Comparator;
import java.util.ArrayList;

public class SkipList<T extends Comparable<T>>
{
    private static int MAX_HEIGHT = 2;

    private SkipNode<T> head;
    private SkipNode<T> tail;

    private int max_levels;

    SkipList()
    {
        SkipNode<T> negNode = new SkipNode<T>(null);
        SkipNode<T> posNode = new SkipNode<T>(null);

        negNode.setNext(posNode);
        posNode.setPrev(negNode);

        head = negNode;
        tail = posNode;

        max_levels = 1;
    }

    public SkipNode<T> find(T data)
    {
        SkipNode<T> currentPos = head;

        while(true)
        {
            while(!(currentPos.getNext().getData().equals("null")) && currentPos.getNext().getData().compareTo(data) <= 0)
            {
                currentPos = currentPos.getNext();
            }

            if(currentPos.getDown() != null){ currentPos = currentPos.getDown(); }
            else break;
        }

        return currentPos;
    }

    public void insert(T data)
    {
        if(data == null){ throw new IllegalArgumentException("Data cannot be NULL"); }

        SkipNode<T> currentPos = find(data);

        if(!(currentPos.getData().equals("null")) && (currentPos.getData().compareTo(data) == 0)){ return; }

        SkipNode<T> toInsert = new SkipNode<T>(data);

        toInsert.setNext(currentPos.getNext());
        toInsert.setPrev(currentPos);
        currentPos.getNext().setPrev(toInsert);
        currentPos.setNext(toInsert);

        int levels = 1; //random level da fare
        //if(levels > max_levels){ max_levels = levels; }

        if(levels > 0){ buildLevels(toInsert, currentPos, levels); }
        
        return;
    }

    public void buildLevels(SkipNode<T> currentPos, SkipNode<T> previousPos, int levels)
    {
        while(levels > max_levels){ buildEmptyLevels(); }

        for(int i = 0; i < levels; i++)
        {
            while(previousPos.getUp() == null){ previousPos = previousPos.getPrev(); }
            previousPos = previousPos.getUp();

            SkipNode<T> levelNode = new SkipNode<T>(currentPos.getData());

            levelNode.setPrev(previousPos);
            previousPos.setNext(levelNode);
            levelNode.setNext(previousPos.getNext());
            previousPos.getNext().setPrev(levelNode);

            levelNode.setDown(currentPos);
            currentPos.setUp(levelNode);

            currentPos = levelNode;
        }
    }

    public void buildEmptyLevels()
    {
        SkipNode<T> tmpHeadNode = new SkipNode<T>(null);
        SkipNode<T> tmpTailNode = new SkipNode<T>(null);

        tmpHeadNode.setNext(tmpTailNode);
        tmpTailNode.setPrev(tmpHeadNode);

        tmpHeadNode.setDown(head);
        tmpTailNode.setDown(tail);

        head.setUp(tmpHeadNode);
        tail.setUp(tmpTailNode);

        head = tmpHeadNode;
        tail = tmpTailNode;

        max_levels++;
    }
}

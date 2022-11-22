import java.util.Comparator;
import java.util.ArrayList;

public class SkipNode<T> 
{
    private SkipNode<T> up = null;
    private SkipNode<T> down = null;
    private SkipNode<T> right = null;
    private SkipNode<T> left = null;

    private int size;
    private T data;

    SkipNode(T data)
    { 
        this.data = data; 
    }

    public SkipNode<T> getUp(){ return up; }
    public SkipNode<T> getDown(){ return down; }
    public SkipNode<T> getNext(){ return right; }
    public SkipNode<T> getPrev(){ return left; }

    public int getSize(){ return size; }
    public T getData(){ return data; }

    public void setUp(SkipNode<T> up){ this.up = up; }
    public void setDown(SkipNode<T> down){ this.down = down; }
    public void setNext(SkipNode<T> right){ this.right = right; }
    public void setPrev(SkipNode<T> left){ this.left = left; }

    public void setSize(int size){ this.size = size; }
    public void setData(T data){ this.data = data; }
}

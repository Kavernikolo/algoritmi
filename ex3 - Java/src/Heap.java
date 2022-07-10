import java.util.ArrayList;

public class Heap<T extends Comparable<T>>
{
    private static final int ROOT = 0;

    private ArrayList<T> array;

    public Heap(int maxsize)
    {
        array = new ArrayList<>(maxsize);
    }

    public void heap()
    {
        for (int index = (array.size() / 2) - 1; index >= 1; index--){ heapify(index); }
        print();
    }

    //inserimento di un elemento - O(log n)
    public void Insert(T element)
    {
        array.add(element);

        int index = array.size() - 1;

        while(index > 0 && array.get(index).compareTo(array.get(getParentIndex(index))) < 0)
        {
            swap(array, index, getParentIndex(index));

            index = getParentIndex(index);
        }
    }

    //restituzione della dimensione dello heap - O(1)
    public int getSize(){ return array.size(); }

    //restituzione del genitore di un elemento - O(1)
    public int getParentIndex(int i){ return (i / 2); }

    public T getParentElement(int i){ return array.get(getParentIndex(i)); }

    //restituzione del figlio sinistro di un elemento - O(1)
    public int getLeftIndex(int i){ return (2 * i); }
    public T getLeftElement(int i){ return array.get(getLeftIndex(i)); }

    //restituzione del figlio destro di un elemento - O(1)
    public int getRightIndex(int i){ return ((2* i) + 1); }
    public T getRightElement(int i){ return array.get(getRightIndex(i)); }

    //estrazione dell'elemento con valore minimo - O(log n)
    public T extractElement()
    {
        T root = array.remove(ROOT);
        T first = array.remove(array.size() - 1);

        array.add(ROOT, first);
        
        heapify(array.size());

        return root;
    }

    private boolean isLeaf(int index)
    {
        if (index >=  (array.size() / 2)  &&  index <= array.size()){ return true; }
        
        return false;
    }

    public void heapify(int index)
    {
        if(!isLeaf(index))
        { 
            if(array.get(index).compareTo(array.get(getLeftIndex(index))) > 0 || array.get(index).compareTo(array.get(getRightIndex(index))) > 0)
            {
                if(array.get(getLeftIndex(index)).compareTo(array.get(getRightIndex(index))) > 0)
                {
                    swap(array, index, getLeftIndex(index));
                    heapify(getLeftIndex(index));
                }
                else
                {
                    swap(array, index, getRightIndex(index));
                    heapify(getRightIndex(index));
                }
            }
        }
    }
    public void print()
    {
        for (int i = 0; i < (this.array.size()-1) / 2; i++)
        {         
                System.out.println("NODE : " + array.get(i) + " LEFT CHILD : " + array.get(getLeftIndex(i)) + " RIGHT CHILD :" + array.get(getRightIndex(i)));
        } 
    }

    private static <T> void swap(final ArrayList<T> array, final int x, final int y)
    {
        T tmp = array.get(x);
        array.set(x, array.get(y));
        array.set(y, tmp);
    }

    public static void main(String...arg)
    {
        System.out.println("The Min Heap is ");
        Heap<Integer> minHeap = new Heap<Integer>(15);
        minHeap.Insert(5);
        minHeap.Insert(3);
        minHeap.Insert(17);
        minHeap.Insert(10);
        minHeap.Insert(84);
        minHeap.Insert(19);
        minHeap.Insert(6);
        minHeap.Insert(22);
        minHeap.Insert(9);
        minHeap.Insert(1);
        minHeap.heap();
        minHeap.print();
        System.out.println("The Min val is " + minHeap.extractElement());
    }
}
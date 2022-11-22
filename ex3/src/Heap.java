import java.util.ArrayList;

public class Heap<T extends Comparable<T>>
{
    private static final int ROOT = 1;

    private ArrayList<T> array;

    //Creazione di uno heap minimo vuoto - O(1)
    public Heap()
    { 
        array = new ArrayList<>(); 
    
        array.add(null); 
    }

    //Inserimento di un elemento - O(log n)
    public void insert(T data)
    {
        array.add(data);

        bubbleUp();
    }

    public void bubbleUp()
    {
        int index = array.size() - 1;

        while(index > 1 && (getParentElement(index).compareTo(array.get(index)) > 0))
        {
            swap(array, index, getParentIndex(index));
            index = getParentIndex(index);
        }
    }

    private static <T> void swap(ArrayList<T> array, int x, int y)
    {
        T tmp = array.get(x);
        array.set(x, array.get(y));
        array.set(y, tmp);
    }

    //Restituzione della dimensione dello heap - O(1)
    public int getSize(){ return array.size(); }

    //Restituzione del genitore di un elemento - O(1)
    public int getParentIndex(int i){ return (i / 2); }
    public T getParentElement(int i){ return array.get(getParentIndex(i)); }

    //restituzione del figlio sinistro di un elemento - O(1)
    public int getLeftIndex(int i){ return ((2 * i)); }
    public T getLeftElement(int i){ return array.get(getLeftIndex(i)); }

    //Restituzione del figlio destro di un elemento - O(1)
    public int getRightIndex(int i){ return ((2 * i) + 1); }
    public T getRightElement(int i){ return array.get(getRightIndex(i)); }

    //Estrazione dell' elemento con valore minimo - O(log n)
    public T extractData()
    {
        T root = array.remove(ROOT);
        T first = array.remove(array.size() - 1);

        array.add(ROOT, first);

        bubbleDown();

        return root;
    }

    public void bubbleDown()
    {
        int index = ROOT;

        int leftIndex;
        int rightIndex;

        int minIndex;

        while(true)
        {
            leftIndex = getLeftIndex(index);
            rightIndex = getRightIndex(index);

            minIndex = index;

            if(array.size() > leftIndex && (array.get(index).compareTo(array.get(leftIndex)) > 0))
            {
                minIndex = leftIndex;
            }

            if(array.size() > rightIndex && (array.get(index).compareTo(array.get(rightIndex)) > 0))
            {
                minIndex = rightIndex;
            }

            if(index != minIndex){ swap(array, index, minIndex); }
            else{ return; }
        }
    }

    //Diminuzione del valore di un elemento - O(log n)
    public void decreaseElement(int index, T data)
    {
        if(index > array.size()){ throw new ArrayIndexOutOfBoundsException("Index out of bound!"); }
        
        if(index == ROOT){ array.add(ROOT, data); bubbleDown(); }
        else
        {  
            T tmp = data;
            array.set(index, tmp);

            bubbleUp();
        }
    }
}

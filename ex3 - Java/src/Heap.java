import java.util.ArrayList;

public class Heap<T extends Comparable<T>>
{
    private static final int ROOT = 1;

    private ArrayList<T> array;

    //Creazione di uno heap minimo vuoto - O(1)
    public Heap(){ array = new ArrayList<>(); array.add(null); }

    public void buildMinHeap()
    {
        //for(int i = (array.size() / 2); i >= 0; i--){ heapify(array.size()); }
        print();
    }

    //inserimento di un elemento - O(log n)
    public void insert(T element)
    {
        array.add(element);
        
        bubbleUp();
    }

    private void bubbleUp()
    {
		int index = array.size() -1;
        
        while (hasParent(index)
                && (getParentElement(index).compareTo(array.get(index)) > 0)) {
            // parent/child are out of order; swap them
            swap(array, index, getParentIndex(index));
            index = getParentIndex(index);
        } 
	}

    //restituzione della dimensione dello heap - O(1)
    public int getSize(){ return array.size(); }

    //restituzione del genitore di un elemento - O(1)
    public int getParentIndex(int i){ return (i / 2); }
    public T getParentElement(int i){ return array.get(getParentIndex(i)); }
    public boolean hasParent(int i){ return i > 1; }

    //restituzione del figlio sinistro di un elemento - O(1)
    public int getLeftIndex(int i){ return (2 * i); }
    public T getLeftElement(int i){ return array.get(getLeftIndex(i)); }
    public boolean hasLeftChild(int i){ return getLeftIndex(i) < array.size() - 1;}

    //restituzione del figlio destro di un elemento - O(1)
    public int getRightIndex(int i){ return (2 * i) + 1; }
    public T getRightElement(int i){ return array.get(getRightIndex(i)); }
    public boolean hasRightChild(int i){ return getLeftIndex(i) <= array.size() - 1; }

    //estrazione dell'elemento con valore minimo - O(log n)
    public T extractElement()
    {
        T root = array.remove(ROOT);
        T first = array.remove(array.size() - 1);
        
        array.add(ROOT, first);
        
        bubbleDown();
        
        return root;
    }

    private static <T> void swap(final ArrayList<T> array, final int x, final int y)
    {
        T tmp = array.get(x);
        array.set(x, array.get(y));
        array.set(y, tmp);
    }

    public void print()
    {
        System.out.println("Array size: " + array.size()+"\n");

        for (int i = 0; i < (array.size()); i++)
        {         
            System.out.println("Array is: " + array.get(i));
        } 
    }

    private void bubbleDown()
    {
        int index = ROOT;

        int leftChild, rightChild, minIndex;
		T tmp;

		while(true){
			leftChild = getLeftIndex(index);
			rightChild = getRightIndex(index);
			minIndex = index;
			if(array.size() > leftChild && array.get(minIndex).compareTo(array.get(leftChild)) > 0)
				minIndex = leftChild;
			if(array.size() > rightChild && array.get(minIndex).compareTo(array.get(rightChild)) > 0)
				minIndex = rightChild;

			if (index != minIndex){
				tmp  = array.get(index);
				array.set(index, array.get(minIndex));
				array.set(minIndex, tmp);
				index = minIndex;
			}
			else 
				return;			 
		}
    }
    public static void main(String[] args)
    {
        System.out.println("The Min Heap is ");
        Heap<Integer> minHeap = new Heap<Integer>();

        minHeap.insert(5);
        minHeap.insert(2);
        minHeap.insert(10);
        minHeap.insert(7);
        minHeap.insert(12);
        minHeap.insert(11);
        minHeap.insert(8);
        minHeap.insert(13);
        minHeap.insert(3);
        minHeap.insert(4);
        minHeap.insert(9);
        minHeap.insert(6);
        minHeap.insert(1);
        
        minHeap.buildMinHeap();

        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();

        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        System.out.println("Remove " + minHeap.extractElement()+"\n");
        minHeap.buildMinHeap();
        
        

        /*minHeap.decreaseElement(1, 55);
        
        System.out.println("Remove " + minHeap.extractElement());*/

    }
}
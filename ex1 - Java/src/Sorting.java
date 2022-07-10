import java.util.ArrayList;
import java.util.Comparator;

public class Sorting
{
    public static <T> void QuickBinaryInsertionSort(ArrayList<T> array, Comparator<T> comparator, int K_FIELD)
    {
        if(array.size() <= K_FIELD)
        {
            System.out.println("Size: " +array.size()+ " < K_FIELD: "+K_FIELD);
            System.out.println("HybridSort: Using Insertion Sort"); 
            
            //InsertionSort(array, 0, array.size() - 1, comparator); 
        }
        else
        {
            System.out.println("HybridSort: Using Quick Sort");
            QuickSort(array, 0, array.size() - 1, comparator, K_FIELD);
        }
    }

    public static <T> void InsertionSort(ArrayList<T> array, int init, int end, Comparator<T> comparator)
    {
        int i = init + 1;
        while(i <= end)
        {
            int j = i - 1;
            T tmp = array.get(i);

            int index = BinarySearch(array, 0, j, tmp, comparator);
            while(j >= index)
            {
                array.set(j + 1, array.get(j));
                j--;
            }
            array.set(index, tmp);
            i++;
        }
    }

    private static <T> int BinarySearch(ArrayList<T> array, int init, int end, T element, Comparator<T> comparator)
    {
        if(init <= end)
        {
            int middle = init + (end - init) / 2;

            if(comparator.compare(array.get(middle), element) == 0){ return middle + 1; }
            else if(comparator.compare(array.get(middle), element) < 0){ return BinarySearch(array, middle + 1, end, element, comparator); }
            else{ return BinarySearch(array, init, middle - 1, element, comparator); }
        }
        else{ return init; }
    }

    public static <T> void QuickSort(ArrayList<T> array, int init, int end, Comparator<T> comparator, int K_FIELD)
    {
        if(end <= K_FIELD)
        { 
            //System.out.println("End: " +end+ " < K_FIELD: "+K_FIELD);
            //System.out.println("QuickSort: Using Insertion Sort"); 
            //InsertionSort(array, init, end, comparator); 
        }
        if(init >= end){ return; }

        int p = Partition(array, init, end, comparator, K_FIELD);
        QuickSort(array, init, p, comparator, K_FIELD);
        QuickSort(array, p + 1, end, comparator, K_FIELD);
    }

    private static <T> int Partition(ArrayList<T> array, int init, int end, Comparator<T> comparator, int K_FIELD)
    {
        int middle = init + (end - init) / 2;

        T pivot = array.get(middle);

        int i = init - 1;
        int j = end + 1;

        while (i < j) 
        {
            i++; while(comparator.compare(array.get(i), pivot) < 0 ){ i++; }
            j--; while(comparator.compare(array.get(j), pivot) > 0){ j--; }
            
            if(i < j){ swap(array, i, j); }
        }
        return j;
    }

    private static <T> void swap(final ArrayList<T> array, final int x, final int y)
    {
        T tmp = array.get(x);
        array.set(x, array.get(y));
        array.set(y, tmp);
    }
}

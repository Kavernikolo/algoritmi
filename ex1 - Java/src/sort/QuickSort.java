package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class QuickSort
{
    private static int K_LIMIT = 32;

    public static <T> void quickSort(ArrayList<T> array, int init, int end, Comparator<T> comparator) throws SorterException
    {
        if((end - init) + 1 <= K_LIMIT){ InsertionSort.insertionSort(array, init, end, comparator); }

        if(init < end)
        {
            int p = partition(array, init, end, comparator);

            quickSort(array, init, p, comparator);
            quickSort(array, p + 1, end, comparator);
        }
    }
    
    public static <T> int partition(ArrayList<T> array, int init, int end, Comparator<T> comparator)
    {
        int pivot = (init / 2) + (end /2);

        T value = array.get(pivot);

        while(init < end)
        {
            while(comparator.compare(array.get(init), value) < 0){ init++; };
            while(comparator.compare(array.get(end), value) > 0){ end--; };

            swap(array, init, end);
        }
        return init;
    }

    public static <T> void swap(ArrayList<T> array, int i, int j)
    {
        T tmp = array.get(i);
        array.set(i, array.get(j));
        array.set(j, tmp);
    }    
}

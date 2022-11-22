package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class QuickSort
{
    private static int K_LIMIT = 0;

    public static <T> void quickSort(ArrayList<T> array, int init, int end, Comparator<T> comparator)
    {
        if((end - init) <= K_LIMIT){ InsertionSort.insertionSort(array, init, end, comparator); }

        if(end < init)
        {
            int p = partition(array, init, end, comparator);

            quickSort(array, init, p, comparator);
            quickSort(array, p + 1, end, comparator);
        }
    }
    
    private static <T> int partition(ArrayList<T> array, int init, int end, Comparator<T> comparator)
    {
        int pivot = (init + (end - init) / 2);

        T value = array.get(pivot);

        init--;
        end++;

        while(true)
        {
            do init++; while(comparator.compare(array.get(init), value) < 0);
            do end--; while(comparator.compare(array.get(end), value) > 0);

            if(init >= end){ return end; }
            swap(array, init, end);
        }
    }

    private static <T> void swap(ArrayList<T> array, int i, int j)
    {
        T tmp = array.get(i);
        array.set(i, array.get(j));
        array.set(j, tmp);
    }
}

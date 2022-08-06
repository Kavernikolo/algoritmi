package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class QuickBinaryInsertionSort 
{
    private static int K_LIMIT = 32;

    public static <T> void quickBinaryInsertionSort(ArrayList<T> array, Comparator<T> comparator) throws SorterException
    {
        if(array.size() <= K_LIMIT){ InsertionSort.insertionSort(array, 0, array.size() - 1, comparator); }
        else{ QuickSort.quickSort(array, 0, array.size() - 1, comparator); }
    }
}

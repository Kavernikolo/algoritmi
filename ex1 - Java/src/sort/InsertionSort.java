package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class InsertionSort 
{
    public static <T> void insertionSort(ArrayList<T> array, int init, int end, Comparator<T> comparator)
    {
        for(int i = init + 1; i <= end; i++)
        {
            int j = i - 1;

            T tmp = array.get(i);
            
            int toInsert = BinarySearch.binarySearch(array, init, j, tmp, comparator);

            while(j >= toInsert && (comparator.compare(array.get(j), tmp) > 0))
            {
                array.set(j + 1, array.get(j));
                j--;
            }
            array.set(j + 1, tmp);
        }
    }
}

package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class InsertionSort 
{
    public static <T> void insertionSort(ArrayList<T> array, int init, int end, Comparator<T> comparator) throws SorterException
    {
        for(int i = init + 1; i < end; i++)
        {
            int j = i - 1;
            T value = array.get(i);
            
            int gps = BinarySearch.binarySearch(array, value, init, j, comparator);            
            while(j >= gps && ((comparator.compare(array.get(j), value)) > 0))
            {
                array.set(j + 1, array.get(j));
                j--;
            }
            
            array.set((j + 1), value);
        }
    }

    public static <T> void swap(ArrayList<T> array, int i, int j)
    {
        T tmp = array.get(i);
        array.set(i, array.get(j));
        array.set(j, tmp);
    }
}

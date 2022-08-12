package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class BinarySearch 
{
    public static <T> int binarySearch(ArrayList<T> array, T value, int init, int end, Comparator<T> comparator)
    {
        if(end <= init)
        {
            if(comparator.compare(value, array.get(init)) < 0){ return init; }
            else{ return init + 1;}
        }

        int middle = (init + ((end - init) / 2));

        int compare = comparator.compare(value, array.get(middle));

        if(compare < 0){ return binarySearch(array, value, init, middle - 1, comparator); }
        else if(compare > 0){ return binarySearch(array, value,middle + 1, end, comparator); }
        else return middle;
    }   
}
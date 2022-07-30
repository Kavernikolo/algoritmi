package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class BinarySearch 
{
    public static <T> int binarySearch(ArrayList<T> array, T value, int init, int end, Comparator<T> comparator)
    {
        if(end <= init)
        {
            if(comparator.compare(array.get(init), value) < 0){ return init; }
            else{ return init + 1;}
        }

        //int middle = (init / 2) + (end /2);
        int middle = (init + ((end - init) / 2));

        int compare = comparator.compare(array.get(middle), value); 

        if(compare < 0){ return binarySearch(array, value, init, middle - 1, comparator); }
        else if(compare > 0){ return binarySearch(array, value, middle + 1, end, comparator); }
        else return middle;
    }   
}
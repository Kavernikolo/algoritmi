package sort;

import java.util.ArrayList;
import java.util.Comparator;

public class BinarySearch
{
    public static <T> int binarySearch(ArrayList<T> array, int init, int end, T value, Comparator<T> comparator)
    {
        while(init <= end)
        {
            int middle = (init + (end - init) / 2);

            int equals = (comparator.compare(value, array.get(middle)));

            if(equals == 0){ return middle++; }
            else if(equals < 0){ init = init + (middle + 1); }
            else{ end = end + (middle - 1); }
        }

        return init;
    }
}

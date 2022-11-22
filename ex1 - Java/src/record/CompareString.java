package record;

import java.util.Comparator;

public class CompareString implements Comparator<Record>
{
    @Override
    public int compare(Record element_1, Record element_2)
    {
        int result = (String.CASE_INSENSITIVE_ORDER).compare(element_1.getField_1(), element_2.getField_1());
            if(result != 0){ return result; }
        
        result = (Integer.valueOf(element_1.getField_2()). compareTo(Integer.valueOf(element_2.getField_2())));
            if(result != 0){ return result; }
        
        return(Float.valueOf(element_1.getField_3()).compareTo(Float.valueOf(element_2.getField_3())));
    }
}

package record;

import java.util.Comparator;

public class CompareINT implements Comparator<Record> 
{
    @Override
    public int compare(Record element_1, Record element_2)
    {
        int result = (Integer.valueOf(element_1.getField_2()).compareTo(Integer.valueOf(element_2.getField_2())));
            if(result != 0){ return result; }
        
        result = (Float.valueOf(element_1.getField_3()).compareTo(Float.valueOf(element_2.getField_3())));
            if(result != 0){ return result; }
        
        return(String.CASE_INSENSITIVE_ORDER).compare(element_1.getField_1(), element_2.getField_1());
    }    
}

import static org.junit.Assert.assertTrue;
import org.junit.Test;

public class Tests 
{
    public Tests() {}
    
    @Test
    public void testInsert() 
    {
        System.out.println("insert");
        Integer element = Integer.valueOf(5); //new Integer(5);
        Heap<Integer> instance = new Heap<Integer>(1);
        instance.Insert(element);
        assertTrue(instance.getSize() == 1);
        
    }
    
    @Test
    public void testMinHeap() {
        System.out.println("minHeap");
        Integer element1 = Integer.valueOf(2); //new Integer(2);
        Integer element2 = Integer.valueOf(8); //new Integer(8);
        Integer element3 = Integer.valueOf(3); //new Integer(3);
        Integer element4 = Integer.valueOf(4); //new Integer(4);
        Integer element5 = Integer.valueOf(5); //new Integer(5);
        Heap<Integer> instance = new Heap<Integer>(5);
        instance.Insert(element1);
        instance.Insert(element2);
        instance.Insert(element3);
        instance.Insert(element4);
        instance.Insert(element5);
        instance.heap();
        assertTrue(instance.extractElement() == 2);
    }
    
    @Test
    public void testRemove() {
        System.out.println("remove");
        Integer element = Integer.valueOf(5); //new Integer(5);
        Integer element2 = Integer.valueOf(6); //new Integer(6);
        Heap<Integer> instance = new Heap<Integer>(1);
        instance.Insert(element);
        instance.Insert(element2);
        assertTrue(instance.getSize() == 2); 
        instance.extractElement();
        assertTrue(instance.getSize() == 1); 
    }
}

import java.util.ArrayList;
import java.util.Comparator;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertTrue;


import org.junit.Test;

public class Tests 
{	
	private Integer i1 = 0;
	private Integer i2 = 1;
	private Integer i3 = 2;

	private ArrayList<Integer> array = new ArrayList<>();

	class IntegerComparator implements Comparator<Integer>
	{
        @Override
        public int compare(Integer i1, Integer i2){ return i1.compareTo(i2); } 
    } 

	/**
	*	TEST ON INSERTION SORT
	**/
	
	@Test
	public void testInsertionSortEmptyArray ()
	{
		sort.InsertionSort.insertionSort(array, 0, array.size() - 1, new IntegerComparator());
		
		assertTrue(array.isEmpty());
	}

	@Test
	public void testInsertionSortAllIdenticalEl()
	{
		array.add(i1);
		array.add(i1);
		array.add(i1);
		
		Integer[] expected = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ expected[i] = array.get(i); }
		
		sort.InsertionSort.insertionSort(array, 0, array.size() - 1, new IntegerComparator());
		
		Integer[] actual = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ actual[i] = array.get(i); }
		
		assertArrayEquals(expected, actual);
	}

	@Test
	public void testInsertionSort()
	{
		array.add(i1);
		array.add(i2);
		array.add(i3);
		
		Integer[] expected = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ expected[i] = array.get(i);   }
		
		sort.InsertionSort.insertionSort(array, 0, array.size() - 1, new IntegerComparator());
		
		Integer[] actual = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ actual[i] = array.get(i);  System.out.println("Actual: "+actual[i]); }
		
		assertArrayEquals(expected, actual);
	}

	@Test
	public void testInsertionSortReverse()
	{
		array.add(i3);
		array.add(i2);
		array.add(i1);

		ArrayList<Integer> arrayExpected = new ArrayList<>();

		arrayExpected.add(i1);
		arrayExpected.add(i2);
		arrayExpected.add(i3);
		
		Integer[] expected = new Integer[arrayExpected.size()];
		for (int i = 0; i < arrayExpected.size(); i++){ expected[i] = arrayExpected.get(i); System.out.println("Expected: "+expected[i]);}
		
		sort.InsertionSort.insertionSort(array, 0, array.size() - 1, new IntegerComparator());
		
		Integer[] actual = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ actual[i] = array.get(i); System.out.println("Expected: "+actual[i]); }
		
		assertArrayEquals(expected, actual);
	}
	
	/**
	*	TEST ON QUICK SORT
	**/
	
	@Test
	public void testQuickSortEmptyArray()
	{
		sort.QuickSort.quickSort(array, 0, array.size() - 1, new IntegerComparator());
		
		assertTrue(array.isEmpty());
	}
	
	@Test
	public void testQuickSortAllIdenticalEl()
	{
		array.add(i1);
		array.add(i1);
		array.add(i1);
		
		Integer[] expected = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ expected[i] = array.get(i); }
		
		sort.QuickSort.quickSort(array, 0, array.size() - 1, new IntegerComparator());
		
		Integer[] actual = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ actual[i] = array.get(i); }
		
		assertArrayEquals(expected, actual);
	}

	@Test
	public void testQuickSort()
	{
		array.add(i1);
		array.add(i2);
		array.add(i3);
		
		Integer[] expected = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ expected[i] = array.get(i); }
		
		sort.QuickSort.quickSort(array, 0, array.size() - 1, new IntegerComparator());
		
		Integer[] actual = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ actual[i] = array.get(i); }
		
		assertArrayEquals(expected, actual);
	}

	@Test
	public void testQuickSortReverse()
	{
		array.add(i3);
		array.add(i2);
		array.add(i1);

		ArrayList<Integer> arrayExpected = new ArrayList<>();

		arrayExpected.add(i1);
		arrayExpected.add(i2);
		arrayExpected.add(i3);
		
		Integer[] expected = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ expected[i] = arrayExpected.get(i); }
		
		sort.QuickSort.quickSort(array, 0, array.size() - 1, new IntegerComparator());
		
		Integer[] actual = new Integer[array.size()];
		for (int i = 0; i < array.size(); i++){ actual[i] = array.get(i); }
		
		assertArrayEquals(expected, actual);
	}
	
}

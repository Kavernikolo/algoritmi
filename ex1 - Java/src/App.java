import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.concurrent.TimeUnit;

import record.CompareID;

import record.CompareFieldINT;
import record.CompareFieldSTRING;
import record.CompareFieldFLOAT;

import record.Record;
import record.RecordException;

import sort.QuickBinaryInsertionSort;
import sort.SorterException;


public class App 
{
    private static final Charset ENCODING = StandardCharsets.UTF_8;

    private static void printArray(ArrayList<Record> orderedArray)
    {
        Record currRec =null;

        System.out.println("\nORDERED ARRAY OF RECORDS\n");

        for(int i = 0; i < orderedArray.size(); i++)
        {
            currRec=orderedArray.get(i);
            System.out.println("<"+currRec.getID()+" - "+currRec.getField_1()+","+currRec.getField_2()+","+currRec.getField_3()+">\n");
            
        }
    }

    private static <T> void isOrdered(ArrayList<T> array, Comparator<T> comparator)
    {
        boolean sortingIsCorrect = true;

        int i = 0;
        
        long startTime = System.nanoTime();
        while(sortingIsCorrect && i < array.size()-1)
        {
            if(comparator.compare(array.get(i), array.get(i++)) <= 0){ i++; }
            else{ sortingIsCorrect = false; }
        }

        long endTime = System.nanoTime();
        if(sortingIsCorrect){ System.out.println("The sorting is correct\nCHECKING TIME: " + TimeUnit.NANOSECONDS.toSeconds(endTime - startTime) + " SECONDS\n"); }
        else{ System.out.println("The sorting is wrong\nCHECKING TIME: " + TimeUnit.NANOSECONDS.toSeconds(endTime - startTime) + " SECONDS\n"); }
    }

    private static void loadArray(String filepath, ArrayList<Record> array) throws IOException, RecordException
    {
        Path inputFilePath = Paths.get(filepath);
        
        try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING))
        {
            String line;
            int lineCounter = 0;

            long startTime = System.nanoTime();
            while((line = fileInputReader.readLine()) != null)
            {
                String[] lineElements = line.split(",");

                Record current = new Record(Integer.parseInt(lineElements[0]), lineElements[1], Integer.parseInt(lineElements[2]), Float.parseFloat(lineElements[3]));
                array.add(current);

                lineCounter++;
            }
            long endTime = System.nanoTime();
            System.out.println("File loaded in: " + TimeUnit.NANOSECONDS.toSeconds(endTime - startTime) + " SECONDS");

            System.out.println("Number line: "+lineCounter);
        }
    }
    
    public static void sorting(String filepath, Comparator<Record> comparator) throws IOException, RecordException, SorterException
    {
            ArrayList<Record> array = new ArrayList<>();
		    loadArray(filepath, array);
            
            long startTime = System.nanoTime();
                QuickBinaryInsertionSort.quickBinaryInsertionSort(array, comparator);
            long endTime = System.nanoTime();
            System.out.println("File ordered in: " + TimeUnit.NANOSECONDS.toSeconds(endTime - startTime) + " SECONDS\n");
            System.out.println("Order check...\n");
                isOrdered(array, comparator);
            //printArray(array);
    }
    
    public static void main(String[] args) throws IOException, RecordException, Exception
    {
        if(args.length < 1){  throw new Exception("Usage: RecordArrayUsageJava <file_name>"); }

        System.out.println ("------------ID------------\n");
            sorting(args[0], new CompareID());

        System.out.println ("------------STRING------------\n");
            sorting(args[0], new CompareFieldSTRING());

        System.out.println ("------------INT------------\n");
            sorting(args[0], new CompareFieldINT());

        System.out.println ("------------FLOAT------------\n");
            sorting(args[0], new CompareFieldFLOAT());     		
	}  
}
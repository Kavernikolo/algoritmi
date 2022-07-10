import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;


public class AppTestForK
{
    private static final Charset ENCODING = StandardCharsets.UTF_8;

    //private static final int K_STRING = 0;
    //private static final int K_INTEGER = 0;
    //private static final int K_FLOAT = 0;
    
    /*private static void printArray(ArrayList<Record> array) throws RecordArrayException
    {
        Record current = null;
        int sizeArrary = array.size();
        
        for(int i=0; i < sizeArrary; i++)
        {
            current = array.get(i);
            System.out.println("<["+current.getID()+"], "+current.getField_1()+", "+current.getField_2()+", "+current.getField_3()+">\n");
        }
    }*/

    private static void loadArray(String filepath, ArrayList<Record> array) throws IOException, RecordArrayException
    {
        Path inputFilePath = Paths.get(filepath);
        
        try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING))
        {
            String line;
            int lineCounter = 0;
            
            while((line = fileInputReader.readLine()) != null)
            {
                String[] lineElements = line.split(",");

                Record current = new Record(Integer.parseInt(lineElements[0]), lineElements[1], Integer.parseInt(lineElements[2]), Float.parseFloat(lineElements[3]));
                array.add(current);

                lineCounter++;
            }
            System.out.println("Number line: "+lineCounter);
        }
    }
    
    public static void sort(String filepath, Comparator<Record> comparator) throws IOException, RecordArrayException
    {
        int chooseK = 1;

        while(chooseK < 1024000)
        {
            System.out.print("I = " +chooseK+ "\n");
            
            ArrayList<Record> array = new ArrayList<>();
		    loadArray(filepath, array);
        
            long start = System.currentTimeMillis();
            //System.out.print("Start: " +start / 1000.0+ "\n");
                Sorting.QuickBinaryInsertionSort(array, comparator, chooseK);
            long finish = System.currentTimeMillis();
            
            //System.out.print("Finish: " +finish / 1000.0+ "\n");
                long timeElapsed = finish - start;
            
            System.out.println("Time: " +timeElapsed / 1000.0 + " Seconds - "+((timeElapsed / 1000.0) / 60)+ " Minutes \n");
            System.out.println("\n");
            
            chooseK = chooseK*2;
        }
        System.out.println("End");
    }
    
    public static void main(String[] args) throws IOException, RecordArrayException, Exception
    {
        if(args.length < 1){  throw new Exception("Usage: RecordArrayUsageJava <file_name>"); }

        System.out.println ("### SORTING BY STRING ###\n");
            sort(args[0], new CompareFieldSTRING());
        /*
        System.out.println ("### SORTING BY INTEGER ###\n");
            sort(args[0], new CompareFieldINT());
        
        System.out.println ("### SORTING BY FLOATING POINT ###\n");
            sort(args[0], new CompareFieldFLOAT()); */      		
	}  
}
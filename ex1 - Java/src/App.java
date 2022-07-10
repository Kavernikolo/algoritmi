import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;


public class App 
{
    private static final Charset ENCODING = StandardCharsets.UTF_8;

    private static final int K_STRING = 0;
    private static final int K_INTEGER = 0;
    private static final int K_FLOAT = 0;

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
    
    public static void sort(String filepath, Comparator<Record> comparator, int K_FIELD) throws IOException, RecordArrayException
    {
            ArrayList<Record> array = new ArrayList<>();
		    loadArray(filepath, array);
            
            Sorting.QuickBinaryInsertionSort(array, comparator, K_FIELD);
    }
    
    public static void main(String[] args) throws IOException, RecordArrayException, Exception
    {
        if(args.length < 1){  throw new Exception("Usage: RecordArrayUsageJava <file_name>"); }

        System.out.println ("### SORTING BY STRING ###\n");
            sort(args[0], new CompareFieldSTRING(), K_STRING);

        System.out.println ("### SORTING BY INTEGER ###\n");
            sort(args[0], new CompareFieldINT(), K_INTEGER);

        System.out.println ("### SORTING BY FLOATING POINT ###\n");
            sort(args[0], new CompareFieldFLOAT(), K_FLOAT);        		
	}  
}
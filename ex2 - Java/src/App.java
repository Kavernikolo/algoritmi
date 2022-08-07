import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.TimeUnit;

public class App
{
    private static final Charset ENCODING = StandardCharsets.UTF_8;

    private static void loadDictionary(String filepath, SkipList<String> list) throws IOException
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

                String current = lineElements[1];
                list.insert(current);

                lineCounter++;
            }
            long endTime = System.nanoTime();
            System.out.println("File loaded in: " + TimeUnit.NANOSECONDS.toSeconds(endTime - startTime) + " SECONDS");

            System.out.println("Number line: "+lineCounter);
        }
    }

    private static void loadCorrectme(String filepath, ArrayList<String> array) throws IOException
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

                String current = lineElements[1];
                array.add(current);

                lineCounter++;
            }
            long endTime = System.nanoTime();
            System.out.println("File loaded in: " + TimeUnit.NANOSECONDS.toSeconds(endTime - startTime) + " SECONDS");

            System.out.println("Number string: "+lineCounter);
        }
    }

    public static void useSkipList(String dictionaryPath, String correctmePath) throws IOException
    {
        SkipList<String> list = new SkipList<>();
            loadDictionary(dictionaryPath, list);
        
        ArrayList<String> array = new ArrayList<>();
            loadCorrectme(correctmePath, array);

        int i = 0;
        while(i < array.size() - 1)
        {
            list.search(array.get(i));
            i++;
        }
        
    }
    public static void main(String[] args) throws Exception
    {
        if(args.length < 2){  throw new Exception("Usage: App <dictionary.txt> <correctme.txt>"); }

    }
}
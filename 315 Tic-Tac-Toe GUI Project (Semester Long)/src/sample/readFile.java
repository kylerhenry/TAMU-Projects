package sample;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class readFile
{
    private Scanner x;

    public void openFile()
    {
        try
        {
            x = new Scanner(new File("score.txt"));
        } catch (Exception e) {
            System.out.println("File not found");  // for testing purposes
        }
    }

    public void  readFile()
    {
        while(x.hasNext())
        {
            String a = x.next();
            String b = x.next();

            System.out.println(a + ", " + b);

        }
    }

    public void  closeFile()
    {
        x.close();
    }

}

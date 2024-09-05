import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class OSLab8_03 {
    public static void main(String [] args)
    {
        int numTask = Integer.parseInt("10");
        ExecutorService pool = Executors.newCachedThreadPool();
        for(int i = 0; i < numTask; i++)
        {
            Runner runner = new Runner(i);
            pool.execute(runner);
        }
        pool.shutdown();
    }
}

class Runner implements Runnable
{
    private int num;
    Runner(int num)
    {
        this.num = num;
    }
    public void run()
    {
        System.out.println("I'm working on task#" + num + ", thread id: " + Thread.currentThread().getId());
    }
}


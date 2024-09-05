public class OSLab8_02 {
    public static void main(String args[])
    {
        Task task = new Task();
        task.start();
        try
        {
            Thread.sleep(100);
        } catch(InterruptedException ie)
        {}
        task.interrupt();
    }
}

class Task extends Thread
    {
        int count = 0;
        public void run()
        {
            while(true)
            {
                count += 1;
                System.out.println("I'm doing work#" + count);
                System.out.println("I'm done for work#" + count);
                if(Thread.currentThread().isInterrupted())
                {
                    System.out.println("I'm interrupted !!!");
                    break;
                }
            }
        }
    }
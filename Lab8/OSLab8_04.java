public class OSLab8_04 {
    public static void main(String[] args)
    {
        int num = 10;
        MyObject obj = new MyObject();
        Thread thd01 = new Thread(new Task01(obj, 20));
        Thread thd02 = new Thread(new Task02(obj, 30));
        thd01.start(); thd02.start();
        // try {thd01.join(); thd02.join();} catch (Exception e){}
        obj.calculated(num);
        System.out.println("From master#0 thread ID: " + Thread.currentThread().getId() + ", value is " + obj.getValue());
    }
}

class Task01 extends Thread
{
    private int num;
    private MyObject obj;
    Task01(MyObject obj, int num)
    {
        this.num = num;
        this.obj = obj;
    }

    public void run()
    {
        obj.calculated(num);
        System.out.println("From worker#1 thread ID: " + Thread.currentThread().getId() + ", value is " + obj.getValue());
    }
}

class Task02 implements Runnable
{
    private int num;
    private MyObject obj;
    Task02(MyObject obj, int num)
    {
        this.num = num;
        this.obj = obj;
    }

    public void run()
    {
        obj.calculated(num);
        System.out.println("From worker#2 thread ID: " + Thread.currentThread().getId() + ", value is " + obj.getValue());
    }
}

class MyObject
{
    private int value;
    MyObject()
    {
        setValue(0);
    }

    public void calculated(int num)
    {
        value += num;
    }

    private void setValue(int value)
    {
        this.value = value;
    }

    public int getValue()
    {
        return value;
    }
}
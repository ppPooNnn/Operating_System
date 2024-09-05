import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class OSLab8_MatrixMulThread 
{
    public static void main(String args[])
    {
        int matrixA[][] = {{5, 10, 13}, {12, 22, 9}};
        int matrixB[][] = {{11, 21}, {51, 12}, {20, 18}};
        MyData dataA = new MyData(matrixA);
        MyData dataB = new MyData(matrixB);
        int matrixC_row = dataA.data.length;
        int matrixC_col = dataB.data[0].length;
        MyData dataC = new MyData(matrixC_row, matrixC_col);

        ExecutorService pool = Executors.newCachedThreadPool();
        
        int start = (int)System.currentTimeMillis();

        for(int i = 0; i < matrixC_row; i++)
        {
            for(int j = 0; j < matrixC_col; j++)
            {
                Thread thread = new Thread(new MatrixMulThread(i, j, dataA, dataB, dataC));
                pool.execute(thread);
            }
        }
        pool.shutdown();

        try {
           pool.awaitTermination(10, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
        }

        dataC.show();

        int end = (int)System.currentTimeMillis() - start;
        System.out.println(end);
    }
}

class MatrixMulThread implements Runnable
{
    private int processingRow;
    private int processingCol;
    private MyData dataA;
    private MyData dataB;
    private MyData dataC;
    MatrixMulThread(int targetRow, int targetCol, MyData dataA, MyData dataB, MyData dataC)
    {
        processingRow = targetRow;
        processingCol = targetCol;
        this.dataA = dataA;
        this.dataB = dataB;
        this.dataC = dataC;
    }

    public void run()
    {
        int sum = 0;
        for(int i = 0; i < dataA.data[0].length; i++)
            sum += dataA.data[processingRow][i] * dataB.data[i][processingCol];
        dataC.data[processingRow][processingCol] = sum;
    }
}

class MyData
{
    public int data[][];
    MyData(int data[][])
    {
        this.data = data;
    }
    MyData(int row, int col)
    {
        data = new int[row][col];
        for(int aRow[] : data)
        {
            Arrays.fill(aRow, 0);
        }
    }

    public void show()
    {
        System.out.println(Arrays.deepToString(data));
    }
}

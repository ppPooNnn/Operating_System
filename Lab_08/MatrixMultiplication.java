public class MatrixMultiplication {
    public static void main(String[] args) {
        int[][] matrixA = {
            {5, 10, 13},
            {12, 22, 9}
        };
        int[][] matrixB = {
            {11, 21},
            {51, 12},
            {20, 18}
        };

        int start = (int)System.currentTimeMillis();
        int[][] matrixC = multiplyMatrices(matrixA, matrixB);

        // Display the result
        System.out.println("Result of Matrix Multiplication:");
        displayMatrix(matrixC);
        int end = (int)System.currentTimeMillis() - start;
        System.out.println(end);
    }

    public static int[][] multiplyMatrices(int[][] matrixA, int[][] matrixB) {
        int rowsA = matrixA.length;
        int colsA = matrixA[0].length;
        int colsB = matrixB[0].length;

        // Initialize the result matrix with appropriate size
        int[][] matrixC = new int[rowsA][colsB];

        // Multiply the matrices
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                for (int k = 0; k < colsA; k++) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }

        return matrixC;
    }

    public static void displayMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int element : row) {
                System.out.print(element + "\t");
            }
            System.out.println();
        }
    }
}
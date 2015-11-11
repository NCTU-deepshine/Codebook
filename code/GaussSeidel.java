import java.io.*;
import java.util.*;

class GaussSeidel{
    
    double[][] matrix;
    double[] vector;
    int n;
    
    GaussSeidel(double[][] matrix){
        this.matrix = matrix;
        n = matrix.length;
        vector = new vector[n];
    }
    
    solve(int iteration){
        for(int round=0;round<iteration;round++){
            for(int i=0;i<n;i++){
                double sum = 0.0;
                for(int j=0;j<n;j++){
                    if(i==j) continue;
                    sum += matrix[i][j] * vector[j];
                }
                vector[i] = (vector[i] - sum) / matrix[i][i];
            }
        }
    }
    
}

using System;

namespace ASA
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] A = {2, 5, 3, 0, 2, 3, 0, 3};
            int[] B = new int[A.Length];
            int k = A.Max();

            int[] C = new int[k + 1];
            for(int i = 0; i < A.Length; i++){
                C[A[i]] = C[A[i]] + 1;
            }

            for(int i = 1; i < k + 1; i++){
                C[i] = C[i] + C[i-1];      //224778
            }
            for(int i = A.Length - 1; i >= 0; i--){
                B[C[A[i]] - 1] = A[i];
                C[A[i]] = C[A[i]] - 1;
            }

            for(int i = 0; i < B.Length; i++)
            {
                System.Console.WriteLine(B[i]);
            }
        }
    }
}
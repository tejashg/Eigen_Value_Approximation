// C++ Program to find the Eigen Values and Eigen Vectors of a Matrix iteratively using Q-R Algorithm.

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Check for Identity Matrix

bool checkidentity(vector<vector<float>> &A, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            if ((i == j && A[i][j] != 1) || (i != j && A[i][j] != 0))
                return false;
    }
    return true;
}

// Multiplying two Matrices

vector<vector<float>> multiply(vector<vector<float>> &A, vector<vector<float>> &B, int size)
{
    vector<vector<float>> ans(size, vector<float>(size, 0));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                ans[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return ans;
}

// Transpose of a Matrix

vector<vector<float>> transpose(vector<vector<float>> A, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i < j)
                swap(A[i][j], A[j][i]);

    return A;
}

// Q-R Decomposition using the Gram-Schmidt Process

pair<vector<vector<float>>, vector<vector<float>>> qrdecom(vector<vector<float>> &A, int size)
{
    vector<vector<float>> Anew = A;

    vector<vector<float>> Q(size, vector<float>(size));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            float temp = 0;
            for (int k = 0; k < size; k++)
                temp += Q[k][j] * A[k][i];
            for (int k = 0; k < size; k++)
                Anew[k][i] -= temp * Q[k][j];
        }
        float magnitude = 0;
        for (int j = 0; j < size; j++)
            magnitude += Anew[j][i] * Anew[j][i];
        magnitude = sqrt(magnitude);
        for (int j = 0; j < size; j++)
            Q[j][i] = Anew[j][i] / magnitude;
    }

    vector<vector<float>> R;
    vector<vector<float>> Qtrans = transpose(Q, size);
    R = multiply(Qtrans, A, size);

    return {Q, R};
}

// Displaying the Matrix

void display(vector<vector<float>> &A, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << A[i][j] << "  ";
        cout << "\n";
    }
}

int main()
{
    // Taking size as input
    int size;
    cout << "\nEnter Size of Matrix : ";
    cin >> size;

    // Taking Matrix as input
    vector<vector<float>> A(size, vector<float>(size));
    cout << "\nEnter Matrix Elements :\n\n";
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }

    // Displaying the Matrix
    cout << "\nGiven Matrix :\n\n";
    display(A, size);

    // Q-R Algorithm
    int step = 0;
    vector<vector<float>> Q;
    vector<vector<float>> R;
    pair<vector<vector<float>>, vector<vector<float>>> p;
    while (step < 15)
    {
        cout << "\nStep " << step + 1 << " :\n\n";
        cout << "A" << step << " :\n\n";
        display(A, size);
        p = qrdecom(A, size);
        Q = p.first;
        R = p.second;
        cout << "\nQ" << step + 1 << " :\n\n";
        display(Q, size);
        cout << "\nR" << step + 1 << " :\n\n";
        display(R, size);
        if (checkidentity(Q, size))
            break;
        A = multiply(R, Q, size);
        step++;
    }

    // Displaying the Eigen Values
    cout << "\nEigen Values are :  ";
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j)
                cout << A[i][j] << "  ";
}
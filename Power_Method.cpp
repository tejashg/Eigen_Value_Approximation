// C++ Program to approximate the Eigen Values and Eigen Vectors of a Matrix iteratively using Power Method.

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void solve(vector<vector<float>> &A, vector<float> X, int size, float eigen, int step)
{
    vector<float> res(size, 0);
    float maximum = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            res[i] += A[i][j] * X[j];
        }
        if (fabs(res[i]) > fabs(maximum))
            maximum = res[i];
    }

    for (int i = 0; i < size; i++)
        res[i] /= maximum;

    cout << "\nSTEP " << step << ":" << endl
         << "Dominant eigen value is : " << maximum << " and the corresponding eigen vector is: " << endl;
    for (int i = 0; i < size; i++)
        cout << res[i] << endl;

    if (eigen != maximum)
        solve(A, res, size, maximum, step + 1);
}

int main()
{
    // Taking size as input
    int size;
    cout << "\nEnter Size of Matrix: ";
    cin >> size;

    // Taking Matrix as input
    vector<vector<float>> A(size, vector<float>(size));
    cout << "\nEnter Matrix Elements: " << endl;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }

    // Displaying the Matrix
    cout << "\nGiven Matrix: " << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << A[i][j] << "  ";
        cout << endl;
    }

    // Initial Guess Vector
    vector<float> X0(size, 1);

    float eigen = 0;
    int step = 1;

    solve(A, X0, size, eigen, step);
}
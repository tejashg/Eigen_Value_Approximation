// C++ Program to find the Eigen Values of a Matrix iteratively using Q-R Algorithm.

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

// Check for Identity Matrix

bool checkidentity(vector<vector<double>> &A, int size, int precision)
{
    double temp = 1 * 1.0 / pow(10, precision);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            if ((i == j && abs(abs(A[i][j]) - 1) >= temp) || (i != j && (abs(A[i][j]) >= temp)))
                return false;
    }
    return true;
}

// Multiplying two Matrices

vector<vector<double>> multiply(vector<vector<double>> &A, vector<vector<double>> &B, int size)
{
    vector<vector<double>> ans(size, vector<double>(size, 0));

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

vector<vector<double>> transpose(vector<vector<double>> A, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i < j)
                swap(A[i][j], A[j][i]);

    return A;
}

// Q-R Decomposition using the Gram-Schmidt Process

pair<vector<vector<double>>, vector<vector<double>>> qrdecom(vector<vector<double>> &A, int size)
{
    vector<vector<double>> Anew = A;

    vector<vector<double>> Q(size, vector<double>(size));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            double temp = 0;
            for (int k = 0; k < size; k++)
                temp += Q[k][j] * A[k][i];
            for (int k = 0; k < size; k++)
                Anew[k][i] -= temp * Q[k][j];
        }
        double magnitude = 0;
        for (int j = 0; j < size; j++)
            magnitude += Anew[j][i] * Anew[j][i];
        magnitude = sqrt(magnitude);
        for (int j = 0; j < size; j++)
            Q[j][i] = Anew[j][i] / magnitude;
    }

    vector<vector<double>> R;
    vector<vector<double>> Qtrans = transpose(Q, size);
    R = multiply(Qtrans, A, size);

    return {Q, R};
}

// Displaying the Matrix

void display(vector<vector<double>> &A, int size, int precision)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << fixed << setprecision(precision) << A[i][j] << "  ";
        cout << "\n";
    }
}

int main()
{
    // Taking size as input
    int size;
    // cout << "\nEnter Size of Matrix : ";
    cin >> size;

    // Taking Matrix as input
    vector<vector<double>> A(size, vector<double>(size));
    // cout << "\nEnter Matrix Elements :\n\n";
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            // cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }

    // Displaying the Matrix
    // cout << "\nGiven Matrix :\n\n";
    // display(A, size);

    // Taking Precision as Input
    int precision;
    cin >> precision;

    // Taking Number of Iterations as Input
    int steps;
    cin >> steps;

    stringstream ss;                                 // create a stringstream object
    streambuf *oldBuf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stringstream

    // Q-R Algorithm
    int step = 0;
    vector<vector<double>> Q;
    vector<vector<double>> R;
    pair<vector<vector<double>>, vector<vector<double>>> p;
    while (step < steps)
    {
        cout << "\nStep " << step + 1 << " :\n\n";
        cout << "A" << step << " :\n\n";
        display(A, size, precision);
        p = qrdecom(A, size);
        Q = p.first;
        R = p.second;
        cout << "\nQ" << step + 1 << " :\n\n";
        display(Q, size, precision);
        cout << "\nR" << step + 1 << " :\n\n";
        display(R, size, precision);
        if (checkidentity(Q, size, precision))
            break;
        A = multiply(R, Q, size);
        step++;
    }

    // Displaying the Eigen Values
    cout << "\nEigen Values are :  " << endl;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i == j)
                cout << endl
                     << fixed << setprecision(precision) << A[i][j];

    cout.rdbuf(oldBuf);
    string output = ss.str(); // extract the string from the stringstream
    cout << output << endl;   // output the string
}
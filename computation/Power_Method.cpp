// C++ Program to approximate the Eigen Values and Eigen Vectors of a Matrix iteratively using Power Method.

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

void solve(int size, vector<vector<double>> &A, vector<double> &X, int precision, int maxstep, double eigen, int step)
{
    vector<double> res(size, 0);
    double maximum = 0;

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

    double temp = 1 * 1.0 / pow(10, precision);

    if (abs(eigen - maximum) < temp)
        return;

    cout << "\nSTEP " << step << ":" << endl
         << "Dominant eigen value is : " << fixed << setprecision(precision) << maximum << " and the corresponding eigen vector is: " << endl;
    for (int i = 0; i < size; i++)
        cout << "/n"
             << fixed << setprecision(precision) << res[i] << endl;

    if (maxstep == step)
    {
        return;
    }

    solve(size, A, res, precision, maxstep, maximum, step + 1);
}

string output(int size, vector<vector<double>> &A, vector<double> &X0, int precision, int maxstep)
{
    double eigen = 0;
    int step = 1;

    stringstream ss;                                 // create a stringstream object
    streambuf *oldBuf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stringstream

    solve(size, A, X0, precision, maxstep, eigen, step);

    cout.rdbuf(oldBuf);
    string output = ss.str(); // extract the string from the stringstream
    cout << output << endl;   // output the string
    return output;
}

int main()
{
    // Taking size as input
    int size;
    // cout << "\nEnter Size of Matrix: ";
    cin >> size;

    // Taking Matrix as Input
    vector<vector<double>> A(size, vector<double>(size));
    // cout << "\nEnter Matrix Elements: " << endl;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            // cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }

    // Taking Guess Vector as Input
    vector<double> X0(size, 1);
    // for (int i = 0; i < size; i++)
    // {
    //     cin >> X0[i];
    // }

    // Taking Precision as Input
    int precision;
    cin >> precision;

    // Taking Number of Iterations as Input
    int steps;
    cin >> steps;

    // Displaying the Matrix
    // cout << "\nGiven Matrix: " << endl;
    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = 0; j < size; j++)
    //         cout << A[i][j] << "  ";
    //     cout << endl;
    // }

    output(size, A, X0, precision, steps);
}
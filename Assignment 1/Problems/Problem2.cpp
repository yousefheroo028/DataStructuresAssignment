#include <iostream>
#include <fstream>
using namespace std;

class Polynomial{
private:
    int degree;
    double* coefficients;

public:
    Polynomial(int degree) : degree(degree){
        coefficients = new double[degree + 2];
    }

    ~Polynomial(){
        delete[] coefficients;
    }

    void input(ifstream& file){
        for (int i = 0; i < degree + 2; i++)
        {
            file >> coefficients[i];
        }
        
    }

    void display() const{
        bool first = true;
        for (int i = degree + 1; i > 0 ; i--)
        {
            if (coefficients[i] != 0)
            {   
                if (!first)
                {
                    if (coefficients[i] < 0)
                    {
                        cout << " - ";   
                    }
                    else
                    {
                        cout << " + ";
                    }
                }
                else
                {
                    if (coefficients[i] < 0)
                    {
                        cout << "-";
                    }
                    first = false;
                }
                if (abs(coefficients[i]) != 1 && i-1 > 0)
                {
                    cout << abs(coefficients[i]);
                }
                if (i-1 == 0)
                {
                    cout << abs(coefficients[i]);
                }
                if (i-1 > 0) 
                {
                    cout << "x";
                }
                if (i-1 > 1)
                {
                    cout << "^" << i-1;
                }
            }
        }
        if (first)
        {
            cout << "0" << endl;
        }
        else
        {
            cout << " = "  << coefficients[0] << endl;
        }
    }

    Polynomial operator+(const Polynomial& other){
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i < maxDegree + 2; i++)
        {
            double coef1 = (i < degree + 2) ? coefficients[i] : 0;
            double coef2 = (i < other.degree + 2) ? other.coefficients[i] : 0;
            result.coefficients[i] = coef1 + coef2;
        }
        return result;
    }

    Polynomial operator-(const Polynomial& other){
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i < maxDegree + 2; i++)
        {
            double coef1 = (i < degree + 2) ? coefficients[i] : 0;
            double coef2 = (i < other.degree + 2) ? other.coefficients[i] : 0;
            result.coefficients[i] = coef1 - coef2;
        }
        return result;            
    }
};


int main(){
    ifstream file("test2.txt");
    if (!file)
    {
        cerr << "Error: could not open the file";
        return 1;
    }

    while(true){
        int degree1, degree2;
    
        if(!(file >> degree1)) break;
        Polynomial p1(degree1);
        p1.input(file);

        if(!(file >> degree2)) break;
        Polynomial p2(degree2);
        p2.input(file);

        cout << endl;

        cout << "First polynomial: ";
        p1.display();

        cout << "Second polynomial: ";
        p2.display();

        Polynomial sum = p1 + p2;
        cout << "Sum of polynomials: ";
        sum.display();

        Polynomial diff = p2 - p1;
        cout << "Difference of polynomials: ";
        diff.display();
    }
    return 0;
}


/*
Test cases:
-----------------------------------------
Test Case 1: Simple Polynomials

Input: 
Order of first polynomial: 2
Enter polynomial: 1 0 -3 2
Order of second polynomial: 2
Enter polynomial: 2 1 0 -1

Output:
First polynomial: 2x^2 - 3x = 1
Second polynomial: -x^2 + 1 = 2
Sum of polynomials: x^2 - 3x + 1 = 3
Difference of polynomials: -3x^2 + 3x + 1 = 1
-----------------------------------------
Test Case 2: Polynomials with Zero Coefficients

Input:
Order of first polynomial: 3
Enter polynomial: 0 0 0 0 5
Order of second polynomial: 3
Enter polynomial: 0 0 0 0 -5

Output:
First polynomial: 5x^3 = 0
Second polynomial: -5x^3 = 0
Sum of polynomials: 0
Difference of polynomials: -10x^3 = 0
-----------------------------------------
Test Case 3: Polynomials with Negative Coefficients

Input:
Order of first polynomial: 2
Enter polynomial: -1 -2 -3 0
Order of second polynomial: 2
Enter polynomial: 3 2 1 0

Output:
First polynomial: -3x - 2 = -1
Second polynomial: x + 2 = 3
Sum of polynomials: -2x = 2
Difference of polynomials: 4x + 4 = 4
-----------------------------------------
Test Case 4: Polynomials with Same Degree and Coefficients

Input:
Order of first polynomial: 1
Enter polynomial: 1 1 1
Order of second polynomial: 1
Enter polynomial: 1 1 1

Output:
First polynomial: x + 1 = 1
Second polynomial: x + 1 = 1
Sum of polynomials: 2x + 2 = 2
Difference of polynomials: 0
-----------------------------------------
Test Case 5: Polynomials with Different Degrees

Input:
Order of first polynomial: 2
Enter polynomial: 1 2 3 4
Order of second polynomial: 3
Enter polynomial: 1 1 1 1 1

Output:
First polynomial: 4x^2 + 3x + 2 = 1
Second polynomial: x^3 + x^2 + x + 1 = 1
Sum of polynomials: x^3 + 5x^2 + 4x + 3 = 2
Difference of polynomials: x^3 - 3x^2 - 2x - 1 = 0
-----------------------------------------
*/
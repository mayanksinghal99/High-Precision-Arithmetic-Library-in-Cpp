#include <bits/stdc++.h>
using namespace std;

// Class definition for BigInt
class BigInt
{
    string digits; // String to store the digits of the large number

public:
    // Constructors
    BigInt(unsigned long long n = 0);
    BigInt(string &);
    BigInt(const char *);
    BigInt(BigInt &);

    // Helper Functions
    friend void divide_by_2(BigInt &a);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);
    int operator[](const int) const;

    /* * * * Operator Overloading * * * */

    // Direct assignment
    BigInt &operator=(const BigInt &);

    // Post/Pre-Incrementation
    BigInt &operator++();
    BigInt operator++(int temp);
    BigInt &operator--();
    BigInt operator--(int temp);

    // Addition and Subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);

    // Comparison operators
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    // Multiplication and Division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);

    // Modulo
    friend BigInt operator%(const BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);

    // Power Function
    friend BigInt &operator^=(BigInt &, const BigInt &);
    friend BigInt operator^(BigInt &, const BigInt &);

    // Square Root Function
    friend BigInt sqrt(BigInt &a);

    // Read and Write
    friend ostream &operator<<(ostream &, const BigInt &);
    friend istream &operator>>(istream &, BigInt &);

    // Others
    friend BigInt NthCatalan(int n);
    friend BigInt NthFibonacci(int n);
    friend BigInt Factorial(int n);
};

// Constructors

// Constructor to initialize from a string
BigInt::BigInt(string &s)
{
    int n = s.size();
    for (int i = n - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

// Constructor to initialize from an unsigned long long
BigInt::BigInt(unsigned long long nr)
{
    do
    {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}

// Constructor to initialize from a character array
BigInt::BigInt(const char *s)
{
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

// Copy constructor
BigInt::BigInt(BigInt &a)
{
    digits = a.digits;
}

// Helper Functions

// Function to check if a BigInt is null
bool Null(const BigInt &a)
{
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}

// Function to get the number of digits in a BigInt
int Length(const BigInt &a)
{
    return a.digits.size();
}

// Function to access individual digits of a BigInt using index
int BigInt::operator[](const int index) const
{
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}

// Operator Overloading

// Comparison operators

// Overloaded equality operator
bool operator==(const BigInt &a, const BigInt &b)
{
    return a.digits == b.digits;
}

// Overloaded inequality operator
bool operator!=(const BigInt &a, const BigInt &b)
{
    return !(a == b);
}

// Overloaded less than operator
bool operator<(const BigInt &a, const BigInt &b)
{
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
    {
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    }
    return false;
}

// Overloaded greater than operator
bool operator>(const BigInt &a, const BigInt &b)
{
    return b < a;
}

// Overloaded greater than or equal to operator
bool operator>=(const BigInt &a, const BigInt &b)
{
    return !(a < b);
}

// Overloaded less than or equal to operator
bool operator<=(const BigInt &a, const BigInt &b)
{
    return !(a > b);
}

// Assignment operator
BigInt &BigInt::operator=(const BigInt &a)
{
    digits = a.digits;
    return *this;
}

// Post-increment operator
BigInt &BigInt::operator++()
{
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9; i++)
        digits[i] = 0;
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}

// Pre-increment operator
BigInt BigInt::operator++(int temp)
{
    BigInt aux;
    aux = *this;
    ++(*this);
    return aux;
}

// Post-decrement operator
BigInt &BigInt::operator--()
{
    if (digits[0] == 0 && digits.size() == 1)
        throw("UNDERFLOW");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n; i++)
        digits[i] = 9;
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}

// Pre-decrement operator
BigInt BigInt::operator--(int temp)
{
    BigInt aux;
    aux = *this;
    --(*this);
    return aux;
}

// Addition and Subtraction

// Addition assignment operator
BigInt &operator+=(BigInt &a, const BigInt &b)
{
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t)
        a.digits.push_back(t);
    return a;
}

// Addition operator
BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

// Subtraction assignment operator
BigInt &operator-=(BigInt &a, const BigInt &b)
{
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10,
                t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(),
            n--;
    return a;
}

// Subtraction operator
BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

// Multiplication and Division

// Multiplication assignment operator
BigInt &operator*=(BigInt &a, const BigInt &b)
{
    if (Null(a) || Null(b))
    {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            v[i + j] += (a.digits[i]) * (b.digits[j]);
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        a.digits.pop_back();
    return a;
}

// Multiplication operator
BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}

// Division assignment operator
BigInt &operator/=(BigInt &a, const BigInt &b)
{
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b)
    {
        a = BigInt();
        return a;
    }
    if (a == b)
    {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
    {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--)
            ;
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    return a;
}

// Division operator
BigInt operator/(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}

// Modulo assignment operator
BigInt &operator%=(BigInt &a, const BigInt &b)
{
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b)
    {
        return a;
    }
    if (a == b)
    {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
    {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--)
            ;
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}

// Modulo operator
BigInt operator%(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}

// Power function

// Power assignment operator
BigInt &operator^=(BigInt &a, const BigInt &b)
{
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent))
    {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}

// Power operator
BigInt operator^(BigInt &a, BigInt &b)
{
    BigInt temp(a);
    temp ^= b;
    return temp;
}

// Helper function to divide a BigInt by 2
void divide_by_2(BigInt &a)
{
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--)
    {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
}

// Square root function
BigInt sqrt(BigInt &a)
{
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right)
    {
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod <= a)
        {
            v = mid;
            ++mid;
            left = mid;
        }
        else
        {
            --mid;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}

// Helper Functions for Factorial, Fibonacci, and Catalan Numbers

// Function to calculate Nth Catalan number
BigInt NthCatalan(int n)
{
    BigInt a(1), b;
    for (int i = 2; i <= n; i++)
        a *= i;
    b = a;
    for (int i = n + 1; i <= 2 * n; i++)
        b *= i;
    a *= a;
    a *= (n + 1);
    b /= a;
    return b;
}

// Function to calculate Nth Fibonacci number
BigInt NthFibonacci(int n)
{
    BigInt a(1), b(1), c;
    if (!n)
        return c;
    n--;
    while (n--)
    {
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}

// Function to calculate factorial of a number
BigInt Factorial(int n)
{
    BigInt f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

// Read and Write Operators

// Input operator
istream &operator>>(istream &in, BigInt &a)
{
    string s;
    in >> s;
    int n = s.size();
    a.digits.resize(n); // Resize the digits vector to the size of the input string
    for (int i = n - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i] - '0';
    }
    return in;
}

// Output operator
ostream &operator<<(ostream &out, const BigInt &a)
{
    for (int i = a.digits.size() - 1; i >= 0; i--)
        out << (short)a.digits[i];
    return out;
}

// Main function for testing
int main()
{
    // Menu-Driven Program
    int choice;
    BigInt num1, num2, result;
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Modulo\n";
        cout << "6. Power\n";
        cout << "7. Square Root\n";
        cout << "8. Nth Fibonacci Number\n";
        cout << "9. Nth Catalan Number\n";
        cout << "10. Factorial\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter first number: ";
            cin >> num1;
            cout << "Enter second number: ";
            cin >> num2;
            result = num1 + num2;
            cout << "Sum: " << result << endl;
            break;
        case 2:
            cout << "Enter first number: ";
            cin >> num1;
            cout << "Enter second number: ";
            cin >> num2;
            result = num1 - num2;
            cout << "Difference: " << result << endl;
            break;
        case 3:
            cout << "Enter first number: ";
            cin >> num1;
            cout << "Enter second number: ";
            cin >> num2;
            result = num1 * num2;
            cout << "Product: " << result << endl;
            break;
        case 4:
            cout << "Enter dividend: ";
            cin >> num1;
            cout << "Enter divisor: ";
            cin >> num2;
            try
            {
                result = num1 / num2;
                cout << "Quotient: " << result << endl;
            }
            catch (const char *msg)
            {
                cout << "Error: " << msg << endl;
            }
            break;
        case 5:
            cout << "Enter dividend: ";
            cin >> num1;
            cout << "Enter divisor: ";
            cin >> num2;
            try
            {
                result = num1 % num2;
                cout << "Remainder: " << result << endl;
            }
            catch (const char *msg)
            {
                cout << "Error: " << msg << endl;
            }
            break;
        case 6:
            cout << "Enter base: ";
            cin >> num1;
            cout << "Enter exponent: ";
            cin >> num2;
            result = num1 ^ num2;
            cout << "Result: " << result << endl;
            break;
        case 7:
            cout << "Enter number: ";
            cin >> num1;
            result = sqrt(num1);
            cout << "Square Root: " << result << endl;
            break;
        case 8:
            int n;
            cout << "Enter the value of N: ";
            cin >> n;
            result = NthFibonacci(n);
            cout << "Nth Fibonacci Number: " << result << endl;
            break;
        case 9:
            cout << "Enter the value of N: ";
            cin >> n;
            result = NthCatalan(n);
            cout << "Nth Catalan Number: " << result << endl;
            break;
        case 10:
            cout << "Enter the value of N: ";
            cin >> n;
            result = Factorial(n);
            cout << "Factorial: " << result << endl;
            break;
        case 0:
            cout << "Exiting the program. Goodbye!";
            exit(0);
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}

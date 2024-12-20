#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void simplify() {
        if (denominator == 0) throw std::invalid_argument("Denominator cannot be zero");
        int commonDivisor = gcd(numerator, denominator);
        numerator /= commonDivisor;
        denominator /= commonDivisor;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0) throw std::invalid_argument("Denominator cannot be zero");
        simplify();
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + denominator * other.numerator,
                        denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - denominator * other.numerator,
                        denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) throw std::invalid_argument("Division by zero");
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& frac) {
        char slash;
        is >> frac.numerator >> slash >> frac.denominator;
        if (frac.denominator == 0) throw std::invalid_argument("Denominator cannot be zero");
        frac.simplify();
        return is;
    }

    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }
};

int main() {
    try {
        Fraction f1(1, 2), f2(1, 3);
        std::cout << "f1 + f2 = " << f1 + f2 << std::endl;
        f1 += f2;
        std::cout << "f1 += f2 = " << f1 << std::endl;

        Fraction f3;
        std::cout << "Enter a fraction (numerator/denominator): ";
        std::cin >> f3;
        std::cout << "You entered: " << f3 << std::endl;
        std::cout << "Fraction to double: " << f3.toDouble() << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

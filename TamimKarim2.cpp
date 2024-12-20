#include <iostream>
#include <vector>
#include <limits>

class Vector {
private:
    std::vector<int> data;

public:
    Vector() {}

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        int value;
        vec.data.clear();
        while (is >> value) {
            vec.data.push_back(value);
        }
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "(";
        for (size_t i = 0; i < vec.data.size(); ++i) {
            os << vec.data[i];
            if (i != vec.data.size() - 1) os << ", ";
        }
        os << ")";
        return os;
    }

    Vector operator+(const Vector& other) const {
        Vector result;
        if (data.size() != other.data.size()) {
            std::cerr << "Error: Vectors must have the same size!" << std::endl;
            return result;
        }
        for (size_t i = 0; i < data.size(); ++i) {
            result.data.push_back(data[i] + other.data[i]);
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        Vector result;
        if (data.size() != other.data.size()) {
            std::cerr << "Error: Vectors must have the same size!" << std::endl;
            return result;
        }
        for (size_t i = 0; i < data.size(); ++i) {
            result.data.push_back(data[i] - other.data[i]);
        }
        return result;
    }

    Vector operator*(int scalar) const {
        Vector result;
        for (size_t i = 0; i < data.size(); ++i) {
            result.data.push_back(data[i] * scalar);
        }
        return result;
    }

    int operator*(const Vector& other) const {
        if (data.size() != other.data.size()) {
            std::cerr << "Error: Vectors must have the same size!" << std::endl;
            return 0;
        }
        int result = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector& operator+=(const Vector& other) {
        if (data.size() != other.data.size()) {
            std::cerr << "Error: Vectors must have the same size!" << std::endl;
            return *this;
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        if (data.size() != other.data.size()) {
            std::cerr << "Error: Vectors must have the same size!" << std::endl;
            return *this;
        }
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }
};

int main() {
    Vector v1, v2;

    std::cout << "Enter values for vector v1:" << std::endl;
    std::cin >> v1;

    std::cout << "Enter values for vector v2:" << std::endl;
    std::cin >> v2;

    Vector sum = v1 + v2;
    std::cout << "v1 + v2 = " << sum << std::endl;

    Vector diff = v1 - v2;
    std::cout << "v1 - v2 = " << diff << std::endl;

    Vector scaled = v1 * 2;
    std::cout << "v1 * 2 = " << scaled << std::endl;

    int dotProduct = v1 * v2;
    std::cout << "Dot product (v1 * v2) = " << dotProduct << std::endl;

    v1 += v2;
    std::cout << "v1 += v2: " << v1 << std::endl;

    v1 -= v2;
    std::cout << "v1 -= v2: " << v1 << std::endl;

    return 0;
}

#pragma once

#include "math.h"
using namespace std;


class Vector2 {
public:
    float x = 0.f, y = 0.f;

    Vector2() = default;

    explicit Vector2(float number) : x(number), y(number) {};

    Vector2(float x, float y) : x(x), y(y) {};

    Vector2(const Vector2& other) = default;

    Vector2& operator=(const Vector2& other) {
        if (this == &other) {
            return *this;
        }
        x = other.x;
        y = other.y;
        return *this;
    };

    Vector2 operator+(const Vector2& other) const {
        return { x + other.x, y + other.y };
    };

    Vector2& operator+=(const Vector2& other) {
        *this = *this + other;
        return *this;
    };

    Vector2 operator-(const Vector2& other) const {
        return { x - other.x, y - other.y };
    };

    Vector2 operator-() const {
        return { -x, -y};
    };

    Vector2& operator-=(const Vector2& other) {
        *this = *this - other;
        return *this;
    };

    Vector2 operator*(float number) const {
        return { x * number, y * number };
    };

    Vector2& operator*=(float number) {
        x = x * number;
        y = y * number;
        return *this;
    };

    Vector2 operator/(float number) const {
        if (number != 0.f) {
            return { x / number, y / number };
        }
        throw ("Divide by zero exception");
    };

    Vector2& operator/=(float number) {
        if (number != 0.f) {
            x = x / number;
            y = y / number;
            return *this;
        }
        throw ("Divide by zero exception");
    };

    float& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        throw ("Vector2 index out of range");
    };

    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw ("Vector2 index out of range");
    };

    Vector2 abs() const {
        return { std::abs(x), std::abs(y) };
    };

    float length() const {
        return sqrt(pow(x, 2) + pow(y, 2));
    };

    Vector2 normalize() const {
        if (length() != 0.f) {
            return { x / length(), y / length() };
        }
        return *this;
    };

    float dotProduct(const Vector2& other) const {
        return (x * other.x) + (y * other.y);
    };


    //However, often it is interesting to evaluate the cross product of two vectors 
    //assuming that the 2D vectors are extended to 3D
    //by setting their z-coordinate to zero. 
   // Vector3 crossProduct(const Vector2& other) const {
   //     return { 0, 0, (x * other.y) - (other.x * y) };
    //};

    bool operator==(const Vector2& other) const {
        return (x == other.x && y == other.y);
    };

    bool operator!=(const Vector2& other) const {
        return !(x == other.x && y == other.y);
    };

    friend std::ostream& operator<<(std::ostream& os, Vector2 vec) {
        os << "(" << vec.x << ", " << vec.y << ")" << endl;
        return os;
    };

};


class Vector3 {
public:
    float x = 0.f, y = 0.f, z = 0.f;

    Vector3() = default;

    explicit Vector3(float number) : x(number), y(number), z(number) {};

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

    Vector3(const Vector2& other) : x(other.x), y(other.y), z(0.f) {} ;

    Vector3(const Vector3& other) = default;

    Vector3& operator=(const Vector3& other) {
        if (this == &other) {
            return *this;
        }
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3 operator+(const Vector3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    };

    Vector3& operator+=(const Vector3& other) {
        *this = *this + other;
        return *this;
    };

    Vector3& operator+=(const float other) {
        *this = *this + Vector3(other);
        return *this;
    };

    Vector3 operator-(const Vector3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    };

    Vector3 operator-() const {
        return { -x, -y, -z };
    };

    Vector3& operator-=(const Vector3& other) {
        *this = *this - other;
        return *this;
    };

    Vector3 operator*(float number) const {
        return { x * number, y * number, z * number };
    };

    Vector3& operator*=(float number) {
        x = x * number;
        y = y * number;
        z = z * number;
        return *this;
    };

    Vector3 operator*(const Vector3& vec) const {
        return { x * vec.x, y * vec.y, z * vec.z };
    }

    Vector3 operator/(float number) const {
        if (number != 0.f) {
            return { x / number, y / number, z / number };
        }
        throw ("Divide by zero exception");
    };

    Vector3& operator/=(float number) {
        if (number != 0.f) {
            x = x / number;
            y = y / number;
            z = z / number;
            return *this;
        }
        throw ("Divide by zero exception");
    };

    float& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw ("Vector3 index out of range");
    }

    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw ("Vector3 index out of range");
    }

    Vector3 abs() const {
        return { std::abs(x), std::abs(y), std::abs(z) };
    }

    float lenght() const {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    };

    Vector3 normalize() const {
        if (lenght() != 0.f) {
            return { x / lenght(), y / lenght(), z / lenght() };
        }
        return *this;
    };

    float dotProduct(const Vector3& other) const {
        return (x * other.x) + (y * other.y) + (z * other.z);
    };

    Vector3 crossProduct(const Vector3& other) const {
        return { y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - other.x * y };
    };

    bool operator==(const Vector3& other) const {
        return (x == other.x && y == other.y && z == other.z);
    };

    bool operator!=(const Vector3& other) const {
        return !(x == other.x && y == other.y && z == other.z);
    };

    friend std::ostream& operator<<(std::ostream& os, Vector3 vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
        return os;
    };
};

class Vector4 {
public:
    float x = 0.f, y = 0.f, z = 0.f, w = 0.f;

    Vector4() = default;

    explicit Vector4(float number) : x(number), y(number), z(number), w(number) {};

    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

    Vector4(const Vector2& other) : x(other.x), y(other.y), z(0.f), w(0.f) {};

    Vector4(const Vector3& other) : x(other.x), y(other.y), z(other.z), w(0.f) {};

    Vector4(const Vector4& other) = default;

    Vector4& operator=(const Vector4& other) {
        if (this == &other) {
            return *this;
        }
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    Vector4 operator+(const Vector4& other) const {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    };

    Vector4& operator+=(const Vector4& other) {
        *this = *this + other;
        return *this;
    };

    Vector4 operator-(const Vector4& other) const {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    };

    Vector4& operator-=(const Vector4& other) {
        *this = *this - other;
        return *this;
    };

    Vector4 operator-() const {
        return { -x, -y, -z, -w};
    };

    Vector4 operator*(float number) const {
        return { x * number, y * number, z * number, w * number };
    };

    Vector4& operator*=(float number) {
        x = x * number;
        y = y * number;
        z = z * number;
        w = w * number;
        return *this;
    };

    Vector4 operator/(float number) const {
        if (number != 0) {
            return { x / number, y / number, z / number, w / number };
        }
        throw ("Divide by zero exception");
    };

    Vector4& operator/=(float number) {
        if (number != 0) {
            x = x / number;
            y = y / number;
            z = z / number;
            w = w / number;
            return *this;
        }
        throw ("Divide by zero exception");
    };

    float& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return x;
        if (index == 3) return y;
        throw ("Vector2 index out of range");
    }

    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return x;
        if (index == 3) return y;
        throw ("Vector2 index out of range");
    };

    Vector4 abs() const {
        return { std::abs(x), std::abs(y), std::abs(z), std::abs(w) };
    }

    float lenght() const {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
    };

    Vector4 normalize() const {
        if (lenght() != 0) {
            return { x / lenght(), y / lenght(), z / lenght(), w / lenght() };
        }
        return *this;
    };

    float dotProduct(const Vector4& other) const {
        return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
    };

    bool operator==(const Vector4& other) const {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
    };

    bool operator!=(const Vector4& other) const {
        return !(x == other.x && y == other.y && z == other.z && w == other.w);
    };

    friend std::ostream& operator<<(std::ostream& os, Vector4 vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")" << std::endl;
        return os;
    };
};
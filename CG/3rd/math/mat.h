#pragma once

#include "math.h"


class Matrix2 {
public:
    float matrix[2][2]{};

    Matrix2() = default;

    explicit Matrix2(float number) : matrix{ {number, 0.f},
                                          {0.f, number} } {}

    Matrix2(float a, float b, float c, float d) : matrix{ {a, c}, 
                                                       {b, d} } {};

    Matrix2(const Vector2& first, const Vector2& second) : matrix{ {first.x, second.x},
                                                          {first.y, second.y} } {};

    Matrix2(const Matrix2& other) = default;

    Matrix2 operator+(const Matrix2& other) const {
        return { matrix[0][0] + other.matrix[0][0], matrix[0][1] + other.matrix[0][1],
                 matrix[1][0] + other.matrix[1][0], matrix[1][1] + other.matrix[1][1] };
    };

    Matrix2& operator+=(const Matrix2& other) {
        *this = *this + other;
        return *this;
    };

    Matrix2 operator-(const Matrix2& other) const {
        return { matrix[0][0] - other.matrix[0][0], matrix[0][1] - other.matrix[0][1],
                 matrix[1][0] - other.matrix[1][0], matrix[1][1] - other.matrix[1][1] };
    };

    Matrix2& operator-=(const Matrix2& other) {
        *this = *this - other;
        return *this;
    };

    Matrix2 operator*(const Matrix2& other) const {
        return { matrix[0][0] * other.matrix[0][0] + matrix[0][1] * other.matrix[1][0], matrix[0][0] * other.matrix[0][1] + matrix[0][1] * other.matrix[1][1],
                 matrix[1][0] * other.matrix[0][0] + matrix[1][1] * other.matrix[1][0], matrix[1][0] * other.matrix[0][1] + matrix[1][1] * other.matrix[1][1] };
    };

    Matrix2& operator*=(const Matrix2& other) {
        *this = *this * other;
        return *this;
    };

    Matrix2 operator*(float number) const {
        return { matrix[0][0] * number, matrix[0][1] * number,
                 matrix[1][0] * number, matrix[1][1] * number };
    };

    Matrix2& operator*=(float number) {
        *this = *this * number;
        return *this;
    };

    Matrix2 operator/(float number) const {
        if (number != 0.f) {
            return { matrix[0][0] / number, matrix[0][1] / number,
                     matrix[1][0] / number, matrix[1][1] / number };
        }
        throw ("Divide by zero exception");
    };

    Matrix2& operator/=(float number) {
        if (number != 0.f) {
            *this = *this / number;
            return *this;
        }
        throw ("Divide by zero exception");
    };

    Matrix2 operator+(float number) const {
        return { matrix[0][0] + number,  matrix[0][1] + number,
                 matrix[1][0] + number,  matrix[1][1] + number };
    };

    Matrix2& operator+=(float number) {
        *this = *this + number;
        return *this;
    };

    Matrix2 operator-(float number) const {
        return { matrix[0][0] - number, matrix[0][1] - number,
                 matrix[1][0] - number, matrix[1][1] - number };
    };

    Matrix2& operator-=(float number) {
        *this = *this - number;
        return *this;
    };

    Vector2 operator*(const Vector2& other) const {
        return { matrix[0][0] * other.x + matrix[0][1] * other.y,
                 matrix[1][0] * other.x + matrix[1][1] * other.y };
    };

    static Matrix2 identity() {
        return Matrix2(1.f);
    };

    float det() {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    Matrix2 reverse() {
        float divideDet = 1.f / det();

        return { matrix[1][1] * divideDet, -matrix[0][1] * divideDet,
                -matrix[1][0] * divideDet, +matrix[0][0] * divideDet };
    };

    Matrix2 transpose() {
        return Matrix2(Row(0), Row(1));
    };

    Vector2 Row(int index) {
        if (index >= 0 && index < 2) {
            return { matrix[index][0], matrix[index][1] };
        }
        return Vector2(0.f);
    }

    Vector2 Column(int index) {
        if (index >= 0 && index < 2) {
            float res[2];
            for (int i = 0; i < 2; i++) {
                res[i] = matrix[i][index];
            }
            return { res[0], res[1] };
        }
        return Vector2(0.f);
    };

    float* operator[](int row) {
        if (row == 0) return matrix[row];
        if (row == 1) return matrix[row];
        throw ("Matrix2 row out of range");
    }

    bool operator==(const Matrix2& other) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (matrix[i][j] != other.matrix[i][j])
                    return false;
        return true;
    };

    bool operator!=(const Matrix2& other) {
        return matrix != other.matrix;
    };

    friend std::ostream& operator<<(std::ostream& os, Matrix2 matrix) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                os << matrix[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }
};

class Matrix3 {
public:
    float matrix[3][3]{};

    Matrix3() = default;

    explicit Matrix3(float number) :
        matrix{ {number, 0.f,      0.f},
                {0.f,      number, 0.f},
                {0.f,      0.f, number} } {};


    Matrix3(float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i) :
        matrix{ {a, d, g},
                {b, e, h},
                {c, f, i} } {}

    Matrix3(const Vector3& first, const Vector3& second, const Vector3& third) {
        matrix[0][0] = first.x;
        matrix[1][0] = first.y;
        matrix[2][0] = first.z;

        matrix[0][1] = second.x;
        matrix[1][1] = second.y;
        matrix[2][1] = second.z;

        matrix[0][2] = third.x;
        matrix[1][2] = third.y;
        matrix[2][2] = third.z;
    }

    Matrix3(const Matrix3& other) = default;

    Matrix3 operator+(const Matrix3& other) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                result.matrix[i][j] = matrix[j][i] + other.matrix[j][i];
        return result;
    };

    Matrix3& operator+=(const Matrix3& other) {
        *this = *this + other;
        return *this;
    };

    Matrix3 operator-(const Matrix3& other) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                result.matrix[i][j] = matrix[j][i] - other.matrix[j][i];
        return result;
    }

    Matrix3& operator-=(const Matrix3& other) {
        *this = *this - other;
        return *this;
    }

    Matrix3 operator*(const Matrix3& other) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                result.matrix[j][i] = 0;
                for (int k = 0; k < 3; k++)
                    result.matrix[j][i] += matrix[i][k] * other.matrix[k][j];
            }
        return result;
    }

    Matrix3& operator*=(const Matrix3& other) {
        *this = *this * other;
        return *this;
    }

    Matrix3 operator*(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                result.matrix[i][j] = matrix[j][i] * number;
        return result;
    }

    Matrix3& operator*=(float number) {
        *this = *this * number;
        return *this;
    }

    Matrix3 operator/(float number) const {
        if (number != 0.f) {
            Matrix3 result;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    result.matrix[i][j] = matrix[j][i] / number;
            return result;
        }
        throw ("Divide by zero exception");
    }

    Matrix3& operator/=(float number) {
        if (number != 0.f) {
            *this = *this / number;
            return *this;
        }
        throw ("Divide by zero exception");
    }

    Matrix3 operator+(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                result.matrix[i][j] = matrix[j][i] + number;
        return result;
    }

    Matrix3& operator+=(float number) {
        *this = *this + number;
        return *this;
    }

    Matrix3 operator-(float number) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                result.matrix[i][j] = matrix[j][i] - number;
        return result;
    }

    Matrix3& operator-=(float number) {
        *this = *this - number;
        return *this;
    }

    Vector3 operator*(const Vector3& vec) const {
        Vector3 result;
        result.x = matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z;
        result.y = matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z;
        result.z = matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z;
        return result;
    }

    static Matrix3 identity() {
        return Matrix3(1.f);
    };

    float det() {

        Matrix2 A = getSubMatrix(0, 0);
        Matrix2 B = getSubMatrix(1, 0);
        Matrix2 C = getSubMatrix(2, 0);

        return matrix[0][0] * A.det() - matrix[1][0] * B.det() + matrix[2][0] * C.det();
    }

    Matrix3 reverse() {
        Matrix3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                Matrix2 subMatrix = getSubMatrix(i, j);
                float sign = (i + j) % 2 == 0 ? 1 : -1;
                float cofactor = subMatrix.det() * sign;
                result[j][i] = cofactor / det();
            }
        }
        return result.transpose();
    };

    Matrix2 getSubMatrix(int exclude_row, int exclude_col) const {
        Matrix2 subMatrix;
        int row = 0, col = 0;
        for (int i = 0; i < 3; ++i) {
            if (i == row) continue;
            for (int j = 0; j < 3; ++j) {
                if (j == col) continue;
                subMatrix[row][col] = matrix[i][j];
                ++col;
            }
            ++row;
            col = 0;
        }
        return subMatrix;
    }

    Matrix3 transpose() {
        return Matrix3(Row(0), Row(1), Row(2));
    };

    Vector3 Row(int index) {
        if (index >= 0 && index < 3) {
            return { matrix[index][0], matrix[index][1], matrix[index][2] };
        }
        return Vector3(0.f);
    };

    Vector3 Column(int index) {
        if (index >= 0 && index < 3) {
            float res[3]{};
            for (int i = 0; i < 3; i++) {
                res[i] = matrix[i][index];
            }
            return { res[0], res[1], res[2] };
        }
        return Vector3(0.f);
    };

    float* operator[](int row) {
        if (row == 0) return matrix[row];
        if (row == 1) return matrix[row];
        if (row == 2) return matrix[row];
        throw ("Matrix3 row out of range");
    }

    bool operator==(const Matrix3& other) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (matrix[i][j] != other.matrix[i][j])
                    return false;
        return true;
    };

    bool operator!=(const Matrix3& other) {
        return matrix != other.matrix;
    };

    friend std::ostream& operator<<(std::ostream& os, Matrix3& matrix) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                os << matrix[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }
};


class Matrix4 {
public:
    float matrix[4][4]{};
    Matrix4() = default;

    explicit Matrix4(float number) : matrix{ {number, 0.f,    0.f,    0.f},
                                             {0.f,    number, 0.f,    0.f},
                                             {0.f,    0.f,    number, 0.f},
                                             {0.f,    0.f,    0.f,    number} } {};

    Matrix4(float a, float b, float c, float d,
            float e, float f, float g, float h,
            float i, float j, float k, float l,
            float m, float n, float o, float r) : matrix{ {a, b, c, d},
                                                          {e, f, g, h},
                                                          {i, j, k, l},
                                                          {m, n, o, r} } {};


    Matrix4(const Vector4& first, const Vector4& second, const Vector4& third, const Vector4& four)
        : matrix{ {first.x,  first.y,  first.z,  first.w},
                  {second.x, second.y, second.z, second.w},
                  {third.x,  third.y,  third.z,  third.w},
                  {four.x,   four.y,   four.z,   four.w} } {}

    Matrix4(const Matrix4& other) = default;

    Matrix4 operator+(const Matrix4& other) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i][j] = matrix[i][j] + other.matrix[i][j];
        return result;
    }

    Matrix4& operator+=(const Matrix4& other) {
        *this = *this + other;
        return *this;
    }

    Matrix4 operator-(const Matrix4& other) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i][j] = matrix[i][j] - other.matrix[i][j];
        return result;
    }

    Matrix4& operator-=(const Matrix4& other) {
        *this = *this - other;
        return *this;
    }

    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                result[i][j] = 0;
                for (int k = 0; k < 4; k++)
                    result[i][j] += other.matrix[i][k] * matrix[k][j];
            }
        return result;
    }

    Matrix4& operator*=(const Matrix4& other) {
        *this = *this * other;
        return *this;
    }

    Matrix4 operator*(float number) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i][j] = matrix[i][j] * number;
        return result;
    }

    Matrix4& operator*=(float number) {
        *this = *this * number;
        return *this;
    }

    Matrix4 operator/(float number) const {
        if (number != 0.f) {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    result[i][j] = matrix[i][j] / number;
            return result;
        }
        throw ("Divide by zero exception");
    }

    Matrix4& operator/=(float number) {
        if (number != 0.f) {
            *this = *this / number;
            return *this;
        }
        throw ("Divide by zero exception");
    }

    Matrix4 operator+(float number) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i][j] = matrix[i][j] + number;
        return result;
    }

    Matrix4& operator+=(float number) {
        *this = *this + number;
        return *this;
    }

    Matrix4 operator-(float number) const {
        Matrix4 result;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                result[i][j] = matrix[i][j] - number;
        return result;
    }

    Matrix4& operator-=(float number) {
        *this = *this - number;
        return *this;
    }

    Matrix4& operator=(const Vector3& vec) {
        matrix[0][0] = vec.x;
        matrix[1][0] = vec.y;
        matrix[2][0] = vec.z;
        return *this;
    }

    Vector4 operator*(const Vector4& vec) const {
        Vector4 result;
        result.x = matrix[0][0] * vec.x + matrix[1][0] * vec.y + matrix[2][0] * vec.z + matrix[3][0] * vec.w;
        result.y = matrix[0][1] * vec.x + matrix[1][1] * vec.y + matrix[2][1] * vec.z + matrix[3][1] * vec.w;
        result.z = matrix[0][2] * vec.x + matrix[1][2] * vec.y + matrix[2][2] * vec.z + matrix[3][2] * vec.w;
        result.w = matrix[0][3] * vec.x + matrix[1][3] * vec.y + matrix[2][3] * vec.z + matrix[3][3] * vec.w;
        return result;
    }

    static Matrix4 identity() {
        return Matrix4(1.f);
    };

    float det() {
        Matrix3 A = getSubMatrix(0, 0);
        Matrix3 B = getSubMatrix(1, 0);
        Matrix3 C = getSubMatrix(2, 0);
        Matrix3 D = getSubMatrix(3, 0);

        return matrix[0][0] * A.det() - matrix[1][0] * B.det() + matrix[2][0] * C.det() - matrix[3][0] * D.det();
    }

    Matrix4 reverse() {
        Matrix4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                Matrix3 subMatrix = getSubMatrix(i, j);
                float sign = (i + j) % 2 == 0 ? 1 : -1;
                float cofactor = subMatrix.det() * sign;
                result[j][i] = cofactor / det();
            }
        }
        return result.transpose();
    }

    Matrix3 getSubMatrix(int exclude_row, int exclude_col) const {
        Matrix3 subMatrix;
        int row = 0, col = 0;
        for (int i = 0; i < 4; ++i) {
            if (i == exclude_row) continue;
            for (int j = 0; j < 4; ++j) {
                if (j == exclude_col) continue;
                subMatrix[row][col] = matrix[i][j];
                ++col;
            }
            ++row;
            col = 0;
        }
        return subMatrix;
    }

    Matrix4 transpose() {
        return Matrix4(Row(0), Row(1), Row(2), Row(3));
    };

    Vector4 Row(int index) {
        if (index >= 0 && index < 4) {
            float result[4]{};
            for (int i = 0; i < 4; i++) {
                result[i] = matrix[i][index];
            }
            return { result[0], result[1], result[2], result[3] };
        }
        return Vector4(0.f);
    };

    Vector4 Column(int index) {
        if (index >= 0 && index < 4) {
            Vector4 result(matrix[index][0], matrix[index][1], matrix[index][2], matrix[index][3]);
            return result;
        }
        return Vector4(0.f);
    };

    float* operator[](int row) {
        if (row == 0) return matrix[row];
        if (row == 1) return matrix[row];
        if (row == 2) return matrix[row];
        if (row == 3) return matrix[row];
        throw ("Matrix4 row out of range");
    }

    bool operator==(const Matrix4& other) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (matrix[i][j] != other.matrix[i][j])
                    return false;
        return true;
    };

    bool operator!=(const Matrix4& other) {
        return matrix != other.matrix;
    };

    friend std::ostream& operator<<(std::ostream& os, Matrix4& matrix) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                os << matrix[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }

};
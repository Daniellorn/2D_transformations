#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <qDebug>

#include "vec3.h"

namespace math {

    class mat3
    {
    public:

        mat3();
        mat3(float value);

        float& operator()(int row, int col);
        const float& operator()(int row, int col) const;

        mat3 operator*(const mat3& other);
        vec3 operator*(const vec3& vector);
        mat3& operator=(const mat3& other) = default;

        static mat3 translation(const mat3& matrix, const vec3& vector);
        static mat3 rotation(const mat3& matrix, float radian);
        static mat3 scaleX(const mat3& matrix, float x);
        static mat3 scaleY(const mat3& matrix, float y);
        static mat3 scaleXY(const mat3& matrix, const vec3& vector);
        static mat3 shearingX(const mat3& matrix, float value);
        static mat3 shearingY(const mat3& matrix, float value);


        int getColNum() const;
        int getRowNum() const;


        void print() const
        {
            for (auto& element: m_matrix)
            {
                qDebug() << element << " ";
            }
        }

    private:
        std::array<float, 9> m_matrix;
        int m_colnum;
        int m_rownum;

    };
}


#endif // MATRIX_H

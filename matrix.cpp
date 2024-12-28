#include "matrix.h"

#include <cmath>

namespace math {

    mat3::mat3():
        m_colnum(3), m_rownum(3)
    {
        m_matrix.fill(0.0f);
    }

    mat3::mat3(float value):
        m_colnum(3), m_rownum(3)
    {
        m_matrix.fill(0.0f);

        for (int i = 0; i < 3; i++)
        {
            m_matrix[3 * i + i] = value;
        }
    }

    float& mat3::operator()(int row, int col)
    {
        return m_matrix[row * m_colnum + col];
    }

    mat3 mat3::operator*(const mat3 &other)
    {
        mat3 result;

        for (int i = 0; i < m_rownum; i++)
        {
            for (int j = 0; j < m_colnum; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    result(i, j) += (*this)(i,k) * other(k, j);
                }
            }
        }

        return result;
    }


    vec3 mat3::operator*(const vec3& vector)
    {
        vec3 result;

        result.x = (*this)(0,0) * vector.x + (*this)(0,1) * vector.y + (*this)(0,2) * vector.z;
        result.y = (*this)(1,0) * vector.x + (*this)(1,1) * vector.y + (*this)(1,2) * vector.z;
        result.z = (*this)(2,0) * vector.x + (*this)(2,1) * vector.y + (*this)(2,2) * vector.z;

        return result;
    }

    const float& mat3::operator()(int row, int col) const
    {
        return m_matrix[row * m_colnum + col];
    }

    mat3 mat3::translation(const mat3& matrix, const vec3& vector)
    {
        mat3 result = matrix;

        result(0,2) = vector.x;
        result(1,2) = vector.y;
        result(2,2) = 1.0f;

        return result;
    }

    mat3 mat3::rotation(const mat3 &matrix, float radian)
    {
        mat3 result = matrix;

        result(0,0) = std::cos(radian);
        result(0,1) = -std::sin(radian);
        result(1,0) = std::sin(radian);
        result(1,1) = std::cos(radian);

        return result;
    }

    mat3 mat3::scaleX(const mat3 &matrix, float x)
    {
        mat3 result = matrix;

        result(0,0) = x;

        return result;
    }

    mat3 mat3::scaleY(const mat3 &matrix, float y)
    {
        mat3 result = matrix;

        result(1,1) = y;

        return result;
    }

    mat3 mat3::scaleXY(const mat3 &matrix, const vec3 &vector)
    {
        mat3 result = matrix;

        result(0,0) = vector.x;
        result(1,1) = vector.y;
        result(2,2) = 1;

        return result;
    }

    mat3 mat3::shearingX(const mat3 &matrix, float value)
    {
        mat3 result = matrix;

        result(0,1) = value;

        return result;
    }

    mat3 mat3::shearingY(const mat3 &matrix, float value)
    {
        mat3 result = matrix;

        result(1,0) = value;

        return result;
    }

    int mat3::getColNum() const
    {
        return m_colnum;
    }

    int mat3::getRowNum() const
    {
        return m_rownum;
    }


}

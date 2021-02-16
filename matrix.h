#pragma once

#include <vector>
#include <type_traits>
#include <string>
#include <fstream>

template <class T>
class Matrix
{
public:
    Matrix(size_t m = 0, size_t n = 0, T defValue = T());

    decltype(auto) operator()(size_t m, size_t n)
    {
        return data[m][n];
    }

    Matrix<T> operator-(Matrix<T> &x);
    Matrix<T> operator*(double x);
    void operator-=(Matrix<T> &x);
    void operator*=(double x);

    std::vector<T> toVector();

    std::pair<size_t, size_t> dim();

    template<typename std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
    void printToFile(std::string const & path = "Matrix.txt")
    {
        std::ofstream out(path);
        for (auto const & x : data)
        {
            for (auto const & j : x)
            {
                out << j << "\t";
            }

            out << std::endl;
        }

        out.close();
    }

    double scalarProduct(Matrix<T> & b);

private:
    std::vector<std::vector<T>> data;
    std::size_t m, n;
};

template <class T>
Matrix<T>::Matrix(size_t m, size_t n, T defValue) : m(m), n(n)
{
    for (size_t i = 0; i < m; i++)
    {
        data.push_back(std::vector<T>());

        for (size_t j = 0; j < n; j++)
            data[i].push_back(defValue);
    }
}

template <class T>
std::pair<size_t, size_t> Matrix<T>::dim()
{
    return std::make_pair(m,n);
}

template <class T>
double Matrix<T>::scalarProduct(Matrix<T> & b)
{
    double scalar = 0;
    assert(this->m == 1 && b.m == 1);
    assert(this->n == b.n);

    for (size_t i = 0; i < n; i++)
        scalar += data[0][i] * b.data[0][i];

    return scalar;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &b)
{
    assert(this->m == b.m && this->n == b.n);
    Matrix<T> tmp(*this);

    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            tmp.data[i][j] -= b.data[i][j];

    return tmp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(double x)
{
    Matrix<T> tmp(*this);

    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            tmp(i,j) *= x;

    return tmp;
}

template <class T>
void Matrix<T>::operator-=(Matrix<T> &x)
{
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            data[i][j] -= x.data[i][j];
}

template <class T>
void Matrix<T>::operator*=(double x)
{
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            data[i][j] *= x;
}

template <class T>
std::vector<T> Matrix<T>::toVector()
{
    std::vector<T> tmp;
    size_t indx = 0;
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        {
            tmp.push_back(data[i][j]);
        }
    return tmp;
}

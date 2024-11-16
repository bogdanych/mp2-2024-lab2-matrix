// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include <iostream>
#include <cassert>

using namespace std;
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector size is too large");
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw length_error("Vector size is too large");
        }
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        sz = 0;
        delete[] pMem;
        pMem = nullptr;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (&v == this) {
            return *this;
        }
        if (sz != v.sz) {
            sz = v.sz;
            T* buf = new T[sz];
            delete[] pMem;
            pMem = buf;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz) {
            throw out_of_range("index out of range");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz) {
            throw out_of_range("index out of range");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;

        T eps = numeric_limits<T>::epsilon();

        for (int i = 0; i < sz; i++) {
            if (abs(pMem[i] - v[i]) > eps) {
                return 0;
            }
        }
        return 1;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector<T> operator+(T val)
    {
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector<T> operator-(T val)
    {
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] - val;
        }
        return res;
    }

    TDynamicVector<T> operator*(T val)
    {
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector<T> operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw length_error("different vector sizes");
        }
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + v[i];
        }
        return res;
    }
    TDynamicVector<T> operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw length_error("different vector sizes");
        }
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - v[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v)  //DONE
    {
        if (sz != v.sz) {
            throw length_error("different vector sizes");
        }
        T res = static_cast<T>(0);
        for (size_t i = 0; i < sz; i++) {
            res += pMem[i] * v[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz > MAX_MATRIX_SIZE) throw length_error("bad matrix size");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;
    using TDynamicVector<TDynamicVector<T>>::size;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != m[i])
                return 0;
        return 1;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) {
            throw length_error("bad vector size");
        }
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] * v;
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix<T> operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw length_error("different matrix sizes");
        }
        TDynamicMatrix<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + m[i];
        }
        return res;
    }
    TDynamicMatrix<T> operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw length_error("different matrix sizes");
        }
        TDynamicMatrix<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] - m[i];
        }
        return res;
    }
    TDynamicMatrix<T> operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw length_error("different matrix sizes");
        }
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                for (int k = 0; k < sz; k++) {
                    res[i][j] += pMem[i][k] * m[k][j];
                }
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v[i] << std::endl;
        }

        return ostr;
    }
};

#endif

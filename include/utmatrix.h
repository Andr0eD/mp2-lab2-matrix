#pragma once

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
    ValType* pVector;
    int Size;       // ������ �������
    int StartIndex; // ������ ������� �������� �������
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // ����������� �����������
    ~TVector();
    int GetSize() { return Size; } // ������ �������
    int GetStartIndex() { return StartIndex; } // ������ ������� ��������
    ValType& operator[](int pos);             // ������
    bool operator==(const TVector& v) const;  // ���������
    bool operator!=(const TVector& v) const;  // ���������
    TVector& operator=(const TVector& v);     // ������������

    // ��������� ��������
    TVector  operator+(const ValType& val);   // ��������� ������
    TVector  operator-(const ValType& val);   // ������� ������
    TVector  operator*(const ValType& val);   // �������� �� ������

    // ��������� ��������
    TVector  operator+(const TVector& v);     // ��������
    TVector  operator-(const TVector& v);     // ���������
    ValType  operator*(const TVector& v);     // ��������� ������������

    // ����-�����
    friend istream& operator>>(istream& in, TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0 || si < 0 || s < si || si > MAX_VECTOR_SIZE || s > MAX_MATRIX_SIZE)
    {
        throw "Error - out of range";
    }
    Size = s - si;
    StartIndex = si;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
    {
        pVector[Size] = 0;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType>& v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
    {
        pVector[Size] = v.pVector[Size]
    }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos < StartIndex || pos >= Size + StartIndex)
    {
        throw "Error - out of range";
    }
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (StartIndex != v.StartIndex)
    {
        return false;
    }
    if (Size != v.Size)
    {
        return false;
    }
    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != v.pVector[i])
        {
            return false;
        }
    }
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector& v) const
{
    if (Size != v.Size)
    {
        return true;
    }
    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != v.pVector[i])
        {
            return true;
        }
    }
    return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (Size != v.Size)
    {
        Size = v.Size;
    }
    if (*this == v)
    {
        return *this;
    }
    
    delete[] pVector;

    pVector = new ValType[Size];
    StartIndex = v.StartIndex;

    for (int i = 0; i < Size; i++)
    {
        pVector[i] = v.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    TVector<ValType> temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] += val;
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    TVector<ValType> temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] -= val;
    }
    return temp;

} /*-------------------------------------------------------------------------*/

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    TVector<ValType> temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] *= val;
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
    TVector<ValType> temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] = temp.pVector[i] + v.pVector[i];
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
    TVector<ValType> temp(*this);
    for (int i = 0; i < Size; i++)
    {
        temp.pVector[i] = temp.pVector[i] - v.pVector[i];
    }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    ValType res = 0;
    for (int i = 0; i < Size; i++)
    {
        res += v.pVector[i] * pVector[i];
    }
    return res;
} /*-------------------------------------------------------------------------*/


// ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // �����������
    TMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
    bool operator==(const TMatrix& mt) const;      // ���������
    bool operator!=(const TMatrix& mt) const;      // ���������
    TMatrix& operator= (const TMatrix& mt);        // ������������
    TMatrix  operator+ (const TMatrix& mt);        // ��������
    TMatrix  operator- (const TMatrix& mt);        // ���������

    // ���� / �����
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
    for (int i = 0; i < s; i++)
    {
        TVector<ValType> temp(s, i);
        pVector[i] = temp;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
    TVector<TVector<ValType> >(mt) {
}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
    TVector<TVector<ValType> >(mt) {

}

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType>> :: operator ==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType>> :: operator !=(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    if (*this == mt)
    {
        return *this;
    }
    if (Size != mt.Size)
    {
        Size = mt.Size;
    }
    
    delete[] pVector;

    pVector = new TVector<ValType>[Size];
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = mt.pVector[i];
    }
    return *this;

} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
    return TVector<TVector<ValType>> :: operator+(mt);

} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{

    return TVector<TVector<ValType>> :: operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector �3 �2 �4 �6
// TMatrix �2 �2 �3 �3
#endif
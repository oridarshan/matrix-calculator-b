#pragma once

/*
    Description
*/

#include <iostream>
#include<vector>

namespace zich
{
    class Matrix
    {
    private:
        std::vector<double> values;
        int col;
        int row;
    public:
        Matrix(std::vector<double> values, int col, int row);
        ~Matrix();
        Matrix operator -();
        Matrix operator +(const Matrix &mat2);
        Matrix operator -(const Matrix &mat2);
        Matrix& operator -=(const Matrix &mat2);
        Matrix& operator +=(const Matrix &mat2);

        Matrix operator *(int n);
        Matrix& operator *=(int n);

        Matrix friend operator *(int n, const Matrix &mat);

        friend bool operator==(const Matrix& mat1, const Matrix& mat2);

        friend std::ostream& operator<< (std::ostream& output, const Matrix& c);
        friend std::istream& operator>> (std::istream& input , Matrix& c);
        
    };
    
    
    
} // namespace zich

#include <vector>
#include <string>
#include "Matrix.hpp"
using namespace zich;

Matrix::Matrix(std::vector<double> values, int row, int col)
{
    if(values.size() != col*row){
        throw ("ERROR! values vector not compatible with required shape");
    }
    if(col <= 0 || row <= 0){
        throw("ERROR! dimentions must be natural numbers");
    }
    this->values = values;
    this->row = row;
    this->col = col;
}
Matrix::~Matrix(){}

std::vector<double> Matrix::operator[](int n){
    return std::vector<double>{values.begin()+col*n, values.begin()+col*(n+1)};
}

double sum_vector(const std::vector<double> vec){
    double sum = 0;
    for(const double& num : vec){
        sum+=num;
    }
    return sum;
}

void zich::check_dimentions(const Matrix &mat1, const Matrix &mat2){
    if(mat1.col != mat2.col || mat1.row != mat2.row){
        throw("Illegal function, dimentions not equal");
    }
}

Matrix Matrix::operator -() const
{
    Matrix copy = *this;
    for(double &val: copy.values){
        val *= -1;
    }
    return copy;
}
Matrix Matrix::operator +(){return *this;}

Matrix Matrix::operator +(const Matrix &mat2)
{
    check_dimentions(*this, mat2);
    //create copy of values
    std::vector<double> arr = values;
    for(size_t i=0; i<row*col; i++){
        arr[i] += mat2.values[i];
    }
    Matrix res{arr, col, row};
    return res;
}

Matrix Matrix::operator -(const Matrix &mat2)
{
    Matrix mat3 = (-mat2);
    return *this + mat3;
}

Matrix Matrix::operator *(int n)
{
    Matrix copy{values, row, col};
    for(size_t i=0; i<row*col; i++){
        copy.values[i] *= n;
    }
    return copy;
}
Matrix& Matrix::operator -=(const Matrix &mat2)
{
    *this = *this - mat2;
    return *this;
}
Matrix& Matrix::operator +=(const Matrix &mat2)
{
    *this = *this + mat2;
    return *this;
}
Matrix& Matrix::operator *=(int n)
{
    *this = *this * n;
    return *this;
}

Matrix Matrix::operator *(Matrix other){
    if(col != other.row){
        throw("Illegal function, dimentions does't fit");
    }
    int new_row = row;
    int new_col = other.col;
    std::vector<double> arr((size_t)(new_row*new_col),0);
    for (size_t i = 0; i < new_row; i++)
    {
        for (size_t j = 0; j < new_col; j++)
        {
            double val = 0;
            for (size_t k = 0; k < col; k++)
            {
                val += values[((size_t)col*i) + k] * other.values[((size_t)other.col*k)+j];
            }
            arr[((size_t)new_col*i)+j] = val;
        }   
    }
    Matrix res{arr, row, other.col};
    return res;
}
Matrix& Matrix::operator *=(Matrix other)
{
    *this = *this * other;
    return *this;
}
//prefix --mat
Matrix& Matrix::operator --()
{
    for(double &val: values){
        val--;
    }
    return *this;
}

Matrix& Matrix::operator ++()
{
    for(double &val: values){
        val++;
    }
    return *this;
}
//postfix mat--
Matrix Matrix::operator --(int)
{
    Matrix copy = *this;
    for(double &val: values){
        val--;
    }
    return copy;
}
Matrix Matrix::operator ++(int)
{
    Matrix copy = *this;
    for(double &val: values){
        val++;
    }
    return copy;
}

Matrix zich::operator *(int n, const Matrix &mat)
{
    Matrix copy = mat;
    for(double &val: copy.values){
        val *= n;
    }
    return mat;
}

bool zich::operator==(const Matrix& mat1, const Matrix& mat2)
{
    check_dimentions(mat1, mat2);
    for (size_t i = 0; i < mat1.col * mat1.row; i++)
    {
        if(mat1.values[i] != mat2.values[i]){
            return false;
        }
    }
    return true;
}
bool zich::operator!=(const Matrix& mat1, const Matrix& mat2)
{
    return !(mat1 == mat2);
}
bool zich::operator<=(const Matrix& mat1, const Matrix& mat2)
{
    check_dimentions(mat1,mat2);
    return sum_vector(mat1.values) <= sum_vector(mat2.values);
}
bool zich::operator>=(const Matrix& mat1, const Matrix& mat2)
{
    check_dimentions(mat1,mat2);
    return sum_vector(mat1.values) >= sum_vector(mat2.values);
}
bool zich::operator<(const Matrix& mat1, const Matrix& mat2)
{
    check_dimentions(mat1,mat2);
    return sum_vector(mat1.values) < sum_vector(mat2.values);
}
bool zich::operator>(const Matrix& mat1, const Matrix& mat2)
{
    check_dimentions(mat1,mat2);
    return sum_vector(mat1.values) > sum_vector(mat2.values);
}


std::ostream& zich::operator<< (std::ostream& output, const Matrix& m){
    std::string res;
    for (size_t i = 0; i < m.row; i++)
    {
        res += "[";
        for (size_t j = 0; j < m.col; j++)
        {
            res += std::to_string(m.values[(size_t)m.col*i+j]);
            res += " ";
        }
        res += "]\n";
    }
    
    return output << res;
} 
std::istream& zich::operator>> (std::istream& input , Matrix& m){return input;}
        
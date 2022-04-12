#include <vector>
#include "Matrix.hpp"
using namespace zich;

Matrix::Matrix(std::vector<double> values, int col, int row)
{
    if(values.size() != col*row){
        throw ("ERROR! values vector not compatible with required shape");
    }
    this->values = values;
    this->col = col;
    this->row = row;
}
Matrix::~Matrix(){}

Matrix Matrix::operator -(){return *this;}
Matrix Matrix::operator +(const Matrix &mat2){return *this;}
Matrix Matrix::operator -(const Matrix &mat2){return *this;}
Matrix& Matrix::operator -=(const Matrix &mat2){return *this;}
Matrix& Matrix::operator +=(const Matrix &mat2){return *this;}

Matrix Matrix::operator *(int n){return *this;}
Matrix& Matrix::operator *=(int n){return *this;}

Matrix zich::operator *(int n, const Matrix &mat){return mat;}

bool zich::operator==(const Matrix& mat1, const Matrix& mat2){
    return mat1.values == mat2.values;
}


std::ostream& zich::operator<< (std::ostream& output, const Matrix& c){return output;} 
std::istream& zich::operator>> (std::istream& input , Matrix& c){return input;}
        
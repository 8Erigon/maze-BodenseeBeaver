#ifndef matrix_h
#define matrix_h

#include "vektors.h"

template <typename type, int lenght, int width> class matrix{
    vektors<type, lenght> colums[width];

    matrix<type, lenght, width> operator*(const int &other){ //function for when you do "matrix * int"
        matrix<type, lenght, width> result;
        for(int i; i<width; i++){
            result.colums[i] = colums[i] * other;
        }
        return result;
    }
    matrix<type, lenght, width> operator/(const int &other){ //function for when you do "matrix / int"
        matrix<type, lenght, width> result;
        for(int i; i<width; i++){
            result.colums[i] = colums[i] / other;
        }
        return result;
    }

    vektors<type, lenght> operator*(const vektors &other){ //function for when you do "matrix * vektors"
        vektors<type, lenght> result;
        matrix<double, lenght, width> preResult;
        for(int i = 0; i < lenght; i++){
            preResult.colums = this->colums[i] * other.content[i]; //Multiplies each vektor element with thier Colum in the matrix
            for(int j = 0; j < lenght; j++){
                result.content[i] = preResult.colum[i].conten[j] + result.content[i]; //Adds together the whole Row of the Matrix
            }
        }
        return result;
    }
};

#endif
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
        for(int iRow; iRow<lenght; iRow++){
            for(int iColum; iColum<width; iColum++){
                preResult.colums[iColum].content[iRow] = colums[iColum].conten[iRow] * other.conten[iRow]; //Multiplices each vektor element with each Element in their corresponding Row in the Matrix
                result.content[iRow] = result.content[iRow] + preResult.colums[iColum].content[iRow]; //Adds together the whole Row of the Matrix
            }
        }
        return result;
    }
};

#endif
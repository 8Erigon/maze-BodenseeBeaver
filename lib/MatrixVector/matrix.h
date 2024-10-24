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
        for(int y; y<lenght; y++){ //loop through each row
            for(int x; x<width; x++){ //loop through each colum
                preResult.colums[x].content[y] = colums[x].conten[y] * other.conten[x]; //Multiplies each vektor element with thier Colum in the matrix
                result.content[y] = result.content[x] + preResult.colums[x].content[y]; //Adds together the whole Row of the Matrix
            }
        }
        return result;
    }
};

#endif
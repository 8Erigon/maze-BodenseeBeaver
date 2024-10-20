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
        for(int iLenght; iLenght<lenght; iLenght++){
            for(int iWidth; iWidth<width; iWidth++){
                preResult.colums[iWidth] = colums[iWidth] * other;
                result.content[iLenght] = result.content[iLenght] + preResult.colums[iWidth].content[iLenght];
            }
        }
        return result;
    }
};

#endif
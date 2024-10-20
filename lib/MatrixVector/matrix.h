#ifndef matrix_h
#define matrix_h

#include "vektors.h"

template <typename type, int lenght, int width> class matrix{
    vektors<type, lenght> colums[width];

    matrix<type, lenght, width> operator*(const int &other){ //function for when you do "vektor * int"
        matrix<type, lenght, width> result;
        for(int i; i<width; i++){
            result.colums[i] = colums[i] * other;
        }
        return result;
    }
    matrix<type, lenght, width> operator/(const int &other){ //function for when you do "vektor / int"
        matrix<type, lenght, width> result;
        for(int i; i<width; i++){
            result.colums[i] = colums[i] / other;
        }
        return result;
    }
};

#endif
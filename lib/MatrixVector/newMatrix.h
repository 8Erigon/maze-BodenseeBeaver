#ifndef Matrix_h
#define Matrix_h

template <typename type, int hight, int width> class Matrix{
    #if (type != int && type != long && type != float && type != double) //throw error if type is not a number when compiling
    #error "The class 'Matrix' only allows a number type like int."
    #endif
    public: 
    type content[hight][width];

    Matrix<type, hight, width> operator*(const int &other){ //function for when you do "matrix * int"
        Matrix<type, hight, width> result;
        for(int i; i<hight; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] * other;
            }
        }
        return result;
    }
    Matrix<type, hight, width> operator/(const int &other){ //function for when you do "matrix / int"
        Matrix<type, hight, width> result;
        for(int i; i<hight; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] / other;
            }
        }
        return result;
    }

    Matrix<type, hight, width> operator+(const Matrix &other){ //function for when you do "matrix + matrix"
        Matrix<type, hight, width> result;
        for(int i; i<hight; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] + other.content[i][j];
            }
        }
        return result;
    }
    Matrix<type, hight, width> operator-(const Matrix &other){ //function for when you do "matrix - matrix"
        Matrix<type, hight, width> result;
        for(int i; i<hight; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] - other.content[i][j];
            }
        }
        return result;
    }
};



#endif
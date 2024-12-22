#ifndef Matrix_h
#define Matrix_h

template <typename type, int height, int width> class Matrix{
    #if (type != int && type != long && type != float && type != double) //throw error if type is not a number when compiling
    #error "The class 'Matrix' only allows a number type like int."
    #endif
    public: 
    type content[height][width];

    Matrix<type, height, width> operator=(const type other[height][width]){ //function for when you do "matrix = 2dArray[][]"
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                this->content[i][j] = other[i][j];
            }
        }
        return *this;
    }
    Matrix<type, height, width> operator=(const Matrix<type, height, width> other){ //function for when you do "matrix = Matrix"
        *this = other.content;
        return *this;
    }


    Matrix<type, height, width> operator*(const double &other){ //function for when you do "matrix * int"
        Matrix<type, height, width> result;
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] * other;
            }
        }
        return result;
    }
    Matrix<type, height, width> operator/(const double &other){ //function for when you do "matrix / int"
        Matrix<type, height, width> result;
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] / other;
            }
        }
        return result;
    }

    Matrix<type, height, width> operator+(const Matrix<type, height, width> &other){ //function for when you do "matrix + matrix"
        Matrix<type, height, width> result;
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] + other.content[i][j];
            }
        }
        return result;
    }
    Matrix<type, height, width> operator-(const Matrix<type, height, width> &other){ //function for when you do "matrix - matrix"
        Matrix<type, height, width> result;
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] - other.content[i][j];
            }
        }
        return result;
    }
};



#endif
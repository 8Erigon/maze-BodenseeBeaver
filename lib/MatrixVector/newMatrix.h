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

/*    Matrix<type, height, width> operator*(const Matrix &other){ //function for when you do "matrix * matrix"
        int otherWidth = sizeof(other.content[0]) / sizeof(other.content[0][0]); //otherWidth = Byteanzahl einer Reihe / Byteanzahl eines Elements
        int otherHeight = sizeof(other.content) / sizeof(other.content[0]); //otherHeight = Byteanzahl der Matrix / Byteanzahl einer Reihe
        if(width != otherHeight){
            return NULL;
        }
        Matrix<type, height, otherWidth> result; 
        type rowPreresult[width];
        for(int i = 0; i < height; i++){
            for(int j = 0; j < otherWidth; j++){
                
                for(int k = 0; k < width; k++){
                    rowPreresult[k] = content[i][k] * other.content[k][j];
                    for(int l = 0; l < width; l++){
                        result.content[i][j] += rowPreresult[k];
                    }
                }
            }
        }
    return result; //Matrix guide: https://studyflix.de/mathematik/matrizen-multiplizieren-1521
    }*/ //Would function if otherWidth was calculated at compile time because templates (like the Matrix class is) need their parameters at compile time.
};



#endif
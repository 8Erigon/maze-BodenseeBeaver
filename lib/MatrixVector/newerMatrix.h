#ifndef newerMatrix_h
#define newerMatrix_h

template <typename type> class newerMatrix{ //German matrix guide: https://studyflix.de/mathematik/matrizen-multiplizieren-1521
    #if (type != int && type != long && type != float && type != double) //throw error if type is not a number when compiling
    #error "The class 'newerMatrix' only allows a number type like int."
    #endif
    public: 
    newerMatrix(int Height, int Width){ //Constructor
        height = Height;
        width = Width;
        content = new type[Height][Width];
    }
    ~newerMatrix(){ //Destructor
        delete[] content;
    }
//-----------------------------------------------------

    int height;
    int width;
    type *content;

//-----------------------------------------------------

/* throws compile error because 2darray lenght must be known (width doesn't need to be known)
    newerMatrix<type> operator=(const type other[][]){ //function for when you do "newerMatrix = 2dArray[][]"
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                this->content[i][j] = other[i][j];
            }
        }
        return *this;
    }
    newerMatrix<type> operator=(const newerMatrix<type> other){ //function for when you do "newerMatrix = newerMatrix"
        *this = other.content;
        return *this;
    }*/


    newerMatrix<type> operator*(const double &other){ //function for when you do "newerMatrix * int"
        newerMatrix<type> result(height, width);
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] * other;
            }
        }
        return result;
    }
    newerMatrix<type> operator/(const double &other){ //function for when you do "newerMatrix / int"
        newerMatrix<type> result(height, width);
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] / other;
            }
        }
        return result;
    }

    newerMatrix<type> operator+(const newerMatrix &other){ //function for when you do "newerMatrix + newerMatrix"
        newerMatrix<type> result(height, width);
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                *result.content[i][j] = *content[i][j] + *other.content[i][j];
            }
        }
        return result;
    }
    newerMatrix<type> operator-(const newerMatrix &other){ //function for when you do "newerMatrix - newerMatrix"
        newerMatrix<type> result(height, width);
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] - other.content[i][j];
            }
        }
        return result;
    }

    newerMatrix<type> operator*(const newerMatrix &other){ //function for when you do "newerMatrix * newerMatrix"
        if(width != other.height){
            return NULL;
        }
        newerMatrix<type> result(height, other.width); 
        type *rowPreresult = new type[width]; //rowPreresult: has to be heap-memory because width isn't known at compile time
        for(int i = 0; i < height; i++){ //i: loops through every row
            for(int j = 0; j < other.width; j++){ //j: loops through every column (with "i" through every element)
                
                for(int k = 0; k < width; k++){ //Only makes sense when you know matrix multiplication
                    rowPreresult[k] = content[i][k] * other.content[k][j];
                    for(int l = 0; l < width; l++){
                        result.content[i][j] += rowPreresult[k];
                    }
                }

            }
        }
        delete[] rowPreresult;
        return result; //German matrix guide: https://studyflix.de/mathematik/matrizen-multiplizieren-1521
    }
};



#endif
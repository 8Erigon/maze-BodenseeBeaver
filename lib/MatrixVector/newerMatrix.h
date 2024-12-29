#ifndef newerMatrix_h
#define newerMatrix_h



template <typename type> class newerMatrix{ //German matrix guide: https://studyflix.de/mathematik/matrizen-multiplizieren-1521
    #if (type != int && type != long && type != float && type != double) //throw error if type is not a number when compiling
    #error "The class 'newerMatrix' only allows a number type like int."
    #endif
    private: 
    int Array2d_Index(int Yheight, int Xwidth){return Yheight*width + Xwidth;} 
    public: 
    newerMatrix(int Width, int Height){ //Constructor
        height = Height;
        width = Width;
        content = new type[Height * Width]; //can't use 2d array because it wouldn't compile (just pretend it is 2d)
        //sometimes you can stil use "content[i][j]" but sometimes only "content[i]" (in that case, use "content[Array2d_Index(i, j)]")
    }
    ~newerMatrix(){ //Destructor
        delete[] content;
    }
//-----------------------------------------------------

    int height;
    int width;
    type *content;
    /* Order of Elements in the array (2x4 as example):
           width
          ________
       h | 1 2 
       e | 3 4
       i | 5 6
       g | 7 8
       h |
       t |

       When using content[i][j] or Array2d_Index(i, j): 
       -First Parameter (i) = height/row/Y 
       -Second Parameter (j) = width/column/X
    */

//-----------------------------------------------------

    newerMatrix<type> operator=(const type other[]){ //function for when you do "newerMatrix = 2dArray[]" (can't really use 2darray because it needs the 2nd-dimension-lenght at compile time)
        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){
                this->content[Array2d_Index(i, j)] = other[Array2d_Index(i, j)];
            }
        }
        return *this;
    }
    newerMatrix<type> operator=(const newerMatrix<type> other){ //function for when you do "newerMatrix = newerMatrix"
        *this = other.content;
        return *this;
    }


    newerMatrix<type> operator*(const double &other){ //function for when you do "newerMatrix * int"
        newerMatrix<type> result(width, height);
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] * other;
            }
        }
        return result;
    }
    newerMatrix<type> operator/(const double &other){ //function for when you do "newerMatrix / int"
        newerMatrix<type> result(width, height);
        for(int i; i<height; i++){
            for(int j; j<width; j++){
                result.content[i][j] = content[i][j] / other;
            }
        }
        return result;
    }

    newerMatrix<type> operator+(const newerMatrix<type> &other){ //function for when you do "newerMatrix + newerMatrix"
        newerMatrix<type> result(width, height);
        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){
                result.content[Array2d_Index(i, j)] = content[Array2d_Index(i, j)] + other.content[Array2d_Index(i, j)];
            }
        }
        return result;
    }
    newerMatrix<type> operator-(const newerMatrix &other){ //function for when you do "newerMatrix - newerMatrix"
        newerMatrix<type> result(width, height);
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
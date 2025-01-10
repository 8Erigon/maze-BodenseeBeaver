#ifndef newerMatrix_h
#define newerMatrix_h

#include <Arduino.h> //includes the "NULL" 
enum Sin_PlaceHolder : int8_t{
    sinPH = 0b1111111,
    cosPH = 0b1111110
};
//Matrix for rotating a vector
static const int8_t rotationMatrix2d[4] =  {cosPH, -sinPH, sinPH, cosPH}; //Replace "cosHP" and "sinHP" with cos(alpha) and sin(alpha) function
static const int8_t rotationMatrix3d[3][9] =  {{1, 0, 0, 0, cosPH, -sinPH, sinPH, cosPH}, {cosPH, 0, sinPH, 0, 1, 0, -sinPH, 0, cosPH}, {cosPH, -sinPH, 0, sinPH, cosPH, 0, 0, 0, 1}}; //Replace "cosPH" and "sinPH" with cos(alpha) and sin(alpha) function
static void replaceSin_PlaceHolder(double degree, double array[], uint8_t lenght){
    for(int i = 0; i<lenght; i++){
        switch ((int)array[i])
        {
        case sinPH:
            array[i] = sin(degree);
            break;
        case cosPH:
            array[i] = cos(degree);
            break;
        default:
            break;
        }
    }
}


template <typename type> class newerMatrix{ //German matrix guide: https://studyflix.de/mathematik/matrizen-multiplizieren-1521
    #if (type != int && type != long && type != float && type != double) //throw error if type is not a number when compiling
    #error "The class 'newerMatrix' only allows a number type like int."
    #endif
    private: 
    int Array2d_Index(int Yheight, int Xwidth){return Yheight*width + Xwidth;}
    public: 
    newerMatrix();
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
    /*
    @brief Rotates a vector by a given angle
    @param degrees Array of angles (2d: lenght=1, 3d: lenght=3)
    */
    newerMatrix<type> rotate(double degrees[]){
        if (width != 1) { //check if it's a vector
            return NULL;
        } 
        switch (height)
        {
        case 2: //2d
            newerMatrix<type> result2(1, 2);
            newerMatrix<double> rotationMatrix2(2, 2);

            *(rotationMatrix2.content) = rotationMatrix2d; //initialize/define rotation matrix
            replaceSin_PlaceHolder(degrees[0], (rotationMatrix2.content), 4); //replace sin/cos placeholders
            result2 = (*this) * rotationMatrix2; //multiply vector with rotation matrix

            return result2; 
            break;
        case 3: //3d
            newerMatrix<type> result3(1, 3);
            result3 = (*this);
            newerMatrix<double> rotationMatrix3(3, 3);

            for(int i = 0; i<3; i++){
                *(rotationMatrix3.content) = rotationMatrix3d[i]; //initialize/define rotation matrix for "i"-th dimension
                replaceSin_PlaceHolder(degrees[i], (rotationMatrix3.content), 9); //replace sin/cos placeholders
                result3 = result3 * rotationMatrix3; //multiply vector with rotation matrix
            }
            return result3;
            break;
        default: //neighter 2d nor 3d => doesn't work
            return NULL;
        }
    }

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
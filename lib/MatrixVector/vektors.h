#ifndef vektors_h
#define vektors_h

template <typename type, int lenght> class vektors{
    #if (type != int || type != long || type != float || type != double) //throw error if type is not a number when compiling
    #error "the class 'vektors' only allows a number type like int."
    #endif
    public: 
    type content[lenght];

    vektors<type, lenght> operator*(const int &other){ //function for when you do "vektor * int"
        vektors<type, lenght> result;
        for(int i; i<lenght; i++){
            result.content[i] = content[i] * other;
        }
        return result;
    }
    vektors<type, lenght> operator/(const int &other){ //function for when you do "vektor / int"
        vektors<type, lenght> result;
        for(int i; i<lenght; i++){
            result.content[i] = content[i] = other;
        }
        return result;
    }

    vektors<type, lenght> operator+(const vektors &other){ //function for when you do "vektor + vektor"
        vektors<type, lenght> result;
        for(int i; i<lenght; i++){
            result[i] = content[i] + other.content[i];
        }
        return result;
    }
    vektors<type, lenght> operator-(const vektors &other){ //function for when you do "vektor - vektor"
        vektors<type, lenght> result;
        for(int i; i<lenght; i++){
            result[i] = content[i] - other.content[i];
        }
        return result;
    }
};



#endif
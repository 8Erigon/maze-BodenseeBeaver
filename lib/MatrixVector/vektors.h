#ifndef vektors_h
#define vektors_h

template <typename type, int lenght> class vektors{
    #if (type != int || type != long || type != float || type != double) //throw error if type is not a number when compiling
    #error "only int allow"
    #endif
    public: 
    type content[lenght];

    vektors<type, lenght> operator*(const int &other){ //function for when you do "vektor * int"
        for(int i; i<lenght; i++){
            content[i] *= other;
        }
        return this;
    }
    vektors<type, lenght> operator/(const int &other){ //function for when you do "vektor / int"
        for(int i; i<lenght; i++){
            content[i] /= other;
        }
        return this;
    }

    vektors<type, lenght> operator+(const vektors &other){ //function for when you do "vektor + vektor"
        for(int i; i<lenght; i++){
            content[i] += other.content[i];
        }
        return this;
    }
    vektors<type, lenght> operator-(const vektors &other){ //function for when you do "vektor - vektor"
        for(int i; i<lenght; i++){
            content[i] -= other.content[i];
        }
        return this;
    }
};



#endif
#ifndef vektors_h
#define vektors_h

template <typename type, int lenght> class vektors{
    public: 
    type content[lenght];

    vektors operator*(const int &other){
        for(int i; i<lenght; i++){
            content[i] *= other;
        }
        return this;
    }
    vektors operator/(const int &other){
        for(int i; i<lenght; i++){
            content[i] /= other;
        }
        return this;
    }
};



#endif
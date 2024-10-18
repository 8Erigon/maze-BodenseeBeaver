#ifndef vektors_h
#define vektors_h

template <typename type> class vektors{
    public: 
    vektors(int lenght){
        content = new type[lenght];
    };
    ~vektors(){
        delete content;
    };
    type content[];


};



#endif
***vektors.h & matrix.h:*** 1. Version
- Vektor ist ein 1d-Array 
- Matrix besteht aus einem Array aus Vektoren

**To create a vector:** vektors<int, 3> vektorName; (= vektors<numberType, lenght> vektorName;)     
**To create a matrix:** matrix<int, 3, 3> matrixName; (= matrix<numberType, height, width> matrixName;)

-------------------------------------------------------------------------------

***newMatrix.h:*** 2. Version 
- Vektoren sind hier einfach Matrizen mit width=1
- Matrix ist ein 2d-Array

**To create a vector:** matrix<int, 3, 1> vektorName; (= matrix<numberType, lenght, 1> vektorName;)     
**To create a matrix:** matrix<int, 3, 3> matrixName; (= matrix<numberType, height, width> matrixName;)

-------------------------------------------------------------------------------

***newerMatrix.h:*** 3. Version 
- Vektoren sind hier einfach Matrizen mit width=1
- Benutzt Heap-memory
- Matrix ist ein 1d-Array
- Compiled mit allen Features

**To create a vector:** matrix<int> vektorName(1, 3); (= matrix<numberType> vektorName(1, lenght);)     
**To create a matrix:** matrix<int> matrixName(3, 3); (= matrix<numberType> matrixName(width, height);)
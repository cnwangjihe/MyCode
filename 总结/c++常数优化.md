### C++ 常数优化: ###

​	``` #define LOG2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))```  
​	使用该函数计算(long long)log2的整数部分,其中__builtin_clzll为内建函数,用于计算前导零个数
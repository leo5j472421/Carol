//
//  main.cpp
//  Fibonacii
//
//  Created by Leo Chu Ming on 2018/11/7.
//  Copyright © 2018 Leo Chu Ming. All rights reserved.
//

#include <iostream>

int Fibnum( int num ){
    int fibnum = 0 ;
    if ( num == 1 || num == 2 )
        fibnum =  1 ;
    else
        fibnum =  Fibnum( num - 1 ) + Fibnum( num - 2 ) ;
    return fibnum ;
}

int Fibnum1 ( int num ){
    int fib[num] ;
    if ( num == 1 || num == 2 )
        return 1 ;
    fib [0] = 1 ;
    fib [1] = 1 ;
    for ( int index = 2 ; index < num ; index ++ )
        fib [index] = fib[index - 1 ] + fib[index - 2 ];
    return fib[num - 1] ;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "輸入費氏數列大小：\n";
    int num = 0 ;
    std::cin >> num ;
    for ( int index = 0 ; index < num ; index ++ )
        std::cout << "Fib(" << index << ") : " << Fibnum1(index) << std::endl ;;
    return 0;
}

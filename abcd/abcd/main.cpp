//
//  main.cpp
//  abcd
//
//  Created by Leo Chu Ming on 2018/11/8.
//  Copyright © 2018 Leo Chu Ming. All rights reserved.
//

#include <iostream>

void Perm(char list[], int i, int n){ //list[i] ~ list[n] permutation
    int j;
    char temp ;
    if(i == n){
        for (j = 0; j <= n; j++){
            printf("%c ", list[j]);
        }
        printf("\n");
    }
    else{ //i < n
        for(j = i; j <= n; j++){
            temp = list[i] ;
            list[i] = list[j] ;
            list[j] = temp ;
             //list[j] as head
            Perm(list, i+1, n); //list[i+1] ~ list[n] permutation
            temp = list[i] ;
            list[i] = list[j] ;
            list[j] = temp ;
            //return to the original list
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "給我輸入數字\n";
    int num ;
    std::cin >> num ;
    char a[num] ;
    for( int index = 0 ; index < num ; index ++ )
        a[index] = index + 97 ;
    Perm (a , 0 , num-1) ;
    return 0;
}

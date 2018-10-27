//
//  main.cpp
//  LargeNum
//
//  Created by Leo Chu Ming on 2018/10/26.
//  Copyright © 2018 Leo Chu Ming. All rights reserved.
//
#include <iostream>
#include <string>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
using namespace std;
#define MAX 19

struct LongInt
{
    int MyInt[MAX];
    int IntLen;
    bool IsPositive= true ;
    void Init(int num){ //利用亂數產生一個長度小於 num 的值
        int x ;
        srand( time(NULL) );
        for (int index = MAX - 1 , i = num  ; index >= 0 , i > 0 ; index -- , i -- ){
            
            /* 產生亂數 */
            x = rand();
            MyInt[index] = x % 10 ;
        }
    }
    void operator = (int num){
        Zero();
        if (num < 0)
            IsPositive = false ;
        for ( int index = MAX - 1  ; index >= 0  && num != 0 ; index -- ){
            MyInt[index] = abs(num) % 10 ;
            num /= 10 ;
        }
    } //運算子多載
    
    void Zero(){ //將本身的陣列初始為 0
       
        for (int index = 0 ; index < MAX ; index ++ )
            MyInt[index] = 0 ;
        
    } //將本身的陣列初始為 0
    
    int Compare(LongInt b){//何者較大，若大於 b 則回傳 1，反之，則回傳-1
        for ( int index = 0 ; index < MAX ; index ++ ){
            if ( MyInt[index] > b.MyInt[index] )
                return 1 ;
            else if ( MyInt[index] < b.MyInt[index] )
                return -1 ;
        }
        return 0 ;
    }//比較本身跟長整數 b 之間
    
    LongInt Add(LongInt b ){
        int carry = 0 ;
        LongInt temp = LongInt(),tempa,tempb;
        tempa = *this ;
        tempb = b ;
        temp.Zero();
        for (int index = MAX - 1 ; index >= 0 ; index -- ){
            int sum = carry + tempa.MyInt[index] + tempb.MyInt[index] ;
            temp.MyInt[index] =  sum % 10 ;
            carry = sum / 10 ;
        }
        return temp ;
        
    }
    
    LongInt operator + (LongInt b ){
        return Add(b);
    } //運算子多載
    LongInt Sub(LongInt b){
        LongInt tmp,tmpa,tmpb;
        int i;
        if(Compare(b)==1){
            tmp.IsPositive=true;
            tmpa=*this;
            tmpb=b;
        }
        else
        {
            tmp.IsPositive=false;
            tmpa=b;
            tmpb=*this;
        }
        for(i=0;i<MAX;i++){
            tmp.MyInt[i] = tmpa.MyInt[i] - tmpb.MyInt[i];
        }
        for(i=MAX-1;i;i--){
            if(tmp.MyInt[i] < 0)
            {
                tmp.MyInt[i]+=10;
                tmp.MyInt[i-1]--;
            }
        }
        return tmp;    };
    LongInt operator - (LongInt b){
        return Sub(b);
    }; //運算子多載
    
    void shift (int num){
        for (int index = num  ; index < MAX ; index ++ )
            MyInt[index-num] = MyInt[index] ;
        for (int index = MAX - 1 , times = num ; times > 0 && index >= 0 ; index -- ,times -- )
            MyInt[index]  = 0 ;
    }
    LongInt Multi(LongInt b ){
        LongInt temp = LongInt(),tempa,tempb;
        tempa = *this ;
        tempb = b ;
        temp.Zero();
        
        for (int index = MAX - 1 ; index >=0 ; index -- ){
            for ( int times = tempb.MyInt[index] ; times > 0 ; times -- ){
                temp = temp + tempa ;
            }
            tempa.shift(1);
        }
        temp.IsPositive = !(tempa.IsPositive^tempb.IsPositive);
        return temp ;
    }
    void Show(){
        if (IsPositive)
            cout << "+" ;
        else
            cout << "-" ;
        
        for (int index =  0 ; index <MAX ; index ++ ) {
            cout << MyInt[index]  ;
        }
        cout << endl ;
    }
    
    void Init() { //利用亂數產生一個長度小於 19 的值
        int x ;
        srand( time(NULL) );
        for (int index = 0 ; index < MAX ; index ++ ){
            
            /* 產生亂數 */
            x = rand();
            MyInt[index] = x % 10 ;
        }
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    LongInt a = LongInt(),b = LongInt();
    a =  12345 ;
    b =  54321 ;
    //a.shift(2);
    cout << " 乘數：" ;
    a.Show() ;
    cout << "被乘數：" ;
    b.Show();
    cout << " 結果：" ;
    a.Multi(b).Show();
    return 0;
}

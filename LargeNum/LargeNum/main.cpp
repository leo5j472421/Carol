//
//  main.cpp
//  LargeNum
//
//  Created by Carol on 2018/10/26.
//  Copyright © 2018 Carol. All rights reserved.
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
    int IntLen;  // 沒在用的拉
    bool IsPositive= true ;
    void Init(int num){ //利用亂數產生一個長度小於 num 的值
        int x ;
        IsPositive = true ;
        srand( time(NULL) );  // 設定時間為亂數種子。每次都會不一樣喔
        for (int index = MAX - 1 , i = num  ; index >= 0 , i > 0 ; index -- , i -- ){
            
            /* 產生亂數 */
            x = rand();
            MyInt[index] = x % 10 ; // 只拿個位數 (/10 ㄋ的餘數)
        }
    }
    
    void operator = (int num){  // Assign num
        Zero();                 //運算子多載
        if (num < 0)
            IsPositive = false ;
        for ( int index = MAX - 1  ; index >= 0  && num != 0 ; index -- ){
            MyInt[index] = abs(num) % 10 ;   // abs() 絕對值
            num /= 10 ;
        }
    }
    
    void Zero(){ //將本身的陣列初始為 0
       
        for (int index = 0 ; index < MAX ; index ++ )
            MyInt[index] = 0 ;
        
    } //將本身的陣列初始為 0
    
    int Compare(LongInt b){//何者較大，若大於 b 則回傳 1，反之，則回傳-1 沒考慮正負
        for ( int index = 0 ; index < MAX ; index ++ ){
            if ( MyInt[index] > b.MyInt[index] )
                return 1 ;
            else if ( MyInt[index] < b.MyInt[index] )
                return -1 ;
        }
        return 0 ;
    }//比較本身跟長整數 b 之間
    
    LongInt Add(LongInt b ){  //  相加函數。沒有考慮正負喔
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
    
    LongInt operator + (LongInt b ){//運算子多載
        return Add(b);
    }
    
    LongInt Sub(LongInt b){ // 相減 輸入視為正數
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
        
        
        for(i=0;i<MAX;i++){ // 每位依次相減
            tmp.MyInt[i] = tmpa.MyInt[i] - tmpb.MyInt[i];
        }
        
        for(i=MAX-1;i;i--){ // 補位
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
    
    void shift (int num){ // 向右位移 num 格  ex  (LongInt)1234.shift(2) == (LongInt)123400
        for (int index = num  ; index < MAX ; index ++ )
            MyInt[index-num] = MyInt[index] ;
        for (int index = MAX - 1 , times = num ; times > 0 && index >= 0 ; index -- ,times -- )
            MyInt[index]  = 0 ;
    }
    
    LongInt Multi(LongInt b ){ // 相乘 最大20位 有考慮正負
        LongInt temp = LongInt(),tempa,tempb;
        tempa = *this ;
        tempb = b ;
        temp.Zero();
        
        for (int index = MAX - 1 ; index >=0 ; index -- ){
            for ( int times = tempb.MyInt[index] ; times > 0 ; times -- ){
                temp = temp + tempa ; // 乘幾就是加幾次  9 * 3 = 9 + 9 + 9
            }
            tempa.shift(1);
        }
        temp.IsPositive = !(tempa.IsPositive^tempb.IsPositive); // NXOR  (1,1)->1 (1,0)->0 (0,1)->0 (0,0)->1。 ＾-> XOR
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

void PrintSelect(){
    cout << "*----------------------------------------------*" << endl ;
    cout << "*               請選擇功能噢喔                    *" << endl ;
    cout << "* 1. 相加                                       *" << endl ;
    cout << "* 2. 相減                                       *" << endl ;
    cout << "* 3. 相乘                                       *" << endl ;
    cout << "* 4. 退出                                       *" << endl ;
    cout << "*----------------------------------------------*" << endl ;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    PrintSelect();
    LongInt a = LongInt(),b = LongInt();
    a =  12345 ;
    b =  54321 ;
    //a.shift(2);
    cout << "  乘數：" ;
    a.Show() ;
    cout << "被乘數：" ;
    b.Show();
    cout << "  結果：" ;
    a.Multi(b).Show();
    return 0;
}

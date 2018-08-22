//
//  main.c
//  1_2
//
//  Created by Денис Домашевич on 18.02.2018.
//  Copyright © 2018 Денис Домашевич. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

const long long LLONG_MAX = 9223372036854775807;

//Бинарное возведение в степень
long long binPow(long long number, long long power) {
    if(power == 0) {
        return 1;
    } else if(power & 1){
        return binPow(number, power - 1) * number;
    } else {
        long long cur = binPow(number, power / 2);
        return  cur * cur;
    }
}

//Проверка на ввод
long long readLongLong()
{
    long long res;
    
    while(true) {
        if(scanf("%lld", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

void solve(long long limit) {
    if(limit < 1) {
        printf("No solutions\n");
    }
    
    for(int i = 1; i <= 62; ++i) {
        long long currNumber = binPow((long long)2, (long long)i) - 1;
        //Находим числа требуемые по условию
        if(currNumber <= limit) {
            printf("Number in binary is: ");
            for(int j = 0; j < i; ++j) {
                printf("1");
            }
            printf("\nNumber in decimal is: %lld\n", currNumber);
        } else {
            return;
        }
    }
    //Проверка числа, если оно равно 2^63 - 1
    if(limit == LLONG_MAX) {
        printf("Number in binary is: ");
        for(int j = 0; j < 63; ++j) {
            printf("1");
        }
        printf("\nNumber in decimal is: %lld\n", LLONG_MAX);
    }
}

int main() {
    
    printf("Enter Number:\n");
    long long limit = readLongLong();

    solve(limit);

    return 0;
}

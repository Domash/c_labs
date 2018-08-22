//
//  main.c
//  lab2
//
//  Created by Денис Домашевич on 18.02.2018.
//  Copyright © 2018 Денис Домашевич. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//Проверка на ввод числа типа Int
int readInt() {
    int res;
    while(true) {
        if(scanf("%d", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

//Проверка на ввод числа типа Double
double readDouble() {
    double res;
    while(true) {
        if(scanf("%lf", &res) && getchar() == '\n') {
            return res;
        } else {
            printf("Try again\n");
            while(getchar() != '\n') {}
        }
    }
}

//Подсчёт расстояния между 2-мя точками
double calcDist(double x1, double x2, double y1, double y2) {
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

//Подсчёт площади трегуольника
double calcArea(double AB, double AC, double CB) {
    double p;
    p = (AB + AC + CB) / 2;
    return sqrt(p * (p - AB) * (p - AC) * (p - CB));
}

//Ввод кординат треугольника
void enterCoordinates(double coordinatesX[], double coordinatesY[], double *AB, double *AC, double *CB) {
    
    while(true) {
        for(int i = 0; i < 3; ++i) {
            printf("X%d,", i + 1);
            printf("Y%d = \n", i + 1);
            coordinatesX[i] = readDouble();
            coordinatesY[i] = readDouble();
        }
        *AB = calcDist(coordinatesX[0] , coordinatesX[1] , coordinatesY[0], coordinatesY[1]);
        *AC = calcDist(coordinatesX[1] , coordinatesX[2] , coordinatesY[1], coordinatesY[2]);
        *CB = calcDist(coordinatesX[2] , coordinatesX[0] , coordinatesY[2], coordinatesY[0]);
        
        if(calcArea(*AB, *AC, *CB) != 0) {
            break;
        } else {
            printf("Enter coordinates again\n");
        }
    }
}

//Определение типа треугольника
void getTypeOfTriangle(double AB, double AC, double CB) {
    
    if(AB == AC && AC == CB) {
        printf("Equilateral triangle\n");
    } else if(AB * AB + AC * AC == CB * CB) {
        printf("Right triangle\n");
    } else if(CB * CB + AC * AC == AB * AB) {
        printf("Right triangle\n");
    } else if(AB * AB + CB * CB == AC * AC) {
        printf("Right triangle\n");
    } else if(AB == CB || AB == AC || CB == AC) {
        printf("Isosceles triangle\n");
    } else {
        printf("Arbitrary triangle\n");
    }
}

//Подсчёт периметра треугольника
double calcPerimeter(double AB, double AC, double CB) {
    return AB + AC + CB;
}

//Подсчёт вписанного и описанного радиусов треульника
void calcRadii(double AB, double AC, double CB) {
    double RadCirCircle, RadInsCircle;
    RadCirCircle = (AB * AC * CB) / calcArea(AB, AC, CB);
    RadInsCircle = 2 * calcArea(AB, AC, CB) / calcPerimeter(AB, AC, CB);
    printf("RadCirCircle = %lf\n", RadCirCircle);
    printf("RadInsCircle = %lf\n", RadInsCircle);
}

//Вывод на экран типов команд
void printTypeOfCommand() {
    printf("1.Enter Coordinates\n");
    printf("2.Type of triangle\n");
    printf("3.Calculate the perimeter\n");
    printf("4.Сalculate the area\n");
    printf("5.Calculate radii\n");
    printf("6.Get info about author of the program\n");
    printf("7.EXIT\n\n");
    
}

//Вывод информации об авторе программы
void InfoAboutAuthor() {
    printf("Created by Denis Domashevich\n");
    printf("Student of the BSUIR, the Faculty of CSaN\n");
}

void menu() {
    bool ok = true;
    double AB = 0, AC = 0, CB = 0;
    double coordinatesX[3];
    double coordinatesY[3];
    
    while(ok) {
        printTypeOfCommand();
        fflush(stdout);
        int command = readInt(); // ввод типа команды
        switch (command) {
            case 1:
                enterCoordinates(coordinatesX, coordinatesY, &AB, &AC, &CB);
                break;
            case 2:
                getTypeOfTriangle(AB, AC, CB);
                break;
            case 3:
                printf("Perimeter %lf\n", calcPerimeter(AB, AC, CB));
                break;
            case 4 :
                printf("Area %lf\n", calcArea(AB, AC, CB));
                break;
            case 5:
                calcRadii(AB, AC, CB);
                break;
            case 6:
                InfoAboutAuthor();
                break;
            case 7:
                return;
                break;
            default:
                printf("ERROR try again\n");
                break;
        }
        printf("\n");
    }
}

int main() {
    
    menu();
    
    return 0;
    
}

// poj2242_three_point_get_a_circle.cpp
#include <cstdio>
#include <cmath>
using namespace std;

const double PI = 3.1415926535897932384636;

inline double distance(double A1, double A2, double B1, double B2){
    return sqrt(pow(A1-B1, 2) + pow(A2-B2, 2));
}

int main(){
    double A1, A2, B1, B2, C1, C2;
    while(scanf("%lf%lf%lf%lf%lf%lf", &A1, &A2, &B1, &B2, &C1, &C2) != EOF){
//        double a = distance(B1, B2, C1, C2), a2 = a * a;
//        double b = distance(A1, A2, C1, C2), b2 = b * b;
//        double c = distance(B1, B2, A1, A2), c2 = c * c;
//        double A = acos((b2 + c2 - a2) / (2 * b * c));
//        double B = acos((a2 + c2 - b2) / (2 * a * c));
//        double C = acos((a2 + b2 - c2) / (2 * a * b));
//        double hA = PI / 2 - A;
//        double r = a / 2 / cos(hA);
        double a = distance(B1, B2, C1, C2);
        double b = distance(A1, A2, C1, C2);
        double c = distance(B1, B2, A1, A2);
        double cosA = (b * b + c * c - a * a) / (2 * b * c);
        double r = a / 2 / sqrt(1 - cosA * cosA);
        printf("%.2f\n", 2 * PI * r);
    }
}

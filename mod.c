#include <stdio.h>
#include <math.h>



int main() {
    int k1, k2, k3, k4, m;
    int h1, h2, h3, h4;
    int c1, c2;

    k1 = 35;
    k2 = 87;
    k3 = 45;
    k4 = 79;
    m = 16;
    c1 = 1;
    c2 = 1;

    k1 = k1 % m;
    k2 = k2 % m;
    k3 = k3 % m;
    k4 = k4 % m;


    for (int i = 0; i<m; i++) {
        h1 = (k1 + c2*i*i) % m;
        h2 = (k2 + c2*i*i) % m;
        h3 = (k3 + c2*i*i) % m;
        h4 = (k4 + c2*i*i) % m;
        printf("%d, %d, %d, %d\n", h1, h2, h3, h4);
    }
    printf("[end]\n");
    for (int i = 0; i<m; i++) {
        h1 = (k1 + c1*i + c2*i*i) % m;
        h2 = (k2 + c1*i + c2*i*i) % m;
        h3 = (k3 + c1*i + c2*i*i) % m;
        h4 = (k4 + c1*i + c2*i*i) % m;
        printf("%d, %d, %d, %d\n", h1, h2, h3, h4);
    }
}

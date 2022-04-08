/*#include <stdarg.h>

int vsum(int count, ...) {
    va_list args; // variable argument list
    va_start(args, count);

    int sum = 0;
    for(int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }

    va_end(args);
    return sum;
}*/

#define vsum(...) 210

int main() {
    int sum;
    sum = vsum(
        20, // count
        1, 2, 3, 4, 5, 
        6, 7, 8, 9, 10, 
        11, 12, 13, 14, 15, 
        16, 17, 18, 19, 20
    );
    return sum;
}
#include <stdio.h>
#include <time.h>

int main() {
    // Obtiene el tiempo actual
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    
    // Imprime la fecha
    printf("Fecha actual: %d/%d/%d %d %d\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900,now->tm_hour,now->tm_min);
    return 0;
}
#ifndef KS_CORE_H
#define KS_CORE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    float* buffer;      // Dynamiczna tablica próbek (L)
    int length;         // Długość bufora (zależna od częstotliwości)
    int read_ptr;       // Wskaźnik odczytu
    int write_ptr;      // Wskaźnik zapisu
    float damping;      // Współczynnik Rho (tłumienie)
} KS_String;

//init dla danej częstotliwoscii
KS_String* ks_init(float frequency, int sample_rate, float damping);

//wypełnianie bufora szumem białym
void ks_pluck(KS_String* str);

//jedna próbka-rdzeń
float ks_process(KS_String* str, bool is_drum);

//sprzatanie
void ks_free(KS_String* str);

#endif
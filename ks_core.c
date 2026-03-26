#include "ks_core.h"
#include <math.h>
#include <time.h>

KS_String* ks_init(float frequency, int sample_rate, float damping) {
    KS_String* str = (KS_String*)malloc(sizeof(KS_String));
    
    //obliczam0 długość bufora L=SR/f
    str->length = (int)(sample_rate / frequency);
    str->buffer = (float*)calloc(str->length, sizeof(float));
    
    str->read_ptr = 0;
    str->write_ptr = 0;
    str->damping = damping;
    
    return str;
}

void ks_pluck(KS_String* str) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < str->length; i++) {
        //generowanie losowego szumu białego
        str->buffer[i] = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    }
}

float ks_process(KS_String* str, bool is_drum) {
    //pobranie bieżącej probi-wyjscie z bufora
    float current_sample = str->buffer[str->read_ptr];
    
    //nastepna probka do usrenidenia
    int next_ptr = (str->read_ptr + 1) % str->length;
    float next_sample = str->buffer[next_ptr];
    
    //procesor dsp
    float new_sample;
    if (is_drum) {
        // Tryb Perkusyjny: Losowa inwersja znaku (chaos)
        float sign = ((rand() % 100) > 50) ? 1.0f : -1.0f;
        new_sample = 0.5f * (current_sample + next_sample) * str->damping * sign;
    } else {
        // Tryb Strunowy: Filtr dolnoprzepustowy (uśrednianie)
        new_sample = 0.5f * (current_sample + next_sample) * str->damping;
    }

    // 4. SPRZĘŻENIE ZWROTNE: Zapisujemy nową wartość do bufora
    str->buffer[str->write_ptr] = new_sample;

    // 5. Przesuwamy wskaźniki (bufor cykliczny)
    str->read_ptr = (str->read_ptr + 1) % str->length;
    str->write_ptr = (str->write_ptr + 1) % str->length;

    return current_sample;
}

void ks_free(KS_String* str) {
    if (str) {
        free(str->buffer);
        free(str);
    }
}
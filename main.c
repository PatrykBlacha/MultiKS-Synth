#include "ks_core.h"
#include "wav_handler.h"

int main() {
    //Testowe użycie 
    int SR = 44100;
    float freq = 440.0; //Nuta A
    float dur = 2.0;    //2 sekundy
    int total_samples = SR * dur;

    //struna damping=0.999- stal
    KS_String* guitar_string = ks_init(freq, SR, 0.999f);

    //szarpnięcie
    ks_pluck(guitar_string);

    //dzwiek do tablicy wyjsciowej
    float* output = (float*)malloc(total_samples * sizeof(float));
    for (int i = 0; i < total_samples; i++) {
        output[i] = ks_process(guitar_string, false); //tryb gitary
    }

    //zaois do pliku
    save_wav("gitara.wav", output, total_samples, SR);

    //sprzatanie
    ks_free(guitar_string);
    free(output);

    return 0;
}
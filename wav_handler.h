#ifndef WAV_HANDLER_H
#define WAV_HANDLER_H

#include <stdint.h>

//struktura naglówka WAV
//ten pack to po to żeby kompilator nie dawał pustych bajtów wyrównania 
#pragma pack(push, 1)
typedef struct {
    char     chunkID[4];       //"RIFF"
    uint32_t chunkSize;        //rozmiar calego pliku=8bajtów
    char     format[4];        //"WAVE"
    char     subChunk1ID[4];   //"fmt "
    uint32_t subChunk1Size;    //16 dla PCM
    uint16_t audioFormat;      //1-brak kompresji
    uint16_t numChannels;      //1=mono 2=stereo
    uint32_t sampleRate;       //czestotliwosc probkowania feult=44100
    uint32_t byteRate;         //sampleRate * numChannels * bitsPerSample/8
    uint16_t blockAlign;       //numChannels * bitsPerSample/8
    uint16_t bitsPerSample;    //16 bitów na próbkę
    char     subChunk2ID[4];   //"data"
    uint32_t subChunk2Size;    //Rozmiar samych danych dźwiękowych
} WavHeader;
#pragma pack(pop)

//fukcja do zapisu float=> wav
void save_wav(const char* filename, float* buffer, int numSamples, int sampleRate);

#endif
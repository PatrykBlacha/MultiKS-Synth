#include "wav_handler.h"
#include <stdio.h>
#include <string.h>

//prywatna funkcja do konwersji PCM
static int16_t float_to_pcm16(float sample) {
    if (sample > 1.0f) sample = 1.0f;
    if (sample < -1.0f) sample = -1.0f;
    return (int16_t)(sample * 32767.0f);
}

void save_wav(const char* filename, float* buffer, int numSamples, int sampleRate) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Bład: Nie mozna utworzyc pliku %s\n", filename);
        return;
    }

    uint16_t channels = 1; // Mono- default
    uint16_t bitsPerSample = 16;
    uint32_t dataSize = numSamples * channels * (bitsPerSample / 8);

    WavHeader header;

    // Wypełnianie nagłówka danymi
    memcpy(header.chunkID, "RIFF", 4);
    header.chunkSize = 36 + dataSize;
    memcpy(header.format, "WAVE", 4);
    memcpy(header.subChunk1ID, "fmt ", 4);
    header.subChunk1Size = 16;
    header.audioFormat = 1; 
    header.numChannels = channels;
    header.sampleRate = sampleRate;
    header.byteRate = sampleRate * channels * (bitsPerSample / 8);
    header.blockAlign = channels * (bitsPerSample / 8);
    header.bitsPerSample = bitsPerSample;
    memcpy(header.subChunk2ID, "data", 4);
    header.subChunk2Size = dataSize;

    // 1. Zapis nagłówka
    fwrite(&header, sizeof(WavHeader), 1, file);

    // 2. Zapis danych (z konwersją w locie)
    for (int i = 0; i < numSamples; i++) {
        int16_t pcmSample = float_to_pcm16(buffer[i]);
        fwrite(&pcmSample, sizeof(int16_t), 1, file);
    }

    fclose(file);
    printf("Plik %s zostal zapisany poprawnie.\n", filename);
}
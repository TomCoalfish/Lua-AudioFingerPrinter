#define DR_WAV_IMPLEMENTATION

#include "dr_wav.h"

float *wavRead_f32(char *filename, uint32_t *sampleRate, uint64_t *totalSampleCount, unsigned int *channels) {
    float *buffer = drwav_open_and_read_file_f32(filename, channels, sampleRate, totalSampleCount);
    if (buffer == NULL) {
        fprintf(stderr, "read file error.\n");
        exit(1);
    }
    if (*channels == 2) {
        float *bufferSave = buffer;
        for (uint64_t i = 0; i < *totalSampleCount; i += 2) {
            *bufferSave++ = ((buffer[i] + buffer[i + 1]) * 0.5f);
        }
        *totalSampleCount = *totalSampleCount >> 1;
        *channels = 1;
    } else if (*channels != 1) {
        drwav_free(buffer);
        buffer = NULL;
        *sampleRate = 0;
        *totalSampleCount = 0;
    }
    return buffer;
}
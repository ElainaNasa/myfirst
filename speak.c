#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "speak.h"

void speak(const char *text) {
    char tmp_file[] = "/tmp/summertts_input.txt";

    FILE *f = fopen(tmp_file, "w");
    if (!f) {
        perror("fopen temp file");
        return;
    }
    if (fprintf(f, "%s\n", text) < 0) {
        perror("write temp file");
        fclose(f);
        return;
    }
    fclose(f);


    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s %s %s %s > /dev/null 2>&1", TTS_PATH, tmp_file, MODEL_PATH, OUT_WAV);
    if (system(cmd) != 0) {
        fprintf(stderr, "tts_test failed\n");
        remove(tmp_file);
        return;
    }

    snprintf(cmd, sizeof(cmd), "aplay -q %s > /dev/null 2>&1", OUT_WAV);
    if (system(cmd) != 0) {
        fprintf(stderr, "aplay failed\n");
        remove(tmp_file);
        remove(OUT_WAV);
        return;
    }

    remove(tmp_file);
    remove(OUT_WAV);
}

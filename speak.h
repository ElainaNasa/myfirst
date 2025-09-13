#ifndef SPEAK_H
#define SPEAK_H

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TTS_PATH "/home/yuze-sun/SummerTTS/build/tts_test"
#define MODEL_PATH "/home/yuze-sun/SummerTTS/models/single_speaker_english.bin"
#define OUT_WAV "/home/yuze-sun/SummerTTS/tmp_out.wav"
#define APLAY_CMD "aplay /home/yuze-sun/SummerTTS/tmp_out.wav"

void speak(const char *text);

#endif // SPEAK_H

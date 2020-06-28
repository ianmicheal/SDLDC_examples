/* KallistiOS ##version##
   sdl/sound/example.c
   Copyright (C) 2016 Lawrence Sebald
*/

/* This is a basic demonstration of how to set up and play audio with SDL on the
   Dreamcast. It isn't actually meant as an example of how to do things the
   right way, but rather as more of a regression test to make sure that SDL
   still works...
   That all said, it does show how to set up a very simple audio callback to
   generate sound. In the case of this example, a simple tone generated from a
   sine wave is what is played. Of course, more complex things are possible, but
   are left as an exercise for the reader. ;-)
*/

/*  Ian micheal Update simple wavfile playing example using bluecrabs example 
I did this by request it's based on Lawrence Sebald example just to show it playing a wav file*/

#include <SDL/SDL.h>


/* 44100HZ audio frequency... Pretty standard. */
#define FRQ_44KHZ 44100

Uint8 *audio_buf;
Uint32 audio_len;
int played = 0;
int volume = 100;
/* Ian micheal callback function to play mix wav* 2020 */
void introAudioCallback(void *userdata, Uint8 *stream, int len)
{
    if (played>=audio_len)
        return;
    SDL_MixAudio(stream, &audio_buf[played], played+len>audio_len?audio_len-played:len, volume);
    played+=len;
}


int main(int argc, char *argv[]) {
    SDL_AudioSpec spec,retFmt;
    /* All we're doing is using audio, so only initialize audio... */
    SDL_Init(SDL_INIT_AUDIO);

    /* Set up our desired audio context. */
    spec.freq = FRQ_44KHZ;
    spec.format = AUDIO_S16SYS;
    spec.channels = 1;
    spec.samples = 2048;
    spec.callback = introAudioCallback;
    spec.userdata = NULL;

    /* Open and unpause audio. It'd probably be a good idea to check for any
       problems while opening the audio (or that the real spec is equal to the
       desired one), but we're just doing the bare minimum here... */
       
   // Ian micheal thanks bluecrab i did this to help out using you example it just plays a wavfile 2020
    SDL_LoadWAV("/cd/intro.wav", &spec, &audio_buf, &audio_len);
     spec.callback = introAudioCallback;
     spec.userdata = NULL;

    SDL_OpenAudio(&spec, &retFmt);
  
   // SDL_OpenAudio(&spec, &rspec);
    SDL_PauseAudio(0);

    /* Let the sound run for a bit... */
    SDL_Delay(10 * 1000);

    /* We're done, so mute the audio and clean it up. */
    SDL_PauseAudio(1);
    SDL_CloseAudio();

    return 0;
}

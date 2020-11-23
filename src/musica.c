void tocar_musica(char const nome[40], int loop){

    Mix_Chunk *som = NULL;
    int canal;
    int canal_audio=2;
    int taxa_audio = 22050;
    Uint16 formato_audio = AUDIO_S16SYS;
    int audio_buffers = 4096;
    if(Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0) {
            printf("Não pode inicializar audio: %s\n", Mix_GetError());
    }
   som = Mix_LoadWAV(nome);
    if(som == NULL) {
            printf("Não pode inicializar audio: %s\n", Mix_GetError());
    }
   Mix_HaltChannel(-1);
   canal = Mix_PlayChannel( -1, som, loop);
    if(canal == -1) {
            printf("Não pode inicializar audio: %s\n", Mix_GetError());
    }
}

void parar_musica(){

  Mix_HaltChannel(-1);

}
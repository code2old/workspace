#include <stdio.h>
#ifdef __cplusplus
extern "C"
{
#endif 

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"

#ifdef __cplusplus
}
#endif

#include "SDL.h"

#define SDL_USEREVENT_REFRESH (SDL_USEREVENT + 1)

static bool s_playing_exit  = false;
static bool s_playing_pause = false;

// ����opaque����Ĳ���֡�ʲ��������̶����ʱ�䷢��ˢ���¼�
static int sdl_thread_handle_refreshing(void *opaque) {
    SDL_Event *sdl_event;
    int frame_rate = *((int *)opaque);
    int interval = (frame_rate > 0) ? 1000 / frame_rate : 40;
}

int simple_video_play2(int argc, char *argv[]) {

}
/**
 * @file
 * API example for demuxing, decoding, filtering, encoding and muxing
 * @example transcoding.c
 */
 #include "libavcodec/avcodec.h"
 #include "libavformat/avformat.h"
 #include "libavfilter/avfiltergraph.h"
 #include "libavfilter/buffersink.h"
 #include "libavutil/opt.h"
 #include "libavutil/pixdesc.h"

 static AVFormatContext *ifmt_ctx;
 static AVFormatContext *ofmt_ctx;

 typedef struct FilteringContext {
     AVFilterContext *buffersink_ctx;
     AVFilterContext *buffersrc_ctx;
     AVFilterGraph   *filter_graph;
 } FilteringContext; 

 static FilteringContext *filter_ctx;

 typedef struct StreamContext {
     AVCodecContext *dec_ctx;
     AVCodecContext *enc_ctx;
 } StreamContext;

 static StreamContext *stream_ctx;

 static int open_input_file(const char *filename) {
     int ret;
     unsigned int i;
     ifmt_ctx = NULL;
     if ((ret = avformat_open_input(&ifmt_ctx, filename, NULL, NULL)) < 0) {
         av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
     }
     if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0) {
         av_log(NULL, AV_LOG_ERROR, "Cnanot find stream information\n");
         return ret;
     }
     
     stream_ctx = av_mallocz_array(ifmt_ctx->nb_streams, sizeof(*stream_ctx));
     if (!stream_ctx) {
         return AVERROR(ENOMEM);
     }

     for (i=0; i<ifmt_ctx->nb_streams; ++i) {
         AVStream *stream = ifmt_ctx->streams[i];
     }
 }
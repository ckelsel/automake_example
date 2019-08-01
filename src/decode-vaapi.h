//
//  decode-vaapi.h
//
//  Created by XieKunming on 2019/07/15
//  Copyright (C) 2019 Nanjing Astute Software Technology Co., Ltd. All rights reserved.
//

#ifndef __DECODE_VAAPI_H__
#define __DECODE_VAAPI_H__

// v1.1

#if 0
#include "channel-display-priv.h"
#else

#include <pixman.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/pixdesc.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/common.h>

typedef struct _TSMFFFmpegDecoder2
{
    AVCodecContext* codec_context;
    AVCodec* codec;
} TSMFFFmpegDecoder2;

typedef struct Ring2 RingItem2;
typedef struct Ring2 {
    RingItem2 *prev;
    RingItem2 *next;
} Ring2;

struct display_stream2;

typedef struct SpiceRect2 {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
} SpiceRect2;

typedef pixman_region32_t QRegion2;

typedef struct stream_decode_frame2
{
    RingItem2 link;
	struct display_stream2 *st;
    SpiceRect2 dest;
	int format;		//PIX_FMT_YUV420P(0)  PIX_FMT_NV12(25)
	int data_width;
	int data_height;
	int refresh_width;
	int refresh_height;
	int top_down_flag;	//0
	int have_region;
	QRegion2 clip;
	int sized_stream;
    uint8_t * y;
    uint8_t * u;
    uint8_t * v;
    AVFrame * frame;
}stream_decode_frame2;
#endif

/**
 * @brief 测试VAAPI硬解是否支持
 *
 * @return 0支持，-1不支持
 */
int is_support_vaapi(void);

/**
 * @brief 硬解码
 *
 * @param decoder
 * @param pkt 待解码的帧
 * @param frame 解码后的帧
 *
 * @return 0成功，-1失败
 */
int hw_vaapi_decode(TSMFFFmpegDecoder2 *decoder, AVPacket *pkt, stream_decode_frame2 *frame);

/**
 * @brief 初始化硬解码器
 *
 * @param decoder 解码模块
 *
 * @return 0成功，-1失败
 */
int hw_vaapi_init(TSMFFFmpegDecoder2 *decoder);

/**
 * @brief 销毁硬解码器
 *
 * @param decoder
 */
void hw_vaapi_destroy(TSMFFFmpegDecoder2 *decoder);

#endif // __DECODE_VAAPI_H__

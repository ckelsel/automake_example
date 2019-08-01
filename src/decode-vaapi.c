//
//  decode-vaapi.c
//
//  Created by XieKunming on 2019/07/15
//  Copyright (C) 2019 Nanjing Astute Software Technology Co., Ltd. All rights reserved.
//

#if 0
#include "spice-client.h"
#include "spice-common.h"
#endif
#include "decode-vaapi.h"

int is_support_vaapi(void)
{
    return -1;
}

int hw_vaapi_decode(TSMFFFmpegDecoder2 *decoder, AVPacket *pkt, stream_decode_frame2 *frame)
{
    return -1;
}

int hw_vaapi_init(TSMFFFmpegDecoder2 *decoder)
{
    return -1;
}

void hw_vaapi_destroy(TSMFFFmpegDecoder2 *decoder)
{
}

/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef __Q6_ASM_H__
#define __Q6_ASM_H__
#include <mach/qdsp6v2/apr.h>
#include <sound/apr_audio.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define IN 0x000
#define OUT 0x001
#define CH_MODE_MONO 0x001
#define CH_MODE_STEREO 0x002
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_LINEAR_PCM 0x0000
#define FORMAT_DTMF 0x0001
#define FORMAT_ADPCM 0x0002
#define FORMAT_YADPCM 0x0003
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_MP3 0x0004
#define FORMAT_MPEG4_AAC 0x0005
#define FORMAT_AMRNB 0x0006
#define FORMAT_AMRWB 0x0007
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_V13K 0x0008
#define FORMAT_EVRC 0x0009
#define FORMAT_EVRCB 0x000a
#define FORMAT_EVRCWB 0x000b
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_MIDI 0x000c
#define FORMAT_SBC 0x000d
#define FORMAT_WMA_V10PRO 0x000e
#define FORMAT_WMA_V9 0x000f
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_AMR_WB_PLUS 0x0010
#define FORMAT_MPEG4_MULTI_AAC 0x0011
#define FORMAT_MULTI_CHANNEL_LINEAR_PCM 0x0012
#define FORMAT_AC3 0x0013
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_DTS 0x0014
#define FORMAT_EAC3 0x0015
#define FORMAT_ATRAC 0x0016
#define FORMAT_MAT 0x0017
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define FORMAT_AAC 0x0018
#define FORMAT_DTS_LBR 0x0019
#define ENCDEC_SBCBITRATE 0x0001
#define ENCDEC_IMMEDIATE_DECODE 0x0002
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define ENCDEC_CFG_BLK 0x0003
#define CMD_PAUSE 0x0001
#define CMD_FLUSH 0x0002
#define CMD_EOS 0x0003
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CMD_CLOSE 0x0004
#define CMD_OUT_FLUSH 0x0005
#define STREAM_PRIORITY_NORMAL 0x0000
#define STREAM_PRIORITY_LOW 0x0001
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define STREAM_PRIORITY_HIGH 0x0002
#define BUFFER_META_ENABLE 0x0010
#define SR_CM_NOTIFY_ENABLE 0x0004
#define ASYNC_IO_MODE 0x0002
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define SYNC_IO_MODE 0x0001
#define NO_TIMESTAMP 0xFF00
#define SET_TIMESTAMP 0x0000
#define SOFT_PAUSE_ENABLE 1
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define SOFT_PAUSE_DISABLE 0
#define SESSION_MAX 0x08
#define SOFT_PAUSE_PERIOD 30  
#define SOFT_PAUSE_STEP_LINEAR 0  
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define SOFT_PAUSE_STEP 2000  
enum {
 SOFT_PAUSE_CURVE_LINEAR = 0,
 SOFT_PAUSE_CURVE_EXP,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SOFT_PAUSE_CURVE_LOG,
};
#define SOFT_VOLUME_PERIOD 30  
#define SOFT_VOLUME_STEP_LINEAR 0  
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define SOFT_VOLUME_STEP 2000  
enum {
 SOFT_VOLUME_CURVE_LINEAR = 0,
 SOFT_VOLUME_CURVE_EXP,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 SOFT_VOLUME_CURVE_LOG,
};
typedef void (*app_cb)(uint32_t opcode, uint32_t token,
 uint32_t *payload, void *priv);
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct audio_buffer {
 dma_addr_t phys;
 void *data;
 uint32_t used;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t size;
 uint32_t actual_size;
 void *mem_buffer;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct audio_aio_write_param {
 unsigned long paddr;
 uint32_t uid;
 uint32_t len;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t msw_ts;
 uint32_t lsw_ts;
 uint32_t flags;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct audio_aio_read_param {
 unsigned long paddr;
 uint32_t len;
 uint32_t uid;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct audio_port_data {
 struct audio_buffer *buf;
 uint32_t max_buf_cnt;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t dsp_buf;
 uint32_t cpu_buf;
 struct mutex lock;
 spinlock_t dsp_lock;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct audio_client {
 int session;
 struct audio_port_data port[2];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct apr_svc *apr;
 struct mutex cmd_lock;
 atomic_t cmd_state;
 atomic_t time_flag;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 atomic_t nowait_cmd_cnt;
 wait_queue_head_t cmd_wait;
 wait_queue_head_t time_wait;
 app_cb cb;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void *priv;
 uint32_t io_mode;
 uint64_t time_stamp;
 atomic_t cmd_response;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct q6asm_ops {
 int (*get_q6_effect) (void);
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct audio_client *q6asm_audio_client_alloc(app_cb cb, void *priv);
struct audio_client *q6asm_get_audio_client(int session_id);
#endif

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
#ifndef __ASM__ARCH_CAMERA_H
#define __ASM__ARCH_CAMERA_H
#include <linux/list.h>
#include <linux/poll.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/wakelock.h>
#include <linux/regulator/consumer.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#include "linux/types.h"
#include <mach/board.h>
#include <media/msm_camera.h>
#include <mach/msm_subsystem_map.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#include <linux/ion.h>
#define CONFIG_MSM_CAMERA_DEBUG
#define CDBG(fmt, args...) do { } while (0)
#ifdef pr_err
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#undef pr_err
#endif
#define pr_err(fmt, args...)   printk(KERN_ERR "[CAM][ERR] " pr_fmt(fmt), ## args)
#ifdef pr_info
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#undef pr_info
#endif
#define pr_info(fmt, args...)   printk(KERN_INFO "[CAM] " pr_fmt(fmt), ## args)
#define PAD_TO_2K(a, b) ((!b) ? a : (((a)+2047) & ~2047))
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define MSM_CAMERA_MSG 0
#define MSM_CAMERA_EVT 1
#define NUM_WB_EXP_NEUTRAL_REGION_LINES 4
#define NUM_WB_EXP_STAT_OUTPUT_BUFFERS 3
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define NUM_AUTOFOCUS_MULTI_WINDOW_GRIDS 16
#define NUM_STAT_OUTPUT_BUFFERS 3
#define NUM_AF_STAT_OUTPUT_BUFFERS 3
#define max_control_command_size 512
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CROP_LEN 36
enum vfe_mode_of_operation{
 VFE_MODE_OF_OPERATION_CONTINUOUS,
 VFE_MODE_OF_OPERATION_SNAPSHOT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MODE_OF_OPERATION_VIDEO,
 VFE_MODE_OF_OPERATION_RAW_SNAPSHOT,
 VFE_MODE_OF_OPERATION_ZSL,
 VFE_MODE_OF_OPERATION_JPEG_SNAPSHOT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_LAST_MODE_OF_OPERATION_ENUM
};
enum msm_queue {
 MSM_CAM_Q_CTRL,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_CAM_Q_VFE_EVT,
 MSM_CAM_Q_VFE_MSG,
 MSM_CAM_Q_V4L2_REQ,
 MSM_CAM_Q_VPE_MSG,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_CAM_Q_PP_MSG,
};
enum vfe_resp_msg {
 VFE_EVENT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_GENERAL,
 VFE_MSG_SNAPSHOT,
 VFE_MSG_OUTPUT_P,
 VFE_MSG_OUTPUT_T,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_OUTPUT_S,
 VFE_MSG_OUTPUT_V,
 VFE_MSG_STATS_AEC,
 VFE_MSG_STATS_AF,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_STATS_AWB,
 VFE_MSG_STATS_RS,
 VFE_MSG_STATS_CS,
 VFE_MSG_STATS_IHIST,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_STATS_SKIN,
 VFE_MSG_STATS_WE,
 VFE_MSG_SYNC_TIMER0,
 VFE_MSG_SYNC_TIMER1,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_SYNC_TIMER2,
 VFE_MSG_COMMON,
 VFE_MSG_V32_START,
 VFE_MSG_V32_START_RECORDING,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_V32_CAPTURE,
 VFE_MSG_V32_JPEG_CAPTURE,
 VFE_MSG_OUTPUT_IRQ,
 VFE_MSG_V2X_PREVIEW,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VFE_MSG_V2X_CAPTURE,
 VFE_MSG_OUTPUT_PRIMARY,
 VFE_MSG_OUTPUT_SECONDARY,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum vpe_resp_msg {
 VPE_MSG_GENERAL,
 VPE_MSG_OUTPUT_V,
 VPE_MSG_OUTPUT_ST_L,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VPE_MSG_OUTPUT_ST_R,
};
enum msm_stereo_state {
 STEREO_VIDEO_IDLE,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 STEREO_VIDEO_ACTIVE,
 STEREO_SNAP_IDLE,
 STEREO_SNAP_STARTED,
 STEREO_SNAP_BUFFER1_PROCESSING,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 STEREO_SNAP_BUFFER2_PROCESSING,
 STEREO_RAW_SNAP_IDLE,
 STEREO_RAW_SNAP_STARTED,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_ispif_intftype {
 PIX0,
 RDI0,
 PIX1,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 RDI1,
 PIX2,
 RDI2,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_ispif_vc {
 VC0,
 VC1,
 VC2,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VC3,
};
enum msm_ispif_cid {
 CID0,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID1,
 CID2,
 CID3,
 CID4,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID5,
 CID6,
 CID7,
 CID8,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID9,
 CID10,
 CID11,
 CID12,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CID13,
 CID14,
 CID15,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_ispif_params {
 uint8_t intftype;
 uint16_t cid_mask;
 uint8_t csid;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_ispif_params_list {
 uint32_t len;
 struct msm_ispif_params params[3];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_vpe_phy_info {
 uint32_t sbuf_phy;
 uint32_t planar0_off;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t planar1_off;
 uint32_t planar2_off;
 uint32_t p0_phy;
 uint32_t p1_phy;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t p2_phy;
 uint8_t output_id;
 uint32_t frame_id;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camera_csid_vc_cfg {
 uint8_t cid;
 uint8_t dt;
 uint8_t decode_format;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_camera_csid_lut_params {
 uint8_t num_cid;
 struct msm_camera_csid_vc_cfg *vc_cfg;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_camera_csid_params {
 uint8_t lane_cnt;
 uint8_t lane_assign;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_camera_csid_lut_params lut_params;
};
struct msm_camera_csiphy_params {
 uint8_t lane_cnt;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint8_t settle_cnt;
 uint8_t lane_mask;
};
struct msm_camera_csi2_params {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_camera_csid_params csid_params;
 struct msm_camera_csiphy_params csiphy_params;
};
#define VFE31_OUTPUT_MODE_PT (0x1 << 0)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VFE31_OUTPUT_MODE_S (0x1 << 1)
#define VFE31_OUTPUT_MODE_V (0x1 << 2)
#define VFE31_OUTPUT_MODE_P (0x1 << 3)
#define VFE31_OUTPUT_MODE_T (0x1 << 4)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VFE31_OUTPUT_MODE_P_ALL_CHNLS (0x1 << 5)
#define CSI_EMBED_DATA 0x12
#define CSI_RESERVED_DATA_0 0x13
#define CSI_YUV422_8 0x1E
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CSI_RAW8 0x2A
#define CSI_RAW10 0x2B
#define CSI_RAW12 0x2C
#define CSI_DECODE_6BIT 0
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define CSI_DECODE_8BIT 1
#define CSI_DECODE_10BIT 2
#define CSI_DECODE_DPCM_10_8_10 5
struct msm_vfe_phy_info {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t sbuf_phy;
 uint32_t planar0_off;
 uint32_t planar1_off;
 uint32_t planar2_off;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t p0_phy;
 uint32_t p1_phy;
 uint32_t p2_phy;
 uint8_t output_id;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t frame_id;
};
struct msm_vfe_stats_msg {
 uint8_t awb_ymin;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t aec_buff;
 uint32_t awb_buff;
 uint32_t af_buff;
 uint32_t ihist_buff;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t rs_buff;
 uint32_t cs_buff;
 uint32_t skin_buff;
 uint32_t status_bits;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t frame_id;
};
struct video_crop_t{
 uint32_t in1_w;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t out1_w;
 uint32_t in1_h;
 uint32_t out1_h;
 uint32_t in2_w;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t out2_w;
 uint32_t in2_h;
 uint32_t out2_h;
 uint8_t update_flag;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_vpe_buf_info {
 uint32_t p0_phy;
 uint32_t p1_phy;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct timespec ts;
 uint32_t frame_id;
 struct video_crop_t vpe_crop;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_vfe_resp {
 enum vfe_resp_msg type;
 struct msm_cam_evt_msg evt_msg;
 struct msm_vfe_phy_info phy;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_vfe_stats_msg stats_msg;
 struct msm_vpe_buf_info vpe_bf;
 void *extdata;
 int32_t extlen;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_vpe_resp {
 enum vpe_resp_msg type;
 struct msm_cam_evt_msg evt_msg;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_vpe_phy_info phy;
 void *extdata;
 int32_t extlen;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_vpe_callback {
 void (*vpe_resp)(struct msm_vpe_resp *,
 enum msm_queue, void *syncdata,
 void *time_stamp, gfp_t gfp);
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void* (*vpe_alloc)(int, void *syncdata, gfp_t gfp);
 void (*vpe_free)(void *ptr);
};
struct msm_vfe_callback {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void (*vfe_resp)(struct msm_vfe_resp *,
 enum msm_queue, void *syncdata,
 gfp_t gfp);
 void* (*vfe_alloc)(int, void *syncdata, gfp_t gfp);
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void (*vfe_free)(void *ptr);
};
struct msm_camvfe_fn {
 int (*vfe_init)(struct msm_vfe_callback *,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct platform_device *);
 int (*vfe_enable)(struct camera_enable_cmd *);
 int (*vfe_config)(struct msm_vfe_cfg_cmd *, void *);
 int (*vfe_disable)(struct camera_enable_cmd *,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct platform_device *dev);
 void (*vfe_release)(struct platform_device *);
 void (*vfe_stop)(void);
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camvfe_params {
 struct msm_vfe_cfg_cmd *vfe_cfg;
 void *data;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_mctl_pp_params {
 struct msm_mctl_pp_cmd *cmd;
 void *data;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_camvpe_fn {
 int (*vpe_reg)(struct msm_vpe_callback *);
 int (*vpe_cfg_update) (void *);
 void (*send_frame_to_vpe) (uint32_t planar0_off, uint32_t planar1_off,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct timespec *ts, int output_id);
 int (*vpe_config)(struct msm_vpe_cfg_cmd *, void *);
 void (*vpe_cfg_offset)(int frame_pack, uint32_t pyaddr,
 uint32_t pcbcraddr, struct timespec *ts, int output_id,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_st_half st_half, int frameid);
 int *dis;
};
struct msm_sensor_ctrl {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int (*s_init)(const struct msm_camera_sensor_info *);
 int (*s_release)(void);
 int (*s_config)(void __user *);
 enum msm_camera_type s_camera_type;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t s_mount_angle;
 enum msm_st_frame_packing s_video_packing;
 enum msm_st_frame_packing s_snap_packing;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_actuator_ctrl {
 int (*a_init_table)(void);
 int (*a_power_up)(void *);
 int (*a_power_down)(void *);
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int (*a_create_subdevice)(void *, void *);
 int (*a_config)(void __user *);
};
struct msm_strobe_flash_ctrl {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int (*strobe_flash_init)
 (struct msm_camera_sensor_strobe_flash_data *);
 int (*strobe_flash_release)
 (struct msm_camera_sensor_strobe_flash_data *, int32_t);
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int (*strobe_flash_charge)(int32_t, int32_t, uint32_t);
};
struct msm_queue_cmd {
 struct list_head list_config;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct list_head list_control;
 struct list_head list_frame;
 struct list_head list_pict;
 struct list_head list_vpe_frame;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct list_head list_eventdata;
 enum msm_queue type;
 void *command;
 atomic_t on_heap;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct timespec ts;
 uint32_t error_code;
};
struct msm_device_queue {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct list_head list;
 spinlock_t lock;
 wait_queue_head_t wait;
 int max;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int len;
 const char *name;
};
struct msm_mctl_stats_t {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct hlist_head pmem_stats_list;
 spinlock_t pmem_stats_spinlock;
};
struct msm_sync {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct hlist_head pmem_frames;
 struct hlist_head pmem_stats;
 struct msm_device_queue event_q;
 struct msm_device_queue frame_q;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int unblock_poll_frame;
 int unblock_poll_pic_frame;
 struct msm_device_queue pict_q;
 int get_pic_abort;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_device_queue vpe_q;
 struct msm_camera_sensor_info *sdata;
 struct msm_camvfe_fn vfefn;
 struct msm_camvpe_fn vpefn;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_sensor_ctrl sctrl;
 struct msm_strobe_flash_ctrl sfctrl;
 struct msm_actuator_ctrl actctrl;
 struct wake_lock wake_lock;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct platform_device *pdev;
 int16_t ignore_qcmd_type;
 uint8_t ignore_qcmd;
 uint8_t opencnt;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 void *cropinfo;
 int croplen;
 int core_powered_on;
 struct fd_roi_info fdroiinfo;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 atomic_t vpe_enable;
 uint32_t pp_mask;
 uint8_t pp_frame_avail;
 struct msm_queue_cmd *pp_prev;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_queue_cmd *pp_snap;
 struct msm_queue_cmd *pp_thumb;
 int video_fd;
 const char *apps_id;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct mutex lock;
 struct list_head list;
 uint8_t liveshot_enabled;
 struct msm_cam_v4l2_device *pcam_sync;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint8_t stereocam_enabled;
 struct msm_queue_cmd *pp_stereocam;
 struct msm_queue_cmd *pp_stereocam2;
 struct msm_queue_cmd *pp_stereosnap;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 enum msm_stereo_state stereo_state;
 int stcam_quality_ind;
 uint32_t stcam_conv_value;
 spinlock_t pmem_frame_spinlock;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 spinlock_t pmem_stats_spinlock;
 spinlock_t abort_pict_lock;
 int snap_count;
 int thumb_count;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
#define MSM_APPS_ID_V4L2 "msm_v4l2"
#define MSM_APPS_ID_PROP "msm_qct"
struct msm_cam_device {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_sync *sync;
 struct device *device;
 struct cdev cdev;
 atomic_t opened;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_control_device {
 struct msm_cam_device *pmsm;
 uint8_t ctrl_data[max_control_command_size];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_ctrl_cmd ctrl;
 struct msm_queue_cmd qcmd;
 struct msm_device_queue ctrl_q;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct register_address_value_pair {
 uint16_t register_address;
 uint16_t register_value;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_pmem_region {
 struct hlist_node list;
 unsigned long paddr;
 unsigned long len;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct file *file;
 struct msm_pmem_info info;
 struct ion_handle *handle;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct axidata {
 uint32_t bufnum1;
 uint32_t bufnum2;
 uint32_t bufnum3;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct msm_pmem_region *region;
};
enum msm_camio_clk_type {
 CAMIO_VFE_MDC_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_MDC_CLK,
 CAMIO_VFE_CLK,
 CAMIO_VFE_AXI_CLK,
 CAMIO_VFE_CAMIF_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_VFE_PBDG_CLK,
 CAMIO_CAM_MCLK_CLK,
 CAMIO_CAMIF_PAD_PBDG_CLK,
 CAMIO_CSI0_VFE_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_CSI1_VFE_CLK,
 CAMIO_VFE_PCLK,
 CAMIO_CSI_SRC_CLK,
 CAMIO_CSI0_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_CSI1_CLK,
 CAMIO_CSI0_PCLK,
 CAMIO_CSI1_PCLK,
 CAMIO_CSI1_SRC_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_CSI_PIX_CLK,
 CAMIO_CSI_PIX1_CLK,
 CAMIO_CSI_RDI_CLK,
 CAMIO_CSI_RDI1_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_CSI_RDI2_CLK,
 CAMIO_CSIPHY0_TIMER_CLK,
 CAMIO_CSIPHY1_TIMER_CLK,
 CAMIO_JPEG_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_JPEG_PCLK,
 CAMIO_VPE_CLK,
 CAMIO_VPE_PCLK,
 CAMIO_CSI0_PHY_CLK,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 CAMIO_CSI1_PHY_CLK,
 CAMIO_CSIPHY_TIMER_SRC_CLK,
 CAMIO_IMEM_CLK,
 CAMIO_MAX_CLK
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
enum msm_camio_clk_src_type {
 MSM_CAMIO_CLK_SRC_INTERNAL,
 MSM_CAMIO_CLK_SRC_EXTERNAL,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 MSM_CAMIO_CLK_SRC_MAX
};
enum msm_s_test_mode {
 S_TEST_OFF,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 S_TEST_1,
 S_TEST_2,
 S_TEST_3
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum msm_s_resolution {
 S_QTR_SIZE,
 S_FULL_SIZE,
 S_INVALID_SIZE
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
enum msm_s_reg_update {
 S_REG_INIT,
 S_UPDATE_PERIODIC,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 S_UPDATE_ALL,
 S_UPDATE_INVALID
};
enum msm_s_setting {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 S_RES_PREVIEW,
 S_RES_CAPTURE
};
enum msm_bus_perf_setting {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 S_INIT,
 S_PREVIEW,
 S_VIDEO,
 S_CAPTURE,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 S_ZSL,
 S_STEREO_VIDEO,
 S_STEREO_CAPTURE,
 S_DEFAULT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 S_EXIT
};
struct msm_cam_clk_info {
 const char *clk_name;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 long clk_rate;
};
#endif

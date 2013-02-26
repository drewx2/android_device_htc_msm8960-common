/* Copyright (c) 2012-2013, The Linux Foundataion. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
*       copyright notice, this list of conditions and the following
*       disclaimer in the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of The Linux Foundation nor the names of its
*       contributors may be used to endorse or promote products derived
*       from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
* ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
* IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#define LOG_TAG "QCameraStream"

#include <utils/Log.h>
#include <utils/Errors.h>
#include "QCamera2HWI.h"
#include "QCameraStream.h"

namespace qcamera {

/*===========================================================================
 * FUNCTION   : get_bufs
 *
 * DESCRIPTION: static function entry to allocate stream buffers
 *
 * PARAMETERS :
 *   @offset     : offset info of stream buffers
 *   @num_bufs   : number of buffers allocated
 *   @initial_reg_flag: flag to indicate if buffer needs to be registered
 *                      at kernel initially
 *   @bufs       : output of allocated buffers
 *   @ops_tbl    : ptr to buf mapping/unmapping ops
 *   @user_data  : user data ptr of ops_tbl
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::get_bufs(
                     cam_frame_len_offset_t *offset,
                     uint8_t *num_bufs,
                     uint8_t **initial_reg_flag,
                     mm_camera_buf_def_t **bufs,
                     mm_camera_map_unmap_ops_tbl_t *ops_tbl,
                     void *user_data)
{
    QCameraStream *stream = reinterpret_cast<QCameraStream *>(user_data);
    if (!stream) {
        ALOGE("getBufs invalid stream pointer");
        return NO_MEMORY;
    }
    return stream->getBufs(offset, num_bufs, initial_reg_flag, bufs, ops_tbl);
}

/*===========================================================================
 * FUNCTION   : put_bufs
 *
 * DESCRIPTION: static function entry to deallocate stream buffers
 *
 * PARAMETERS :
 *   @ops_tbl    : ptr to buf mapping/unmapping ops
 *   @user_data  : user data ptr of ops_tbl
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::put_bufs(
                     mm_camera_map_unmap_ops_tbl_t *ops_tbl,
                     void *user_data)
{
    QCameraStream *stream = reinterpret_cast<QCameraStream *>(user_data);
    if (!stream) {
        ALOGE("putBufs invalid stream pointer");
        return NO_MEMORY;
    }
    return stream->putBufs(ops_tbl);
}

/*===========================================================================
 * FUNCTION   : QCameraStream
 *
 * DESCRIPTION: constructor of QCameraStream
 *
 * PARAMETERS :
 *   @allocator  : memory allocator obj
 *   @camHandle  : camera handle
 *   @chId       : channel handle
 *   @camOps     : ptr to camera ops table
 *   @paddingInfo: ptr to padding info
 *
 * RETURN     : None
 *==========================================================================*/
QCameraStream::QCameraStream(QCameraAllocator &allocator,
                             uint32_t camHandle,
                             uint32_t chId,
                             mm_camera_ops_t *camOps,
                             cam_padding_info_t *paddingInfo) :
        mCamHandle(camHandle),
        mChannelHandle(chId),
        mHandle(0),
        mCamOps(camOps),
        mStreamInfo(NULL),
        mNumBufs(0),
        mDataCB(NULL),
        mStreamInfoBuf(NULL),
        mStreamBufs(NULL),
        mAllocator(allocator),
        mBufDefs(NULL)
{
    mMemVtbl.user_data = this;
    mMemVtbl.get_bufs = get_bufs;
    mMemVtbl.put_bufs = put_bufs;
    memset(&mFrameLenOffset, 0, sizeof(mFrameLenOffset));
    memcpy(&mPaddingInfo, paddingInfo, sizeof(cam_padding_info_t));
}

/*===========================================================================
 * FUNCTION   : ~QCameraStream
 *
 * DESCRIPTION: deconstructor of QCameraStream
 *
 * PARAMETERS : None
 *
 * RETURN     : None
 *==========================================================================*/
QCameraStream::~QCameraStream()
{
    if (mStreamInfoBuf != NULL) {
        int rc = mCamOps->unmap_stream_buf(mCamHandle,
                    mChannelHandle, mHandle, CAM_MAPPING_BUF_TYPE_STREAM_INFO, 0, -1);
        if (rc < 0) {
            ALOGE("Failed to map stream info buffer");
        }
        mStreamInfoBuf->deallocate();
        delete mStreamInfoBuf;
        mStreamInfoBuf = NULL;
    }

    // delete stream
    if (mHandle > 0) {
        mCamOps->delete_stream(mCamHandle, mChannelHandle, mHandle);
        mHandle = 0;
    }
}

/*===========================================================================
 * FUNCTION   : init
 *
 * DESCRIPTION: initialize stream obj
 *
 * PARAMETERS :
 *   @stream_type : type of the stream
 *   @stream_cb   : stream data notify callback. Can be NULL if not needed
 *   @userdata    : user data ptr
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::init(cam_stream_type_t stream_type,
                         stream_cb_routine stream_cb, void *userdata)
{
    int32_t rc = OK;
    mm_camera_stream_config_t stream_config;

    mHandle = mCamOps->add_stream(mCamHandle, mChannelHandle);
    if (!mHandle) {
        ALOGE("add_stream failed");
        rc = UNKNOWN_ERROR;
        goto done;
    }

    // Allocate and map stream info memory
    mStreamInfoBuf = mAllocator.allocateStreamInfoBuf(stream_type);
    if (!mStreamInfoBuf) {
        ALOGE("Failed to allocate stream info object");
        goto err1;
    }
    mStreamInfo = reinterpret_cast<cam_stream_info_t *>(mStreamInfoBuf->getPtr(0));

    rc = mCamOps->map_stream_buf(mCamHandle,
                mChannelHandle, mHandle, CAM_MAPPING_BUF_TYPE_STREAM_INFO,
                0, -1, mStreamInfoBuf->getFd(0), mStreamInfoBuf->getSize(0));
    if (rc < 0) {
        ALOGE("Failed to map stream info buffer");
        goto err2;
    }

    // Configure the stream
    stream_config.stream_info = mStreamInfo;
    stream_config.mem_vtbl = mMemVtbl;
    stream_config.stream_cb = dataNotifyCB;
    stream_config.padding_info = mPaddingInfo;
    stream_config.userdata = this;
    rc = mCamOps->config_stream(mCamHandle,
                mChannelHandle, mHandle, &stream_config);
    if (rc < 0) {
        ALOGE("Failed to config stream, rc = %d", rc);
        goto err3;
    }

    mDataCB = stream_cb;
    mUserData = userdata;
    return 0;

err3:
    mCamOps->unmap_stream_buf(mCamHandle,
                mChannelHandle, mHandle, CAM_MAPPING_BUF_TYPE_STREAM_INFO, 0, -1);

err2:
    mStreamInfoBuf->deallocate();
    delete mStreamInfoBuf;
    mStreamInfoBuf = NULL;
err1:
    mCamOps->delete_stream(mCamHandle, mChannelHandle, mHandle);
    mHandle = 0;
done:
    return rc;
}

/*===========================================================================
 * FUNCTION   : start
 *
 * DESCRIPTION: start stream. Will start main stream thread to handle stream
 *              related ops.
 *
 * PARAMETERS : none
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::start()
{
    int32_t rc = 0;
    rc = mProcTh.launch(dataProcRoutine, this);
    return rc;
}

/*===========================================================================
 * FUNCTION   : stop
 *
 * DESCRIPTION: stop stream. Will stop main stream thread
 *
 * PARAMETERS : none
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::stop()
{
    int32_t rc = 0;
    rc = mProcTh.exit();
    return rc;
}

/*===========================================================================
 * FUNCTION   : processZoomDone
 *
 * DESCRIPTION: process zoom done event
 *
 * PARAMETERS :
 *   @previewWindoe : preview window ops table to set preview crop window
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::processZoomDone(preview_stream_ops_t *previewWindow)
{
    int32_t rc = 0;

    // get stream param for crop info
    mStreamInfo->parm_buf.is_crop_valid = TRUE;
    rc = mCamOps->get_stream_parms(mCamHandle,
                                   mChannelHandle,
                                   mHandle,
                                   &mStreamInfo->parm_buf);


    // update preview window crop if it's preview/postview stream
    if ( (previewWindow != NULL) &&
         (mStreamInfo->stream_type == CAM_STREAM_TYPE_PREVIEW ||
          mStreamInfo->stream_type == CAM_STREAM_TYPE_POSTVIEW) ) {
        rc = previewWindow->set_crop(previewWindow,
                                     mStreamInfo->parm_buf.crop.left,
                                     mStreamInfo->parm_buf.crop.top,
                                     mStreamInfo->parm_buf.crop.width,
                                     mStreamInfo->parm_buf.crop.height);
    }

    return rc;
}

/*===========================================================================
 * FUNCTION   : processDataNotify
 *
 * DESCRIPTION: process stream data notify
 *
 * PARAMETERS :
 *   @frame   : stream frame received
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::processDataNotify(mm_camera_super_buf_t *frame)
{
    ALOGI("%s:\n", __func__);
    mDataQ.enqueue((void *)frame);
    return mProcTh.sendCmd(CAMERA_CMD_TYPE_DO_NEXT_JOB, FALSE, FALSE);
}

/*===========================================================================
 * FUNCTION   : dataNotifyCB
 *
 * DESCRIPTION: callback for data notify. This function is registered with
 *              mm-camera-interface to handle data notify
 *
 * PARAMETERS :
 *   @recvd_frame   : stream frame received
 *   userdata       : user data ptr
 *
 * RETURN     : none
 *==========================================================================*/
void QCameraStream::dataNotifyCB(mm_camera_super_buf_t *recvd_frame,
                                 void *userdata)
{
    ALOGI("%s:\n", __func__);
    QCameraStream* stream = (QCameraStream *)userdata;
    if (stream == NULL ||
        recvd_frame == NULL ||
        recvd_frame->bufs[0] == NULL ||
        recvd_frame->bufs[0]->stream_id != stream->getMyHandle()) {
        ALOGE("%s: Not a valid stream to handle buf", __func__);
        return;
    }

    mm_camera_super_buf_t *frame =
        (mm_camera_super_buf_t *)malloc(sizeof(mm_camera_super_buf_t));
    if (frame == NULL) {
        ALOGE("%s: No mem for mm_camera_buf_def_t", __func__);
        stream->bufDone(recvd_frame->bufs[0]->buf_idx);
        return;
    }
    *frame = *recvd_frame;
    stream->processDataNotify(frame);
    return;
}

/*===========================================================================
 * FUNCTION   : dataProcRoutine
 *
 * DESCRIPTION: function to process data in the main stream thread
 *
 * PARAMETERS :
 *   @data    : user data ptr
 *
 * RETURN     : none
 *==========================================================================*/
void *QCameraStream::dataProcRoutine(void *data)
{
    int running = 1;
    int ret;
    QCameraStream *pme = (QCameraStream *)data;
    QCameraCmdThread *cmdThread = &pme->mProcTh;

    ALOGI("%s: E", __func__);
    do {
        do {
            ret = cam_sem_wait(&cmdThread->cmd_sem);
            if (ret != 0 && errno != EINVAL) {
                ALOGE("%s: cam_sem_wait error (%s)",
                      __func__, strerror(errno));
                return NULL;
            }
        } while (ret != 0);

        // we got notified about new cmd avail in cmd queue
        camera_cmd_type_t cmd = cmdThread->getCmd();
        switch (cmd) {
        case CAMERA_CMD_TYPE_DO_NEXT_JOB:
            {
                ALOGD("%s: Do next job", __func__);
                mm_camera_super_buf_t *frame =
                    (mm_camera_super_buf_t *)pme->mDataQ.dequeue();
                if (NULL != frame) {
                    if (pme->mDataCB != NULL) {
                        pme->mDataCB(frame, pme, pme->mUserData);
                    } else {
                        // no data cb routine, return buf here
                        pme->bufDone(frame->bufs[0]->buf_idx);
                        free(frame);
                    }
                }
            }
            break;
        case CAMERA_CMD_TYPE_EXIT:
            ALOGD("%s: Exit", __func__);
            /* flush data buf queue */
            pme->mDataQ.flush();
            running = 0;
            break;
        default:
            break;
        }
    } while (running);
    ALOGD("%s: X", __func__);
    return NULL;
}

/*===========================================================================
 * FUNCTION   : bufDone
 *
 * DESCRIPTION: return stream buffer to kernel
 *
 * PARAMETERS :
 *   @index   : index of buffer to be returned
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::bufDone(int index)
{
    int32_t rc = NO_ERROR;

    if (index >= mNumBufs || mBufDefs == NULL)
        return BAD_INDEX;

    rc = mCamOps->qbuf(mCamHandle, mChannelHandle, &mBufDefs[index]);
    if (rc < 0)
        return rc;

    mStreamBufs->invalidateCache(index);
    return rc;
}

/*===========================================================================
 * FUNCTION   : bufDone
 *
 * DESCRIPTION: return stream buffer to kernel
 *
 * PARAMETERS :
 *   @opaque    : stream frame/metadata buf to be returned
 *   @isMetaData: flag if returned opaque is a metadatabuf or the real frame ptr
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::bufDone(const void *opaque, bool isMetaData)
{
    int32_t rc = NO_ERROR;

    int index = mStreamBufs->getMatchBufIndex(opaque, isMetaData);
    if (index == -1 || index >= mNumBufs) {
        ALOGE("%s: Cannot find buf for opaque data = %p", __func__, opaque);
        return BAD_INDEX;
    }

    rc = bufDone(index);
    return rc;
}

/*===========================================================================
 * FUNCTION   : getBufs
 *
 * DESCRIPTION: allocate stream buffers
 *
 * PARAMETERS :
 *   @offset     : offset info of stream buffers
 *   @num_bufs   : number of buffers allocated
 *   @initial_reg_flag: flag to indicate if buffer needs to be registered
 *                      at kernel initially
 *   @bufs       : output of allocated buffers
 *   @ops_tbl    : ptr to buf mapping/unmapping ops
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::getBufs(cam_frame_len_offset_t *offset,
                     uint8_t *num_bufs,
                     uint8_t **initial_reg_flag,
                     mm_camera_buf_def_t **bufs,
                     mm_camera_map_unmap_ops_tbl_t *ops_tbl)
{
    int rc = NO_ERROR;
    uint8_t *regFlags;

    if (!ops_tbl) {
        ALOGE("%s: ops_tbl is NULL", __func__);
        return INVALID_OPERATION;
    }

    mFrameLenOffset = *offset;

    //Allocate and map stream info buffer
    mStreamBufs = mAllocator.allocateStreamBuf(mStreamInfo->stream_type,
                                mFrameLenOffset.frame_len);
    if (!mStreamBufs) {
        ALOGE("%s: Failed to allocate stream buffers", __func__);
        return NO_MEMORY;
    }

    mNumBufs = mStreamBufs->getCnt();
    for (int i = 0; i < mNumBufs; i++) {
        rc = ops_tbl->map_ops(i, -1, mStreamBufs->getFd(i),
                mStreamBufs->getSize(i), ops_tbl->userdata);
        if (rc < 0) {
            ALOGE("%s: map_stream_buf failed: %d", __func__, rc);
            for (int j = 0; j < i; j++) {
                ops_tbl->unmap_ops(j, -1, ops_tbl->userdata);
            }
            mStreamBufs->deallocate();
            delete mStreamBufs;
            mStreamBufs = NULL;
            return INVALID_OPERATION;
        }
    }

    //regFlags array is allocated by us, but consumed and freed by mm-camera-interface
    regFlags = (uint8_t *)malloc(sizeof(uint8_t) * mNumBufs);
    if (!regFlags) {
        ALOGE("%s: Out of memory", __func__);
        for (int i = 0; i < mNumBufs; i++) {
            ops_tbl->unmap_ops(i, -1, ops_tbl->userdata);
        }
        mStreamBufs->deallocate();
        delete mStreamBufs;
        mStreamBufs = NULL;
        return NO_MEMORY;
    }

    mBufDefs = (mm_camera_buf_def_t *)malloc(mNumBufs * sizeof(mm_camera_buf_def_t));
    if (mBufDefs == NULL) {
        ALOGE("%s: getRegFlags failed %d", __func__, rc);
        for (int i = 0; i < mNumBufs; i++) {
            ops_tbl->unmap_ops(i, -1, ops_tbl->userdata);
        }
        mStreamBufs->deallocate();
        delete mStreamBufs;
        mStreamBufs = NULL;
        return INVALID_OPERATION;
    }
    for (int i = 0; i < mNumBufs; i++) {
        mStreamBufs->getBufDef(mFrameLenOffset, mBufDefs[i], i);
    }

    rc = mStreamBufs->getRegFlags(regFlags);
    if (rc < 0) {
        ALOGE("%s: getRegFlags failed %d", __func__, rc);
        for (int i = 0; i < mNumBufs; i++) {
            ops_tbl->unmap_ops(i, -1, ops_tbl->userdata);
        }
        mStreamBufs->deallocate();
        delete mStreamBufs;
        mStreamBufs = NULL;
        free(mBufDefs);
        mBufDefs = NULL;
        return INVALID_OPERATION;
    }

    *num_bufs = mNumBufs;
    *initial_reg_flag = regFlags;
    *bufs = mBufDefs;
    return NO_ERROR;
}

/*===========================================================================
 * FUNCTION   : putBufs
 *
 * DESCRIPTION: deallocate stream buffers
 *
 * PARAMETERS :
 *   @ops_tbl    : ptr to buf mapping/unmapping ops
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::putBufs(mm_camera_map_unmap_ops_tbl_t *ops_tbl)
{
    int rc = NO_ERROR;
    for (int i = 0; i < mNumBufs; i++) {
        rc = ops_tbl->unmap_ops(i, -1, ops_tbl->userdata);
        if (rc < 0) {
            ALOGE("%s: map_stream_buf failed: %d", __func__, rc);
        }
    }
    mBufDefs = NULL; // mBufDefs just keep a ptr to the buffer
                     // mm-camera-interface own the buffer, so no need to free
    memset(&mFrameLenOffset, 0, sizeof(mFrameLenOffset));
    mStreamBufs->deallocate();
    delete mStreamBufs;

    return rc;
}

/*===========================================================================
 * FUNCTION   : isTypeOf
 *
 * DESCRIPTION: helper function to determine if the stream is of the queried type
 *
 * PARAMETERS :
 *   @type    : stream type as of queried
 *
 * RETURN     : true/false
 *==========================================================================*/
bool QCameraStream::isTypeOf(cam_stream_type_t type)
{
    if (mStreamInfo != NULL && (mStreamInfo->stream_type == type)) {
        return true;
    } else {
        return false;
    }
}

/*===========================================================================
 * FUNCTION   : getFrameOffset
 *
 * DESCRIPTION: query stream buffer frame offset info
 *
 * PARAMETERS :
 *   @offset  : reference to struct to store the queried frame offset info
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::getFrameOffset(cam_frame_len_offset_t &offset)
{
    offset = mFrameLenOffset;
    return 0;
}

/*===========================================================================
 * FUNCTION   : getCropInfo
 *
 * DESCRIPTION: query crop info of the stream
 *
 * PARAMETERS :
 *   @crop    : reference to struct to store the queried crop info
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::getCropInfo(cam_rect_t &crop)
{
    if (mStreamInfo != NULL) {
        crop = mStreamInfo->parm_buf.crop;
        return 0;
    }
    return -1;
}

/*===========================================================================
 * FUNCTION   : getFrameDimension
 *
 * DESCRIPTION: query stream frame dimension info
 *
 * PARAMETERS :
 *   @dim     : reference to struct to store the queried frame dimension
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::getFrameDimension(cam_dimension_t &dim)
{
    if (mStreamInfo != NULL) {
        dim = mStreamInfo->dim;
        return 0;
    }
    return -1;
}

/*===========================================================================
 * FUNCTION   : getFormat
 *
 * DESCRIPTION: query stream format
 *
 * PARAMETERS :
 *   @fmt     : reference to stream format
 *
 * RETURN     : int32_t type of status
 *              NO_ERROR  -- success
 *              none-zero failure code
 *==========================================================================*/
int32_t QCameraStream::getFormat(cam_format_t &fmt)
{
    if (mStreamInfo != NULL) {
        fmt = mStreamInfo->fmt;
        return 0;
    }
    return -1;
}

}; // namespace qcamera

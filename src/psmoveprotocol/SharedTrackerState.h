#ifndef SHARED_TRACKER_STATE_H
#define SHARED_TRACKER_STATE_H

#include <boost/interprocess/sync/interprocess_mutex.hpp>

struct SharedVideoFrameHeader
{
    //Mutex to protect access to the shared memory
    boost::interprocess::interprocess_mutex mutex;

    int width;
    int height;
    int stride;
    int frame_index;
    // Buffer stored past the end of the header

    const unsigned char *getBuffer() const
    {
        return reinterpret_cast<const unsigned char *>(this) + sizeof(SharedVideoFrameHeader);
    }

    unsigned char *getBufferMutable()
    {
        return const_cast<unsigned char *>(getBuffer());
    }

    static size_t computeVideoBufferSize(int stride, int height)
    {
        return stride*height;
    }

    static size_t computeTotalSize(int stride, int height)
    {
        return sizeof(SharedVideoFrameHeader) + computeVideoBufferSize(stride, height);
    }
};

#endif // SHARED_TRACKER_STATE_H
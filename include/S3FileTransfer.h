#ifndef __S3_FILE_TRANSFER_H__
#define __S3_FILE_TRANSFER_H__

#include "FileTransfer.h"

class S3FileTransfer : public FileTransfer
{
    public:
        S3FileTransfer();
        ~S3FileTransfer();
        void uploadFile(const std::string filepath);
        void downloadFile(const std::string filepath);
};

#endif

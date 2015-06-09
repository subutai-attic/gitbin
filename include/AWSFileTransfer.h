#ifndef __AWS_FILE_TRANSFER_H__
#define __AWS_FILE_TRANSFER_H__

#include "FileTransfer.h"

class AWSFileTransfer : public FileTransfer
{
    public:
        AWSFileTransfer();
        ~AWSFileTransfer();
        void uploadFile(const std::string filepath);
        void downloadFile(const std::string filepath);
};

#endif

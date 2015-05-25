#ifndef __FILE_TRANSFER_H__
#define __FILE_TRANSFER_H__

#include <iostream>
#include <Poco/Process.h>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>

using Poco::Process;
using Poco::ProcessHandle;
using Poco::Pipe;
using Poco::PipeOutputStream;
using Poco::PipeInputStream;

class FileTransfer
{
    public:
        FileTransfer();
        virtual ~FileTransfer();
        virtual void uploadFile(const std::string filepath);
        virtual void downloadFile(const std::string filepath);
        void setTargetUrl(const std::string targetUrl);
    protected:
        std::string _targetUrl;
};

#endif

#ifndef __FILE_TRANSFER_H__
#define __FILE_TRANSFER_H__

#include <Poco/Process.h>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>

#include "Plugin.h"

using Poco::Process;
using Poco::Pipe;
using Poco::PipeOutputStream;
using Poco::PipeInputStream;

class FileTransfer
{
    public:
        FileTransfer();
        virtual ~FileTransfer();
        virtual void uploadFile(const std::string uuid);
        virtual void downloadFile(const std::string uuid);
};

#endif

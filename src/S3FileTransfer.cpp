#include "S3FileTransfer.h"

S3FileTransfer::S3FileTransfer()
{
    // TODO: Check if s3tool scripts are installed
}

S3FileTransfer::~S3FileTransfer()
{

}

void S3FileTransfer::uploadFile(const std::string uuid)
{
    Process::Args args;
    args.push_back(uuid);
    ProcessHandle ph = Process::launch("s3cmd", args, 0, 0, 0);
    if (ph.wait() != 0)
    {
        std::cout << "Failed to upload file to S3" << std::endl;
        return;
    }
}

void S3FileTransfer::downloadFile(const std::string uuid)
{
    Process::Args args;
    args.push_back(uuid);
    ProcessHandle ph = Process::launch("s3cmd", args, 0, 0, 0);
    if (ph.wait() != 0)
    {
        std::cout << "Failed to upload file to S3" << std::endl;
        return;
    }

}

#include "S3FileTransfer.h"

S3FileTransfer::S3FileTransfer()
{
    // TODO: Check if s3tool scripts are installed
}

S3FileTransfer::~S3FileTransfer()
{

}

void S3FileTransfer::uploadFile(const std::string filepath)
{
    Process::Args args;
    args.push_back("put");
    args.push_back(filepath);
    args.push_back(_targetUrl); 
    ProcessHandle ph = Process::launch("s3cmd", args, 0, 0, 0);
    if (ph.wait() != 0)
    {
        std::cout << "Failed to upload file to S3" << std::endl;
        return;
    }
}

void S3FileTransfer::downloadFile(const std::string filepath)
{
    Process::Args args;
    args.push_back("get");
    std::string fullpath(_targetUrl);
    fullpath.append(filepath);
    args.push_back(fullpath);
    args.push_back(filepath);
    ProcessHandle ph = Process::launch("s3cmd", args, 0, 0, 0);
    if (ph.wait() != 0)
    {
        std::cout << "Failed to upload file to S3" << std::endl;
        return;
    }

}

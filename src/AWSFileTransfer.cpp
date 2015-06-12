#include "AWSFileTransfer.h"

const std::string AWSFileTransfer::AWS_TOOL = "aws";

AWSFileTransfer::AWSFileTransfer()
{
    // TODO: Check if s3tool scripts are installed
}

AWSFileTransfer::~AWSFileTransfer()
{

}

void AWSFileTransfer::uploadFile(const std::string filepath)
{
    Process::Args args;
    args.push_back("s3");
    args.push_back("cp");
    args.push_back(filepath);
    args.push_back(_targetUrl); 
    Poco::Pipe out, err;
    ProcessHandle ph = Process::launch(AWSFileTransfer::AWS_TOOL, args, 0, &out, &err);
    if (ph.wait() != 0)
    {
        Poco::PipeInputStream stream(err);
        Poco::StreamCopier::copyStream(stream, std::cout);
        std::cout << "Failed to upload file to AWS" << std::endl;
        return;
    }
}

void AWSFileTransfer::downloadFile(const std::string filepath)
{
    Process::Args args;
    args.push_back("s3");
    args.push_back("cp");
    std::string fullpath(_targetUrl);
    fullpath.append("/");
    fullpath.append(filepath);
    args.push_back(fullpath);
    args.push_back(filepath);
    ProcessHandle ph = Process::launch(AWSFileTransfer::AWS_TOOL, args, 0, 0, 0);
    if (ph.wait() != 0)
    {
        std::cout << "Failed to download file from AWS" << std::endl;
        return;
    }
}

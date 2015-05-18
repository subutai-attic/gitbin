#include "FileTransfer.h"

FileTransfer::FileTransfer()
{

}

FileTransfer::~FileTransfer()
{

}

void FileTransfer::uploadFile(const std::string uuid)
{
    std::string sourcePath(Plugin::GIT_CACHE_DIR);
    sourcePath.append("/").append(uuid);
    Process::Args args;
    args.push_back(uuid);
    // TODO: Change this name
    std::string targetPath("~/keshig-storage/");
    targetPath.append(uuid);
    Poco::ProcessHandle ph = Process::launch("scp", args, 0, 0, 0); 
    if (ph.wait() != 0) throw new Poco::RuntimeException("Failed to upload file");
}

void FileTransfer::downloadFile(const std::string uuid)
{
    std::string sourcePath(Plugin::GIT_CACHE_DIR);
    sourcePath.append("/").append(uuid);
    Process::Args args;
    args.push_back(uuid);
    // TODO: Change this name
    std::string targetPath("~/keshig-storage/");
    targetPath.append(uuid);
    Poco::ProcessHandle ph = Process::launch("scp", args, 0, 0, 0); 
    if (ph.wait() != 0) throw new Poco::RuntimeException("Failed to upload file");
}

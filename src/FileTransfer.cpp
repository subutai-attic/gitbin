#include "FileTransfer.h"
#include "Plugin.h"

FileTransfer::FileTransfer()
{

}

FileTransfer::~FileTransfer()
{

}

void FileTransfer::uploadFile(const std::string filepath)
{
    std::string sourcePath(Plugin::GIT_CACHE_DIR);
    sourcePath.append("/").append(filepath);
    Process::Args args;
    args.push_back(filepath);
    // TODO: Change this name
    std::string targetPath("~/keshig-storage/");
    targetPath.append(filepath);
    Poco::ProcessHandle ph = Process::launch("scp", args, 0, 0, 0); 
    if (ph.wait() != 0) throw new Poco::RuntimeException("Failed to upload file");
}

void FileTransfer::downloadFile(const std::string filepath)
{
    std::string sourcePath(Plugin::GIT_CACHE_DIR);
    sourcePath.append("/").append(filepath);
    Process::Args args;
    args.push_back(filepath);
    // TODO: Change this name
    std::string targetPath("~/keshig-storage/");
    targetPath.append(filepath);
    Poco::ProcessHandle ph = Process::launch("scp", args, 0, 0, 0); 
    if (ph.wait() != 0) throw new Poco::RuntimeException("Failed to upload file");
}

void FileTransfer::setTargetUrl(const std::string targetUrl)
{
    _targetUrl = targetUrl;
}

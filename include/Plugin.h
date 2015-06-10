/*
 * =====================================================================================
 *
 *       Filename:  Plugin.h
 *
 *    Description:  Main Plugin class
 *
 *        Version:  1.0
 *        Created:  05/06/2015 03:02:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mikhail Savochkin (msavochkin@critical-factor.com), 
 *
 * =====================================================================================
 */
#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include <iostream>
#include <fstream>

#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Message.h>
#include <Poco/Channel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/Logger.h>
#include <Poco/LogStream.h>
#include <Poco/AutoPtr.h>
#include <Poco/File.h>
#include <Poco/Util/IntValidator.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/Process.h>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/DigestStream.h>
#include <Poco/MD5Engine.h>
#include <Poco/StringTokenizer.h>
#include <Poco/String.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/FileStream.h>
#include <Poco/URI.h>

#include "FileTransfer.h"
#include "S3FileTransfer.h"
#include "AWSFileTransfer.h"

using Poco::trim;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Message;
using Poco::Channel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Logger;
using Poco::SplitterChannel;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::AutoPtr;
using Poco::LogStream;
using Poco::Util::IntValidator;
using Poco::File;
using Poco::Util::PropertyFileConfiguration;
using Poco::Process;
using Poco::Pipe;
using Poco::PipeOutputStream;
using Poco::PipeInputStream;
using Poco::DigestOutputStream;
using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::StringTokenizer;
using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::FileInputStream;
using Poco::FileOutputStream;
using Poco::URI;

struct IndexEntry
{
    std::string filepath;
    std::string md5;
    std::string uuid;
};

typedef enum
{
    ADD,
    DELETE,
    LIST,
    CHECK,
    INIT,
    HELP
} GitAction;

typedef enum
{
    NOT_TRACKED,
    MODIFIED,
    DELETED
} FileStatus;

class Plugin : public ServerApplication
{
    public:
        Plugin();
        ~Plugin();
        void initialize(Application& self);
            // Initializes plugin application
        void uninitialize();
            // Uninitializes plugin application
        void setupLogger();
            // Initializes logger. 
        void defineOptions(OptionSet& options);
            // Defines option set
        void handleHelp(const std::string& name, const std::string& value);
            // Display a help information
        void handleAdd(const std::string& name, const std::string& value);
            // Adds files into index, replaces binary files with text files
        void handleList(const std::string& name, const std::string& value);
            // List all files in index
        void handleCheck(const std::string& name, const std::string& value);
            // Checks for binary/large files under specific directory 
        void handleInit(const std::string& name, const std::string& value);
            // Initializes new git-bin configuration files
        void handleSync(const std::string& name, const std::string& value);
            // Starts a sync of files over network
        void handleStatus(const std::string& name, const std::string& value);
        int main(const std::vector<std::string>& args);
            // Main function. Didn't used
        bool hasGitDirectory();
            // Returns true if program runs under git repository. False otherwise
        int replaceWithLink(std::string filepath);
            // Replaces binary or large file with text-link files
        static const std::string GIT_DIR;
            // Main .git directory
        static const std::string GIT_CONFIG;
            // Path to a keshig configuration file
        static const std::string GIT_CACHE_DIR;
            // Path to cache dir for large binary files
        static const std::string GIT_BIN_INDEX;
            // Index file of binary files
        static const std::string SEPARATOR;
        void addFile(const std::string filepath);
        bool isFileIndexed(const std::string filepath);
        void readIndex();
        void writeIndex();
        bool isUuidUnique(const std::string uuid);
        std::string getFileMd5(const std::string filepath) const;
        IndexEntry* getIndexEntry(const std::string filepath);
        std::vector<IndexEntry>* getIndex();
    private:
        std::vector<IndexEntry> _index;
        bool _terminate;
            // True if we want to display help and quit application
        std::string _type;
        std::string _url;
            // Path to a storage
        GitAction _action;
};

#endif

git-bin plugin for git

Building
========

In order to build git-bin you need to build Poco C++ Libraries first:
1. Clone poco from github: git clone 
2. cd poco
3. ./configure --omit=Data/ODBC,Data/MySQL
3.a. If you planning to make a static build (single binary only) you need to configure poco with static libraries support: ./configure --static --omit=Data/ODBC,Data/MySQL
4. make
5. make install 
5.a. If you did a static build you need to create "lib" directory under git-bin project and move *.a file from poco/lib directory into git-bin/lib

Now you need to configure and build git-bin itself:
1.  ./configure 
    or
    ./configure --static
    for static build
2. make
3. make install

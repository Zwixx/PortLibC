/*
 * =====================================================================================
 *
 *       Filename:  FileAttributes.h
 *
 *    Description:  
 *
 *        Version:  3.0
 *        Created:  08/23/2017 02:36:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  surkeh@protonmail.com
 *
 * =====================================================================================
 */
#ifndef PORTLIBC_FILEATTRIBUTES_H
#define PORTLIBC_FILEATTRIBUTES_H

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#if defined(_WIN32) || defined (__CYGWIN__)
#include <windows.h>
#else
// Define Windows File attribute flags if undefined
#define FILE_ATTRIBUTE_READONLY 1
#define FILE_ATTRIBUTE_HIDDEN 2
#define FILE_ATTRIBUTE_DIRECTORY 16
#define FILE_ATTRIBUTE_ARCHIVE 32
#define FILE_ATTRIBUTE_DEVICE 64
#define FILE_ATTRIBUTE_NORMAL 128
#define FILE_ATTRIBUTE_COMPRESSED 2048
#define FILE_ATTRIBUTE_SYSTEM 4
#define FILE_ATTRIBUTE_TEMPORARY 256
#define FILE_ATTRIBUTE_SPARSE_FILE 512
#define FILE_ATTRIBUTE_REPARSE_POINT 1024
#define FILE_ATTRIBUTE_OFFLINE 4096
#define FILE_ATTRIBUTE_NOT_INDEXED 8192
#define FILE_ATTRIBUTE_INTEGRITY_STREAM 32768
#define FILE_ATTRIBUTE_VIRTUAL 65536
#define FILE_ATTRIBUTE_NO_SCRUB 131072
#define FILE_ATTRIBUTE_RECALL_ON_OPEN 262144
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 4194304
#endif


#define WINDOWS_TICK      10000000
#define SEC_TO_UNIX_EPOCH 11644473600
#define UNIX_EPOCH        0 //approximately

// Posix permissions in octal
#define POSIX_RUSR     0400
#define POSIX_RGRP     0040
#define POSIX_ROTH     0004
#define POSIX_WUSR     0200
#define POSIX_WGRP     0020
#define POSIX_WOTH     0002
#define POSIX_XUSR     0100
#define POSIX_XGRP     0010
#define POSIX_XOTH     0001
#define POSIX_READONLY 0444
#define POSIX_NORMAL   0644


typedef struct FileTimePortable {
  uint32_t dwLowDateTime;
  uint32_t dwHighDateTime;
} FileTimePortable;

int isPosixTime(time_t t);
time_t convertToPosixTime (FileTimePortable windowsTime);
FileTimePortable convertToFileTime (time_t posixTime);
uint32_t convertToWindowsAttributes(uint32_t posixMode);
uint32_t convertToPosixAttributes(uint32_t windowsAttributes);

#endif //PORTLIBCPP_FILEATTRIBUTES_H
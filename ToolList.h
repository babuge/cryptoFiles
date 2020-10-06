#pragma once
#ifndef _WIN32
#define _WIN32

//#ifndef _LINUX
//#define _LINUX

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#elif _LINUX
#include <stdarg.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#define DIR_SPLITE_CHAR "\\"
#elif _LINUX
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)
#define _MAX_PATH 260
#define _MAX_DRIVE 256
#define _MAX_DIR 256
#define _MAX_FNAME 256
#define _MAX_EXT 256
#define DIR_SPLITE_CHAR "/"
void _splitpath(char *path, char *drive, char *dir, char *fname, char *ext);
void _split_whole_name(char *whole_name, char *fname, char *ext);
#endif
#include <stdio.h>  // printf
#include <stdlib.h> // rand
#include <time.h> // time_t
#include <sys/stat.h> // stat. etc filelength
#include <string.h>

#define STR_TIME_MAX 84

#define FILE_MAX_PATH   260

#endif // _LINUX or _WIN32
typedef struct
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char fname_ext[_MAX_FNAME + _MAX_EXT];
	char path[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT];
} PathInfo;

// 获取系统当前时间（字符串，最小到秒，通用）
void TimeToString(char*);
// 获取文件大小（window 、linux通用）
long file_size2(char*);
// 获取控制台字符串
char* s_gets(char*, int);
// 连续获取随机数
void s_rand(int*);
// 文件路径分割
void split_path(char*, PathInfo *);
// 创建文件夹
int creat_dir(char *);

#include "ToolList.h"

// 获取系统当前时间（字符串，最小到秒，通用）
void TimeToString(char* str_ret)
{
	time_t now_time;
	time(&now_time);
	struct tm* sysTem = localtime(&now_time);
	if (strftime(str_ret, STR_TIME_MAX, "%Y-%m-%d %H:%M:%S", sysTem) == 0)
	{
		printf("时间转换失败！\n");
	}
}

// 获取文件大小
long file_size2(char* filename)
{
	struct stat statbuf;
	stat(filename, &statbuf);
	long size = statbuf.st_size;
	return size;
}

// 获取控制台字符串
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
		{
			*find = '\0';
		}
		else
		{
			while (getchar() != '\n')
			{
				continue;
			}
		}
	}
	return ret_val;
}

// 连续获取随机数
void s_rand(int* a)
{
	static int rand_start = 1;
	if (rand_start)
	{
		rand_start = 0;
		srand((unsigned)time(NULL));
	}
	*a = rand() % 9000 + 1000;
}

#ifndef _WIN32
void _splitpath(char *path, char *drive, char *dir, char *fname, char *ext)
{
	char *p_whole_name;

	drive[0] = '\0';
	if (NULL == path)
	{
		dir[0] = '\0';
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	if ('/' == path[strlen(path)])
	{
		strcpy(dir, path);
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	p_whole_name = rindex(path, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		_split_whole_name(p_whole_name, fname, ext);

		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		_split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}

void _split_whole_name(char *whole_name, char *fname, char *ext)
{
	char *p_ext;

	p_ext = rindex(whole_name, '.');
	if (NULL != p_ext)
	{
		strcpy(ext, p_ext);
		snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		ext[0] = '\0';
		strcpy(fname, whole_name);
	}
}

#endif
// 文件路径与文件名分割
void split_path(char* str, PathInfo* path_info)
{
	_splitpath(str, path_info->drive, path_info->dir, path_info->fname, path_info->ext);
	if ((strlen(path_info->fname) + strlen(path_info->ext) + 1) <= (_MAX_EXT + _MAX_FNAME)) {
		strcpy(path_info->fname_ext, path_info->fname);
		strcat(path_info->fname_ext, path_info->ext);
		strcpy(path_info->path, str);
	}
	else
	{
        printf("beyond maximum size!\n");
	}
}

// 创建文件夹
int creat_dir(char* pszDir)
{
	int i = 0;
	int iRet;
	int iLen = strlen(pszDir);
	//在末尾加/
	if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}
	// 创建目录
	for (i = 0; i < iLen; i++)
	{
		if (pszDir[i] == '\\' || (pszDir[i] == '/' && i != 0))
		{
			pszDir[i] = '\0';

			//如果不存在,创建
			iRet = ACCESS(pszDir, 0);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
					return -1;
				}

			}
			//支持linux,将所有\换成/
			pszDir[i] = '/';
		}
	}
	return 0;
}

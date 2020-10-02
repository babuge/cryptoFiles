#include "main.h"
#include "ToolList.h"
#include "eatline.h"

int main()
{
    int flag = 1;
    while (flag) {
        en_or_de_meun();
        printf("请输入选择命令:\n>");
        char en_or_de;
        scanf("%c", &en_or_de);
        eatline();
        switch (en_or_de)
        {
            case 'a':
            case 'b':
                // 加密解密 功能
                if (endecrypto(en_or_de) == 0) {
                    flag = 0;
                }
                break;
            case 'q':
                return 0;
                break;
            default:
                printf("输入命令有误!\n");
                break;
        }
    }
    return 0;
}

// 加密或解密菜单
void en_or_de_meun()
{
    printf("**********************\n");
    printf("*                    *\n");
    printf("*    应用选择菜单    *\n");
    printf("*    a-加密文件      *\n");
    printf("*    b-解密密文件    *\n");
    printf("*    q-退出应用      *\n");
    printf("*                    *\n");
    printf("**********************\n");
}

// 加密解密 功能
int endecrypto(char en_or_de)
{
    // 用户输入的要加密的文件名
    char pem_fpath[_MAX_PATH] = "D:\\cryptoSpace\\picture\\_pem.pem";
    FILE* fp_pem; // pem文件指针
    char* p_memory; // pem文件动态内存指针
    long file_pem_size = 0; // pem文件大小

    FILE* fp_target; // 目标文件，待加密、待解密
    long size_file_target; // 目标文件大小
    // 待加密待解密文件
    char target_path[_MAX_PATH];
    char endeCN[] = "加密文件";
    if (en_or_de != 'a')
    {
        strcpy(endeCN, "解密文件");
    }
    while (1)
    {
        printf("请输入用于%s的密钥文件路径: (手动创建一个)\n>", en_or_de == 'a'? "加密":"解密");
        // 请输入文件路径
        if (s_gets(pem_fpath, _MAX_PATH) != NULL && pem_fpath[0] != '\0')
        {
            if ((fp_pem = fopen(pem_fpath, "rb")) == NULL)
            {
                printf("未找到该文件！\n");
                continue;
            }
            file_pem_size = file_size2(pem_fpath);
            // 密钥长度校验
            if (file_pem_size <= 0)
            {
                printf("密钥无效！\n");
                fclose(fp_pem);
                continue;
            }
            PathInfo path_info;
            split_path(pem_fpath, &path_info);
            printf(
                "密钥校验成功！\n------文件尺寸：%ldbyte  文件名：%s------\n", file_pem_size, path_info.fname_ext
            );
            p_memory = (char*)malloc(sizeof(char) * file_pem_size);
            fread(p_memory, sizeof(char) * file_pem_size, 1, fp_pem);
            while (1)
            {
                printf("请输入待%s路径：(输入'q'退出)\n>", endeCN);
                if (s_gets(target_path, _MAX_PATH) != NULL && target_path[0] != '\0')
                {
                    if (strlen(target_path) <= 1 && target_path[0] == 'q')
                    {
                        printf("应用退出!\n");
                        break;
                    }
                    if ((fp_target = fopen(target_path, "rb")) == NULL)
                    {
                        printf("未找到待%s！\n", endeCN);
                        continue;
                    }
                    size_file_target = file_size2(target_path);
                    if (size_file_target <= 0)
                    {
                        printf("空文件，无需%s！\n", endeCN);
                        fclose(fp_target);
                        break;
                    }
                    PathInfo target_path_info;
                    split_path(target_path, &target_path_info);
                    printf("------\n\t待处理文件信息\n\t文件尺寸：%ldbyte  文件名：%s\n------\n",
                        size_file_target, target_path_info.fname_ext);
                    char out_file[_MAX_DRIVE+_MAX_DIR+_MAX_FNAME+_MAX_EXT];
                    char out_file_dir[_MAX_DRIVE + _MAX_DIR];
                    strcpy(out_file, target_path_info.drive);
                    strcat(out_file, target_path_info.dir);
                    strcat(out_file,DIR_SPLITE_CHAR);
                    if (en_or_de == 'a')
                    {
                        strcat(out_file, "encryp");
                    }
                    else
                    {
                        strcat(out_file, "decryp");

                    }
                    strcat(out_file,DIR_SPLITE_CHAR);
                    strcpy(out_file_dir, out_file);
                    strcat(out_file, target_path_info.fname_ext);
                    // 不存在就创建目录
                    creat_dir(out_file_dir);
                    FILE* fp_out_file;
                    if ((fp_out_file = fopen(out_file, "wb")) == NULL)
                    {
                        printf("------\n\t不能打开此文件：\n\t[%s].\n------\n", target_path_info.path);
                        fclose(fp_target);
                        continue;
                    }
                    unsigned long long i = 0;
                    unsigned long long j;
                    char ch;
                    j = file_pem_size;
                    ch = fgetc(fp_target);
                    // 加密算法开始
                    while (!feof(fp_target))
                    {
                        fputc(ch ^ p_memory[i >= j ? i = 0 : i++], fp_out_file); // 异或后写入fp_out_file文件
                        ch = fgetc(fp_target);
                    }
                    printf("-------\n\t文件 %s 成功！[%s]\n------\n", en_or_de == 'a' ? "加密": "解密", out_file);
                    fclose(fp_target);
                    fclose(fp_out_file);
                }
            }
            free(p_memory);
            fclose(fp_pem);
            break;
        }
    }
    return 0;
}

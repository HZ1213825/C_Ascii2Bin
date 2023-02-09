#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define uint8_t unsigned char

uint8_t Ascll2uchar(uint8_t input)
{
    if (input >= 'a' && input <= 'z')
        return input - 'a' + 10;
    else if (input >= 'A' && input <= 'Z')
        return input - 'A' + 10;
    else if (input >= '0' && input <= '9')
        return input - '0';
}
int main(int argc, char *argv[])
{
    int begintime, endtime;
    uint8_t data_all, data_first, data_last;
    uint8_t data_zj;
    FILE *input_fp, *output_fp;

    char *Add_output;
    char *Add_input = argv[1];
    char *Add_output_befor = argv[2];
    char *Add_output_after = argv[3];
    // char *Add_input = "C:\\Users\\HZ12138\\Desktop\\1.txt";
    // char *Add_output_befor = "output";
    // char *Add_output_after = ".jpeg";
    begintime = clock();
    for (int i = 0;; i++)
    {
        Add_output = (char *)malloc(sizeof(char) *
                                    (strlen(Add_output_befor) + strlen(Add_output_after) + 15));

        sprintf(Add_output, "%s%d%s", Add_output_befor, i, Add_output_after);
        // puts(Add_output);
        if (access(Add_output, 0) != 0)
            break;
        else
            free(Add_output);
        if (i > 1000000)
        {
            printf("ERROR:output file name error\r\n");
        }
    }
    puts(Add_output);
    input_fp = fopen(Add_input, "r");
    if (input_fp == NULL)
    {
        printf("ERROR: failed to open the read file!\r\n");
        fclose(input_fp);
        fclose(output_fp);
        free(Add_output);
        system("pause");
        return 0;
    }
    output_fp = fopen(Add_output, "wb");
    while (!feof(input_fp)) // 读文件
    {
        data_zj = fgetc(input_fp);
        if (data_zj == ' ')
            continue;
        if (feof(input_fp))
            break;
        data_first = Ascll2uchar(data_zj);
        data_last = Ascll2uchar(fgetc(input_fp));
        data_all = (data_first << 4) | data_last;
        // printf("%x ", data_all);
        fputc(data_all, output_fp);
    }
    fclose(input_fp);
    fclose(output_fp);
    free(Add_output);
    endtime = clock();
    printf("finish\r\nspend %d ms\r\n", endtime - begintime);
    return 0;
}
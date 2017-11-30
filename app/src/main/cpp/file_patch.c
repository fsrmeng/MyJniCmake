#include "jni.h"
#include <stdlib.h>
#include <stdio.h>
#include <android/log.h>

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, "zp", FORMAT, ##__VA_ARGS__)

//
// Created by zp on 2017/11/1.
//
//根据文件的路径，获得文件的大小
long get_file_size(char* path) {
    FILE* fp = fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

//拆分
JNIEXPORT void JNICALL
Java_com_zhangpan_myjnicmake_FilePatchUtil_split(JNIEnv *env, jclass jcla, jstring path_,
                                                jstring path_pattern_, jint file_count) {
    //需要分割的文件路径
    const char* path = (*env)->GetStringUTFChars(env, path_, NULL);
    //分割后的子文件路径模板
    const char* path_pattern = (*env)->GetStringUTFChars(env, path_pattern_, NULL);

    //得到分割后的子文件的路径列表
    char** patches = malloc(sizeof(char*) * file_count);
    //也可以这样去动态分配内存
    //char **patches = malloc(sizeof(char) * get_file_size(path));
    int i = 0;
    for (; i < file_count; i++) {
        //元素赋值
        patches[i] = malloc(sizeof(char) * 100);
        //也可以这样动态分配内存
        //patches[i] = malloc(sizeof(char) * (get_file_size(path) / file_count));

        //path_pattern /storage/emulated/0/AS_%d.avi
        // /storage/emulated/0/AS_1.avi
        // /storage/emulated/0/AS_2.avi
        // /storage/emulated/0/AS_3.avi
        // /storage/emulated/0/AS_4.avi
        sprintf(patches[i], path_pattern, (i+1));
        LOGD("%s", patches[i]);
    }

    //不断读取path文件，循环写入file_count个文件中
    //整除：文件大小为90，分成9个文件，每个文件为10
    //不整除：文件大小为110，分成9个文件，前(9-1)个文件为(110 / (9-1)) = 13，最后一个文件为(110 % (9-1)) = 6
    //前(9-1)个文件为110/9 + 1 = 13，最后一个文件为 110 - 13*8 = 6
    int fileSize = get_file_size(path);
    FILE* fpr = fopen(path, "rb");
    if (fileSize % file_count == 0) {       //整除
        int partSize = fileSize / file_count;
        int i = 0;
        for (; i < file_count; i++) {
            int j = 0;
            FILE* fpw = fopen(patches[i], "wb");
            for(; j < partSize; j++) {
                fputc(fgetc(fpr), fpw);
            }
            fclose(fpw);
        }
    } else {                                //非整除
        int prePartSize = fileSize / file_count + 1;
        int lastPartSize = fileSize - (file_count - 1) * prePartSize;
        //写入前(file_count - 1)个文件
        int i = 0;
        for(; i < file_count - 1; i++) {
            FILE* fpw = fopen(patches[i], "wb");
            int j = 0;
            for (; j < prePartSize; j++) {
                fputc(fgetc(fpr), fpw);
            }
            fclose(fpw);
        }

        //写入最后一个文件
        int j = 0;
        FILE* fpw = fopen(patches[file_count - 1], "wb");
        for (; j < lastPartSize; j++) {
            fputc(fgetc(fpr), fpw);
        }
        fclose(fpw);
    }
    fclose(fpr);

    //释放
    i = 0;
    for (; i < file_count; i++) {
        free(patches[i]);
    }
    free(patches);

    (*env)->ReleaseStringUTFChars(env, path_, path);
    (*env)->ReleaseStringUTFChars(env, path_pattern_, path_pattern);
}

//合并
JNIEXPORT void JNICALL
Java_com_zhangpan_myjnicmake_FilePatchUtil_merge(JNIEnv *env, jclass jcla, jstring path_merge_,
                                                jstring path_pattern_, jint file_count) {
    const char *path_merge = (*env)->GetStringUTFChars(env, path_merge_, NULL);
    const char *path_pattern = (*env)->GetStringUTFChars(env, path_pattern_, NULL);

    char** patches = malloc(sizeof(char*) * file_count);
    FILE* fpw = fopen(path_merge, "wb");
    int i = 0;
    for (; i < file_count; i++) {
        patches[i] = malloc(sizeof(char) * 100);
        sprintf(patches[i], path_pattern, (i+1));
//        __android_log_print(ANDROID_LOG_DEBUG, "zp", "%s", patches[i]);
        LOGD("%s", patches[i]);
        //获取每个分割后的子文件大小
        int patchFileSize = get_file_size(patches[i]);
        FILE* fpr = fopen(patches[i], "rb");

        //边读边写
        int j = 0;
        for (; j < patchFileSize; j++) {
            fputc(fgetc(fpr), fpw);
        }
        fclose(fpr);
    }
    fclose(fpw);
    //释放
    i = 0;
    for(; i < file_count; i++) {
        free(patches[i]);
    }
    free(patches);

    (*env)->ReleaseStringUTFChars(env, path_merge_, path_merge);
    (*env)->ReleaseStringUTFChars(env, path_pattern_, path_pattern);
}
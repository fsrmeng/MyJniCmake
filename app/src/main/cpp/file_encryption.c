//
// Created by zp on 2017/10/31.
//

#include "jni.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

char password[] = "ChinaIsPowerful";
//加密
JNIEXPORT void JNICALL
Java_com_zhangpan_myjnicmake_Encryptor_cryption(JNIEnv *env, jclass jcla, jstring normal_path_jstr, jstring crypt_path_jstr) {
    //jstring --> char*
    char* normal_path = (*env)->GetStringUTFChars(env, normal_path_jstr, NULL);
    char* crypt_path = (*env)->GetStringUTFChars(env, crypt_path_jstr, NULL);

    __android_log_print(ANDROID_LOG_DEBUG, "system.out", "%s", normal_path);
    //打开文件
    FILE* nomal_fp = fopen(normal_path, "rb");
    FILE* crypt_fp = fopen(crypt_path, "wb");

    if (nomal_fp == NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "system.out", "文件打开失败");
        return;
    }

    //一次读取一个字符
    int ch = 0;
    int i = 0;
    int pwd_length = strlen(password);
    while ((ch = fgetc(nomal_fp)) != EOF) {	//End of File
        //写入(异或运算)
        fputc(ch ^ password[i % pwd_length], crypt_fp);
        i++;
    }

    //关流
    fclose(nomal_fp);
    fclose(crypt_fp);
}

//解密
JNIEXPORT void JNICALL
Java_com_zhangpan_myjnicmake_Encryptor_decryption(JNIEnv *env, jclass jcla, jstring crypt_path_jstr, jstring decrypt_path_jstr) {
    //jstring --> char*
    char *crypt_path = (*env)->GetStringUTFChars(env, crypt_path_jstr, NULL);
    char *decrypt_path = (*env)->GetStringUTFChars(env, decrypt_path_jstr, NULL);
    FILE* crypt_fp = fopen(crypt_path, "rb");
    FILE* decrypt_fp = fopen(decrypt_path, "wb");

    int ch;
    int i = 0;
    int pwd_length = strlen(password);
    while ((ch = fgetc(crypt_fp)) != EOF)
    {
        fputc(ch ^ password[i % pwd_length], decrypt_fp);
        i++;
    }

    fclose(crypt_fp);
    fclose(decrypt_fp);
}
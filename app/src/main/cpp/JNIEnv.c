//
// Created by zp on 2017/10/25.
//

//JNIEnv是结构体指针的别名
typedef struct JNIEnvInterface_* JNIEnv;

struct JNIEnvInterface_ {
    char* (*NewStringUTF)(JNIEnv*, char*);
};

//函数实现
char* NewStringUTF(JNIEnv* env, char* str) {
    (*env)->NewStringUTF
    return str;
}

char* NewStringUTF1(JNIEnv env, char* str) {
    env->NewStringUTF
    return str;
}

void main() {
    //实例化结构体
    struct JNIEnvInterface_ struct_env;
    struct_env.NewStringUTF = NewStringUTF;

    //结构体指针
    JNIEnv e = &struct_env;
    //结构体的二级指针
    JNIEnv* env = &e;
    //通过二级指针调用函数
    (*env)->NewStringUTF(env, "abc");
}
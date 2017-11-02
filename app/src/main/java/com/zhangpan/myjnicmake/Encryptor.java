package com.zhangpan.myjnicmake;

/**
 * Created by ZhangPan on 2017/10/31
 */

public class Encryptor {
    static {
        System.loadLibrary("file_encryption");
    }

    //加密
    public native static void cryption(String normalPath, String cryptPath);
    //解密
    public native static void decryption(String cryptPath, String decryptPath);
}

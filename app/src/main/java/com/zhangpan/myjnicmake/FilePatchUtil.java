package com.zhangpan.myjnicmake;

/**
 * Created by ZhangPan on 2017/11/1
 */

public class FilePatchUtil {
    static {
        System.loadLibrary("file_patch");
    }

    //拆分
    public native static void split(String path, String pathPattern, int count);
    //合并
    public native static void merge(String pathMerge, String pathPattern, int count);
}

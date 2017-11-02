package com.zhangpan.myjnicmake;

import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import java.io.File;

/**
 * Created by ZhangPan on 2017/11/1
 */

public class FilePatchActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_file_patch);
    }

    public void mSplit(View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "AS.avi";
                String pathPattern = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "AS_%d.avi";
                FilePatchUtil.split(path, pathPattern, 4);
                Log.d("zhangpan", "拆分完成...");
            }
        }).start();
    }

    public void mMerge(View view) {
        new Thread((new Runnable() {
            @Override
            public void run() {
                String pathMerge = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "AS_merge.avi";
                String pathPattern = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "AS_%d.avi";
                FilePatchUtil.merge(pathMerge, pathPattern, 4);
                Log.d("zhangpan", "合并完成...");
            }
        })).start();
    }
}

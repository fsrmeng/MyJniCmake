package com.zhangpan.myjnicmake;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

/**
 * Created by ZhangPan on 2017/11/30
 */

public class AppStartActivity extends AppCompatActivity implements View.OnClickListener{
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_app_start);

        initView();
    }

    private void initView() {
        findViewById(R.id.btnBasic).setOnClickListener(this);
        findViewById(R.id.btnEncryptor).setOnClickListener(this);
        findViewById(R.id.btnPatch).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btnBasic:
                startActivity(new Intent(this, MainActivity.class));
                break;
            case R.id.btnEncryptor:
                startActivity(new Intent(this, FileEncryptionActivity.class));
                break;
            case R.id.btnPatch:
                startActivity(new Intent(this, FilePatchActivity.class));
                break;
            default:
                break;
        }
    }
}

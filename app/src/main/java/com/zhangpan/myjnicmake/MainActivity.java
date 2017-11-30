package com.zhangpan.myjnicmake;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.Random;
import java.util.UUID;

public class MainActivity extends AppCompatActivity{

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String getStringFromJNI();

    public String key = "john";
    private static int count = 10;
    private Animal animal = new Cat();

    //访问属性
    public native void accessField();
    //访问静态属性
    public native void accessStaticField();
    //访问方法
    public native void accessMethod();
    //访问静态方法
    public native void accessStaticMethod();
    //访问构造方法
    public native void accessConstructor();
    //访问父类的方法
    public native void accessNonvirtualMethod();
    //访问
    public native String accessChineseChars(String str);
    //传入数组
    public native void putArray(int[] arr);
    //返回数组
    public native int[] getArray(int arrLength);
    //局部引用
    public native void localRef();
    //全局引用
    public native void createGlobalRef();
    public native String getGlobalRef();
    public native void deleteGlobalRef();
    //异常处理
    public native void exception();
    //缓存处理
    public native void cache();
    public native static void initIDs();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("zhangpan");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(getStringFromJNI());

        System.out.println("修改前：" + key);
        this.accessField();
        System.out.println("修改后：" + key);

        System.out.println("修改前count：" + count);
        accessStaticField();
        System.out.println("修改后count：" + count);

        accessMethod();
        accessStaticMethod();
        accessConstructor();
//        animal.eat();
        accessNonvirtualMethod();
        System.out.println(accessChineseChars("刘涛"));

        int[] array = {1, 20, 11, 55, 90, 100, 5, 70};
        /*putArray(array);
        //如果不加同步代码，这里打印出来的还是未排序的
        for (int i = 0; i < array.length; i++) {
            System.out.println("Java " + array[i]);
        }*/

        int[] arr = getArray(5);
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i]);
        }

        System.out.println("------------------");
        createGlobalRef();
        System.out.println(getGlobalRef());
        deleteGlobalRef();
        System.out.println("释放完了...");
//        System.out.println(getGlobalRef());     //释放完了，再获取会报空指针

        System.out.println("------------------");
        try {
            exception();
        } catch (Exception e) {
            System.out.println("发生异常：" + e.getMessage());
        }
        System.out.println("异常处理完了..");

        int i = 0;
        for (; i < 10; i++) {
            cache();
        }
    }

    //产生指定范围的随机数
    public int getRandomInt(int value) {
        System.out.println("getRandomInt 执行了");
        return new Random().nextInt(value);
    }

    //产生UUID字符串
    public static String getUUID() {
        return UUID.randomUUID().toString();
    }
}

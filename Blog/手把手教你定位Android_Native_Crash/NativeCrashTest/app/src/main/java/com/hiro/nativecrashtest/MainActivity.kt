package com.hiro.nativecrashtest

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle

class MainActivity : AppCompatActivity() {

    companion object {
        init {
            System.loadLibrary("crash_test")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        // trigger native crash
        nativeCrashTest()
    }

    /**
     * 声明 native 方法
     */
    private external fun nativeCrashTest()
}
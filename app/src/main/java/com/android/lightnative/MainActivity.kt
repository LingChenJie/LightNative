package com.android.lightnative

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.android.lightnative.bean.TestBean
import com.android.lightnative.databinding.ActivityMainBinding
import com.android.lightnative.ext.click

class MainActivity : AppCompatActivity() {

    private val binding: ActivityMainBinding by lazy {
        ActivityMainBinding.inflate(layoutInflater)
    }
    private val lightNativeLib = LightNativeLib()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)
        initView()
    }

    private fun initView() {
        binding.sampleText.text = lightNativeLib.hello()
        binding.getJavaBeanFromC.click {
            val bean = lightNativeLib.javaBeanFromNative
            Log.d("TAG", bean.toString())
        }
        binding.javaBeanToStruct.click {
            val testBean = TestBean()
            lightNativeLib.transferJavaBeanToNative(testBean)
        }
    }


}
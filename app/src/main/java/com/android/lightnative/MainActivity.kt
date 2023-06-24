package com.android.lightnative

import android.os.Build
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.android.lightnative.bean.TestBean
import com.android.lightnative.databinding.ActivityMainBinding
import com.android.lightnative.ext.click
import com.android.lightnative.utils.LogUtil

private const val TAG = "MainActivity"

class MainActivity : AppCompatActivity() {


    private val binding: ActivityMainBinding by lazy {
        ActivityMainBinding.inflate(layoutInflater)
    }
    private val lightNativeLib = LightNativeLib()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)
        initView()
        val abi = Build.SUPPORTED_ABIS[0]
        LogUtil.e(TAG, "abi:$abi")
    }

    private fun initView() {
        binding.sampleText.text = lightNativeLib.hello()
        binding.helloJni.click {
            val helloJni = OperateString().helloJni("Hello JNI")
            toast(helloJni);
        }
        binding.operateIntArray.click {
            val inArray = intArrayOf(10, 100)
            OperateArray().operateIntArray(inArray)?.forEach {
                LogUtil.e(TAG, "operateIntArray:$it")
            }
        }
        binding.operateStringArray.click {
            val inArray = arrayOf("Hello", "JNI")
            OperateArray().operateStringArray(inArray)?.forEach {
                LogUtil.e(TAG, "operateStringArray:$it")
            }
        }
        binding.getJavaBeanFromC.click {
            val bean = lightNativeLib.javaBeanFromNative
            LogUtil.d(TAG, bean.toString())
        }
        binding.javaBeanToStruct.click {
            val testBean = TestBean()
            lightNativeLib.transferJavaBeanToNative(testBean)
        }
    }

    private fun toast(str: String) {
        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
    }

}
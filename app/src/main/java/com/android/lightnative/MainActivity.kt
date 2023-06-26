package com.android.lightnative

import android.os.Build
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.android.lightnative.bean.Student
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
        binding.operateStudentArray.click {
            val inArray = arrayOf(Student(10, "zhangsan"), Student(20, "lisi"))
            OperateArray().operateStudentArray(inArray)?.forEach {
                LogUtil.e(TAG, "operateStudentArray:$it")
            }
        }
        binding.operateTwoIntArray.click {
            val inArray = arrayOf(intArrayOf(10, 100), intArrayOf(20, 200))
            OperateArray().operateTwoIntArray(inArray)?.forEach {
                it.forEach { it ->
                    LogUtil.e(TAG, "operateTwoIntArray:$it")
                }
            }
        }
        binding.accessFiled.click {
            val inArray = Student(12, "zhangsan")
            OperateFiled().accessFiled(inArray)
            LogUtil.e(TAG, "accessFiled:$inArray")
        }
        binding.accessStaticFiled.click {
            OperateFiled().accessStaticFiled()
            LogUtil.e(TAG, "accessStaticFiled Student.staticId::${Student.staticId}")
            LogUtil.e(TAG, "accessStaticFiled Student.staticString::${Student.staticString}")
        }
        binding.callMethod.click {
            val student = OperateMethod().callMethod()
            LogUtil.e(TAG, "callMethod:$student")
        }
        binding.callStaticMethod.click {
            OperateMethod().callStaticMethod()
            LogUtil.e(TAG, "callStaticMethod Student.staticString::${Student.staticString}")
        }
        binding.callSuperMethod.click {
            OperateMethod().callSuperMethod()
        }
        binding.throwException.click {
            try {
                OperateException().throwException2()
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
        binding.threadWork.click {
            OperateThread().threadWork()
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
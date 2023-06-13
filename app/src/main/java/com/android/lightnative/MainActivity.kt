package com.android.lightnative

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.android.lightnative.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val lightNativeLib = LightNativeLib()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.sampleText.text = lightNativeLib.hello()
    }


}
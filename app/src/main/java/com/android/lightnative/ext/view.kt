package com.android.lightnative.ext

import android.view.View

/**
 * Created by SuQi on 2023/6/19.
 * Describe:
 */
fun <T : View> T.click(block: (T) -> Unit) {
    setOnClickListener { block(this) }
}
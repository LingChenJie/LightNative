package com.android.lightnative;

import com.android.lightnative.bean.Student;

/**
 * Created by SuQi on 2023/6/24.
 * Describe:
 */
public class OperateArray {

    // 一维数组入参和作为返回值
    public native int[] operateIntArray(int[] array);

    public native String[] operateStringArray(String[] array);

    public native Student[] operateStudentArray(Student[] array);

}

package com.android.lightnative.bean;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

/**
 * File describe:
 * Author: SuQi
 * Create date: 2023/6/28
 * Modify date: 2023/6/28
 * Version: 1
 */
public class ClassA {

    private final byte[] mByteArray = new byte[4];
    private short mShort;
    private byte mByte;

    public ClassA() {
        for (int i = 0; i < mByteArray.length; i++) {
            mByteArray[i] = (byte) (i * 10);
        }
        mShort = 20;
        mByte = 10;
    }

    /**
     * Converting object into byte array.
     *
     * @return byte array of ClassA
     */
    public byte[] serialToBuffer() {
        ByteBuffer mByteBuffer = ByteBuffer.allocate(1024);
        mByteBuffer.clear();
        mByteBuffer.order(ByteOrder.LITTLE_ENDIAN);

        mByteBuffer.put(mByteArray);
        mByteBuffer.putShort((short) mShort);
        mByteBuffer.put(mByte);

        mByteBuffer.flip();
        byte[] ret = new byte[mByteBuffer.limit()];
        mByteBuffer.get(ret);
        return ret;
    }

    /**
     * Converting byte array into object.
     *
     * @param byteArray byte array of ClassA
     */
    public void serialFromBuffer(byte[] byteArray) {
        ByteBuffer mByteBuffer = ByteBuffer.wrap(byteArray);
        mByteBuffer.order(ByteOrder.LITTLE_ENDIAN);

        mByteBuffer.get(this.mByteArray);
        this.mShort = (short) mByteBuffer.getShort();
        this.mByte = mByteBuffer.get();

    }

    @Override
    public String toString() {
        return "ClassA{" +
                "mByteArray=" + Arrays.toString(mByteArray) +
                ", mShort=" + mShort +
                ", mByte=" + mByte +
                '}';
    }
}

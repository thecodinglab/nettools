package ch.thecodinglab.nettools;

public class ByteBuffer extends Pointer {

    public ByteBuffer(long capacity) {
        mNativeHandle = WinNative.nBufferCreate(capacity);
        GarbageCollector.registerPointer(mNativeHandle, GarbageCollector.DeleteFunc.DELETE_OBJECT);
    }

    public long getNativeBufferAtOffset() {
        return WinNative.nBufferGetAtPosition(mNativeHandle);
    }

    public long getCapacity() {
        return WinNative.nBufferGetCapacity(mNativeHandle);
    }

    public long getLimit() {
        return WinNative.nBufferGetLimit(mNativeHandle);
    }

    public long getOffset() {
        return WinNative.nBufferGetOffset(mNativeHandle);
    }

    public void setLimit(long limit) {
        WinNative.nBufferSetLimit(mNativeHandle, limit);
    }

    public void setOffset(long offset) {
        WinNative.nBufferSetOffset(mNativeHandle, offset);
    }

    public void flip() {
        WinNative.nBufferFlip(mNativeHandle);
    }

    public byte getByte(long off) {
        return WinNative.nBufferGetI8(mNativeHandle, off);
    }

    public short getShort(long off) {
        return WinNative.nBufferGetI16(mNativeHandle, off);
    }

    public int getInt(long off) {
        return WinNative.nBufferGetI32(mNativeHandle, off);
    }

    public long getLong(long off) {
        return WinNative.nBufferGetI64(mNativeHandle, off);
    }

    public void putByte(long off, byte val) {
        WinNative.nBufferPutI8(mNativeHandle, off, val);
    }

    public void putShort(long off, short val) {
        WinNative.nBufferPutI16(mNativeHandle, off, val);
    }

    public void putInt(long off, int val) {
        WinNative.nBufferPutI32(mNativeHandle, off, val);
    }

    public void putLong(long off, long val) {
        WinNative.nBufferPutI64(mNativeHandle, off, val);
    }

    public byte getByte() {
        return WinNative.nBufferGetI8(mNativeHandle);
    }

    public short getShort() {
        return WinNative.nBufferGetI16(mNativeHandle);
    }

    public int getInt() {
        return WinNative.nBufferGetI32(mNativeHandle);
    }

    public long getLong() {
        return WinNative.nBufferGetI64(mNativeHandle);
    }

    public void putByte(byte val) {
        WinNative.nBufferPutI8(mNativeHandle, val);
    }

    public void putShort(short val) {
        WinNative.nBufferPutI16(mNativeHandle, val);
    }

    public void putInt(int val) {
        WinNative.nBufferPutI32(mNativeHandle, val);
    }

    public void putLong(long val) {
        WinNative.nBufferPutI64(mNativeHandle, val);
    }
}

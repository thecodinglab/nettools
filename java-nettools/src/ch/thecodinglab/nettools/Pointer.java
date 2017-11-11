package ch.thecodinglab.nettools;

public class Pointer {

    protected long mNativeHandle;

    public long getNativeHandle() {
        return mNativeHandle;
    }

    public void delete() {
        GarbageCollector.delete(mNativeHandle);
        mNativeHandle = 0;
    }
}

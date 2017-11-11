package ch.thecodinglab.nettools;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class GarbageCollector {

    private static final HashMap<Long, PtrData> sPointers = new HashMap<>();

    public static void registerPointer(long pointer, DeleteFunc deleteFunc) {
        PtrData data = new PtrData();
        data.mDeleteFunc = deleteFunc;

        StackTraceElement[] stackTrace = Thread.currentThread().getStackTrace();
        data.mRegisterer = stackTrace[2];

        sPointers.put(pointer, data);
    }

    public static void unregisterPointer(long pointer) {
        sPointers.remove(pointer);
    }

    public static void delete(long ptr) {
        if (ptr == 0) return;
        PtrData data = sPointers.remove(ptr);
        if (data == null) return;

        switch (data.mDeleteFunc) {
            case FREE:
                WinNative.nFree(ptr);
                break;
            case DELETE_OBJECT:
                WinNative.nDeleteObject(ptr);
                break;
            case DELETE_ARRAY:
                WinNative.nDeleteArray(ptr);
                break;
        }
    }

    public static void cleanup() {
        for (Iterator<Map.Entry<Long, PtrData>> itr = sPointers.entrySet().iterator(); itr.hasNext(); ) {
            Map.Entry<Long, PtrData> entry = itr.next();
            PtrData data = entry.getValue();
            System.err.printf("WARNING: Needed to clean pointer 0x%x registered in %s\n", entry.getKey(), data.mRegisterer.toString());
            switch (data.mDeleteFunc) {
                case FREE:
                    WinNative.nFree(entry.getKey());
                    break;
                case DELETE_OBJECT:
                    WinNative.nDeleteObject(entry.getKey());
                    break;
                case DELETE_ARRAY:
                    WinNative.nDeleteArray(entry.getKey());
                    break;
            }
        }
    }

    public enum DeleteFunc {
        FREE,
        DELETE_OBJECT,
        DELETE_ARRAY
    }

    private static class PtrData {
        DeleteFunc mDeleteFunc;
        StackTraceElement mRegisterer;
    }
}

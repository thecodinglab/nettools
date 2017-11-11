package ch.thecodinglab.nettools;

import java.util.Arrays;

public class SocketAddress {

    private byte[] mAddress;
    private short mPort;

    public SocketAddress() {
        mAddress = new byte[4];
        mPort = 0;
    }

    public SocketAddress(byte[] address, short port) {
        mAddress = address;
        mPort = port;
    }

    public byte[] getAddress() {
        return mAddress;
    }

    public short getPort() {
        return mPort;
    }

    public void setPort(short port) {
        mPort = port;
    }

    public long toNative() {
        long pointer = WinNative.nSocketAddressCreate();
        GarbageCollector.registerPointer(pointer, GarbageCollector.DeleteFunc.DELETE_OBJECT);
        WinNative.nSocketAddressSetAddress(pointer, mAddress);
        WinNative.nSocketAddressSetPort(pointer, mPort);
        return pointer;
    }

    public void update(long pointer) {
        byte[] address = WinNative.nSocketAddressGetAddress(pointer);
        System.arraycopy(address,0, mAddress, 0, 4);
        mPort = WinNative.nSocketAddressGetPort(pointer);
    }

    @Override
    public String toString() {
        return (mAddress[0] & 0xff) + "." + (mAddress[1] & 0xff) + "." +(mAddress[2] & 0xff) + "." +(mAddress[3] & 0xff) + ":" + mPort;
    }
}

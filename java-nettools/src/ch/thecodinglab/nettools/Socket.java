package ch.thecodinglab.nettools;

import java.io.Closeable;
import java.io.IOException;
import java.util.Arrays;

public class Socket implements Closeable {

    private long mNativeHandle;

    public Socket(SocketFamily family, SocketType type, IPProtocol protocol) {
        mNativeHandle = WinNative.nSocketCreate(family.getWinNative(), type.getWinNative(), protocol.getWinNative());
    }

    private Socket(long nativeHandle) {
        mNativeHandle = nativeHandle;
    }

    public long getNativeHandle() {
        return mNativeHandle;
    }
    public void bind(SocketAddress address) {
        long addressPointer = address.toNative();
        WinNative.nSocketBind(mNativeHandle, addressPointer);
        GarbageCollector.delete(addressPointer);
    }

    public void connect(SocketAddress address) {
        long addressPointer = address.toNative();
        WinNative.nSocketConnect(mNativeHandle, addressPointer);
        GarbageCollector.delete(addressPointer);
    }

    public void listen() {
        WinNative.nSocketListen(mNativeHandle);
    }

    public Socket accept(SocketAddress address) {
        long addressPointer = address.toNative();
        long socket = WinNative.nSocketAccept(mNativeHandle, addressPointer);
        address.update(addressPointer);
        GarbageCollector.delete(addressPointer);

        return new Socket(socket);
    }

    public void send(ByteBuffer buffer) {
        WinNative.nSocketSend(mNativeHandle, buffer.getNativeHandle());
    }

    public int read(ByteBuffer buffer) {
        return WinNative.nSocketRead(mNativeHandle, buffer.getNativeHandle());
    }

    public void sendTo(ByteBuffer buffer, SocketAddress receiver) {
        long addressPointer = receiver.toNative();
        WinNative.nSocketSendTo(mNativeHandle, buffer.getNativeHandle(), addressPointer);
        GarbageCollector.delete(addressPointer);
    }

    public int readFrom(ByteBuffer buffer, SocketAddress receiver) {
        long addressPointer = receiver.toNative();
        int read = WinNative.nSocketReadFrom(mNativeHandle, buffer.getNativeHandle(), addressPointer);
        receiver.update(addressPointer);
        GarbageCollector.delete(addressPointer);

        return read;
    }

    public void configureBlocking(boolean blocking) {
        WinNative.nSocketConfigureBlocking(mNativeHandle, blocking);
    }

    public void configureBroadcast(boolean broadcast) {
        WinNative.nSocketConfigureBroadcast(mNativeHandle, broadcast);
    }

    public void configureSendTimeout(long timeout) {
        WinNative.nSocketConfigureSendTimeout(mNativeHandle, timeout);
    }

    public void configureReadTimeout(long timeout) {
        WinNative.nSocketConfigureReadTimeout(mNativeHandle, timeout);
    }

    public void doUDPBroadcastMethodAllAtOnce(ByteBuffer buffer, NetworkInterface iface, short port) {
        // TODO
        throw new UnsupportedOperationException("This is not supported right now");
    }

    public void doUDPBroadcastMethodOneATime(ByteBuffer buffer, NetworkInterface iface, short port) {
        // TODO
        throw new UnsupportedOperationException("This is not supported right now");
    }

    @Override
    public void close() {
        WinNative.nSocketClose(mNativeHandle);
        mNativeHandle = 0;
    }

    public static void initialize() {
        WinNative.nSocketInit();
    }

    public static void cleanup() {
        WinNative.nSocketCleanup();
    }
}

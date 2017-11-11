package ch.thecodinglab.nettools;

import java.util.Arrays;

public class Test {

    public static void main(String[] args) {
        WinNative.loadLibrary();

        Socket.initialize();

        NetworkInterface iface = NetworkInterface.query();
        SocketAddress address = new SocketAddress(iface.getUnicastAddress(), (short) 12346);

        Socket socket = new Socket(SocketFamily.AF_INET, SocketType.SOCK_DGRAM, IPProtocol.IPPROTO_UDP);
        socket.bind(address);

        ByteBuffer buffer = new ByteBuffer(1024);
        SocketAddress client = new SocketAddress();
        socket.readFrom(buffer, client);
        buffer.flip();
        System.out.println(buffer.getInt());

        buffer.setOffset(0);
        buffer.setLimit(buffer.getCapacity());

        buffer.putInt(98745);
        buffer.flip();

        socket.sendTo(buffer, client);

        buffer.delete();
        socket.close();

        Socket.cleanup();
        GarbageCollector.cleanup();
    }
}

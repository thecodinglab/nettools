package ch.thecodinglab.nettools;

import java.io.File;

public class Test implements Discovery.Callback {

    boolean finished;

    @Override
    public boolean discoveryRequestReceived(SocketAddress address) {
        return true;
    }

    @Override
    public void discoveryClientFound(SocketAddress address) {
        System.out.println("Found: " + address.toString());
        Discovery.ping(address);
    }

    @Override
    public void discoveryPingResult(SocketAddress address, int time, boolean reachable) {
        System.out.println(address.toString() + " " + time + "ms " + reachable);
        finished = true;
    }

    public static void main(String[] args) {
        //WinNative.loadLibrary(new File("..\\bin\\Debug\\"));
        WinNative.loadLibrary(new File("native"));

        Socket.initialize();

        Test test = new Test();

        Discovery.initailize((short) 12346);
        Discovery.setCallback(test);

        long started = System.currentTimeMillis();
        System.out.println("TEST");
        Discovery.search((short) 12345, false);
        long needed = System.currentTimeMillis() - started;
        System.out.println("Took " + needed + "ms");

        while (!test.finished) {
            Discovery.update();
        }

        Discovery.close();
        Socket.cleanup();
        GarbageCollector.cleanup();
    }
}

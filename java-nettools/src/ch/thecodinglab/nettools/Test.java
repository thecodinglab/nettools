package ch.thecodinglab.nettools;

import java.io.File;
import java.util.Arrays;

public class Test {

    public static void main(String[] args) {
        WinNative.loadLibrary(new File("P:\\C++\\win-nettools\\bin\\Debug\\"));
        //WinNative.loadLibrary(new File("native"));

        Socket.initialize();

        Discovery.initailize((short) 12346);
        Discovery.setCallback(new Discovery.Callback() {
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
            }
        });

        while (true) {
            Discovery.update();
        }

        /*Socket.cleanup();
        GarbageCollector.cleanup();*/
    }
}

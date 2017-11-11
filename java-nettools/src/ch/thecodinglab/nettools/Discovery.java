package ch.thecodinglab.nettools;

public class Discovery implements WinNative.NDiscoveryCallback {

    private static final Discovery sInstance = new Discovery();
    private static Callback sCallback = null;

    private Discovery() {
    }

    @Override
    public boolean nCallbackDiscoveryRequest(long client) {
        if (sCallback != null) {
            SocketAddress address = new SocketAddress();
            address.update(client);

            return sCallback.discoveryRequestReceived(address);
        }
        return true;
    }

    @Override
    public void nCallbackDiscoveryFound(long client) {
        if (sCallback != null) {
            SocketAddress address = new SocketAddress();
            address.update(client);

            sCallback.discoveryClientFound(address);
        }
    }

    public static void initailize(short port) {
        WinNative.nDiscoveryInit(port);
        WinNative.nDiscoverySetHandlers(sInstance);
    }

    public static void setCallback(Callback callback) {
        sCallback = callback;
    }

    public static void search(short port, boolean allAtOnce) {
        WinNative.nDiscoverySearch(port, allAtOnce);
    }

    public static void update() {
        WinNative.nDiscoveryUpdate();
    }

    public static void close() {
        WinNative.nDiscoveryClose();
    }

    public interface Callback {

        boolean discoveryRequestReceived(SocketAddress address);
        void discoveryClientFound(SocketAddress address);
    }
}

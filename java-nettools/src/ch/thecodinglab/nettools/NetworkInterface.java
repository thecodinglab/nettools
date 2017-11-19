package ch.thecodinglab.nettools;

public class NetworkInterface {

    private byte[] mUnicastAddress;
    private byte[] mSubnetAddress;
    private byte[] mNetworkAddress;
    private byte[] mBroadcastAddress;

    private NetworkInterface(byte[] unicastAddress, byte[] subnetAddress, byte[] networkAddress, byte[] broadcastAddress) {
        mUnicastAddress = unicastAddress;
        mSubnetAddress = subnetAddress;
        mNetworkAddress = networkAddress;
        mBroadcastAddress = broadcastAddress;
    }

    public byte[] getUnicastAddress() {
        return mUnicastAddress;
    }

    public byte[] getSubnetAddress() {
        return mSubnetAddress;
    }

    public byte[] getNetworkAddress() {
        return mNetworkAddress;
    }

    public byte[] getBroadcastAddress() {
        return mBroadcastAddress;
    }

    public static NetworkInterface query() {
        long iface = WinNative.nInterfaceQuery();
        GarbageCollector.registerPointer(iface, GarbageCollector.DeleteFunc.DELETE_ARRAY);
        byte[] unicastAddress = WinNative.nInterfaceGetUnicastAddress(iface);
        byte[] subnetAddress = WinNative.nInterfaceGetSubnetAddress(iface);
        byte[] networkAddress = WinNative.nInterfaceGetNetworkAddress(iface);
        byte[] broadcastAddress = WinNative.nInterfaceGetBroadcastAddress(iface);
        GarbageCollector.delete(iface);

        return new NetworkInterface(unicastAddress, subnetAddress, networkAddress, broadcastAddress);
    }
}

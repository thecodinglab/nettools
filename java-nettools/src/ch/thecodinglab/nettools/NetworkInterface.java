package ch.thecodinglab.nettools;

public class NetworkInterface {

    private byte[] mUnicastAddress;
    private byte[] mDnsServerAddress;
    private byte[] mGatewayAddress;
    private int mSubnetPrefix;
    private byte[] mNetworkAddress;
    private byte[] mBroadcastAddress;

    private NetworkInterface(byte[] unicastAddress, byte[] dnsServerAddress, byte[] gatewayAddress, int subnetPrefix, byte[] networkAddress, byte[] broadcastAddress) {
        mUnicastAddress = unicastAddress;
        mDnsServerAddress = dnsServerAddress;
        mGatewayAddress = gatewayAddress;
        mSubnetPrefix = subnetPrefix;
        mNetworkAddress = networkAddress;
        mBroadcastAddress = broadcastAddress;
    }

    public byte[] getUnicastAddress() {
        return mUnicastAddress;
    }

    public byte[] getDnsServerAddress() {
        return mDnsServerAddress;
    }

    public byte[] getGatewayAddress() {
        return mGatewayAddress;
    }

    public int getSubnetPrefix() {
        return mSubnetPrefix;
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
        byte[] dnsServerAddress = WinNative.nInterfaceGetDnsServerAddress(iface);
        byte[] gatewayAddress = WinNative.nInterfaceGetGatewayAddress(iface);
        int subnetPrefix = WinNative.nInterfaceGetSubnetPrefix(iface) & 0xff;
        byte[] networkAddress = WinNative.nInterfaceGetNetworkAddress(iface);
        byte[] broadcastAddress = WinNative.nInterfaceGetBroadcastAddress(iface);
        GarbageCollector.delete(iface);

        return new NetworkInterface(unicastAddress, dnsServerAddress, gatewayAddress, subnetPrefix, networkAddress, broadcastAddress);
    }
}

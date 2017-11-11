package ch.thecodinglab.nettools;

public class NetworkInterface {

    private byte[] mUnicastAddress;
    private byte[] mMulticastAddress;
    private byte[] mDnsServerAddress;
    private byte[] mGatewayAddress;
    private int mSubnetPrefix;

    private NetworkInterface(byte[] unicastAddress, byte[] multicastAddress, byte[] dnsServerAddress, byte[] gatewayAddress, int subnetPrefix) {
        mUnicastAddress = unicastAddress;
        mMulticastAddress = multicastAddress;
        mDnsServerAddress = dnsServerAddress;
        mGatewayAddress = gatewayAddress;
        mSubnetPrefix = subnetPrefix;
    }

    public byte[] getUnicastAddress() {
        return mUnicastAddress;
    }

    public byte[] getMulticastAddress() {
        return mMulticastAddress;
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

    public static NetworkInterface query() {
        long iface = WinNative.nInterfaceQuery();
        GarbageCollector.registerPointer(iface, GarbageCollector.DeleteFunc.DELETE_ARRAY);
        byte[] unicastAddress = WinNative.nInterfaceGetUnicastAddress(iface);
        byte[] multicastAddress = WinNative.nInterfaceGetMulticastAddress(iface);
        byte[] dnsServerAddress = WinNative.nInterfaceGetDnsServerAddress(iface);
        byte[] gatewayAddress = WinNative.nInterfaceGetGatewayAddress(iface);
        int subnetPrefix = WinNative.nInterfaceGetSubnetPrefix(iface) & 0xff;
        GarbageCollector.delete(iface);

        return new NetworkInterface(unicastAddress, multicastAddress, dnsServerAddress, gatewayAddress, subnetPrefix);
    }
}

package ch.thecodinglab.nettools;

import java.io.File;

public class WinNative {

    public static final int AF_UNSPEC = 0; // unspecified
    public static final int AF_UNIX = 1; // local to host (pipes; portals)
    public static final int AF_INET = 2; // internetwork: UDP; TCP; etc.
    public static final int AF_IMPLINK = 3; // arpanet imp addresses
    public static final int AF_PUP = 4; // pup protocols: e.g. BSP
    public static final int AF_CHAOS = 5; // mit CHAOS protocols
    public static final int AF_NS = 6; // XEROX NS protocols
    public static final int AF_IPX = AF_NS; // IPX protocols: IPX; SPX; etc.
    public static final int AF_ISO = 7; // ISO protocols
    public static final int AF_OSI = AF_ISO; // OSI is ISO
    public static final int AF_ECMA = 8; // european computer manufacturers
    public static final int AF_DATAKIT = 9; // datakit protocols
    public static final int AF_CCITT = 10; // CCITT protocols; X.25 etc
    public static final int AF_SNA = 11; // IBM SNA
    public static final int AF_DECnet = 12; // DECnet
    public static final int AF_DLI = 13; // Direct data link interface
    public static final int AF_LAT = 14; // LAT
    public static final int AF_HYLINK = 15; // NSC Hyperchannel
    public static final int AF_APPLETALK = 16; // AppleTalk
    public static final int AF_NETBIOS = 17; // NetBios-style addresses
    public static final int AF_VOICEVIEW = 18; // VoiceView
    public static final int AF_FIREFOX = 19; // Protocols from Firefox
    public static final int AF_UNKNOWN1 = 20; // Somebody is using this!
    public static final int AF_BAN = 21; // Banyan
    public static final int AF_ATM = 22; // WinNative ATM Services
    public static final int AF_INET6 = 23; // Internetwork Version 6
    public static final int AF_CLUSTER = 24; // Microsoft Wolfpack
    public static final int AF_12844 = 25; // IEEE 1284.4 WG AF
    public static final int AF_IRDA = 26; // IrDA
    public static final int AF_NETDES = 28; // Network Designers OSI & gateway

    public static final int SOCK_STREAM = 1; // stream socket
    public static final int SOCK_DGRAM = 2; // datagram socket
    public static final int SOCK_RAW = 3; // raw-protocol interface
    public static final int SOCK_RDM = 4; // reliably-delivered message
    public static final int SOCK_SEQPACKET = 5; // sequenced packet stream

    public static final int IPPROTO_HOPOPTS = 0;  // IPv6 Hop-by-Hop options
    public static final int IPPROTO_ICMP = 1;
    public static final int IPPROTO_IGMP = 2;
    public static final int IPPROTO_GGP = 3;
    public static final int IPPROTO_IPV4 = 4;
    public static final int IPPROTO_ST = 5;
    public static final int IPPROTO_TCP = 6;
    public static final int IPPROTO_CBT = 7;
    public static final int IPPROTO_EGP = 8;
    public static final int IPPROTO_IGP = 9;
    public static final int IPPROTO_PUP = 12;
    public static final int IPPROTO_UDP = 17;
    public static final int IPPROTO_IDP = 22;
    public static final int IPPROTO_RDP = 27;
    public static final int IPPROTO_IPV6 = 41; // IPv6 header
    public static final int IPPROTO_ROUTING = 43; // IPv6 Routing header
    public static final int IPPROTO_FRAGMENT = 44; // IPv6 fragmentation header
    public static final int IPPROTO_ESP = 50; // encapsulating security payload
    public static final int IPPROTO_AH = 51; // authentication header
    public static final int IPPROTO_ICMPV6 = 58; // ICMPv6
    public static final int IPPROTO_NONE = 59; // IPv6 no next header
    public static final int IPPROTO_DSTOPTS = 60; // IPv6 Destination options
    public static final int IPPROTO_ND = 77;
    public static final int IPPROTO_ICLFXBM = 78;
    public static final int IPPROTO_PIM = 103;
    public static final int IPPROTO_PGM = 113;
    public static final int IPPROTO_L2TP = 115;
    public static final int IPPROTO_SCTP = 132;
    public static final int IPPROTO_RAW = 255;
    public static final int IPPROTO_MAX = 256;

    public static void loadLibrary(File nativesFolder) {
        String arch = System.getProperty("os.arch");

        String archExtension;
        if (arch.contains("64")) {
            archExtension = "x64";
        } else {
            archExtension = "x86";
        }

        File nettoolsFile = new File(nativesFolder, "win-nettools_" + archExtension + ".dll");
        File libraryFile = new File(nativesFolder, "jni_nettools_" + archExtension + ".dll");

        System.load(nettoolsFile.getAbsolutePath());
        System.load(libraryFile.getAbsolutePath());
    }

    public static native void nFree(long ptr);
    public static native void nDeleteObject(long ptr);
    public static native void nDeleteArray(long ptr);

    public static native long nBufferCreate(long capacity);
    public static native long nBufferGetAtPosition(long buffer);
    public static native long nBufferGetCapacity(long buffer);
    public static native long nBufferGetLimit(long buffer);
    public static native long nBufferGetOffset(long buffer);
    public static native void nBufferSetLimit(long buffer, long limit);
    public static native void nBufferSetOffset(long buffer, long offset);
    public static native void nBufferFlip(long buffer);
    public static native void nBufferReset(long buffer);
    public static native void nBufferGet(long buffer, long offset, long destination, long size);
    public static native byte nBufferGetI8(long buffer, long offset);
    public static native short nBufferGetI16(long buffer, long offset);
    public static native int nBufferGetI32(long buffer, long offset);
    public static native long nBufferGetI64(long buffer, long offset);
    public static native void nBufferPut(long buffer, long offset, long source, long size);
    public static native void nBufferPutI8(long buffer, long offset, byte value);
    public static native void nBufferPutI16(long buffer, long offset, short value);
    public static native void nBufferPutI32(long buffer, long offset, int value);
    public static native void nBufferPutI64(long buffer, long offset, long value);
    public static native void nBufferGet(long buffer, long destination, long size);
    public static native byte nBufferGetI8(long buffer);
    public static native short nBufferGetI16(long buffer);
    public static native int nBufferGetI32(long buffer);
    public static native long nBufferGetI64(long buffer);
    public static native void nBufferPut(long buffer, long source, long size);
    public static native void nBufferPutI8(long buffer, byte value);
    public static native void nBufferPutI16(long buffer, short value);
    public static native void nBufferPutI32(long buffer, int value);
    public static native void nBufferPutI64(long buffer, long value);

    public static native long nSocketAddressCreate();
    public static native byte[] nSocketAddressGetAddress(long address);
    public static native short nSocketAddressGetPort(long address);
    public static native void nSocketAddressSetAddress(long address, byte[] value);
    public static native void nSocketAddressSetPort(long address, short port);

    public static native long nInterfaceQuery();
    public static native byte[] nInterfaceGetUnicastAddress(long iface);
    public static native byte[] nInterfaceGetDnsServerAddress(long iface);
    public static native byte[] nInterfaceGetGatewayAddress(long iface);
    public static native byte nInterfaceGetSubnetPrefix(long iface);
    public static native byte[] nInterfaceGetNetworkAddress(long iface);
    public static native byte[] nInterfaceGetBroadcastAddress(long iface);

    public static native void nSocketInit();
    public static native void nSocketCleanup();
    public static native long nSocketCreate(int family, int type, int protocol);
    public static native void nSocketBind(long socket, long address);
    public static native void nSocketConnect(long socket, long address);
    public static native void nSocketListen(long socket);
    public static native long nSocketAccept(long socket, long address);
    public static native void nSocketSend(long socket, long buffer);
    public static native int nSocketRead(long socket, long buffer);
    public static native void nSocketSendTo(long socket, long buffer, long address);
    public static native int nSocketReadFrom(long socket, long buffer, long address);
    public static native void nSocketClose(long socket);
    public static native void nSocketConfigureBlocking(long socket, boolean blocking);
    public static native void nSocketConfigureBroadcast(long socket, boolean broadcast);
    public static native void nSocketConfigureSendTimeout(long socket, long timeout);
    public static native void nSocketConfigureReadTimeout(long socket, long timeout);
    public static native void nSocketUDPBroadcastMethodAllAtOnce(long socket, long buffer, long iface, short port);
    public static native void nSocketUDPBroadcastMethodOneATime(long socket, long buffer, long iface, short port);

    public static native void nDiscoveryInit(short port);
    public static native void nDiscoverySetHandlers(NDiscoveryCallback callback);
    public static native void nDiscoverySearch(short port, boolean allAtOnce);
    public static native void nDiscoveryUpdate();
    public static native void nDiscoveryPing(long address);
    public static native void nDiscoveryClose();

    public interface NDiscoveryCallback {
        boolean nCallbackDiscoveryRequest(long client);
        void nCallbackDiscoveryFound(long client);
        void nCallbackDiscoveryPingResult(long client, int time, boolean reachable);
    }
}

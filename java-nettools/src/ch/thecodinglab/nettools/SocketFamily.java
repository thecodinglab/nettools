package ch.thecodinglab.nettools;

public enum SocketFamily {

    AF_UNSPEC(WinNative.AF_UNSPEC), // unspecified
    AF_UNIX(WinNative.AF_UNIX), // local to host (pipes; portals)
    AF_INET(WinNative.AF_INET), // internetwork: UDP; TCP; etc.
    AF_IMPLINK(WinNative.AF_IMPLINK), // arpanet imp addresses
    AF_PUP(WinNative.AF_PUP), // pup protocols: e.g. BSP
    AF_CHAOS(WinNative.AF_CHAOS), // mit CHAOS protocols
    AF_NS(WinNative.AF_NS), // XEROX NS protocols
    AF_IPX(WinNative.AF_IPX), // IPX protocols: IPX; SPX; etc.
    AF_ISO(WinNative.AF_ISO), // ISO protocols
    AF_OSI(WinNative.AF_OSI), // OSI is ISO
    AF_ECMA(WinNative.AF_ECMA), // european computer manufacturers
    AF_DATAKIT(WinNative.AF_DATAKIT), // datakit protocols
    AF_CCITT(WinNative.AF_CCITT), // CCITT protocols; X.25 etc
    AF_SNA(WinNative.AF_SNA), // IBM SNA
    AF_DECnet(WinNative.AF_DECnet), // DECnet
    AF_DLI(WinNative.AF_DLI), // Direct data link interface
    AF_LAT(WinNative.AF_LAT), // LAT
    AF_HYLINK(WinNative.AF_HYLINK), // NSC Hyperchannel
    AF_APPLETALK(WinNative.AF_APPLETALK), // AppleTalk
    AF_NETBIOS(WinNative.AF_NETBIOS), // NetBios-style addresses
    AF_VOICEVIEW(WinNative.AF_VOICEVIEW), // VoiceView
    AF_FIREFOX(WinNative.AF_FIREFOX), // Protocols from Firefox
    AF_UNKNOWN1(WinNative.AF_UNKNOWN1), // Somebody is using this!
    AF_BAN(WinNative.AF_BAN), // Banyan
    AF_ATM(WinNative.AF_ATM), // WinNative ATM Services
    AF_INET6(WinNative.AF_INET6), // Internetwork Version 6
    AF_CLUSTER(WinNative.AF_CLUSTER), // Microsoft Wolfpack
    AF_12844(WinNative.AF_12844), // IEEE 1284.4 WG AF
    AF_IRDA(WinNative.AF_IRDA), // IrDA
    AF_NETDES(WinNative.AF_NETDES); // Network Designers OSI & gateway

    private final int mWinNative;

    SocketFamily(int winNative) {
        mWinNative = winNative;
    }

    public int getWinNative() {
        return mWinNative;
    }
}

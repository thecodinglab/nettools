package ch.thecodinglab.nettools;

public enum IPProtocol {

    IPPROTO_HOPOPTS(WinNative.IPPROTO_HOPOPTS),  // IPv6 Hop-by-Hop options
    IPPROTO_ICMP(WinNative.IPPROTO_ICMP),
    IPPROTO_IGMP(WinNative.IPPROTO_IGMP),
    IPPROTO_GGP(WinNative.IPPROTO_GGP),
    IPPROTO_IPV4(WinNative.IPPROTO_IPV4),
    IPPROTO_ST(WinNative.IPPROTO_ST),
    IPPROTO_TCP(WinNative.IPPROTO_TCP),
    IPPROTO_CBT(WinNative.IPPROTO_CBT),
    IPPROTO_EGP(WinNative.IPPROTO_EGP),
    IPPROTO_IGP(WinNative.IPPROTO_IGP),
    IPPROTO_PUP(WinNative.IPPROTO_PUP),
    IPPROTO_UDP(WinNative.IPPROTO_UDP),
    IPPROTO_IDP(WinNative.IPPROTO_IDP),
    IPPROTO_RDP(WinNative.IPPROTO_RDP),
    IPPROTO_IPV6(WinNative.IPPROTO_IPV6), // IPv6 header
    IPPROTO_ROUTING(WinNative.IPPROTO_ROUTING), // IPv6 Routing header
    IPPROTO_FRAGMENT(WinNative.IPPROTO_FRAGMENT), // IPv6 fragmentation header
    IPPROTO_ESP(WinNative.IPPROTO_ESP), // encapsulating security payload
    IPPROTO_AH(WinNative.IPPROTO_AH), // authentication header
    IPPROTO_ICMPV6(WinNative.IPPROTO_ICMPV6), // ICMPv6
    IPPROTO_NONE(WinNative.IPPROTO_NONE), // IPv6 no next header
    IPPROTO_DSTOPTS(WinNative.IPPROTO_DSTOPTS), // IPv6 Destination options
    IPPROTO_ND(WinNative.IPPROTO_ND),
    IPPROTO_ICLFXBM(WinNative.IPPROTO_ICLFXBM),
    IPPROTO_PIM(WinNative.IPPROTO_PIM),
    IPPROTO_PGM(WinNative.IPPROTO_PGM),
    IPPROTO_L2TP(WinNative.IPPROTO_L2TP),
    IPPROTO_SCTP(WinNative.IPPROTO_SCTP),
    IPPROTO_RAW(WinNative.IPPROTO_RAW),
    IPPROTO_MAX(WinNative.IPPROTO_MAX);

    private final int mWinNative;

    IPProtocol(int winNative) {
        mWinNative = winNative;
    }

    public int getWinNative() {
        return mWinNative;
    }
}

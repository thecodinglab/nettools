package ch.thecodinglab.nettools;

public enum SocketType {

    SOCK_STREAM(WinNative.SOCK_STREAM), // stream socket
    SOCK_DGRAM(WinNative.SOCK_DGRAM), // datagram socket
    SOCK_RAW(WinNative.SOCK_RAW), // raw-protocol interface
    SOCK_RDM(WinNative.SOCK_RDM), // reliably-delivered message
    SOCK_SEQPACKET(WinNative.SOCK_SEQPACKET); // sequenced packet stream

    private final int mWinNative;

    SocketType(int winNative) {
        mWinNative = winNative;
    }

    public int getWinNative() {
        return mWinNative;
    }
}

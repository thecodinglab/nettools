#pragma once

#ifdef _WIN32
#include <win32/jni_md.h>
#else
#include <linux/jni_md.h>
#define JNIEXPORT
#define JNICALL
#endif
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nFree(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDeleteObject(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDeleteArray(JNIEnv*, jclass, jlong);

    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferCreate(JNIEnv*, jclass, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetAtPosition(JNIEnv*, jclass, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetCapacity(JNIEnv*, jclass, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetLimit(JNIEnv*, jclass, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetOffset(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferSetLimit(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferSetOffset(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferFlip(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferReset(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGet__JJJJ(JNIEnv*, jclass, jlong, jlong, jlong, jlong);
    JNIEXPORT jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI8__JJ(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI16__JJ(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI32__JJ(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI64__JJ(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPut__JJJJ(JNIEnv*, jclass, jlong, jlong, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI8__JJB(JNIEnv*, jclass, jlong, jlong, jbyte);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI16__JJS(JNIEnv*, jclass, jlong, jlong, jshort);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI32__JJI(JNIEnv*, jclass, jlong, jlong, jint);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI64__JJJ(JNIEnv*, jclass, jlong, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGet__JJJ(JNIEnv*, jclass, jlong, jlong, jlong);
    JNIEXPORT jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI8__J(JNIEnv*, jclass, jlong);
    JNIEXPORT jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI16__J(JNIEnv*, jclass, jlong);
    JNIEXPORT jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI32__J(JNIEnv*, jclass, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI64__J(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPut__JJJ(JNIEnv*, jclass, jlong, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI8__JB(JNIEnv*, jclass, jlong, jbyte);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI16__JS(JNIEnv*, jclass, jlong, jshort);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI32__JI(JNIEnv*, jclass, jlong, jint);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI64__JJ(JNIEnv*, jclass, jlong, jlong);

    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressCreate(JNIEnv*, jclass);
    JNIEXPORT jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressGetAddress(JNIEnv*, jclass, jlong);
    JNIEXPORT jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressGetPort(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressSetAddress(JNIEnv*, jclass, jlong, jbyteArray);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressSetPort(JNIEnv*, jclass, jlong, jshort);

    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceQuery(JNIEnv*, jclass);
    JNIEXPORT jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetUnicastAddress(JNIEnv*, jclass, jlong);
    JNIEXPORT jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetSubnetAddress(JNIEnv*, jclass, jlong);
    JNIEXPORT jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetNetworkAddress(JNIEnv*, jclass, jlong);
    JNIEXPORT jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetBroadcastAddress(JNIEnv*, jclass, jlong);

    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketInit(JNIEnv*, jclass);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketCleanup(JNIEnv*, jclass);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketCreate(JNIEnv*, jclass, jint, jint, jint);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketBind(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConnect(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketListen(JNIEnv*, jclass, jlong);
    JNIEXPORT jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAccept(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketSend(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketRead(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketSendTo(JNIEnv*, jclass, jlong, jlong, jlong);
    JNIEXPORT jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketReadFrom(JNIEnv*, jclass, jlong, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketClose(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureBlocking(JNIEnv*, jclass, jlong, jboolean);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureBroadcast(JNIEnv*, jclass, jlong, jboolean);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureSendTimeout(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureReadTimeout(JNIEnv*, jclass, jlong, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketUDPBroadcastMethodAllAtOnce(JNIEnv*, jclass, jlong, jlong, jlong, jshort);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketUDPBroadcastMethodOneATime(JNIEnv*, jclass, jlong, jlong, jlong, jshort);

    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryInit(JNIEnv*, jclass, jshort);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoverySetHandlers(JNIEnv*, jclass, jobject);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoverySearch(JNIEnv*, jclass, jshort, jboolean);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryUpdate(JNIEnv*, jclass);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryPing(JNIEnv*, jclass, jlong);
    JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryClose(JNIEnv*, jclass);
#ifdef __cplusplus
}
#endif

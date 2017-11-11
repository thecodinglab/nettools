#include "jnettools.h"
#include <buffer.h>
#include <socket.h>
#include <interface.h>

JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nFree(JNIEnv*, jclass, jlong ptr)
{
    free(reinterpret_cast<void*>(ptr));
}

JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDeleteObject(JNIEnv*, jclass, jlong ptr)
{
    delete reinterpret_cast<void*>(ptr);
}
JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDeleteArray(JNIEnv*, jclass, jlong ptr)
{
    delete[] reinterpret_cast<void*>(ptr);
}



jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferCreate(JNIEnv*, jclass, jlong capacity)
{
    return reinterpret_cast<jlong>(new nettools::byte_buffer(capacity));
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetAtPosition(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<jlong>(reinterpret_cast<nettools::byte_buffer*>(buffer)->get_buffer_at_offset());
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetCapacity(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_capacity();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetLimit(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_limit();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetOffset(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_offset();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferSetLimit(JNIEnv*, jclass, jlong buffer, jlong limit)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->set_limit(limit);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferSetOffset(JNIEnv*, jclass, jlong buffer, jlong offset)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->set_offset(offset);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferFlip(JNIEnv*, jclass, jlong buffer)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->flip();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferReset(JNIEnv*, jclass, jlong buffer)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->flip();
}

jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI8__JJ(JNIEnv*, jclass, jlong buffer, jlong off)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i8(off);
}

jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI16__JJ(JNIEnv*, jclass, jlong buffer, jlong off)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i16(off);
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI32__JJ(JNIEnv*, jclass, jlong buffer, jlong off)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i32(off);
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI64__JJ(JNIEnv*, jclass, jlong buffer, jlong off)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i64(off);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI8__JJB(JNIEnv*, jclass, jlong buffer, jlong off, jbyte val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i8(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI16__JJS(JNIEnv*, jclass, jlong buffer, jlong off, jshort val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i16(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI32__JJI(JNIEnv*, jclass, jlong buffer, jlong off, jint val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i32(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI64__JJJ(JNIEnv*, jclass, jlong buffer, jlong off, jlong val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i64(off, val);
}

jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI8__J(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i8();
}

jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI16__J(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i16();
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI32__J(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i32();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI64__J(JNIEnv*, jclass, jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer*>(buffer)->get_i64();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI8__JB(JNIEnv*, jclass, jlong buffer, jbyte val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i8(val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI16__JS(JNIEnv*, jclass, jlong buffer, jshort val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i16(val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI32__JI(JNIEnv*, jclass, jlong buffer, jint val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i32(val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI64__JJ(JNIEnv*, jclass, jlong buffer, jlong val)
{
    reinterpret_cast<nettools::byte_buffer*>(buffer)->put_i64(val);
}



jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressCreate(JNIEnv*, jclass)
{
    return reinterpret_cast<jlong>(new nettools::socket_address());
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressGetAddress(JNIEnv* env, jclass, jlong address)
{
    nettools::inet_address addr = reinterpret_cast<nettools::socket_address*>(address)->m_addr;

    jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressGetPort(JNIEnv*, jclass, jlong address)
{
    return reinterpret_cast<nettools::socket_address*>(address)->m_port;
}
void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressSetAddress(JNIEnv* env, jclass, jlong address, jbyteArray val)
{
    u32 addr;
    env->GetByteArrayRegion(val, 0, 4, reinterpret_cast<jbyte*>(&addr));
    reinterpret_cast<nettools::socket_address*>(address)->m_addr.m_address = addr;
}
void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressSetPort(JNIEnv*, jclass, jlong address, jshort val)
{
    reinterpret_cast<nettools::socket_address*>(address)->m_port = val;
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceQuery(JNIEnv*, jclass)
{
    const nettools::network_interface iface = nettools::interface_query();
    nettools::network_interface* result = new nettools::network_interface[1];
    result[0] = iface;
    return reinterpret_cast<jlong>(result);
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetUnicastAddress(JNIEnv* env, jclass, jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface*>(iface)->m_unicast_addr;

    jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetDnsServerAddress(JNIEnv* env, jclass, jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface*>(iface)->m_dns_server_addr;

    jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetGatewayAddress(JNIEnv* env, jclass, jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface*>(iface)->m_gateway_addr;

    jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}
jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetSubnetPrefix(JNIEnv*, jclass, jlong iface)
{
    return reinterpret_cast<nettools::network_interface*>(iface)->m_subnet_prefix;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetNetworkAddress(JNIEnv* env, jclass, jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface*>(iface)->m_network_addr;

    jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetBroadcastAddress(JNIEnv* env, jclass, jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface*>(iface)->m_broadcast_addr;

    jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}


void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketInit(JNIEnv*, jclass)
{
    nettools::socket_init();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketCleanup(JNIEnv*, jclass)
{
    nettools::socket_cleanup();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketCreate(JNIEnv*, jclass, jint family, jint type, jint protocol)
{
    return nettools::socket_create(family, type, protocol);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketBind(JNIEnv*, jclass, jlong socket, jlong address)
{
    nettools::socket_address* addr = reinterpret_cast<nettools::socket_address*>(address);
    nettools::socket_bind(socket, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConnect(JNIEnv*, jclass, jlong socket, jlong address)
{
    nettools::socket_address* addr = reinterpret_cast<nettools::socket_address*>(address);
    nettools::socket_connect(socket, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketListen(JNIEnv*, jclass, jlong socket)
{
    nettools::socket_listen(socket);
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAccept(JNIEnv*, jclass, jlong socket, jlong address)
{
    nettools::socket_address* addr = reinterpret_cast<nettools::socket_address*>(address);
    return nettools::socket_accept(socket, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketSend(JNIEnv*, jclass, jlong socket, jlong buffer)
{
    nettools::byte_buffer* buf = reinterpret_cast<nettools::byte_buffer*>(buffer);
    nettools::socket_send(socket, buf);
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketRead(JNIEnv*, jclass, jlong socket, jlong buffer)
{
    nettools::byte_buffer* buf = reinterpret_cast<nettools::byte_buffer*>(buffer);
    return nettools::socket_read(socket, buf);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketSendTo(JNIEnv*, jclass, jlong socket, jlong buffer, jlong address)
{
    nettools::byte_buffer* buf = reinterpret_cast<nettools::byte_buffer*>(buffer);
    nettools::socket_address* addr = reinterpret_cast<nettools::socket_address*>(address);
    nettools::socket_sendto(socket, buf, addr);
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketReadFrom(JNIEnv*, jclass, jlong socket, jlong buffer, jlong address)
{
    nettools::byte_buffer* buf = reinterpret_cast<nettools::byte_buffer*>(buffer);
    nettools::socket_address* addr = reinterpret_cast<nettools::socket_address*>(address);
    return nettools::socket_readfrom(socket, buf, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketClose(JNIEnv*, jclass, jlong socket)
{
    nettools::socket_close(socket);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureBlocking(JNIEnv*, jclass, jlong socket, jboolean blocking)
{
    nettools::socket_configure_blocking(socket, blocking);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureBroadcast(JNIEnv*, jclass, jlong socket, jboolean broadcast)
{
    nettools::socket_configure_broadcast(socket, broadcast);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureSendTimeout(JNIEnv*, jclass, jlong socket, jlong timeout)
{
    nettools::socket_configure_send_timeout(socket, timeout);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureReadTimeout(JNIEnv*, jclass, jlong socket, jlong timeout)
{
    nettools::socket_configure_read_timeout(socket, timeout);
}

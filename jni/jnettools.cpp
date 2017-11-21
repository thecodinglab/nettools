/*
* nettols is a library for comonly used network stuff for windows and linux
* Copyright (C) 2017  TheCodingLab
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "jnettools.h"
#include <nettools/buffer.h>
#include <nettools/socket.h>
#include <nettools/interface.h>
#include <nettools/udp_utility.h>
#include <nettools/discovery.h>

JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nFree(JNIEnv*, jclass, const jlong ptr)
{
    free(reinterpret_cast<void*>(ptr));
}

JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDeleteObject(JNIEnv*, jclass, const jlong ptr)
{
    delete reinterpret_cast<void*>(ptr);
}
JNIEXPORT void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDeleteArray(JNIEnv*, jclass, const jlong ptr)
{
    delete[] reinterpret_cast<void*>(ptr);
}



jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferCreate(JNIEnv*, jclass, const jlong capacity)
{
    return reinterpret_cast<jlong>(new nettools::byte_buffer(capacity));
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetAtPosition(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<jlong>(reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_buffer_at_offset());
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetCapacity(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_capacity();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetLimit(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_limit();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetOffset(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_offset();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferSetLimit(JNIEnv*, jclass, const jlong buffer, const jlong limit)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->set_limit(limit);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferSetOffset(JNIEnv*, jclass, const jlong buffer, const jlong offset)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->set_offset(offset);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferFlip(JNIEnv*, jclass, const jlong buffer)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->flip();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferReset(JNIEnv*, jclass, const jlong buffer)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->flip();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGet__JJJJ(JNIEnv*, jclass, const jlong buffer, const jlong offset, const jlong destination, const jlong length)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get(offset, reinterpret_cast<void*>(destination), length);
}

jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI8__JJ(JNIEnv*, jclass, const jlong buffer, const jlong off)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i8(off);
}

jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI16__JJ(JNIEnv*, jclass, const jlong buffer, const jlong off)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i16(off);
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI32__JJ(JNIEnv*, jclass, const jlong buffer, const jlong off)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i32(off);
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI64__JJ(JNIEnv*, jclass, const jlong buffer, const jlong off)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i64(off);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPut__JJJJ(JNIEnv*, jclass, const jlong buffer, const jlong offset, const jlong source, const jlong length)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put(offset, reinterpret_cast<void*>(source), length);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI8__JJB(JNIEnv*, jclass, const jlong buffer, const jlong off, const jbyte val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i8(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI16__JJS(JNIEnv*, jclass, const jlong buffer, const jlong off, const jshort val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i16(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI32__JJI(JNIEnv*, jclass, const jlong buffer, const jlong off, const jint val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i32(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI64__JJJ(JNIEnv*, jclass, const jlong buffer, const jlong off, const jlong val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i64(off, val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGet__JJJ(JNIEnv*, jclass, const jlong buffer, const jlong destination, const jlong length)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get(reinterpret_cast<void*>(destination), length);
}

jbyte JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI8__J(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i8();
}

jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI16__J(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i16();
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI32__J(JNIEnv*, jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i32();
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferGetI64__J(JNIEnv*, const jclass, const jlong buffer)
{
    return reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->get_i64();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPut__JJJ(JNIEnv*, jclass, const jlong buffer, const jlong source, const jlong length)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put(reinterpret_cast<void*>(source), length);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI8__JB(JNIEnv*, jclass, const jlong buffer, const jbyte val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i8(val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI16__JS(JNIEnv*, jclass, const jlong buffer, const jshort val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i16(val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI32__JI(JNIEnv*, jclass, const jlong buffer, const jint val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i32(val);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nBufferPutI64__JJ(JNIEnv*, jclass, const jlong buffer, const jlong val)
{
    reinterpret_cast<nettools::byte_buffer_ptr>(buffer)->put_i64(val);
}



jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressCreate(JNIEnv*, jclass)
{
    return reinterpret_cast<jlong>(new nettools::socket_address());
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressGetAddress(JNIEnv* env, jclass, const jlong address)
{
    nettools::inet_address addr = reinterpret_cast<nettools::socket_address_ptr>(address)->m_addr;

    const jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jshort JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressGetPort(JNIEnv*, jclass, const jlong address)
{
    return reinterpret_cast<nettools::socket_address_ptr>(address)->m_port;
}
void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressSetAddress(JNIEnv* env, jclass, const jlong address, const jbyteArray val)
{
    u32 addr;
    env->GetByteArrayRegion(val, 0, 4, reinterpret_cast<jbyte*>(&addr));
    reinterpret_cast<nettools::socket_address_ptr>(address)->m_addr.m_address = addr;
}
void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAddressSetPort(JNIEnv*, jclass, const jlong address, const jshort val)
{
    reinterpret_cast<nettools::socket_address_ptr>(address)->m_port = val;
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceQuery(JNIEnv*, jclass)
{
    const nettools::network_interface iface = nettools::interface_query();
    nettools::network_interface_ptr result = new nettools::network_interface[1];
    result[0] = iface;
    return reinterpret_cast<jlong>(result);
}

JNIEXPORT jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetMacAddress(JNIEnv* env, jclass, const jlong iface)
{
    nettools::hardware_address addr = reinterpret_cast<nettools::network_interface_ptr>(iface)->m_mac_address;

    const jbyteArray result = env->NewByteArray(6);
    env->SetByteArrayRegion(result, 0, 6, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetUnicastAddress(JNIEnv* env, jclass, const jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface_ptr>(iface)->m_unicast_addr;

    const jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetSubnetAddress(JNIEnv* env, jclass, const jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface_ptr>(iface)->m_subnet_addr;

    const jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetNetworkAddress(JNIEnv* env, jclass, const jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface_ptr>(iface)->m_network_addr;

    const jbyteArray result = env->NewByteArray(4);
    env->SetByteArrayRegion(result, 0, 4, reinterpret_cast<jbyte*>(&addr));
    return result;
}

jbyteArray JNICALL Java_ch_thecodinglab_nettools_WinNative_nInterfaceGetBroadcastAddress(JNIEnv* env, jclass, const jlong iface)
{
    nettools::inet_address addr = reinterpret_cast<nettools::network_interface_ptr>(iface)->m_broadcast_addr;

    const jbyteArray result = env->NewByteArray(4);
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

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketCreate(JNIEnv*, jclass, const jint family, const jint type, const jint protocol)
{
    return nettools::socket_create(family, type, protocol);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketBind(JNIEnv*, jclass, const jlong socket, const jlong address)
{
    const nettools::socket_address_ptr addr = reinterpret_cast<nettools::socket_address_ptr>(address);
    nettools::socket_bind(socket, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConnect(JNIEnv*, jclass, const jlong socket, const jlong address)
{
    const nettools::socket_address_ptr addr = reinterpret_cast<nettools::socket_address_ptr>(address);
    nettools::socket_connect(socket, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketListen(JNIEnv*, jclass, const jlong socket)
{
    nettools::socket_listen(socket);
}

jlong JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketAccept(JNIEnv*, jclass, const jlong socket, const jlong address)
{
    const nettools::socket_address_ptr addr = reinterpret_cast<nettools::socket_address_ptr>(address);
    return nettools::socket_accept(socket, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketSend(JNIEnv*, jclass, const jlong socket, const jlong buffer)
{
    const nettools::byte_buffer_ptr buf = reinterpret_cast<nettools::byte_buffer_ptr>(buffer);
    nettools::socket_send(socket, buf);
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketRead(JNIEnv*, jclass, const jlong socket, const jlong buffer)
{
    const nettools::byte_buffer_ptr buf = reinterpret_cast<nettools::byte_buffer_ptr>(buffer);
    return nettools::socket_read(socket, buf);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketSendTo(JNIEnv*, jclass, const jlong socket, const jlong buffer, const jlong address)
{
    const nettools::byte_buffer_ptr buf = reinterpret_cast<nettools::byte_buffer_ptr>(buffer);
    const nettools::socket_address_ptr addr = reinterpret_cast<nettools::socket_address_ptr>(address);
    nettools::socket_sendto(socket, buf, addr);
}

jint JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketReadFrom(JNIEnv*, jclass, const jlong socket, const jlong buffer, const jlong address)
{
    const nettools::byte_buffer_ptr buf = reinterpret_cast<nettools::byte_buffer_ptr>(buffer);
    const nettools::socket_address_ptr addr = reinterpret_cast<nettools::socket_address_ptr>(address);
    return nettools::socket_readfrom(socket, buf, addr);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketClose(JNIEnv*, jclass, const jlong socket)
{
    nettools::socket_close(socket);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureBlocking(JNIEnv*, jclass, const jlong socket, const jboolean blocking)
{
    nettools::socket_configure_blocking(socket, blocking);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureBroadcast(JNIEnv*, jclass, const jlong socket, const jboolean broadcast)
{
    nettools::socket_configure_broadcast(socket, broadcast);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureSendTimeout(JNIEnv*, jclass, const jlong socket, const jlong timeout)
{
    nettools::socket_configure_send_timeout(socket, timeout);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketConfigureReadTimeout(JNIEnv*, jclass, const jlong socket, const jlong timeout)
{
    nettools::socket_configure_read_timeout(socket, timeout);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketUDPBroadcastMethodAllAtOnce(JNIEnv*, jclass, const jlong socket, const jlong buffer, const jlong iface, const jshort port)
{
    nettools::socket_udp_broadcast_method_allatonce(socket, reinterpret_cast<nettools::byte_buffer_ptr>(buffer), reinterpret_cast<nettools::network_interface_ptr>(iface), port);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nSocketUDPBroadcastMethodOneATime(JNIEnv*, jclass, const jlong socket, const jlong buffer, const jlong iface, const jshort port)
{
    nettools::socket_udp_broadcast_method_oneatime(socket, reinterpret_cast<nettools::byte_buffer_ptr>(buffer), reinterpret_cast<nettools::network_interface_ptr>(iface), port);
}


static JavaVM* jvm = NULL;
static jclass callbackClass = NULL;
static jobject callbackInstance = NULL;

bool discovery_request(const nettools::socket_address_ptr client)
{
    if (jvm != NULL && callbackClass != NULL && callbackInstance != NULL)
    {
        JNIEnv* env;
        jint result = jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), NULL);
        if (result == JNI_OK)
        {
            jmethodID method = env->GetMethodID(callbackClass, "nCallbackDiscoveryRequest", "(J)Z");
            bool accept = env->CallBooleanMethod(callbackInstance, method, reinterpret_cast<jlong>(client));
            jvm->DetachCurrentThread();
            return accept;
        }
    }
    return true;
}

void discovery_found(const nettools::socket_address_ptr client)
{
    if (jvm != NULL && callbackClass != NULL && callbackInstance != NULL)
    {
        JNIEnv* env;
        jint result = jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), NULL);
        if (result == JNI_OK)
        {
            jmethodID method = env->GetMethodID(callbackClass, "nCallbackDiscoveryFound", "(J)V");
            env->CallVoidMethod(callbackInstance, method, reinterpret_cast<jlong>(client));
            jvm->DetachCurrentThread();
        }
    }
}

void discovery_ping_result(const nettools::socket_address_ptr client, const u32 time, const bool reachable)
{
    if (jvm != NULL && callbackClass != NULL && callbackInstance != NULL)
    {
        JNIEnv* env;
        const jint result = jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), NULL);
        if (result == JNI_OK)
        {
            const jmethodID method = env->GetMethodID(callbackClass, "nCallbackDiscoveryPingResult", "(JIZ)V");
            env->CallVoidMethod(callbackInstance, method, reinterpret_cast<jlong>(client), static_cast<jint>(time), static_cast<jboolean>(reachable));
            jvm->DetachCurrentThread();
        }
    }
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryInit(JNIEnv*, jclass, const jshort port)
{
    nettools::discovery_init(port);
    nettools::discovery_set_handlers(discovery_request, discovery_found, discovery_ping_result);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoverySetHandlers(JNIEnv* env, jclass, const jobject callback)
{
    const jint result = env->GetJavaVM(&jvm);
    if (result != JNI_OK) return;

    if (callbackClass != NULL) env->DeleteGlobalRef(callbackClass);
    if (callbackInstance != NULL) env->DeleteGlobalRef(callbackInstance);

    callbackInstance = env->NewGlobalRef(callback);

    const jclass objClass = env->GetObjectClass(callback);
    if (objClass)
    {
        callbackClass = static_cast<jclass>(env->NewGlobalRef(objClass));
        env->DeleteLocalRef(objClass);
    }
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoverySearch(JNIEnv*, jclass, const jshort port, const jboolean allatonce)
{
    nettools::discovery_search(port, allatonce);
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryUpdate(JNIEnv*, jclass)
{
    nettools::discovery_update();
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryPing(JNIEnv*, jclass, const jlong addr)
{
    nettools::discovery_ping(reinterpret_cast<nettools::socket_address*>(addr));
}

void JNICALL Java_ch_thecodinglab_nettools_WinNative_nDiscoveryClose(JNIEnv* env, jclass)
{
    nettools::discovery_close();
    if (callbackClass != NULL) env->DeleteGlobalRef(callbackClass);
    if (callbackInstance != NULL) env->DeleteGlobalRef(callbackInstance);
    callbackClass = NULL;
    callbackInstance = NULL;
    jvm = NULL;
}
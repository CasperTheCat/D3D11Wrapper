#pragma once

//#include <WinSock2.h> // Baremetal Sockets
//#include <ws2tcpip.h> // TCPIP Header
#if defined(CORE_D3D11)

#elif defined(CORE_D3D9)

#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <mutex>
#include <condition_variable>
#include "Ringbuffer.h"

class CNetwork
{
private:
    CCircularBuffer<uint64_t> m_ring;
    std::mutex m_mtxRing;
    std::condition_variable m_cvRing;


    std::thread m_trWorker;
    bool m_bCanSubmit;

    WSADATA m_wsaData;
    SOCKET m_skClientSocket;
        

private:
    void WorkerThread_RT();

    void Connect(std::wstring strHostname, uint16_t uPort);
public:
    CNetwork(std::wstring strHostname, uint16_t uPort);
    ~CNetwork();

    void SendU64(uint64_t uData);
};





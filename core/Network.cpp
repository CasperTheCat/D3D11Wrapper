#include "Network.h"
//#include <minwinbase.h>
#include <iostream>
void CNetwork::WorkerThread_RT()
{
	while (true)
	{
		//std::unique_lock<std::mutex> lock(m_mtxRing);
		//m_cvRing.wait(lock, [this]() { return !m_ring.empty() || !m_bCanSubmit; });

		if (!m_bCanSubmit) return;

		auto sendVector = m_ring.dequeue(4096);

		//auto sendable = m_ring[0];
		//m_ring.remove(1);

		//std::cout << "RSZ:" << m_ring.size() << std::endl;

		//lock.unlock();
		//m_cvRing.notify_one();

		//auto r = send(m_skClientSocket, reinterpret_cast<char*>(&sendable), sizeof(uint64_t), NULL);
		//if (r == SOCKET_ERROR)
		//{
		//	std::cout << WSAGetLastError() << std::endl;
		//}
		//std::cout << "Sent " << r << "bytes" << std::endl;

		if (sendVector.size() > 0)
		{
			auto r = send(m_skClientSocket, reinterpret_cast<char*>(sendVector.data()), sendVector.size() * sizeof(uint64_t), NULL);
			//std::cout << "Sent " << r << " bytes" << std::endl;
		}
		else
		{
			//std::cout << "Called with empty vector" << std::endl;
		}
		// Send

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void CNetwork::Connect(std::wstring strHostname, uint16_t uPort)
{
	// Windows Socket returns 0 on success...
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != NO_ERROR)
	{
		throw std::exception();
	}

	m_skClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_skClientSocket == INVALID_SOCKET)
	{
		throw std::exception();
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	//clientService.sin_addr.s_addr = inet_addr(strHostname.c_str());
	InetPton(AF_INET, strHostname.c_str(), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(uPort);



	// Connect
	if (connect(m_skClientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		closesocket(m_skClientSocket);
		throw std::exception();
	}
}

CNetwork::CNetwork(std::wstring strHostname, uint16_t uPort)
	:
	m_bCanSubmit(true),
	m_ring(1024*4) // One page is enough?
{
	Connect(strHostname, uPort);

	m_trWorker = std::thread(&CNetwork::WorkerThread_RT, this);
	std::cout << "Built" << std::endl;
}

CNetwork::~CNetwork()
{
	// Stop all submissions
	m_bCanSubmit = false;
	// Let all running queues exit.

	// Closedown the thread!
	m_trWorker.join();

	// Close Network
	//const auto stat = shutdown(m_skClientSocket, SD_BOTH);
	//if (stat == NO_ERROR)
	closesocket(m_skClientSocket);
	WSACleanup();
}

void CNetwork::SendU64(uint64_t uData)
{
	if (m_bCanSubmit)
	{
		std::unique_lock<std::mutex> lock(m_mtxRing);
		m_cvRing.wait(lock, [this]() { return !m_ring.full(); });

		m_ring.push_back(uData);

		lock.unlock();
		m_cvRing.notify_one();
	}
}

#include "Frame.h"

CCall* CFrame::GetCurrentCall()
{
	return &(m_calls[m_calls.size() - 1]);
}

CFrame::CFrame()
{
	m_calls.emplace_back(static_cast<uint32_t>(m_calls.size()));
}

CFrame::~CFrame()
{
}

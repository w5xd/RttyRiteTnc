// WlTncA.cpp : Implementation of CWlTncA

#include "pch.h"
#include "WlTncA.h"



CWlTncA::CWlTncA() : m_announcedVersion(false)
{
	m_XmitState = RECEIVE;
	m_NextReceivedLetter = 'A'; // TEST
}

HRESULT CWlTncA::SetFskReverse(short Xmit, short Rcv) //non zero means set reverse
{
	return S_OK;
}

HRESULT CWlTncA::GetFskReverse(short* pXmit, short* pRcv)	//read back what was set
{
	*pXmit = 0;
	*pRcv = 0;
	return S_OK;
}

HRESULT CWlTncA::ConfigureTnc()	// put up a dialog box for the TNC, if necessary
{
	return S_OK;
}

HRESULT CWlTncA::CanConfigureTnc() // S_OK means yes, S_FALSE means no
{
	return S_FALSE;
}

HRESULT CWlTncA::SetupCommPort(short CommPortNumber) // 1 is COM1, 2 is COM2, etc.
{
	return S_OK;
}

HRESULT CWlTncA::SetSpeedIndex(enum WlTncSpeeds Speed)
{
	switch (Speed)
	{
	case WLTNC_SPEED_45:
	case WLTNC_SPEED_50:
	case WLTNC_SPEED_57:
	case WLTNC_SPEED_72:
	case WLTNC_SPEED_ASCII:
	case WLTNC_SPEED_BPSK:
	case WLTNC_SPEED_QPSKU:
	case WLTNC_SPEED_QPSKL:
	case WLTNC_SPEED_CW:
		break;

	}
	return S_OK;
}

HRESULT CWlTncA::PeekProc()
{
	return S_OK;
}

void CWlTncA::OnReceiveTimer()
{
	// TEST
	if (!m_announcedVersion)
	{
		static const char VERSION_STR[] =
		"\r\nWlTnc VERSION " TNC_VERSION_STRING "\r\n";
		for (auto p = &VERSION_STR[0]; *p; p+=1)
			m_pCallback->AddChar(*p, 1, 1);
		m_announcedVersion = true;
		return;
	}
	m_pCallback->AddChar(m_NextReceivedLetter++, 1, 1);
	if (m_NextReceivedLetter >= 'Z')
		m_NextReceivedLetter = 'A';
}

void CWlTncA::OnTransmitTimer()
{
	unsigned char	NextChars[CHARS_PER_TIMER];
	long r;
	if (SUCCEEDED(m_pCallback->NextNXmitChars(sizeof(NextChars), &r, NextChars)))
	{
		if (r > 0)
		{
			// For this test implementation, even though we read 3 characters,
			// we only process one
			if (NextChars[0] != WLTNC_RXEND_CHAR)
			{
				m_pCallback->AddChar(NextChars[0], 2, 1);
			}
			else
			{
				ReceiveNow();
			}

			// We have to tell RttyRite how many characters we processed.
			m_pCallback->RemoveNXmitChars(1);
		}
	}
}

HRESULT CWlTncA::TimerProc()
{
	switch (m_XmitState)
	{
	case RECEIVE:
		OnReceiveTimer();
		break;

	case TRANSMIT:
		OnTransmitTimer();
		break;
	}
	return S_OK;
}

HRESULT CWlTncA::XmitNow()
{
	m_XmitState = TRANSMIT;
	m_pCallback->ReplaceTimer(100);	//TEST 100 msec timer while transmitting	
	return S_OK;
}

HRESULT CWlTncA::ReceiveNow()
{
	m_XmitState = RECEIVE;
	m_pCallback->ReplaceTimer(40);	//TEST 40 msec timer while receiving
	return S_OK;
}

HRESULT CWlTncA::LettersNow()	// force baudot conversion to LTRS now.
{
	return S_OK;
}

HRESULT CWlTncA::get_AfcState(short* pVal)
{
	*pVal = 0;
	return S_OK;
}

HRESULT CWlTncA::put_AfcState(short newVal)
{
	return S_OK;
}

HRESULT CWlTncA::get_ModeMask(enum WlTncModeMask* pVal) //report supported modes
{
	*pVal = WLTNC_CAN_DO_RTTY; // TEST
	return S_OK;
}

// This will be the first call after creation.
HRESULT CWlTncA::SetCallBack(IWlTncCallBack* pCallBack)
{
	m_pCallback = pCallBack;
	return S_OK;
}


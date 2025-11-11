// WlTncA.cpp : Implementation of CWlTncA

#include "pch.h"
#include "WlTncA.h"

namespace {

	const char ESCAPE = '\033';
	const char STX = '\002';
	const char EOT = '\004';
}

CWlTncA::CWlTncA() 
	: m_announcedVersion(false)
	, m_firstCharXmitted(false)
	, m_CommChannel(INVALID_HANDLE_VALUE)
	, m_XmitState(RECEIVE)
	, m_readState(RECEIVE)
	, m_wOverlapped({})
	, m_rOverlapped({})
	, m_prevCommErrorBits(-1)
	, m_prevcbInQue(-1)
	, m_lastReadError(-1)
	, m_CommPortNumber(-1)
	, m_priorCharacterXmit(-1)
{
}

HRESULT CWlTncA::FinalConstruct()
{
	if (::GetPrivateProfileInt("RttyRite", "W6IWI_LOGGING", 0, "WRITELOG.INI") != 0)
	{
		wchar_t *pFolderName;
		auto ok = SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, 0, &pFolderName);
		if (SUCCEEDED(ok))
		{
			auto w = ::WideCharToMultiByte(CP_ACP, 0, pFolderName, -1, 0, 0, 0,0);
			std::vector<char> fn(w);
			::WideCharToMultiByte(CP_ACP, 0, pFolderName, -1, &fn[0], fn.size(), 0, 0);
			std::ostringstream oss;
			oss << &fn[0] << "\\WlTncW6IWI.log";
			m_logFile.open(oss.str().c_str());
		}
		if (pFolderName)
			CoTaskMemFree(pFolderName);
		if (m_logFile.is_open())
		{
			std::string tm;
			TimeStamp(tm);
			m_logFile << tm << " WlTncW6IWI log file begin " TNC_VERSION_STRING << std::endl;
		}
	}
	return S_OK;
}

void CWlTncA::FinalRelease()
{	
	m_pCallback.Release();
	CloseComm();
	if (m_logFile.is_open())
	{
		std::string tm;
		TimeStamp(tm);
		m_logFile << tm << " WlTncW6IWI log file end" << std::endl;
		m_logFile.close();
	}
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

void CWlTncA::CloseComm()
{
	if (m_CommChannel != INVALID_HANDLE_VALUE)
		::CloseHandle(m_CommChannel);
	m_CommChannel = INVALID_HANDLE_VALUE;
}

HRESULT CWlTncA::SetupCommPort(short CommPortNumber) // 1 is COM1, 2 is COM2, etc.
{
	CloseComm();
	if (CommPortNumber < 1)
		return E_INVALIDARG;
	std::ostringstream oss;
	oss << "\\\\.\\COM" << static_cast<int>(CommPortNumber);

	m_CommChannel = CreateFileA(oss.str().c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	if (INVALID_HANDLE_VALUE != m_CommChannel)
	{
		enum { CHAR_BUFFER_LENGTH = 1000 };
		#ifdef _DEBUG
		DCB dcbPrior;
		dcbPrior.DCBlength = sizeof(DCB);
		GetCommState(m_CommChannel, &dcbPrior);
		#endif
		DCB dcb = {};
		dcb.DCBlength = sizeof(dcb);
		dcb.BaudRate = ::GetPrivateProfileIntA("RttyRite", "W6IWI_TNC_BAUD", 921600, "WRITELOG.INI");
		dcb.ByteSize = 8;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.fAbortOnError = 0;
		dcb.fBinary = 1;
		dcb.fOutxCtsFlow = 0;
		dcb.fOutxDsrFlow = 0;
		dcb.XoffChar = '\x13';
		dcb.XonChar = '\x11';
		dcb.fOutX = 0;
		dcb.fInX = 0;
		dcb.XoffLim = (CHAR_BUFFER_LENGTH * 9) / 10;
		dcb.XonLim = 0;
		dcb.fNull = 0;
		/* After a LOT of test runs where the modem was sending
		** characters but ReadFile would not return them, these 3
		** were changed and finally, ReadFile would work. With them
		** set to zero, (almost) no characters are received.
		** Note that these ENABLE parity and modem control
		** and are distinct from setting them!*/
		dcb.fParity = TRUE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		auto ret = SetCommState(m_CommChannel, &dcb);
		if (!ret)
		{
			logGetLastError("SetCommState"); 
			return E_FAIL;
		}
		SetupComm(m_CommChannel, CHAR_BUFFER_LENGTH, CHAR_BUFFER_LENGTH);
		COMMTIMEOUTS CommTimeouts = { MAXDWORD, 0, 0, 0, 0 };
		SetCommTimeouts(m_CommChannel, &CommTimeouts);
		EscapeCommFunction(m_CommChannel, SETDTR);
		EscapeCommFunction(m_CommChannel, CLRRTS);
		m_CommPortNumber = CommPortNumber;
		m_prevCommErrorBits = -1;
		m_prevcbInQue = -1;
		m_lastReadError = -1;
		return S_OK;
	}

	m_CommPortNumber = -1;
	return E_FAIL;
}

HRESULT CWlTncA::SetSpeedIndex(enum WlTncSpeeds Speed)
{
	std::ostringstream oss;
	oss << "UsbEcho\t0\r";		// ************* turning UsbEcho OFF.
	oss << "BaudRate\t";
	switch (Speed)
	{
	case WLTNC_SPEED_45:
		oss << "45.45";
		break;
	case WLTNC_SPEED_50:
		oss << "50";
		break;
	case WLTNC_SPEED_57:
		oss << "56.9";
		break;
	case WLTNC_SPEED_72:
		oss << "74.2";
		break;
	default:
		return E_INVALIDARG;
	}
	oss << '\r';
	oss << "KOS\t1\r";		// ************* turning KOS ON.
	oss << "UsbEcho\t1\r";		// ************* turning UsbEcho now ON.
	CommandsToModem(oss.str());
	return S_OK;
}

HRESULT CWlTncA::PeekProc()
{
	checkCommDisconnect();
	return S_OK;
}

void CWlTncA::TimeStamp(std::string &s)
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	s = buf;
}

void CWlTncA::logGetLastError(const std::string& s)
{
    if (m_logFile.is_open())
    {
        DWORD err = GetLastError();
        LPVOID lpMsgBuf = "";
        DWORD res = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            err,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR)&lpMsgBuf,
            0,
            NULL);
        std::string output;
        if (lpMsgBuf && *static_cast<const char*>(lpMsgBuf))
            output = static_cast<const char*>(lpMsgBuf);
		while (!output.empty())
		{
			auto cr = output.size() - 1;
			if (!isspace(output[cr]))
				break;
			output.resize(cr);
		}
		std::string buf;
		TimeStamp(buf);
        m_logFile <<  buf << ' ' << s <<  " GetLastError=0x" << std::hex << err << " " << output << std::endl;
        if (res)
            LocalFree(lpMsgBuf);
    }
}

std::vector<char> CWlTncA::ReadModem()
{
	static const unsigned READ_MODEM_CHARS(100);
	std::vector<char> ret(READ_MODEM_CHARS);
	if (m_CommChannel == INVALID_HANDLE_VALUE)
		ret.clear();
	else
	{
		memset(&m_rOverlapped, 0, sizeof(m_rOverlapped));
		auto rf = ReadFile(m_CommChannel, &ret[0], ret.size(),
			0,	&m_rOverlapped);
		auto gle = ::GetLastError();
		if (!rf || gle != m_lastReadError)
			logGetLastError("ReadFile");
		m_lastReadError = gle;
		DWORD Max(0);
		auto gor = ::GetOverlappedResult(m_CommChannel, &m_rOverlapped, &Max, FALSE);
		if (!gor)
			logGetLastError("GetOverlappedResult");
		if (Max == 0)
		{
			DWORD    CommErrorBits(0);
			COMSTAT cs({});
			ClearCommError(m_CommChannel, &CommErrorBits, &cs);
			if ((m_prevCommErrorBits != CommErrorBits) || (m_prevcbInQue != cs.cbInQue))
			{
				if (m_logFile.is_open())
					m_logFile << "cbInQue = " << cs.cbInQue << " CommErrorBits = 0x" << std::hex << CommErrorBits << std::endl;
				m_prevCommErrorBits = CommErrorBits;
				m_prevcbInQue = cs.cbInQue;
			}
		}
		ret.resize(Max);
	}
	return ret;
}

unsigned CWlTncA::WriteModem(const char*p, unsigned count)
{
	unsigned ret(0);
	if (m_CommChannel != INVALID_HANDLE_VALUE)
	{
		memset(&m_wOverlapped, 0, sizeof(m_wOverlapped));
		DWORD WriteCount;
		auto wf = ::WriteFile(m_CommChannel, p, count, &WriteCount, &m_wOverlapped);
		if (!wf)
			logGetLastError("WriteFile");
		ret = WriteCount;
	}
	return ret;
}

void CWlTncA::CommandsToModem(const std::string&s)
{
	static const char MODEM[] = "modem\r";
	WriteModem(&ESCAPE, 1);
	if (!s.empty())
		WriteModem(s.c_str(), s.size());
	WriteModem(MODEM, sizeof(MODEM)-1);
}

void CWlTncA::OnReceiveTimer()
{
}

void CWlTncA::OnTransmitTimer()
{
	static const long CHARS_PER_TIMER = 5;
	unsigned char	NextChars[CHARS_PER_TIMER+1];
	long r;
	if (SUCCEEDED(m_pCallback->NextNXmitChars(CHARS_PER_TIMER, &r, NextChars)))
	{
		unsigned count = 0;
		for (unsigned i = 0; i < static_cast<unsigned>(r); i++)
		{
			count += 1;
			const char c = static_cast<char>(NextChars[i]);
			if (c != static_cast<char>(WLTNC_RXEND_CHAR))
			{
				if (!m_firstCharXmitted)
				{
					static const char THROW_AWAY = STX;
					WriteModem(&THROW_AWAY, 1);
					m_firstCharXmitted = true;
				}
				bool skip = c == '\n' && m_priorCharacterXmit == '\r';
				m_priorCharacterXmit = c;
				if (skip)
					continue;
				WriteModem(&c, 1);
				if (c == '\r')
				{
					static const char NL = '\n';
					WriteModem(&NL, 1);
				}
			}
			else
			{
				m_XmitState = RECEIVE;
				break;
			}
		}
		// We have to tell RttyRite how many characters we processed.
		if (count) m_pCallback->RemoveNXmitChars(count);
	}
}

HRESULT CWlTncA::TimerProc()
{
	if (!m_announcedVersion)
	{
		static const char VERSION_STR[] =
			"\r\nW6IWI TNC Version " TNC_VERSION_STRING "\r\n";
		for (auto p = &VERSION_STR[0]; *p; p += 1)
			m_pCallback->AddChar(*p, 1, 1);
		m_announcedVersion = true;
	}

	for (;;)
	{
		auto fromModem = ReadModem();
		if (fromModem.empty())
			break;
		for (auto c : fromModem)
		{
			static const short RECEIVED = 1;
			static const short TRANSMITTED = 2;
			static const short SHOULD_BE_ONE = 1;
			switch (c)
			{
				case STX:
					m_readState = TRANSMIT;
					break;

				case EOT:
					m_readState = RECEIVE;
					break;

				default:
					break;
			}
			m_pCallback->AddChar(c, m_readState == RECEIVE ? RECEIVED : TRANSMITTED, SHOULD_BE_ONE);
		}
	}

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
	if (m_XmitState != TRANSMIT)
		m_firstCharXmitted = false;
	m_XmitState = TRANSMIT;
	m_pCallback->ReplaceTimer(100);	//100 msec timer while transmitting	
	return S_OK;
}

HRESULT CWlTncA::ReceiveNow()
{
	if (m_XmitState != RECEIVE)
		CommandsToModem("");
	m_XmitState = RECEIVE;
	m_pCallback->ReplaceTimer(40);	//40 msec timer while receiving
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
	*pVal = WLTNC_CAN_DO_RTTY; 
	return S_OK;
}

// This will be the first call after creation.
HRESULT CWlTncA::SetCallBack(IWlTncCallBack* pCallBack)
{
	m_pCallback = pCallBack;
	return S_OK;
}

void CWlTncA::checkCommDisconnect()
{
	auto now = std::chrono::steady_clock::now();
	if (now - m_disconnectChecked > std::chrono::seconds(1))
	{
		m_disconnectChecked = now;
		if (m_CommChannel != INVALID_HANDLE_VALUE)
		{
			// https://stackoverflow.com/questions/20713207/identify-disconnect-event-with-a-windows-usb-virtual-com-port
			DCB dcb({});
			dcb.DCBlength = sizeof(DCB);
			if (!::GetCommState(m_CommChannel, &dcb) ||
				!::SetCommState(m_CommChannel, &dcb))
			{
				if (m_logFile.is_open())
				{
					std::string buf;
					TimeStamp(buf);
					m_logFile << buf << ' ' << "COM port disconnected. closing it" << std::endl;
				}
				::CloseHandle(m_CommChannel);
				m_CommChannel = INVALID_HANDLE_VALUE;
				if (m_pCallback)
					m_pCallback->AddString(reinterpret_cast<unsigned char *>(const_cast<char*>("COM port disconnected\r\n")), 2, 1);
			}
			#ifdef _DEBUG
			auto x = 0;
			#endif
		}
		else if (m_CommPortNumber > 0)
		{
			if (SUCCEEDED(SetupCommPort(m_CommPortNumber)))
			{
				std::string buf;
				TimeStamp(buf);
				m_logFile << buf << ' ' << "COM port restored" << std::endl;
			}
		}

	}
}
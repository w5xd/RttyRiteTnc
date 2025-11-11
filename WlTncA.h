// WlTncA.h : Declaration of the CWlTncA

#pragma once
#include "resource.h"       // main symbols
#include "WlTnc_i.h"


using namespace ATL;


// CWlTncA

class ATL_NO_VTABLE CWlTncA :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CWlTncA, &CLSID_WlTncA>,
    public IWlTnc
{
public:
    CWlTncA();

    DECLARE_REGISTRY_RESOURCEID(IDR_WLTNCA)


    BEGIN_COM_MAP(CWlTncA)
        COM_INTERFACE_ENTRY(IWlTnc)
    END_COM_MAP()


    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct();

    void FinalRelease();

public:
    // IWlTnc
public:
    STDMETHODIMP SetFskReverse(short Xmit, short Rcv); //non zero means set reverse
    STDMETHODIMP GetFskReverse(short* pXmit, short* pRcv);	//read back what was set
    STDMETHODIMP ConfigureTnc();	// put up a dialog box for the TNC, if necessary
    STDMETHODIMP CanConfigureTnc(); // S_OK means yes, S_FALSE means no
    STDMETHODIMP SetupCommPort(short CommPortNumber); // 1 is COM1, 2 is COM2, etc.
    STDMETHODIMP SetSpeedIndex(enum WlTncSpeeds Speed);
    STDMETHODIMP PeekProc();
    STDMETHODIMP TimerProc();
    STDMETHODIMP XmitNow();
    STDMETHODIMP ReceiveNow();
    STDMETHODIMP LettersNow();	// force baudot conversion to LTRS now.
    STDMETHODIMP get_AfcState(short* pVal);
    STDMETHODIMP put_AfcState(short newVal);
    STDMETHODIMP get_ModeMask(enum WlTncModeMask* pVal); //report supported modes

    // This will be the first call after creation.
    STDMETHODIMP SetCallBack(IWlTncCallBack* pCallBack);

protected:
    void CloseComm();
    void OnReceiveTimer(void);
    void OnTransmitTimer(void);
    void CommandsToModem(const std::string &);
    unsigned WriteModem(const char *, unsigned);
    std::vector<char> ReadModem();
    void logGetLastError(const std::string &);
    void TimeStamp(std::string &);
    void checkCommDisconnect();

    // TNC may need intermediate states to transition between rcv/xmit.
    enum XmitState_t
    {
        RECEIVE,
        TRANSMIT,
    }    m_XmitState;

    enum XmitState_t m_readState;

    HANDLE m_CommChannel;
    bool   m_announcedVersion;
    bool   m_firstCharXmitted;
    CComPtr<IWlTncCallBack>	m_pCallback;
    OVERLAPPED m_wOverlapped;
    OVERLAPPED m_rOverlapped;

    std::ofstream m_logFile;
    DWORD m_prevCommErrorBits;
    DWORD m_prevcbInQue;
    DWORD m_lastReadError;
    char m_priorCharacterXmit;
    std::chrono::steady_clock::time_point m_disconnectChecked;
    short m_CommPortNumber;
};

OBJECT_ENTRY_AUTO(__uuidof(WlTncA), CWlTncA)

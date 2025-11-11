// dllmain.h : Declaration of module class.

class CWlTncModule : public ATL::CAtlDllModuleT< CWlTncModule >
{
public :
	DECLARE_LIBID(LIBID_WlTncLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_WLTNC, "{94A1B6B7-B462-4F0E-A190-C3B92A966D90}")
};

extern class CWlTncModule _AtlModule;

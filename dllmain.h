// dllmain.h : Declaration of module class.

class CWlTncModule : public ATL::CAtlDllModuleT< CWlTncModule >
{
public :
	DECLARE_LIBID(LIBID_WlTncLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_WLTNC, "{9a1ee755-f1eb-44e4-96e2-1a891d583999}")
};

extern class CWlTncModule _AtlModule;

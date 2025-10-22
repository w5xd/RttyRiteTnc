21 October, 2025
Wayne Wright, W5XD

This is a sample TNC DLL that plugs into RttyRite.
WriteLog 10.27E or later is required.

The design is this:
1. You implement a COM object with the IWlTnc interface. 
Choose new GUIDs for:
    {1a891ad9-504d-45df-91f7-439bbe294cdb}  is the coclass GUID. It appears in: WlTnc.idl, WlTncA.rgs and Product.wxs
    {9a1ee755-f1eb-44e4-96e2-1a891d583999}  is the typelib GUID. It appears in dllmain.h, WlTnc.idl, and WlTncA.rgs
    Also in Product.wxs: Change the GUIDs as indicated in its comments. Do NOT change GUIDs not commented
The name of the DLL file built by the WlTnc project must be unique in WriteLog's \Program Files (x86)\WriteLog\Programs directory

2. RttyRite will find your COM object by looking for the following
two registry entries:

    Windows Registry Editor Version 5.00

    [HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\W5XD\WriteLog\RttyRite]
    "CustomTnc1MenuEntry"="Custom WlTncABC"
    "CustomTnc1ProgId"="WriteLog.WlTncABC"

The digit "1" can be any of "1", "2", or "3"
The first entry shows up in RttyRite's "Tu Type" menu.
The second entry must be the COM ProgID for your COM object

3. When RttyRite instances your COM object, it calls you first on your
SetCallBack method, and that's how you tell it what characters you
have received, and how you find out what characters to transmit.

You can build this project as-is, to test that you have your
environment correct. Edit WRITELOG.INI per step (2) above and
install this project and select this tnc. You'll get a steady stream
of letters on receive, and it will echo what you transmit.


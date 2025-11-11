msbuild WlTnc.vcxproj /p:Configuration="Release" /p:Platform="Win32"
msbuild WlTncSetup/WlTncW6IWISetup.wixproj /p:Configuration="Release" /p:Platform="X86"
move WlTncSetup\bin\X86\Release\WlTncW6IWISetup*.msi .\Downloads\
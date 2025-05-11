
#include "NativeModule.h"
#include "TextWriter.h"
#include <e32cmn.h>

_LIT(KLddName,"EKernCtl");
_LIT(KLddFileName,"EKernCtl.ldd");

class REKernCtl : public RBusLogicalChannel
{
public:
        inline TInt Open()
		{
        	//return DoCreate(KLddName,TVersion(1,0,1),KNullUnit,NULL,NULL, EOwnerThread);
        	return DoCreate(KLddName,TVersion(1,0,1),KNullUnit,NULL,NULL);
        }
        inline TInt SendControl(TInt aReq, TAny* aArg0, TAny* aArg1)
        {
        	return DoControl(aReq, aArg0 , aArg1);
        }
};


_LIT(KAboutString, "KRestartModule (Restart SymbianOS Kernel) / (C) 2025 - JigokuMaster");

class KRestartModule : public NativeModule {
private:
  // the functions this module supports,
  // the enumeration values correspond to function indices
  enum Functions {
    DoRestartFunction, AboutFunction
  };

  ~KRestartModule()
  {
  }

private:
	void DoKernRestartL()
	{
		TInt err = User::LoadLogicalDevice(KLddFileName);
		if ((err != KErrNone) && ( err != KErrAlreadyExists))
		{
			runtime->GetWriter()->WriteL(_L("Unable to load EKernCtl.ldd!"));
			runtime->SignalError(err);
			return;
		}
	
		REKernCtl aDriver;
		err = aDriver.Open();
		if (err != KErrNone)
		{
			runtime->GetWriter()->WriteL(_L("EKernCtl.Open() failed!"));
			runtime->SignalError(err);
			return;
		}
	
		err = aDriver.SendControl(1, NULL,NULL);
		// will not reach
		if (err != KErrNone)
		{
			runtime->GetWriter()->WriteL(_L("EKernCtl.SendControl() failed!"));
			runtime->SignalError(err);			
			return;

		}
		
		err = User::FreeLogicalDevice(KLddName);
		if (err != KErrNone)
		{
			runtime->GetWriter()->WriteL(_L("Unable to unload EKernCtl!"));
			runtime->SignalError(err);			
		}
}

protected: // from NativeModule
  TInt ExpectedRuntimeVersion() { return Runtime::VERSION; }

  const char *ModuleVersion() { return "$Revision: 1.0 $"; }

  void ConstructL() {
    // the functions this module supports
    runtime->AddNativeFunctionL(_L("do_restart"), 0, 0, DoRestartFunction);
    runtime->AddNativeFunctionL(_L("about"), 0, 0, AboutFunction);
  }
  
  Runtime::Value ExecuteL(TInt index, Runtime::Value *params,
                          TInt paramCount, TRequestStatus &status)
 {

    // a variable which will contain the function result
    Runtime::Value result;
    result.SetNull(); // default for functions returning null
    switch (index)
	{
		case DoRestartFunction:
		{
			DoKernRestartL();
			break;
		}
		case AboutFunction:
		{
			result = runtime->NewStringL(KAboutString);
			break;
		}
    }
    return result;
  }

};

// the first exported function creates an instance of this module
EXPORT_C NativeModule* NewKRestartModuleL() { return new(ELeave) KRestartModule; }

// the second exported function is required by DLL conventions (2nd ed only)
#ifndef EKA2
GLDEF_C TInt E32Dll(TDllReason) { return KErrNone; }
#endif

#include<e32std.h>
#include<e32base.h>
#include <e32cmn.h>
#include<unistd.h>
#ifdef ENABLE_LOGGING
#include<stdio.h>
#include<stdarg.h>
#define LOG_FP "C:\\krestart.log"

void WriteToLog(char* fmt, ...)
{
    va_list marker;	
    FILE* f;
	if(fmt == NULL)
	{
		if( (f = fopen(LOG_FP,"w")) != NULL )
		{	
			fclose(f);
		}
		return;
	}	
	
	else{
		f = fopen(LOG_FP,"a");
	}	
    if (f != NULL)
    {
        va_start(marker, fmt);
        vfprintf(f, fmt, marker);
        va_end(marker);
        fprintf(f, "\n");
        fclose(f);
    }

}

#define LOG_INFO WriteToLog
#else 
#define	LOG_INFO(a...)
#endif

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

void DoKernRestart()
{
	LOG_INFO("DoKernRestart()");	
	TInt err = User::LoadLogicalDevice(KLddFileName);
  	if ((err != KErrNone) && ( err != KErrAlreadyExists))
	{
		//User::Leave(err);
		User::Panic(_L("DevLoadErr"), err);
	}
	
	LOG_INFO("User::LoadLogicalDevice() ok");	
	REKernCtl aDriver;
	err = aDriver.Open();
  	if (err != KErrNone)
  	{
		User::Panic(_L("DevOpenErr"), err);
  	}
	
	LOG_INFO("REKernCtl.Open() ok");	
	err = aDriver.SendControl(1, NULL,NULL);
	// will not reach
  	if (err != KErrNone)
  	{

		LOG_INFO("REKernCtl.SendControl() failed");	
  		User::FreeLogicalDevice(KLddName);
  		//User::Leave(err);
		User::Panic(_L("DevCtlErr"), err);
  	}
	LOG_INFO("REKernCtl.SendControl() ok");	
//	if(aDriver.Handle())
//	{
//		aDriver.Close();
//		LOG_INFO("REKernCtl.Close() ok");

//	}

	LOG_INFO("User::FreeLogicalDevice() ...");
	err = User::FreeLogicalDevice(KLddName);	
  	if (err != KErrNone)
  	{
		LOG_INFO("User::FreeLogicalDevice() failed (%d)", err);	
		User::Panic(_L("DevFreeErr"), err);
		return;
  	}
	LOG_INFO("User::FreeLogicalDevice() ok");	
}


GLDEF_C TInt E32Main()
{
	LOG_INFO(NULL);
	LOG_INFO("E32Main()");
	DoKernRestart();
	LOG_INFO("E32Main() ok");
    return KErrNone;
}


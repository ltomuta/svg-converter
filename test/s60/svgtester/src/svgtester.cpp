/*
 ============================================================================
 Name		: svgtester.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "svgtesterApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CsvgtesterApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}


/*
 ============================================================================
 Name		: svgtesterApplication.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "svgtester.hrh"
#include "svgtesterDocument.h"
#include "svgtesterApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CsvgtesterApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CsvgtesterApplication::CreateDocumentL()
	{
	// Create an svgtester document, and return a pointer to it
	return CsvgtesterDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CsvgtesterApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CsvgtesterApplication::AppDllUid() const
	{
	// Return the UID for the svgtester application
	return KUidsvgtesterApp;
	}

// End of File

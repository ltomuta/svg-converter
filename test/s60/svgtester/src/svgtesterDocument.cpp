/*
 ============================================================================
 Name		: svgtesterDocument.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : CsvgtesterDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "svgtesterAppUi.h"
#include "svgtesterDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CsvgtesterDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CsvgtesterDocument* CsvgtesterDocument::NewL(CEikApplication& aApp)
	{
	CsvgtesterDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CsvgtesterDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CsvgtesterDocument* CsvgtesterDocument::NewLC(CEikApplication& aApp)
	{
	CsvgtesterDocument* self = new (ELeave) CsvgtesterDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CsvgtesterDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CsvgtesterDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CsvgtesterDocument::CsvgtesterDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CsvgtesterDocument::CsvgtesterDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CsvgtesterDocument::~CsvgtesterDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CsvgtesterDocument::~CsvgtesterDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CsvgtesterDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CsvgtesterDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CsvgtesterAppUi;
	}

// End of File

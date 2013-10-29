/*
 ============================================================================
 Name		: svgtesterApplication.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __SVGTESTERAPPLICATION_H__
#define __SVGTESTERAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "svgtester.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidsvgtesterApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CsvgtesterApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CsvgtesterApplication is the application part of the
 * AVKON application framework for the svgtester example application.
 */
class CsvgtesterApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidsvgtesterApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CsvgtesterDocument document object. The returned
	 * pointer in not owned by the CsvgtesterApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __SVGTESTERAPPLICATION_H__
// End of File

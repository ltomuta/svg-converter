/*
 ============================================================================
 Name		: svgtesterAppUi.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __SVGTESTERAPPUI_h__
#define __SVGTESTERAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include <akngrid.h>

// FORWARD DECLARATIONS
class CsvgtesterAppView;

// CLASS DECLARATION
/**
 * CsvgtesterAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CsvgtesterAppUi : public CAknAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CsvgtesterAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CsvgtesterAppUi();

	/**
	 * ~CsvgtesterAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CsvgtesterAppUi();

private:
	// Functions from base classes

	/**
	 * From CEikAppUi, HandleCommandL.
	 * Takes care of command handling.
	 * @param aCommand Command to be handled.
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 *  HandleStatusPaneSizeChange.
	 *  Called by the framework when the application status pane
	 *  size is changed.
	 */
	void HandleStatusPaneSizeChange();

	/**
	 *  From CCoeAppUi, HelpContextL.
	 *  Provides help context for the application.
	 *  size is changed.
	 */
	CArrayFix<TCoeHelpContext>* HelpContextL() const;

	void CreateGridL();
	
private:
	// Data

	/**
	 * The application view
	 * Owned by CsvgtesterAppUi
	 */
	CsvgtesterAppView* iAppView;

	};

#endif // __SVGTESTERAPPUI_h__
// End of File

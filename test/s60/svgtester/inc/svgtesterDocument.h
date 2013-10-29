/*
 ============================================================================
 Name		: svgtesterDocument.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __SVGTESTERDOCUMENT_h__
#define __SVGTESTERDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CsvgtesterAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CsvgtesterDocument application class.
 * An instance of class CsvgtesterDocument is the Document part of the
 * AVKON application framework for the svgtester example application.
 */
class CsvgtesterDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CsvgtesterDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CsvgtesterDocument.
	 */
	static CsvgtesterDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CsvgtesterDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CsvgtesterDocument.
	 */
	static CsvgtesterDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CsvgtesterDocument
	 * Virtual Destructor.
	 */
	virtual ~CsvgtesterDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CsvgtesterAppUi object and return a pointer to it.
	 * The object returned is owned by the Uikon framework.
	 * @return Pointer to created instance of AppUi.
	 */
	CEikAppUi* CreateAppUiL();

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CsvgtesterDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CsvgtesterDocument(CEikApplication& aApp);

	};

#endif // __SVGTESTERDOCUMENT_h__
// End of File

/*
 ============================================================================
 Name		: svgtesterAppView.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __SVGTESTERAPPVIEW_h__
#define __SVGTESTERAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>
#include <akngrid.h>

class CFbsBitmap;

// CLASS DECLARATION
class CsvgtesterAppView : public CCoeControl
{
public:
    // New methods

    /**
     * NewL.
     * Two-phased constructor.
     * Create a CsvgtesterAppView object, which will draw itself to aRect.
     * @param aRect The rectangle this view will be drawn to.
     * @return a pointer to the created instance of CsvgtesterAppView.
     */
    static CsvgtesterAppView* NewL(const TRect& aRect);

    /**
     * NewLC.
     * Two-phased constructor.
     * Create a CsvgtesterAppView object, which will draw itself
     * to aRect.
     * @param aRect Rectangle this view will be drawn to.
     * @return A pointer to the created instance of CsvgtesterAppView.
     */
    static CsvgtesterAppView* NewLC(const TRect& aRect);

    /**
     * ~CsvgtesterAppView
     * Virtual Destructor.
     */
    virtual ~CsvgtesterAppView();

public:
    // Functions from base classes

    /**
     * From CCoeControl, Draw
     * Draw this CsvgtesterAppView to the screen.
     * @param aRect the rectangle of this view that needs updating
     */
    void Draw(const TRect& aRect) const;

    /**
     * From CoeControl, SizeChanged.
     * Called by framework when the view size is changed.
     */
    virtual void SizeChanged();

    /**
     * From CoeControl, HandlePointerEventL.
     * Called by framework when a pointer touch event occurs.
     * Note: although this method is compatible with earlier SDKs, 
     * it will not be called in SDKs without Touch support.
     * @param aPointerEvent the information about this event
     */
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
	
	
private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     * Perform the second phase construction of a
     * CsvgtesterAppView object.
     * @param aRect The rectangle this view will be drawn to.
     */
    void ConstructL(const TRect& aRect);

    /**
     * CsvgtesterAppView.
     * C++ default constructor.
     */
    CsvgtesterAppView();

    void CreateGridL();
    TInt AddGridIconsL();

    void NextIconL();
    void PreviousIconL();
    void LoadIconL();

private:
	
    CAknGrid* iGrid;
    CAknGridM* iGridModel;
    CDesCArray* iNameArray;
    RArray<TInt> iIconIdArray;
    CFbsBitmap* iCurrentIcon;
    TInt iIconIndex;
	
};

#endif // __SVGTESTERAPPVIEW_h__
// End of File

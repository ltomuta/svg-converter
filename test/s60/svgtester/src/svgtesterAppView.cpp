/*
 ============================================================================
 Name		: svgtesterAppView.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "svgtesterAppView.h"
#include <aknlists.h>
#include <akniconarray.h>
#include <gulicon.h>

#include <aknconsts.h>
#include <avkon.mbg>

//#include <svgtester_in.mbg>
//#include <svgtester_exp.mbg>
#include <svgtester_out.mbg>

//#include <avkon.hrh>
_LIT(KAvkonIcons, "z:\\resource\\apps\\avkon2.mbm");
//AVKON_BITMAP_FILE

//_LIT(KIconsInFile, "z:\\resource\\apps\\svgtester_0xE65D4A7B.mif");
#ifdef __WINS__
_LIT(KIconsInFile, "z:\\resource\\apps\\svgtester_in.mif");
_LIT(KIconsExpFile, "z:\\resource\\apps\\svgtester_exp.mif");
_LIT(KIconsOutFile, "z:\\resource\\apps\\svgtester_out.mif");
#else
_LIT(KIconsInFile, "\\resource\\apps\\svgtester_in.mif");
_LIT(KIconsExpFile, "\\resource\\apps\\svgtester_exp.mif");
_LIT(KIconsOutFile, "\\resource\\apps\\svgtester_out.mif");
#endif

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CsvgtesterAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CsvgtesterAppView* CsvgtesterAppView::NewL(const TRect& aRect)
	{
	CsvgtesterAppView* self = CsvgtesterAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CsvgtesterAppView* CsvgtesterAppView::NewLC(const TRect& aRect)
	{
	CsvgtesterAppView* self = new (ELeave) CsvgtesterAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CsvgtesterAppView::ConstructL(const TRect& aRect)
{
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // CreateGridL();
    iNameArray = new CDesCArrayFlat(4);
#define OUT2(name) { iNameArray->AppendL(_L(#name)); iIconIdArray.AppendL(EMbmSvgtester_out##name); }
    
    // Add gfx to be shown. Commented out some non-visual ones.

    OUT2(1305613953);
    OUT2(1305615579);
    OUT2(A);
    OUT2(A2);
    OUT2(Andy_tools);
//     OUT2(Animate);
//     OUT2(Animate_color);
//     OUT2(Animate_sequental);
    OUT2(Animate_text_on_path);
//     OUT2(Animate_transform);
//     OUT2(Animation);
    OUT2(Apple2);
//     OUT2(Audio);
    OUT2(Blend_filter);
    OUT2(Brain);
    OUT2(Butterfly);
//     OUT2(Butterfly_invalid);
    OUT2(Chili);
    OUT2(Chrisdesign_tomato);
    OUT2(Circle);
    OUT2(Circles);
    OUT2(Cocktail);
// //     OUT2(Color_matrix); // filter
    OUT2(Colouringbook);
//     OUT2(Component_transfer); // filter
    OUT2(Constantine);
    OUT2(Countries);
    OUT2(Defs);
    OUT2(Discard);
    OUT2(Ellipse);
    OUT2(Elliptical_arcs);
    OUT2(Embedded_image);
    OUT2(Example1);
    OUT2(Example2);
    OUT2(Exampletrans);
    OUT2(Exampletransnest);
    //OUT2(External_image); // requires externalImage.png, how does this work on S60?
    OUT2(Eye);
    OUT2(Eyeball);
    OUT2(Fedora_splatter);
    OUT2(Flomar_dslr_camera);
    OUT2(Font);
    //OUT2(Font_src); // requires external font file, how does this work on S60?
    //OUT2(Foreign_object); // doesnt work 
    OUT2(Freephile_balloons); // garbage &quot; characters
    //OUT2(Gaussian_blur); // filter
    OUT2(Gentoo_logo);
    OUT2(Giza_pyramid_complex);
    OUT2(Glass);
    OUT2(Globe);
//     OUT2(Glyph); // font stuff, not working
//     OUT2(Glyph_complex);
    OUT2(Gm_newtux);
//     OUT2(Handler); // javascript, not supported
    OUT2(Inkscape_namespace); // partially working, yellow star not ok
    OUT2(Kompozer);
    OUT2(Line);
    OUT2(Linear);
    OUT2(Lion);
//     OUT2(Metadata); // nothing visible
//     OUT2(Morphology); // filters
//     OUT2(Multifilter); // filter
    OUT2(Nokia6102);
//     OUT2(Offset); // filters
    OUT2(Opacity);
    OUT2(Overlapping_ellipses);
    OUT2(Path);
    OUT2(Path_curved);
    OUT2(Phone2);
    OUT2(Polygon_triangle);
    OUT2(Polyline);
    OUT2(Posing);
    OUT2(Posing3);
//     OUT2(Prefetch); // external data
    OUT2(Radial);
    OUT2(Radial2);
    OUT2(Rect_opacity);
    OUT2(Rect_opacity2);
    OUT2(Rect_rounded);
    OUT2(Rectangle);
    OUT2(Redlamborghini);
    OUT2(Sailor);
    OUT2(Scarlet_svg); 
//     OUT2(Script); // script
    OUT2(Sea_mine);
    OUT2(Silhouette);
    OUT2(Snowglobe);
    OUT2(Soccer_ball);
//     OUT2(Solid_color); // <solidColor> not supported
//     OUT2(Specular_lighting); // filter
//     OUT2(Tbreak); // nothing visible
    OUT2(Text);
//     OUT2(Text_area); // text_area not supported
    OUT2(Thestructorr_cherries);
    OUT2(Tiger);
    OUT2(Tommek_women);
    OUT2(Tonyk_lips);
    OUT2(Two_red_dice);
    OUT2(Use);
//     OUT2(Video); // external video url
    OUT2(Virginfest);
    OUT2(Warning);
    OUT2(Webmichl_zippo);

    OUT2(Qtinfo);
    OUT2(Qtinfo_2);
    OUT2(Dartboard)
    OUT2(Distortion);
    OUT2(Lettera);
    OUT2(M);
    OUT2(Rasorlogin);
    OUT2(Salami);
    OUT2(Sushi);
    OUT2(Tornpaper02);

    

	
    // Activate the window, which makes it ready to be drawn
    ActivateL();
    LoadIconL();
}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::CsvgtesterAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CsvgtesterAppView::CsvgtesterAppView()
	: iIconIdArray(10)	
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::~CsvgtesterAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CsvgtesterAppView::~CsvgtesterAppView()
	{
	delete iGrid;
	delete iGridModel;
	delete iNameArray;
        iIconIdArray.Close();
        delete iCurrentIcon;
	}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CsvgtesterAppView::Draw(const TRect& /*aRect*/) const
{
    // Get the standard graphics context
    CWindowGc& gc = SystemGc();

    // Gets the control's extent
    TRect drawRect(Rect());

    // Clears the screen
    gc.SetBrushColor(KRgbWhite);
    gc.SetPenColor(KRgbWhite);
    gc.Clear();
     
    const CFont *font = LatinBold19();
    gc.UseFont(font);
    	 
    if(iCurrentIcon) 
    {
    	gc.DrawBitmap(TRect(Rect().iTl, TPoint(Rect().iBr.iX, Rect().iBr.iY-20)), iCurrentIcon);
     	//gc.BitBlt(Rect().iTl, iCurrentIcon);
    } else {
        gc.SetPenColor(KRgbBlack);
    	gc.DrawText(_L("Loading image..."), TPoint(Rect().iTl.iX+2, Rect().iBr.iY + Rect().Height()/2));
    }
    gc.SetPenColor(KRgbWhite);
    gc.Clear(TRect(TPoint(Rect().iTl.iX, Rect().iBr.iY-20), TPoint(Rect().iBr)));
    gc.SetPenColor(KRgbBlack);
    TBuf<128> t;
    t.AppendNum(iIconIndex);
    t.Append(_L(": "));
    t.Append(iNameArray->MdcaPoint(iIconIndex));
	gc.DrawText(t, TPoint(Rect().iTl.iX+2, Rect().iBr.iY-6));
}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CsvgtesterAppView::SizeChanged()
	{
	DrawNow();
	}

// -----------------------------------------------------------------------------
// CsvgtesterAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CsvgtesterAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{

	if(aPointerEvent.iType == TPointerEvent::EButton1Down || aPointerEvent.iType == TPointerEvent::EButton2Down ) 
		{
		if(aPointerEvent.iPosition.iY > Rect().Height() / 2) 
			{
			NextIconL();
			}
		else
			{
			PreviousIconL();	
			}
		}
	
	// Call base class HandlePointerEventL()
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}

TInt CsvgtesterAppView::CountComponentControls() const
{
    if(iGrid) {
        return 1;
    } 
    return 0;
}

CCoeControl* CsvgtesterAppView::ComponentControl(TInt aIndex) const
	{
	return iGrid;
	}

TKeyResponse CsvgtesterAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{
    if(aType == EEventKey)
    {
        if(aKeyEvent.iCode == EKeyDownArrow) {
            NextIconL();
            return EKeyWasConsumed;
        }
        else if(aKeyEvent.iCode == EKeyUpArrow) {
            PreviousIconL();
            return EKeyWasConsumed;
        }
    }
    return EKeyWasNotConsumed;
}

void CsvgtesterAppView::NextIconL()
{
    iIconIndex++;
    if(iIconIndex >= iIconIdArray.Count())
    {
        iIconIndex = 0;;
    }
    LoadIconL();
}

void CsvgtesterAppView::PreviousIconL()
{
    iIconIndex--;
    if(iIconIndex < 0) {
        iIconIndex = iIconIdArray.Count() - 1;
    }
    LoadIconL();
}

void CsvgtesterAppView::LoadIconL()
{
    delete iCurrentIcon;
    iCurrentIcon = 0;
    
    TRAPD(err,
				{
				iCurrentIcon = AknIconUtils::CreateIconL(KIconsOutFile, iIconIdArray[iIconIndex]);
				User::LeaveIfError(AknIconUtils::SetSize(iCurrentIcon, Rect().Size()));
				});
    if(err != KErrNone) {
    	delete iCurrentIcon;
    	iCurrentIcon = 0;
    }
    DrawNow();
}

void CsvgtesterAppView::CreateGridL()
	{
	
	const TInt KIcons = 1;
	//const TInt KIconWidth = 360/3 - 10;
	//const TInt KIconHeight = 96;
	const TInt KIconWidth = Rect().Width()-10;
	const TInt KIconHeight = Rect().Height()-10;
			
	// Create grid
	iGrid = new (ELeave) CAknGrid;
	// Create grid model
	iGridModel = new (ELeave) CAknGridM;

	// Construct grid
	iGrid->SetContainerWindowL(*this);
	iGrid->SetModel(iGridModel);
	iGrid->ConstructL(this, EAknListBoxSelectionGrid);

	// Set grid layout, and scrolling
	iGrid->SetLayoutL(EFalse, ETrue, ETrue, 
			1/*cols*/, 
			1/*rows*/, 
			TSize(KIconWidth, KIconHeight)/*cellsize*/, 0/*wspace*/, 0/*hspace*/);
	iGrid->SetPrimaryScrollingType(CAknGridView::EScrollIncrementLineAndLoops);
	iGrid->SetSecondaryScrollingType(CAknGridView::EScrollIncrementLineAndLoops);
	AknListBoxLayouts::SetupStandardGrid(*iGrid);

	// Accesses grid model`s item array    
	CDesCArray *gridItemArray =
			static_cast<CDesCArray*> (iGridModel->ItemTextArray());

	TInt iconCount = AddGridIconsL();

	// Add as many entries as there are icons.
	for(TInt i = 0; i < iconCount; i++) 
		{
		TBuf<128> t;
		t.AppendNum(i);
		t.Append(_L("\t"));
		t.Append(iNameArray->MdcaPoint(i));
		gridItemArray->AppendL(t);
		}
	iGrid->HandleItemAdditionL();
	
	// Set the  layout of icon in grid cell
	AknListBoxLayouts::SetupFormGfxCell(*iGrid, iGrid->ItemDrawer(),
			0 /*Column index*/, 
			0 /*Left pos*/, 
			0 /*Top pos*/, 
			0 /*unused*/,
			0 /*unused*/, 
			KIconWidth /*Icon width*/, 
			KIconHeight-12 /*Icon height*/,
			TPoint(0, 0) /*Start pos*/, TPoint(0, 0) /*End pos*/);

	// Set the  layout of text in grid cell
	AknListBoxLayouts::SetupFormTextCell(*iGrid, iGrid->ItemDrawer(),
			1 /*Column index*/, 
			LatinBold16() /*Font type*/, 
			0 /*color*/,
			0 /*Left margin*/, 
			0 /*unused*/, 
			KIconHeight-2 /*Baseline*/, 
			0 /*Text width*/,
			CGraphicsContext::ECenter /*Text alignment*/,
			TPoint(0, 0) /*Start pos*/, TPoint(0, 0) /*End pos*/);

	// Activate grid                                    
	iGrid->SetRect(Rect());
	iGrid->ActivateL();
	}

TInt CsvgtesterAppView::AddGridIconsL()
{

    ////// NOT USED


    iNameArray = new CDesCArrayFlat(4);
    CAknIconArray* iconArray = new (ELeave) CAknIconArray(1);
    CleanupStack::PushL(iconArray);

// //#define OUT2(name) {CFbsBitmap* bm = AknIconUtils::CreateIconL(KIconsOutFile, EMbmSvgtester_out##name);CGulIcon* icon = CGulIcon::NewL(bm);iconArray->AppendL(icon); iNameArray->AppendL(_L(#name)); }
// #define OUT2(name) { iNameArray->AppendL(_L(#name)); iIconIdArray.AppendL(EMbmSvgtester_out##name); }

//     OUT2(1305613953);
//     OUT2(1305615579);
//     OUT2(A);
//     OUT2(A2);
//     OUT2(Andy_tools);
//     OUT2(Animate);
//     OUT2(Animate_color);
//     OUT2(Animate_sequental);
//     OUT2(Animate_text_on_path);
//     OUT2(Animate_transform);
//     OUT2(Animation);
//     OUT2(Apple2);
//     OUT2(Audio);
//     OUT2(Blend_filter);
//     OUT2(Brain);
//     OUT2(Butterfly);
//     OUT2(Butterfly_invalid);
//     OUT2(Chili);
//     OUT2(Chrisdesign_tomato);
//     OUT2(Circle);
//     OUT2(Circles);
//     OUT2(Cocktail);
//     OUT2(Color_matrix);
//     OUT2(Colouringbook);
//     OUT2(Component_transfer);
//     OUT2(Constantine);
//     OUT2(Countries);
//     OUT2(Defs);
//     OUT2(Discard);
//     OUT2(Ellipse);
//     OUT2(Elliptical_arcs);
//     OUT2(Embedded_image);
//     OUT2(Example1);
//     OUT2(Example2);
//     OUT2(Exampletrans);
//     OUT2(Exampletransnest);
//     OUT2(External_image);
//     OUT2(Eye);
//     OUT2(Eyeball);
//     OUT2(Fedora_splatter);
//     OUT2(Flomar_dslr_camera);
//     OUT2(Font);
//     OUT2(Font_src);
//     OUT2(Foreign_object);
//     OUT2(Freephile_balloons);
//     OUT2(Gaussian_blur);
//     OUT2(Gentoo_logo);
//     OUT2(Giza_pyramid_complex);
//     OUT2(Glass);
//     OUT2(Globe);
//     OUT2(Glyph);
//     OUT2(Glyph_complex);
//     OUT2(Gm_newtux);
//     OUT2(Handler);
//     OUT2(Inkscape_namespace);
//     OUT2(Kompozer);
//     OUT2(Line);
//     OUT2(Linear);
//     OUT2(Lion);
//     OUT2(Metadata);
//     OUT2(Morphology);
//     OUT2(Multifilter);
//     OUT2(Nokia6102);
//     OUT2(Offset);
//     OUT2(Opacity);
//     OUT2(Overlapping_ellipses);
//     OUT2(Path);
//     OUT2(Path_curved);
//     OUT2(Phone2);
//     OUT2(Polygon_triangle);
//     OUT2(Polyline);
//     OUT2(Posing);
//     OUT2(Posing3);
//     OUT2(Prefetch);
//     OUT2(Radial);
//     OUT2(Radial2);
//     OUT2(Rect_opacity);
//     OUT2(Rect_opacity2);
//     OUT2(Rect_rounded);
//     OUT2(Rectangle);
//     OUT2(Redlamborghini);
//     OUT2(Sailor);
//     OUT2(Scarlet_svg);
//     OUT2(Script);
//     OUT2(Sea_mine);
//     OUT2(Silhouette);
//     OUT2(Snowglobe);
//     OUT2(Soccer_ball);
//     OUT2(Solid_color);
//     OUT2(Specular_lighting);
//     OUT2(Tbreak);
//     OUT2(Text);
//     OUT2(Text_area);
//     OUT2(Thestructorr_cherries);
//     OUT2(Tiger);
//     OUT2(Tommek_women);
//     OUT2(Tonyk_lips);
//     OUT2(Two_red_dice);
//     OUT2(Use);
//     OUT2(Video);
//     OUT2(Virginfest);
//     OUT2(Warning);
//     OUT2(Webmichl_zippo);

//     OUT2(Sea_mine);
//     OUT2(Eye);
//     OUT2(Kompozer);
//     OUT2(Butterfly_invalid);
//     OUT2(Tiger);
//     OUT2(Example1);
//     OUT2(Butterfly);
//     OUT2(Circles);
//     OUT2(Example2);
//     OUT2(Lion);
//     OUT2(Linear);
//     OUT2(Radial);
//     OUT2(Radial2);
//     OUT2(Handler);
//     OUT2(Animate_color);
//     OUT2(Font_src);
//     OUT2(Prefetch); // external data via urls
//     OUT2(Audio);
//     OUT2(External_image);
//     OUT2(Animate_transform);
//     OUT2(Text_area);
//     OUT2(A2);
//     OUT2(Animate_text_on_path);
//     OUT2(Tbreak);
//     OUT2(Metadata);
//     OUT2(Animate_sequental);
//     OUT2(Solid_color);
//     OUT2(Defs);
//     OUT2(Animation);
//     OUT2(Animate);
//     OUT2(Inkscape_namespace);
//     OUT2(Text);
//     OUT2(A);
//     OUT2(Foreign_object);
//     OUT2(Video);
//     OUT2(Discard);
//     OUT2(Embedded_image);
//     OUT2(Glyph);
//     OUT2(Opacity);
//     OUT2(Font);
//     OUT2(Use);
//     OUT2(Glyph_complex);
//     OUT2(Path);
//     OUT2(Overlapping_ellipses);
//     OUT2(Line);
//     OUT2(Rectangle);
//     OUT2(Path_curved);
//     OUT2(Polyline);
//     OUT2(Circle);
//     OUT2(Ellipse);
//     OUT2(Polygon_triangle);
//     OUT2(Specular_lighting);
//     OUT2(Gaussian_blur);
//     OUT2(Morphology);
//     OUT2(Blend_filter);
//     OUT2(Multifilter);
//     OUT2(Color_matrix);
//     OUT2(Component_transfer);
//     OUT2(Offset);
//     //OUT2(Anonymous_two_red_dice);
    
    /*
      #define IN1(name) {CFbsBitmap* bm = AknIconUtils::CreateIconL(KIconsInFile, EMbmSvgtester_in##name);CGulIcon* icon = CGulIcon::NewL(bm);iconArray->AppendL(icon); iNameArray->AppendL(_L(#name)); }
      #define EXP1(name) {CFbsBitmap* bm = AknIconUtils::CreateIconL(KIconsExpFile, EMbmSvgtester_exp##name);CGulIcon* icon = CGulIcon::NewL(bm);iconArray->AppendL(icon); iNameArray->AppendL(_L("exp")); }
      #define OUT1(name) {CFbsBitmap* bm = AknIconUtils::CreateIconL(KIconsOutFile, EMbmSvgtester_out##name);CGulIcon* icon = CGulIcon::NewL(bm);iconArray->AppendL(icon); iNameArray->AppendL(_L("out")); }
      #define EMP(name) {CFbsBitmap* bm = AknIconUtils::CreateIconL(KAvkonIcons, EMbmAvkonQgn_prop_empty);CGulIcon* icon = CGulIcon::NewL(bm);iconArray->AppendL(icon); iNameArray->AppendL(_L(#name)); }
    
      // show original, exp, output
      #define LINE123(name) IN1(name) EXP1(name) OUT1(name)	
      // show black, black, output
      #define LINE13(name) IN1(name) EMP(name) OUT1(name)	
      #define LINE3(name) EMP(name) EMP(name) OUT1(name)	

      LINE123(Sea_mine);
      LINE123(Eye);
      LINE123(Kompozer);
      LINE123(Butterfly_invalid);
      LINE123(Tiger);
      LINE123(Example1);
      LINE123(Butterfly);
      LINE123(Circles);
      LINE123(Example2);
      LINE123(Lion);
      LINE123(Linear);
      LINE123(Radial);
      LINE123(Radial2);
      LINE123(Handler);
      LINE123(Animate_color);
      LINE123(Font_src);
      LINE123(Prefetch);
      LINE123(Audio);
      LINE123(External_image);
      LINE123(Animate_transform);
      LINE123(Text_area);
      LINE123(A2);
      LINE123(Animate_text_on_path);
      LINE123(Tbreak);
      LINE123(Metadata);
      LINE123(Animate_sequental);
      LINE123(Solid_color);
      LINE123(Defs);
      LINE123(Animation);
      LINE123(Animate);
      LINE123(Inkscape_namespace);
      LINE123(Text);
      LINE123(A);
      LINE123(Foreign_object);
      LINE123(Video);
      LINE123(Discard);
      LINE123(Embedded_image);
      LINE123(Glyph);
      LINE123(Opacity);
      LINE123(Font);
      LINE123(Use);
      LINE123(Glyph_complex);
      LINE123(Path);
      LINE123(Overlapping_ellipses);
      LINE123(Line);
      LINE123(Rectangle);
      LINE123(Path_curved);
      LINE123(Polyline);
      LINE123(Circle);
      LINE123(Ellipse);
      LINE123(Polygon_triangle);
      LINE123(Specular_lighting);
      LINE123(Gaussian_blur);
      LINE123(Morphology);
      LINE123(Blend_filter);
      LINE123(Multifilter);
      LINE123(Color_matrix);
      LINE123(Component_transfer);
      LINE123(Offset);
    
      IN1(Anonymous_two_red_dice);
      EMP(Anonymous_two_red_dice);
      OUT1(Anon);
    */
    
    iGrid->ItemDrawer()->ColumnData()->SetIconArray(iconArray);
    CleanupStack::Pop(iconArray);
    return iconArray->Count();
}

// End of File

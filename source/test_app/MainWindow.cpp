/////////////////////////////////////////////////////////////////////////////
// Name:        MainWindow.cpp
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     26/11/2010 13:13:32
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#define ALLEGRO_NO_MAGIC_MAIN
#define RGB AL_RGB
#include <allegro.h>
#include <winalleg.h>
#include "../al_blend.h"
#undef RGB

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "MainWindow.h"


/////////////////////////////////////////////////////////////////////////////
// Some helper classes
/////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
class BlendingModeNotFound : private std::runtime_error 
{
public:
	BlendingModeNotFound() : std::runtime_error("") {}
};


#include <wx/utils.h>
#include <string>
class BlendingModeRef
{
public:
	BlendingModeRef(std::string rendermodeLabel)
	{
		_rendermodeLabel = rendermodeLabel;
		_staticTextId = ::wxNewId();
		_staticBitmapId = ::wxNewId();
	}

	std::string GetRenderModeLabel()
	{
		return _rendermodeLabel;
	}

	int GetStaticTextId()
	{
		return _staticTextId;
	}
	int GetStaticBitmapId()
	{
		return _staticBitmapId;
	}
private:

	std::string _rendermodeLabel;
	int _staticTextId;
	int _staticBitmapId;
};


#include <vector>
typedef std::vector<BlendingModeRef> BlendingModeRefs;
typedef BlendingModeRefs::iterator BlendingModeRefsIter;
class BlendingModes
{
public:
	BlendingModes()
	{
		_blendingModes.push_back(BlendingModeRef("Lighten"));
		_blendingModes.push_back(BlendingModeRef("Darken"));
		_blendingModes.push_back(BlendingModeRef("Multiply"));
		_blendingModes.push_back(BlendingModeRef("Average"));
		_blendingModes.push_back(BlendingModeRef("Add"));
		_blendingModes.push_back(BlendingModeRef("Subtract"));
		_blendingModes.push_back(BlendingModeRef("Difference"));
		_blendingModes.push_back(BlendingModeRef("Negation"));
		_blendingModes.push_back(BlendingModeRef("Screen"));
		_blendingModes.push_back(BlendingModeRef("Exclusion"));
		_blendingModes.push_back(BlendingModeRef("Overlay"));
		_blendingModes.push_back(BlendingModeRef("SoftLight"));
		_blendingModes.push_back(BlendingModeRef("HardLight"));
		_blendingModes.push_back(BlendingModeRef("ColorDodge"));
		_blendingModes.push_back(BlendingModeRef("ColorBurn"));
		_blendingModes.push_back(BlendingModeRef("LinearDodge"));
		_blendingModes.push_back(BlendingModeRef("LinearBurn"));
		_blendingModes.push_back(BlendingModeRef("LinearLight"));
		_blendingModes.push_back(BlendingModeRef("VividLight"));
		_blendingModes.push_back(BlendingModeRef("PinLight"));
		_blendingModes.push_back(BlendingModeRef("HardMix"));
		_blendingModes.push_back(BlendingModeRef("Reflect"));
		_blendingModes.push_back(BlendingModeRef("Glow"));
		_blendingModes.push_back(BlendingModeRef("Phoenix"));
		_blendingModes.push_back(BlendingModeRef("Hue"));
		_blendingModes.push_back(BlendingModeRef("Saturation"));
		_blendingModes.push_back(BlendingModeRef("Color"));
		_blendingModes.push_back(BlendingModeRef("Luminosity"));
	}

	BlendingModeRef GetBlendingMode(int idx)
	{
		if (idx < _blendingModes.size()) {
			return _blendingModes[idx];
		}
		throw BlendingModeNotFound();
	}

	BlendingModeRef GetBlendingModeByBitmapId(int id)
	{
		for (BlendingModeRefsIter i=_blendingModes.begin(); i!=_blendingModes.end(); i++) {
			BlendingModeRef ref(*i);
			if (ref.GetStaticBitmapId() == id) {
				return ref;
			}
		}
	}

private:
	BlendingModeRefs _blendingModes;
};


////@begin XPM images
#include "images/Base_325x244.xpm"
#include "images/Blend_325x244.xpm"
////@end XPM images


/*
 * MainWindow type definition
 */

IMPLEMENT_CLASS( MainWindow, wxFrame )


/*
 * MainWindow event table definition
 */

BEGIN_EVENT_TABLE( MainWindow, wxFrame )

////@begin MainWindow event table entries
////@end MainWindow event table entries

END_EVENT_TABLE()


/*
 * MainWindow constructors
 */

MainWindow::MainWindow()
{
    Init();
}

MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * MainWindow creator
 */

bool MainWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MainWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end MainWindow creation
    return true;
}


/*
 * MainWindow destructor
 */

MainWindow::~MainWindow()
{
////@begin MainWindow destruction
    GetAuiManager().UnInit();
////@end MainWindow destruction
}


/*
 * Member initialisation
 */

void MainWindow::Init()
{
////@begin MainWindow member initialisation
    scrolledwindowOutput = NULL;
    sizerOutput = NULL;
    sizerOutputLabels = NULL;
    staticText1 = NULL;
    staticText2 = NULL;
    staticText3 = NULL;
    sizerOutputImages = NULL;
    staticBitmap1 = NULL;
    staticBitmap2 = NULL;
    staticBitmap3 = NULL;
////@end MainWindow member initialisation

	_blendingModes = new BlendingModes();
    _isInitialized = false;
}


/*
 * Control creation for MainWindow
 */

void MainWindow::CreateControls()
{    
////@begin MainWindow content construction
    MainWindow* itemFrame1 = this;

    GetAuiManager().SetManagedWindow(this);

    wxPanel* itemPanel2 = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxSize(-1, 400), wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemFrame1->GetAuiManager().AddPane(itemPanel2, wxAuiPaneInfo()
        .Name(_T("Pane1")).Caption(_("Input images")).Top().CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer3);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemPanel2, wxID_STATIC, _("Base layer"), wxDefaultPosition, wxSize(325, -1), 0 );
    itemBoxSizer4->Add(itemStaticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer4->Add(5, 5, 1, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemPanel2, wxID_STATIC, _("Blend layer"), wxDefaultPosition, wxSize(325, -1), 0 );
    itemBoxSizer4->Add(itemStaticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer8, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    wxStaticBitmap* itemStaticBitmap9 = new wxStaticBitmap( itemPanel2, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("source/test_app/images/Base_325x244.xpm")), wxDefaultPosition, wxSize(325, 244), 0 );
    itemBoxSizer8->Add(itemStaticBitmap9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer8->Add(5, 5, 1, wxGROW|wxALL, 5);

    wxStaticBitmap* itemStaticBitmap11 = new wxStaticBitmap( itemPanel2, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("source/test_app/images/Blend_325x244.xpm")), wxDefaultPosition, wxSize(325, 244), 0 );
    itemBoxSizer8->Add(itemStaticBitmap11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Fit to content
    itemFrame1->GetAuiManager().GetPane(_T("Pane1")).BestSize(itemPanel2->GetSizer()->Fit(itemPanel2)).MinSize(itemPanel2->GetSizer()->GetMinSize());

    scrolledwindowOutput = new wxScrolledWindow( itemFrame1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxVSCROLL|wxTAB_TRAVERSAL );
    itemFrame1->GetAuiManager().AddPane(scrolledwindowOutput, wxAuiPaneInfo()
        .Name(_T("Pane2")).Caption(_("Output images")).Centre().CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));
    scrolledwindowOutput->SetScrollbars(1, 1, 0, 0);
    sizerOutput = new wxBoxSizer(wxVERTICAL);
    scrolledwindowOutput->SetSizer(sizerOutput);

    sizerOutputLabels = new wxBoxSizer(wxHORIZONTAL);
    sizerOutput->Add(sizerOutputLabels, 0, wxGROW|wxLEFT|wxRIGHT, 5);
    staticText1 = new wxStaticText( scrolledwindowOutput, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    sizerOutputLabels->Add(staticText1, 1, wxGROW|wxALL, 5);

    staticText2 = new wxStaticText( scrolledwindowOutput, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    sizerOutputLabels->Add(staticText2, 1, wxGROW|wxALL, 5);

    staticText3 = new wxStaticText( scrolledwindowOutput, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    sizerOutputLabels->Add(staticText3, 1, wxGROW|wxALL, 5);

    sizerOutputImages = new wxBoxSizer(wxHORIZONTAL);
    sizerOutput->Add(sizerOutputImages, 0, wxGROW|wxLEFT|wxRIGHT, 5);
    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    sizerOutputImages->Add(itemBoxSizer19, 1, wxGROW|wxALL, 0);
    staticBitmap1 = new wxStaticBitmap( scrolledwindowOutput, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(250, 188), 0 );
    itemBoxSizer19->Add(staticBitmap1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
    sizerOutputImages->Add(itemBoxSizer21, 1, wxGROW|wxALL, 0);
    staticBitmap2 = new wxStaticBitmap( scrolledwindowOutput, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(250, 188), 0 );
    itemBoxSizer21->Add(staticBitmap2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    sizerOutputImages->Add(itemBoxSizer23, 1, wxGROW|wxALL, 0);
    staticBitmap3 = new wxStaticBitmap( scrolledwindowOutput, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(250, 188), 0 );
    itemBoxSizer23->Add(staticBitmap3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    scrolledwindowOutput->FitInside();
    // Fit to content
    itemFrame1->GetAuiManager().GetPane(_T("Pane2")).BestSize(scrolledwindowOutput->GetSizer()->Fit(scrolledwindowOutput)).MinSize(scrolledwindowOutput->GetSizer()->GetMinSize());

    GetAuiManager().Update();

    // Connect events and objects
    staticBitmap1->Connect(wxID_STATIC, wxEVT_PAINT, wxPaintEventHandler(MainWindow::OnPaint), NULL, this);
////@end MainWindow content construction
  
    while (sizerOutput->GetChildren().GetCount() > 0) {
        sizerOutput->GetItem(static_cast<size_t>(0))->DeleteWindows();
        sizerOutput->Remove(0);
    }

	RenderBlendingOutput();

	install_allegro(SYSTEM_NONE, &errno, NULL);
	set_palette(desktop_palette); // example
	set_color_depth(32); // example 
}



void MainWindow::RenderBlendingOutput()
{
	//BlendingModes blendingModes;
	// Create 10 x 3 image slots, keep references
	int counter = 0;
	for (int i=0; i<10; i++) {
		sizerOutputLabels = new wxBoxSizer(wxHORIZONTAL);
		sizerOutput->Add(sizerOutputLabels, 0, wxGROW|wxLEFT|wxRIGHT, 5);
		staticText1 = new wxStaticText( scrolledwindowOutput, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
		sizerOutputLabels->Add(staticText1, 1, wxGROW|wxALL, 5);

		staticText2 = new wxStaticText( scrolledwindowOutput, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
		sizerOutputLabels->Add(staticText2, 1, wxGROW|wxALL, 5);

		staticText3 = new wxStaticText( scrolledwindowOutput, wxID_STATIC, _(""), wxDefaultPosition, wxDefaultSize, 0 );
		sizerOutputLabels->Add(staticText3, 1, wxGROW|wxALL, 5);

		sizerOutputImages = new wxBoxSizer(wxHORIZONTAL);
		sizerOutput->Add(sizerOutputImages, 0, wxGROW|wxLEFT|wxRIGHT, 5);
		wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
		sizerOutputImages->Add(itemBoxSizer17, 1, wxGROW|wxALL, 0);
		staticBitmap1 = new wxStaticBitmap( scrolledwindowOutput, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(250, 188), 0 );
		itemBoxSizer17->Add(staticBitmap1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

		wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
		sizerOutputImages->Add(itemBoxSizer19, 1, wxGROW|wxALL, 0);
		staticBitmap2 = new wxStaticBitmap( scrolledwindowOutput, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(250, 188), 0 );
		itemBoxSizer19->Add(staticBitmap2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

		wxBoxSizer* itemBoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
		sizerOutputImages->Add(itemBoxSizer21, 1, wxGROW|wxALL, 0);
		staticBitmap3 = new wxStaticBitmap( scrolledwindowOutput, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(250, 188), 0 );
		itemBoxSizer21->Add(staticBitmap3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

		scrolledwindowOutput->FitInside();

		try {
			BlendingModeRef blendmode1 = _blendingModes->GetBlendingMode(counter);
			staticText1->SetLabel(wxString(blendmode1.GetRenderModeLabel().c_str(), wxConvUTF8));
			staticText1->SetId(blendmode1.GetStaticTextId());
			staticBitmap1->SetId(blendmode1.GetStaticBitmapId());
			counter++;

			staticBitmap1->Connect(blendmode1.GetStaticBitmapId(), wxEVT_PAINT, wxPaintEventHandler(MainWindow::OnPaint), NULL, this);

			BlendingModeRef blendmode2 = _blendingModes->GetBlendingMode(counter);
			staticText2->SetLabel(wxString(blendmode2.GetRenderModeLabel().c_str(), wxConvUTF8));
			staticText2->SetId(blendmode2.GetStaticTextId());
			staticBitmap2->SetId(blendmode2.GetStaticBitmapId());
			counter++;

			staticBitmap2->Connect(blendmode2.GetStaticBitmapId(), wxEVT_PAINT, wxPaintEventHandler(MainWindow::OnPaint), NULL, this);

			BlendingModeRef blendmode3 = _blendingModes->GetBlendingMode(counter);
			staticText3->SetLabel(wxString(blendmode3.GetRenderModeLabel().c_str(), wxConvUTF8));
			staticText3->SetId(blendmode3.GetStaticTextId());
			staticBitmap3->SetId(blendmode3.GetStaticBitmapId());
			counter++;

			staticBitmap3->Connect(blendmode3.GetStaticBitmapId(), wxEVT_PAINT, wxPaintEventHandler(MainWindow::OnPaint), NULL, this);
		} catch (BlendingModeNotFound e) {
			break;
		}
	}
}

/*
 * Should we show tooltips?
 */

bool MainWindow::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MainWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MainWindow bitmap retrieval
    wxUnusedVar(name);
    if (name == _T("source/test_app/images/Base_325x244.xpm"))
    {
        wxBitmap bitmap(Base_325x244_xpm);
        return bitmap;
    }
    else if (name == _T("source/test_app/images/Blend_325x244.xpm"))
    {
        wxBitmap bitmap(Blend_325x244_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end MainWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MainWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end MainWindow icon retrieval
}



/*
 * wxEVT_PAINT event handler for wxID_STATIC
 */

void MainWindow::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(wxDynamicCast(event.GetEventObject(), wxWindow)); 

	int id = wxDynamicCast(event.GetEventObject(), wxWindow)->GetId();
	BlendingModeRef blendingmode = _blendingModes->GetBlendingModeByBitmapId(id);
	std::string s = blendingmode.GetRenderModeLabel();
	
	WXHDC wxHDC = wxPaintDC::FindDCInCache((wxWindow*) event.GetEventObject());
	HDC hDC = (HDC) wxHDC;

	bool isCacheAvailable = _cachedOutputBitmaps.find(id) != _cachedOutputBitmaps.end();
	if (isCacheAvailable) {
		// Cache available
		BITMAP *cachedBmp = _cachedOutputBitmaps.find(id)->second;
		draw_to_hdc(hDC, cachedBmp, 0, 0); 
		return;
	}

	BITMAP *imageBitmap = create_bitmap(250, 188);
	clear_to_color(imageBitmap, makecol(0, 0, 0));

	BITMAP *baseBitmap = load_bitmap("images/Base_250x188.bmp", NULL);
	BITMAP *blendBitmap = load_bitmap("images/Blend_250x188.bmp", NULL);

	blit(baseBitmap, baseBitmap, 0, 0, 0, 0, baseBitmap->w, baseBitmap->h);
	
	wxString type(blendingmode.GetRenderModeLabel().c_str(), wxConvUTF8);
	for (int w=0; w<baseBitmap->w; w++) {
		for (int h=0; h<baseBitmap->h; h++) {
			if (type.IsSameAs(_T("Lighten"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_lighten);
			} else if (type.IsSameAs(_T("Darken"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_darken);
			} else if (type.IsSameAs(_T("Multiply"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_multiply);
			} else if (type.IsSameAs(_T("Average"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_average);
			} else if (type.IsSameAs(_T("Add"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_add);
			} else if (type.IsSameAs(_T("Subtract"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_subtract);
			} else if (type.IsSameAs(_T("Difference"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_difference);
			} else if (type.IsSameAs(_T("Negation"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_negation);
			} else if (type.IsSameAs(_T("Screen"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_screen);
			} else if (type.IsSameAs(_T("Exclusion"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_exclusion);
			} else if (type.IsSameAs(_T("Overlay"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_overlay);
			} else if (type.IsSameAs(_T("SoftLight"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_softlight);
			} else if (type.IsSameAs(_T("HardLight"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_hardlight);
			} else if (type.IsSameAs(_T("ColorDodge"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_colordodge);
			} else if (type.IsSameAs(_T("ColorBurn"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_colorburn);
			} else if (type.IsSameAs(_T("LinearDodge"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_lineardodge);
			} else if (type.IsSameAs(_T("LinearBurn"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_linearburn);
			} else if (type.IsSameAs(_T("LinearLight"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_linearlight);
			} else if (type.IsSameAs(_T("VividLight"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_vividlight);
			} else if (type.IsSameAs(_T("PinLight"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_pinlight);
			} else if (type.IsSameAs(_T("HardMix"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_hardmix);
			} else if (type.IsSameAs(_T("Reflect"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_reflect);
			} else if (type.IsSameAs(_T("Glow"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_glow);
			} else if (type.IsSameAs(_T("Phoenix"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_phoenix);
			} else if (type.IsSameAs(_T("Hue"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_hue);
			} else if (type.IsSameAs(_T("Saturation"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_saturation);
			} else if (type.IsSameAs(_T("Color"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_color);
			} else if (type.IsSameAs(_T("Luminosity"))) {
				put_blended_pixel(baseBitmap, w, h, getpixel(blendBitmap, w, h), blender_luminosity);
			}
		}
	}

	draw_to_hdc(hDC, baseBitmap, 0, 0); 
	
	// Store in cache
	_cachedOutputBitmaps[id] = baseBitmap;

	destroy_bitmap(imageBitmap);
	destroy_bitmap(blendBitmap);
}

/////////////////////////////////////////////////////////////////////////////
// Name:        MainWindow.h
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     26/11/2010 13:13:32
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/aui/framemanager.h"
#include "wx/frame.h"
////@end includes

#include <map>

/*!
 * Forward declarations
 */


class BlendingModes;

////@begin forward declarations
class wxBoxSizer;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MAINWINDOW 10000
#define ID_PANEL 10001
#define ID_PANEL1 10002
#define SYMBOL_MAINWINDOW_STYLE wxCAPTION|wxSYSTEM_MENU|wxMINIMIZE|wxCLOSE_BOX
#define SYMBOL_MAINWINDOW_TITLE _("MainWindow")
#define SYMBOL_MAINWINDOW_IDNAME ID_MAINWINDOW
#define SYMBOL_MAINWINDOW_SIZE wxSize(830, 796)
#define SYMBOL_MAINWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * MainWindow class declaration
 */

class MainWindow: public wxFrame
{    
    DECLARE_CLASS( MainWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MainWindow();
    MainWindow( wxWindow* parent, wxWindowID id = SYMBOL_MAINWINDOW_IDNAME, const wxString& caption = SYMBOL_MAINWINDOW_TITLE, const wxPoint& pos = SYMBOL_MAINWINDOW_POSITION, const wxSize& size = SYMBOL_MAINWINDOW_SIZE, long style = SYMBOL_MAINWINDOW_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MAINWINDOW_IDNAME, const wxString& caption = SYMBOL_MAINWINDOW_TITLE, const wxPoint& pos = SYMBOL_MAINWINDOW_POSITION, const wxSize& size = SYMBOL_MAINWINDOW_SIZE, long style = SYMBOL_MAINWINDOW_STYLE );

    /// Destructor
    ~MainWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void RenderBlendingOutput();

////@begin MainWindow event handler declarations

    /// wxEVT_PAINT event handler for wxID_STATIC
    void OnPaint( wxPaintEvent& event );

////@end MainWindow event handler declarations

////@begin MainWindow member function declarations

    /// Returns the AUI manager object
    wxAuiManager& GetAuiManager() { return m_auiManager; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MainWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MainWindow member variables
    wxAuiManager m_auiManager;
    wxScrolledWindow* scrolledwindowOutput;
    wxBoxSizer* sizerOutput;
    wxBoxSizer* sizerOutputLabels;
    wxStaticText* staticText1;
    wxStaticText* staticText2;
    wxStaticText* staticText3;
    wxBoxSizer* sizerOutputImages;
    wxStaticBitmap* staticBitmap1;
    wxStaticBitmap* staticBitmap2;
    wxStaticBitmap* staticBitmap3;
////@end MainWindow member variables

	BlendingModes *_blendingModes;
	std::map<int, BITMAP *> _cachedOutputBitmaps;
    bool _isInitialized;
};

#endif
    // _MAINWINDOW_H_

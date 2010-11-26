/////////////////////////////////////////////////////////////////////////////
// Name:        Application.cpp
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     26/11/2010 13:13:19
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

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

#include "Application.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( Application )
////@end implement app


/*
 * Application type definition
 */

IMPLEMENT_CLASS( Application, wxApp )


/*
 * Application event table definition
 */

BEGIN_EVENT_TABLE( Application, wxApp )

////@begin Application event table entries
////@end Application event table entries

END_EVENT_TABLE()


/*
 * Constructor for Application
 */

Application::Application()
{
    Init();
}


/*
 * Member initialisation
 */

void Application::Init()
{
////@begin Application member initialisation
////@end Application member initialisation
}

/*
 * Initialisation for Application
 */

bool Application::OnInit()
{    
////@begin Application initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	MainWindow* mainWindow = new MainWindow( NULL );
	mainWindow->Show(true);
////@end Application initialisation

    return true;
}


/*
 * Cleanup for Application
 */

int Application::OnExit()
{    
////@begin Application cleanup
	return wxApp::OnExit();
////@end Application cleanup
}


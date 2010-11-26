/////////////////////////////////////////////////////////////////////////////
// Name:        Application.h
// Purpose:     
// Author:      Ray Burgemeestre
// Modified by: 
// Created:     26/11/2010 13:13:19
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _APPLICATION_H_
#define _APPLICATION_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "MainWindow.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * Application class declaration
 */

class Application: public wxApp
{    
    DECLARE_CLASS( Application )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    Application();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin Application event handler declarations

////@end Application event handler declarations

////@begin Application member function declarations

////@end Application member function declarations

////@begin Application member variables
////@end Application member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(Application)
////@end declare app

#endif
    // _APPLICATION_H_

#include <iostream>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "mainframe.h"

class Minesweeper : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(Minesweeper);

bool Minesweeper::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}
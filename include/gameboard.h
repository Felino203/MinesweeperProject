#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class GameBoard : public wxPanel
{

public:
    GameBoard(wxFrame *parent);

    void paintNow();

    DECLARE_EVENT_TABLE()

private:
    void OnPaint(wxPaintEvent &evt);
    void render(wxDC &dc);

    wxFrame *m_parent = nullptr;
};

#endif
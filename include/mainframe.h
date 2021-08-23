#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class GameBoard;

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void createMenuBar();
    void createGameBoard(int height, int width);

    void onBeginner(wxCommandEvent &event);
    void onIntermediate(wxCommandEvent &event);
    void onExpert(wxCommandEvent &event);
    void onCustom(wxCommandEvent &event);
    void onNew(wxCommandEvent &event);
    void onExit(wxCommandEvent &event);
    void onAbout(wxCommandEvent &event);

    void OnPaint(wxPaintEvent &e);

    void clearChecks();

    wxSizer *sizer = nullptr;
    GameBoard *gameBoard = nullptr;
    wxMenu *menuGame = nullptr;
};

enum EVENT_VALS
{
    ID_NEW = 1,
    ID_BEGINNER = 2,
    ID_INTERMEDIATE = 3,
    ID_EXPERT = 4,
    ID_CUSTOM = 5,
};

#endif
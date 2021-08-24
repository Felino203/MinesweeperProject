#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <unordered_map>
#include <string>

class Minefield;

class GameBoard : public wxPanel
{

public:
    GameBoard(wxFrame *parent, int nbRows, int nbColumns);

    void paintNow();
    void drawSingleTile(int tileNb, int tileVal);
    void drawSingleTile(wxDC &dc, int tileNb, int tileVal);
    void updateDimensions();

    DECLARE_EVENT_TABLE()

private:
    void OnPaint(wxPaintEvent &evt);
    void OnSize(wxSizeEvent &event);
    void prepDC(wxDC &dc);
    void drawBoard(wxDC &dc);
    float getScaleFactor();

    int mouseToTile();
    void mouseDown(wxMouseEvent &event);

    int rows = -1;
    int columns = -1;

    int xPos = -1;
    int yPos = -1;

    int windowHeight = -1;
    int windowWidth = -1;

    int boardHeight = -1;
    int boardWidth = -1;

    const int tileWidth = 128;

    wxFrame *m_parent = nullptr;
    Minefield *minefield = nullptr;
    std::unordered_map<int, wxBitmap> spriteMap = {{0, wxBitmap("assets\\blank_case.png", wxBITMAP_TYPE_PNG)},
                                                   {1, wxBitmap("assets\\1_case.png", wxBITMAP_TYPE_PNG)},
                                                   {2, wxBitmap("assets\\2_case.png", wxBITMAP_TYPE_PNG)},
                                                   {3, wxBitmap("assets\\3_case.png", wxBITMAP_TYPE_PNG)},
                                                   {4, wxBitmap("assets\\4_case.png", wxBITMAP_TYPE_PNG)},
                                                   {5, wxBitmap("assets\\5_case.png", wxBITMAP_TYPE_PNG)},
                                                   {6, wxBitmap("assets\\6_case.png", wxBITMAP_TYPE_PNG)},
                                                   {7, wxBitmap("assets\\7_case.png", wxBITMAP_TYPE_PNG)},
                                                   {8, wxBitmap("assets\\8_case.png", wxBITMAP_TYPE_PNG)},
                                                   {-1, wxBitmap("assets\\mine_case.png", wxBITMAP_TYPE_PNG)},
                                                   {-2, wxBitmap("assets\\flag_case.png", wxBITMAP_TYPE_PNG)},
                                                   {-3, wxBitmap("assets\\dugblank_case.png", wxBITMAP_TYPE_PNG)},
                                                   {-4, wxBitmap("assets\\redmine_case.png", wxBITMAP_TYPE_PNG)}};
};

#endif
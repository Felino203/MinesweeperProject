#include "mainframe.h"

#include <iostream>
#include "minefield.h"
#include "tile.h"
#include "gameboard.h"

using namespace std;

void clearConsole()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void executeGame()
{
    clearConsole();

    Minefield minefield = Minefield(16, 30);
    minefield.generateMines(99);
    minefield.generateValues();
    minefield.printField();

    cout << "test";
}

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Minesweeper")
{
    createMenuBar();
    CreateStatusBar();
}

void MainFrame::createMenuBar()
{
    menuGame = new wxMenu;
    menuGame->Append(ID_NEW, "New \tF2", "Create a new game", wxITEM_NORMAL);
    menuGame->AppendSeparator();
    menuGame->Append(ID_BEGINNER, "Beginner", "", wxITEM_CHECK);
    menuGame->Append(ID_INTERMEDIATE, "Intermediate", "", wxITEM_CHECK);
    menuGame->Append(ID_EXPERT, "Expert", "", wxITEM_CHECK);
    menuGame->Append(ID_CUSTOM, "Custom", "", wxITEM_CHECK);
    menuGame->AppendSeparator();
    menuGame->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuGame, "&Game");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainFrame::onNew, this, ID_NEW);
    Bind(wxEVT_MENU, &MainFrame::onBeginner, this, ID_BEGINNER);
    Bind(wxEVT_MENU, &MainFrame::onIntermediate, this, ID_INTERMEDIATE);
    Bind(wxEVT_MENU, &MainFrame::onExpert, this, ID_EXPERT);
    Bind(wxEVT_MENU, &MainFrame::onCustom, this, ID_CUSTOM);
    Bind(wxEVT_MENU, &MainFrame::onAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);
}

void MainFrame::createGameBoard(int rows, int columns)
{
    wxBoxSizer *sizerH = new wxBoxSizer(wxHORIZONTAL);

    gameBoard = new GameBoard(this);

    this->SetSizer(sizerH);

    sizerH->Add(gameBoard, 0, wxSHAPED || wxALIGN_CENTER);

    gameBoard->paintNow();
    this->Refresh();
    this->Update();

    // wxGridSizer *gridSizer = new wxGridSizer(rows, columns, 1, 1);
    // this->SetSizer(gridSizer);

    // for (int i = 0; i < rows * columns; i++)
    // {
    //     wxImage *tileImg = new wxImage();
    //     tileImg->LoadFile("assets\\blank_case.png", wxBITMAP_TYPE_PNG);

    //     wxStaticBitmap *tile = new wxStaticBitmap(this, i + 20, wxBitmap(*tileImg));

    //     gridSizer->Add(tile);

    //     //wxBitmap *tileBitmap = new wxBitmap("assets\\blank_case.png", wxBITMAP_TYPE_PNG);
    //     //tileBitmap->SetHeight(32);
    //     //tileBitmap->SetWidth(32);
    //     //gridSizer->Add(new wxStaticBitmap(this, i + 20, *tileBitmap));
    // }
}

void MainFrame::OnPaint(wxPaintEvent &e)
{

    // wxImage *tileImg = new wxImage();
    // tileImg->LoadFile("assets\\blank_case.png", wxBITMAP_TYPE_PNG);

    // wxBitmap tileBmp = wxBitmap(*tileImg);
    // wxPaintDC dc(this);

    // float fWScale = 1.0f; // horizontal scaling factor
    // float fHScale = 1.0f; // vertical scaling factor
    // int iImageH = -1;     // the bitmap's height
    // int iImageW = -1;     // the bitmap's width
    // int iThisH = -1;      // the panel's height
    // int iThisW = -1;      // the panel's width

    // // how is the bitmap's actual size?
    // iImageH = tileBmp.GetHeight();
    // iImageW = tileBmp.GetWidth();

    // //Panel size
    // GetSize(&iThisW, &iThisH);

    // // no division by zero !
    // if ((iImageH > 0) && (iImageW > 0))
    // {
    //     // calculate the scaling factor for the 2 dimensions
    //     fHScale = (float)iThisH / (float)iImageH;
    //     fWScale = (float)iThisW / (float)iImageW;

    //     // always take the smaller scaling factor,
    //     // so that the bitmap will always fit into the panel's paintable area
    //     if (fHScale < fWScale)
    //     {
    //         fWScale = fHScale;
    //     }
    //     else
    //     {
    //         fHScale = fWScale;
    //     }
    // }

    // dc.SetUserScale(fHScale, fWScale);
    // dc.DrawBitmap(tileBmp, 0, 0, false);
}

void MainFrame::clearChecks()
{
    for (auto item : menuGame->GetMenuItems())
    {
        if (item->IsCheck())
            item->Check(false);
    }
}

void MainFrame::onExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::onAbout(wxCommandEvent &event)
{
    wxMessageBox("How about you google this: HOW DO I PLAY MINESWEEPER??? You clown.",
                 "You dont know how to play?", wxOK | wxICON_INFORMATION);
}

void MainFrame::onNew(wxCommandEvent &event)
{
    createGameBoard(3, 3);
    //executeGame();
}

void MainFrame::onBeginner(wxCommandEvent &event)
{
    clearChecks();
    menuGame->Check(ID_BEGINNER, true);
}

void MainFrame::onIntermediate(wxCommandEvent &event)
{
    clearChecks();
    menuGame->Check(ID_INTERMEDIATE, true);
}

void MainFrame::onExpert(wxCommandEvent &event)
{
    clearChecks();
    menuGame->Check(ID_EXPERT, true);
}

void MainFrame::onCustom(wxCommandEvent &event)
{
    clearChecks();
    menuGame->Check(ID_CUSTOM, true);
}
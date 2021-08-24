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
    minefield.displayField();

    cout << "test";
}

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Minesweeper")
{
    SetSize(400, 100, 400, 300);
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
    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

    this->SetSizer(mainSizer);

    if (gameBoard != nullptr)
        gameBoard->Destroy();
    gameBoard = new GameBoard(this, 20, 25);

    mainSizer->Add(gameBoard, 1, 0);

    gameBoard->paintNow();
    this->Refresh();
    this->Update();
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
    wxMessageBox("How about you google this:\nHOW DO I PLAY MINESWEEPER??? \n\nYou are a clown.",
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
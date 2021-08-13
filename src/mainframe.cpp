#include "mainframe.h"

#include <iostream>
#include "minefield.h"
#include "tile.h"

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
    wxMenu *menuGame = new wxMenu;
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

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MainFrame::OnNew, this, ID_NEW);
    Bind(wxEVT_MENU, &MainFrame::OnBeginner, this, ID_BEGINNER);
    Bind(wxEVT_MENU, &MainFrame::OnIntermediate, this, ID_INTERMEDIATE);
    Bind(wxEVT_MENU, &MainFrame::OnExpert, this, ID_EXPERT);
    Bind(wxEVT_MENU, &MainFrame::OnCustom, this, ID_CUSTOM);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

    executeGame();
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnNew(wxCommandEvent &event) {}

void MainFrame::OnBeginner(wxCommandEvent &event) {}

void MainFrame::OnIntermediate(wxCommandEvent &event) {}

void MainFrame::OnExpert(wxCommandEvent &event) {}

void MainFrame::OnCustom(wxCommandEvent &event) {}
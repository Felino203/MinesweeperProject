#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnBeginner(wxCommandEvent &event);
    void OnIntermediate(wxCommandEvent &event);
    void OnExpert(wxCommandEvent &event);
    void OnCustom(wxCommandEvent &event);
    void OnNew(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
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
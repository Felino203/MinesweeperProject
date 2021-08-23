#include "gameboard.h"

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

BEGIN_EVENT_TABLE(GameBoard, wxPanel)
EVT_PAINT(GameBoard::OnPaint)
END_EVENT_TABLE()

GameBoard::GameBoard(wxFrame *parent) : m_parent(parent), wxPanel(parent)
{
    this->SetSize(200, 200);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void GameBoard::OnPaint(wxPaintEvent &evt)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    render(dc);
}

void GameBoard::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void GameBoard::render(wxDC &dc)
{
    dc.Clear();

    wxImage *tileImg = new wxImage();
    tileImg->LoadFile("assets\\blank_case.png", wxBITMAP_TYPE_PNG);

    wxBitmap tileBmp = wxBitmap(*tileImg);

    float fWScale = 1.0f; // horizontal scaling factor
    float fHScale = 1.0f; // vertical scaling factor
    int iImageH = -1;     // the bitmap's height
    int iImageW = -1;     // the bitmap's width
    int iThisH = -1;      // the panel's height
    int iThisW = -1;      // the panel's width

    // how is the bitmap's actual size?
    iImageH = tileBmp.GetHeight();
    iImageW = tileBmp.GetWidth();

    //Panel size
    GetSize(&iThisW, &iThisH);

    int rows = 10;
    int columns = 10;

    // no division by zero !
    if ((iImageH > 0) && (iImageW > 0))
    {
        // calculate the scaling factor for the 2 dimensions
        fHScale = (float)iThisH / (float)iImageH / (float)(rows);
        fWScale = (float)iThisW / (float)iImageW / (float)(columns);

        // always take the smaller scaling factor,
        // so that the bitmap will always fit into the panel's paintable area
        if (fHScale < fWScale)
        {
            fWScale = fHScale;
        }
        else
        {
            fHScale = fWScale;
        }
    }

    dc.Clear();
    dc.SetUserScale(fHScale, fWScale);
    int j = 0;
    for (int i = 0; j < columns; i++)
    {
        dc.SetUserScale(fHScale, fWScale);
        dc.DrawBitmap(tileBmp, i * iImageH, j * iImageW, false);
        if (i >= columns - 1)
        {
            j++;
            i = -1;
        }
    }
}
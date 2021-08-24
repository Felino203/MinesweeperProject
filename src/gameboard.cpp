#include "gameboard.h"
#include "minefield.h"
#include "tile.h"
#include <cmath>

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

BEGIN_EVENT_TABLE(GameBoard, wxPanel)
EVT_PAINT(GameBoard::OnPaint)
EVT_SIZE(GameBoard::OnSize)
EVT_LEFT_DOWN(GameBoard::mouseDown)
END_EVENT_TABLE()

GameBoard::GameBoard(wxFrame *parent, int nbRows, int nbColumns) : m_parent(parent),
                                                                   rows(nbRows),
                                                                   columns(nbColumns),
                                                                   wxPanel(parent)
{
    minefield = new Minefield(columns, rows);
    boardWidth = tileWidth * columns;
    boardHeight = tileWidth * rows;
    updateDimensions();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void GameBoard::updateDimensions()
{
    m_parent->GetClientSize(&windowWidth, &windowHeight);

    xPos = abs(windowWidth - windowHeight) / 2;
    yPos = 0;
    if (windowWidth <= windowHeight)
    {
        int temp = xPos;
        xPos = yPos;
        yPos = temp;
    }

    if (windowHeight < windowWidth)
        windowWidth = windowHeight;
    else
        windowHeight = windowWidth;
    this->SetSize(xPos, yPos, windowHeight, windowWidth);
}

void GameBoard::OnSize(wxSizeEvent &event)
{
    updateDimensions();
    paintNow();
    event.Skip();
}

void GameBoard::OnPaint(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    prepDC(dc);
    drawBoard(dc);
    event.Skip();
}

void GameBoard::paintNow()
{
    wxClientDC dc(this);
    prepDC(dc);
    drawBoard(dc);
}

float GameBoard::getScaleFactor()
{
    float fWScale = 1.0f; // horizontal scaling factor
    float fHScale = 1.0f; // vertical scaling factor

    // calculate the scaling factor for the 2 dimensions
    fHScale = (float)windowHeight / (float)tileWidth / (float)(rows);
    fWScale = (float)windowWidth / (float)tileWidth / (float)(columns);

    // always take the smaller scaling factor,
    // so that the bitmap will always fit into the panel's paintable area
    if (fHScale < fWScale)
        fWScale = fHScale;
    else
        fHScale = fWScale;

    return fHScale;
}

void GameBoard::prepDC(wxDC &dc)
{
    float fHScale = getScaleFactor();
    dc.SetUserScale(fHScale, fHScale);
}

void GameBoard::drawBoard(wxDC &dc)
{
    dc.Clear();
    for (int i = 0; i < columns * rows; i++)
    {
        drawSingleTile(dc, i, minefield->getField()[i]->getTileValue());
    }
}

void GameBoard::drawSingleTile(int tileNb, int tileVal)
{
    wxClientDC dc(this);
    prepDC(dc);
    drawSingleTile(dc, tileNb, tileVal);
}

void GameBoard::drawSingleTile(wxDC &dc, int tileNb, int tileVal)
{
    int x = tileNb / columns;
    int y = tileNb % columns;
    dc.DrawBitmap(spriteMap[tileVal], x * tileWidth, y * tileWidth, false);
}

void GameBoard::mouseDown(wxMouseEvent &event)
{
    while (wxGetMouseState().LeftIsDown())
    {
        int tileNb = mouseToTile();
        drawSingleTile(tileNb, -3);
        for (int direction : {1, -1, columns, -columns, -columns - 1, -columns + 1, columns + 1, columns - 1})
            drawSingleTile(tileNb + direction, 0);
    }
    event.Skip();
}

int GameBoard::mouseToTile()
{
    int mouseX;
    int mouseY;
    float fScale = getScaleFactor();
    wxGetMousePosition(&mouseX, &mouseY);
    ScreenToClient(&mouseX, &mouseY);
    return (floor((float)mouseX / (float)tileWidth / fScale) * columns + floor((float)mouseY / (float)tileWidth / fScale));
}
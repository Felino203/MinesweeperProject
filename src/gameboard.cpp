#include "gameboard.h"
#include "minefield.h"
#include "tile.h"
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

BEGIN_EVENT_TABLE(GameBoard, wxPanel)
EVT_PAINT(GameBoard::OnPaint)
EVT_SIZE(GameBoard::OnSize)
EVT_RIGHT_DOWN(GameBoard::rightMouseDown)
EVT_LEFT_DOWN(GameBoard::leftMouseDown)
EVT_LEFT_UP(GameBoard::leftMouseRelease)
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
    minefield->generateMines(80);
}

void GameBoard::updateDimensions()
{
    m_parent->GetClientSize(&windowWidth, &windowHeight);

    float fScale = getScaleFactor();

    boardWidth = ((float)tileWidth * (float)fScale * (float)columns);
    boardHeight = ((float)tileWidth * (float)fScale * (float)rows);

    if (boardWidth <= windowWidth && boardHeight >= windowHeight)
    {
        xPos = abs(boardWidth - windowWidth) / 2;
        yPos = 0;
    }
    else
    {
        xPos = 0;
        yPos = abs(boardHeight - windowHeight) / 2;
    }

    this->SetSize(xPos, yPos, boardWidth, boardHeight);
}

void GameBoard::OnSize(wxSizeEvent &event)
{
    if (rows * columns > 900)
    {
        m_parent->SetSize(1000, 800);
    }
    updateDimensions();
    Refresh();
    Update();
}

void GameBoard::OnPaint(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    prepDC(dc);
    drawBoard(dc);
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

    return std::min(fHScale, fWScale);
}

void GameBoard::prepDC(wxDC &dc)
{
    float fScale = getScaleFactor();
    dc.SetUserScale(fScale, fScale);
}

void GameBoard::drawBoard(wxDC &dc)
{
    dc.Clear();
    Tile *curTile = nullptr;
    for (int i = 0; i < columns * rows; i++)
    {
        curTile = minefield->getField()[i].get();
        if (!curTile->isCovered())
        {
            if (curTile->getTileValue() == 0)
                drawSingleTile(dc, i, -3);
            else
                drawSingleTile(dc, i, curTile->getTileValue());
        }
        else if (curTile->isFlagged())
            drawSingleTile(dc, i, -2);
        else
            drawSingleTile(dc, i, 0);
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
    dc.DrawBitmap(spriteMap[tileVal], y * tileWidth, x * tileWidth, false);
}

void GameBoard::rightMouseDown(wxMouseEvent &event)
{
    int tileNb = mouseToTile();
    if (tileNb != -1)
    {
        if (minefield->getField()[tileNb]->isCovered())
        {
            minefield->getField()[tileNb]->setFlagged(!minefield->getField()[tileNb]->isFlagged());
            drawSingleTile(tileNb, -(minefield->getField()[tileNb]->isFlagged() * 2));
        }
    }
    event.Skip();
}

void GameBoard::leftMouseDown(wxMouseEvent &event)
{
    int lastTileNb = -1;
    while (wxGetMouseState().LeftIsDown())
    {
        int tileNb = mouseToTile();
        if (tileNb == -1)
        {
            drawSingleTile(lastTileNb, 0);
        }
        else
        {
            if (minefield->getField()[tileNb]->isCovered() && !minefield->getField()[tileNb]->isFlagged())
            {
                if (lastTileNb != -1 && lastTileNb != tileNb && minefield->getField()[lastTileNb]->isCovered() && !minefield->getField()[lastTileNb]->isFlagged())
                    drawSingleTile(lastTileNb, 0);
                drawSingleTile(tileNb, -3);
                lastTileNb = tileNb;
            }
            if (lastTileNb != -1 && lastTileNb != tileNb && minefield->getField()[lastTileNb]->isCovered() && !minefield->getField()[lastTileNb]->isFlagged())
                drawSingleTile(lastTileNb, 0);
        }
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
    int tileNb = floor((float)mouseX / (float)tileWidth / fScale) + floor((float)mouseY / (float)tileWidth / fScale) * columns;
    if (tileNb < 0 || tileNb > rows * columns || mouseX < 0 || mouseY < 0 || mouseX > boardWidth || mouseY > boardHeight)
        tileNb = -1;
    return tileNb;
}

void GameBoard::leftMouseRelease(wxMouseEvent &event)
{
    int tileNb = mouseToTile();
    if (tileNb != -1)
    {
        drawSingleTile(tileNb, minefield->getField()[tileNb]->getTileValue());
        minefield->getField()[tileNb]->setUncovered();
        if (minefield->getField()[tileNb]->getTileValue() == 0)
        {
            set<int> tilesToUncover;
            floodSearch(tilesToUncover, {1, -1, columns, -columns, -columns - 1, -columns + 1, columns + 1, columns - 1}, {0, 1, 2, 3}, 0, tileNb);
            for (int tilePos : tilesToUncover)
            {
                drawSingleTile(tilePos, -3);
                minefield->getField()[tilePos]->setUncovered();
                if (minefield->getField()[tilePos]->getTileValue() != 0)
                    drawSingleTile(tilePos, minefield->getField()[tilePos]->getTileValue());
            }
        }
    }
    event.Skip();
}

void GameBoard::floodSearch(set<int> &items, set<int> directions, set<int> valuesSearched, int floodValue, int curPosition)
{
    for (auto direction : directions)
    {
        int neighborPos = curPosition + direction;
        if (neighborPos >= 0 && neighborPos < rows * columns && items.find(neighborPos) == items.end() && !(abs((neighborPos % columns) - (curPosition % columns)) > 1))
        {
            int neighborValue = minefield->getField()[neighborPos]->getTileValue();
            if (valuesSearched.find(neighborValue) != valuesSearched.end())
            {
                items.insert(neighborPos);
                if (neighborValue == floodValue)
                    floodSearch(items, directions, valuesSearched, 0, neighborPos);
            }
        }
    }
}
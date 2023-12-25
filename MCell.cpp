#include "MCell.h"
#include "MWidget.h"

MCell::MCell(MWidget *parent)
	: QPushButton(parent)
{
	Parent = parent;
	Visuable = new bool(true);
	IfLine = new bool(true);
	IfFill = new bool(false);
}

MCell::~MCell()
{}

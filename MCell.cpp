#include "MCell.h"
#include "MWidget.h"

MCell::MCell(MWidget *parent)
	: QPushButton(parent)
{
	Parent = parent;
}

MCell::~MCell()
{}

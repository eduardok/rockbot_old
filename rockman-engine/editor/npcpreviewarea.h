#ifndef NPCPREVIEWAREA_H
#define NPCPREVIEWAREA_H

#include <QWidget>
#include <QPainter>
#include <stdio.h>
#include <QMouseEvent>
#include "mediator.h"


extern Mediator *dataExchanger;

class npcPreviewArea : public QWidget
{
  Q_OBJECT

public:
  // methods
  npcPreviewArea(QWidget *parent = 0);

  // variables
  //QWidget *myParent;
private:
  int editor_selectedTileX;
  int editor_selectedTileY;
  int image_w;
  int image_h;

protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent * event);

  QWidget *myParent;

signals:
	 void clickedIn();

public slots:
   //void changeTile();
};


#endif // NPCPREVIEWAREA_H

#include "npcpreviewarea.h"

npcPreviewArea::npcPreviewArea(QWidget *parent) : QWidget(parent) {
    myParent = parent;
	editor_selectedTileX = 0;
	editor_selectedTileY = 0;
	parent->resize(QSize(999, 200));
	this->show();
}

void npcPreviewArea::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	QLineF *line;
	QRectF *target, *source;
	int i;
	//printf("DEBUG - EditorArea.paintEvent\n");
	// draw the picked tile in the tileset
	//printf("DEBUG.npcPreviewArea::paintEvent - filename: %s\n", dataExchanger->addNpcFilename);
	QPixmap image(dataExchanger->addNpcFilename);
	if (image.isNull()) {
		//printf("npcPreviewArea::paintEvent - Could not load image file '%s'\n", dataExchanger->addNpcFilename);
		return;
	}
	image_w = image.width();
	image_h = image.height();
	image = image.scaled(image.width()*2, image.height()*2);
	this->resize(1500, 999);
	myParent->resize(1500, 999);
	myParent->setGeometry(0, 0, 1000, 1000);
	myParent->adjustSize();
	target = new QRectF(QPoint(0, 0), QSize(image.width(), image.height()));
	source = new QRectF(QPoint(0, 0), QSize(image.width(), image.height()));
	painter.drawPixmap(*target, image, *source);

	//printf("npcPreviewArea::paintEvent - gSize: %d\n", dataExchanger->npcGraphicSize_w);

   painter.setPen(QColor(0, 120, 0));
   for (i=1; i<=this->width(); i=i+dataExchanger->npcGraphicSize_w*2) {
	  // linhas verticais
	  line = new QLineF(i, 0, i, this->height());
	  painter.drawLine(*line);
   }
   for (i=1; i<this->height(); i=i+dataExchanger->npcGraphicSize_h*2) {
	  // linhas horizontais
	  line = new QLineF(0, i, this->width(), i);
	  painter.drawLine(*line);
   }

   int posX = editor_selectedTileX*dataExchanger->npcGraphicSize_w*2;
   int posY = editor_selectedTileY*dataExchanger->npcGraphicSize_h*2;
   // paint the selected frame
   painter.setPen(QColor(255, 0, 0));
   line = new QLineF(posX, posY, posX+dataExchanger->npcGraphicSize_w*2, posY);
   painter.drawLine(*line);
   line = new QLineF(posX, posY, posX, posY+dataExchanger->npcGraphicSize_h*2);
   painter.drawLine(*line);
   line = new QLineF(posX, posY+dataExchanger->npcGraphicSize_h*2, posX+dataExchanger->npcGraphicSize_w*2, posY+dataExchanger->npcGraphicSize_h*2);
   painter.drawLine(*line);
   line = new QLineF(posX+dataExchanger->npcGraphicSize_w*2, posY+dataExchanger->npcGraphicSize_h*2, posX+dataExchanger->npcGraphicSize_w*2, posY);
   painter.drawLine(*line);
}


void npcPreviewArea::mousePressEvent(QMouseEvent *event) {
	printf(">> INSIDE npcPreviewArea::mousePressEvent, editMode: %d, editTool: %d\n", dataExchanger->editMode, dataExchanger->editTool);

	QPoint pnt = event->pos();
	// checks if click was inside the image
	if (pnt.x() <= image_w*2 && pnt.y() <= image_h*2) {
		editor_selectedTileX = pnt.x()/dataExchanger->npcGraphicSize_w/2;
		editor_selectedTileY = pnt.y()/dataExchanger->npcGraphicSize_h/2;
		printf(">> npcPreviewArea::mousePressEvent - x: %d, y: %d\n", editor_selectedTileX, editor_selectedTileY);
		dataExchanger->setPalleteX(editor_selectedTileX);
		dataExchanger->setPalleteY(editor_selectedTileY);
		emit clickedIn();
		repaint();
	}
}


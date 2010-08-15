#include <QWidget>
#include <QShortcut>
#include <QPainter>
#include <QTimer>
#include <QScrollArea>
#include <QMessageBox>
#include <QColor>
#include <QMouseEvent>
#include "mediator.h"

#ifndef EDITORTILEPALLETE
    #include "editortilepallete.h"
#endif

#ifndef FILE_GAME
	#include "format/file_game.h"
#endif

extern int palleteX;
extern int palleteY;
extern Mediator *dataExchanger;


struct pointElement{
   int palleteX, palleteY, type;
};

class EditorArea : public QWidget
{
  Q_OBJECT

public:
  // methods
  EditorArea(QWidget *parent = 0);
  void setInfoPalette(EditorTilePallete *temp_pallete);

  // variables
  QWidget *myParent;

protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent * event);
  void mouseMoveEvent(QMouseEvent *event);
  int temp;
  int editor_selectedTileX, editor_selectedTileY;
  EditorTilePallete *my_pallete;
  void fill_area();

  int map_backup_n;

//signals:
//     void save();

public slots:
   void changeTile();
   //void saveMap();
   void saveGame(int game_n);
   void saveMap(int game_n, int map_n);
   //void loadMap();
   void addNpcToMap(int, int);
   void addObjectToMap(int, int);
};

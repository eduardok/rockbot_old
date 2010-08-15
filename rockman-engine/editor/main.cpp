#include <QtGui/QApplication>
#include <dirent.h>
#include "mediator.h"

int palleteX=0;
int palleteY=0;
Mediator *dataExchanger = new Mediator();

#include "format/file_game.h"
//#include "format/file_stage.h"
#include "editortilepallete.h"
#include "editorarea.h"
#include "mainwindow.h"

struct file_map map;
struct file_game game;
char FILEPATH[255];


int main(int argc, char *argv[])
{
	dataExchanger->initGameVar();
    QApplication a(argc, argv);
	strncpy (FILEPATH, argv[0], strlen(argv[0])-7);
    MainWindow w;
	w.resize(1024, 680);
    w.show();
    return a.exec();
}

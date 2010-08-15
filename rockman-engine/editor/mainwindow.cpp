#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defines.h"
#include "addwizard.h"
#include "dialognpcedit.h"
#include "dialogobjectedit.h"
#include "loadgamepicker.h"
#include <QStandardItemModel>
#include <QListView>
#include <QList>
#include <QListWidgetItem>

extern Mediator *dataExchanger;
extern char FILEPATH[255];


void MainWindow::fillMapList() {
	char buffer[255];
	int i, n_game, max;

	max = ui->mapListCombo->count();
	for (i=0; i<max; i++) {
		ui->mapListCombo->removeItem(0);
	}
	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(buffer, "%s/data/game/game_%s/", FILEPATH, dataExchanger->centNumber);
	n_game = dataExchanger->freeSlot(buffer, "map");
	for (i=1; i<n_game; i++) {
		dataExchanger->centNumberFormat(i);
		sprintf(buffer, "%s.map", dataExchanger->centNumber);
		ui->mapListCombo->addItem(buffer);
	}
}


void MainWindow::fillNpcList() {
	char buffer[255], directory[255], filename[255];
	int i, n_game, max;
	QListWidgetItem* item;
	QListWidgetItem* item_to_del;
	FILE *fp;
	struct file_npc temp_npc;

	max = ui->listWidget->count();
	// remove previous ones
	for (i=0; i<max; i++) {
		//printf(">>> Removing item %d from list, count: %d\n", i, ui->listWidget->count());
		item_to_del = ui->listWidget->takeItem(0);
		delete item_to_del;
	}

	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(directory, "%s/data/game/game_%s", FILEPATH, dataExchanger->centNumber);
	n_game = dataExchanger->freeSlot(directory, "npc");

	//printf("######### MainWindow::fillNpcList - buffer: %s, n_game: %d\n", directory, dataExchanger->currentGame);
	for (i=1; i<n_game; i++) {
		dataExchanger->centNumberFormat(i);
		sprintf(buffer, "%s/%s.npc", directory, dataExchanger->centNumber);
		//printf("######### MainWindow::fillNpcList - adding item: %s, count: %d\n", buffer, ui->listWidget->count());

		fp = fopen(buffer, "r");
		if (fp) {
			fread(&temp_npc, sizeof(file_npc), 1, fp);
			fclose(fp);
		} else {
			printf("DEBUG - no npc file, ignoring load.\n");
		}
		//printf("DEBUG.MainWindow::fillNpcList - adding %s\n", buffer);
		//ui->npcListCombo->addItem(buffer);
		item = new QListWidgetItem;
		item->setText(temp_npc.name);
		//printf(">> MainWindow::fillNpcList - name: '%s', hp: %d, filename: '%s'\n", temp_npc.name, temp_npc.hp.total, temp_npc.filename);
		sprintf(filename, "%s/data/images/sprites/enemies/%s", FILEPATH, temp_npc.filename);
		QPixmap image(filename);
		image = image.copy(0, 0, temp_npc.framesize_w, temp_npc.framesize_h);
		image = image.scaled(32, 32);
		item->setIcon(image);
		ui->listWidget->addItem(item);
	}
	ui->listWidget->update();
}


void MainWindow::fillObjList() {

	char buffer[255], directory[255], filename[255];
	int i, n_game, max;
	QListWidgetItem* item;
	QListWidgetItem* item_to_del;
	FILE *fp;
	struct struct_object temp_object;

	max = ui->objectListWidget->count();
	// remove previous ones
	for (i=0; i<max; i++) {
		item_to_del = ui->objectListWidget->takeItem(0);
		delete item_to_del;
	}

	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(directory, "%s/data/game/game_%s", FILEPATH, dataExchanger->centNumber);
	n_game = dataExchanger->freeSlot(directory, "obj");

	//printf("######### MainWindow::fillObjList - buffer: %s, n_game: %d\n", directory, dataExchanger->currentGame);
	for (i=1; i<n_game; i++) {
		dataExchanger->centNumberFormat(i);
		sprintf(buffer, "%s/%s.obj", directory, dataExchanger->centNumber);
		//printf("######### MainWindow::fillObjList - adding item: %s, count: %d\n", buffer, ui->objectListWidget->count());

		fp = fopen(buffer, "r");
		if (fp) {
			fread(&temp_object, sizeof(struct_object), 1, fp);
			fclose(fp);
		} else {
			printf("DEBUG - no object file, ignoring load.\n");
		}
		//printf("DEBUG.MainWindow::fillNpcList - adding %s\n", buffer);
		//ui->npcListCombo->addItem(buffer);
		item = new QListWidgetItem;
		item->setText(temp_object.name);
		sprintf(filename, "%s/data/images/sprites/objects/%s", FILEPATH, temp_object.filename);
		//printf(">> MainWindow::fillObjectList - name: '%s', filename: '%s'\n", temp_object.name, filename);
		QPixmap image(filename);
		if (!image) {
			printf("Error loading file '%s' into a QPixmap\n", filename);
		}
		image = image.copy(0, 0, temp_object.framesize_w, temp_object.framesize_h);
		image = image.scaled(32, 32);
		item->setIcon(image);
		ui->objectListWidget->addItem(item);
	}
	ui->objectListWidget->update();
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	QStandardItem* temp_game_item;
	QStandardItem* temp_map_item;
	QStandardItem* temp_sub_map_item;
	int n, n_game;
	char buffer[255];
	int i, j;

    ui->setupUi(this);
	dataExchanger->loadGame(1);
	fillMapList();
	fillNpcList();
	fillObjList();
	ui->editArea->repaint();
	QObject::connect(ui->pallete, SIGNAL(signalPalleteChanged()), ui->editArea, SLOT(repaint()));
    // add maps to the list
    model = new QStandardItemModel();

	QStandardItem* games = new QStandardItem("GAMES");

	sprintf(buffer, "%s/data/game/", FILEPATH);
	n = dataExchanger->freeSlot(buffer, "gme");
	for (i=1; i<n; i++) {
		dataExchanger->centNumberFormat(i);
		sprintf(buffer, "Game %s", dataExchanger->centNumber);
		temp_game_item = new QStandardItem(buffer);
		temp_game_item->setEditable(FALSE);
		games->appendRow(temp_game_item);


		sprintf(buffer, "%s/data/game/game_%s/", FILEPATH, dataExchanger->centNumber);
		if (!QDir(buffer).exists()) {
			//printf("WARNING: Creating '%s'' folder\n", buffer);
			QDir().mkdir(buffer);
		}
		n_game = dataExchanger->freeSlot(buffer, "map");
		temp_map_item = new QStandardItem("MAPS");
		temp_game_item->appendRow(temp_map_item);
		for (j=1; j<n_game; j++) {
			dataExchanger->centNumberFormat(j);
			sprintf(buffer, "%s.map", dataExchanger->centNumber);
			temp_sub_map_item = new QStandardItem(buffer);
			temp_map_item->appendRow(temp_sub_map_item);
			//QObject::connect(ui->pallete, SIGNAL(signalPalleteChanged()), ui->editArea, SLOT(repaint()));
		}

	}
    QStandardItem* npcs = new QStandardItem("NPCs");
    npcs->setEditable(FALSE);
    QStandardItem* npc1 = new QStandardItem("NPC 001");
    npc1->setEditable(FALSE);
    npcs->appendRow(npc1);

	model->appendRow(games);
    model->appendRow(npcs);
    //iStandardModel->appendRow(item2);
    model->setHeaderData(0, Qt::Horizontal, "Item List");
	//ui->mapList->setModel(model);
	//parent->restoreGeometry();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionSave_triggered()
{
	ui->editArea->saveGame(dataExchanger->currentGame);
}

void MainWindow::on_actionOpen_triggered()
{
	QDialog *open = new loadGamePicker;
	open->show();
	//dataExchanger->loadGame();
	//ui->editArea->repaint();
}

void MainWindow::on_pallete_signalPalleteChanged()
{
	printf("DEBUG on_pallete_signalPalleteChanged\n");
}


void MainWindow::on_addNpcButton_clicked()
{
	printf("DEBUG.MainWindow::on_addNpcButton_clicked - NpcAddNumber: '%d'\n", dataExchanger->NpcAddNumber);
	dataExchanger->editMode = EDITMODE_ADDNPC;
}





void MainWindow::on_actionNew_triggered()
{
	dataExchanger->createGame();
	ui->editArea->repaint();
}

void MainWindow::reloadComboItems(void) {
	printf(">>>>> MainWindow::reloadComboItems\n");
	fillMapList();
	fillNpcList();
	fillObjList();
}

// ------------------- EDIT BUTTONS --------------------- //



void MainWindow::on_actionLock_Edit_triggered()
{
	if (ui->actionLock_Edit->isChecked()) {
		ui->actionNormal_Edit->setChecked(FALSE);
		ui->actionEraser->setChecked(FALSE);
		ui->actionFill->setChecked(FALSE);
		ui->actionLink->setChecked(FALSE);
		ui->actionStairs->setChecked(FALSE);
		ui->toolBox->setCurrentWidget(ui->Terrain);
		dataExchanger->editTool = EDITMODE_LOCK;
	// to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
	} else {
		ui->actionLock_Edit->setChecked(TRUE);
	}
	ui->editArea->repaint();
}

void MainWindow::on_actionNormal_Edit_triggered()
{
	if (ui->actionNormal_Edit->isChecked()) {
		ui->actionLock_Edit->setChecked(FALSE);
		ui->actionEraser->setChecked(FALSE);
		ui->actionFill->setChecked(FALSE);
		ui->actionLink->setChecked(FALSE);
		ui->actionStairs->setChecked(FALSE);
		dataExchanger->editTool = EDITMODE_NORMAL;
	// to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
	} else {
		ui->actionNormal_Edit->setChecked(TRUE);
	}
	ui->editArea->repaint();
}

void MainWindow::on_actionEraser_triggered()
{
	if (ui->actionEraser->isChecked()) {
		ui->actionLock_Edit->setChecked(FALSE);
		ui->actionNormal_Edit->setChecked(FALSE);
		ui->actionFill->setChecked(FALSE);
		ui->actionLink->setChecked(FALSE);
		ui->actionStairs->setChecked(FALSE);
		dataExchanger->editTool = EDITMODE_ERASER;
	// to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
	} else {
		ui->actionEraser->setChecked(TRUE);
	}
}




void MainWindow::on_actionFill_triggered()
{
	if (ui->actionFill->isChecked()) {
		ui->actionLock_Edit->setChecked(FALSE);
		ui->actionNormal_Edit->setChecked(FALSE);
		ui->actionEraser->setChecked(FALSE);
		ui->actionLink->setChecked(FALSE);
		ui->actionStairs->setChecked(FALSE);
		dataExchanger->editTool = EDITMODE_FILL;
	// to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
	} else {
		ui->actionFill->setChecked(TRUE);
	}
}


void MainWindow::on_MainWindow_iconSizeChanged(QSize iconSize)
{
	saveGeometry();
}

void MainWindow::on_actionLink_triggered()
{
	ui->toolBox->setCurrentIndex(2);
	ui->editArea->saveMap(dataExchanger->currentGame, dataExchanger->currentMap);
	if (ui->actionLink->isChecked()) {
		ui->actionLock_Edit->setChecked(FALSE);
		ui->actionNormal_Edit->setChecked(FALSE);
		ui->actionEraser->setChecked(FALSE);
		ui->actionFill->setChecked(FALSE);
		ui->actionStairs->setChecked(FALSE);
                ui->actionAdd_Object->setChecked(FALSE);
		dataExchanger->editTool = EDITMODE_LINK;
		ui->editArea->repaint();
	// to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
	} else {
		ui->actionFill->setChecked(TRUE);
		ui->editArea->repaint();
	}
}


void MainWindow::on_actionStairs_triggered()
{
	if (ui->actionStairs->isChecked()) {
		ui->actionNormal_Edit->setChecked(FALSE);
		ui->actionEraser->setChecked(FALSE);
		ui->actionFill->setChecked(FALSE);
		ui->actionLock_Edit->setChecked(FALSE);
		ui->actionLink->setChecked(FALSE);
		ui->actionAdd_Object->setChecked(FALSE);
		dataExchanger->editTool = EDITMODE_STAIRS;
	// to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
	} else {
		ui->actionStairs->setChecked(TRUE);
	}
	ui->editArea->repaint();
}


void MainWindow::on_actionAdd_Object_triggered()
{
	ui->toolBox->setCurrentWidget(ui->page_objects);
    if (ui->actionAdd_Object->isChecked()) {
			ui->actionEdit_NPC->setChecked(FALSE);
			ui->actionNormal_Edit->setChecked(TRUE);
            ui->actionEraser->setChecked(FALSE);
            ui->actionFill->setChecked(FALSE);
            ui->actionLock_Edit->setChecked(FALSE);
            ui->actionLink->setChecked(FALSE);
            ui->actionAdd_Object->setChecked(TRUE);
			dataExchanger->editMode = EDITMODE_OBJECT;
			dataExchanger->editTool = EDITMODE_NORMAL;
    // to make things simpler, we do not allow "uncheck" of the tool, you must pick another one to uncheck
    } else {
            ui->actionAdd_Object->setChecked(TRUE);
    }
    ui->editArea->repaint();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
	dataExchanger->layerLevel = index+1;
	ui->editArea->repaint();
}

void MainWindow::on_actionEdit_NPC_triggered()
{
	ui->toolBox->setCurrentWidget(ui->page_npc);
	if (ui->actionEdit_Tileset->isChecked()) {
		ui->actionEdit_Tileset->setChecked(FALSE);
		ui->actionEdit_NPC->setChecked(TRUE);
		ui->actionAdd_Object->setChecked(FALSE);
	}
	ui->actionFill->setDisabled(TRUE);
	ui->actionLink->setDisabled(TRUE);
	ui->actionLock_Edit->setDisabled(TRUE);
	ui->actionStairs->setDisabled(TRUE);
	ui->toolBox->setCurrentIndex(1);
	dataExchanger->editMode = EDITMODE_NPC;
}

void MainWindow::on_actionEdit_Tileset_triggered()
{
	if (ui->actionEdit_NPC->isChecked()) {
		ui->actionEdit_NPC->setChecked(FALSE);
		ui->actionAdd_Object->setChecked(FALSE);
		ui->actionEdit_Tileset->setChecked(TRUE);
	}
	ui->actionFill->setDisabled(FALSE);
	ui->actionLink->setDisabled(FALSE);
	ui->actionLock_Edit->setDisabled(FALSE);
	ui->actionStairs->setDisabled(FALSE);
	ui->toolBox->setCurrentIndex(0);
	dataExchanger->editMode = EDITMODE_NORMAL;
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
	printf(">>>> MainWindow::on_listWidget_currentRowChanged, row: %d\n", currentRow);
	dataExchanger->selectedNPC = currentRow+1;
	ui->editNPCButton->setEnabled(TRUE);
}

void MainWindow::on_editNPCButton_clicked()
{
	dataExchanger->editModeNPC = 1;
	QDialog *npc_editor = new DialogNPCEdit;
	npc_editor->show();
	QObject::connect(npc_editor, SIGNAL(finishedNPCEditor()), this, SLOT(reloadComboItems()));
}

void MainWindow::on_newNPCButton_clicked()
{
	dataExchanger->editModeNPC = 0;
	QDialog *npc_editor = new DialogNPCEdit;
	npc_editor->show();
	QObject::connect(npc_editor, SIGNAL(finishedNPCEditor()), this, SLOT(reloadComboItems()));
}

void MainWindow::on_actionOne_triggered()
{
    dataExchanger->layerLevel = 1;
    ui->editArea->repaint();
}

void MainWindow::on_actionTwo_triggered()
{
    dataExchanger->layerLevel = 2;
    ui->editArea->repaint();
}

void MainWindow::on_actionThree_triggered()
{
    dataExchanger->layerLevel = 3;
    ui->editArea->repaint();
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    dataExchanger->object_type = index+3;
}



void MainWindow::on_mapListCombo_currentIndexChanged(int index)
{
	ui->editArea->saveMap(dataExchanger->currentGame, dataExchanger->currentMap);
	//printf("DEBUG - loading map %d\n", index+1);
	dataExchanger->loadMap(dataExchanger->currentGame, index+1);
	dataExchanger->currentMap = index+1;
	ui->editArea->repaint();
}

void MainWindow::on_editObjectButton_clicked()
{
	dataExchanger->editModeNPC = 1;
	QDialog *object_editor = new DialogObjectEdit ();
	object_editor->show();
	QObject::connect(object_editor, SIGNAL(finishedObjectEditor()), this, SLOT(reloadComboItems()));
}

void MainWindow::on_newObjectButton_clicked()
{
	dataExchanger->editModeNPC = 0;
	QDialog *object_editor = new DialogObjectEdit ();
	object_editor->show();
	QObject::connect(object_editor, SIGNAL(finishedObjectEditor()), this, SLOT(reloadComboItems()));
}

void MainWindow::on_objectListWidget_currentRowChanged(int currentRow)
{
	dataExchanger->selectedNPC = currentRow+1;
	printf(">>>> MainWindow::on_objectListWidget_currentRowChanged, row: %d, dataExchanger->selectedNPC: %d\n", currentRow, dataExchanger->selectedNPC);
	ui->editObjectButton->setEnabled(TRUE);
}

void MainWindow::on_toolBox_currentChanged(int index)
{
	dataExchanger->selectedNPC = -1;
}

void MainWindow::on_pushButton_clicked()
{
	dataExchanger->addMap();
	fillMapList();
}

void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
	dataExchanger->terrainType = currentRow+1;
}

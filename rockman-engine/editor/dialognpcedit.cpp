#include <stdio.h>
#include <QDir>
#include "dialognpcedit.h"
#include "ui_dialognpcedit.h"
#include "mediator.h"
#include "defines.h"
#include "format/file_npc.h"

extern char FILEPATH[255];

extern Mediator *dataExchanger;

DialogNPCEdit::DialogNPCEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNPCEdit)
{
    char filename[255];
    int n;

    ui->setupUi(this);
    ui->frameTypeCombo->addItem("NONE");
    ui->frameTypeCombo->addItem("ANIM_STAND");
    ui->frameTypeCombo->addItem("ANIM_WALK");
    ui->frameTypeCombo->addItem("ANIM_JUMP");
    ui->frameTypeCombo->addItem("ANIM_ATTACK");
    ui->frameTypeCombo->addItem("ANIM_TELEPORT");
    ui->frameTypeCombo->addItem("ANIM_JUMP_ATTACK");
    ui->frameTypeCombo->addItem("ANIM_WALK_ATTACK");
    ui->frameTypeCombo->addItem("ANIM_HIT");
    ui->frameTypeCombo->addItem("ANIM_STAIRS");
    ui->frameTypeCombo->addItem("ANIM_STAIRS_SEMI");
    ui->frameTypeCombo->addItem("ANIM_STAIRS_ATTACK");
    ui->frameTypeCombo->addItem("ANIM_STAIRS_MOVE");
    ui->frameTypeCombo->addItem("ANIM_THROW");
    ui->frameTypeCombo->addItem("ANIM_TURN");
    //ui->npcPreviewAreaWidget->
    fillNPCGraphicsList();
    printf("%%%% DialogNPCEdit::DialogNPCEdit - dataExchanger->selectedNPC: %d, editMode: %d\n", dataExchanger->selectedNPC, dataExchanger->editModeNPC);
    if (dataExchanger->editModeNPC == 1) {
            loadNPCData(dataExchanger->selectedNPC);
    } else {
            dataExchanger->centNumberFormat(dataExchanger->currentGame);
			sprintf(filename, "%s/data/game/game_%s/", FILEPATH, dataExchanger->centNumber);
            n = dataExchanger->freeSlot(filename, "npc");
            printf(">> DialogNPCEdit::DialogNPCEdit - New NPC dir: '%s', slot: %d\n", filename, n);
            dataExchanger->selectedNPC = n;
    }
    QObject::connect(ui->npcPreviewAreaWidget, SIGNAL(clickedIn()), this, SLOT(setNPCFrame()));
}




void DialogNPCEdit::loadNPCData(int npc_n) {
	FILE *fp;
	struct file_npc temp_npc;
	char buffer[255], directory[255];
	int i;

	printf("Trying to load npc '%d' data\n", npc_n);
	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(directory, "%s/data/game/game_%s", FILEPATH, dataExchanger->centNumber);
	dataExchanger->centNumberFormat(npc_n);
	sprintf(buffer, "%s/%s.npc", directory, dataExchanger->centNumber);
	printf(">> MainWindow::fillNpcList - buffer: %s\n", buffer);

	fp = fopen(buffer, "rb");
	if (fp) {
		fread(&temp_npc, sizeof(file_npc), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no npc file, ignoring load.\n");
	}
	ui->NpcName->setText(temp_npc.name);
	ui->NpcHP->setValue(temp_npc.hp.total);
	ui->npcGraphicSizeSpin_w->setValue(temp_npc.framesize_w);
	ui->npcGraphicSizeSpin_h->setValue(temp_npc.framesize_h);
	dataExchanger->npcGraphicSize_w = temp_npc.framesize_w;
	dataExchanger->npcGraphicSize_h = temp_npc.framesize_h;
	for (i=0; i<ui->npcListCombobox->count(); i++) {
		if (ui->npcListCombobox->itemText(i) == QString(temp_npc.filename)) {
			ui->npcListCombobox->setCurrentIndex(i);
			break;
		}
	}
	for (i=0; i<NPC_FRAME_NUMBER; i++) {
		dataExchanger->frameset[i] = temp_npc.frameset[i];
		dataExchanger->frameset_time[i] = temp_npc.frameset_time[i];
	}
	if (temp_npc.can_shoot == 1) {
		ui->checkBoxCanShoot->setChecked(true);
	}
	if (temp_npc.is_boss == 1) {
		ui->isBossCheckbox->setChecked(true);
	}
	ui->comboBoxShieldType->setCurrentIndex(temp_npc.have_shield);
	ui->comboBoxIA->setCurrentIndex(temp_npc.IA);
}



void DialogNPCEdit::saveNPCData(int npc_n) {
	FILE *fp;
	struct file_npc temp_npc;
	char buffer[255], directory[255];
	int i;

	strcpy (temp_npc.name, ui->NpcName->text().toLatin1());

	temp_npc.hp.total = ui->NpcHP->value();
	temp_npc.framesize_w = ui->npcGraphicSizeSpin_w->value();
	temp_npc.framesize_h = ui->npcGraphicSizeSpin_h->value();
	//temp_npc.filesize = dataExchanger->npcGraphicSize;
	//temp_npc.filename = ui->npcListCombobox->currentText();
	strcpy (temp_npc.filename, ui->npcListCombobox->currentText().toLatin1());

	//printf(">> DialogNPCEdit::saveNPCData - name: '%s', filename: '%s'\n", temp_npc.name, temp_npc.filename);

	//printf(">> DialogNPCEdit::saveNPCData - Trying to save npc '%d' data\n", npc_n);
	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(directory, "%s/data/game/game_%s", FILEPATH, dataExchanger->centNumber);
	dataExchanger->centNumberFormat(npc_n);
	sprintf(buffer, "%s/%s.npc", directory, dataExchanger->centNumber);
	//printf(">> DialogNPCEdit::saveNPCData - buffer: %s\n", buffer);

	if (ui->checkBoxCanShoot->isChecked()) {
		temp_npc.can_shoot=1;
	} else {
		temp_npc.can_shoot=0;
	}
	if (ui->isBossCheckbox->isChecked()) {
		temp_npc.is_boss = 1;
	} else {
		temp_npc.is_boss = 0;
	}
	temp_npc.have_shield = ui->comboBoxShieldType->currentIndex();

	for (i=0; i<NPC_FRAME_NUMBER; i++) {
		temp_npc.frameset[i] = dataExchanger->frameset[i];
		temp_npc.frameset_time[i] = dataExchanger->frameset_time[i];
	}

	temp_npc.IA = ui->comboBoxIA->currentIndex();
	printf("DialogNPCEdit::saveNPCData >> comboBoxIA->currentIndex: %d, temp_npc.IA: %d\n",  ui->comboBoxIA->currentIndex(), temp_npc.IA);

	fp = fopen(buffer, "wb");
	if (fp) {
		fwrite(&temp_npc, sizeof(file_npc), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no npc file, ignoring load.\n");
	}
}



DialogNPCEdit::~DialogNPCEdit()
{
    delete ui;
}

void DialogNPCEdit::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void DialogNPCEdit::fillNPCGraphicsList() {
	printf("DEBUG - fillNPCGraphicsList - START\n");
	qDebug(QString("dir: "+QString(FILEPATH)+"/data/images/sprites/enemies/").toAscii());
	QDir *dir = new QDir(QString(FILEPATH)+"/data/images/sprites/enemies/");
	dir->setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	dir->setSorting(QDir::Size | QDir::Reversed);
	QFileInfoList list = dir->entryInfoList();
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		printf("fileName: %s\n", qPrintable(fileInfo.fileName()));
		if (i == 0) {
			sprintf(dataExchanger->addNpcFilename, "%s/data/images/sprites/enemies/%s", FILEPATH, qPrintable(fileInfo.fileName()));
			printf(">> SET > dataExchanger::fillNPCGraphicsList->addNpcFilename: '%s'\n", dataExchanger->addNpcFilename);
		}
		//dataExchanger->NpcPreviewFile = new QString(fileInfo.fileName());
		//sprintf(dataExchanger->addNpcFilename, "%s", qPrintable(fileInfo.fileName()));
		ui->npcListCombobox->addItem(fileInfo.fileName());
	}
	printf(">> dataExchanger::fillNPCGraphicsList->addNpcFilename: '%s'\n", dataExchanger->addNpcFilename);
	ui->npcPreviewAreaWidget->repaint();
}




void DialogNPCEdit::on_npcGraphicSizeSpin_w_valueChanged(int value)
{
	dataExchanger->npcGraphicSize_w = value;
	ui->npcPreviewAreaWidget->repaint();
}

void DialogNPCEdit::on_npcGraphicSizeSpin_h_valueChanged(int value)
{
	dataExchanger->npcGraphicSize_h = value;
	ui->npcPreviewAreaWidget->repaint();
}

void DialogNPCEdit::on_npcListCombobox_currentIndexChanged(QString item)
{
	sprintf(dataExchanger->addNpcFilename, "%s/data/images/sprites/enemies/%s", FILEPATH, qPrintable(item));
	ui->npcPreviewAreaWidget->repaint();
}

void DialogNPCEdit::on_buttonBox_accepted()
{
	printf(">> DialogNPCEdit::on_buttonBox_accepted\n");
	saveNPCData(dataExchanger->selectedNPC);
	emit finishedNPCEditor();
}

void DialogNPCEdit::setNPCFrame() {
	printf(">> DialogNPCEdit::setNPCFrame - CALLED\n");
	ui->frameTypeCombo->setCurrentIndex(dataExchanger->frameset[dataExchanger->getPalleteX()]+1);
	ui->spinBox->setValue(dataExchanger->frameset_time[dataExchanger->getPalleteX()]);
}

void DialogNPCEdit::on_frameTypeCombo_currentIndexChanged(int index)
{
	dataExchanger->frameset[dataExchanger->getPalleteX()] = index-1;
}

void DialogNPCEdit::on_spinBox_valueChanged(int value)
{
	dataExchanger->frameset_time[dataExchanger->getPalleteX()] = value;
}

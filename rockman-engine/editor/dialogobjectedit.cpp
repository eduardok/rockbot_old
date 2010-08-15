#include "dialogobjectedit.h"
#include "ui_dialogobjectedit.h"
#include "format/file_object.h"
#include <QDir>

extern char FILEPATH[255];

DialogObjectEdit::DialogObjectEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogObjectEdit)
{
	char filename[255];
	int n;

	ui->setupUi(this);
	fillObjectGraphicsList();
	if (dataExchanger->editModeNPC == 1) {
		loadObjectData(dataExchanger->selectedNPC);
	} else {
		dataExchanger->centNumberFormat(dataExchanger->currentGame);
		sprintf(filename, "%s/data/game/game_%s/", FILEPATH, dataExchanger->centNumber);
		n = dataExchanger->freeSlot(filename, "obj");
		printf(">> DialogObjectEdit::DialogObjectEdit - New object dir: '%s', slot: %d\n", filename, n);
		dataExchanger->selectedNPC = n;
	}
	QObject::connect(ui->npcPreviewAreaWidget, SIGNAL(clickedIn()), this, SLOT(setObjectFrame()));
}

DialogObjectEdit::~DialogObjectEdit()
{
    delete ui;
}

void DialogObjectEdit::changeEvent(QEvent *e)
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

void DialogObjectEdit::setObjectFrame() {
	printf(">> DialogObjectEdit::setObjectFrame - CALLED\n");
	//ui->frameTypeCombo->setCurrentIndex(dataExchanger->frameset[dataExchanger->getPalleteX()]+1);
	//ui->spinBox->setValue(dataExchanger->frameset_time[dataExchanger->getPalleteX()]);
}

void DialogObjectEdit::on_buttonBox_accepted()
{
	printf(">> DialogObjectEdit::on_buttonBox_accepted\n");
	saveObjectData(dataExchanger->selectedNPC);
	emit finishedObjectEditor();
	close();
}

void DialogObjectEdit::fillObjectGraphicsList() {
	printf("DEBUG - fillObjectGraphicsList - START\n");
	QString dirPath(QString(FILEPATH)+"/data/images/sprites/objects/");
	QDir *dir = new QDir(dirPath);
	dir->setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	dir->setSorting(QDir::Size | QDir::Reversed);
	QFileInfoList list = dir->entryInfoList();
	qDebug (QString (">> fillObjectGraphicsList - dir: " + dirPath + ", list.size: " + QString::number(list.size ())).toAscii());
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		printf("fileName: %s\n", qPrintable(fileInfo.fileName()));
		if (i == 0) {
			sprintf(dataExchanger->addNpcFilename, "%s/data/images/sprites/objects/%s", FILEPATH, qPrintable(fileInfo.fileName()));
			printf(">> SET > dataExchanger::fillObjectGraphicsList->addObjectFilename: '%s'\n", dataExchanger->addNpcFilename);
		}
		//dataExchanger->NpcPreviewFile = new QString(fileInfo.fileName());
		//sprintf(dataExchanger->addNpcFilename, "%s", qPrintable(fileInfo.fileName()));
		ui->objectListCombobox->addItem(fileInfo.fileName());
	}
	printf(">> dataExchanger::fillObjectGraphicsList->addObjectFilename: '%s'\n", dataExchanger->addNpcFilename);
	ui->npcPreviewAreaWidget->repaint();
}

void DialogObjectEdit::on_npcGraphicSizeSpin_w_valueChanged(int value)
{
	dataExchanger->npcGraphicSize_w = value;
	ui->npcPreviewAreaWidget->repaint();
}

void DialogObjectEdit::on_npcGraphicSizeSpin_h_valueChanged(int value)
{
	dataExchanger->npcGraphicSize_h = value;
	ui->npcPreviewAreaWidget->repaint();
}

void DialogObjectEdit::on_objectListCombobox_currentIndexChanged(QString item)
{
	sprintf(dataExchanger->addNpcFilename, "%s/data/images/sprites/objects/%s", FILEPATH, qPrintable(item));
	ui->npcPreviewAreaWidget->repaint();
}



void DialogObjectEdit::loadObjectData(int object_n) {
	FILE *fp;
	struct struct_object temp_object;
	char buffer[255], directory[255];
	int i;

	printf("Trying to load object '%d' data\n", object_n);
	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(directory, "%s/data/game/game_%s", FILEPATH, dataExchanger->centNumber);
	dataExchanger->centNumberFormat(object_n);
	sprintf(buffer, "%s/%s.obj", directory, dataExchanger->centNumber);
	printf(">> MainWindow::fillObjectList - buffer: %s\n", buffer);

	fp = fopen(buffer, "rb");
	if (fp) {
		fread(&temp_object, sizeof(struct_object), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no object file, ignoring load.\n");
	}
	ui->NpcName->setText(temp_object.name);
	ui->npcGraphicSizeSpin_w->setValue(temp_object.framesize_w);
	ui->npcGraphicSizeSpin_h->setValue(temp_object.framesize_h);
	ui->comboBoxType->setCurrentIndex(temp_object.type);

	ui->spinBox_timer->setValue(temp_object.timer);
	ui->spinBox_speed->setValue(temp_object.speed);
	ui->spinBox_limit->setValue(temp_object.limit);

	dataExchanger->npcGraphicSize_w = temp_object.framesize_w;
	dataExchanger->npcGraphicSize_h = temp_object.framesize_h;
	for (i=0; i<ui->objectListCombobox->count(); i++) {
		if (ui->objectListCombobox->itemText(i) == QString(temp_object.filename)) {
			ui->objectListCombobox->setCurrentIndex(i);
			break;
		}
	}
}



void DialogObjectEdit::saveObjectData(int object_n) {
	FILE *fp;
	struct struct_object temp_object;
	char buffer[255], directory[255];

	strcpy (temp_object.name, ui->NpcName->text().toLatin1());

	temp_object.type = ui->comboBoxType->currentIndex();
	temp_object.framesize_w = ui->npcGraphicSizeSpin_w->value();
	temp_object.framesize_h = ui->npcGraphicSizeSpin_h->value();
	printf(">> DialogobjectEdit::saveobjectData - temp_object.framesize_w: '%d', temp_object.framesize_h: '%d'\n", temp_object.framesize_w, temp_object.framesize_h);

	strcpy (temp_object.filename, ui->objectListCombobox->currentText().toLatin1());

	printf(">> DialogobjectEdit::saveobjectData - name: '%s', filename: '%s'\n", temp_object.name, temp_object.filename);

	//printf(">> DialogobjectEdit::saveobjectData - Trying to save object '%d' data\n", object_n);
	dataExchanger->centNumberFormat(dataExchanger->currentGame);
	sprintf(directory, "%s/data/game/game_%s", FILEPATH, dataExchanger->centNumber);
	dataExchanger->centNumberFormat(object_n);
	sprintf(buffer, "%s/%s.obj", directory, dataExchanger->centNumber);
	//printf(">> DialogobjectEdit::saveobjectData - buffer: %s\n", buffer);

	temp_object.timer = ui->spinBox_timer->value();
	temp_object.speed = ui->spinBox_speed->value();
	temp_object.limit = ui->spinBox_limit->value();


	fp = fopen(buffer, "wb");
	if (fp) {
		fwrite(&temp_object, sizeof(struct_object), 1, fp);
		fclose(fp);
	} else {
		printf("DEBUG - no object file, ignoring load.\n");
	}
}


void DialogObjectEdit::on_buttonBox_rejected()
{
	close();
}

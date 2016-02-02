#include "SETestKCL_GUI.h"

#include <QMessageBox>

SETestKCL_GUI::SETestKCL_GUI() :
ui(new Ui::SETestKCL_GUI)
{
    ui->setupUi(this);

	connect(ui->c_yesButton, SIGNAL(released()), this, SLOT(slot_yesButtonPressed()));
	connect(ui->c_noButton, SIGNAL(released()), this, SLOT(slot_noButtonPressed()));
	connect(ui->c_undoButton, SIGNAL(released()), this, SLOT(slot_undoButtonPressed()));
	connect(ui->c_helpButton, SIGNAL(released()), this, SLOT(slot_helpButtonPressed()));

	m_timer = new QTimer();
	m_timeValue = new QTime();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateElapsed()));
	m_timer->start(1000);
	m_timeValue->start();

	m_negotiate.Start(true);
}

SETestKCL_GUI::~SETestKCL_GUI()
{
	m_negotiate.Stop();

    delete ui;
}

void SETestKCL_GUI::UpdateElapsed()
{
	int msec = m_timeValue->elapsed();
	double sec = msec / 1000;
	double min = sec / 60;
	double hr = min / 60;
	QString timeStr = QString("%1:%2:%3")
		.arg(QString::number(int(hr)))
		.arg(QString::number(fmod(min, 60.0), 'f', 0))
		.arg(QString::number(fmod(sec, 60.0), 'f', 0));

	unsigned int numYes = m_negotiate.GetNumberOfYes();
	unsigned int numNo = m_negotiate.GetNumberOfNo();
	//calculate number of Yes's per minute (avoid divide by zero)
	double yes_per_min = numYes / double(min>0 ? min : 1);
	//calculate number of No's per minute
	double no_per_min = numNo / double(min>0 ? min : 1);

	//calculate the ratio between Yes and No numbers
	double total_yes_no = numYes + numNo;
	double yes_no_ratio = numYes / (total_yes_no>0 ? total_yes_no : 1);

	//update user interface
	ui->c_time->setText(timeStr);
	ui->c_numYes->setText(QString::number(numYes));
	ui->c_yesPerMin->setText(QString::number(yes_per_min, 'f', 2));
	ui->c_numNo->setText(QString::number(numNo));
	ui->c_noPerMin->setText(QString::number(no_per_min, 'f', 2));
	ui->c_ratio->setText(QString::number(yes_no_ratio, 'f', 2));
}

void SETestKCL_GUI::slot_yesButtonPressed()
{
	m_negotiate.AppendInput('y');
}

void SETestKCL_GUI::slot_noButtonPressed()
{
	m_negotiate.AppendInput('n');
}

void SETestKCL_GUI::slot_undoButtonPressed()
{
	m_negotiate.AppendInput('z');
}

void SETestKCL_GUI::slot_helpButtonPressed()
{
	QMessageBox msgBox;
	msgBox.setText( QString(m_negotiate.GenerateHelpText().c_str()) );
	msgBox.exec();
}
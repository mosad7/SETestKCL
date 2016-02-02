#ifndef SETESTKCL_GUI_H
#define SETESTKCL_GUI_H

#include "ui_SETestKCL_GUI.h"

#include <QDialog>
#include <Qtimer>
#include <QTime>

#include "Negotiator.h"

class SETestKCL_GUI : public QDialog
{
    Q_OBJECT

	Ui::SETestKCL_GUI *ui;

	QTimer *m_timer;
	QTime  *m_timeValue;

	Negotiator m_negotiate;

public:
	SETestKCL_GUI();
	~SETestKCL_GUI();

private:

signals :

public slots :
	void UpdateElapsed();
	void slot_yesButtonPressed();
	void slot_noButtonPressed();
	void slot_undoButtonPressed();
	void slot_helpButtonPressed();
};

#endif // SETESTKCL_GUI_H

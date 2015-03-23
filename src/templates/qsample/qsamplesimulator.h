#ifndef QSAMPLESIMULATOR_H
#define QSAMPLESIMULATOR_H

#include "core/templatesimulator.h"

#include "ui_qsamplesimulator.h"


namespace Ui {
  class QsampleSimulator;
}

class TemplateCore;
class QLabel;
class QPushButton;
class QRadioButton;

/// \brief Simulator for Qsample template.
/// \ingroup template-qsample
class QsampleSimulator : public TemplateSimulator {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit QsampleSimulator(TemplateCore *core, QWidget *parent = 0);
    virtual ~QsampleSimulator();

  public slots:
    bool startSimulation();
    bool stopSimulation();
    bool goBack();

  private slots:
    void start();
    void restart();
    void exit();

    void prepareSummary();
    void questionSubmitted();

  private:
    Ui::QsampleSimulator *m_ui;
};

#endif // QsampleSIMULATOR_H


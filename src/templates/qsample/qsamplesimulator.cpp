#include "templates/qsample/qsamplesimulator.h"

#include "core/templatecore.h"
#include "templates/qsample/qsamplecore.h"
#include "templates/qsample/qsampleeditor.h"
#include "templates/qsample/qsampleitem.h"
#include "definitions/definitions.h"

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


QsampleSimulator::QsampleSimulator(TemplateCore *core, QWidget *parent)
  : TemplateSimulator(core, parent), m_ui(new Ui::QsampleSimulator) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblHeading->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADING_SIZE_INCREASE);
  m_ui->m_lblHeading->setFont(caption_font);

  connect(m_ui->m_btnStart, SIGNAL(clicked()), this, SLOT(start()));
  connect(m_ui->m_btnRestart, SIGNAL(clicked()), this, SLOT(restart()));
  connect(m_ui->m_btnExit, SIGNAL(clicked()), this, SLOT(exit()));
}

QsampleSimulator::~QsampleSimulator() {
  qDebug("Destroying QsampleSimulator instance.");

  delete m_ui;
}

bool QsampleSimulator::startSimulation() {
  QsampleEditor *editor = static_cast<QsampleEditor*>(core()->editor());

  if (!editor->canGenerateApplications()) {
    // There are no active questions or qsample does not
    // containt its name or author name.
    return false;
  }

  // Remove existing questions.
  while (m_ui->m_phoneWidget->count() > 3) {
    QWidget *question_widget = m_ui->m_phoneWidget->widget(2);

    m_ui->m_phoneWidget->removeWidget(question_widget);
    question_widget->deleteLater();
  }

  // Load the questions, setup the qsample and start it.
  m_ui->m_btnStart->setEnabled(true);
  m_ui->m_lblAuthor->setText(editor->m_ui->m_txtAuthor->lineEdit()->text());
  m_ui->m_lblHeading->setText(editor->m_ui->m_txtName->lineEdit()->text());

  int question_number = 1;
  QList<QsampleQuestion> questions = editor->activeQuestions();

  foreach (const QsampleQuestion &question, questions) {
    QsampleItem *item = new QsampleItem(m_ui->m_phoneWidget);

    connect(item, SIGNAL(questionSubmitted()), this, SLOT(questionSubmitted()));

    item->setQuestion(question, question_number++, questions.size());
    m_ui->m_phoneWidget->insertWidget(m_ui->m_phoneWidget->count() - 1, item);
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);
  return true;
}

bool QsampleSimulator::stopSimulation() {
  m_ui->m_phoneWidget->setCurrentIndex(0);

  emit canGoBackChanged(false);

  return true;
}

bool QsampleSimulator::goBack() {
  return false;
}

void QsampleSimulator::start() {
  m_ui->m_phoneWidget->setCurrentIndex(2);
}

void QsampleSimulator::prepareSummary() {
  int answered_correctly = 0;
  int answered_wrongly = 0;
  int unanswered = 0;

  for (int i = 2; i < m_ui->m_phoneWidget->count() - 1; i++) {
    QsampleItem *widget = static_cast<QsampleItem*>(m_ui->m_phoneWidget->widget(i));

    switch (widget->state()) {
      case QsampleItem::AnsweredCorrectly:
        answered_correctly++;
        break;

      case QsampleItem::AnsweredWrongly:
        answered_wrongly++;
        break;

      case QsampleItem::Unanswered:
      default:
        unanswered++;
        break;
    }
  }

  m_ui->m_lblTotalCorrect->setText(tr("Total correct %1").arg(answered_correctly));
  m_ui->m_lblTotalWrong->setText(tr("Total wrong %1").arg(answered_wrongly));
  m_ui->m_lblTotalUnanswered->setText(tr("Total unanswered %1").arg(unanswered));
}

void QsampleSimulator::questionSubmitted() {
  int current_index = m_ui->m_phoneWidget->currentIndex();

  if (current_index == m_ui->m_phoneWidget->count() - 2) {
    // This is the last confirmed question. Go to "summary".
    prepareSummary();
  }

  m_ui->m_phoneWidget->setCurrentIndex(current_index + 1);
}

void QsampleSimulator::restart() {
  // Reset all the questions.
  for (int i = 2; i < m_ui->m_phoneWidget->count() - 1; i++) {
    static_cast<QsampleItem*>(m_ui->m_phoneWidget->widget(i))->reset();
  }

  m_ui->m_phoneWidget->setCurrentIndex(1);
}

void QsampleSimulator::exit() {
  stopSimulation();
  emit simulationStopRequested();
}


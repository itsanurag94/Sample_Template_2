#include "templates/qsample/qsampleitem.h"

#include "definitions/definitions.h"


QsampleItem::QsampleItem(QWidget *parent) : QWidget(parent), m_state(Unanswered), m_ui(new Ui::QsampleItem) {
  m_ui->setupUi(this);

  QFont caption_font = m_ui->m_lblQuestionNumber->font();
  caption_font.setPointSize(caption_font.pointSize() + SIMULATOR_HEADER_SIZE_INCREASE);
  m_ui->m_lblQuestionNumber->setFont(caption_font);
   m_ui->m_lblPicture->setFixedHeight((int) (SIMULATOR_CONTENTS_HEIGHT * 0.4));

  setupButtons();
  createConnections();
}

QsampleItem::~QsampleItem() {
  delete m_ui;
}

void QsampleItem::setupButtons() {
  m_answerButtons = QList<QRadioButton*>();
  m_answerButtons.append(m_ui->m_rbAnswerOne);
  m_answerButtons.append(m_ui->m_rbAnswerTwo);
//  m_btnPictureSelect.append(m_ui->m_)
}

void QsampleItem::createConnections() {
//  connect(m_ui->m_btnPictureSelect, SIGNAL(clicked()), this, SLOT(selectPicture()));
  connect(m_ui->m_btnNext, SIGNAL(clicked()), this, SLOT(onNextClicked()));
  connect(m_ui->m_btnConfirm, SIGNAL(clicked()), this, SLOT(onSubmitClicked()));
  connect(m_ui->m_rbAnswerOne, SIGNAL(toggled(bool)), m_ui->m_lblWarning, SLOT(hide()));
  connect(m_ui->m_rbAnswerTwo, SIGNAL(toggled(bool)), m_ui->m_lblWarning, SLOT(hide()));
}

void QsampleItem::clearStylesheets() {
  foreach (QRadioButton *answer_button, m_answerButtons) {
    answer_button->setStyleSheet(QString());
  }
}

void QsampleItem::setQuestion(const QsampleQuestion &question, int question_number, int total_questions) {
  m_question = question;

  m_ui->m_rbAnswerOne->setText(question.answerOne());
  m_ui->m_rbAnswerTwo->setText(question.answerTwo());

  m_ui->m_rbAnswerOne->setVisible(question.correctAnswer() == 0 || !question.answerOne().simplified().isEmpty());
  m_ui->m_rbAnswerTwo->setVisible(question.correctAnswer() == 1 || !question.answerTwo().simplified().isEmpty());

  m_ui->m_lblQuestionNumber->setText(tr("Question number %1 of %2").arg(QString::number(question_number),
                                                                        QString::number(total_questions)));
  m_ui->m_lblQuestionText->setText(question.question());
  m_ui->m_lblPicture->setPixmap(QPixmap(question.picturePath()).scaled(m_ui->m_lblPicture->size(), Qt::KeepAspectRatio));
}

QsampleItem::State QsampleItem::state() const {
  return m_state;
}

void QsampleItem::reset() {
  clearStylesheets();

  foreach (QRadioButton *answer_button, m_answerButtons) {
    // Hacky way to really force all radio buttons to be unchecked.
    answer_button->setEnabled(false);
    answer_button->setCheckable(false);
    answer_button->setChecked(false);
    answer_button->setEnabled(true);
    answer_button->setCheckable(true);
  }

  m_ui->m_lblWarning->setVisible(false);
  m_ui->m_btnConfirm->setEnabled(true);
  //m_ui->m_btnPictureSelect->setEnabled(false);
  m_state = Unanswered;
}

void QsampleItem::onNextClicked() {
  // Just signal that user is done with this question.
  emit questionSubmitted();
}

void QsampleItem::onSubmitClicked() {
  // Check if user selected any answer, if he did not, then remind him it.
  if (!m_ui->m_rbAnswerOne->isChecked() && !m_ui->m_rbAnswerTwo->isChecked()){
    m_ui->m_lblWarning->setText("Select some answer, please.");
    m_ui->m_lblWarning->setVisible(true);
  }
  else {
    int selected_answer = 0;

    // User selected some answer, highlight correct and incorrect answer.
    for (int i = 0; i < m_answerButtons.size(); i++) {
      if (m_answerButtons.at(i)->isChecked()) {
        selected_answer = i;
      }
    }

    if (selected_answer == m_question.correctAnswer()) {
      m_ui->m_lblWarning->setText("That is correct answer.");
      m_answerButtons.at(selected_answer)->setStyleSheet("background-color: green;");
      m_state = AnsweredCorrectly;
    }
    else {
      m_ui->m_lblWarning->setText("That is wrong answer.");
      m_answerButtons.at(selected_answer)->setStyleSheet("background-color: red;");
      m_answerButtons.at(m_question.correctAnswer())->setStyleSheet("background-color: green;");
      m_state = AnsweredWrongly;
    }

    foreach (QRadioButton *button, m_answerButtons) {
      button->setEnabled(false);
    }

    m_ui->m_btnConfirm->setEnabled(false);
    m_ui->m_lblWarning->setVisible(true);
  }
}


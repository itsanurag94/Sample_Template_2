#include "templates/qsample/qsamplequestion.h"

#include <QStringList>


QsampleQuestion::QsampleQuestion() {
  m_answers = QStringList();
  m_answers << QString() << QString() << QString() << QString();
}

QsampleQuestion::~QsampleQuestion() {
}

int QsampleQuestion::correctAnswer() const {
  return m_correctAnswer;
}

void QsampleQuestion::setCorrectAnswer(int correctAnswer) {
  m_correctAnswer = correctAnswer;
}

void QsampleQuestion::setAnswer(int index, const QString &answer) {
  if (index >= 0 && index < 2) {
    m_answers.replace(index, answer);
  }
}

QString QsampleQuestion::answerOne() const {
  return m_answers.at(0);
}

QString QsampleQuestion::answerTwo() const {
  return m_answers.at(1);
}

//QString QsampleQuestion::answerThree() const {
//  return m_answers.at(2);
//}

//QString QsampleQuestion::answerFour() const {
//  return m_answers.at(3);
//}

QString QsampleQuestion::question() const {
  return m_question;
}

void QsampleQuestion::setQuestion(const QString &question) {
  m_question = question;
}

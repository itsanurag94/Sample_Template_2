#ifndef QSAMPLEQUESTION_H
#define QSAMPLEQUESTION_H

#include <QMetaType>
//#include "templates/qsample/qsampleeditor.h"

#include <QStringList>

/// \brief Container for one question.
/// \ingroup template-qsample
class QsampleQuestion {
  public:
    explicit QsampleQuestion();
    virtual ~QsampleQuestion();

    /// \brief Access to inde of correct answer.
    /// \return Returns index of correct answer.
    /// \warning Index is NOT numbered from 0. It is numbered from 1. So if first
    /// answer is correct, then index of correct answer is ONE.
    int correctAnswer() const;
    void setCorrectAnswer(int correctAnswer);

    void setAnswer(int index, const QString &answer);
    QString answerOne() const;
    QString answerTwo() const;
    QString picturePath() const;
    void setPicturePath(const QString& picture_path);

    QString question() const;
    void setQuestion(const QString &question);

  private:
    QString m_question;
    QStringList m_answers;
    int m_correctAnswer;
    QString m_picturePath;
};

Q_DECLARE_METATYPE(QsampleQuestion)

#endif // QsampleQUESTION_H


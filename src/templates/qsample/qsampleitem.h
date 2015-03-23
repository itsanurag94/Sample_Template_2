#ifndef QSAMPLEITEM_H
#define QSAMPLEITEM_H

#include <QWidget>

#include "ui_qsampleitem.h"

#include "templates/qsample/qsamplequestion.h"


namespace Ui {
  class QsampleItem;
}

/// \brief Widget which represents single question in Qsample.
/// \ingroup template-qsample
class QsampleItem : public QWidget {
    Q_OBJECT

  public:
    /// \brief Enum containing possible states for widget for the question.
    enum State {
      Unanswered,
      AnsweredCorrectly,
      AnsweredWrongly
    };

    // Contructors and destructors.
    explicit QsampleItem(QWidget *parent = 0);
    virtual ~QsampleItem();

    /// \brief Sets new question for this widget.
    /// \param question Question object.
    /// \param question_number Number of the question.
    void setQuestion(const QsampleQuestion &question, int question_number, int total_questions);

    /// \brief Access to state of qsample question widget.
    /// \return Returns the state of qsample question widget.
    State state() const;

  public slots:
    /// \brief Resets widget for the question to its original/default state.
    void reset();

  signals:
    /// \brief Emitted if users clicks "Next" or "Submit"
    void questionSubmitted();

  private slots:
    void onNextClicked();
    void onSubmitClicked();

  private:
    void setupButtons();
    void createConnections();
    void clearStylesheets();

  private:
    State m_state;
    Ui::QsampleItem *m_ui;
    QsampleQuestion m_question;
    QList<QRadioButton*> m_answerButtons;
};

#endif // QsampleITEM_H


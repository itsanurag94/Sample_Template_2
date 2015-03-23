#ifndef QSAMPLEEDITOR_H
#define QSAMPLEEDITOR_H

#include "core/templateeditor.h"

#include "ui_qsampleeditor.h"
#include "templates/qsample/qsamplequestion.h"

#include <QIcon>


namespace Ui {
  class QsampleEditor;
}

class QsampleSimulator;
class QShowEvent;

/// \brief Editor for Qsample.
/// \ingroup template-qsample
class QsampleEditor : public TemplateEditor {
    Q_OBJECT

    friend class QsampleSimulator;
    friend class QsampleCore;

  public:
    // Constructors and destructors.
    explicit QsampleEditor(TemplateCore *core, QWidget *parent = 0);
    virtual ~QsampleEditor();

    QString generateBundleData();
    bool canGenerateApplications();
    bool loadBundleData(const QString &bundle_data);

    /// \brief Access to list of added questions.
    /// \return Returns list of added questions.
    QList<QsampleQuestion> activeQuestions() const;

    QString projectName();
    QString authorName();

  private slots:
    void selectPicture();
    void loadPicture(const QString &picture_path);
    void updateQuestionCount();
    void addQuestion(const QString &question, const QStringList &answers, int correct_answer, const QString& picture_path);
    void addQuestion();
    void loadQuestion(int index);
    void removeQuestion();
    void saveQuestion();
    void moveQuestionUp();
    void moveQuestionDown();

    void configureUpDown();
    void setEditorsEnabled(bool enabled);

    void checkName();
    void checkAuthor();

    void updateNameStatus();
    void updateAuthorStatus();

  private:
    QsampleQuestion m_activeQuestion;
    Ui::QsampleEditor *m_ui;
    QIcon m_iconYes;
    QIcon m_iconNo;
};

#endif // QsampleEDITOR_H


#include "templates/qsample/qsampleeditor.h"

#include "miscellaneous/iconfactory.h"
#include "templates/qsample/qsamplequestion.h"
#include "core/templatefactory.h"
#include "core/templatecore.h"
#include "core/templateentrypoint.h"

#include <QToolTip>
#include <QTimer>
#include <QShowEvent>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>


QsampleEditor::QsampleEditor(TemplateCore *core, QWidget *parent)
  : TemplateEditor(core, parent), m_ui(new Ui::QsampleEditor) {
  m_ui->setupUi(this);

  // Set validators.
  QRegExpValidator *author_validator = new QRegExpValidator(this);
  QRegExpValidator *title_validator = new QRegExpValidator(this);
  QRegExpValidator *option_validator = new QRegExpValidator(this);

  author_validator->setRegExp(QRegExp(".{,50}"));
  title_validator->setRegExp(QRegExp(".{,100}"));
  option_validator->setRegExp(QRegExp(".{,60}"));
 // m_ui->m_txtQuestion->lineEdit->setValidator(question_validator); //Change Done
  m_ui->m_txtAuthor->lineEdit()->setValidator(author_validator);
  m_ui->m_txtName->lineEdit()->setValidator(title_validator);
  m_ui->m_txtAnswerOne->setValidator(option_validator);
  m_ui->m_txtAnswerTwo->setValidator(option_validator);
  m_ui->m_txtQuestion->setMaxLength(60);

  // Set tab order.
  QList<QWidget*> tab_order_widgets;
  tab_order_widgets << m_ui->m_txtQuestion<<m_ui->m_txtQuestion << m_ui->m_btnAnswerOne << m_ui->m_txtAnswerOne <<
                       m_ui->m_btnAnswerTwo << m_ui->m_txtAnswerTwo <<
                       m_ui->m_txtAuthor->lineEdit() << m_ui->m_txtName->lineEdit() <<
                       m_ui->m_listQuestions << m_ui->m_btnQuestionAdd << m_ui->m_btnQuestionRemove <<     //2 tab
                       m_ui->m_btnQuestionUp << m_ui->m_btnQuestionDown;
//Set order
  for (int i = 1; i < tab_order_widgets.size(); i++) {
    setTabOrder(tab_order_widgets.at(i - 1), tab_order_widgets.at(i));
  }

  m_ui->m_txtNumberOfQuestions->lineEdit()->setEnabled(false);
  
  //m_ui->m_lblPictureFile->label()->setWordWrap(true);
  IconFactory *factory = IconFactory::instance();

 //  m_ui->m_lblPictureFile->setStatus(WidgetWithStatus::Error, QString(), tr("No picture selected"));
  m_ui->m_txtAuthor->lineEdit()->setPlaceholderText(tr("Who is this cool fellow"));
  m_ui->m_txtName->lineEdit()->setPlaceholderText(tr("What's your cool stuff name"));

  m_ui->m_btnAnswerOne->setProperty("id", 0);
  m_ui->m_btnAnswerTwo->setProperty("id", 1);

  m_ui->m_btnQuestionAdd->setIcon(factory->fromTheme("item-add"));
  m_ui->m_btnQuestionRemove->setIcon(factory->fromTheme("item-remove"));
  m_ui->m_btnQuestionUp->setIcon(factory->fromTheme("move-up"));
  m_ui->m_btnQuestionDown->setIcon(factory->fromTheme("move-down"));

  m_iconNo = factory->fromTheme("dialog-no");
  m_iconYes = factory->fromTheme("dialog-yes");

  m_ui->m_btnAnswerOne->setIcon(m_iconNo);
  m_ui->m_btnAnswerTwo->setIcon(m_iconNo);

//Update Author and Qsample name
  connect(m_ui->m_txtAuthor->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateAuthorStatus()));
  connect(m_ui->m_txtName->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(updateNameStatus()));

//Signals to the button
  connect(m_ui->m_btnQuestionAdd, SIGNAL(clicked()), this, SLOT(addQuestion()));
  connect(m_ui->m_btnQuestionRemove, SIGNAL(clicked()), this, SLOT(removeQuestion()));
  connect(m_ui->m_listQuestions, SIGNAL(currentRowChanged(int)), this, SLOT(loadQuestion(int)));

  connect(m_ui->m_btnAnswerOne, SIGNAL(clicked()), this, SLOT(saveQuestion()));
  connect(m_ui->m_btnAnswerTwo, SIGNAL(clicked()), this, SLOT(saveQuestion()));


//Save the answer of the question
  connect(m_ui->m_txtAnswerOne, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtAnswerTwo, SIGNAL(textEdited(QString)), this, SLOT(saveQuestion()));
  connect(m_ui->m_txtQuestion, SIGNAL(textChanged()), this, SLOT(saveQuestion()));

  connect(m_ui->m_btnQuestionUp, SIGNAL(clicked()), this, SLOT(moveQuestionUp()));
  connect(m_ui->m_btnQuestionDown, SIGNAL(clicked()), this, SLOT(moveQuestionDown()));

  setEditorsEnabled(false);
  updateQuestionCount();
  checkName();
  checkAuthor();
  qRegisterMetaType<QsampleQuestion>("Do or Die");
}

QsampleEditor::~QsampleEditor() {
  qDebug("Your time and game is up!!.");

  delete m_ui;
}

QList<QsampleQuestion> QsampleEditor::activeQuestions() const {
  QList<QsampleQuestion> questions;


//Update number of questions count
  for (int i = 0; i < m_ui->m_listQuestions->count(); i++) {
    questions.append(m_ui->m_listQuestions->item(i)->data(Qt::UserRole).value<QsampleQuestion>());
  }

  return questions;
}

//Save project name
QString QsampleEditor::projectName() {
  return m_ui->m_txtName->lineEdit()->text();
}

//Save author's name
QString QsampleEditor::authorName() {
  return m_ui->m_txtAuthor->lineEdit()->text();
}

//Update question count
void QsampleEditor::updateQuestionCount() {
  m_ui->m_txtNumberOfQuestions->lineEdit()->setText(QString::number(m_ui->m_listQuestions->count()));

  if (m_ui->m_listQuestions->count() > 0) {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Ok, tr("You have still got chances to survive."));
  }
  else {
    m_ui->m_txtNumberOfQuestions->setStatus(WidgetWithStatus::Error, tr("There ain't any chances for you."));
  }
}

//Set new question and it's correct answer
void QsampleEditor::addQuestion(const QString &question, const QStringList &answers, int correct_answer) {
  QsampleQuestion new_question;

  new_question.setQuestion(question);
  new_question.setCorrectAnswer(correct_answer);

  int answer_index = 0;
  foreach (const QString &answer, answers) {
    new_question.setAnswer(answer_index++, answer);
  }

  int marked_question = m_ui->m_listQuestions->currentRow();
  QListWidgetItem *new_item = new QListWidgetItem();
  new_item->setText(new_question.question());
  new_item->setData(Qt::UserRole, QVariant::fromValue(new_question));

  if (m_ui->m_listQuestions->count() == 0) {
    // We are adding first question.
    setEditorsEnabled(true);

    m_ui->m_btnQuestionRemove->setEnabled(true);

    m_ui->m_listQuestions->insertItem(0, new_item);
    m_ui->m_listQuestions->setCurrentRow(0);
  }
  else {
    m_ui->m_listQuestions->insertItem(marked_question + 1, new_item);
    m_ui->m_listQuestions->setCurrentRow(marked_question + 1);
  }

  updateQuestionCount();
}

void QsampleEditor::addQuestion() {
  addQuestion(tr("Gujarat's capital is Ahmedabad?"),
              QStringList() << tr("True") << tr("False"),2);
      //        tr("I have seven beasts.") << tr("Cats? Well, we own eleven dogs."),
      //        2);

  launch();
  emit changed();
}

//Load the question upon opening
void QsampleEditor::loadQuestion(int index) {
  m_ui->m_txtQuestion->blockSignals(true);
  m_ui->m_txtAnswerOne->blockSignals(true);
  m_ui->m_txtAnswerTwo->blockSignals(true);
  m_ui->m_btnAnswerOne->blockSignals(true);
  m_ui->m_btnAnswerTwo->blockSignals(true);

  if (index >= 0) {
    QsampleQuestion question = m_ui->m_listQuestions->item(index)->data(Qt::UserRole).value<QsampleQuestion>();

    m_ui->m_txtQuestion->setText(question.question());
    m_ui->m_txtAnswerOne->setText(question.answerOne());
   m_ui->m_txtAnswerTwo->setText(question.answerTwo());
    m_ui->m_btnAnswerOne->setIcon(question.correctAnswer() == 0 ? m_iconYes : m_iconNo);
    m_ui->m_btnAnswerTwo->setIcon(question.correctAnswer() == 1 ? m_iconYes : m_iconNo);

    m_activeQuestion = question;
  }
  else {
    m_ui->m_txtQuestion->setText(QString());
    m_ui->m_txtAnswerOne->setText(QString());
    m_ui->m_txtAnswerTwo->setText(QString());
    m_ui->m_btnAnswerOne->setIcon(m_iconNo);
    m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
  }

  m_ui->m_txtQuestion->blockSignals(false);
  m_ui->m_txtAnswerOne->blockSignals(false);
  m_ui->m_txtAnswerTwo->blockSignals(false);
  m_ui->m_btnAnswerOne->blockSignals(false);
  m_ui->m_btnAnswerTwo->blockSignals(false);

  QTimer::singleShot(0, this, SLOT(configureUpDown()));
}

void QsampleEditor::removeQuestion() {
  int current_row = m_ui->m_listQuestions->currentRow();

  if (current_row >= 0) {
    if (m_ui->m_listQuestions->count() == 1) {
      // We are removing last visible question.
      setEditorsEnabled(false);

      m_ui->m_btnQuestionRemove->setEnabled(false);
    }

    delete m_ui->m_listQuestions->takeItem(current_row);
  }

  updateQuestionCount();
  launch();
  emit changed();
}

void QsampleEditor::saveQuestion() {
  PlainToolButton *button_sender = dynamic_cast<PlainToolButton*>(sender());

  if (button_sender != NULL) {
    // User clicked some of the "answer" buttons.
    m_activeQuestion.setCorrectAnswer(button_sender->property("id").toInt());

    // Change icons.
    switch (m_activeQuestion.correctAnswer()) {
      case 0:
        m_ui->m_btnAnswerOne->setIcon(m_iconYes);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
        break;

      case 1:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconYes);
        break;


      default:
        m_ui->m_btnAnswerOne->setIcon(m_iconNo);
        m_ui->m_btnAnswerTwo->setIcon(m_iconNo);
   //     m_ui->m_btnAnswerThree->setIcon(m_iconNo);
   //     m_ui->m_btnAnswerFour->setIcon(m_iconNo);
        break;
    }
  }

  m_activeQuestion.setQuestion(m_ui->m_txtQuestion->toPlainText());
  m_activeQuestion.setAnswer(0, m_ui->m_txtAnswerOne->text());
  m_activeQuestion.setAnswer(1, m_ui->m_txtAnswerTwo->text());

  m_ui->m_listQuestions->currentItem()->setData(Qt::UserRole, QVariant::fromValue(m_activeQuestion));
  m_ui->m_listQuestions->currentItem()->setText(m_activeQuestion.question());

  emit changed();
}

//Set the norms for various options
void QsampleEditor::moveQuestionUp() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index - 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index - 1);

  emit changed();
}

void QsampleEditor::moveQuestionDown() {
  int index = m_ui->m_listQuestions->currentRow();

  m_ui->m_listQuestions->insertItem(index + 1, m_ui->m_listQuestions->takeItem(index));
  m_ui->m_listQuestions->setCurrentRow(index + 1);

  emit changed();
}

void QsampleEditor::configureUpDown() {
  if (m_ui->m_listQuestions->count() > 1) {
    int index = m_ui->m_listQuestions->currentRow();

    if (index == 0) {
      m_ui->m_btnQuestionUp->setEnabled(false);
      m_ui->m_btnQuestionDown->setEnabled(true);
    }
    else if (index == m_ui->m_listQuestions->count() - 1) {
      m_ui->m_btnQuestionUp->setEnabled(true);
      m_ui->m_btnQuestionDown->setEnabled(false);
    }
    else {
      m_ui->m_btnQuestionUp->setEnabled(true);
      m_ui->m_btnQuestionDown->setEnabled(true);
    }
  }
  else {
    m_ui->m_btnQuestionUp->setEnabled(false);
    m_ui->m_btnQuestionDown->setEnabled(false);
  }
}

void QsampleEditor::setEditorsEnabled(bool enabled) {
  m_ui->m_groupQuestionEditor->setEnabled(enabled);
}

void QsampleEditor::checkName() {
  if (m_ui->m_txtName->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Error, tr("Enter the name of the qsample."));
  }
  else {
    m_ui->m_txtName->setStatus(WidgetWithStatus::Ok, tr("Name is okay."));
  }
}

void QsampleEditor::checkAuthor() {
  if (m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty()) {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Error, tr("Enter the name of the author of the qsample."));
  }
  else {
    m_ui->m_txtAuthor->setStatus(WidgetWithStatus::Ok, tr("Enter the name of the author of the qsample."));
  }
}

void QsampleEditor::updateNameStatus() {
  checkName();
  launch();
  emit changed();
}

void QsampleEditor::updateAuthorStatus() {
  checkAuthor();
  launch();
  emit changed();
}

bool QsampleEditor::canGenerateApplications() {
  return
      !m_ui->m_txtName->lineEdit()->text().simplified().isEmpty() &&
      !m_ui->m_txtAuthor->lineEdit()->text().simplified().isEmpty() &&
      !activeQuestions().isEmpty();
}

bool QsampleEditor::loadBundleData(const QString &bundle_data) {
  QDomDocument bundle_document;
  bundle_document.setContent(bundle_data);

  QDomNodeList items = bundle_document.documentElement().elementsByTagName("item");

  for (int i = 0; i < items.size(); i++) {
    QDomNode item = items.at(i);

    if (item.isElement()) {
      QString question = item.namedItem("question").toElement().text();
      int correct_answer = item.namedItem("answer").toElement().text().toInt();
      QDomNodeList answer_items = item.toElement().elementsByTagName("option");
      QList<QString> answers;

      for (int j = 0; j < answer_items.size(); j++) {
        answers.append(answer_items.at(j).toElement().text());
      }

      if (question.isEmpty() || answers.size() < 2 || answers.size() > 4) {
        // TODO: error
        continue;
      }
      else {
        addQuestion(question, answers, correct_answer);
      }
    }
    else {
      continue;
    }
  }

  // Load author & name.
  m_ui->m_txtAuthor->lineEdit()->setText(bundle_document.documentElement().namedItem("author").namedItem("name").toElement().text());
  m_ui->m_txtName->lineEdit()->setText(bundle_document.documentElement().namedItem("title").toElement().text());

  return true;
}

QString QsampleEditor::generateBundleData() {
  /*if (!canGenerateApplications()) {
    return QString();
  }*/

  QDomDocument source_document = qApp->templateManager()->generateBundleHeader(core()->entryPoint()->typeIndentifier(),
                                                                               m_ui->m_txtAuthor->lineEdit()->text(),
                                                                               QString(),
                                                                               m_ui->m_txtName->lineEdit()->text(),
                                                                               QString(),
                                                                               "1");
  FIND_DATA_ELEMENT(data_element, source_document);

  foreach (const QsampleQuestion &question, activeQuestions()) {
    QDomElement item_element = source_document.createElement("item");

    // Fill in details about question.
    QDomElement question_element = source_document.createElement("question");
    QDomElement answer_one_element = source_document.createElement("option");
    QDomElement answer_two_element = source_document.createElement("option");
    QDomElement answer_number_element = source_document.createElement("answer");

    question_element.appendChild(source_document.createTextNode(question.question()));
    answer_one_element.appendChild(source_document.createTextNode(question.answerOne()));
    answer_two_element.appendChild(source_document.createTextNode(question.answerTwo()));
    answer_number_element.appendChild(source_document.createTextNode(QString::number(question.correctAnswer())));

    item_element.appendChild(question_element);
    item_element.appendChild(answer_one_element);
    item_element.appendChild(answer_two_element);
    item_element.appendChild(answer_number_element);

    data_element.appendChild(item_element);
  }

  return source_document.toString(XML_BUNDLE_INDENTATION);
}

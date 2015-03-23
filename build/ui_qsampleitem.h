/********************************************************************************
** Form generated from reading UI file 'qsampleitem.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSAMPLEITEM_H
#define UI_QSAMPLEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QsampleItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *m_lblQuestionNumber;
    QFrame *line;
    QLabel *m_lblPicture;
    QLabel *m_lblQuestionText;
    QRadioButton *m_rbAnswerOne;
    QRadioButton *m_rbAnswerTwo;
    QSpacerItem *verticalSpacer;
    QLabel *m_lblWarning;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_btnNext;
    QPushButton *m_btnConfirm;

    void setupUi(QWidget *QsampleItem)
    {
        if (QsampleItem->objectName().isEmpty())
            QsampleItem->setObjectName(QStringLiteral("QsampleItem"));
        QsampleItem->resize(283, 329);
        verticalLayout = new QVBoxLayout(QsampleItem);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_lblQuestionNumber = new QLabel(QsampleItem);
        m_lblQuestionNumber->setObjectName(QStringLiteral("m_lblQuestionNumber"));

        verticalLayout->addWidget(m_lblQuestionNumber);

        line = new QFrame(QsampleItem);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        m_lblPicture = new QLabel(QsampleItem);
        m_lblPicture->setObjectName(QStringLiteral("m_lblPicture"));
        m_lblPicture->setFrameShape(QFrame::Box);
        m_lblPicture->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout->addWidget(m_lblPicture);

        m_lblQuestionText = new QLabel(QsampleItem);
        m_lblQuestionText->setObjectName(QStringLiteral("m_lblQuestionText"));

        verticalLayout->addWidget(m_lblQuestionText);

        m_rbAnswerOne = new QRadioButton(QsampleItem);
        m_rbAnswerOne->setObjectName(QStringLiteral("m_rbAnswerOne"));

        verticalLayout->addWidget(m_rbAnswerOne);

        m_rbAnswerTwo = new QRadioButton(QsampleItem);
        m_rbAnswerTwo->setObjectName(QStringLiteral("m_rbAnswerTwo"));

        verticalLayout->addWidget(m_rbAnswerTwo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_lblWarning = new QLabel(QsampleItem);
        m_lblWarning->setObjectName(QStringLiteral("m_lblWarning"));
        m_lblWarning->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lblWarning);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_btnNext = new QPushButton(QsampleItem);
        m_btnNext->setObjectName(QStringLiteral("m_btnNext"));

        horizontalLayout->addWidget(m_btnNext);

        m_btnConfirm = new QPushButton(QsampleItem);
        m_btnConfirm->setObjectName(QStringLiteral("m_btnConfirm"));

        horizontalLayout->addWidget(m_btnConfirm);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(QsampleItem);

        QMetaObject::connectSlotsByName(QsampleItem);
    } // setupUi

    void retranslateUi(QWidget *QsampleItem)
    {
        QsampleItem->setWindowTitle(QApplication::translate("QsampleItem", "Form", 0));
        m_lblQuestionNumber->setText(QApplication::translate("QsampleItem", "Question number", 0));
        m_lblPicture->setText(QString());
        m_lblQuestionText->setText(QApplication::translate("QsampleItem", "Question text", 0));
        m_rbAnswerOne->setText(QApplication::translate("QsampleItem", "Answer one", 0));
        m_rbAnswerTwo->setText(QApplication::translate("QsampleItem", "Answer two", 0));
        m_lblWarning->setText(QString());
        m_btnNext->setText(QApplication::translate("QsampleItem", "&Next", 0));
        m_btnConfirm->setText(QApplication::translate("QsampleItem", "&Submit", 0));
    } // retranslateUi

};

namespace Ui {
    class QsampleItem: public Ui_QsampleItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSAMPLEITEM_H

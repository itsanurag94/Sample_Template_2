#ifndef QSAMPLECORE_H
#define QSAMPLECORE_H

#include "core/templatecore.h"

#define ANSWER_FIRST    0
#define ANSWER_SECOND   1
#define ANSWER_THIRD    2
#define ANSWER_FOURTH   3


class QsampleEditor;
class QsampleSimulator;

/// \brief Main core of Qsample template.
/// \ingroup template-qsample
class QsampleCore : public TemplateCore {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit QsampleCore(TemplateEntryPoint *entry_point, QObject *parent = 0);
    virtual ~QsampleCore();

    GenerationResult generateMobileApplication(const QString &input_apk_file, QString &output_file);

  private:
    QsampleEditor *qsampleEditor();
    QsampleSimulator *qsampleSimulator();
};

#endif // QsampleCORE_H

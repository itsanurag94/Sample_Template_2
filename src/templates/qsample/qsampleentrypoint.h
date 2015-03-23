#ifndef QSAMPLEENTRYPOINT_H
#define QSAMPLEENTRYPOINT_H

#include "core/templateentrypoint.h"


class TemplateFactory;

/// \brief Entry point.
/// \ingroup template-qsample
class QsampleEntryPoint : public TemplateEntryPoint {
    Q_OBJECT

  public:
    // Constructors.
    explicit QsampleEntryPoint(TemplateFactory *parent);
    virtual ~QsampleEntryPoint();

    TemplateCore *createNewCore();
    TemplateCore *loadCoreFromBundleData(const QString &raw_data);
};

#endif // QsampleENTRYPOINT_H

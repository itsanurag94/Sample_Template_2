#include "templates/qsample/qsampleentrypoint.h"

#include "core/templatefactory.h"
#include "templates/qsample/qsamplecore.h"
#include "templates/qsample/qsampleeditor.h"
#include "templates/qsample/qsamplesimulator.h"


QsampleEntryPoint::QsampleEntryPoint(TemplateFactory *parent) : TemplateEntryPoint(parent) {
  m_baseFolder = "qsample";
  m_description = "Choose this template to create Qsample-like applications.";
  m_humanName = "Qsample";
  m_name = "qsample";
  m_thumbnailImage = "thumbnail.png";
  m_typeIndentifier = "QsampleTemplate";
//  m_mobileApplicationApkFile = "QsampleTemplateApp.apk";
}

QsampleEntryPoint::~QsampleEntryPoint() {
}

TemplateCore *QsampleEntryPoint::createNewCore() {
  return new QsampleCore(this, this);
}

TemplateCore *QsampleEntryPoint::loadCoreFromBundleData(const QString &raw_data) {
  QsampleCore *core = new QsampleCore(this, this);
  if (core->editor()->loadBundleData(raw_data)) {
    return core;
  }
  else {
    core->simulator()->deleteLater();
    core->editor()->deleteLater();
    core->deleteLater();
    return NULL;
  }
}

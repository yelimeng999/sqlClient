#include "MainWidget.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);

    m_databaseManager = std::make_shared<DatabaseManager>(nullptr);
}

MainWidget::~MainWidget()
{}

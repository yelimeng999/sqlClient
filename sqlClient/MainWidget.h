#pragma once

#include <QWidget>
#include "ui_MainWidget.h"
#include "databasemanager.h"

class MainWidget : public QWidget, public Ui::MainWidgetClass
{
public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private:
    std::shared_ptr <DatabaseManager> m_databaseManager;

};

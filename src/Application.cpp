#include "Application.h"

#include "ManagementLayer/ApplicationManager.h"

#include <QFile>
#include <QFont>
#include <QPalette>
#include <QProcess>
#include <QStyle>
#include <QStyleFactory>

void Application::restart()
{
    if (QProcess::startDetached(arguments().first(), arguments().mid(1))) {
        exit();
    }
}

Application::Application(int& argc, char* argv[])
    : QApplication(argc, argv)
{
    // Настроим информацию о приложении
    setApplicationName("FaceChanger");
    setApplicationVersion("0.1");

    // Настроим приложение
    initUI();

    // Запускаем приложение
    m_manager.reset(new ManagementLayer::ApplicationManager);
    m_manager->exec();
}

Application::~Application() = default;

void Application::initUI()
{
    setFont(QFont("Open Sans", 14));

    // Загрузка стилей
    setStyle(QStyleFactory::create("Fusion"));

    QFile styleSheetFile(":/Design/UI/stylesheet.qss");
    if (styleSheetFile.open(QIODevice::ReadOnly)) {
        setStyleSheet(styleSheetFile.readAll());
        styleSheetFile.close();
    }
    QPalette palette = QStyleFactory::create("Fusion")->standardPalette();
    palette.setColor(QPalette::Window, QColor("#182038"));
    palette.setColor(QPalette::WindowText, QColor("#ebebeb"));
    palette.setColor(QPalette::Button, QColor("#414244"));
    palette.setColor(QPalette::ButtonText, QColor("#ebebeb"));
    palette.setColor(QPalette::Base, QColor("#404040"));
    palette.setColor(QPalette::AlternateBase, QColor("#353535"));
    palette.setColor(QPalette::Text, QColor("#ebebeb"));
    palette.setColor(QPalette::Highlight, QColor("#2b78da"));
    palette.setColor(QPalette::HighlightedText, QColor("#ffffff"));
    palette.setColor(QPalette::Light, QColor("#404040"));
    palette.setColor(QPalette::Midlight, QColor("#696765"));
    palette.setColor(QPalette::Dark, QColor("#696765"));
    palette.setColor(QPalette::Shadow, QColor("#1c2023"));

    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor("#a1a1a1"));
    palette.setColor(QPalette::Disabled, QPalette::Button, QColor("#1b1e21"));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor("#a1a1a1"));
    palette.setColor(QPalette::Disabled, QPalette::Base, QColor("#333333"));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor("#666769"));
    palette.setColor(QPalette::Disabled, QPalette::Highlight, QColor("#eeeeee"));
    setPalette(palette);
}

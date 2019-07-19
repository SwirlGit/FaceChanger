#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include <memory>

namespace ManagementLayer {
class ApplicationManager;
}


class Application : public QApplication
{
    Q_OBJECT

public:
    /**
     * @brief Перезапустить приложение
     */
    static void restart();

public:
    explicit Application(int& argc, char* argv[]);
    ~Application();

private:
    /**
     * @brief Настроить внешний вид приложения
     */
    void initUI();

    /**
     * @brief Настроить перевод приложения
     */
    void initTranslation(const QString& language);

private:
    /**
     * @brief Менеджер управлеющий приложением
     */
    std::unique_ptr<ManagementLayer::ApplicationManager> m_manager;
};

#endif // APPLICATION_H

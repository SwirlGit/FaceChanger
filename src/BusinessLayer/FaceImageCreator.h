#ifndef FACEIMAGECREATOR_H
#define FACEIMAGECREATOR_H

namespace cv {
class CascadeClassifier;
class Mat;
}
namespace BusinessLayer {
class FaceImage;
}
class QImage;
class QString;

namespace BusinessLayer
{
/**
 * @brief Интерфейс для поиска лица на изображении
 */
class IFaceImageCreator
{
public:
    virtual ~IFaceImageCreator() = default;

    /**
     * @brief Чистая функция для поиска лица на изображении
     */
    virtual FaceImage createFaceImage(const QImage& image) const = 0;
};

/**
 * @brief Класс, который определяет лицо на изображении с помощью OpenCV
 */
class OpenCVFaceImageCreator : public IFaceImageCreator
{
public:
    OpenCVFaceImageCreator();
    ~OpenCVFaceImageCreator();

    /**
     * @brief Реализация функции поиска лица на изображении
     */
    BusinessLayer::FaceImage createFaceImage(const QImage& image) const override final;

private:
    /**
     * @brief Вывести в лог строку ошибки
     */
    void logErrorString(const QString& errorString) const;

private:
    /**
     * @brief Флаг валидности объекта
     */
    bool m_isValid = false;

    /**
     * @brief определитель лица
     */
    cv::CascadeClassifier* m_faceDetector = nullptr;

    /**
     * @brief определитель глаз
     */
    cv::CascadeClassifier* m_eyesDetector = nullptr;
};

} // BusinessLayer

#endif // FACEIMAGECREATOR_H

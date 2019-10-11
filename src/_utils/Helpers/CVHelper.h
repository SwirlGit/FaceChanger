#ifndef CVHELPER_H
#define CVHELPER_H

namespace cv {
class Mat;
}
class QImage;

/**
 * @brief Помощник в работе с OpenCV
 */
class CVHelper
{
public:
    /**
     * @brief Перевести QImage в cv::Mat
     */
    static cv::Mat QImageToMat(const QImage& image);
};

#endif // CVHELPER_H

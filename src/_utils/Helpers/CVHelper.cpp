#include "CVHelper.h"

#include <opencv2/core/mat.hpp>

#include <QImage>

using namespace cv;

Mat CVHelper::QImageToMat(const QImage& image)
{
    Mat mat;
    switch(image.format()) {
        case QImage::Format_Invalid:
        {
            break;
        }
        case QImage::Format_RGB32:
        {
            mat = Mat(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());
            break;
        }
        case QImage::Format_RGB888:
        {
            mat = Mat(image.height(),image.width(),CV_8UC3,(void *)image.constBits(),image.bytesPerLine());
            break;
        }
        default:
        {
            QImage conv = image.convertToFormat(QImage::Format_ARGB32);
            mat = Mat(conv.height(),conv.width(),CV_8UC4,(void *)conv.constBits(),conv.bytesPerLine());
            break;
        }
    }
    return mat;
}

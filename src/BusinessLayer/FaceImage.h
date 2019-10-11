#ifndef FACEIMAGE_H
#define FACEIMAGE_H

#include <QImage>
#include <QPointF>

namespace BusinessLayer
{

/**
 * @brief Глаз
 */
class Eye
{
public:
    Eye();
    Eye(const QPointF& center, double width, double height);

    QPointF center() const;
    double width() const;
    double height() const;
    double radius() const;

private:
    QPointF m_center;
    double m_width;
    double m_height;
};

/**
 * @brief Лицо
 */
class Face
{
public:
    Face();
    Face(const QPointF& center, double width, double height);

    QPointF center() const;
    double width() const;
    double height() const;
    double radius() const;

    bool hasLeftEye() const;
    bool hasRightEye() const;
    bool hasBothEyes() const;
    void setLeftEye(const Eye& leftEye);
    void setRightEye(const Eye& rightEye);
    void setEyes(const Eye& leftEye, const Eye& rightEye);
    Eye leftEye();
    Eye rightEye();
    QPair<Eye, Eye> eyes() const;

private:
    QPointF m_center;
    double m_width;
    double m_height;
    bool m_hasLeftEye = false;
    bool m_hasRightEye = false;
    bool m_hasBothEyes = false;
    Eye m_leftEye;
    Eye m_rightEye;
};

/**
 * @brief Изображение с лицами
 */
class FaceImage
{
public:
    FaceImage();

    void setImage(const QImage& image);
    QImage image() const;

    bool hasFaces() const;
    void addFace(const Face& face);
    QVector<Face> faces() const;

private:
    QImage m_image;
    QVector<Face> m_faces;
};

}
#endif // FACEIMAGE_H

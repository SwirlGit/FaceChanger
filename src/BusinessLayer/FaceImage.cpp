#include "FaceImage.h"

namespace BusinessLayer
{

Eye::Eye()
{
}

Eye::Eye(const QPointF& center, double width, double height) :
    m_center(center),
    m_width(width),
    m_height(height)
{
}

QPointF Eye::center() const
{
    return m_center;
}

double Eye::width() const
{
    return m_width;
}

double Eye::height() const
{
    return m_height;
}

double Eye::radius() const
{
    return (m_width + m_height) * 0.25;
}

Face::Face()
{
}

Face::Face(const QPointF& center, double width, double height) :
    m_center(center),
    m_width(width),
    m_height(height)
{
}

QPointF Face::center() const
{
    return m_center;
}

double Face::width() const
{
    return m_width;
}

double Face::height() const
{
    return m_height;
}

double Face::radius() const
{
    return (m_width + m_height) * 0.25;
}

bool Face::hasLeftEye() const
{
    return m_hasLeftEye;
}

bool Face::hasRightEye() const
{
    return m_hasRightEye;
}

bool Face::hasBothEyes() const
{
    return m_hasBothEyes;
}

void Face::setLeftEye(const Eye& leftEye)
{
    m_leftEye = leftEye;
    m_hasLeftEye = true;
    if (m_hasRightEye) {
        m_hasBothEyes = true;
    }
}

void Face::setRightEye(const Eye& rightEye)
{
    m_rightEye = rightEye;
    m_hasRightEye = true;
    if (m_hasLeftEye) {
        m_hasBothEyes = true;
    }
}

void Face::setEyes(const BusinessLayer::Eye &leftEye, const BusinessLayer::Eye &rightEye)
{
    setLeftEye(leftEye);
    setRightEye(rightEye);
    m_hasBothEyes = true;
}

Eye Face::leftEye() const
{
    return m_leftEye;
}

Eye Face::rightEye() const
{
    return m_rightEye;
}

QPair<BusinessLayer::Eye, BusinessLayer::Eye> Face::eyes() const
{
    return {m_leftEye, m_rightEye};
}

FaceImage::FaceImage()
{
}

void FaceImage::setImage(const QImage &image)
{
    m_image = image;
}

QImage FaceImage::image() const
{
    return m_image;
}

bool FaceImage::hasFaces() const
{
    return m_faces.size() > 0;
}

void FaceImage::addFace(const BusinessLayer::Face &face)
{
    m_faces.append(face);
}

QVector<BusinessLayer::Face> FaceImage::faces() const
{
    return m_faces;
}

} // namespace BusinessLayer

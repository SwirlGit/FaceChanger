#include "FaceImageCreator.h"

#include "_utils/Helpers/CVHelper.h"
#include "FaceImage.h"

#include <QDebug>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using BusinessLayer::Eye;
using BusinessLayer::Face;
using BusinessLayer::FaceImage;
using BusinessLayer::OpenCVFaceImageCreator;

OpenCVFaceImageCreator::OpenCVFaceImageCreator()
{
    const String face_cascade_name = "/home/user/opencv/data/haarcascades/haarcascade_frontalface_alt.xml";
    m_faceDetector = new CascadeClassifier();
    if (!m_faceDetector->load(face_cascade_name)) {
        logErrorString("Error loading face cascade by path: " + QString::fromUtf8(face_cascade_name.c_str()));
        return;
    }

    const String eyes_cascade_name = "/home/user/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    m_eyesDetector = new CascadeClassifier();
    if (!m_eyesDetector->load(eyes_cascade_name)) {
        logErrorString("Error loading eyes cascade by path: " + QString::fromUtf8(eyes_cascade_name.c_str()));
        return;
    }

    m_isValid = true;
}

OpenCVFaceImageCreator::~OpenCVFaceImageCreator()
{
    if (m_faceDetector != nullptr) {
        delete m_faceDetector;
    }
    if (m_eyesDetector != nullptr) {
        delete m_eyesDetector;
    }
}

FaceImage OpenCVFaceImageCreator::createFaceImage(const QImage& image) const
{
    // Инициализируем изображение с лицом
    FaceImage faceImage;
    faceImage.setImage(image);

    // Если openCV объект не инициализирован, пишем ошибку и выходим
    static const QString invalidErrorString = "can not create face image: creator is not valid";
    if (!m_isValid) {
        logErrorString(invalidErrorString);
        return faceImage;
    }

    // Переводим наше изображение в GRAY
    Mat imageMat = CVHelper::QImageToMat(faceImage.image());
    Mat frameGray;
    cvtColor(imageMat, frameGray, COLOR_BGR2GRAY);
    equalizeHist(frameGray, frameGray);

    // Находим лица
    std::vector<Rect> faces;
    m_faceDetector->detectMultiScale(frameGray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Для каждого лица ищем глаза
    for(size_t i = 0; i < faces.size(); ++i) {
        // Выделяем участок с лицом
        Mat faceROI = frameGray(faces[i]);

        // Находим глаза
        std::vector<Rect> eyes;
        m_eyesDetector->detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // Формируем лицо с глазами
        Face face({faces[i].x + 0.5 * faces[i].width, faces[i].y + 0.5 * faces[i].height},
                  faces[i].width, faces[i].height);
        for(size_t j = 0; j < eyes.size(); ++j) {
            Eye eye({faces[i].x + eyes[j].x + 0.5 * eyes[j].width, faces[i].y + eyes[j].y + 0.5 * eyes[j].height},
                    eyes[j].width, eyes[j].height);
            eye.center().x() > face.center().x() ? face.setLeftEye(eye) : face.setRightEye(eye);
        }
        faceImage.addFace(face);

        // В случае, если количество найденных глаз для лица не равно двум, информируем
        if (eyes.size() != 2) {
            logErrorString("Number of found eyes is equal to " + QString::number(eyes.size()));
        }
        // В случае, если найдены не все глаза - информируем
        if (!face.hasBothEyes()) {
            logErrorString("Did not found both eyes");
        }
    }

    return faceImage;
}

void OpenCVFaceImageCreator::logErrorString(const QString& errorString) const
{
    static const QString logPrefix = "OpenCVFaceImageCreator: ";
    qDebug() << logPrefix << errorString << endl;
}

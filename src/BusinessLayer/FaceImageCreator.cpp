#include "FaceImageCreator.h"

#include "_utils/Helpers/CVHelper.h"
#include "FaceImage.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QTemporaryDir>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;

namespace {

// Ширина изображения для поиска лиц
const double kDetectionWidth = 640;

} // namespace

namespace BusinessLayer
{

OpenCVFaceImageCreator::OpenCVFaceImageCreator()
{
    QTemporaryDir tempDir;
    if (!tempDir.isValid()) {
        logErrorString("Can not create temporary dir for haarcascade files");
        return;
    }

    // Директория с ресурсами для OpenCV
    const QString resourcesDir = ":/Data/OpenCV";

    // Делаем временную копию файла для определения лица и загружаем
    const QString faceCascadeName = "haarcascade_frontalface_alt.xml";
    const QString faceCascadeResourceFileName = resourcesDir + "/" + faceCascadeName;
    const QString faceCascadeTempFileName = tempDir.path() + "/" + faceCascadeName;
    if (!QFile::copy(faceCascadeResourceFileName, faceCascadeTempFileName)) {
        logErrorString(QString("Can not copy face cascade file %1 to temp file %2")
                       .arg(faceCascadeResourceFileName).arg(faceCascadeTempFileName));
        return;
    }
    m_faceDetector = new CascadeClassifier();
    if (!m_faceDetector->load(faceCascadeTempFileName.toUtf8().constData())) {
        logErrorString("Error loading face cascade by path: " + faceCascadeTempFileName);
        return;
    }

    // Делаем временную копию файла для определения глаз и загружаем
    const QString eyesCascadeName = "haarcascade_eye_tree_eyeglasses.xml";
    const QString eyesCascadeResourceFileName = resourcesDir + "/" + eyesCascadeName;
    const QString eyesCascadeTempFileName = tempDir.path() + "/" + eyesCascadeName;
    if (!QFile::copy(eyesCascadeResourceFileName, eyesCascadeTempFileName)) {
        logErrorString(QString("Can not copy eyes cascade file %1 to temp file %2")
                       .arg(eyesCascadeResourceFileName).arg(eyesCascadeTempFileName));
        return;
    }
    m_eyesDetector = new CascadeClassifier();
    if (!m_eyesDetector->load(eyesCascadeTempFileName.toUtf8().constData())) {
        logErrorString("Error loading eyes cascade by path: " + eyesCascadeTempFileName);
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

    // Сожмем изображение для ускорения
    const double scaleFactor = image.width() > kDetectionWidth ?
                image.width() / kDetectionWidth :
                1.0;
    cv::Mat resizedFrameGray(cvRound(frameGray.rows / scaleFactor), cvRound(frameGray.cols / scaleFactor), CV_8UC1);
    cv::resize(frameGray, resizedFrameGray, resizedFrameGray.size());

    // Находим лица
    std::vector<Rect> faces;
    m_faceDetector->detectMultiScale(resizedFrameGray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));

    // Для каждого лица ищем глаза
    for(size_t i = 0; i < faces.size(); ++i) {
        Mat faceROI = resizedFrameGray(faces[i]);
        std::vector<Rect> eyes;
        m_eyesDetector->detectMultiScale(faceROI, eyes, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // Возвращаем исходные величины до сжатия
        faces[i].x *= scaleFactor;
        faces[i].y *= scaleFactor;
        faces[i].width *= scaleFactor;
        faces[i].height *= scaleFactor;
        Face face({faces[i].x + 0.5 * faces[i].width, faces[i].y + 0.5 * faces[i].height},
                  faces[i].width, faces[i].height);
        for(size_t j = 0; j < eyes.size(); ++j) {
            eyes[j].x *= scaleFactor;
            eyes[j].y *= scaleFactor;
            eyes[j].width *= scaleFactor;
            eyes[j].height *= scaleFactor;
            Eye eye({faces[i].x + eyes[j].x + 0.5 * eyes[j].width, faces[i].y + eyes[j].y + 0.5 * eyes[j].height},
                    eyes[j].width, eyes[j].height);
            eye.center().x() > face.center().x() ? face.setLeftEye(eye) : face.setRightEye(eye);
        }
        faceImage.addFace(face);

        if (eyes.size() != 2) {
            logErrorString("Number of found eyes is equal to " + QString::number(eyes.size()));
        }
        if (!face.hasBothEyes()) {
            logErrorString("Did not found both eyes");
        }
    }
    return faceImage;
}

void OpenCVFaceImageCreator::logErrorString(const QString& errorString) const
{
    static const QString logPrefix = "OpenCVFaceImageCreator: ";
    qDebug() << logPrefix << errorString;
}

} // namespace BusinessLayer

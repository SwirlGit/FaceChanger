#include "FrameCreator.h"

namespace BusinessLayer
{

IFrameCreator::IFrameCreator(QObject *parent) :
    QObject(parent)
{
}

OpenCVFrameCreator::OpenCVFrameCreator(QObject *parent) :
    IFrameCreator(parent)
{
}

void OpenCVFrameCreator::start()
{

}

} // namespace BusinessLayer

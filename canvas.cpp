#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
    setCursor();
}

bool Canvas::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool Canvas::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}


void Canvas::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void Canvas::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void Canvas::setCursor()
{
    pen=false;
     line=false;
     ellipse=false;
     rectangle=false;
     cursor=true;
}

void Canvas::setPen()
{
     pen=true;
     line=false;
     ellipse=false;
     rectangle=false;
     cursor=false;
}

void Canvas::setLine()
{
     pen=false;
     line=true;
     ellipse=false;
     rectangle=false;
     cursor=false;
}

void Canvas::setEllipse()
{
     pen=true;
     line=true;
     ellipse=true;
     rectangle=true;
     cursor=false;
}

void Canvas::setRectangle()
{
     pen=false;
     line=false;
     ellipse=false;
     rectangle=true;
     cursor=false;
}

void Canvas::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(pen)
        {
            lastPoint = event->pos();
            scribbling = true;
        }
        if(line)
        {
         firstPoint= event->pos();
         scribbling=true;
        }
        if(ellipse)
        {
         firstPoint= event->pos();
         scribbling=true;
        }
        if(rectangle)
        {
         firstPoint= event->pos();
         scribbling=true;
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    update();
        if ((event->buttons() & Qt::LeftButton) && scribbling)
        {
            if(pen)
            {
            drawLineTo(event->pos());
            }
            else lastPoint=event->pos();
        }
}
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
        if (event->button() == Qt::LeftButton && scribbling)
        {
            if(pen)
            {
            drawLineTo(event->pos());
            scribbling = false;
            }
            if(line)
            {
                drawLineTo(firstPoint, event->pos());
                update();
                scribbling=false;
            }
            if(ellipse)
            {
             drawEllipse(firstPoint,event->pos());
             update();
             scribbling=false;
            }
            if(rectangle)
            {
             drawRectangle(firstPoint,event->pos());
             update();
             scribbling=false;
            }
        }
}

void Canvas::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
    if(rectangle)
    {
      painter.drawRect(firstPoint.x(),firstPoint.y(),(lastPoint.x()-firstPoint.x()),(lastPoint.y()-firstPoint.y()));
      update();
    }
    if(ellipse)
    {
        painter.drawEllipse(firstPoint,(lastPoint.x()-firstPoint.x()),(lastPoint.y()-firstPoint.y()));
        update();
    }
    if(line)
    {
        painter.drawLine(firstPoint, lastPoint);
        update();
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void Canvas::drawLineTo(const QPoint &endPoint)
{
        QPainter painter(&image);
        painter.setRenderHint( QPainter::Antialiasing );
        painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawLine(lastPoint, endPoint);
        modified = true;

        int rad = (myPenWidth / 2) + 2;
        update(QRect(lastPoint, endPoint).normalized()
                                         .adjusted(-rad, -rad, +rad, +rad));
        lastPoint = endPoint;
}

void Canvas::drawLineTo(const QPoint &firstPoint, const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(firstPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
}

void Canvas::drawEllipse(const QPoint &firstPoint, const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawEllipse(firstPoint,(endPoint.x()-firstPoint.x()),(endPoint.y()-firstPoint.y()));
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
}

void Canvas::drawRectangle(const QPoint &firstPoint, const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawRect(firstPoint.x(),firstPoint.y(),(endPoint.x()-firstPoint.x()),(endPoint.y()-firstPoint.y()));
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
}
void Canvas::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

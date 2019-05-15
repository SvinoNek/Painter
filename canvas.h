#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>


class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setCursor();
    void setPen();
    void setLine();
    void setEllipse();
    void setRectangle();

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void drawLineTo(const QPoint &firstPoint,const QPoint &endPoint);
    void drawEllipse(const QPoint &firstPoint,const QPoint &endPoint);
    void drawRectangle(const QPoint &firstPoint,const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    bool pen;
    bool line;
    bool ellipse;
    bool rectangle;
    bool cursor;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QPoint firstPoint;
};

#endif // CANVAS_H

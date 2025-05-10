#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget> // 这个必须放前面

#include <QImage>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QClipboard>
#include <QMimeData>
#include <QString>
#include <QKeyEvent>
#include <QProcess>
#include <QApplication>
#include <QSize>
#include <QScreen>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
    QString Title = "PinBrd V0.5";
    
    uint8_t func = 0;
    bool ifTop = true; // 是否置顶
  
    
public slots:
    void keyHandle(uint8_t keyValue, bool ifPress); // 按键处理
    void keyPressEvent(QKeyEvent *event); // 按键按下
    void keyReleaseEvent(QKeyEvent *event); // 按键抬起
    
    void pasteFromClipboard(); // 从剪贴板粘贴内容
    void setImageScale(int scalePercent); // 设置图像缩放比例(百分比)
    void adjustWindowToImage(); // 自动调整窗口大小以适应图片
protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }
private:
    QPoint m_dragPos;
    
private:
    Ui::Widget *ui;
    
    void setTop(uint8_t top); // 是否置顶
    uint8_t key_to_USB(int key, int Vkey); // QT键值转USB键值
    
    void updateImageDisplay();  // 更新图像显示
    
    QLabel *displayLabel;
    QTextEdit *textDisplay;
    QImage currentImage;
    int imageScaleFactor = 100;  // 默认100%缩放
};

#endif // WIDGET_H











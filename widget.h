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
    bool ifTitle = true; // 是否有标题栏
    uint8_t opacity = 10; // 不透明度
    
public slots:
    void keyHandle(uint8_t keyValue, bool ifPress); // 按键处理
    void keyPressEvent(QKeyEvent *event); // 按键按下
    void keyReleaseEvent(QKeyEvent *event); // 按键抬起
    
    void pasteFromClipboard(); // 从剪贴板粘贴内容
    void setImageScale(int scalePercent); // 设置图像缩放比例(百分比)
    void adjustWindowToImage(); // 自动调整窗口大小以适应图片
    
protected:
    void mousePressEvent(QMouseEvent *event) override {
        func = 0; // 测试代码!!!
        if(event->button() == Qt::LeftButton) { // 左键
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
        if(event->button() == Qt::MiddleButton) { // 中键
            this->close(); // 关闭自己
            event->accept();
        }
        if(event->button() == Qt::RightButton) { // 右键
            showMinimized(); // 最小化
            event->accept();
        }
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if(event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }
    void wheelEvent(QWheelEvent *event) override {
        // 获取滚轮滚动方向和距离（像素或角度）
        QPoint angleDelta = event->angleDelta();  // 滚轮角度变化（通常 120 为一格）
        QPoint pixelDelta = event->pixelDelta();  // 像素级滚动（高精度设备如触控板）

        if (!angleDelta.isNull()) {
            if (angleDelta.y() > 0) {
                keyHandle(79, 1);// 按键处理
                //printf("wheelUp\n");
                // 放大或上翻页
            } else {
                keyHandle(80, 1);// 按键处理
                //printf("wheelDown\n");
                // 缩小或下翻页
            }
        }

        event->accept();  // 标记事件已处理
    }
private:
    QPoint m_dragPos;
    
private:
    Ui::Widget *ui;
    
    void setTop(uint8_t top); // 是否置顶
    void setTitleBarVisible(uint8_t title); // 控制标题栏显示
    uint8_t key_to_USB(int key, int Vkey); // QT键值转USB键值
    
    void updateImageDisplay();  // 更新图像显示
    
    QLabel *displayLabel;
    QTextEdit *textDisplay;
    QImage currentImage;
    int imageScaleFactor = 100;  // 默认100%缩放
};

#endif // WIDGET_H











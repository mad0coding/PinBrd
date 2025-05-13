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

#define kv_A			4
#define kv_B			5
#define kv_C			6
#define kv_D			7
#define kv_E			8
#define kv_F			9
#define kv_G			10
#define kv_H			11
#define kv_I			12
#define kv_J			13
#define kv_K			14
#define kv_L			15
#define kv_M			16
#define kv_N			17
#define kv_O			18
#define kv_P			19
#define kv_Q			20
#define kv_R			21
#define kv_S			22
#define kv_T			23
#define kv_U			24
#define kv_V			25
#define kv_W			26
#define kv_X			27
#define kv_Y			28
#define kv_Z			29

#define kv_orig_1		30
#define kv_orig_2		31
#define kv_orig_3		32
#define kv_orig_4		33
#define kv_orig_5		34
#define kv_orig_6		35
#define kv_orig_7		36
#define kv_orig_8		37
#define kv_orig_9		38
#define kv_orig_0		39

#define kv_esc			41
#define kv_space		44
#define kv_right		79
#define kv_left			80
#define kv_down			81
#define kv_up			82

#define kv_wheel_up     240
#define kv_wheel_down   241
#define kv_mouse_l      246
#define kv_mouse_m      247
#define kv_mouse_r      248


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
    void keyHandle(uint8_t keyValue); // 按键处理
    void keyPressEvent(QKeyEvent *event); // 按键按下
    void keyReleaseEvent(QKeyEvent *event); // 按键抬起
    
    void pasteFromClipboard(); // 从剪贴板粘贴内容
    void setImageScale(int scalePercent); // 设置图像缩放比例(百分比)
    void adjustWindowToImage(int frame); // 自动调整窗口大小以适应图片
    
protected:
    void mousePressEvent(QMouseEvent *event) override {
        func = 0; // 测试代码!!!
        if(event->button() == Qt::LeftButton) { // 左键
            keyHandle(kv_mouse_l); // 按键处理
            m_dragPos = event->globalPos() - frameGeometry().topLeft(); // 拖动处理
            event->accept();
        }
        if(event->button() == Qt::MiddleButton) { // 中键
            event->accept();
        }
        if(event->button() == Qt::RightButton) { // 右键
            keyHandle(kv_mouse_r); // 按键处理
            event->accept();
        }
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        func = 0; // 测试代码!!!
        if(event->button() == Qt::LeftButton) { // 左键
            event->accept();
        }
        if(event->button() == Qt::MiddleButton) { // 中键
            keyHandle(kv_mouse_m); // 按键处理
            event->accept();
        }
        if(event->button() == Qt::RightButton) { // 右键
            event->accept();
        }
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if(event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - m_dragPos); // 拖动处理
            event->accept();
        }
    }
    void wheelEvent(QWheelEvent *event) override {
        // 获取滚轮滚动方向和距离(像素或角度)
        QPoint angleDelta = event->angleDelta();  // 滚轮角度变化(一格)
        //QPoint pixelDelta = event->pixelDelta();  // 像素级滚动(高精度设备如触控板)

        if(!angleDelta.isNull()){
            if(angleDelta.y() > 0){ // 放大或上翻页
                keyHandle(kv_wheel_up); // 按键处理
                //printf("wheelUp\n");
            }
            else{ // 缩小或下翻页
                keyHandle(kv_wheel_down); // 按键处理
                //printf("wheelDown\n");
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
    
    void updateImageDisplay(); // 更新图像显示
    
    QLabel *displayLabel;
    QTextEdit *textDisplay;
    QImage currentImage;
    int imageScaleFactor = 100; // 默认100%缩放
};

#endif // WIDGET_H











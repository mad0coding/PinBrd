#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    // 初始化界面
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->setContentsMargins(0, 0, 0, 0); // 移除主布局的外边距
    mainLayout->setSpacing(0); // 移除布局内控件间的间距
    
    // 图像显示区域
    displayLabel = new QLabel(this);
    displayLabel->setAlignment(Qt::AlignCenter);
    displayLabel->setFrameShape(QFrame::NoFrame); // 移除边框
    displayLabel->setMinimumSize(10, 10);
    //displayLabel->setFrameShape(QFrame::Box);
    displayLabel->setWordWrap(true);
    
    // 文本显示区域
    textDisplay = new QTextEdit(this);
    textDisplay->setReadOnly(true);
    textDisplay->setWordWrapMode(QTextOption::WordWrap);
    textDisplay->setVisible(false);
    textDisplay->setFocusPolicy(Qt::NoFocus);
    
    // 粘贴按钮
    //QPushButton *pasteButton = new QPushButton("Paste", this);
    
    mainLayout->addWidget(displayLabel);
    mainLayout->addWidget(textDisplay);
    //mainLayout->addWidget(pasteButton);
    
    // 连接信号槽
    //connect(pasteButton, &QPushButton::clicked, this, &Widget::pasteFromClipboard);
    
    
    setTop(1); // 置顶
    
    
    // 隐藏标题栏（无边框窗口）
//    setWindowFlags(Qt::FramelessWindowHint);
    
//    setStyleSheet("QMainWindow { border: 1px solid #ccc; border-radius: 4px; }");
}

Widget::~Widget(){
    delete ui;
}

void Widget::setTop(uint8_t top) // 是否置顶
{
    if(top == 0) ifTop = false;
    else if(top == 1) ifTop = true;
    else ifTop = !ifTop;
    
    Qt::WindowFlags flags = windowFlags();
    if(ifTop){
        flags |= Qt::WindowStaysOnTopHint;
        this->setWindowTitle("PinBrd V0.5");
    }
    else{
        flags &= ~Qt::WindowStaysOnTopHint;
        this->setWindowTitle("pinBrd V0.5");
    }

    hide(); // 先隐藏
    setWindowFlags(flags);
    show(); // 再显示
}

void Widget::setTitleBarVisible(uint8_t title)
{
    if(title == 0) ifTitle = false;
    else if(title == 1) ifTitle = true;
    else ifTitle = !ifTitle;
    
    // 获取当前窗口标志
    Qt::WindowFlags flags = windowFlags();
    bool wasVisible = isVisible();
    
    if (ifTitle) {
        // 显示标题栏
        flags |= Qt::WindowTitleHint | Qt::WindowSystemMenuHint | 
                Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
        flags &= ~Qt::FramelessWindowHint;
        
        // 恢复正常背景
        setAttribute(Qt::WA_TranslucentBackground, false);
        setStyleSheet("");  // 清除样式表
    } else {
        // 隐藏标题栏
        flags |= Qt::FramelessWindowHint;
        flags &= ~(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | 
                  Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
        
        // 设置阴影效果
        setAttribute(Qt::WA_TranslucentBackground);
        setStyleSheet(
            "Widget {"
            "    background: transparent;"
            "    padding: 6px;"
            "}"
            "QWidget#centralWidget {"
            "    background: white;"
            "    border: 1px solid #CCCCCC;"
            "    border-radius: 2px;"
            "    margin: 0px;"
            "    box-shadow: 3px 3px 10px rgba(0,0,0,0.2);"
            "}"
        );
    }
    
    // 保持窗口可见状态
    if (wasVisible) {
        hide();
        setWindowFlags(flags);
        show();
    } else {
        setWindowFlags(flags);
    }
}

uint8_t Widget::key_to_USB(int key, int Vkey) // QT键值转USB键值
{
    if(Vkey >= 65 && Vkey <= 90) return Vkey - 61;//A~Z(4~29)
    
    if(Vkey >= 49 && Vkey <= 57) return Vkey - 19;//1~9(30~38)
    if(Vkey == 48) return 39;//0
    
    if(key == Qt::Key_Return) return 40;//Return
    if(key == Qt::Key_Escape) return 41;//Escape
    if(key == Qt::Key_Backspace) return 42;//Backspace
    if(key == Qt::Key_Tab) return 43;//Tab
    if(key == Qt::Key_Space) return 44;//Space
    if(Vkey == 189) return 45;//-_
    if(Vkey == 187) return 46;//=+
    if(Vkey == 219) return 47;//[{
    if(Vkey == 221) return 48;//]}
    if(Vkey == 220) return 49;//(|\)
    //if(Vkey == 192) return 50;//`~
    if(Vkey == 186) return 51;//;:
    if(Vkey == 222) return 52;//'"
    if(Vkey == 192) return 53;//`~
    if(Vkey == 188) return 54;//,<
    if(Vkey == 190) return 55;//.>
    if(Vkey == 191) return 56;//(/?)
    if(key == Qt::Key_CapsLock) return 57;//caps lock
    
    if(key >= Qt::Key_F1 && key <= Qt::Key_F12) return key - Qt::Key_F1 + 58;//F1~F12(58~69)
    
    if(key == Qt::Key_Print) return 70;//截图
    if(key == Qt::Key_ScrollLock) return 71;//滚动锁定
    if(key == Qt::Key_Pause) return 72;//暂停键
    if(key == Qt::Key_Insert) return 73;//Insert
    if(key == Qt::Key_Home) return 74;//Home
    if(key == Qt::Key_PageUp) return 75;//上页
    if(key == Qt::Key_Delete) return 76;//Delete
    if(key == Qt::Key_End) return 77;//End
    if(key == Qt::Key_PageDown) return 78;//下页
    if(key == Qt::Key_Right) return 79;//→
    if(key == Qt::Key_Left) return 80;//←
    if(key == Qt::Key_Down) return 81;//↓
    if(key == Qt::Key_Up) return 82;//↑
    if(key == Qt::Key_NumLock) return 83;//NumLock
    if(Vkey == 111) return 84;//(/)
    if(Vkey == 106) return 85;//(*)
    if(Vkey == 109) return 86;//-
    if(Vkey == 107) return 87;//+
    if(key == Qt::Key_Enter) return 88;//Enter
    
    if(Vkey >= 97 && Vkey <= 105) return Vkey - 8;//NUM1~NUM9(89~97)
    if(Vkey == 96) return 98;//NUM0
    
    if(Vkey == 110) return 99;//.
    
    if(key == Qt::Key_Control) return 249;//ctrl
    if(key == Qt::Key_Shift) return 250;//shift
    if(key == Qt::Key_Alt) return 251;//alt
    if(key == 16777250) return 252;//win
    
    return 0;
}

void Widget::keyHandle(uint8_t keyValue, bool ifPress) // 按键处理
{
    //printf("0x%02X  %d  %d\n", func, keyValue, ifPress);
    
    if(!ifPress) return; // 释放沿 跳过
    
    // 快捷键处理
    if(func & 0x01){ // Ctrl
        if(keyValue == 20) this->close(); // Ctrl+Q 关闭自己
        else if(keyValue == 25) pasteFromClipboard(); // Ctrl+V 粘贴
    }
    if(keyValue == 5){ // B 边框
        setTitleBarVisible(0xFF);
    }
    else if(keyValue == 9){ // F 尺寸自适应
        adjustWindowToImage();
    }
    else if(keyValue == 17){ // N 打开新进程
        QProcess process;
        QString exePath = QApplication::applicationFilePath(); // 获取当前exe路径
        process.startDetached(exePath); // 启动新进程 独立运行
    }
    else if(keyValue == 23) setTop(0xFF); // T Top/UnTop
    
    func = 0; // 测试代码!!!
}

void Widget::keyPressEvent(QKeyEvent *event) // 按键按下
{
    if(!isActiveWindow()){ // 若当前为非活动窗口则可能发生切屏
        func = 0;
        return; // 舍弃键值直接返回
    }
    if(event->isAutoRepeat()) return;//若为自动重复触发或正在发送数据则返回
    int key1 = event->key();//读取第一种键值
    int key2 = event->nativeVirtualKey();//读取第二种键值
    
    uint8_t keyValue = key_to_USB(key1, key2); // 映射到USB键值
    
    if(keyValue >= 249 && keyValue <= 252) func |= 0x01 << (keyValue - 249);
    else keyHandle(keyValue, 1);
}

void Widget::keyReleaseEvent(QKeyEvent *event) // 按键抬起
{
    if(event->isAutoRepeat()) return;//若为自动重复触发或正在发送数据则返回
    int key1 = event->key();//读取第一种键值
    int key2 = event->nativeVirtualKey();//读取第二种键值
    
    uint8_t keyValue = key_to_USB(key1, key2);//映射到USB键值
    
    if(keyValue >= 249 && keyValue <= 252) func &= ~(0x01 << (keyValue - 249));
    //else keyHandle(keyValue, 0);
}


void Widget::pasteFromClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    
    // 先隐藏所有显示区域
    displayLabel->setVisible(true);
    textDisplay->setVisible(false);
    
    // 检查剪贴板中是否有图像
    if (clipboard->mimeData()->hasImage()) {
        currentImage = clipboard->image();
        if (!currentImage.isNull()) {
            updateImageDisplay();
            adjustWindowToImage(); // 调整窗口大小
            return;
        }
    }
    
    // 检查剪贴板中是否有文本
    if (clipboard->mimeData()->hasText()) {
        QString text = clipboard->text();
        if (!text.isEmpty()) {
            displayLabel->setVisible(false);
            textDisplay->setVisible(true);
            textDisplay->setPlainText(text);
            return;
        }
    }
    
    // 如果没有有效内容
    displayLabel->setText("剪贴板中没有可显示的文本或图像");
    displayLabel->setPixmap(QPixmap());
}

void Widget::setImageScale(int scalePercent)
{
    if (scalePercent < 10) scalePercent = 10;  // 最小缩放10%
    if (scalePercent > 500) scalePercent = 500;  // 最大缩放500%
    
    imageScaleFactor = scalePercent;
    
    if (!currentImage.isNull()) {
        updateImageDisplay();
    }
}

void Widget::updateImageDisplay()
{
    // 计算缩放后的尺寸
    QSize scaledSize = currentImage.size() * imageScaleFactor / 100;
    
    // 缩放图像并保持宽高比
    QImage scaledImage = currentImage.scaled(
        scaledSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );
    
    // 显示图像
    displayLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void Widget::adjustWindowToImage()
{
    if (currentImage.isNull()) {
        return;  // 如果没有当前图像，不做任何操作
    }

    // 获取当前图像的显示大小（考虑缩放因子）
    QSize imageSize = currentImage.size() * imageScaleFactor / 100;
    
    // 计算窗口边框和布局的额外空间
    int frameWidth = this->frameGeometry().width() - this->width();
    int frameHeight = this->frameGeometry().height() - this->height();
    
    frameWidth = frameHeight = 2; // 现在不考虑边框 直接占满界面

    // 设置新的窗口大小
    resize(imageSize.width() + frameWidth, imageSize.height() + frameHeight);
    
    // 确保窗口不会超出屏幕
    QSize screenSize = QApplication::primaryScreen()->availableSize();
    if (width() > screenSize.width() || height() > screenSize.height()) {
        resize(screenSize * 0.8);  // 如果太大，缩放到屏幕的80%
    }
}



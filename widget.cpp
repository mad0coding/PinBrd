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
    lb_main = new QLabel(this);
    lb_main->setWordWrap(true);
    lb_main->setAlignment(Qt::AlignCenter);
    lb_main->setFrameShape(QFrame::NoFrame); // 移除边框
    lb_main->setMinimumSize(10, 10);
    //lb_main->setFrameShape(QFrame::Box);
    
    // 文本显示区域
    txtEdit_main = new QTextEdit(this);
    txtEdit_main->setVisible(false);
    txtEdit_main->setWordWrapMode(QTextOption::WordWrap);
    txtEdit_main->setReadOnly(true);
    txtEdit_main->setFocusPolicy(Qt::NoFocus);
    txtEdit_main->setAttribute(Qt::WA_TransparentForMouseEvents); // 鼠标事件可穿透
    
    mainLayout->addWidget(lb_main);
    mainLayout->addWidget(txtEdit_main);
    
    
    setTop(1); // 置顶
    setTitleBarVisible(0); // 不显示边框
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
        this->setWindowTitle(Title + Version);
    }
    else{
        flags &= ~Qt::WindowStaysOnTopHint;
        this->setWindowTitle(title + Version);
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
        txtEdit_main->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 鼠标事件不可可穿透
        // 显示标题栏
        flags |= Qt::WindowTitleHint | Qt::WindowSystemMenuHint | 
                Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;
        flags &= ~Qt::FramelessWindowHint;
        
        // 恢复正常背景
        setAttribute(Qt::WA_TranslucentBackground, false);
        setStyleSheet("");  // 清除样式表
    } else {
        txtEdit_main->setAttribute(Qt::WA_TransparentForMouseEvents); // 鼠标事件可穿透
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

void Widget::keyHandle(uint8_t keyValue) // 按键处理
{
    //printf("0x%02X  %d  %d\n", func, keyValue, ifPress);
    
    uint8_t ctrl = func & 0x01, shift = func & 0x02, alt = func & 0x04; // 获取 ctrl shift alt 状态
    
    int8_t dir = 0; // 方向
    
    // 快捷键处理
    switch (keyValue) { // 键值
    case kv_B: // 边框
        setTitleBarVisible(0xFF); // 切换边框显示
        break;
    case kv_F: // 尺寸自适应
        windowAdjust(ctrl ? 0 : 2); // 有ctrl则取消轮廓
        break;
    case kv_N: // 打开新进程
        QProcess::startDetached(QApplication::applicationFilePath()); // 获取当前exe路径并启动新进程 独立运行
        break;
    case kv_T: // 切换置顶
        setTop(0xFF);
        break;
    case kv_V: // 粘贴
        if(!ctrl) break;
        if(!shift) imgScale = 100; // 重置缩放
        clipboardPaste();
        break;
    case kv_Q: // 退出
        if(!ctrl) break; // 有ctrl才执行下面
    case kv_esc:
    case kv_mouse_m: // 退出
        this->close(); // 关闭自己
        break;
    case kv_left:
    case kv_right: // 不透明度
        dir = (keyValue == kv_right ? 1 : -1); // 向右为正
        setWinOpacity(MODE_CHANGE, dir); // 修改窗口不透明度
        break;
    case kv_up:
    case kv_down: // 缩放
        dir = (keyValue == kv_up ? 1 : -1); // 向上为正
        break;
    case kv_wheel_down:
    case kv_wheel_up: // 不透明度/缩放
        dir = (keyValue == kv_wheel_up ? 1 : -1); // 向上为正
        if(ctrl){ // 不透明度
            setWinOpacity(MODE_CHANGE, dir); // 修改窗口不透明度
        }
        else if(shift/* || alt*/){
            if(displayCs == DISPLAY_TXT){
                QScrollBar *horizontalBar = txtEdit_main->horizontalScrollBar(); // 水平滚动条
                // 向下滚动 100 像素
                horizontalBar->setValue(horizontalBar->value() + dir * (-55) * !ifTitle);
            }
        }
        else{ // 缩放
            if(displayCs == DISPLAY_IMG){
                setImgScale(MODE_CHANGE, dir * 10);
                windowAdjust(2);
            }
            else if(displayCs == DISPLAY_TXT){
                QScrollBar *verticalBar = txtEdit_main->verticalScrollBar(); // 垂直滚动条
                // 向下滚动 100 像素
                verticalBar->setValue(verticalBar->value() + dir * (-60) * !ifTitle);
            }
        }
        break;
    case kv_mouse_r: // 最小化
        showMinimized(); // 窗口最小化
        break;
    default:
        break;
    }
    
    //func = 0; // 测试代码!!!
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
    else keyHandle(keyValue);
}

void Widget::keyReleaseEvent(QKeyEvent *event) // 按键抬起
{
    if(event->isAutoRepeat()) return;//若为自动重复触发或正在发送数据则返回
    int key1 = event->key();//读取第一种键值
    int key2 = event->nativeVirtualKey();//读取第二种键值
    
    uint8_t keyValue = key_to_USB(key1, key2);//映射到USB键值
    
    if(keyValue >= 249 && keyValue <= 252) func &= ~(0x01 << (keyValue - 249));
}


void Widget::clipboardPaste()
{
    QClipboard *clipboard = QApplication::clipboard();
    
    // 先隐藏所有显示区域
//    lb_main->setVisible(true);
//    txtEdit_main->setVisible(false);
    
    bool hasImg = false;
    
    // 检查剪贴板内容
    do{
        if(clipboard->mimeData()->hasImage()){ // 有图像
            mainImage = clipboard->image();
        }
        else if(clipboard->mimeData()->hasUrls()){ // 有文件路径
            QUrl url = clipboard->mimeData()->urls().at(0); // 只取第一个
            QString filePath = url.toLocalFile(); // 转文件路径
            QFileInfo fileInfo(filePath);
            QString suffix = fileInfo.suffix().toLower();
            if(!fileInfo.exists() || !fileInfo.isFile()) break; // 文件不存在或不是普通文件
            
            static const QStringList imageExtensions = { // 支持的图片扩展名列表
                "png", "jpg", "jpeg", "bmp", "webp", "gif", "tiff"
            };
            if(!imageExtensions.contains(suffix)) break; // 扩展名不匹配
            
            QImage tmpImage;
            if(!tmpImage.load(filePath)) break; // 加载失败
            mainImage = tmpImage;
        }
        else break;
        if(!mainImage.isNull()) mainTxt = ""; // 清空文本
        hasImg = true;
    } while (0);
    if(!hasImg && clipboard->mimeData()->hasHtml()){ // 无图像 有富文本 测试代码!!!
        mainTxt = clipboard->mimeData()->html();
        if(!mainTxt.isEmpty()) mainImage = QImage(); // 清空图像
    }
    else if(!hasImg && clipboard->mimeData()->hasText()){ // 无图像 有文本
        mainTxt = clipboard->text();
        if(!mainTxt.isEmpty()) mainImage = QImage(); // 清空图像
    }
    
    // 显示
    if(!mainImage.isNull()){ // 有图像
        txtEdit_main->setVisible(false); // 隐藏文本显示
        lb_main->setVisible(true); // 启用图像显示
        imageUpdate();
        windowAdjust(2); // 调整窗口大小
        displayCs = DISPLAY_IMG;
    }
    else if(!mainTxt.isEmpty()){ // 有文本
        lb_main->setVisible(false); // 隐藏图像显示
        txtEdit_main->setVisible(true); // 启用文本显示
        //txtEdit_main->setPlainText(mainTxt); // 设置文本
        txtEdit_main->setHtml(mainTxt); // 设置Html文本
        displayCs = DISPLAY_TXT;
    }
    else{ // 都没有
        lb_main->setText("剪贴板中没有可显示的文本或图像"); // 测试代码!!!
        lb_main->setPixmap(QPixmap());
        displayCs = DISPLAY_NONE;
    }
}

void Widget::setImgScale(uint8_t mode, int value) // 设置图像缩放
{
    if(mode == MODE_CHANGE) imgScale += value; // 增量式
    else if(mode == MODE_SET) imgScale = value; // 赋值式
    
    imgScale = LIMIT(imgScale, 10, 500); // 范围10%~500%
    
    if(!mainImage.isNull()) imageUpdate();
}

void Widget::setWinOpacity(uint8_t mode, int value) // 设置窗口不透明度
{
    if(mode == MODE_CHANGE) winOpacity += value; // 增量式
    else if(mode == MODE_SET) winOpacity = value; // 赋值式
    
    winOpacity = LIMIT(winOpacity, 1, 10); // 范围1/10~10/10
    
    setWindowOpacity((double)winOpacity / 10); // 设置窗口不透明度
}

void Widget::imageUpdate()
{
    // 计算缩放后的尺寸
    QSize scaledSize = mainImage.size() * imgScale / 100;
    
    // 缩放图像并保持宽高比
    QImage scaledImage = mainImage.scaled(
        scaledSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );
    
    // 显示图像
    lb_main->setPixmap(QPixmap::fromImage(scaledImage));
}

void Widget::windowAdjust(int frame)
{
    if(mainImage.isNull()) return; // 如果没有当前图像 不做任何操作

    // 获取当前图像的显示大小(考虑缩放因子)
    QSize imageSize = mainImage.size() * imgScale / 100;
    
    // 计算窗口边框和布局的额外空间 这个暂时无视
    int frameWidth = this->frameGeometry().width() - this->width();
    int frameHeight = this->frameGeometry().height() - this->height();
    
    frameWidth = frameHeight = frame; // 预留frame宽度

    // 设置新的窗口大小
    resize(imageSize.width() + frameWidth, imageSize.height() + frameHeight);
    
    // 确保窗口不会超出屏幕
//    QSize screenSize = QApplication::primaryScreen()->availableSize();
//    if (width() > screenSize.width() || height() > screenSize.height()) {
//        resize(screenSize * 0.8);  // 如果太大，缩放到屏幕的80%
//    }
}



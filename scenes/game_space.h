#include <QtOpenGLWidgets/QOpenGLWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class game_space; }
QT_END_NAMESPACE

class game_space : public QOpenGLWidget {
    Q_OBJECT
public:
    explicit game_space(QWidget *parent = nullptr);
    ~game_space() override;
private:
    QBackingStore *m_backingStore;
    Ui::game_space *ui;
    public slots:
};

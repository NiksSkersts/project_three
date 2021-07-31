#include "main_menu.h"

main_menu::main_menu(QWindow *parent): QWindow(parent), m_backingStore(new QBackingStore(this))
{
    this->setMinimumHeight(400);
    this->setMinimumWidth(400);
    setGeometry(100, 100, 300, 200);
}
void main_menu::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        renderNow();
}
void main_menu::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
}
void main_menu::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), QGradient::NightFade);
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}
void main_menu::render(QPainter *painter)
{
    painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));
}
void main_menu::renderLater()
{
    requestUpdate();
}
bool main_menu::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}
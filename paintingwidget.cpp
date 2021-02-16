#include "paintingwidget.h"
#include "ui_paintingwidget.h"

PaintingWidget::PaintingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintingWidget)
{
    ui->setupUi(this);
    _matrix = std::make_unique<Matrix<double>>(Matrix<double>(pixelsCount,pixelsCount, false));
}

void PaintingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);


    drawGrind(painter);

    if(isClicked)
    {
        fillCell(painter);
        updateCells(painter);
        isClicked = false;
    }

}

void PaintingWidget::mousePressEvent(QMouseEvent *event)
{
    clickPoint = event->pos();
    isClicked = true;
    update();
}

void PaintingWidget::fillCell(QPainter &painter)
{
    int column = clickPoint.x() / horizontalStep, row = clickPoint.y() / verticalStep;

    if ((*_matrix)(row, column))
        (*_matrix)(row, column) = 0;
    else
        (*_matrix)(row, column) = 1;
    _matrix->printToFile();
}

void PaintingWidget::drawGrind(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));

    horizontalStep = static_cast<double>(width()) / pixelsCount;
    verticalStep = static_cast<double>(height()) / pixelsCount;

    double x = 0, y = 0;

    for (int i = 0; i <= pixelsCount; i++)
    {
        painter.drawLine(x, 0, x, height());
        x += horizontalStep;
        painter.drawLine(0, y, width(), y);
        y += verticalStep;
    }
    painter.setPen(nullptr);
}

void PaintingWidget::updateCells(QPainter &painter)
{
    painter.setBrush(Qt::red);
    for (size_t i = 0; i < pixelsCount; i++)
    {
        for (size_t j = 0; j < pixelsCount; j++)
            if ((*_matrix)(i,j))
            {
                painter.drawRect(j * horizontalStep + 2, i * verticalStep + 2, horizontalStep - 4, verticalStep - 4);
            }
    }
}

std::unique_ptr<Matrix<double>> PaintingWidget::getMatrix()
{
    auto ret = std::move(_matrix);
    _matrix = std::make_unique<Matrix<double>>(Matrix<double>(pixelsCount, pixelsCount,0));
    update();
    return std::move(ret);
}

PaintingWidget::~PaintingWidget()
{
    delete ui;
}

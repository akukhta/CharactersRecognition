#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include "matrix.h"

namespace Ui {
class PaintingWidget;
}

class PaintingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintingWidget(QWidget *parent = nullptr);
    ~PaintingWidget();
    std::unique_ptr<Matrix<double>> getMatrix();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void drawGrind(QPainter &painter);
    Ui::PaintingWidget *ui;
    bool isClicked = false;
    void fillCell(QPainter &painter);
    void updateCells(QPainter &painter);
    double horizontalStep, verticalStep;
    size_t const pixelsCount = 8;
    QPoint clickPoint;
    std::unique_ptr<Matrix<double>> _matrix;
};


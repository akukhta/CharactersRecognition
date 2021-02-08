#pragma once

#include <QMainWindow>
#include <fstream>
#include <string>
#include "paintingwidget.h"
#include "neuralnetwork.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    std::ofstream trainingSet;
    std::vector<std::pair<std::unique_ptr<Matrix<double>>, std::vector<double>>> traines;
    std::unique_ptr<NeuralNetwork> net;
};


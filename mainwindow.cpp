#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItems({"Learning", "Recognition"});
    ui->comboBox_2->addItems({"K", "U", "H", "T"});
    trainingSet.open("tmp.txt");
    net = std::make_unique<NeuralNetwork>(4,64);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto matrix = ui->paintingWidget->getMatrix();
    std::vector<double> values{0,0,0,0};
    values[ui->comboBox_2->currentIndex()] = 1;
    traines.push_back(std::make_pair(std::move(matrix), values));
}

void MainWindow::on_pushButton_2_clicked()
{
    trainingSet << traines.size() << std::endl;

    for (auto & x : traines)
    {
        for (size_t i = 0; i < x.first->dim().first; i++)
            for (size_t j = 0; j < x.first->dim().second; j++)
                    trainingSet << (*x.first)(i,j) << std::endl;

            for (size_t i = 0; i < 4; i++)
                trainingSet << x.second[i] << std::endl;

    }

    trainingSet.close();
    traines.clear();
    std::filesystem::rename("tmp.txt","trainingSet.txt");

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (ui->comboBox->currentIndex() == 0)
    {
        ui->pushButton_3->setVisible(false);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_5->setVisible(false);
        ui->label_2->setVisible(true);
        ui->comboBox_2->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
    }
    else
    {
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->label_2->setVisible(false);
        ui->comboBox_2->setVisible(false);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    net->saveWeigths();
}

void MainWindow::on_pushButton_3_clicked()
{
    for(size_t i = 0; i < 20; i++)
        net->train("trainingSet.txt",15000);
    net->saveErrors();
    ui->textBrowser->append("Trained!\n");
}

void MainWindow::on_pushButton_5_clicked()
{
    auto result = net->predict(ui->paintingWidget->getMatrix()->toVector());
    ui->textBrowser->clear();
    ui->textBrowser->append("K:" + QString::number(result[0]) + "%\n");
    ui->textBrowser->append("U:" + QString::number(result[1]) + "%\n");
    ui->textBrowser->append("H:" + QString::number(result[2]) + "%\n");
    ui->textBrowser->append("T:" + QString::number(result[3]) + "%\n");
}

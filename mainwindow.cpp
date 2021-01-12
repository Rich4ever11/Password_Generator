#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #F7F7F7; color: black;");
    ui->spinBox->setMaximum(4096);
    ui->spinBox->setMinimum(6);
    ui->lineEdit->setReadOnly(true);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    QWidget::setWindowTitle("Secured Password Generator");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generateButton_clicked()
{
    ui->lineEdit->setText("");
    std::string password = "";
    std::vector<std::vector<char>> pass_key = {};
    bool add_lower = ui->checkBox_3->isChecked();
    bool add_Upper = ui->checkBox_4->isChecked();
    bool add_num = ui->checkBox_2->isChecked();
    bool no_repeat = ui->checkBox_5->isChecked();
    int pass_lenght = ui->spinBox->value();
    bool add_special_char = ui->Special_Characters->isChecked();
    if (add_lower) {
        pass_key.push_back({'a','b', 'c','d', 'e','f','g','h','i','j','k', 'l','m','n','o','p','q','r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'});
    }
    if (add_special_char) {
        pass_key.push_back({'!','"','#', '$', '%','&', '(',')','*','+',',','-','.','/',':',';', '<','=','>','?','@','[',
                           ']','^','_','`','{','|','}','~', '\''});
    }
    if (add_Upper) {
        pass_key.push_back({'A','B', 'C','D', 'E','F','G','H','I','J','K', 'L','M','N','O','P','Q','R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});
    }
    if (add_num) {
        pass_key.push_back({'1','2','3','4','5','6','7','8','9','0'});
    }
    if (no_repeat && (!pass_key.empty())) {
        if (pass_lenght - 1 > 92) {
            pass_lenght = 92;
            ui->spinBox->setValue(92);
        }
        int max_lists = pass_key.size();
        int rand_list = 0;
        int rand_char = 0;
        for (int i = 0; i < pass_lenght; i++) {
            rand_list = rand() % max_lists;
            rand_char = rand() % pass_key[rand_list].size();
            if (password.find(pass_key[rand_list][rand_char]) == std::string::npos) {
                password += pass_key[rand_list][rand_char];
            }
        }
    }
    else if ((!pass_key.empty())) {
        int max_lists = pass_key.size();
        int rand_list = 0;
        int rand_char = 0;
        for (int i = 0; i < pass_lenght; i++) {
            rand_list = rand() % max_lists;
            rand_char = rand() % pass_key[rand_list].size();
            password += pass_key[rand_list][rand_char];
        }
    }
    QString qpassword = QString::fromStdString(password);
    if (qpassword == "") {
        ui->lineEdit->insert("Please Choose A Valid Option");
    }
    ui->lineEdit->insert(qpassword);
}


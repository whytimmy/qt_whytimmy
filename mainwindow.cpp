#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "secondwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->resize(400, 300);

    QGroupBox *authorizationGroup = new QGroupBox("Авторизация", this);

    QLabel *labelUsername = new QLabel("Имя пользователя:", this);
    QLabel *labelPassword = new QLabel("Пароль:", this);

    QLineEdit *lineEditUsername = new QLineEdit(this);
    QLineEdit *lineEditPassword = new QLineEdit(this);
    lineEditPassword->setEchoMode(QLineEdit::Password);

    QPushButton *buttonLogin = new QPushButton("Войти", this);

    // Используем QFormLayout для красивой и логичной компоновки элементов
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(labelUsername, lineEditUsername); // Добавляем строку: метка и поле ввода для имени пользователя
    formLayout->addRow(labelPassword, lineEditPassword); // Добавляем строку: метка и поле ввода для пароля

    // Добавляем кнопку под формой
    QVBoxLayout *groupBoxLayout = new QVBoxLayout();
    groupBoxLayout->addLayout(formLayout);
    groupBoxLayout->addWidget(buttonLogin, 0, Qt::AlignCenter); // Размещаем кнопку по центру

    // Устанавливаем компоновку для QGroupBox
    authorizationGroup->setLayout(groupBoxLayout);

    // Создаем основной layout для окна, чтобы элементы центрировались
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(authorizationGroup, 0, Qt::AlignCenter); // Центрируем QGroupBox

    // Создаем центральный виджет и применяем к нему основной layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(buttonLogin, &QPushButton::clicked, this, [this, lineEditUsername, lineEditPassword]() {
        // Проверяем введенные данные
        QString username = lineEditUsername->text();
        QString password = lineEditPassword->text();

        if (username == "tim" && password == "1234") {
            // Если логин и пароль верны, открываем второе окно
            hide();
            SecondWindow *secondWindow = new SecondWindow();
            secondWindow->show();
        } else {
            // Показываем сообщение об ошибке
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

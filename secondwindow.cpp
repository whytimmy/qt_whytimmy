#include "secondwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

SecondWindow::SecondWindow(QWidget *parent) : QWidget(parent), firstNum(0), userIsTypingSecondNumber(false)
{
    this->setWindowTitle("Калькулятор");
    this->resize(300, 400);

    // Создаем элементы интерфейса
    display = new QLineEdit("0", this);
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);
    display->setMinimumHeight(50);

    // Кнопки
    QPushButton *button0 = new QPushButton("0", this);
    QPushButton *button1 = new QPushButton("1", this);
    QPushButton *button2 = new QPushButton("2", this);
    QPushButton *button3 = new QPushButton("3", this);
    QPushButton *button4 = new QPushButton("4", this);
    QPushButton *button5 = new QPushButton("5", this);
    QPushButton *button6 = new QPushButton("6", this);
    QPushButton *button7 = new QPushButton("7", this);
    QPushButton *button8 = new QPushButton("8", this);
    QPushButton *button9 = new QPushButton("9", this);


    buttonPlus = new QPushButton("+", this);
    buttonMinus = new QPushButton("-", this);
    buttonMultiply = new QPushButton("*", this);
    buttonDivide = new QPushButton("/", this);
    buttonEquals = new QPushButton("=", this);
    buttonClear = new QPushButton("C", this);
    buttonDecimal = new QPushButton(".", this);

    buttonPlus->setCheckable(true);
    buttonMinus->setCheckable(true);
    buttonMultiply->setCheckable(true);
    buttonDivide->setCheckable(true);

    // Layout для размещения кнопок
    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->addWidget(button7, 0, 0);
    buttonLayout->addWidget(button8, 0, 1);
    buttonLayout->addWidget(button9, 0, 2);
    buttonLayout->addWidget(buttonDivide, 0, 3);

    buttonLayout->addWidget(button4, 1, 0);
    buttonLayout->addWidget(button5, 1, 1);
    buttonLayout->addWidget(button6, 1, 2);
    buttonLayout->addWidget(buttonMultiply, 1, 3);

    buttonLayout->addWidget(button1, 2, 0);
    buttonLayout->addWidget(button2, 2, 1);
    buttonLayout->addWidget(button3, 2, 2);
    buttonLayout->addWidget(buttonMinus, 2, 3);

    buttonLayout->addWidget(button0, 3, 0);
    buttonLayout->addWidget(buttonDecimal, 3, 1);
    buttonLayout->addWidget(buttonEquals, 3, 2);
    buttonLayout->addWidget(buttonPlus, 3, 3);

    // Основной layout для окна
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(display);       // Добавляем поле для вывода
    mainLayout->addLayout(buttonLayout);  // Добавляем кнопки

    setLayout(mainLayout);

    // Соединение кнопок с обработчиками сигналов
    connect(button0, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button1, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button2, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button3, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button4, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button5, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button6, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button7, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button8, &QPushButton::released, this, &SecondWindow::digitPressed);
    connect(button9, &QPushButton::released, this, &SecondWindow::digitPressed);

    connect(buttonPlus, &QPushButton::released, this, &SecondWindow::binaryOperationPressed);
    connect(buttonMinus, &QPushButton::released, this, &SecondWindow::binaryOperationPressed);
    connect(buttonMultiply, &QPushButton::released, this, &SecondWindow::binaryOperationPressed);
    connect(buttonDivide, &QPushButton::released, this, &SecondWindow::binaryOperationPressed);

    connect(buttonEquals, &QPushButton::released, this, &SecondWindow::on_pushButton_equals_clicked);
    connect(buttonClear, &QPushButton::released, this, &SecondWindow::on_pushButton_clear_clicked);
    connect(buttonDecimal, &QPushButton::released, this, &SecondWindow::on_pushButton_decimal_clicked);
}

void SecondWindow::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonValue = button->text();
    QString displayValue = display->text();

    if ((displayValue.toDouble() == 0 && !displayValue.contains('.')) || userIsTypingSecondNumber)
    {
        display->setText(buttonValue);
        userIsTypingSecondNumber = false;
    }
    else
    {
        display->setText(displayValue + buttonValue);
    }
}

void SecondWindow::binaryOperationPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    firstNum = display->text().toDouble();
    button->setChecked(true);
    userIsTypingSecondNumber = true;
}

void SecondWindow::on_pushButton_equals_clicked()
{
    double secondNum = display->text().toDouble();
    double result = 0.0;

    if (buttonPlus->isChecked()) {
        result = firstNum + secondNum;
        buttonPlus->setChecked(false);
    }
    else if (buttonMinus->isChecked()) {
        result = firstNum - secondNum;
        buttonMinus->setChecked(false);
    }
    else if (buttonMultiply->isChecked()) {
        result = firstNum * secondNum;
        buttonMultiply->setChecked(false);
    }
    else if (buttonDivide->isChecked()) {
        if (secondNum == 0.0) {
            display->setText("Error");
            return;
        }
        result = firstNum / secondNum;
        buttonDivide->setChecked(false);
    }

    display->setText(QString::number(result));
    userIsTypingSecondNumber = true;
}

void SecondWindow::on_pushButton_clear_clicked()
{
    // Сброс всех операций и экрана
    buttonPlus->setChecked(false);
    buttonMinus->setChecked(false);
    buttonMultiply->setChecked(false);
    buttonDivide->setChecked(false);

    userIsTypingSecondNumber = false;
    display->setText("0");
}



void SecondWindow::on_pushButton_decimal_clicked()
{
    // Добавляем десятичную точку, если её ещё нет
    QString displayValue = display->text();
    if (!displayValue.contains('.')) {
        display->setText(displayValue + ".");
    }
}

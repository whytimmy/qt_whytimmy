#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QLineEdit>  // Добавляем этот include
#include <QPushButton>

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);

private slots:
    void digitPressed();
    void binaryOperationPressed();
    void on_pushButton_equals_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_decimal_clicked();

private:
    QLineEdit *display;  // Поле для отображения чисел
    double firstNum;
    bool userIsTypingSecondNumber;
    QPushButton *buttonPlus;
    QPushButton *buttonMinus;
    QPushButton *buttonMultiply;
    QPushButton *buttonDivide;
    QPushButton *buttonEquals;
    QPushButton *buttonClear;
    QPushButton *buttonDecimal;

};

#endif // SECONDWINDOW_H

#ifndef COMPARISON_FILE_H
#define COMPARISON_FILE_H

#include <QDialog>

namespace Ui {
class comparison_file;
}

class comparison_file : public QDialog
{
    Q_OBJECT

public:
    explicit comparison_file(QWidget *parent = nullptr);
    ~comparison_file();



private slots:
    void on_comparison_clicked();

private:
    Ui::comparison_file *ui;
};

#endif // COMPARISON_FILE_H

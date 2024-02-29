#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void passDataButtonClicked(const QString &data);

private slots:
    void onPassDataButtonClicked();

private:
    QPushButton *m_passDataButton;
};

#endif // MAINWINDOW_H

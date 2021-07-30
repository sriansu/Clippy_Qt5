#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QClipboard>
#include<QTimer>
#include<QStringListModel>
#include<QList>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include<QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Clippy; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionnew_triggered();

    void on_actioncut_triggered();

    void on_actionopen_triggered();

    void on_actioncopy_page_triggered();

    void on_actionpage_paste_triggered();

    void on_actionsave_triggered();

    void on_actionsave_As_triggered();

    void on_actionstart_triggered();

    void on_actionstop_triggered();

    void on_actiondelete_triggered();

    void timeout();

private:
    Ui::Clippy *ui;
    //vars
    QTimer m_timer;
    QString m_last;
    QStringListModel m_model;
    QStringList m_list;
    QString m_path;
    bool m_changed;

    void init();
    void check_saved();
    // QPaintDevice interface
//public:
//    QPaintEngine *paintEngine() const override;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
